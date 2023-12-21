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
         char* tmp=(char*)malloc((strlen(line->string)+ strlen(sym))* sizeof(char));
        strcpy(tmp,line->string);
        strcat(tmp,sym);
        line->string=tmp;
        line->size+=strlen(sym);
    }
    else{
        line->string= (char*)malloc(strlen(sym)* sizeof(char));
        strcpy(line->string,sym);
        line->size=strlen(sym);
    }
}
void create_string(string* line){
    line->size=0;
}
void create_string_from_string(string* line,char* str,int size){
    line->size=size;
    line->string=(char*) malloc(line->size+1);
    strcpy(line->string,str);
}
void clear(string* main){
    main->size=0;
   // free(main->string);
}
#endif //TEST_C_STRING_H
