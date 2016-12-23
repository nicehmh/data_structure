#include<stdio.h>
#define N 100
typedef int ElemType;
//二叉排序树的结点结构
typedef struct Node{
   ElemType val;
   struct Node *LChild,*RChild;
}Node;
Node *BitRepTr;
//查找关键字为key的结点，返回指向该结点的指针
Node *Search(Node *root,int key){
  Node *p=NULL;
  if(root==NULL){
    return NULL;
  }
  p=root;
  while(p){
    if(p->val==key){
      return p;
    }else if(p->val>key){//当前节点的值大于key则去结点的左子树查找
      p=p->LChild;
    }else{
      p=p->RChild;
    }
  }
  return p;
}
//在二叉排序树中插入一个关键字为value的结点
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
//从二叉排序树中删除值为value的结点并重新连接它的左或右子树
int Delete(Node *root,int value){
  Node *s,*p,*q;
  p=Search(root,value);//查找value的结点
  if(p==NULL) return 1;//没有找到
  if(!p->RChild){//右子树空则只需重接它的左子树
    q=p;
    p=p->LChild;
    free(p);
  }else if(!p->LChild){//左子树空则只需重接它的右子树
    q=p;
    p=p->RChild;
    free(p);
  }else{//左右子树均不空
    q=p;
    s=p->RChild;
    while(s->LChild){//转右，然后向左到尽头
      q=s;
      s=s->LChild;
    }
    p->val=s->val;//s指向被删结点的前驱
    if(q!=p){
      q->LChild=s->RChild;
    }else{
      q->LChild=s->LChild;
    }
    free(s);
  }
  return 0;
}
//中序遍历二叉排序树
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
  printf("首先建立二叉排序树\n");
  printf("请输入结点个数\n");
  scanf("%d",&n);
  if(n<1){
    return -1;
  }
  root=(Node *)malloc(sizeof(Node));
  printf("输入各节点的关键字值，以空格间隔\n");
  scanf("%d",&num[0]);
  root->val=num[0];
  root->LChild=NULL;
  root->RChild=NULL;
  for(i=1;i<n;i++){
    scanf("%d",&num[i]);
    Insert(root,num[i]);
  }
  printf("对二叉排序树进行的中序遍历结果如下：\n");
  MidOrder(root);
  printf("\n");
  printf(" 1-----------查找\n");
  printf(" 2-----------查找\n");
  printf(" 3-----------查找\n");
  printf("请选择（1-3）：");
  scanf("%d",&k);
  switch(k){
    case 1:
      printf("选择了查找\n");
      printf("请输入要查找的值：");
      scanf("%d",&val);
      if(Search(root,val)!=NULL){
        printf("找到了\n");
      }else{
        printf("没有找到\n");
      }
     break;
    case 2:
      printf("选择了插入\n");
      printf("请输入要插入的值：");
      scanf("%d",&val);
      if(Insert(root,val)!=0){
        printf("插入成功\n");
        printf("对新二叉排序树进行中序遍历的结果如下：\n");
        MidOrder(root);
        printf("\n");
      }else{
        printf("插入失败，值为%d的结点已存在\n",val);
      }
     break;
    case 3:
      printf("选择了删除\n");
      printf("请输入要删除的值：");
      scanf("%d",&val);
      if(Delete(root,val)!=1){
        printf("删除成功\n");
        printf("对新二叉排序树进行中序遍历的结果如下：\n");
        MidOrder(root);
        printf("\n");
      }else{
        printf("删除失败，值为%d的结点不存在\n",val);
      }
     break;
    default:
        printf(" 1-----------查找\n");
        printf(" 2-----------查找\n");
        printf(" 3-----------查找\n");
      break;
  }
}
