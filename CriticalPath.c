#include<stdio.h>
#define N 20
typedef int ElemType;
/* ����ͼ���ڽӱ��ʾ��*/
//�߱���
typedef struct {
   int info;
   ElemType adjvex;
   struct ArcNode *nextarc;
}ArcNode;
//��ͷ���
typedef struct{
   ElemType data;
   int indegree;
   ArcNode *firstarc;
}VertexNode;
//ͼ
typedef struct{
   VertexNode vertex[N];
   int kind;//kind=1Ϊ����ͼ
   int vexnum,arcnum;//ͼ�Ķ������ͻ���
}AdjList;
//��
typedef struct{
   int i;
   int j;
   int f;
}Side;
//��������ͼ
int CreateDAG(AdjList *L){
   int i,j;
   ArcNode *p=NULL;
   //��������
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
//����ڽӱ�洢
void PrintALGraph(AdjList *L){
   ArcNode *p=NULL;
   int i,k=0;
   for(i=1;i<=L->vexnum;i++){
      k=L->vertex[i].data;
      printf("V%d",k);
      printf(" ���Ϊ%d �ڽӵ��� ",(L->vertex[i].indegree));
      p=L->vertex[k].firstarc;
      while(p!=NULL){
         printf(" %d",p->adjvex);
         p=p->nextarc;
      }
      printf("\n");
   }
}
//��������
int TopoSort(AdjList *L,int S[],int ve[]){
     int i,j,m=0,Stack[N],num=0,k;
     ArcNode *p=NULL;
     for(i=1;i<=L->vexnum;i++){
        if(L->vertex[i].indegree==0){
           Stack[num]=i;num++;
        }
        ve[i]=0;//��ʼ�������¼������緢��ʱ��
     }
       // printf("�������� ");
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
//�ؼ�·��
int CriticalPath(AdjList *L){
   int i,j,k,e,l,tag,dut,v[N],ve[N],T[N];
   ArcNode *p=NULL;
   if(TopoSort(L,T,ve)){
      printf("���д��ڻ�\n");
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
      printf("����������'*'��ʾ�ؼ����\n");
      for(j=1;j<=L->vexnum;++j)
        for(p=L->vertex[j].firstarc;p;p=p->nextarc){
          k=p->adjvex;
          dut=p->info;
          e=ve[j];l=v[k]-dut;
          if(e==1){
             printf("v%d,v%d,�������ʱ��%d,���緢��ʱ��%d,��ٷ���ʱ��%d,tag* \n",j,k,dut,e,l,tag);
          }else{
             printf("v%d,v%d,�������ʱ��%d,���緢��ʱ��%d,��ٷ���ʱ��%d,tag  \n",j,k,dut,e,l,tag);
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
      printf("����ʧ��\n");
   }
}
