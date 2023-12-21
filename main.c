#include <stdlib.h>
#include <stdio.h>
#include "priorety_queue.h"
#include "abc.h"
#include <string.h>
#include "tree_of_haffman.h"
#include "encode.h"
#include "string.h"
#include "arc.h"

int main(int argc, char *argv[]){
 //   archiv(argc,argv);
    /*FILE* file= fopen("arc.txt","rb");
    arc main;
    read_arc(file,&main);
    arc_file file_of_archive;
    file_of_archive.offset_of_file_in_archive= find_offset_of_file(&main,"host.txt");
    read_file(file,&main,&file_of_archive);*/

    FILE* archive;
   // write_archive(archive,argc-1,argv);
    archive= fopen("test_of_write.arc","rb");
    arc main;
    read_arc(archive,&main);
    arc_file file;
    file.offset_of_file_in_archive=main.offset_of_file[0];
    read_file(archive,&main,&file);
    fclose(archive);
    return 0;
}