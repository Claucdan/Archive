#ifndef TEST_C_ARC_H
#define TEST_C_ARC_H

typedef struct arc arc;
typedef struct arc_file arc_file;
typedef struct abc_of_file abc_of_file;

struct arc{
    int count_of_file;
    char** name_of_file;
    int* offset_of_file;
};
struct arc_file{
    int size_of_all;
    int offset_of_file_in_archive;
    int size_of_abc;
    char* key_of_abc;
    int* frequency_of_key;
    int size_of_encode_text;
    unsigned int extra_bits;
    char* text;
};
struct abc_of_file{
    char* key;
    int* size_of_code;
    char** code
};


void read_from_file(string* line,FILE* input);
void creat_map_of_string(map* abc,string* line);
void creat_tree_of_Haffman(map_c* main,map* map_of_abc);
void create_arc_file(FILE* file,arc_file* arcFile);
void encode_original_text_to_bits(arc_file* file,map_c* main,string* original_text);
void creat_mass_of_encode_message(arc_file* file,string* text);
void copy_from_map_of_abc_to_arc_file_abc(arc_file* file,map* map_of_abc);
void write_arc_file(FILE* output,arc_file* file);

/*Reading basic archive data*/
void read_arc(FILE* archive,arc* main){
    fseek(archive,0,SEEK_SET);
    fread(&main->count_of_file,sizeof(int),1,archive);
    main->name_of_file=(char**)malloc(main->count_of_file);
    main->offset_of_file=(int*)malloc(main->count_of_file);
    for(int i=0;i<main->count_of_file;i++){
        main->name_of_file[i]=(char*) malloc(20);
    }
    for(int i=0;i<main->count_of_file;i++)
        fread(main->name_of_file[i],20,1,archive);
    fread(main->offset_of_file, sizeof(int),main->count_of_file,archive);
    for(int i=0;i<main->count_of_file;i++){
        printf("%s %d\n",main->name_of_file[i],main->offset_of_file[i]);
    }
}
/*Read basic file data*/
void read_file(FILE* archive,arc* main,struct arc_file* file){
    fseek(archive,file->offset_of_file_in_archive,SEEK_SET);
    fread(&file->size_of_abc, sizeof(int),1,archive);
    file->key_of_abc=(char*) malloc(file->size_of_abc* sizeof(char));
    file->frequency_of_key=(int*) malloc(file->size_of_abc* sizeof(int));
    for(int i=0;i<file->size_of_abc;i++){
        fread(&file->key_of_abc[i],1,1,archive);
        fread(&file->frequency_of_key[i], sizeof(int),1,archive);
    }
    fread(&file->size_of_encode_text, sizeof(int),1,archive);
    fread(&file->extra_bits, sizeof(unsigned int),1,archive);
    file->text=(char*) malloc(file->size_of_encode_text* sizeof(char));
    for(int i=0;i<file->size_of_encode_text;i++) {
        fread(&file->text[i],1,1,archive);
    }
    for(int i=0;i<file->size_of_abc;i++){
        printf("%c %d\n",file->key_of_abc[i],file->frequency_of_key[i]);
    }
    printf("%s\n",file->text);
}










/*Find offset of chosen file*/
int find_offset_of_file(arc* main,char* name_of_file){
    for(int i=0;i<main->count_of_file;i++){
        if(!strcmp(name_of_file,main->name_of_file[i]))
            return main->offset_of_file[i];
    }
    printf("No such file in archive\n");
    //exit(-2);
    return 0;
}



/*Write files to archive*/
void write_archive(FILE* archiv,int count,char *name[]){
    fseek(archiv,0,SEEK_SET);
    fwrite(&count, sizeof(int),1,archiv);
    arc_file *arcFiles=(arc_file*) malloc(count*sizeof(arc_file*));


    /*Write name of Files*/
    for(int i=0;i<count;i++){
        char *str=(char*) malloc(20);
        strcpy(str,name[i+1]);
        fwrite(str,20,1,archiv);
        free(str);
    }

    for(int i=0;i<count;i++){
        FILE* file_to_copy= fopen(name[i+1],"rb");
        create_arc_file(file_to_copy,&arcFiles[i]);
        fclose(file_to_copy);
    }


    /*Write offset of files*/
    int start=4+20*count+4*count;
    for(int i=0;i<count;i++){
        fwrite(&start, sizeof(int),1,archiv);
        start+=arcFiles[i].size_of_all;
    }
    /*Write information of files*/
    for(int i=0;i<count;i++){
        write_arc_file(archiv,&arcFiles[i]);
    }
    fclose(archiv);
}




