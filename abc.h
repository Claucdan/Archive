//
// Created by dania on 08.12.2023.
//

#ifndef TEST_C_ABC_H
#define TEST_C_ABC_H
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "string.h"

typedef struct map map;
typedef struct map_c map_c;
struct map{
     char *key;
    int *data;
    int max_size;
    int size;
};
struct map_c{
    char *key;
    char **data;
    int max_size;
    int size;
};
/*Find in map element this key*, if there is no such element, then we create it*/
int find(map* main, char key){
    for(int i=0;i<main->size;i++){
        if(main->key[i]==key)
            return ++main->data[i];
    }
    if(main->size!=0){
        main->key=(char*) realloc(main->key,main->size+1);
        main->data=(int*) realloc(main->data,main->size* sizeof(int)+ sizeof(int));
    }
    else{
        main->key=(char*) malloc(1);
        main->data=(int*) malloc(sizeof(int));
    }
    main->key[main->size]=key;
    main->data[main->size]=1;
    main->size++;
    return 1;
}
/*Find in map element this key*, if there is no such element, then we create it*/
char* find_c(map_c* main, char key){
    for(int i=0;i<main->size;i++){
        if(main->key[i]==key)
            return main->data;
    }
    main->key[main->size]=key;
    main->data[main->size]="";
    main->size++;
    return "";
}
/*Find in map element this key* and insert in string*/
void find_c_buf(map_c* main, char key,string* buf){
    for(int i=0;i<main->size;i++){
        if(main->key[i]==key){
            push_back(buf,main->data[i]);
            return;
        }
    }
}
/*Print all key this data*/
void print_map(map* main){
    for(int i=0;i<main->size;i++){
        printf("%c %d\n",main->key[i],main->data[i]);
    }
}
/*Print all key this data*/
void print_map_c(map_c* main){
    for(int i=0;i<main->size;i++){
        printf("%c %s\n",main->key[i],main->data[i]);
    }
}
/*Add in map key this data*/
void add(map_c* main, char* key, char* data){
    if(main->size!=0){
        main->key=(char*) realloc(main->key,main->size*sizeof(char*)+sizeof(char*));
        main->data=(char**) realloc(main->data,main->size*sizeof(char**)+sizeof(char**));
    }
    else{
        main->key=(char*) malloc(sizeof(char*));
        main->data=(char**) malloc(sizeof(char**));
    }
    main->key[main->size]=*key;
    main->data[main->size]=(char*) malloc(strlen(data)+1);
    strcpy(main->data[main->size],data);
    main->size++;
}
/*Constructor of map*/
int create_map(map* main,int max_size){
    main->size=0;
    main->max_size=max_size;
}
/*Constructor of map_c*/
int create_map_c(map_c* main,int max_size){
    main->size=0;
    main->max_size=max_size;
}
char find_data_in_map_c(map_c* main,char* sym){
    for(int i=0;i<main->size;i++){
        if(!strcmp(main->data[i],sym))
            return main->key[i];
    }
    return '\0';
}


#endif //TEST_C_ABC_H
