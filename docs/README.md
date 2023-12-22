# Archiver
<div id="badges">
 <img src=https://img.shields.io/badge/CLion-grey?style=for-the-badge&logo=clion&logoColor=white></img>
 <img src=https://img.shields.io/badge/CMake-orange?style=for-the-badge&logo=cmake&logoColor=white></img>
 <img src=https://img.shields.io/badge/Visual%20Studio%20Code-0078d7.svg?style=for-the-badge&logo=visual-studio-code&logoColor=white></img>
 <img src=https://img.shields.io/badge/c-black.svg?style=for-the-badge&logo=c&logoColor=white></img>

</div>



## Some information
***
<div>
This archiver is designed to increase understanding of the programming language.<br> 
This archiver uses Huffman encoding. One of the problems with this archiver is that I encode only one character, which does not compress the file as much as it could if we took 3 characters each.
</div>

***

## Struct of archive

### Header of archive file
***
* **size** - count files in archive (**4 bytes**)
* **name of files** - name of file in archive (**20*size bytes**)
* **offset of files** - offset of files in archive (**4*size bytes**)
<br>
```c
    struct arc{
    int count_of_file;
    char** name_of_file;
    int* offset_of_file;
    };
```

### Header of files in archive
***
* **size of file** - size of file in archive (**-not write in archive-**)
* **offset of file** - offset of file in archive (**-not write in archive-**)
* **size of abc** - size of abc of file (**4 bytes**)
* **key of abc** - all keys in abc of file (**size of abc bytes**)
* **data of abc** - frequency of keys in file (**4*size of abc bytes**)
* **size of encode text** - size of encode text in archive (**4 bytes**)
* **extra bites** - extra bites of encode text (**4 bytes**)
* **encode text** - encode file(**(size of encode) text bytes**)
```c
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
```
## Some extra information
### Some functions of arc.h
***
* <code><b>void read_from_file(string* line,FILE* input);</b></code> - read from file information and put it in string
* <code><b>void creat_map_of_string(map* abc,string* line);</b></code> - creat map of keys and frequency of string
* <code><b>void creat_tree_of_Haffman(map_c* main,map* map_of_abc);</b></code> - creat tree of Haffman
* <code><b>void create_arc_file(FILE* file,arc_file* arcFile);</b></code> - creat archive base on archive
* <code><b>void encode_original_text_to_bits(arc_file* file,map_c* main,string* original_text);</b></code> - encode original text to string of 1/0 using map_c
* <code><b>void creat_mass_of_encode_message(arc_file* file,string* text);</b></code> - compresses a string from 1/0 to a char array
* <code><b>void copy_from_map_of_abc_to_arc_file_abc(arc_file* file,map* map_of_abc);</b></code> - copy map to header of file in archive
* <code><b>void write_arc_file(FILE* output,arc_file* file);</b></code> - write new archive
### Struct of map
***
```c
struct map{
     char *key;
    int *data;
    int max_size;
    int size;
};
```
### Struct of string
***
```c
struct string {
     char* string;
    int size;
};
```
### Function of decoding file
***
```c
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
```