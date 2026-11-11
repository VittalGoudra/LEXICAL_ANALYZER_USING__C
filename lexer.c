#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include "lexer.h"

const char *keywords[32] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do",
    "double", "else", "enum", "extern", "float", "for", "goto", "if",
    "int", "long", "register", "return", "short", "signed", "sizeof", "static",
    "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"
};

const char single_operators[16] = {
    '+', '-', '*', '/', '%', '=', '>', '<',
    '&', '|', '^', '~', '!', '?', ':', '.'
};

const char *double_operators[21] = {
    "++", "--", "+=", "-=", "*=", "/=", "%=",
    "==", "!=", ">=", "<=", "&&", "||",
    "<<", ">>", "&=", "|=", "^=", "<<=", ">>=", "->"
};

const char punctuators[8] = {'(', ')', '{', '}', '[', ']', ';', ','};

int is_keyword(char* str)
{
    for(int i=0;i<32;i++)
    {
        if(strcmp(str,keywords[i])==0)
        {
            return 1;
        }
    }
    return 0;
}


//validation of a filename
int validate_filename(char* filename)
{
    char* extension=strrchr(filename,'.');
     if(extension == NULL)
     {
        return 0;
     }
     else if(strcmp(extension,".c")==0)
     {
        return 1;
     }
     
    return 0;   
}
   
void remove_comments(char* data)
{
    int i=0;                //"Hello how  //you" 
    int j=0;
    while(data[i]!='\0')
    { 
        if(data[i]=='"')
        {
            //copy the opening double quote
           data[j]=data[i];
           i++;
           j++;

           //copy the string contents

           while(data[i]!='\0')
           {
              // handle the eacape characters
              if(data[i]=='\\')
              {
                 data[j]=data[i];
                 i++;
                 j++;

                 if(data[i]!='\0')
                 {
                    data[j]=data[i];
                    i++;
                    j++;
                 }
              }
              else if(data[i]=='"')
              {
                data[j]=data[i];
                i++;
                j++;
                break;
              }
              else
              {
                data[j]=data[i];
                i++;
                j++;
              }
           }
          
        }  
        else if(data[i]=='\'')       // '\''  
            {
                //copy the opening character
                data[j]=data[i];
                i++;
                j++;

                //copy the contents
                while(data[i]!='\0')
                {
                    //handle the escape character
                    if(data[i]=='\\')
                    {
                        data[j]=data[i];
                        i++;
                        j++;

                        if(data[i]!='\0')
                        {
                            data[j]=data[i];
                            i++;
                            j++;
                        }
                    }
                        //check the closing sigle quote
                        else if(data[i]=='\'')
                        {
                            data[j]=data[i];
                            i++;
                            j++;
                            break;
                        }
                        else
                        {
                            data[j]=data[i];
                            i++;
                            j++;
                        }
                }
            }
        else if(data[i]=='/' && data[i+1]=='/')  //wwe are removing the comments and again storing back in the data (DMA )
                                                     //only
        {
            //skip the sigle line comment
            while(data[i]!='\n' && data[i]!='\0')
            {
                i++;
            }
        }
        //multi line comment removal
      else if(data[i]=='/' && data[i+1]=='*')
       {
          //skip opening
          i=i+2;

          while(data[i]!='\0')
          {
            //check closing
             if(data[i]=='*' && data[i+1]=='/')
             {
                i=i+2;
                break;
             }
             //preserve newline
             if(data[i] == '\n')
                {
                    data[j] = data[i];
                    j++;
                }
             i++;
          }
       }
        else
        {
            data[j]=data[i];
            j++;
            i++;
        }
    }

    data[j]='\0';
}

void remove_extra_spaces(char *data)
{
    int i = 0;
    int j = 0;
    int space = 0;

    while(data[i] != '\0')
    {
        // Handle string
        if(data[i] == '"')
        {
            if(space == 1 && j > 0)
            {
                data[j] = ' ';
                j++;
                space = 0;
            }

            // Copy complete string
            while(data[i] != '\0')
            {
                data[j] = data[i];

                if(data[i] == '\\' && data[i+1] != '\0')
                {
                    i++;
                    j++;
                    data[j] = data[i];
                }
                else if(data[i] == '"' && j > 0)
                {
                    i++;
                    j++;
                    break;
                }

                i++;
                j++;
            }
        }
        // Handle character constant
        else if(data[i] == '\'')
        {
            if(space == 1 && j > 0)
            {
                data[j] = ' ';
                j++;
                space = 0;
            }

            // Copy complete character constant
            while(data[i] != '\0')
            {
                data[j] = data[i];

                if(data[i] == '\\' && data[i+1] != '\0')
                {
                    i++;
                    j++;
                    data[j] = data[i];
                }
                else if(data[i] == '\'')
                {
                    i++;
                    j++;
                    break;
                }

                i++;
                j++;
            }
        }
        // Handle whitespace
        else if(data[i] == ' ' || data[i] == '\t')
        {
            space = 1;
            i++;
        }
        // Preserve newline
        else if(data[i] == '\n')
        {
            data[j] = data[i];
            i++;
            j++;
            space = 0;
        }
        else
        {
            if(space == 1 && j > 0 && data[j-1] != '\n')
            {
                data[j] = ' ';
                j++;
            }

            space = 0;

            data[j] = data[i];
            i++;
            j++;
        }
    }

    data[j] = '\0';
}

