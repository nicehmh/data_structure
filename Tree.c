#include<stdio.h>
//二叉树的创建和遍历
typedef char Elemtype;
typedef struct Node{
   Elemtype data;
   struct Node * LChild;
   struct Node * RChild;
}BiTNode,*BiTree;
BiTNode *CreateBiTNode(char *str){
   char ch;int top=-1,k,j=0;
   BiTNode *bt=NULL,*stack[200],*p=NULL;
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
             p=(BiTNode *)malloc(sizeof(BiTNode));
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
//前序遍历
void Preorder(BiTNode *bt){
   if(bt!=NULL){
      printf("%c",bt->data);
      Preorder(bt->LChild);
      Preorder(bt->RChild);
   }
}
int main(){
  BiTNode *bt=NULL;
  char *str="a(b(c,d(e,f)),i(j,k(x,y)))";
  bt=CreateBiTNode(str);
  Preorder(bt);
}
