#include <stdio.h>
#include <assert.h>

#include <editline/readline.h>
#include "mpc.h"

/* Assert condition holds */
#define LASSERT(args, cond, n, rest, err...)								\
	if (!(cond)) { lval_del(n+1, args, rest); return lval_err("%s: condition %s does not hold!", err); }   

/* Assert lval has cnt cells */
#define CASSERT(args, cnt, n, rest, name)							\
	if (args->count != cnt) { lval_del(n+1, args, rest); return lval_err("%s: lval has wrong number of members! Expected %u, got %u", name, cnt, args->count); }

/* Assert lval does no contain the empty expression */
#define EASSERT(args, n, rest, name)											\
	for (int i = 0; i < args->count; i++) {								\
	if (args->cell[i]->count == 0) { lval_del(n+1, args, rest); return lval_err("%s: lval contains empty sexpr at position %i!", name, i); } \
}

/* Assert lval is of type t */
#define TASSERT(args, i, t, n, rest, name)								\
	if (args->cell[i]->type != t) { lval_del(n+1, args, rest); return lval_err("%s: lval has wrong type! Expected %s, got %s", name, ltype_name(t), ltype_name(args->cell[i]->type)); }

struct lval;
struct lenv;
typedef struct lval lval;
typedef struct lenv lenv;

/* Declare enum for possible lval types*/
enum { LVAL_NUM, LVAL_ERR, LVAL_SYM, LVAL_SEXPR, LVAL_QEXPR, LVAL_FUN, LVAL_BUILTIN };

char* ltype_name (int t) {
	switch (t) {
	case LVAL_NUM: return "Number";
	case LVAL_ERR: return "Error";
	case LVAL_SYM: return "Symbol";
	case LVAL_SEXPR: return "S-expression";
	case LVAL_QEXPR: return "Q-expression";
	case LVAL_FUN: return "Function";
	case LVAL_BUILTIN: return "Builtin function";
	default: return "Unknown type";
	}
}		

typedef lval*(*lbuiltin)(lenv*, lval*);

/* Declare new Lisp Value struct*/
struct lval {
    unsigned int type;
    long num;
    /* error and symbol lvals have a string*/
    char* err;
    char* sym;
	/* function pointer */
	lbuiltin builtin;
	lenv* env;
	lval* formals;
	lval* body;
	
    /* double pointer to the children*/
    struct lval** cell;
    unsigned int count;
};

struct lenv {
	int count;
	char** symbols;
	lval** lvals;
};

/* Creates a new number lval*/
lval* lval_num (long x) {
    lval* v = calloc(1, sizeof(lval));
    v->type = LVAL_NUM;
    v->num = x;
    return v;
}

/* Creates a new error lval*/
lval* lval_err (char* fmt, ...) {
    lval* v = calloc(1, sizeof(lval));
    v->type = LVAL_ERR;

	va_list va;
	va_start(va, fmt);
	v->err = malloc(512);
	vsnprintf(v->err, 511, fmt, va);
    v->err = realloc(v->err, strlen(v->err) + 1);
	va_end(va);
    return v;
}

lval* lval_sym (char* m) {
    lval* v = calloc(1, sizeof(lval));
    v->type = LVAL_SYM;
    v->sym = malloc(strlen(m) + 1);
    strcpy(v->sym, m);
    return v;
}

lval* lval_sexpr (void) {
    lval* v = calloc(1, sizeof(lval));
    v->type = LVAL_SEXPR;
    v->count = 0;
    v->cell = NULL;
    return v;
}

lval* lval_qexpr (void) {
    lval* v = calloc (1, sizeof (lval));
    v->type = LVAL_QEXPR;
    v->count = 0;
    v->cell = NULL;
    return v;
}

lval* lval_builtin (lbuiltin builtin) {
	lval* v = calloc (1, sizeof (lval));
	v->type = LVAL_BUILTIN;
	v->builtin = builtin;
	return v;
}

lenv* lenv_new (void);

lval* lval_fun (lval* formals, lval* body) {
	lval* v = calloc (1, sizeof (lval));
	v->type = LVAL_FUN;
	v->formals = formals;
	v->body = body;
	v->env = lenv_new();
	return v;
}

void lenv_del (lenv*);

