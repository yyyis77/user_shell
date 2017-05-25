//
// Created by 杨咏仪 on 5/17/17.
//

#ifndef USER_SHELL_USER_SHELL_H
#define USER_SHELL_USER_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

void redirect(int start1, int end1, int start2, int end2);
void output_to_file(int start, int end);
void and(int start, int end);
void execute(int start, int end);
char **split(char* str, int strlen);
char *cut_tail(char *str, int strlen);

char *input;


#endif //USER_SHELL_USER_SHELL_H
