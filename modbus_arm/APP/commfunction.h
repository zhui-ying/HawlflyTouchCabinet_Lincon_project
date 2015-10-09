#ifndef __COMMFUNCTIION_H_
#define __COMMFUNCTIION_H_

void CommChangePassWord(FUN_BLOCK **funBlock);
void CommClearAllBox(FUN_BLOCK **funBlock);
void CommLockOneBox(FUN_BLOCK **funBlock);
void CommUnLockOneBox(FUN_BLOCK **funBlock);
void CommLockAllBox(FUN_BLOCK **funBlock);
void CommUnLockAllBox(FUN_BLOCK **funBlock);
void CommRegistUser(FUN_BLOCK **funBlock);
void CommCancleUser(FUN_BLOCK **funBlock);

#endif