void write_arc_file(FILE* output,arc_file* file){
    fwrite(&file->size_of_abc, sizeof(int),1,output);
    for(int i=0;i<file->size_of_abc;i++){
        fwrite(&file->key_of_abc[i],1,1,output);
        fwrite(&file->frequency_of_key[i], sizeof(int),1,output);
    }
    fwrite(&file->size_of_encode_text, sizeof(int),1,output);
    fwrite(&file->extra_bits, sizeof(unsigned int),1,output);
    fwrite(file->text,file->size_of_encode_text,1,output);
}









/*Creat encode file what we put in archive*/
void create_arc_file(FILE* file,arc_file* arcFile){
    fseek(file,0,SEEK_SET);
    string original_text;map map_of_abc;map_c reverse_map;
    /*Read information of original file*/
    read_from_file(&original_text,file);
    /*Creat map of sym*/
    creat_map_of_string(&map_of_abc,&original_text);
    //print_map(&map_of_abc);
    /*Creat map of encode string*/
    creat_tree_of_Haffman(&reverse_map,&map_of_abc);
    //print_map_c(&reverse_map);
    copy_from_map_of_abc_to_arc_file_abc(arcFile,&map_of_abc);
    encode_original_text_to_bits(arcFile,&reverse_map,&original_text);

    arcFile->size_of_all= sizeof(int)+(sizeof(int)+1)* arcFile->size_of_abc+ sizeof(int)+sizeof(int)+ arcFile->size_of_encode_text;
    printf("check");
}








/*Copy from map to abc of file in archive*/
void copy_from_map_of_abc_to_arc_file_abc(arc_file* file,map* map_of_abc){
    file->size_of_abc=map_of_abc->size;
    file->key_of_abc= map_of_abc->key;
    file->frequency_of_key=map_of_abc->data;
}
/*Creat message from text and map of keys*/
void encode_original_text_to_bits(arc_file* file,map_c* main,string* original_text){
    string line;create_string(&line);
    for(int i=0;i<original_text->size;i++){
        find_c_buf(main,original_text->string[i],&line);
    }
    //printf("%s\n",line.string);
    creat_mass_of_encode_message(file,&line);
}
/*Creat mass of bytes to write in file*/
void creat_mass_of_encode_message(arc_file* file,string* text){
    string to_write;create_string(&to_write);
    char buffer=0;
    char tmp[2];tmp[1]='\0';
    for(int i=0;i< strlen(text->string);i++){
        if(i%8==0 && i!=0){
            tmp[0]=buffer;
            push_back(&to_write,tmp);
        }
        if(text->string[i]=='1'){
            buffer=(buffer<<1)|1;
        }
        else
            buffer=(buffer<<1)|0;

    }
    if((file->extra_bits=(8-strlen(text->string)%8))!=8){
        buffer=(buffer<<file->extra_bits)|0;
    }
    tmp[0]=buffer;
    push_back(&to_write,tmp);
    //printf("%s\n",to_write.string);
    file->size_of_encode_text= to_write.size;
    file->text=to_write.string;
}








/*Read information from file to string*/
void read_from_file(string* line,FILE* input){
    create_string(line);
    char* buffer_to_read=(char*) malloc(2);
    buffer_to_read[1]='\0';
    while((buffer_to_read[0]=fgetc(input)) != EOF){
        push_back(line,buffer_to_read);
    }
    //printf("%s\n",line->string);
}
/*Creat map of string*/
void creat_map_of_string(map* abc,string* line){
    create_map(abc,256);
    for(int i=0;i< strlen(line->string);i++){
        find(abc,line->string[i]);
    }
}
/*Creat reverse map for string*/
void creat_tree_of_Haffman(map_c* main,map* map_of_abc){
    priority_queue queue;
    create_queue(&queue,256);
    for(int i=0;i<map_of_abc->size;i++){
        Node* tmp=(Node*) malloc(sizeof (Node));
        tmp->sym=map_of_abc->key[i];
        tmp->data=map_of_abc->data[i];
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
    create_map_c(main,256);
    char* str="";
    create_revarse_map(main,root,str);
}


#endif //TEST_C_ARC_H