void lval_del(int n, ...) {
	va_list list;
	va_start(list, n);

	for (int i = 0; i < n; i++) {
		lval* v = va_arg(list, lval*);
		
		switch (v->type) {
			/* Do nothing special for number and lbuiltin type*/
		case LVAL_NUM: break;
		case LVAL_BUILTIN: break;
			/* For Err or Sym free the string data*/
		case LVAL_FUN:
			lenv_del(v->env);
			lval_del(1, v->formals);
			lval_del(1, v->body);
			break;
		case LVAL_ERR: free(v->err); break;
		case LVAL_SYM: free(v->sym); break;
			/* If Sexpr then delete all elements inside*/
		case LVAL_SEXPR:
		case LVAL_QEXPR:
			for (int i = 0; i < v->count; i++) {
				lval_del(1, v->cell[i]);
			}
			/* Also free the memory allocated to contain the pointers*/
			free(v->cell);
			break;
		}
		/* Free the memory allocated for the "lval" struct itself*/
		free(v);
	}

	va_end(list);
}

lenv* lenv_new (void) {
	lenv* e = calloc(1, sizeof(lenv));
	e->count = 0;
	e->symbols = NULL;
	e->lvals = NULL;
	return e;
}

void lenv_del (lenv* e) {
	for (int i = 0; i < e->count; i++) {
		free(e->symbols[i]);
		lval_del(1, e->lvals[i]);
	}
	free(e->symbols);
	free(e->lvals);
	free(e);
}

lval* lval_copy (lval*);

lenv* lenv_copy (lenv* e) {
	lenv* env = lenv_new();
	env->count = e->count;
	env->symbols = malloc (env->count * sizeof(char*));
	env->lvals = malloc (env->count * sizeof(lval*));

	for (int i = 0; i < e->count; i++) {
		env->symbols[i] = malloc(strlen(e->symbols[i]) + 1);
		strcpy(env->symbols[i], e->symbols[i]);
		env->lvals[i] = lval_copy(e->lvals[i]);
	}
}

void lval_print (lval* v);

void lval_print_expr (lval* v, char open, char close) {
    putchar(open);
    for (int i = 0; i < v->count; i++) {
		lval_print(v->cell[i]);

		if (i != v->count-1) {
			putchar(' ');
		}
    }
    putchar(close);
} 

/* Print an "lval"*/
void lval_print(lval* v) {
    switch (v->type) {
		/* In the case the type is a number print it*/
    case LVAL_NUM: printf("%li", v->num); break;
    case LVAL_SYM: printf("%s", v->sym); break;
    case LVAL_ERR: printf("Error: %s", v->err); break;
    case LVAL_SEXPR: lval_print_expr (v, '(', ')'); break;
    case LVAL_QEXPR: lval_print_expr (v, '{', '}'); break;
	case LVAL_BUILTIN: printf("<builtin function>"); break;
	case LVAL_FUN:
		printf("(\\ "); lval_print(v->formals);
		putchar(' ');  lval_print(v->body); putchar(')');
		break;
    }
}

/* Print an "lval" followed by a newline*/
void lval_println(lval* v) { lval_print(v); putchar('\n'); }

lval* lval_read_num (mpc_ast_t* t) {
    errno = 0;
    long x = strtol(t->contents, NULL, 10);
    return errno != ERANGE ? lval_num(x) : lval_err("invalid number"); 
}

/* Change to return null and set errno on error */
lval* lval_pop (lval* v, unsigned int i) {
    LASSERT(v, i < v->count, 0, NULL, "lval_pop", "index in range of v->count");
    
    lval* x = v->cell[i];
    memmove (&v->cell[i], &v->cell[i+1], sizeof (lval*) * (v->count - i - 1));
    v->count--;
    v->cell = realloc (v->cell, sizeof (lval*) * v->count);
    return x;
}

lval* lval_take (lval* v, unsigned int i) {
    lval* x = lval_pop (v, i);
    lval_del (1, v);
    return x;
}

lval* lval_copy (lval* v) {
	
	lval* w = calloc(1, sizeof(lval));
	w->type = v->type;
	
	switch (v->type) {
	case LVAL_NUM:
		w->num = v->num;
		break;
	case LVAL_BUILTIN:
		w->builtin = v->builtin;
		break;
	case LVAL_FUN:
		w->env = lenv_copy(v->env);
		w->formals = lval_copy(v->formals);
		w->body = lval_copy(v->body);
		break;
	case LVAL_SYM:
		w->sym = malloc(strlen(v->sym)+1);
		strncpy(w->sym, v->sym, strlen(v->sym)+1);
		break;
	case LVAL_ERR:
		w->err = malloc(strlen(v->err)+1);
		strncpy(w->err, v->err, strlen(v->err)+1);
		break;
	case LVAL_QEXPR:
	case LVAL_SEXPR:
		w->count = v->count;
		w->cell = calloc(v->count, sizeof(lval*));
		for (int i = 0; i < v->count; i++) {
			w->cell[i] = lval_copy(v->cell[i]);
		}
		break;
	}

	return w;
}

