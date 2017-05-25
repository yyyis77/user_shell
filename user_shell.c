//
// Created by 杨咏仪 on 5/17/17.
//
#include "user_shell.h"


void redirect(int start1, int end1, int start2, int end2) {
    int i,j;
    int len1=end1-start1+1, len2=end2-start2+1;
    char *command1=malloc(sizeof(char)*len1);
    char *command2=malloc(sizeof(char)*len2);

    j=0;
    for(i=start1; i<end1; i++){
        command1[j++]=input[i];
    }
    command1[j]='\0';

    j=0;
    for(i=start2; i<end2; i++){
        command2[j++]=input[i];
    }
    command2[j]='\0';

    char **command1_split = split(command1, len1);
    char **command2_split = split(command2, len2);

    int fd[2];
    pipe(fd);

    pid_t pid1=fork();
    // parent
    if(pid1 > 0){
        pid_t pid2=fork();
        if(pid2 > 0){
            close(fd[0]); close(fd[1]);

            int status1, status2;
            waitpid(pid1,&status1,0);
            waitpid(pid2,&status2,0);

        }
        else  if(pid2==0){
            close(fd[1]); // close write
            dup2(fd[0],0);
            close(fd[0]);
            execvp(command2_split[0], command2_split);
            perror("child2 fail\n");
        }
        else{
            perror("fork second process fail\n");
            return;
        }
    }
    else if(pid1 == 0){
        close(fd[0]); // close read
        dup2(fd[1],1);
        close(fd[1]);
        execvp(command1_split[0], command1_split);
    }
    else{
        perror("fork first proccess fail\n");
        return;
    }
}

void output_to_file(int start, int end) {

}

void and(int start, int end) {

}

void execute(int start, int end) {
    int i,j;
    int len = end - start ;
    char *command=malloc(sizeof(char)*len);
    j=0;
    for(i=start; i<end; i++){
        command[j]=input[i];
        j++;
    }
    command[j]='\0';
    char **split_com = split(command, len);

    pid_t pid = fork();
    // parent process
    if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
    }
    // children process
    else if(pid==0){
        execvp(split_com[0], split_com);
    }
    else{
        perror("fork fail\n");
        return;
    }
}

char **split(char *str, int strlen) {
    char **res;
    int i, j, k=0;
    int total_count = 0;

    for (i = 0; i < strlen; i++) {
        if (str[i] == ' ')
            total_count++;
    }
    total_count++;

    res = malloc(sizeof(char *) * (total_count+1));

    for (i = 0; i < total_count; i++) {
        res[i] = malloc(sizeof(char) * 256);
    }

    j = 0;
    for (i = 0; i < strlen; i++) {
        if (str[i] == ' ') {
            res[j][k] = '\0';
            j++;
            k = 0;
        } else {
            res[j][k] = str[i];
            k++;
        }
    }
    res[j][k] = '\0';
    j++;
    res[j]=NULL;

    return res;
}

char *cut_tail(char *str, int strlen){
    int i=strlen-2;
    while(str[i]==' '){
        i--;
    }
    str[i+1]='\0';
    return str;
}