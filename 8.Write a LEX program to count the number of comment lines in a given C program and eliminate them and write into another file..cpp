%{
    int comment_lines = 0;
    FILE *outfile;
%}

%%

"/*"   { comment_lines++; BEGIN(COMMENT); }
<COMMENT>"*/"  { comment_lines++; BEGIN(INITIAL); }
<COMMENT>.|\n   comment_lines++;
.|\n   {
        fprintf(outfile, "%s", yytext);
    }

%%

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s input_file\n", argv[0]);
        exit(1);
    }

    yyin = fopen(argv[1], "r");
    if (!yyin) {
        perror(argv[1]);
        exit(1);
    }

    outfile = fopen("output.c", "w");
    if (!outfile) {
        perror("output.c");
        exit(1);
    }

    yylex();

    printf("Number of comment lines: %d\n", comment_lines);

    fclose(yyin);
    fclose(outfile);

    return 0;
}
