//
// Created by dania on 21.12.2023.
//

#ifndef TEST_C_DECODE_ARC_FILE_H
#define TEST_C_DECODE_ARC_FILE_H

void creat_map_from_arc_file(map* main,arc_file* file){
    main->size=file->size_of_abc;
    main->data=file->frequency_of_key;
    main->key=file->key_of_abc;
}
void from_char_bytes_to_string(char* text,int* size,int* extra_bits,string* bytes){
    bytes->size=*size*8-*extra_bits;
    bytes->string=(char*)malloc(bytes->size+1);
    bytes->string[bytes->size]='\0';
    unsigned char buffer;
    for(int i=0;i<bytes->size;i++){
        if(i%8==0)
            buffer=text[i/8];
        if((buffer>>(7-i%8))&1)
            bytes->string[i]='1';
        else
            bytes->string[i]='0';
    }
    printf("%s\n",bytes->string);
}
void decode_arc_file(arc_file* file_to_decode,FILE* file_to_write){
    map_c reverse_map;
    map map_of_abc;
    creat_map_from_arc_file(&map_of_abc,file_to_decode);
    creat_tree_of_Haffman(&reverse_map,&map_of_abc);
    string encode_text;
    from_char_bytes_to_string(file_to_decode->text,&file_to_decode->size_of_encode_text,(int*)&file_to_decode->extra_bits,&encode_text);
    string buffer,original_text;
    create_string(&buffer);create_string(&original_text);
    char tmp[2];tmp[1]='\0';
    for(int i=0;i<encode_text.size;i++){
        tmp[0]=encode_text.string[i];
        push_back(&buffer,tmp);
        tmp[0]=find_data_in_map_c(&reverse_map,buffer.string);
        if(tmp[0]!='\0'){
            push_back(&original_text,tmp);
            clear(&buffer);
        }
    }
    fseek(file_to_write,0,SEEK_SET);
    for(int i=0;i<original_text.size;i++){
        fwrite(&original_text.string[i],1,1,file_to_write);
    }
}
#endif //TEST_C_DECODE_ARC_FILE_H
