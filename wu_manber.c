#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int shift_table[95][95],max_shift;
char one_word_pat[127];


int get_shift(char* str_to_hash){	//transform two char to hash as index 
	return shift_table[str_to_hash[0]-32][str_to_hash[1]-32];
}

void search(char* target_str, char** pattern){	//wu-manber search 
    int i,j,shift;
 	int target_len = strlen(target_str);

    i = 0;
    while (i+max_shift-2 < target_len) {
        for(j=0; pattern[j]!=NULL;j++){
        	if(!strncmp(target_str + i, pattern[j], strlen(pattern[j])))
        		printf("MATCH pattern %s\n",pattern[j]);
        }
        shift = get_shift(target_str+max_shift-2+i);
        i += shift;
    }
    printf("NO MATCH\n");
    return;
}

void init(char** pattern){
	int i,j,len;
	int one_word_count = 0;
	char first_char, char1, char2;
	max_shift = 999999;
	for(i=0;pattern[i]!=NULL;i++){	//get the min length of all pattern as max shift window
		len = strlen(pattern[i]);
		if(len>1 &&  max_shift>len)
			max_shift = len;
		else if(len == 1)	//we use two char as hash, so pattern with one char only should be handled exceptionally 
			one_word_pat[one_word_count++] = pattern[i][0];
	}

	one_word_pat[one_word_count] = '\0';

	for(i=0;i<95;i++)
		for(j=0;j<95;j++)
			shift_table[i][j] = max_shift;

	for(i=0;pattern[i] != NULL; i++){		
		for(j=0;j<95;j++){
			first_char = pattern[i][0];
			if(shift_table[j][first_char-32] > max_shift-2)
				shift_table[j][first_char-32] = max_shift-2;

		}
		len = strlen(pattern[i]);
		for(j=0;j<max_shift-2;j++){
			char1 = pattern[i][j];
			char2 = pattern[i][j+1];

			if(shift_table[char1-32][char2-32] > max_shift-j-2)
				shift_table[char1-32][char2-32] = max_shift-j-2;
			printf("%c%c:%d\n",char1,char2,max_shift-j-2);
		}
	}
	return ;
}

int main(){
	char text[500] = "tttttooh ateetchtzztooth?finthnaltfinal youuuuz youu";
	char** pattern;
    int i;
    pattern = (char**)malloc(sizeof(char*) * 6 );
    for(i=0;i<5;i++)
        pattern[i] = (char*)malloc(sizeof(char)*50);
    pattern[5] = NULL;
	strcpy(pattern[0],"teeth");
	strcpy(pattern[1],"tooth");
	strcpy(pattern[2],"teezzzzz");
	strcpy(pattern[3],"final");
	strcpy(pattern[4],"youuuu");
	init(pattern);
	search(text,pattern);
	return 0;
	}