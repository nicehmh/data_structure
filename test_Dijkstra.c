//Dijkstra求单源最短路径
#include<stdio.h>
#define N 20 //图的顶点最多数
#define MAX 1000
#define MIN -1
typedef int ElemType;//图的顶点标识，这里为自然数
//图的结点结构
typedef struct ArcNode{
  ElemType adjvex;//图的顶点 （该弧指向顶点的位置）
  struct ArcNode *nextarc;//指向下一条弧的指针
  int info//该弧权值
}ArcNode;
//表头结点表
typedef struct VertexNode{
   ElemType data;
   ArcNode *firstarc;
}VertexNode;
//图
typedef struct AdjList{
   VertexNode vertex[N];
   int vexnum;//图的顶点数
   int arcnum;//弧数;
   int kind;//图的种类（kind=1为有向图）
   int dist[N];//图的路径长度
   int path[N];//辅助数组
}AdjList;
//边
typedef struct{
   int i;
   int j;
   int f;
}Side;
//邻接表法创建图
int CreateDAG(AdjList *L){
   int i,j;
   ArcNode *p=NULL;
   //测试用例
   Side S[N];
   S[0].i=1;S[0].j=3;S[0].f=10;
   S[1].i=1;S[1].j=5;S[1].f=30;
   S[2].i=1;S[2].j=6;S[2].f=100;
   S[3].i=2;S[3].j=3;S[3].f=5;
   S[4].i=3;S[4].j=4;S[4].f=50;
   S[5].i=4;S[5].j=6;S[5].f=10;
   S[6].i=5;S[6].j=6;S[6].f=60;
   S[7].i=5;S[7].j=4;S[7].f=20;
   for(i=1;i<7;i++){
      L->vertex[i].data=i;
      L->dist[i]=MAX;//设为最大值，表示不可达
      L->path[i]=MIN;//设为最小值，表示尚未初始化
      //L->vertex[i].indegree=0;
      L->vertex[i].firstarc=NULL;
   }
   L->kind=1;
   L->vexnum=6;
   L->arcnum=8;
   for(i=0;i<8;i++){
        p=(ArcNode *)malloc(sizeof(ArcNode));
        p->adjvex=S[i].j;
        p->info=S[i].f;
        p->nextarc=L->vertex[(S[i].i)].firstarc;
        L->vertex[(S[i].i)].firstarc=p;
        if(S[i].i==1){//初始顶点为1
            L->dist[(S[i].j)]=S[i].f;
            //L->path[(S[i].j)]=S[i].f;
        }
       // L->vertex[(S[i].j)].indegree++;
   }
   return 1;
}
//输出邻接表存储
void PrintALGraph(AdjList *L){
   ArcNode *p=NULL;
   int i,k=0;
   for(i=1;i<=L->vexnum;i++){
      k=L->vertex[i].data;
      printf("V%d",k);
     // printf(" 入度为%d 邻接点有 ",(L->vertex[i].indegree));
      p=L->vertex[k].firstarc;
      while(p!=NULL){
         printf(" ->%d",p->adjvex);
         p=p->nextarc;
      }
      printf("\n");
   }
}
//Dijkstra求单源最短路径
void Dijkstra(AdjList *L){
   int i=1,j,k=0;
   Side s;
   ArcNode *p=NULL;
   while(k<5){
      p=L->vertex[i].firstarc;
      if(p==NULL){
        for(i=2;i<=L->vexnum;i++){
           if(L->path[i]==MIN){
               break;
           }
        }
      }else{
          s.f=MAX;
          while(p!=NULL){
            if(s.f>p->info){
              s.f=p->info;
              s.i=i;
              s.j=p->adjvex;
            }
            p=p->nextarc;
          }
          if(s.f==MAX){
                for(i=2;i<=L->vexnum;i++){
                   if(L->dist[i]==MAX){
                        break;
                   }
                }
          }else if(L->dist[(s.j)]>L->dist[i]+s.f){
               L->dist[(s.j)]=L->dist[i]+s.f;
               L->path[(s.j)]=L->dist[(s.j)];
               i=s.j;
               k++;
          }else{
               L->path[(s.j)]=L->dist[(s.j)];
               i=s.j;
               k++;
          }
       }
   }
   //输出
   printf("输出最短路径:\n");
   for(i=1;i<=L->vexnum;i++){
       if(L->dist[i]==1000||i==1){
         printf("v1到v%d不存在最短路径\n",i);
       }else{
         printf("v1到v%d的最短路径是%d\n",i,L->dist[i]);
       }
       printf("path is %d\n",L->path[i]);
   }
}
int main(){
   AdjList *L=(AdjList *)malloc(sizeof(AdjList));
   if(CreateDAG(L)==1){
        PrintALGraph(L);
        Dijkstra(L);
   }else{
      printf("创建失败\n");
   }
}
