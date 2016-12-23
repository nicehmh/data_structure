//floyd�����ⶥ�������·��
#include<stdio.h>
#define N 20//��󶥵���
#define INF 10000
typedef struct {
  int vexs[N];//�����
  int adjMatrix[N][N];//�ڽӾ��󣬼��߱�
  int vexnum,arcnum;//�������ͱ���
}MGraph;//ͼ
typedef struct{
  int begin,end;//�߶������
  int cost;//���ϵ�Ȩֵ
}TreeEdge;//���ڱ�����С�������ı߱�����
//��������ͼ���ڽӾ���洢
void CreateMGraph(MGraph *G){
   int i,j,k,x;
   printf("�����붥�����ͱ���������ĸ�ʽΪ�������� ��������\n");
   scanf("%d %d",&(G->vexnum),&(G->arcnum));
   for(i=0;i<G->vexnum;i++)//��ʼ���ڽӾ����Ԫ��
     for(j=0;j<G->arcnum;j++){
        G->adjMatrix[i][j]=INF;
     }
   printf("����%d���ߣ���ʽ�����±� ���±� ���ϵ�Ȩֵ\n",G->arcnum);
   for(k=0;k<G->arcnum;k++){
     scanf("%d %d %d",&i,&j,&x);
        G->adjMatrix[i][j]=x;
   }
}
//���i,j���·�����м���
void shortpath(int path[][N],int i,int j){
   int k=path[i][j];
   if(k){
     shortpath(path,i,k);
     printf("%d,",k);
     shortpath(path,k,j);
   }
}
//���������еĸ��Զ���i��j֮������p[i][j]�����Ȩ·��A[i][j]
void Floyd(MGraph *G){
   int i,j,k;
   int A[N][N],p[N][N];
   for(i=0;i<G->vexnum;i++){//���Զ���֮���ʼ��֪·��������
      for(j=0;j<G->vexnum;j++){
        A[i][j]=G->adjMatrix[i][j];
        p[i][j]=0;
      }
      A[i][i]=0;
   }
   //ͨ��vk����vi��vj�����·��
   for(k=0;k<G->vexnum;k++)//kΪ�𽥼�����м���
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
   printf("�������·����\n");
   for(i=0;i<G->vexnum;i++)
     for(j=0;j<G->vexnum;j++)
      if(A[i][j]==0){
        if(i!=j){
          printf("��%d��%d������·��\n",i,j);
        }
      }else{
          printf("��%d��%d�����·������Ϊ��%d\t·��Ϊ��",i,j,A[i][j]);
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
