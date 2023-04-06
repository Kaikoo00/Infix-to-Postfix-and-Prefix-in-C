#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct math_op{
    int num;
    char operation;
    char op_value;
}math;

math arrOfItems[20];
int size = 0;

int precedence(char operator) {
    if (operator == '+' || operator == '-') {
        return 1;
    } else if (operator == '*' || operator == '/') {
        return 2;
    } else if (operator == '^') {
        return 3;
    } else {
        return 0;
    }
}

math generate_random_math_operation(){
    int inp =  rand()%5;
    math return_value;
    if(inp==0) return_value = (math){.operation='+', .op_value=1};
    else if(inp==1) return_value = (math){.operation='-', .op_value=1};
    else if(inp==2) return_value = (math){.operation='*', .op_value=2};
    else if(inp==3) return_value = (math){.operation='/', .op_value=2};
    else if(inp==4) return_value = (math){.operation='^', .op_value=3};
    return return_value;
}

int generate_random_num(){
    return abs(rand()%100);
}

char* turn_struct_to_string(char *str){
    sprintf(str, "%d%c",arrOfItems[0].num, arrOfItems[0].operation);
    int i=1;
    for(i=1; i<size-1; i++){
        sprintf(str, "%s%d%c", str, arrOfItems[i].num, arrOfItems[i].operation);
    }
    sprintf(str, "%s%d", str, arrOfItems[i].num);
    str[strlen(str)]='\0';
    return str;
}

char* convert_to_postfix(char *str, char *postfix_string){
    sprintf(postfix_string, "%c", str[0]);
    int i=1;
    int top = 0;
    char stack[30]; stack[top]='(';

    while(str[i]!='\0'){
        if(isdigit(str[i])){
            sprintf(postfix_string, "%s%c", postfix_string, str[i]);
        }else if(str[i]==' '){
            sprintf(postfix_string, "%s%c", postfix_string, ' ');
        }else{
            while(true){
                sprintf(postfix_string, "%s%c", postfix_string, ' ');
                if(precedence(stack[top])>=precedence(str[i])){
                    sprintf(postfix_string, "%s%c", postfix_string, stack[top]);
                    top--;
                }else{
                    top++;
                    stack[top]=str[i];
                    break;
                }
            }
        }
        i++;
    }
    while(stack[top]!='\0' && top != 0){
        sprintf(postfix_string, "%s%c", postfix_string, ' ');
        sprintf(postfix_string, "%s%c", postfix_string, stack[top]);
        top--;
    }
    return postfix_string;
}

char* convert_to_prefix(char *str, char *prefix){
    strrev(str);
    sprintf(prefix, "%c", str[0]);
    int i=1;
    int top = 0;
    char stack[30]; stack[top]='(';

    while(str[i]!='\0'){
        if(isdigit(str[i])){
            sprintf(prefix, "%s%c", prefix, str[i]);
        }else if(str[i]==' '){
            sprintf(prefix, "%s%c", prefix, ' ');
        }else{
            while(true){
                sprintf(prefix, "%s%c", prefix, ' ');
                if(precedence(stack[top])>precedence(str[i])){
                    sprintf(prefix, "%s%c", prefix, stack[top]);
                    top--;
                }else{
                    top++;
                    stack[top]=str[i];
                    break;
                }
            }
        }
        i++;
    }
    while(stack[top]!='\0' && top != 0){
        sprintf(prefix, "%s%c", prefix, ' ');
        sprintf(prefix, "%s%c", prefix, stack[top]);
        top--;
    }
    strrev(prefix);
    return prefix;
}

int main(){
    while(true){
        char str[50], answer[50];
        printf("How many numbers: ");
        int amount; scanf("%d", &amount); getchar();
        printf("\nSoal: ");
        for(int i=0; i<amount; i++){
            size++;
            arrOfItems[i] = generate_random_math_operation();
            arrOfItems[i].num = generate_random_num();
            if(i==amount-1){
                arrOfItems[i]=(math){.op_value=0,.operation='\0'};
                arrOfItems[i].num = generate_random_num();
                printf("%d\n", arrOfItems[i].num);
                break;
            }
            printf("%d %c ",arrOfItems[i].num,arrOfItems[i].operation);
        }
        printf("\n");
        turn_struct_to_string(str);
        int ch; 
        jump:
            printf("1. Postfix\n");
            printf("2. Prefix\n>>");
            scanf("%d", &ch);getchar();
            if(ch==1){
                convert_to_postfix(str, answer);
            }else if(ch==2){
                convert_to_prefix(str,answer);
            }else{
                system("cls");
                goto jump;
            }

        printf("\nJawaban anda: ");
        char inp[30]; scanf("%[^\n]", inp); getchar();
        if(!strcmp(inp, answer)){
            printf("\n|| Benar XDD ||\n");
        }else{
            printf("\n|| Salah T_T ||\n");
            printf("\nJawaban yang benar : %s\n", answer);
        }
        system("pause");system("cls");
        size=0;
    }
}
