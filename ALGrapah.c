/*图的邻接表表示法和遍历算法的实现 */
#include<stdio.h>
#define N 20   //最多顶点的个数
#define M 7    //
typedef char ElemType;
//边表结点
typedef struct ArcNode{
   int adjvex;  //该弧指向定点的位置
   struct ArcNode *nextarc; //指向下一弧的指针
   //OtherInfo info;//与该弧相关的信息如权值
}ArcNode;
//表头结点
typedef struct VertexNode{
   ElemType data;//顶点数据
   ArcNode *firstarc;//指向该顶点第一条弧的指针
}VertexNode;
//表头结点表
typedef struct{
   VertexNode vertex[N];
   int vexnum,arcnum;//图的顶点数和弧数
   int kind;//图的种类标志 0表示无向图
}AdjList;
//存储边信息
typedef struct{
   int i;
   int j;
}Side;
//定义队列
typedef struct{
   int Q[M];
   int front;
   int rear;
}Queue;
//初始化队列
void InitQueue(Queue *Q){
   Q->front=Q->rear=0;
}
//入队
void EnterQueue(Queue *Q,int n){
   if((Q->rear+1)%M==Q->front){
        printf("入队出错\n");
   }else{
        Q->Q[Q->rear]=n;
        Q->rear=(Q->rear+1)%M;
   }
}
//判断队列是否为空
int EmptyQueue(Queue *Q){
   if(Q==NULL||Q->front==Q->rear){
       return 0;
   }
   return 1;
}
//出队
int DeleteQueue(Queue *Q){
   int g;
   if(Q->rear==Q->front){
      printf("队列为空");
      return 0;
   }
   g=Q->Q[Q->front];
   Q->front=(Q->front+1)%M;
   return g;
}
//图的存储
void CreateALGrapah(AdjList *L,int A[],Side S[],int m){
   int i=0,k,j=0;
   ArcNode *s=NULL;
   do{
        L->vertex[i].data=A[i];
        L->vertex[i].firstarc=NULL;
        i++;
   }while(A[i]!=-1);
   L->arcnum=m;
   L->vexnum=i-1;
   L->kind=0;
   for(k=0;k<m;k++){
       //头插法建边表
       i=S[k].i;
       j=S[k].j;
    // printf("%d-%d\n",i,j);
     s=(ArcNode *)malloc(sizeof(ArcNode));
     s->adjvex=j;
     s->nextarc=L->vertex[i].firstarc;
     L->vertex[i].firstarc=s;
     s=(ArcNode *)malloc(sizeof(ArcNode));
     s->adjvex=i;
     s->nextarc=L->vertex[j].firstarc;
     L->vertex[j].firstarc=s;
   }
}
//输出邻接表存储
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
//深度优先搜索
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
//广度优先搜索
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
int main(){
   AdjList *L=(AdjList *)malloc(sizeof(AdjList));
   int i,V[M];
   //测试数据
   int A[8]={0,1,2,3,4,5,6,-1};//图的顶点信息 0为开始位 -1为结束位
   Side S[9];
   S[0].i=1;S[0].j=2;
   S[1].i=1;S[1].j=3;
   S[2].i=1;S[2].j=5;
   S[3].i=1;S[3].j=6;
   S[4].i=2;S[4].j=3;
   S[5].i=3;S[5].j=4;
   S[6].i=3;S[6].j=5;
   S[7].i=4;S[7].j=5;
   S[8].i=5;S[8].j=6;
  // printf("s1.j=%d\n",S[1].j);
   CreateALGrapah(L,A,S,9);
   PrintALGraph(L);
   //深度优先搜索  V[]为访问记录是否被访问（0为访问）
   printf("深度优先搜索\n");
   for(i=1;i<M;i++){
     V[i]=0;
   }
   DepthFirstSearch(L,V,1);
   printf("\n广度优先搜索\n");
    for(i=1;i<M;i++){
     V[i]=0;
   }
   BreadthFirstSearch(L,V,1);
}
