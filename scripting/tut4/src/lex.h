// lex.h: lexer defines & declarations

#ifndef _LEX_H_
#define _LEX_H_

#include <cstdio>

#ifdef _LEX_CPP_
   int lineno = 1; // line number count; this will be used for error messages later
#else
   // Import some variables
   extern int lineno;
   extern FILE *yyin;  // the input stream

   // Function prototype
   int yylex ();
#endif

#endif
