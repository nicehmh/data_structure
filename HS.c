#include<stdio.h>
#define N 13
//��ϣ������������������
int HS(int key){
  return key%N;
}
//�ڹ�ϣ���в���key,���ҵ����������ڵ�λ�ã�����key�����ϣ�������򷵻�-1
int thread(int key,int m,int addr[]){
  int i,j;
  i=HS(i);//����key�Ĺ�ϣ��ַ
  if(addr[i]==key){//��key�ڹ�ϣ�����򷵻�����λ��
    return i;
  }
  i--;
  j=(i+1)%m;//����̽����ɢ�д����ͻ
  while(addr[j]!=key&&addr[j]!=0){
     if(j!=i){
       j=(j+1)%m;
     }else{
       return -1;//����
     }
  }
  if(addr[j]==key) return j;
  if(addr[j]==0){
    addr[j]=key;//���ҵ���λ�������
    return j;
  }
}
int main(){
  int i,j,m,n,num[N],addr[N];
  printf("����Ԫ�صĸ�����");
  scanf("%d",&n);
  printf("�����Ԫ��ֵ���ÿո������");
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
  printf("���ù�ϣ��������ʾ��\n");
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
    printf("����Ҫ���һ�Ҫ�����Ԫ��ֵ��");
    scanf("%d",&j);
    m=thread(j,N,addr);
    printf("%d���ڵ�λ���ǣ�%d\n",j,m);
}
