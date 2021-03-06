#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <editline/readline.h>
#include "mpc.h"

/* Declare new Lisp Value struct */
typedef struct {
  int type;
  long num;
  double dec;
  int err;
} lval;

/* Declare enum for possible lval types */
enum { LVAL_NUM, LVAL_DEC, LVAL_ERR };
/* Decalre enum for possible error typer */
enum { LERR_DIV_ZERO, LERR_BAD_OP, LERR_BAD_NUM, LERR_BAD_DEC, LERR_NEG_POWER, LERR_BAD_TYPE };

/* Creates a new number lval */
lval lval_num (long x) {
  lval v;
  v.type = LVAL_NUM;
  v.num = x;
  return v;
}

/* Creates a new decimal lval */
lval lval_dec (double x) {
  lval v;
  v.type = LVAL_DEC;
  v.dec = x;
  return v;
}

/* Creates a new error lval */
lval lval_err (int x) {
  lval v;
  v.type = LVAL_ERR;
  v.err = x;
  return v;
}

/* Print an "lval" */
void lval_print(lval v) {
  switch (v.type) {
    /* In the case the type is a number print it */
    /* Then 'break' out of the switch. */
  case LVAL_NUM: printf("%li", v.num); break;
  case LVAL_DEC: printf("%f", v.dec); break;
    /* In the case the type is an error */
  case LVAL_ERR:
    /* Check what type of error it is and print it */
    if (v.err == LERR_DIV_ZERO) {
      printf("Error: Division By Zero!");
    }
    if (v.err == LERR_BAD_OP)
      {
	printf("Error: Invalid Operator!");
      }
    if (v.err == LERR_BAD_NUM) {
      printf("Error: Invalid Number!");
    }
    break;
  }
}

/* Print an "lval" followed by a newline */
void lval_println(lval v) { lval_print(v); putchar('\n'); }

long max (long a, long b) {
  if (a > b) { return a; }
  else { return b; }
}

long min (long a, long b) {
  if (a < b) { return a; }
  else { return b; }
}

long power (long a, long b) {
  if (b <= 0) { return 1; }
  else { return a * power (a, b - 1); }
}

double maxDec (double a, double b) {
  if (a > b) { return a; }
  else { return b; }
}

double minDec (double a, double b) {
  if (a < b) { return a; }
  else { return b; }
}

double powerDec (double a, double b) {
  if (b <= 0) { return 1.0; }
  else { return a * powerDec (a, b - 1.0); }
}

lval eval_op (lval x, char * op, lval y) {
  /* If either value is an error return it */
  if (x.type == LVAL_ERR) { return x; }
  if (y.type == LVAL_ERR) { return y; }
  
  /* Otherwise do maths on the number values */
  if (x.type == y.type) {
    if (x.type == LVAL_NUM) {
      if (strcmp(op, "+") == 0) { return lval_num (x.num + y.num); }
      else if (strcmp(op, "-") == 0) { return lval_num (x.num - y.num); }
      else if (strcmp(op, "*") == 0) { return lval_num (x.num * y.num); }
      else if (strcmp(op, "max") == 0) { return lval_num (max (x.num, y.num)); }
      else if (strcmp(op, "min") == 0) { return lval_num (min (x.num, y.num)); }
      else if (strcmp(op, "^") == 0) {
	/* If second operand is less than zero return an error, implement later */
	return y.num < 0
	  ? lval_err (LERR_NEG_POWER)
	  : lval_num (power (x.num, y.num));
      }
      else if (strcmp(op, "%") == 0) {
	/* If second operand is zero return error */
	return y.num == 0
	  ? lval_err(LERR_DIV_ZERO)
	  : lval_num(x.num % y.num);
      }
      else if (strcmp(op, "/") == 0) {
	/* If second operand is zero return error */
	return y.num == 0
	  ? lval_err(LERR_DIV_ZERO)
	  : lval_num(x.num / y.num);
      }
      else {
	return lval_err(LERR_BAD_OP);
      }
    }
    else {
      if (strcmp(op, "+") == 0) { return lval_dec (x.dec + y.dec); }
      else if (strcmp(op, "-") == 0) { return lval_dec (x.dec - y.dec); }
      else if (strcmp(op, "*") == 0) { return lval_dec (x.dec * y.dec); }
      else if (strcmp(op, "max") == 0) { return lval_dec (maxDec (x.dec, y.dec)); }
      else if (strcmp(op, "min") == 0) { return lval_dec (minDec (x.dec, y.dec)); }
      /* else if (strcmp(op, "^") == 0) { */
      /* 	/\* If second operand is less than zero return an error, implement later *\/ */
      /* 	return y.dec < 0 */
      /* 	  ? lval_err (LERR_NEG_POWER) */
      /* 	  : lval_dec (powerDec (x.dec, y.dec)); */
      /* } */
      /* else if (strcmp(op, "%") == 0) { */
      /* 	/\* If second operand is zero return error *\/ */
      /* 	return y.dec == 0 */
      /* 	  ? lval_err(LERR_DIV_ZERO) */
      /* 	  : lval_dec(x.dec % y.dec); */
      /* } */
      else if (strcmp(op, "/") == 0) {
	/* If second operand is zero return error */
	return y.dec == 0
	  ? lval_err(LERR_DIV_ZERO)
	  : lval_dec(x.dec / y.dec);
      }
      else {
	return lval_err(LERR_BAD_OP);
      }
    }
  }
  else {
    return lval_err(LERR_BAD_TYPE);
  }
}
 
