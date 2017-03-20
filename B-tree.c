//B树查找
#include<stdio.h>
#define M 3//B树阶数
typedef int keyType;//结点数据类型
//B树的结点结构
typedef struct MbtNode{
  struct MbtNode *parent;
  int keynum;
  keyType key[M+1];
  struct MbtNode *ptr[M+1];
}MbtNode,*Mbtree;
//寻找小于或等于关键字k的最大关键字序号
int search(Mbtree mbt,keyType key){
  int n=mbt->keynum;
  int i=1;
  while(i<=n&&mbt->key[i]<=key) i++;
  return (i-1);
}
//打印B树
void PrintBtree(Mbtree mbt){
  int n=mbt->keynum;
  int i=1;
  printf("keynum is %d\n",n);
  printf("树为：");
  while(i<=n){
    if(mbt->key[i]){
     printf("%d ",mbt->key[i]);
    }
     i++;
  }
}
//B树的分裂过程
void spilt(Mbtree oldp,Mbtree *newp){
  int i,s,n;
  s=ceil((float)M/2);
  n=M-s;
  *newp=(Mbtree)malloc(sizeof(MbtNode));
  (*newp)->keynum=n;
  (*newp)->parent=oldp->parent;
  (*newp)->ptr[0]=oldp->ptr[s];
  for(i=1;i<=n;i++){
    (*newp)->key[i]=oldp->key[s+i];
    (*newp)->ptr[i]=oldp->ptr[s+i];
  }
  oldp->keynum=s-1;
}
//在根为mbt的B树中查找关键字k,查找成功则将所在结点地址放入np，将结点内位置序号放入pos,
//否则，将k应被插入的结点地址放入np,将结点内应插入的位置序号放入pos
int search_mbtree(Mbtree mbt,keyType k,Mbtree *np,int *pos){
   Mbtree p=mbt,fp=NULL;
   int found=0,i=0;
   while(p!=NULL&&found==0){
     i=search(p,k);
     if(i>0&&p->key[i]==k){
       found=1;
     }else{
       fp=p;
       p=p->ptr[i];
     }
   }
   if(found==1){
     *np=p;
     *pos=i;
     return 1;
   }else{
     *np=fp;
     *pos=i;
     return 0;
   }
}
//初始化B树根
void InitMbtree(Mbtree *mbt,int k){
  (*mbt)->keynum=1;
  (*mbt)->parent=NULL;
  (*mbt)->key[1]=k;
  (*mbt)->ptr[0]=NULL;
  (*mbt)->ptr[1]=NULL;
}

//在mbt->key[ipos+1]处插入key,在mbt->ptr[ipos+1]处插上rp
void Insert(Mbtree mbp,int ipos,keyType key,Mbtree rp)
{
  int j;
  for(j=mbp->keynum;j>=ipos+1;j--){
    mbp->key[j+1]=mbp->key[j];
    mbp->ptr[j+1]=mbp->ptr[j];
  }
  mbp->key[ipos+1]=key;
  mbp->ptr[ipos+1]=rp;
  mbp->keynum++;
  printf("keynum is %d\n",mbp->keynum);
}
//B树的插入
//在M阶B树t中插入k:如果mbt=NULL,则生成初始根；
//否则q指向某个最小非终端结点,k应插入该节点中q->key[i+1]处，
//插入后如果q->keynum>m-1,则进行分裂处理
void insert_mbtree(Mbtree mbt,keyType k,Mbtree q,int i){
  Mbtree q1,ap,new_root;
  int s;
  keyType x;
  int finish;
  if(mbt==NULL){
    mbt=(MbtNode *)malloc(sizeof(MbtNode));
    InitMbtree(mbt,k);
  }else{
    x=k;ap=NULL;finish=0;
    while(q!=NULL&&finish==0){
       Insert(q,i,x,ap);
       if(q->keynum<M){
          finish=1;
       }else{
          s=ceil((float)M/2);
          spilt(q,&q1);
          x=q->key[s];
          ap=q1;
          q=q->parent;
          if(q!=NULL){
            i=search(q,x);
          }
       }
    }
    if(finish==0){//产生新根
      new_root=(Mbtree)malloc(sizeof(MbtNode));
      new_root->keynum=1;
      new_root->parent=NULL;
      new_root->key[1]=x;
      new_root->ptr[0]=mbt;
      new_root->ptr[1]=ap;
      mbt=new_root;
    }
  }
}
//创建B树
void CreateBtree(){
   Mbtree mbt=(MbtNode *)malloc(sizeof(MbtNode)),q=NULL;
   int n=0,i=0;
   while(n!=-1){
     printf("Input k:");
     scanf("%d",&n);
     insert_mbtree(mbt,n,q,i);
     i++;
   }
   PrintBtree(mbt);
}
int main(){
   CreateBtree();
}
