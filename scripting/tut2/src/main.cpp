#include <cstdio>
#include <iostream>
#include "lex.h"
#include "lexsymb.h"

// Names of our tokens for displaying them
char *name[] = {
   "IF", "ELSE", "PRINT", "INPUT", "ASSIGN", "EQUAL",
   "CONCAT", "END_STMT", "OPEN_PAR", "CLOSE_PAR", "BEGIN_CS", "END_CS",
   "ID", "STRING",
};

YYSTYPE yylval; // union in which strings are passed

// This function is called by the lexer when the end-of-file
// is reached; you can reset yyin (the input FILE*) and return 0
// if you want to process another file; otherwise just return 1.
extern "C" int yywrap(void) {
  return 1;
}

// The main program: just report all tokens found
int main (int argc, char *argv[])  {
   int token;

   // Set the input stream (either a file from the command line or stdin)
   yyin = NULL;
   if (argc == 2)   {
      yyin = fopen (argv[1], "rt");
   }
   if (yyin == NULL)
      yyin = stdin;

   // Get all tokens and show them on screen
   while ((token = yylex ()) != 0)   {
      std::cout << "Token: ";
      switch (token)   {
      case ID:
	      std::cout << name[token-IF] << " = " << yylval.str << std::endl;
		   delete [] yylval.str;
		   break;
      case STRING:
	      std::cout << name[token-IF] << " = \"" << yylval.str << "\"" << std::endl;
		   delete [] yylval.str;
		   break;
      case ERROR_TOKEN:
	      std::cout << "ILLEGAL TOKEN" << std::endl;
		   break;
      default:
	      std::cout << name[token-IF] << std::endl;
         break;
	   }
   }
   return 0;
}

