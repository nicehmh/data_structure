/* �Ѵ��Ļ������� */
#include<stdio.h>
//����Ѵ��Ĵ洢�ṹ
typedef struct{
  char * ch;
  int len;
}HString;
//��ʼ���Ѵ�
void InitHString(HString *str){
   str->ch=(char *)malloc(sizeof(char));
   str->len=-1;
}
//����Ѵ�
void InsertHString(HString *str,int pos,HString *t){
   int i;char *temp=NULL;
   if(pos<0||pos>s->len||s->len==0){
        printf("ERROR");
   }
   temp=(char *)malloc(s->len+t->len);
   if(temp==NULL){
      printf("�ڴ����ʧ��");
   }
   for(i=0;i<s->len;i++){
      temp[i]
   }
}
int main(){
    HString *str=(HString *)malloc(sizeof(HString));
    InitHString(str);
}
