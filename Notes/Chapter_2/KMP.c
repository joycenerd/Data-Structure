#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 200
typedef unsigned long int ui;


int main()
{
    char string[200];
    strncpy(string, "ababbababaa", N);
    ui len = strlen(string);
    int i, j;
    int failure[N];
    failure[0] = 0;
    char head = string[0];
    for (i = 1; i < len; i++) {
        if (failure[i - 1] == 0) {
            if (string[i] == head) failure[i] = 1;
            else failure[i] = 0;
        }
        else {
            j = i - 1;
            int index = 0;
            int find = 0;
            while (j >= 1) {
                if (failure[j] == 1 /*&& j + failure[i - 1] == i*/) {
                    index = j;
                    find = 1;
                    break;
                }
                j--;
            }
           /* if (find == 0) {
                j = i - 1;
                while (j > 0) {
                    if (string[j] == head && failure[j]==1) {
                        index = j;
                        break;
                    }
                    j--;
                }
            }*/
            int count;
            count = i - index + 1;
            if (strncmp(string + 0, string + index, count) == 0) failure[i] = count;
            else {
                int flag = 0;
                for (j = index + 1; j < i; j++) {
                    if (string[j] == head) {
                        count = i - j + 1;
                        if (strncmp(string, string + j, count) == 0) {
                            failure[i] = count;
                            flag = 1;
                            break;
                        }
                    }
                }
                if (flag == 0) {
                    if (string[i] == head) failure[i] = 1;
                    else failure[i] = 0;
                }
            }
        }
    }
    for (i = 0; i < len; i++) printf("%c %d\n", string[i], failure[i]);
    return 0;
}
