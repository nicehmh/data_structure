//线索二叉树及遍历
#include<stdio.h>

typedef char Elemtype;

typedef struct Node{
    Elemtype data;
    struct Node *LChild,*RChild;
    int LTag,RTag;
}BiThrNode,*BiThrTree;
BiThrNode *pre=NULL;
//创建未线索化的二叉树
BiThrNode *CreateBiThrNode(char *str){
   char ch;int top=-1,k,j=0;
   BiThrNode *bt=NULL,*stack[200],*p=NULL;
   ch=str[j];
   while(ch!='\0'){
        switch(ch){
          case '(':
              top++;
              stack[top]=p;
              k=1;
              break;
          case ',':
              k=2;
              break;
          case ')':
              top--;
              break;
          default:
             p=(BiThrNode *)malloc(sizeof(BiThrNode));
             p->data=ch;
             p->LChild=p->RChild=NULL;
             if(bt==NULL){
                bt=p;
             }else{
               if(k==1){
                 stack[top]->LChild=p;
               }else{
                 stack[top]->RChild=p;
               }
             }
              break;
        }
        j++;ch=str[j];
   }
   return bt;
}
//前序遍历未线索化的二叉树
void Preorder(BiThrNode *bt){
   if(bt!=NULL){
      printf("%c",bt->data);
      Preorder(bt->LChild);
      Preorder(bt->RChild);
   }
}
//建立中序线索树
void InThreading(BiThrNode *bt){
    if(bt!=NULL){
        InThreading(bt->LChild);
        if(bt->LChild==NULL){
           bt->LTag=1;
           bt->LChild=pre;
        }else{
           bt->LTag=0;
        }
        if(bt->RChild==NULL){
           bt->RTag=1;
        }else{
           bt->RTag=0;
        }
        if(pre!=NULL&&pre->RChild==NULL){
            pre->RChild=bt;
            pre->RTag=1;
        }else{
            bt->RTag=0;
        }
        pre=bt;

        InThreading(bt->RChild);
    }
}
//中序遍历二叉线索树
void InOrderTrave(BiThrNode *bt){
   BiThrNode *p=bt->LChild;
   while(p!=bt){
       while(p->LTag==0){
          p=p->LChild;
       }
       printf("%c",p->data);
       while(p->RTag==1&&p->RChild!=bt){
           p=p->RChild;
            printf("%c",p->data);
       }
       p=p->RChild;
   }
}
int main(){
  BiThrNode *bt=NULL;
  char *str="a(b(c,d(e,f)),i(j,k(x,y)))";
  bt=CreateBiThrNode(str);
  pre=bt;
  Preorder(bt);
  printf("\n");
  InThreading(bt);
  InOrderTrave(bt);
}
