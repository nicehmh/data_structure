#include<stdio.h>
#include <math.h>
#define N 100
typedef char ElemType;

typedef struct Stack{
   ElemType elem[N];
   int top;
}Stack;
//初始化栈
void InitStack(Stack *S){
   S->top=-1;
}
//出栈
void Pop(Stack *S){
  if(S->top==-1){
      printf("stack is null");
   }else{
      S->top--;
   }
}
//入栈
void Push(Stack *S,ElemType e){
   S->top++;
   S->elem[S->top]=e;
}
//打印栈
void showStack(Stack *S){
   int i;
   if(S->top==-1){
      printf("stack is null");
   }else{
      for(i=S->top;i>=0;i--){
        printf("%c",S->elem[i]);
      }
   }
   printf("\n");
}
//十进制转其他进制
void statechange(Stack *S,int n,int i){
    int a=n,b;
    char c;
    do{
      b=a%i;
      if(b>9){
        c=b-10+'A';
      }else{
        c=b+'0';
      }
      Push(S,c);
      a=a/i;
    }while(a>0);
}

//其他进制转十进制
int changestate(Stack *L,int i){
   int k,n=0,l=L->top,g;
   for(k=0;k<=l;k++){
      g=L->elem[k]-'0';
      if(g>i){
          printf("输入的进制错误");
          return -1;
      }else{
           n+=pow(i,l-k)*(g);
      }
   }
   return n;
}
int main(){
   Stack *L=(Stack *)malloc(sizeof(Stack)) ;
   InitStack(L);
   Push(L,'3');Push(L,'1');Push(L,'5');
   int n=changestate(L,16);
   printf("%d\n",n);
   if(n>0){
     Stack *S=(Stack *)malloc(sizeof(Stack)) ;
     InitStack(S);
     statechange(S,n,2);
     showStack(S);
   }
   //Pop(S);
   //printf("%d",S->top);
}
