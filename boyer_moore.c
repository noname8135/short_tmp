#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int shift_map[127]; // all visible char, shift_map[ascii] = shift distance

void build_shift_map(char* pattern){
    int i,len = strlen(pattern);
    for(i=0; i<127; i++)
        shift_map[i] = len;
    for(i=0; i< len-1; i++){
        printf("(%c %d)\n", pattern[i],i);
        shift_map[pattern[i]] = len - 1 - i;
    }
    return ;
}

void bm_search(char* target_str, int target_len, char* pattern){    //boyer moore search
    
    int i,j;
    int patlen = strlen(pattern);
    
    if (patlen == 0)  return ;
    
    i = 0;
    while (i < target_len) {
        
        j = patlen-1;
        while (j >= 0 && (target_str[i+j] == pattern[j]))
            --j;
        if (j < 0) {    // got a match
            printf("MATCH!\n");
            return ;
        }
        printf("%d s%d\n",i,shift_map[target_str[i+patlen-1]]);
        i += shift_map[target_str[i+patlen-1]];
        
    }
    printf("NO MATCH\n");
    return;
    
}

int main(){
    int i;
    char pat[6] ="tooth";
    char target[50]="ladththtdootooth";
    build_shift_map(pat);
    bm_search(target,strlen(target),pat);
    
}