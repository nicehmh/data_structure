#include<stdio.h>
//#define ElemType char
typedef char ElemType;
//定义链表
typedef struct Node{
   ElemType data;
   struct Node * Next;
}Node,*LinkList;
//打印链表
void showLinkList(Node *L){
   Node *p=L->Next;
   while(p!=NULL){
      printf("%c",p->data);
      p=p->Next;
   }
   printf("\n");
}
//头插法创建链表
void createLinkList(Node *L){
   Node *s;
   char c;
   int flag=0;
   while(flag==0){
        c=getchar();
        if(c!='&'){
           s=(Node *)malloc(sizeof(Node));
           s->data=c;
           s->Next=L->Next;
           L->Next=s;
        }else{
           flag=1;
        }
   }
}
//删除链表
int DeleteLinkList(Node *L,int i){
   Node *p=L,*e;
   int j=0;
   if(i<=0){
      return 0;
   }
   while(p!=NULL&&j<i-1){
        p=p->Next;
        j++;
   }
   e->Next=p->Next->Next;
   p->Next=e->Next;
}
//插入链表
void InsertLinkList(Node *L,int i,ElemType data){
    Node *p=L;
    int j=0;
    while(p!=NULL&&j<i-1){
       p=p->Next;
       j++;
    }
    //printf("%d\n",j);
    Node *s=(Node *)malloc(sizeof(Node));
    s->data=data;
    s->Next=p->Next;
    p->Next=s;
}
//按序号查询链表
int queryLinkList(Node *L,int i){
   Node *p=L;
   int j=0;
   if(i<=0){
      return 0;
   }
   while(p!=NULL&&j<i){
      p=p->Next;
      j++;
   }
   printf("%c",p->data);
}
int main(){
  //初始化链表
  Node *L=(Node *)malloc(sizeof(Node));
  L->Next=NULL;
  createLinkList(L);
  showLinkList(L);
  InsertLinkList(L,3,'p');
  showLinkList(L);
  DeleteLinkList(L,3);
  showLinkList(L);
  queryLinkList(L,2);
}
