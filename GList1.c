#include<stdio.h>
typedef char AtomType;
typedef enum {ATOM,LIST} ElemTag;/* ATOM��ʾԭ��;LIST��ʾ�ӱ�  */
typedef struct GLNode{
   ElemTag tag; /* ����ԭ�ӽ��ͱ��� */
   union{
     AtomType atom;  /*  ԭ�ӽ���ֵ��  */
     struct {struct GLNode *hp,*tp} htp;  /* ����ָ����htp,������ͷָ����hp�ͱ�βָ����tp */
   }atom_htp;
}GLNode,*GList;

//���������

//��ӡ�����
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
