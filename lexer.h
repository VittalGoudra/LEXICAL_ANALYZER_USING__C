#ifndef LEXER_H
#define LEXER_H

#define success 1
#define failure 0

//validation of a filename
int validate_filename(char* filename);

void remove_comments(char* data);

void remove_extra_spaces(char* data);

void tokenize(char* data);

int is_keyword(char* str);

void check_missing_semicolon(char *data, int pos, int line_count);

#endif
