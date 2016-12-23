//floyd求任意顶点间的最短路径
#include<stdio.h>
#define N 20//最大顶点数
#define INF 10000
typedef struct {
  int vexs[N];//顶点表
  int adjMatrix[N][N];//邻接矩阵，即边表
  int vexnum,arcnum;//顶点数和边数
}MGraph;//图
typedef struct{
  int begin,end;//边顶点序号
  int cost;//边上的权值
}TreeEdge;//用于保存最小生成树的边表类型
//创建有向图的邻接矩阵存储
void CreateMGraph(MGraph *G){
   int i,j,k,x;
   printf("请输入顶点数和边数（输入的格式为：顶点数 边数）；\n");
   scanf("%d %d",&(G->vexnum),&(G->arcnum));
   for(i=0;i<G->vexnum;i++)//初始化邻接矩阵的元素
     for(j=0;j<G->arcnum;j++){
        G->adjMatrix[i][j]=INF;
     }
   printf("输入%d条边，格式：行下标 列下标 边上的权值\n",G->arcnum);
   for(k=0;k<G->arcnum;k++){
     scanf("%d %d %d",&i,&j,&x);
        G->adjMatrix[i][j]=x;
   }
}
//输出i,j最短路径的中间结点
void shortpath(int path[][N],int i,int j){
   int k=path[i][j];
   if(k){
     shortpath(path,i,k);
     printf("%d,",k);
     shortpath(path,k,j);
   }
}
//求有向网中的各对顶点i和j之间的最短p[i][j]及其带权路径A[i][j]
void Floyd(MGraph *G){
   int i,j,k;
   int A[N][N],p[N][N];
   for(i=0;i<G->vexnum;i++){//各对顶点之间初始已知路径及距离
      for(j=0;j<G->vexnum;j++){
        A[i][j]=G->adjMatrix[i][j];
        p[i][j]=0;
      }
      A[i][i]=0;
   }
   //通过vk修正vi到vj的最短路径
   for(k=0;k<G->vexnum;k++)//k为逐渐加入的中间结点
     for(i=0;i<G->vexnum;i++){
        if(A[i][k]<INF){
           for(j=0;j<G->vexnum;j++){
              if(A[i][k]+A[k][j]<A[i][j]){
                   A[i][j]=A[i][k]+A[k][j];
                   p[i][j]=k;
              }
           }
        }
     }
   printf("输入最短路径：\n");
   for(i=0;i<G->vexnum;i++)
     for(j=0;j<G->vexnum;j++)
      if(A[i][j]==0){
        if(i!=j){
          printf("从%d到%d不存在路径\n",i,j);
        }
      }else{
          printf("从%d到%d的最短路径长度为：%d\t路径为：",i,j,A[i][j]);
          printf("%d,",i);
          shortpath(p,i,j);
          printf("%d\n",j);
      }
}
int main(){
   MGraph *G=(MGraph *)malloc(sizeof(MGraph));
   CreateMGraph(G);
   Floyd(G);
}