lval eval (mpc_ast_t * t) {

  if (strstr(t->tag, "number")) {
    /* Check if there is some error in conversion */
    /* first check if it's a decimal */
    if (strstr(t->contents, ".")) {
      errno = 0;
      double x = strtod(t->contents, NULL);
      return errno != ERANGE ? lval_dec(x) : lval_err(LERR_BAD_DEC);
    }
    else {
      errno = 0;
      long x = strtol(t->contents, NULL, 10);
      return errno != ERANGE ? lval_num(x) : lval_err(LERR_BAD_NUM);
    }
  }
  
  /* The operator is the second child */
  char * op = t->children[1]->contents;

  /* Store the first expression in x */
  lval x = eval (t->children[2]);

  /* support unary minus */
  if ((strcmp (op, "-") == 0)
      && (t->children_num == 4)
      && (x.type == LVAL_NUM)) {
    return lval_num (- x.num);
  }

  /* Iterate over the rest of the expressions, accumulating the result */
  int i = 3;
  while (strstr (t->children[i]->tag, "expr")) {
    x = eval_op (x, op, eval (t->children[i++]));
  }

  return x;
}

int main (int argc, char **argv) {
  mpc_parser_t * Number = mpc_new("number");
  mpc_parser_t * Operator = mpc_new("operator");
  mpc_parser_t * Expr = mpc_new("expr");
  mpc_parser_t * Lispy = mpc_new("lispy");

  /* Define them with the following Language */
  mpca_lang(MPCA_LANG_DEFAULT,
	    "                                                    \
              number: /-?[0-9]+([.][0-9]+)?/ ;                   \
              operator : '+' | '-' | '*' | '/' | '%' | '^'       \
                         | \"max\" | \"min\"                     \
                         | \"add\" | \"sub\" | \"mul\"           \
                         | \"div\" | \"mod\" ;			 \
              expr: <number> | '(' <operator> <expr>+ ')' ;      \
              lispy: /^/ <operator> <expr>+ /$/ ;                \
            ",
	    Number, Operator, Expr, Lispy); 
  
  puts ("Lispy version 0.4");
  puts ("Exit with Ctrl-c");

  while (1) {
    char *input = readline ("lispy> ");
    
    add_history (input);

    mpc_result_t r;

    /* Attempt to parser user input */
    if (mpc_parse("<stdin>", input, Lispy, &r)) {
      /* On sucess print AST */
      mpc_ast_print(r.output);
      lval result = eval (r.output);
      lval_println (result);
      mpc_ast_delete(r.output);
    } else {
      mpc_err_print(r.error);
      mpc_err_delete(r.error);
    }

    free (input);
  }

  /* Undefine and Delete our Parsers */
  mpc_cleanup(4, Number, Operator, Expr, Lispy);

  return 0;
}
   
