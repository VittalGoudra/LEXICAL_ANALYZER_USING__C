/*
PROJECT NAME : LEXICAL ANALYZER

I developed a Lexical Analyzer project in C to analyze and tokenize source code.
It identifies and classifies tokens such as Keywords, Identifiers, Operators, Constants, and Special Symbols.
It also detects basic lexical and syntax-related errors in C programs, such as invalid tokens, unmatched delimiters, and missing semicolons.

NAME   : Vittal S. Goudra
MOB    : 8867462834
EMAIL  : vittalgoudra123@gmail.com
BATCH  : 26015B

*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "lexer.h"



//   argv[0]   argv[1]
//   ./a.out   input.c 
int main(int argc,char* argv[])
{
   if(argc<2)
   {
    printf("ERROR : Invalid arguments\n");
    printf("Usage : \n");
    printf("./a.out  input_filename.c\n");
    return 1;
   }
   else
   {
    if(!validate_filename(argv[1]))
    {
      printf("Error : please provide .c extension file\n");
      return 1;
    }
   }
   printf("Filename validation successful\n");
   //printf("-----------------------------------\n");

   //file handling part

   FILE* fp=fopen(argv[1],"r");//dont use double quotes in like "argv[1]"
    if(fp==NULL)
    {
        printf("Error : Unale to read the file\n");
        return 1;
    }
    fseek(fp,0,SEEK_END);
    long size=ftell(fp);
      if(size<0)
      {
        printf("Unable to calculate the size of file\n");
        fclose(fp);
        return 1;
      }
    rewind(fp);

    char* data=malloc(size+1);  //data is like a buffer 
    if(data==NULL)
    {
        printf("Memory not allocated \n");
        //free(data);
        fclose(fp);
        return 1;
    }
    size_t bytes_read=fread(data,1,size,fp);
    data[bytes_read]='\0';

    if(bytes_read!=(size_t)size)
    {
        printf("Error : Unable to read complete file\n");
        free(data);
        fclose(fp);
        return 1;
    }
    printf("\n");
    printf("-------FILE CONTENTS-------\n");
    printf("\n");
    printf("%s\n",data); //printing the data

   

   // printf("--------------------------------------------------------\n");
    remove_comments(data);
    //printf("After removing the comments\n");
    //printf("\n");
   // printf("%s",data);


    remove_extra_spaces(data);
    //printf("\n");
   // printf("%s",data);
      
    printf("\n"); 
    //printf("----------------------------------\n");
    tokenize(data);
    
    fclose(fp);
    free(data);

   return 0;
}