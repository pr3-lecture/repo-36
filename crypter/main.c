#include <stdio.h>
#include "crypto.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h> 
#include <errno.h>



void convertToUppercase(char* temp){
  while(*temp){
  *temp = toupper((unsigned char)*temp);//toupper expects an integer in the range of an unsigned char.
  temp++;
 }
}


int main(int argc, char** argv){ 

    int result = 0;             
    char buffer[255];
    char* input;
    char* output;
    FILE* fp;
    KEY key ={1,argv[1]};



    int (*func)(KEY, const char*, char*)=NULL;

    if(strcmp(argv[0],"./encrypt")==0){
        func = encrypt;
        printf("USING ENCRYPT\n");
    }else if(strcmp(argv[0],"./decrypt")==0){
        func = decrypt;
        printf("USING DECRYPT\n");
    }else{
        fprintf(stderr, "%s", "Illegal file name\n");
        //https://stackoverflow.com/questions/2425167/use-of-exit-function
        return (EXIT_FAILURE);
    }


    switch(argc){

    case 1:  fprintf(stderr, "%s", "Usage: KEY [file name]\n");
             fprintf(stderr, "%s", "./encrypt aaa ../test.txt\n");
             break;

    case 2:  input = fgets(buffer,254,stdin);
             int result = 0;

             if(input[strlen(input)-1] =='\n'){
                input[strlen(input)-1]='\0';
             }
             
             output = (char*) malloc(strlen(input) + 1);
             convertToUppercase(input);
             convertToUppercase(key.chars);

             result=(*func)(key,input,output);
             printf("%s\n",output);
             free(output);
             break;

    case 3:  convertToUppercase(key.chars);
             fp = fopen(argv[2],"r");
             
             if(fp==NULL){
                fprintf(stderr,"Error opening file: %s\n",strerror(errno));
                return (EXIT_FAILURE);
             }
             
             while((input=fgets(buffer,254,fp))){

                convertToUppercase(input);

                if(input[strlen(input)-1] =='\n'){
                    input[strlen(input)-1]='\0';
                }

                output=(char*) malloc(strlen(input)+1);
                result=(*func)(key,input,output);

                if(result!=0){
                    free(output);
                    fclose(fp);
                    return result;
                }
                printf("%s\n",output);

             }

             free(output);
             fclose(fp);
             break;
    }
    return result;
}
