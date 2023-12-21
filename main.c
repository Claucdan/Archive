#include <stdlib.h>
#include <stdio.h>
#include "priorety_queue.h"
#include "abc.h"
#include <string.h>
#include "tree_of_haffman.h"
#include "string.h"
#include "arc.h"
#include "decode_arc_file.h"

int main(int argc, char *argv[]){
    FILE* archive;
   // write_archive(archive,argc-1,argv);
    archive= fopen("test_of_write.arc","rb");
    arc main;
    read_arc(archive,&main);
    arc_file file;
    file.offset_of_file_in_archive=main.offset_of_file[0];
    read_file(archive,&main,&file);
    FILE *file_to_wr=fopen("test_of_decode.txt","w");
    decode_arc_file(&file,file_to_wr);
    fclose(file_to_wr);
    fclose(archive);
    return 0;
}