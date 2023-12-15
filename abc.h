//
// Created by dania on 08.12.2023.
//

#ifndef TEST_C_ABC_H
#define TEST_C_ABC_H
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "string.h"


typedef struct {
    unsigned char *key;
    int *data;
    int max_size;
    int size;
}map;
typedef struct {
    unsigned char *key;
    unsigned char **data;
    int max_size;
    int size;
}map_c;

/*Find in map element this key*, if there is no such element, then we create it*/
int find(map* main,unsigned char key){
    for(int i=0;i<main->size;i++){
        if(main->key[i]==key)
            return ++main->data[i];
    }
    main->key[main->size]=key;
    main->data[main->size]=1;
    main->size++;
    return 1;
}


/*Find in map element this key*, if there is no such element, then we create it*/
unsigned char* find_c(map_c* main,unsigned char key){
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
void find_c_buf(map_c* main,unsigned char key,string* buf){
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
void add(map_c* main,unsigned char* key,unsigned char* data){
    main->key[main->size]=*key;
    main->data[main->size]=(unsigned char *) malloc(strlen(data));
    strcpy(main->data[main->size],data);
    main->size++;
}

/*Constructor of map*/
int create_map(map* main,int max_size){
    main->size=0;
    main->max_size=max_size;
    main->key=(unsigned char*)malloc(max_size);
    main->data=(int*)malloc(max_size);
}



/*Constructor of map_c*/
int create_map_c(map_c* main,int max_size){
    main->size=0;
    main->max_size=max_size;
    main->key=(unsigned char*)malloc(max_size);
    main->data=(unsigned char**)malloc(max_size);
}


#endif //TEST_C_ABC_H
