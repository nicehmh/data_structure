#include<stdio.h>
#define N 100
typedef int ElemType;
//�����������Ľ��ṹ
typedef struct Node{
   ElemType val;
   struct Node *LChild,*RChild;
}Node;
Node *BitRepTr;
//���ҹؼ���Ϊkey�Ľ�㣬����ָ��ý���ָ��
Node *Search(Node *root,int key){
  Node *p=NULL;
  if(root==NULL){
    return NULL;
  }
  p=root;
  while(p){
    if(p->val==key){
      return p;
    }else if(p->val>key){//��ǰ�ڵ��ֵ����key��ȥ��������������
      p=p->LChild;
    }else{
      p=p->RChild;
    }
  }
  return p;
}
//�ڶ����������в���һ���ؼ���Ϊvalue�Ľ��
int Insert(Node *root,int value){
  Node *p=root,*q=NULL,*par=NULL;
  int mark=0;
  while(p!=NULL&&mark==0){//
      par=p;
      if(p->val==value){
        mark=1;
      }else if(p->val>value){
        p=p->LChild;
      }else if(p->val<value){
        p=p->RChild;
      }
  }
  if(mark==1)  return 0;
  q=(Node *)malloc(sizeof(Node));
  q->val=value;
  q->LChild=q->RChild=NULL;
  if(root==NULL){
     root=q;
  }else if(par->val>q->val){
     par->LChild=q;
  }else{
     par->RChild=q;
  }
  return 1;
}
//�Ӷ�����������ɾ��ֵΪvalue�Ľ�㲢���������������������
int Delete(Node *root,int value){
  Node *s,*p,*q;
  p=Search(root,value);//����value�Ľ��
  if(p==NULL) return 1;//û���ҵ�
  if(!p->RChild){//����������ֻ���ؽ�����������
    q=p;
    p=p->LChild;
    free(p);
  }else if(!p->LChild){//����������ֻ���ؽ�����������
    q=p;
    p=p->RChild;
    free(p);
  }else{//��������������
    q=p;
    s=p->RChild;
    while(s->LChild){//ת�ң�Ȼ�����󵽾�ͷ
      q=s;
      s=s->LChild;
    }
    p->val=s->val;//sָ��ɾ����ǰ��
    if(q!=p){
      q->LChild=s->RChild;
    }else{
      q->LChild=s->LChild;
    }
    free(s);
  }
  return 0;
}
//�����������������
void MidOrder(Node *root){
  if(root!=NULL){
     MidOrder(root->LChild);
     printf("%d ",root->val);
     MidOrder(root->RChild);
  }
}
int main(){
  Node *root,*p;
  int k,i,val,n,num[N];
  printf("���Ƚ�������������\n");
  printf("�����������\n");
  scanf("%d",&n);
  if(n<1){
    return -1;
  }
  root=(Node *)malloc(sizeof(Node));
  printf("������ڵ�Ĺؼ���ֵ���Կո���\n");
  scanf("%d",&num[0]);
  root->val=num[0];
  root->LChild=NULL;
  root->RChild=NULL;
  for(i=1;i<n;i++){
    scanf("%d",&num[i]);
    Insert(root,num[i]);
  }
  printf("�Զ������������е��������������£�\n");
  MidOrder(root);
  printf("\n");
  printf(" 1-----------����\n");
  printf(" 2-----------����\n");
  printf(" 3-----------����\n");
  printf("��ѡ��1-3����");
  scanf("%d",&k);
  switch(k){
    case 1:
      printf("ѡ���˲���\n");
      printf("������Ҫ���ҵ�ֵ��");
      scanf("%d",&val);
      if(Search(root,val)!=NULL){
        printf("�ҵ���\n");
      }else{
        printf("û���ҵ�\n");
      }
     break;
    case 2:
      printf("ѡ���˲���\n");
      printf("������Ҫ�����ֵ��");
      scanf("%d",&val);
      if(Insert(root,val)!=0){
        printf("����ɹ�\n");
        printf("���¶���������������������Ľ�����£�\n");
        MidOrder(root);
        printf("\n");
      }else{
        printf("����ʧ�ܣ�ֵΪ%d�Ľ���Ѵ���\n",val);
      }
     break;
    case 3:
      printf("ѡ����ɾ��\n");
      printf("������Ҫɾ����ֵ��");
      scanf("%d",&val);
      if(Delete(root,val)!=1){
        printf("ɾ���ɹ�\n");
        printf("���¶���������������������Ľ�����£�\n");
        MidOrder(root);
        printf("\n");
      }else{
        printf("ɾ��ʧ�ܣ�ֵΪ%d�Ľ�㲻����\n",val);
      }
     break;
    default:
        printf(" 1-----------����\n");
        printf(" 2-----------����\n");
        printf(" 3-----------����\n");
      break;
  }
}
