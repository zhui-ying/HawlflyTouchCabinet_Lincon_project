#ifndef __FUNCTIONLIST_H_
#define __FUNCTIONLIST_H_

#define MAX_SYS_FUN_BLOCK  15
#define MAX_PARENT_FUN_BLOCK 4
#define MAX_COMM_FUN_BLOCK 15

#define LINE_LENGTH  25

/*定义一个基本功能的结构体*/
typedef struct fun_block{
	void *current_display;         //显示操作
	struct fun_block *pnext_block;//指向上一个功能
	struct fun_block *plast_block;//指向下一个功能		  行程双向链表
	struct fun_block *origin_block;//指向上一级操作
	struct fun_block *sub_block;   //指向下一级操作	
	void (*current_function)(struct fun_block **);			 //指向该级功能实现函数
	enum {NONUM , XINGNUM , ZINUM} data_type;		 //本级属性
}FUN_BLOCK;

typedef struct sing_display{
		char y1[LINE_LENGTH];
		char y2[LINE_LENGTH];
		char y3[LINE_LENGTH];
		char y4[LINE_LENGTH];
}DIS_SING;

extern FUN_BLOCK sysFunBlock[MAX_SYS_FUN_BLOCK];
extern FUN_BLOCK commFunBlock[MAX_COMM_FUN_BLOCK];
extern FUN_BLOCK *pfunBlock;
extern FUN_BLOCK *pfunSubBlock;
extern FUN_BLOCK parentFunBlock[MAX_PARENT_FUN_BLOCK];
extern FUN_BLOCK userChangeCodeFunBlock[1];
extern FUN_BLOCK mainFunBlock[1];

void AdjustBlock(FUN_BLOCK *funBlock , unsigned char length);

#endif

