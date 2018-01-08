#include "crypto.h"
#include <stdio.h>
#include <string.h> //strlen
#include <ctype.h> //toupper
#include <stdlib.h>


int isAllowed(const char* input,char* allowedChars){
    int i;
    int j;
    int counter = 0;
    int len = strlen(allowedChars);
    int lenInput=strlen(input);
    for(i=0;i<lenInput;i++){
        for(j=0;j<len;j++){
            if(input[i]==allowedChars[j]){
                counter++;
            }
        }
    } 

    if(counter!=lenInput){
        return -1;
    }

    return 0;
}

int helper(KEY key, const char* input,char* output){
    int i = 0;
    int j = 0;
    int len = strlen(input);
    int lenKey = strlen(key.chars);

    for(i=0;i<len;i++){
        output[i] = ((input[i] -'A'+1)^(key.chars[j]-'A'+1))+'A'-1;
        j=(j+1)%lenKey;
    }

    return 0;
}

int encrypt(KEY key, const char* input, char* output){

    if(isAllowed(input,MESSAGE_CHARACTERS)==-1){
        fprintf(stderr, "%s", "E_MESSAGE_ILLEGAL_CHAR\n");
        return E_MESSAGE_ILLEGAL_CHAR;
    }

    if(strlen(key.chars) == 0){
        fprintf(stderr, "%s", "E_KEY_TOO_SHORT\n");
        return E_KEY_TOO_SHORT;
    }

    if(isAllowed(key.chars,KEY_CHARACTERS)==-1){
        fprintf(stderr, "%s", "E_KEY_ILLEGAL_CHAR\n");
        return E_KEY_ILLEGAL_CHAR;
    }
 

    return helper(key,input,output);
}



int decrypt(KEY key, const char* cypherText,char* output){
 
    if(isAllowed(cypherText,CYPHER_CHARACTERS)==-1){
        fprintf(stderr, "%s", "E_CYPHER_ILLEGAL_CHAR\n");
        return E_CYPHER_ILLEGAL_CHAR;
    }

    if(strlen(key.chars) == 0){
        fprintf(stderr, "%s", "E_KEY_TOO_SHORT\n");
        return E_KEY_TOO_SHORT;
    }

    if(isAllowed(key.chars,KEY_CHARACTERS)==-1){
        fprintf(stderr, "%s", "E_KEY_ILLEGAL_CHAR\n");
        return E_KEY_ILLEGAL_CHAR;
    }

 
    return helper(key,cypherText,output);
}





