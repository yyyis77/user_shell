#include "user_shell.h"


int main() {
    size_t buffer_size=4096;
    input = malloc(sizeof(char)*buffer_size);
    while (1){
        getline(&input,&buffer_size,stdin);
        // test whether exit program
        char if_exit[5];
        memcpy(if_exit,input,5);
        if(strcmp(if_exit,"exit")==0){
            return 0;
        }

        int i=0,j=0,k=0,l=0;

        while(input[j]!='\0'){
            if(input[j+1]=='\n'){
                input[j+1]='\0';
            }
            if(input[j+1]=='\0'){
                execute(i,j+1);
            }
            switch (input[j]){
                case '|':
                    l=j+1;
                    if(input[l]=='|'){
                        k=j+1;

                    }
                    else{
                        k=j+1;
                        while(input[k] == ' '){
                            k++;
                        }
                        l=k+1;
                        while(input[l]!='|' && input[l]!='>' && input[l]!='&' && input[l]!='\0'){
                            l++;
                        }
                        input[j]='\0';
                        redirect(i,j,k,l-1);
                    }
                    i=j+1;
                    break;
                case '>':
                    output_to_file(i,j);
                    i=j+1;
                    break;
                case '&':
                    and(i,j);
                    i=j+1;
                    break;
                default:
                    break;
            }
            j++;
        }
    }
}
