/*  c语言实现队列的基本操作  */
#include<stdio.h>

//定义存储结构
typedef char ElemType;
typedef struct Node{
   char data;
   struct Node * Next;
}QueueNode;
typedef struct{
   QueueNode * head;
   QueueNode * near;
}Queue;
//初始化队列 空链表队尾指针指向对头
void Init(Queue *Q){
   Q->head=(QueueNode *)malloc(sizeof(QueueNode));
   if(Q->head!=NULL){
      Q->head->Next=NULL;
      Q->near=Q->head;
   }else{
      printf("初始化队列失败\n");
   }
}
//打印队列
void showQueue(Queue *Q){
   if(Q==NULL){
      printf("队列为空\n");
   }else{
      QueueNode *N=Q->head->Next;
      while(N!=NULL){
           printf("%c",N->data);
           N=N->Next;
      }
   }
   printf("\n");
}
//插入链表
void InsertQueue(Queue *Q,ElemType c){
   if(Q->head==NULL){
      Init(Q);
   }
   QueueNode *N=(QueueNode *)malloc(sizeof(QueueNode));
   if(N!=NULL){
      N->data=c;
      N->Next=NULL;
      Q->near->Next=N;
      Q->near=N;
   }else{
      printf("申请空间失败\n");
   }
}
//删除队列
void DeleteQueue(Queue *Q){
   if(Q==NULL||Q->head==Q->near){
       printf("队列为空");
   }else{
       Q->head=Q->head->Next;
   }
}
int main(){
   Queue *Q=(Queue *)malloc(sizeof(Queue));
   if(Q!=NULL){
       Init(Q);
       InsertQueue(Q,'c');
       InsertQueue(Q,'d');
       showQueue(Q);
       DeleteQueue(Q);
       showQueue(Q);
   }else{
       printf("申请空间失败\n");
   }
}
