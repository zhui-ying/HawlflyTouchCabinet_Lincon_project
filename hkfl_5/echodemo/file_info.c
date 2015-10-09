#include "file_info.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SEEK_SET 0//文件开头
#define SEEK_CUR 1//文件当前位置
#define SEEK_END 2//文件末尾

unsigned char read_file(int *size , const char *file_name)
{
	FILE *box_file;
//	int write_count;

	box_file = fopen(file_name,"r+b");//以二进制形态打开文件,可读可写
	if(NULL == box_file)
	return 0;
	fseek(box_file , 0, SEEK_END);//移动文件指针到需要的位置
	*size=ftell(box_file);
	fclose(box_file);//关闭文件
	return 1;		
}
/*名字交换 datafile/  将datafile/desk1.jpg和datafile/12.jpg互换名字*/
unsigned char ex_name(void)
{
	//if(0 != rename("datafile/desk1.jpg" , "datafile/13.jpg")) 
//	return 0;
	if(0 != rename("datafile/12.jpg" , "datafile/desk1.jpg"))
	return 0;
//	if(0 != rename("datafile/desk1temp.jpg" , "datafile/12.jpg"))
//	return 0;
	return 1;
	
}

unsigned char copy(void)
{
	FILE *file1;
	FILE *file2;
	unsigned char buf[1024];
	unsigned int read_count,write_count;

	file1 = fopen("datafile/desk1.jpg","w+b");//以二进制形态打开文件,可读可写,清空该文件
	file2 = fopen("datafile/12.jpg","r+b");
	if(file1 == NULL  || file2 == NULL) return 0;
	fseek(file1,0,SEEK_SET);//移动文件指针到首位
	fseek(file2,0,SEEK_SET);//移动文件指针到首位

	while(1)//匹配读出来的信息，直到相等
	{
		read_count = fread(buf ,  1 , 1024 , file2);//顺序读取
		write_count = fwrite(buf ,  1 , read_count , file1);

		if(write_count < 1024)
		{
			fclose(file1);
			fclose(file2);
			return 1;//匹配失败，到末尾了
		}
	}	
	
}

