//
// Created by dania on 08.12.2023.
//

#ifndef TEST_C_TREE_OF_HAFFMAN_H
#define TEST_C_TREE_OF_HAFFMAN_H





void create_revarse_map(map_c* main,Node* root,char* data){
    if(root->sym!='\0') {
        add(main,&root->sym,data);
        return;
    }
    char* str1,*str2;
    str1=(char*) malloc(strlen(data)+1);
    strcpy(str1,data);
    strcat(str1,"1");
    str2=(char*) malloc(strlen(data)+1);
    strcpy(str2,data);
    strcat(str2,"0");
    create_revarse_map(main,root->left,str1);
    create_revarse_map(main,root->right,str2);
}



#endif //TEST_C_TREE_OF_HAFFMAN_H
