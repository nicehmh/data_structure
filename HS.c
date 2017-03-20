#include<stdio.h>
#define N 13
//哈希函数（除留余数法）
int HS(int key){
  return key%N;
}
//在哈希表中查找key,若找到返回其所在的位置，否则将key插入哈希表或表满则返回-1
int thread(int key,int m,int addr[]){
  int i,j;
  i=HS(i);//计算key的哈希地址
  if(addr[i]==key){//若key在哈希表中则返回所在位置
    return i;
  }
  i--;
  j=(i+1)%m;//线性探测再散列处理冲突
  while(addr[j]!=key&&addr[j]!=0){
     if(j!=i){
       j=(j+1)%m;
     }else{
       return -1;//表满
     }
  }
  if(addr[j]==key) return j;
  if(addr[j]==0){
    addr[j]=key;//若找到空位置则插入
    return j;
  }
}
int main(){
  int i,j,m,n,num[N],addr[N];
  printf("输入元素的个数：");
  scanf("%d",&n);
  printf("输入各元素值，用空格隔开：");
  for(i=0;i<n;i++){
    scanf("%d",&num[i]);
  }
  printf("\n");
  for(i=0;i<N;i++){
    addr[i]=0;
  }
  for(i=0;i<n;i++){
    thread(num[i],N,addr);
  }
  printf("所得哈希表如下所示：\n");
  for(i=0;i<N;i++){
     printf("%5d",i);
  }
  printf("\n");
  for(i=0;i<N;i++){
    if(addr[i]!=0){
      printf("%5d",addr[i]);
    }else{
      printf("%5c",' ');
    }
  }
    printf("\n\n");
    printf("输入要查找或要插入的元素值：");
    scanf("%d",&j);
    m=thread(j,N,addr);
    printf("%d所在的位置是：%d\n",j,m);
}
