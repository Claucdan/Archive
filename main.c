#include <stdlib.h>
#include <stdio.h>
#include "priorety_queue.h"
#include "abc.h"
#include <string.h>
#include "tree_of_haffman.h"
#include "string.h"
#include "arc.h"
#include "decode_arc_file.h"
enum mode_of_archive{
    creat,
    list,
    extract,
    none
};


void mode_creat(char* files_name[],int count_of_files,char* name_of_archive){
    printf("Start of creat archive\n");
    printf("Completed work [*///////////////////]\n");
    FILE* archive= fopen(name_of_archive,"w");
    write_archive(archive,count_of_files,files_name);
    printf("Completed work [********************]\n");
    printf("Archiving completed, thanks for waiting\n");
    fclose(archive);
}

void mode_list(char* name_of_archive){
    printf("**********INFORMATION ABOUT ARCHIVE**********\n");
    FILE* archive= fopen(name_of_archive,"rb");
    if(archive==NULL){
        printf("No such archive");
        exit(-1);
    }
    arc archive_header;
    read_arc(archive,&archive_header);
    printf("Count of files in archive: %d\n",archive_header.count_of_file);
    printf("Files     |     Offset\n");
    for(int i=0;i<archive_header.count_of_file;i++){
        printf("%s   %d\n",archive_header.name_of_file[i],archive_header.offset_of_file[i]);
    }
    printf("*********************************************");
    fclose(archive);
}

void mode_extract(char* files_name[],int count_of_files,char* name_of_archive){
    if(count_of_files>1){
        printf("Choose more less files");
    }
    FILE* archive= fopen(name_of_archive,"rb");
    if(archive==NULL){
        printf("No such archive");
        exit(-1);
    }
    printf("**********START OF EXTRACT FILE FROM ARCHIVE**********\n");
    arc archive_header;
    read_arc(archive,&archive_header);
    printf("Completed work [*///////////////////]\n");
    arc_file arcFile;
    arcFile.offset_of_file_in_archive=find_offset_of_file(&archive_header,files_name[0]);
    read_file(archive,&archive_header,&arcFile);
    printf("Completed work [***/////////////////]\n");
    FILE *file= fopen(files_name[0],"w");
    decode_arc_file(&arcFile,file);
    fclose(file);
    printf("Completed work [********************]\n");
    printf("******************************************************\n");
}


int main(int argc, char *argv[]){
    enum mode_of_archive mode=none;
    char* name_of_archive=NULL;
    int count_of_files=0;
    char* files_name[10];
    for(int i=1;i<argc;i++) {
        if (argv[i][0] == '-') {
            if(argv[i][2]=='f'){
                name_of_archive = argv[i + 1];
                i++;
            }
            else if(argv[i][2] == 'c')
                mode=creat;
            else if(argv[i][2] == 'l')
                mode=list;
            else if(argv[i][2] == 'e')
                mode=extract;
        }
        else {
            files_name[count_of_files++]=argv[i];
        }
    }
    if(name_of_archive==NULL){
        printf("You don't choose archive for work");
        exit(-2);
    }



    switch (mode) {
        case creat:
            if(count_of_files==0){
                printf("You don't choose files for work");
                exit(-2);
            }
            mode_creat(files_name,count_of_files,name_of_archive);
            break;
        case list:
            mode_list(name_of_archive);
            break;
        case extract:
            if(count_of_files==0){
                printf("You don't choose files for work");
                exit(-2);
            }
            mode_extract(files_name,count_of_files,name_of_archive);
            break;
        case none:
            printf("You don't choose action for archive");
            exit(-2);
    }

    return 0;
}