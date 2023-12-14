#ifndef TEST_C_ENCODE_H
#define TEST_C_ENCODE_H
#include "string.h"
#include <stdlib.h>
#include <stdio.h>
void encode(FILE* input,FILE* output,map_c* main);
void archiv(int argc, char *argv[]);
/*void write_code(FILE* output,map_c* main);*/
void from_string_to_bits(FILE* output,char* line)   {
    char buffer;
    int i=0;
    while(line[i]!='\0'){
        buffer=0;
        for(int j=0;j<8 && i+j< strlen(line);j++){
            if(line[i+j]=='1'){
                buffer=(buffer<<1)|1;
            }
            else
                buffer=(buffer<<1)|0;
        }
        printf("%d\n",buffer);i+=8;
        fwrite(&buffer,1,1,output);
    }
}


void archiv(int argc, char *argv[]) {

    /*Открытие файлов*/
    FILE *input,*output;
    char* buffer;
    strtok_r(argv[1],"=",&buffer);
    char* name_file_input = strtok_r(NULL, "", &buffer);
    input = fopen(name_file_input, "rb");
    strtok_r(argv[2],"=",&buffer);
    char* name_file_output = strtok_r(NULL, "", &buffer);
    output = fopen(name_file_output, "w");


    /*Ставим указатель в начале*/
    fseek(input,0,SEEK_SET);



    string original_text;
    create_string(&original_text);

    /*Чтение сообщения из файла*/
    char* buffer_to_read=(char*) malloc(2);
    buffer_to_read[1]='\0';
    printf("check\n");
    while((buffer_to_read[0]=fgetc(input)) != EOF){
        push_back(&original_text,buffer_to_read);
    }



    /*Вывод исходной строки*/
    printf("check\n");
    printf("%s",original_text.string);




    map map_of_abc;
    priority_queue queue;

    create_queue(&queue,256);
    create_map(&map_of_abc,256);


    for(int i=0;i< strlen(original_text.string);i++){
        find(&map_of_abc,original_text.string[i]);
    }
    print_map(&map_of_abc);
    printf("\n");
    for(int i=0;i<map_of_abc.size;i++){
        Node* tmp=(Node*) malloc(sizeof (Node));
        tmp->sym=map_of_abc.key[i];
        tmp->data=map_of_abc.data[i];
        insert(&queue,tmp);
    }
    while (queue.size!=1){
        Node* first= extract_min(&queue);
        Node* second= extract_min(&queue);
        Node* tmp=(Node*) malloc(sizeof (Node));
        tmp->data= first->data+second->data;
        tmp->sym='\0';
        tmp->left=first;
        tmp->right=second;
        insert(&queue,tmp);
    }
    Node* root=extract_min(&queue);
    map_c reverse_map;
    char* str="";
    create_map_c(&reverse_map,256);
    create_revarse_map(&reverse_map,root,str);
    print_map_c(&reverse_map);


    encode(input,output,&reverse_map);



    fclose(input);
    fclose(output);


}

void encode(FILE* input,FILE* output,map_c* main){
    fseek(input,0,SEEK_SET);
    string original_text;
    create_string(&original_text);
    char* buffer_to_read=(char*) malloc(2);
    buffer_to_read[1]='\0';
    while((buffer_to_read[0]=fgetc(input)) != EOF){
        find_c_buf(main,buffer_to_read[0],&original_text);
    }
    printf("%s",original_text.string);

    fseek(output,0,SEEK_SET);
    /*write_code(output,main);*/
    from_string_to_bits(output,original_text.string);
}

#endif //TEST_C_ENCODE_H
