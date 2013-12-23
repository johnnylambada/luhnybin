#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MIN_LUHN_DIGITS 14
#define MAX_LUHN_DIGITS 16
#define MASK 'X'

int odd[] =  { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
int even[] = { 0, 2, 4, 6, 8, 1, 3, 5, 7, 9 };

void mask(char *dst, int count){
    //printf("mask(%s,%d)\n",dst,count);
    while(count--){
        if (*dst>='0' && *dst<='9'){
            *dst=MASK;
        }
        --dst;
    }
}

void luhnmask(char *line, char *src, char *dst){
    int count=1;
    int check=0;
    char *s = src;
    int add;

    //printf("luhnmask\n");
    while(count<=MAX_LUHN_DIGITS && s>=line){
        if (! (*s==' '||*s=='-') ) {
            // It's not whitespace
            if (*s>='0' && *s<='9'){
                if (count & 0x1)
                    add = odd[*s-'0'];
                else
                    add = even[*s-'0'];

                check = check + add;
                //printf("count=%d s=%c add=%d check=%d div=%d\n",count,*s,add,check,check%10);
                if (count>=MIN_LUHN_DIGITS){
                    if (check%10 == 0){
                        mask(dst,src-s+1);
                    }
                }
                count++;
            } else {
                // it's not a digit, so we can bail
                break;
            }
        }
        s--;
    }
}

int main(int argc, char** argv){
    char in[MAX_LINE_LENGTH];
    char out[MAX_LINE_LENGTH];
    char *s,*d;
    char last=-1;

    while( fgets(in, MAX_LINE_LENGTH, stdin) != NULL ){
        strncpy(out,in,MAX_LINE_LENGTH);
        for(s=in,d=out;*s!='\0';s++,d++)   // Find the end of the strings
            ;
        while(--s!=in){
            --d;
            if (*s>='0' && *s<='9')
                luhnmask(in,s,d);
        }
        fputs(out, stdout);
    }
}
