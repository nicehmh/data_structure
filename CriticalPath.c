#include<stdio.h>
#define N 20
typedef int ElemType;
/* 有向图的邻接表表示法*/
//边表结点
typedef struct {
   int info;
   ElemType adjvex;
   struct ArcNode *nextarc;
}ArcNode;
//表头结点
typedef struct{
   ElemType data;
   int indegree;
   ArcNode *firstarc;
}VertexNode;
//图
typedef struct{
   VertexNode vertex[N];
   int kind;//kind=1为有向图
   int vexnum,arcnum;//图的顶点数和弧数
}AdjList;
//边
typedef struct{
   int i;
   int j;
   int f;
}Side;
//创建有向图
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
      L->vertex[i].indegree=0;
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
        L->vertex[(S[i].j)].indegree++;
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
      printf(" 入度为%d 邻接点有 ",(L->vertex[i].indegree));
      p=L->vertex[k].firstarc;
      while(p!=NULL){
         printf(" %d",p->adjvex);
         p=p->nextarc;
      }
      printf("\n");
   }
}
//拓扑排序
int TopoSort(AdjList *L,int S[],int ve[]){
     int i,j,m=0,Stack[N],num=0,k;
     ArcNode *p=NULL;
     for(i=1;i<=L->vexnum;i++){
        if(L->vertex[i].indegree==0){
           Stack[num]=i;num++;
        }
        ve[i]=0;//初始化定点事件的最早发生时间
     }
       // printf("拓扑排序 ");
        while(num!=0){
             k=Stack[num-1];num--;S[m]=k;m++;
             //printf("v%d ",L->vertex[i].data);
            // m++;
             p=L->vertex[k].firstarc;
             while(p!=NULL){
                i=p->adjvex;
                L->vertex[i].indegree--;
                if(L->vertex[i].indegree==0){
                  Stack[num]=i;
                  num++;
                }
                if(ve[k]+p->info>ve[i]){
                    ve[i]=ve[k]+p->info;
                }
                p=p->nextarc;
             }
        }
        if(m!=L->vexnum){
            return 1;
        }
        return 0;
        //printf("\n");
}
//关键路径
int CriticalPath(AdjList *L){
   int i,j,k,e,l,tag,dut,v[N],ve[N],T[N];
   ArcNode *p=NULL;
   if(TopoSort(L,T,ve)){
      printf("网中存在环\n");
      return 0;
   }
   for(i=1;i<=L->vexnum;i++){
     v[i]=ve[L->vexnum-1];
   }
   for(i=L->vexnum;i>=1;i--){
      j=T[i];
      p=L->vertex[j].firstarc;
      while(p!=NULL){
        k=p->adjvex;
        dut=p->info;
        if(v[k]-dut<v[j]){
           v[j]=v[k]-dut;
        }
        p=p->nextarc;
      }
      printf("各活动的情况（'*'表示关键活动）\n");
      for(j=1;j<=L->vexnum;++j)
        for(p=L->vertex[j].firstarc;p;p=p->nextarc){
          k=p->adjvex;
          dut=p->info;
          e=ve[j];l=v[k]-dut;
          if(e==1){
             printf("v%d,v%d,活动持续的时间%d,最早发生时间%d,最迟发生时间%d,tag* \n",j,k,dut,e,l,tag);
          }else{
             printf("v%d,v%d,活动持续的时间%d,最早发生时间%d,最迟发生时间%d,tag  \n",j,k,dut,e,l,tag);
          }
        }
        return 1;
   }
}
int main(){
   AdjList *L=(AdjList *)malloc(sizeof(AdjList));
   if(CreateDAG(L)==1){
        PrintALGraph(L);
        CriticalPath(L);
        //TopoSort(L);
   }else{
      printf("创建失败\n");
   }
}
