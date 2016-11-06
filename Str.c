/* 堆串的基本操作 */
#include<stdio.h>
//定义堆串的存储结构
typedef struct{
  char * ch;
  int len;
}HString;
//初始化堆串
void InitHString(HString *str){
   str->ch=(char *)malloc(sizeof(char));
   str->len=-1;
}
//插入堆串
void InsertHString(HString *str,int pos,HString *t){
   int i;char *temp=NULL;
   if(pos<0||pos>s->len||s->len==0){
        printf("ERROR");
   }
   temp=(char *)malloc(s->len+t->len);
   if(temp==NULL){
      printf("内存分配失败");
   }
   for(i=0;i<s->len;i++){
      temp[i]
   }
}
int main(){
    HString *str=(HString *)malloc(sizeof(HString));
    InitHString(str);
}
