#include <stdio.h>

#define MAX_LINE_LENGTH 1024

int main(int argc, char** argv){
    char line[MAX_LINE_LENGTH];

    while( fgets(line, MAX_LINE_LENGTH, stdin) != NULL ){
        fputs(line, stdout);
    }
}