lval* lenv_get (lenv* env, lval* s) {
	for (int i = 0; i < env->count; i++) {
		if (strcmp(env->symbols[i], s->sym) == 0) {
			return lval_copy(env->lvals[i]);
		}
	}

	return lval_err("Unbound symbol! %s", s->sym);
}

void lenv_put (lenv* env, lval* s, lval* v) {
	for (int i = 0; i < env->count; i++) {
		if (strcmp(env->symbols[i], s->sym) == 0) {
			lval_del(1, env->lvals[i]);
			env->lvals[i] = lval_copy(v);
			return;
		}
	}

	env->count++;
	env->symbols = realloc(env->symbols, sizeof(char*) * env->count);
	env->lvals = realloc(env->lvals, sizeof(lval*) * env->count);
	
	env->symbols[env->count - 1] = malloc(strlen(s->sym) + 1);
	strcpy(env->symbols[env->count - 1], s->sym);
	env->lvals[env->count - 1] = lval_copy(v);
}

void lenv_print (lenv* e) {
	for (int i = 0; i < e->count; i++) {
		printf("Name: %s, Value: ", e->symbols[i]);
		lval_println(e->lvals[i]);
	}
}

lval* builtin_op (lenv* e, lval* rands, char* rator) {
	LASSERT(rands, (rands->count >= 1), 0, NULL, rator, "needs at least 1 argument");
	
    /* Check if all numbers */
    for (unsigned int i = 0; i < rands->count; i++) {
		TASSERT(rands, i, LVAL_NUM, 0, NULL, rator);
    }

    lval* x = lval_pop (rands, 0);

    /* Perform unary negation if necessary */
    if ((strcmp (rator, "-") == 0)
		&& (rands->count == 0)) {
		x->num = - x->num;
    }

    while (rands->count > 0) {
		lval* y = lval_pop (rands, 0);

		if (strcmp (rator, "+") == 0) { x->num += y->num; }
		else if (strcmp (rator, "-") == 0) { x->num -= y->num; }
		else if (strcmp (rator, "*") == 0) { x->num *= y->num; }
		else if (strcmp (rator, "/") == 0) {
			if (y->num == 0) {
				lval_del (3, x, rands, y);
				return lval_err ("Division by zero!");
			} else {
				x->num /= y->num;
			}
		}

		lval_del (1, y);
    }

    lval_del (1, rands);
    return x;
}

lval* builtin_add (lenv* e, lval* a) {
	return builtin_op(e, a, "+");
}

lval* builtin_sub (lenv* e, lval* s) {
	return builtin_op(e, s, "-");
}

lval* builtin_mul (lenv* e, lval* m) {
	return builtin_op(e, m, "*");
}

lval* builtin_div (lenv* e, lval* d) {
	return builtin_op(e, d, "/");
}	

lval* builtin_head (lenv* e, lval* v) {
	CASSERT(v, 1, 0, NULL, "builtin_head");
	TASSERT(v, 0, LVAL_QEXPR, 0, NULL, "builtin_head");
	EASSERT(v, 0, NULL, "builtin_head");
  
	return lval_take (lval_take (v, 0), 0);
}

lval* builtin_tail (lenv* e, lval* v) {
	CASSERT(v, 1, 0, NULL, "builtin_tail");
	TASSERT(v, 0, LVAL_QEXPR, 0, NULL, "builtin_tail");
	EASSERT(v, 0, NULL, "builtin_tail");

    lval* a = lval_take (v, 0);
    lval_del (1, lval_pop (a, 0));

    return a;
}

lval* builtin_list (lenv* e, lval* v) {
	v->type = LVAL_QEXPR;
	return v;
}

lval* lval_eval (lenv* e, lval* v);

lval* builtin_eval (lenv* e, lval* v) {
	CASSERT(v, 1, 0, NULL, "builtin_eval");
	TASSERT(v, 0, LVAL_QEXPR, 0, NULL, "builtin_eval");
	lval* a = lval_take(v, 0);
	a->type = LVAL_SEXPR;
	return lval_eval(e, a);
}

