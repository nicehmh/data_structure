#include<stdio.h>
typedef char AtomType;
typedef enum {ATOM,LIST} ElemTag;/* ATOM表示原子;LIST表示子表  */
typedef struct GLNode{
   ElemTag tag; /* 区别原子结点和表结点 */
   union{
     AtomType atom;  /*  原子结点的值域  */
     struct {struct GLNode *hp,*tp} htp;  /* 表结点指针域htp,包括表头指针域hp和表尾指针域tp */
   }atom_htp;
}GLNode,*GList;

//创建广义表

//打印广义表
int showGList(GLNode *L){
   if(L!=NULL){
      if(L->tag==ATOM){
        printf("%c,",L->atom_htp.atom);
         return 0;
      }else if(L->tag==LIST){
         showGList(L->atom_htp.htp.hp);
         showGList(L->atom_htp.htp.tp);
      }else{
         printf("error");
         return 0;
      }
   }
   return 0;
}
int main(){
   GLNode *L=(GLNode *)malloc(sizeof(GLNode));
   char *a=(char *)malloc(20*sizeof(char));
   printf("input c:");
   scanf("%s",a);
   CreateGList(L,a);
   showGList(L);

}
