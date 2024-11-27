%{
%}
 
%%
[ \t\r]
\/          fputc(' ', yyout);
".-"        fputc('a', yyout);
"-..."      fputc('b', yyout);
"-.-."      fputc('c', yyout);
"-.."       fputc('d', yyout);
"."         fputc('e', yyout);
"..-."      fputc('f', yyout);
"--."       fputc('g', yyout);
"...."      fputc('h', yyout);
".."        fputc('i', yyout);
".---"      fputc('j', yyout);
"-.-"       fputc('k', yyout);
".-.."      fputc('l', yyout);
"--"        fputc('m', yyout);
"-."        fputc('n', yyout);
"---"       fputc('o', yyout);
".--."      fputc('p', yyout);
"--.-"      fputc('q', yyout);
".-."       fputc('r', yyout);
"..."       fputc('s', yyout);
"-"         fputc('t', yyout);
"..-"       fputc('u', yyout);
"...-"      fputc('v', yyout);
".--"       fputc('w', yyout);
"-..-"      fputc('x', yyout);
"-.--"      fputc('y', yyout);
"--.."      fputc('z', yyout);
%%

int yywrap() {}

int main() {
    char file_name[100];
    printf("Filename: ");
    scanf("%s", file_name);
    FILE *in = fopen(file_name, "r");
    if (in == NULL) {
        printf("ERROR: file can't be opened\n");
        exit(1);
    }
    FILE *out = fopen("output.txt", "w");
    if (out == NULL) {
        printf("ERROR: can not create output file\n");
        exit(1);
    }

    yyin = in;
    yyout = out;
    yylex();
}
