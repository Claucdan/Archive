//
// Created by dania on 08.12.2023.
//

#ifndef TEST_C_STRING_H
#define TEST_C_STRING_H
typedef struct string string;
struct string {
     char* string;
    int size;
};

void push_back(string* line, char* sym){
    if(line->size!=0){
         char* tmp=(char*)malloc(strlen(line->string)+ strlen(sym));
        strcpy(tmp,line->string);
        strcat(tmp,sym);
        line->string=tmp;
        line->size+=strlen(sym);
    }
    else{
        line->string= (char*)malloc(strlen(sym));
        strcpy(line->string,sym);
        line->size=strlen(sym);
    }
}
void create_string(string* line){
    line->size=0;
}


#endif //TEST_C_STRING_H
