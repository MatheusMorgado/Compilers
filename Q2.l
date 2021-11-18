%{
 
#include <stdio.h>
%}
%%

">"     {   printf("GT\n");      }
"<"     {   printf("LT\n");      }
">="    {   printf("GTE\n");     }
"<="    {   printf("LTE\n");     }
"=="    {   printf("EQ\n");      }
"!="    {   printf("DIF\n");     }
"*"     {   printf("MUL\n");     }
"+"     {   printf("PLUS\n");    }
":="    {   printf("AT\n");      }
"while" {   printf("WHILE\n");   }
"if"    {   printf("IF\n");      }
"int"   {   printf("INTEGER\n"); }
"real"  {   printf("FLOAT\n");   }
[ \t \n]+  /* do nothing, blank space */;

[0-9]+   {   printf("NUM\n");     }
^[a-zA-Z]+[a-zA-Z0-9]*[_]?[a-zA-Z0-9]+ { printf("ID\n"); }
.       { printf("Invalid Token\n");}
%%