/*ͼ���ڽӱ��ʾ���ͱ����㷨��ʵ�� */
#include<stdio.h>
#define N 20   //��ඥ��ĸ���
#define M 7    //

typedef char ElemType;
//�߱���
typedef struct ArcNode{
   int adjvex;  //�û�ָ�򶨵��λ��
   struct ArcNode *nextarc; //ָ����һ����ָ��
   int info;//Ȩֵ
}ArcNode;
//��ͷ���
typedef struct VertexNode{
   ElemType data;//��������
   ArcNode *firstarc;//ָ��ö����һ������ָ��
}VertexNode;
//��ͷ����
typedef struct{
   VertexNode vertex[N];
   int vexnum,arcnum;//ͼ�Ķ������ͻ���
   int kind;//ͼ�������־ 0��ʾ����ͼ
}AdjList;
//�洢����Ϣ
typedef struct{
   int i;
   int j;
   int f;
}Side;
//�������
typedef struct{
   int Q[M];
   int front;
   int rear;
}Queue;
//��ʼ������
void InitQueue(Queue *Q){
   Q->front=Q->rear=0;
}
//���
void EnterQueue(Queue *Q,int n){
   if((Q->rear+1)%M==Q->front){
        printf("��ӳ���\n");
   }else{
        Q->Q[Q->rear]=n;
        Q->rear=(Q->rear+1)%M;
   }
}
//�ж϶����Ƿ�Ϊ��
int EmptyQueue(Queue *Q){
   if(Q==NULL||Q->front==Q->rear){
       return 0;
   }
   return 1;
}
//����
int DeleteQueue(Queue *Q){
   int g;
   if(Q->rear==Q->front){
      printf("����Ϊ��");
      return 0;
   }
   g=Q->Q[Q->front];
   Q->front=(Q->front+1)%M;
   return g;
}

//ͼ�Ĵ洢
void CreateALGrapah(AdjList *L,int A[],Side S[],int m){
   int i=0,k,j=0,f=0;
   ArcNode *s=NULL;
   do{
        L->vertex[i].data=A[i];
        L->vertex[i].firstarc=NULL;
       // printf("%d",A[i]);
        i++;
   }while(A[i]!=-1);
   L->arcnum=m;
   L->vexnum=i-1;
   L->kind=0;
   for(k=0;k<m;k++){
       //ͷ�巨���߱�
       i=S[k].i;
       j=S[k].j;
       f=S[k].f;
     //printf("\n%d-%d",i,j);
     s=(ArcNode *)malloc(sizeof(ArcNode));
     s->adjvex=j;
     s->info=f;
     s->nextarc=L->vertex[i].firstarc;
     L->vertex[i].firstarc=s;
     s=(ArcNode *)malloc(sizeof(ArcNode));
     s->adjvex=i;
     s->nextarc=L->vertex[j].firstarc;
     s->info=f;
     L->vertex[j].firstarc=s;
   }
}
//����ڽӱ�洢
void PrintALGraph(AdjList *L){
   ArcNode *p=NULL;
   int i,k=0;
   for(i=1;i<=L->vexnum;i++){
      k=L->vertex[i].data;
      printf("V%d",k);
      p=L->vertex[k].firstarc;
      while(p!=NULL){
         printf(" ->%d",p->adjvex);
         p=p->nextarc;
      }
      printf("\n");
   }
}
//�����������
void DepthFirstSearch(AdjList *L,int V[],int n){
  printf("V%d ",n);
  V[n]=1;
  ArcNode *p=L->vertex[n].firstarc;
  while(p!=NULL){
    if(V[p->adjvex]==0){
       DepthFirstSearch(L,V,p->adjvex);
    }
     p=p->nextarc;
  }
}
//�����������
void BreadthFirstSearch(AdjList *L,int V[],int n){
  int k;
  ArcNode *p;
  printf("V%d ",n);
  V[n]=1;
  Queue *Q=(Queue *)malloc(sizeof(Queue));
  InitQueue(Q);
  EnterQueue(Q,n);
  while(EmptyQueue(Q)==1){
     n=DeleteQueue(Q);
     if(n==0){
       return 0;
     }
     p=L->vertex[n].firstarc;
     k=p->adjvex;
     while(k>0){
        if(V[k]==0){
           printf("V%d ",k);
           V[k]=1;
           EnterQueue(Q,k);
        }
        p=p->nextarc;
        if(p!=NULL){
           k=p->adjvex;
        }else{
           k=0;
        }
     }
  }
}
//����ķ�㷨����С������
int MiniTree_prim(AdjList *L,int V[],int n){
  int k,B[N],l=-1,i;
  Side e;
  ArcNode *p;
  V[n]=1;
  l++;B[l]=n;//
  while(l<M-1){
     e.f=100;
     e.j=0;
     e.i=0;
    for(i=0;i<=l;i++){
     n=B[i];
     if(n==0){
       return 0;
     }
     p=L->vertex[n].firstarc;
     k=p->adjvex;
     while(k>0){
        if(V[k]==0){
            if(p->info<e.f){
                e.f=p->info;
                e.i=n;
                e.j=k;
            }
        }

        p=p->nextarc;
        if(p!=NULL){
           k=p->adjvex;
        }else{
           k=0;
        }
     }
    }
     if(e.j>0){
        V[e.j]=1;
        printf("%d %d %d\n",e.i,e.j,e.f);
        l++;
        B[l]=e.j;
     }else{
        return 0;
     }
  }
}
/*  ��ʱ��������
//�Ա�����
void sortSide(Side S[],int A[]){
  int i,j,m;
  for(i=0;i<10;i++){
     m=1;
     for(j=0;j<10;j++){
        if(S[j].f<S[i].f){
           m++;
        }
     }
     A[m]=i;
  }
}
//��³˹�����㷨����С������
void minitree_kruskal(Adjvex *L,int V[],Side S[],int n){
   int m,A[N];
   ArcNode *p=L->vertex[n].firstarc;
   sortSide(S,A);

}
*/
int main(){
   AdjList *L=(AdjList *)malloc(sizeof(AdjList));
   int i=0,V[M];
   //��������
   Side S[9];
   S[0].i=1;S[0].j=2;S[0].f=6;
   S[1].i=1;S[1].j=3;S[1].f=1;
   S[2].i=1;S[2].j=4;S[2].f=5;
   S[3].i=2;S[3].j=3;S[3].f=5;
   S[4].i=2;S[4].j=5;S[4].f=3;
   S[5].i=3;S[5].j=4;S[5].f=5;
   S[6].i=3;S[6].j=5;S[6].f=6;
   S[7].i=3;S[7].j=6;S[7].f=4;
   S[8].i=4;S[8].j=6;S[8].f=2;
   S[9].i=5;S[9].j=6;S[9].f=6;
   int A[8]={0,1,2,3,4,5,6,-1};//ͼ�Ķ�����Ϣ 0Ϊ��ʼλ -1Ϊ����
  // printf("s1.j=%d\n",S[1].j);
   CreateALGrapah(L,A,S,10);
   PrintALGraph(L);
   //�����������  V[]Ϊ���ʼ�¼�Ƿ񱻷��ʣ�0Ϊ���ʣ�
   printf("�����������\n");
   for(i=1;i<M;i++){
     V[i]=0;
   }
   DepthFirstSearch(L,V,1);
   printf("\n�����������\n");
    for(i=1;i<M;i++){
     V[i]=0;
   }
   BreadthFirstSearch(L,V,1);
   //
   printf("\n����ķ�㷨����С������\n");
   for(i=1;i<M;i++){
     V[i]=0;
   }
   MiniTree_prim(L,V,1);
}
