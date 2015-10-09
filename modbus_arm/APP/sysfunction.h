#ifndef __SYSFUNCTION_H_
#define __SYSFUNCTION_H_

void SysChangePassWord(FUN_BLOCK **funBlock);
void SysSetWorkMod(FUN_BLOCK **funBlock);
void SysSetBoxNum(FUN_BLOCK **funBlock);
void SysSetCabStation(FUN_BLOCK **funBlock);
void SysOpenOneBox(FUN_BLOCK **funBlock);
void SysOpenAllBox(FUN_BLOCK **funBlock);
void SysSetPort(FUN_BLOCK **funBlock);
void SysSetTime(FUN_BLOCK **funBlock);
void SysCheckRecord(FUN_BLOCK **funBlock);
void SysRecoveryInit(FUN_BLOCK **funBlock);
void SysExit(FUN_BLOCK **funBlock);
void RestKeyCheck(void);
unsigned char AuthorProcess(unsigned char key_data);

#endif

