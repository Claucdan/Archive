//
// Created by dania on 08.12.2023.
//

#ifndef TEST_C_STRING_H
#define TEST_C_STRING_H

typedef struct {
    unsigned char* string;
    int size;
}string;

void push_back(string* line,unsigned char* sym){
    if(line->size!=0){
        unsigned char* tmp=(unsigned char*)malloc(strlen(line->string)+1);
        strcpy(tmp,line->string);
        strcat(tmp,sym);
        line->string=tmp;
        line->size++;
    }
    else{
        line->string= (unsigned char*)malloc(strlen(sym));
        strcpy(line->string,sym);
        line->size++;
    }
}
void create_string(string* line){
    line->size=0;
}


#endif //TEST_C_STRING_H
