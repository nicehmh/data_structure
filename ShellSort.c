#include<stdio.h>
#define N 100
//ϣ������
typedef int KeyType;
typedef struct{
  KeyType key;
  //OtherType other_data;
}RecordType;
//�Լ�¼����r��һ��ϣ������lengthΪ���鳤�ȣ�deltaΪ����
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
//�Լ�¼����r��ϣ������lengthΪ����r�ĳ��ȣ�deltaΪ�������飬nΪdelta[]�ĳ���
void ShellSort(RecordType r[],int length,int delta[],int n){
    int i;
  for(i=0;i<=n-1;++i){
   //   printf("i=%d\n",i);
    ShellInsert(r,length,delta[i]);
  }
}
//ȡ��������.d=n/2����ȡ��,�������鳤��
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
//��ӡ����
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
  printf("���������������\n");
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
