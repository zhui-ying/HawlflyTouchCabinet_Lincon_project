#ifndef __MAINFUNCTION_H_
#define __MAINFUNCTION_H_

void DisplaySubBlock(FUN_BLOCK *funBlock);
unsigned char KeyDisplay(FUN_BLOCK *funBlock , unsigned char key_length);
void GetSubFunBlock(FUN_BLOCK **pfunSubBlock);

void MainEnter(FUN_BLOCK **funBlock);
void SysEnter(FUN_BLOCK **funBlock);
void CommEnter(FUN_BLOCK **funBlock);
void UserEnter(FUN_BLOCK **funBlock);

#endif

