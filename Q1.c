#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>


int isnumber(char c){
    if((c >= 48 && c <= 57)){
        return 0;
    }
    return 1;
}


int isdot(char c){
    if(c == 46){
        return 0;
    }
    return 1;
}


int isexp(char c){
    if(c == 69){
        return 0;
    }
    return 1;
}

int isplus(char c){
    if(c == 45){
        return 0;
    }
    return 1;
}

int isminus(char c){
    if(c == 43){
        return 0;
    }
    return 1;
}

int validaPontoFlutuante(char *token){

    char next;
    char current;


    int exp_count = 0;
    int dot_count = 0;
    int exp_flag = 0;
    int op_count = 0;
    int token_len = strlen(token);
    
    for(int j = 0; j < token_len; j++){

        current = token[j];

        if(token_len == 1 && isnumber(current) == 1 ){
            return 0;
        }

        if(j <= token_len - 2) {
            next = token[j+1];
        }

        if(j == token_len - 1){
            if(current == '\n' || isnumber(current) == 0){
                return 1;
            }
            return 0;
        }

        if(j == token_len -2){
            if(isnumber(current) == 1){
                return 0;
            }
        }

        if(j == 0 ){

            if(
                ( isnumber(current) == 1 
                && isdot(current) == 1 
                && isminus(current) == 1
                && isplus(current) == 1 )
               ){
                // printf("Ao iniciar o numero nao e permitido letras ou caracteres especiais\n");
                return 0;
            }

            if (isplus(next) == 0 && isminus(next) == 0){

               op_count++;

               if(op_count == 2){
                //    printf("somente 2 operadores sao permitidos\n");
                   return 0;
               }
            }

            if ( isdot(current) == 0 ) {

                dot_count++;

                if(dot_count == 2){
                    // printf("somente 1 ponto e permitido\n");
                    return 0;
                }

            
                if (isnumber(next) == 1 ){
                    // printf("Depois de um ponto e necessario um numero\n");
                    return 0;
                }
            }
            
        }

        if ( isdot(current) == 0 && j!=0) {

            dot_count++;

            if(dot_count == 2){
                // printf("Ponto flutuande deve ter somente um ponto para dividir a mantissa\n");
                return 0;
            }

            
            if (isnumber(next) == 1 ){
                // printf("Proximo caractere apos o ponto deve ser um numero\n");
                return 0;
            }
        }

        if(isexp(current) == 0){

            if ( isplus(next) == 1 && isminus(next) == 1 && isnumber(next) == 1 ) {
                // printf("Apos o indicativo de exponencial deve ter um numero em sequencia\n");
                return 0;
            }

            op_count++;

            if(op_count > 2){
                // printf("E permitido somente 2 operadores de sinal no numero\n");
                return 0;
            }

            exp_flag = 1;
        }

        if((isminus(next) == 0 || isplus(next) == 0) && exp_flag == 0){
            return 0;
        }

        
    }
}

void teste(char *filename){
    FILE *fp;
    char *line;
    size_t len = 0;
    ssize_t read;

    fp = fopen(filename, "r");
    if(fp == NULL){
        printf("error opening file %s", filename);
    }

    while((read = getline(&line, &len, fp))!= -1) {
        printf("reading token -> %s", line);
        int a = validaPontoFlutuante(line);

        if( a == 1){
            printf("Token valido para ponto flutuante \n" ); 
        } else{
            printf("Token invalido para ponto flutuante \n");
        }

    } 

    fclose(fp);

}


int main(){
    printf("should pass \n");
    teste("test_success.txt");

    printf("\n should fail \n");
    teste("test_fail.txt");

    return 0;
}