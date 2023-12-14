//
// Created by dania on 08.12.2023.
//

#ifndef TEST_C_STRING_H
#define TEST_C_STRING_H

typedef struct {
    char* string;
    int size;
}string;

void push_back(string* line,char* sym){
    if(line->size!=0){
        char* tmp=(char*)malloc(strlen(line->string)+1);
        strcpy(tmp,line->string);
        strcat(tmp,sym);
        line->string=tmp;
        line->size++;
    }
    else{
        line->string= (char*)malloc(strlen(sym));
        strcpy(line->string,sym);
        line->size++;
    }
}
void create_string(string* line){
    line->size=0;
}


#endif //TEST_C_STRING_H