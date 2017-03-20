#include<stdio.h>
#define N 100
//希尔排序
typedef int KeyType;
typedef struct{
  KeyType key;
  //OtherType other_data;
}RecordType;
//对记录数组r坐一趟希尔排序，length为数组长度，delta为增量
void ShellInsert(RecordType r[],int length,int delta){
    int i,j;
    RecordType t;
   // printf("%d\n",length);
  for(i=delta;i<=length;i++){
    if(r[i].key<r[i-delta].key){
      t=r[i];
      for(j=i-delta;j>=0&&t.key<r[j].key;j-=delta){
         r[j+delta]=r[j];
      }
      r[j+delta]=t;
    }
  }
}
//对记录数组r做希尔排序，length为数组r的长度，delta为增量数组，n为delta[]的长度
void ShellSort(RecordType r[],int length,int delta[],int n){
    int i;
  for(i=0;i<=n-1;++i){
   //   printf("i=%d\n",i);
    ShellInsert(r,length,delta[i]);
  }
}
//取增量函数.d=n/2向上取整,返回数组长度
int GetDelta(int delta[],int length){
  int i=1;
  if(length<2){
    return 0;
  }
  delta[0]=(length+1)/2;
  while(delta[i-1]!=1){
    delta[i]=(delta[i-1]+1)/2;
    i++;
  }
  return i;
}
//打印数组
void PrintArr(RecordType r[],int length){
  int i;
  for(i=0;i<=length;i++){
    printf("%d ",r[i].key);
  }
  printf("\n");
}
int main(){
  RecordType r[N];
  int i=-1,delta[N],k=0;
  printf("请输入测试用例：\n");
  do{
    i++;
    scanf("%d",&r[i].key);
  }while(r[i].key!=-10000);
 // PrintArr(r,i-1);
  k=GetDelta(delta,i);
 // PrintArr(delta,k-1);
  //return 1;

  if(k==0){
    printf("%d",r[0].key);
  }else{
     // printf("k=%d\n",k);
     ShellSort(r,i-1,delta,k);
     PrintArr(r,i-1);
  }
}
