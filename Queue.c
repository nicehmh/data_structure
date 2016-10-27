/*  c����ʵ�ֶ��еĻ�������  */
#include<stdio.h>

//����洢�ṹ
typedef char ElemType;
typedef struct Node{
   char data;
   struct Node * Next;
}QueueNode;
typedef struct{
   QueueNode * head;
   QueueNode * near;
}Queue;
//��ʼ������ �������βָ��ָ���ͷ
void Init(Queue *Q){
   Q->head=(QueueNode *)malloc(sizeof(QueueNode));
   if(Q->head!=NULL){
      Q->head->Next=NULL;
      Q->near=Q->head;
   }else{
      printf("��ʼ������ʧ��\n");
   }
}
//��ӡ����
void showQueue(Queue *Q){
   if(Q==NULL){
      printf("����Ϊ��\n");
   }else{
      QueueNode *N=Q->head->Next;
      while(N!=NULL){
           printf("%c",N->data);
           N=N->Next;
      }
   }
   printf("\n");
}
//��������
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
      printf("����ռ�ʧ��\n");
   }
}
//ɾ������
void DeleteQueue(Queue *Q){
   if(Q==NULL||Q->head==Q->near){
       printf("����Ϊ��");
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
       printf("����ռ�ʧ��\n");
   }
}