void tokenize(char* data)
{
    int line_count=1;
    char temp[100];
    

    char stack[100];
    int top = -1;

    int stack_line[100];

    printf("\n");
    printf("-------------------------------------------------------------------------\n");
    printf("%-25s %-30s %10s\n","LEXEME" , "TOKEN" ,"LINE NO.");
    printf("-------------------------------------------------------------------------\n");
    
    int i=0;
    while(data[i]!='\0')
    {
        if(isalpha(data[i]) || data[i]=='_' )
          {
             int k=0;

             while(isalnum(data[i]) || data[i]=='_')
               {
                if(k<99)
                 {
                   temp[k]=data[i];
                    k++;
                 }
                i++;
        
               }
               temp[k]='\0';
    
               int x=is_keyword(temp);
               if(x)
               {
                 printf("%-25s %-30s %10d \n", temp, "KEYWORD" ,line_count);
               }
               else
               {
                 printf("%-25s %-30s %10d \n", temp, "IDENTIFIER" ,line_count);
               }
        }
        else if(isdigit(data[i]))
        {
            int j=0;//temp
            int dot_count=0;
            int invalid=0;


            while(isalnum(data[i]) || data[i]=='.')
            {
                if(data[i]=='.')
                {
                    dot_count++;
                }
                else if(isalpha(data[i]))
                {
                    invalid=1;
                }
                if(j<100)
                {
                  temp[j]=data[i];
                  j++;
                }
                i++;
            }
            temp[j]='\0';
            if(invalid==1 || dot_count>1)
            {
                printf("%-25s %-30s %10d \n", temp, "INVALID CONSTANT" ,line_count);
            }
            else if(dot_count==1)
            {
                printf("%-25s %-30s %10d \n", temp, "FLOATING CONSTANT" ,line_count);
            }
            else
            {
                printf("%-25s %-30s %10d \n", temp, "INTEGER CONSTANT" ,line_count);
            }
        }
        else if(data[i] == '"')    //stsring constant
        {
            int k = 0;
            int closed=0;

            // Copy opening double quote
            temp[k] = data[i];
            k++;
            i++;

            // Read string contents
            while(data[i] != '\0' && data[i]!='\n' && data[i]!='\r')
             {
                // Handle escape characters
                if(data[i] == '\\')
                {
                    if(k < 98)
                    {
                      temp[k] = data[i];
                      k++;
                    }
                    i++;

                if(data[i] != '\0' && data[i]!='\n' && data[i]!='\r')
                    {
                      if(k < 98)
                      {
                       temp[k] = data[i];
                       k++;
                      }
                      i++;
                    }
                }
                   // Check closing double quote
                else if(data[i] == '"')
                {
                   if(k < 99)
                    {
                      temp[k] = data[i];
                      k++;
                    }
                    i++;
                    closed=1;
                    break;
                }
                else
                {
                   if(k < 99)
                   {
                     temp[k] = data[i];
                      k++;
                   }
                   i++;
                }
            }

            temp[k] = '\0';

            if(closed==1)
            {
                printf("%-25s %-30s %10d \n", temp, "STRING CONSTANT" ,line_count);
            }
            else 
            {
                printf("%-25s %-30s %10d \n", temp, "INVALID STRING CONSTANT" ,line_count);
            }   
        }  
        else if(data[i] == '\'')
        {
           int k = 0;
           int count = 0;

           temp[k++] = data[i];
           i++;

           while(data[i] != '\0' && data[i] != '\'' && data[i] != '\n')
            {
               if(data[i] == '\\')
                {
                  temp[k++] = data[i];
                  i++;

                   if(data[i] != '\0')
                   {
                      temp[k++] = data[i];
                      i++;
                      count++;
                   }
               }
               else
               {
                temp[k++] = data[i];
                i++;
                count++;
               }
            }

           if(data[i] == '\'')
           {
            temp[k++] = data[i];
             i++;
           }

           temp[k] = '\0';

            if(count == 1 && temp[k-1] == '\'')
             {
              printf("%-25s %-30s %10d\n", temp, "CHARACTER CONSTANT", line_count);
             }
            else
              {
                 printf("%-25s %-30s %10d\n", temp, "INVALID CHAR CONSTANT", line_count);
              }
        }  
        else if(data[i]=='#')
        {

           
            int k=0;
            while(data[i]!='\0' && data[i]!='\n' && data[i]!='\r')
            {
                //printf("Inside the loop : %c\n",data[i]);
                if(k<99)
                {
                    temp[k++]=data[i];
                }
                i++;
            }
            // printf("Total %d characterd occupies\n",k);
            temp[k]='\0';

            printf("%-25s %-30s %10d \n", temp, "PREPROCESSOR DIRECTIVE" ,line_count);
        }
        else if(data[i]=='+' || data[i]=='-' || data[i]=='*' || data[i]=='/' ||
                data[i]=='%' || data[i]=='=' || data[i]=='>' || data[i]=='<' ||
                data[i]=='&' || data[i]=='|' || data[i]=='^' || data[i]=='~' ||
                data[i]=='!' || data[i]=='?' || data[i]==':' || data[i]=='.' )
        {
                  int maxlen=0;
                  int found=0;

                  //check for the double and triple operators
                  for(int j=0;j<21;j++)
                  {
                    int len=strlen(double_operators[j]);

                    if(strncmp(&data[i],double_operators[j],len)==0)
                    {
                        if(len>maxlen)
                        {
                            maxlen=len;
                            found=1;
                        }
                    }
                  }
                  //if the double or triple is found
                  if(maxlen>0)
                  {
                    printf("%-25.*s %-30s %10d \n",maxlen, &data[i], "DOUBLE OPERATOR", line_count);
                    i=i+maxlen;
                  }
                  else
                  {
                    //otherwise check single character operator                    
                    for(int j=0;j<16;j++)
                    {
                        if(data[i]==single_operators[j])
                        
                          printf("%-25c %-30s %10d\n", data[i], "OPERATOR", line_count);
                           break;
                        }
                    }
                    i++;    
        }  
        else if(data[i]=='(' || data[i]==')' || data[i]=='{' || data[i]=='}' ||
                data[i]=='[' || data[i]==']' || data[i]==';' || data[i]==',')
        {
            for(int j=0; j<8; j++)
            {
               if(data[i] == punctuators[j])
                   {
                      printf("%-25c %-30s %10d\n",data[i], "SPECIAL SYMBOL", line_count);
                      break;
                   }
            }

            // Opening delimiters
            if(data[i]=='(' || data[i]=='{' || data[i]=='[')
            {
              top++;
              stack[top] = data[i];
              stack_line[top] = line_count;
            }

           // Closing delimiters
            else if(data[i]==')' || data[i]=='}' || data[i]==']')
            {
                if(data[i] == '}')
                {
                  check_missing_semicolon(data, i, line_count);
                }
               
                if(top == -1)
                {
                    printf("ERROR: Extra closing delimiter '%c' at line %d\n",data[i], line_count);
                }
                else if((stack[top]=='(' && data[i]==')') ||
                        (stack[top]=='{' && data[i]=='}') ||
                        (stack[top]=='[' && data[i]==']'))
                {
                   top--;
                }
                else
                {
                   printf("ERROR: Mismatched delimiter '%c' at line %d\n", data[i], line_count);
                   top--;
                }
            }

            i++;

        }
        else if(data[i] == '\n')
        {
            check_missing_semicolon(data, i, line_count);

            line_count++;
            i++;
       }
        else if(isspace(data[i]))
        {
            i++;
        }  
        else
        {
           printf("%-25c %-30s %10d \n",data[i] , "UNKNOWN TOKEN", line_count);
           i++;
        }
    
    }
    while(top >= 0)
    {
        if(stack[top] == '(')
          printf("ERROR: Missing ')' for '(' opened at line %d\n",stack_line[top]);

        else if(stack[top] == '{')
          printf("ERROR: Missing '}' for '{' opened at line %d\n",stack_line[top]);

      else if(stack[top] == '[')
        printf("ERROR: Missing ']' for '[' opened at line %d\n",stack_line[top]);

      top--;
    }
    printf("-------------------------------------------------------------------------\n");

}
 
void check_missing_semicolon(char *data, int pos, int line_count)
{
    int i = pos - 1;

    // Skip spaces, tabs and Windows newline character
    while(i >= 0 && (data[i] == ' ' || data[i] == '\t' || data[i] == '\r'))
        i--;

    // Empty line
    if(i < 0 || data[i] == '\n')
        return;

    // Valid endings
    if(data[i] == ';' || data[i] == '{' ||
       data[i] == '}' || data[i] == ':' ||
       data[i] == ')' || data[i] == ',')
        return;

    // Find beginning of line
    int start = i;

    while(start >= 0 && data[start] != '\n')
        start--;

    start++;

    // Skip leading spaces
    while(data[start] == ' ' || data[start] == '\t')
        start++;

    // Ignore preprocessor
    if(data[start] == '#')
        return;

    // Ignore control statements
    if(strncmp(&data[start], "if", 2) == 0 ||
       strncmp(&data[start], "else", 4) == 0 ||
       strncmp(&data[start], "for", 3) == 0 ||
       strncmp(&data[start], "while", 5) == 0 ||
       strncmp(&data[start], "do", 2) == 0)
        return;

    printf("ERROR: Missing ';' at line %d\n", line_count);
}