lval* builtin_print_env (lenv* e, lval* v) {
	lenv_print(e);
	return lval_sexpr();
}

/* Transform AST to lval   */
lval* lval_add (lval* v, lval* w) {
    v->count++;
    v->cell = realloc(v->cell, sizeof(lval*) * v->count);
    v->cell[v->count-1] = w;
    return v;
}

lval* lval_prepend(lval* v, lval* w) {
	v->count++;
	v->cell = realloc(v->cell, sizeof(lval*) * v->count);
	memmove(v->cell + 1, v->cell, sizeof(lval*) * (v->count - 1));
	v->cell[0] = w;
	return v;
}

lval* lval_join (lval* x, lval* y) {
	while (y->count) {
		x = lval_add(x, lval_pop(y, 0));
	}

	return x;
}

lval* builtin_join (lenv* e, lval* x) {
	for (int i = 0; i < x->count; i++) {
		TASSERT(x, i, LVAL_QEXPR, 0, NULL, "builtin_join");
	}

	lval* a = lval_pop(x, 0);

	while (x->count) {
		a = lval_join(a, lval_pop(x, 0));
	}
	
	lval_del(1, x);
	return a;
}

lval* builtin_cons (lenv* e, lval* v) {
	CASSERT(v, 2, 0, NULL, "builtin_cons");
	TASSERT(v, 1, LVAL_QEXPR, 0, NULL, "builtin_cons");

	lval* val = lval_pop(v, 0);
	lval* qexpr = lval_pop(v, 0);
	lval_del(1, v);

	return lval_prepend(qexpr, val);
}

lval* builtin_len (lenv* e, lval* v) {
	CASSERT(v, 1, 0, NULL, "builtin_len");
	TASSERT(v, 0, LVAL_QEXPR, 0, NULL, "builtin_len");

	return lval_num(v->cell[0]->count);
}

lval* builtin_init (lenv* e, lval* v) {
	CASSERT(v, 1, 0, NULL, "builtin_init");
	TASSERT(v, 0, LVAL_QEXPR, 0, NULL, "builtin_init");

	lval* a = lval_take(v, 0);
	lval_del(1, lval_pop(a, a->count - 1));
	return a;
}

lval* builtin_def (lenv* e, lval* a) {
	TASSERT(a, 0, LVAL_QEXPR, 0, NULL, "builtin_def");
	
	lval* symbols = lval_pop(a, 0);

	for (int i = 0; i < symbols->count; i++) {
		TASSERT(symbols, i, LVAL_SYM, 1, a, "builtin_def");
	}

	CASSERT(symbols, a->count, 1, a, "builtin_def");

	for (int i = 0; i < symbols->count; i++) {
		lenv_put(e, symbols->cell[i], a->cell[i]);
	}

	lval_del(2, symbols, a);
	return lval_sexpr();
}

lval* builtin_exit (lenv* e, lval* a) {
	exit(0);
	return lval_sexpr();
}

lval* lval_eval_sexpr (lenv* e, lval* v) {

    /* First evaluate the children */
    for (unsigned int i = 0; i < v->count; i++) {
		v->cell[i] = lval_eval (e, v->cell[i]);
    }

    /* Return the first error we find */
    for (unsigned int i = 0; i < v->count; i++) {
		if (v->cell[i]->type == LVAL_ERR) { return lval_take (v, i); }
    }

    /* Empty expressions are just returned  */
    if (v->count == 0) { return v; }

    /* Ensure the first element maps to a function in the environment */
	lval* f = lval_pop(v, 0);
	if ((f->type != LVAL_FUN) || (f->type != LVAL_BUILTIN)) {
		lval_del(2, f, v);
		return lval_err("S-expression does not start with function");
	}

	/* Call function */
	lval* result;
	if (f->type == LVAL_FUN) {
		result =  
	} else {
		result = f->builtin(e, v);
	}
	lval_del(1, f);
	return result;	
}

/* Eval lval */
lval* lval_eval (lenv* e, lval* v) {
	if (v->type == LVAL_SYM) {
		lval* x = lenv_get(e, v);
		lval_del(1, v);
		return x;
	}
	
    if (v->type == LVAL_SEXPR) { return lval_eval_sexpr (e, v); }

    /* All other lvals stay the same */
    return v;
}

