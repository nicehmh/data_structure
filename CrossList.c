/*  */
#include<stdio.h>
/*  ʮ������Ľṹ����
*/
typedef int ElemType;
typedef struct OLNode{
  int row,col;
  ElemType value;
  struct OLNode *right,*down;
}OLNode,*OLink;

typedef struct{
   OLink *row_head,*col_head;
   int m,n,len;
}CrossList;
/*������Ԫϡ�����
  1������ϡ�������С��С�����Ԫ�صĸ���
  2����̬�����С��������ͷָ������
  3������������Ԫ�أ��ֱ����������������
*/
int CreateCrossList(CrossList *s){
   int k,m,n,t,i,j;
   ElemType e;
   OLNode *p=NULL,*q=NULL;
   printf("Input m,n,t of CrossList:\n");
   scanf("%d %d %d",&m,&n,&t);
   s->m=m;s->n=n;s->len=t;
   s->row_head=(OLNode *)malloc((m+1)*sizeof(OLNode));
   if(s->row_head==NULL){
      printf("��ͷָ�봴��ʧ��\n");
   }
   s->col_head=(OLNode *)malloc((n+1)*sizeof(OLNode));

   if(s->col_head==NULL){
      printf("��ͷָ�봴��ʧ��\n");
   }
   for(i=1;i<=s->m;i++){
      s->row_head[i]=NULL;
   }
   for(i=1;i<=s->n;i++){
     s->col_head[i]=NULL;
   }

  for(i=1;i<=t;i++){
      scanf(" %d %d %d",&k,&j,&e);
    if(!(p=(OLNode *)malloc(sizeof(OLNode)))){
       printf("�ڴ治��");
    }
    p->row=k;p->col=j;p->value=e;
    p->right=NULL;p->down=NULL;
    if(s->row_head[k]==NULL){
        s->row_head[k]=p;
    }else{
        for(q=s->row_head[k];q->right&&q->right->col<j;q=q->right);
        //p->right=q->right;
        q->right=p;
    }
    if(s->col_head[j]==NULL){
       s->col_head[j]=p;
    }else{
        for(q=s->col_head[j];q->down&&q->down->row<k;q=q->down);
        //p->down=q->down;
        q->down=p;
    }

   }
   return 0;
}
//��ӡʮ������
int showCrossList(CrossList *s){
   int i;
   OLNode *p=NULL;
   for(i=1;i<=s->m;i++){
       p=s->row_head[i];
       while(p!=NULL){
            printf("%d ",p->value);
            p=p->right;
       }
       printf("\n");
   }
}
/*�������
  ��q��ָ�����ÿһ�У����ж���Ӧ��L��ָ�����Ƿ���ֵ�������У����
*/
int multiCrossList(CrossList *s,CrossList *p){
    OLNode *q=NULL,*L=NULL;
    int i,num;
    if(s->n==p->m){
       for(i=1;i<=s->m;i++){
          q=s->row_head[i];
          while(q!=NULL){
             num=0;
             L=p->row_head[q->col];
             if(L==NULL){
               num+=0;
             }else{
               if(p->col_head[q->row]==NULL){
                  num+=0;
               }else{
                   for(;L->right&&L->right==p->col_head[q->row];L=L->right);
                   if(L==NULL){
                       num+=0;
                   }else{
                       num=num+L->value*q->value;
                   }
               }
             }
             q->value+=num;
             q=q->right;
          }
       }
    }else{
      printf("�����޷����");
    }
}
int main(){
     CrossList *s=(CrossList *)malloc(sizeof(CrossList));
     CrossList *p=(CrossList *)malloc(sizeof(CrossList));
     CreateCrossList(s);
     CreateCrossList(p);
     multiCrossList(s,p);
     showCrossList(s);
}
