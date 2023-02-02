%{
#include <stdio.h>
%}

%x IN_WORD

%%

"0"[xX][0-9a-fA-F]+      { printf("Hexadecimal constant: %s\n", yytext); }

[1-9][0-9]*              { printf("Decimal constant: %s\n", yytext); }

0[0-7]+                  { printf("Octal constant: %s\n", yytext); }

[0-9]+\.[0-9]+           { printf("Floating-point constant: %s\n", yytext); }

0[eE][-+]?[0-9]+         { printf("Exponent constant: %s\n", yytext); }

.

%%

int main(int argc, char *argv[]) {
    ++argv, --argc;  /* skip over program name */
    if (argc > 0) {
        yyin = fopen(argv[0], "r");
    } else {
        yyin = stdin;
    }
    yylex();
    return 0;
}