lval* lval_read (mpc_ast_t* t) {

    /* If number or symbol convert node to that type*/
    if (strstr (t->tag, "number")) { return lval_read_num (t); }
    if (strstr (t->tag, "symbol")) { return lval_sym(t->contents); }

    lval* x = NULL;

    /* todo allow for several expressions at top level. We prob need a (begin ...) construct for that  */
    if (strcmp (t->tag, ">") == 0) { return lval_read (t->children[1]); }
    /* if it's a sexpr create an empty list of sub lvals*/
    if (strstr (t->tag, "sexpr")) { x = lval_sexpr (); }
    else if (strstr (t->tag, "qexpr")) { x = lval_qexpr (); }
  
    /* Fill the list with any subexpression*/
    for (int i = 0; i < t->children_num; i++) {
		if (strcmp (t->children[i]->contents, "(") == 0) { continue; }
		else if (strcmp (t->children[i]->contents, ")") == 0) { continue; }
		else if (strcmp (t->children[i]->contents, "{") == 0) { continue; }
		else if (strcmp (t->children[i]->contents, "}") == 0) { continue; }
		else if (strcmp (t->children[i]->tag, "regex") == 0) { continue; }
		x = lval_add(x, lval_read(t->children[i]));
    }

    return x;
}

void lenv_add_builtin (lenv* e, char* name, lbuiltin func) {
	lval* n = lval_sym(name);
	lval* f = lval_builtin(func);
	lenv_put(e, n, f);
	lval_del(2, n, f);
}

void lenv_add_builtins (lenv* e) {
	lenv_add_builtin(e, "+", builtin_add);
	lenv_add_builtin(e, "-", builtin_sub);
	lenv_add_builtin(e, "*", builtin_mul);
	lenv_add_builtin(e, "/", builtin_div);
	
	lenv_add_builtin(e, "head", builtin_head);
	lenv_add_builtin(e, "tail", builtin_tail);
	lenv_add_builtin(e, "join", builtin_join);
	lenv_add_builtin(e, "cons", builtin_cons);
	lenv_add_builtin(e, "len", builtin_len);
	lenv_add_builtin(e, "init", builtin_init);
	lenv_add_builtin(e, "eval", builtin_eval);
	lenv_add_builtin(e, "list", builtin_list);
	lenv_add_builtin(e, "def", builtin_def);
	lenv_add_builtin(e, "print-env", builtin_print_env);
	lenv_add_builtin(e, "exit", builtin_exit);
}

int main (int argc, char** argv) {
    /* maybe get rid of expr and represent everything as sexpr*/
    mpc_parser_t* Number = mpc_new("number");
    mpc_parser_t* Symbol = mpc_new("symbol");
    mpc_parser_t* Sexpr = mpc_new("sexpr");
    mpc_parser_t* Qexpr = mpc_new("qexpr");
    mpc_parser_t* Expr = mpc_new("expr");
    mpc_parser_t* Lispy = mpc_new("lispy");

    /* Define them with the following Language*/
    mpca_lang(MPCA_LANG_DEFAULT,
			  "                                                  \
              number: /-?[0-9]+/ ;								 \
              symbol: /[a-zA-Z0-9_+\\-*\\/\\\\=<>!&]+/ ;		 \
              sexpr: '(' <expr>* ')' ;                           \
              qexpr: '{' <expr>* '}' ;                           \
              expr: <number> | <symbol> | <sexpr> | <qexpr> ;    \
              lispy: /^/ <expr> /$/ ;                            \
            ",
			  Number, Symbol, Sexpr, Qexpr, Expr, Lispy);

	lenv* e = lenv_new();
	lenv_add_builtins(e);
  
    puts ("Lispy version 0.4");
    puts ("Exit with Ctrl-c or Ctrl-d");

    while (1) {
    	char* input = readline ("lispy> ");
    	if (input == NULL) {
    	    mpc_cleanup(5, Number, Symbol, Sexpr, Qexpr, Expr, Lispy);
			printf("\n");
			return 1;
    	}
    
    	add_history (input);

    	mpc_result_t r;

    	/* Attempt to parser user input*/
    	if (mpc_parse("<stdin>", input, Lispy, &r)) {
    	    lval* result = lval_eval (e, lval_read (r.output));
    	    lval_println (result);
    	    lval_del (1, result);
    	    mpc_ast_delete(r.output);
    	} else {
    	    mpc_err_print(r.error);
    	    mpc_err_delete(r.error);
    	}

    	free (input);
    }

    mpc_cleanup(5, Number, Symbol, Sexpr, Qexpr, Expr, Lispy);
    return 0;
}

   
