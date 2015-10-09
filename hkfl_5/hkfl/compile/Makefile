CFLAGS=
PROG_DIR=D:/SProgram\ Files/LinCon/ArgusSoft
PROG_DIR_M=D:/SProgram\ Files/LinCon/ArgusSoft
X86CC=$(PROG_DIR)/mingw/gcc/bin/gcc
X86AR=$(PROG_DIR)/mingw/gcc/bin/ar
HMICC=$(PROG_DIR)/mingw/arm-gnueabi/bin/arm-none-linux-gnueabi-gcc
HMISTRIP=$(PROG_DIR)/mingw/arm-gnueabi/bin/arm-none-linux-gnueabi-strip
HMIAR=$(PROG_DIR)/mingw/arm-gnueabi/bin/arm-none-linux-gnueabi-ar
INCLUDE=$(PROG_DIR)/include
SYS_HMI_INCLUDE=.
PRJ_DIR=D:/SProgram\ Files/LinCon/project/hkfl_5/hkfl
LCHMIFUNC=$(PROG_DIR)/hmi/cortex-a8/lchmifunc.c
LCHMIFUNC_M=$(PROG_DIR_M)/hmi/cortex-a8/lchmifunc.c
LCHMIUTILWIN=$(PROG_DIR)/hmi/cortex-a8/libhmiutil_win.a
LCHMIUTIL=$(PROG_DIR)/hmi/cortex-a8/libhmiutil.a

all:lchmifunc.dll libhmiuserfun.so

lchmifunc.dll:$(LCHMIFUNC_M) __hmi_funcs.c main_prop.o main_event.o logo_prop.o logo_event.o win_get_pack_prop.o win_get_pack_event.o win_test_prop.o win_test_event.o win_box_tip_prop.o win_box_tip_event.o win_input_password_prop.o win_input_password_event.o win_admin_prop.o win_admin_event.o TextKeyboard6_prop.o TextKeyboard6_event.o win_cabinet_set_prop.o win_cabinet_set_event.o win_tip_prop.o win_tip_event.o win_box_set_prop.o win_box_set_event.o win_box_operate_prop.o win_box_operate_event.o win_sender_psd_prop.o win_sender_psd_event.o win_wait_tip_prop.o win_wait_tip_event.o win_input_send_tm_prop.o win_input_send_tm_event.o win_input_pnum_type_prop.o win_input_pnum_type_event.o win_save_pack_next_tip_prop.o win_save_pack_next_tip_event.o NumKeyboard3_prop.o NumKeyboard3_event.o win_sys_set_prop.o win_sys_set_event.o win_change_admin_psd_prop.o win_change_admin_psd_event.o win_sys_set_time_prop.o win_sys_set_time_event.o win_sys_reset_prop.o win_sys_reset_event.o win_ad_prop.o win_ad_event.o win_disp_box_status_prop.o win_disp_box_status_event.o win_history_prop.o win_history_event.o win_history_detail_prop.o win_history_detail_event.o __external_c_win.a 
	$(X86CC) $(CFLAGS) -D_WINDOWS -D_WINDOWSGUI -O2 -I$(INCLUDE) -shared -o lchmifunc.dll $(LCHMIFUNC) __hmi_funcs.c main_prop.o main_event.o logo_prop.o logo_event.o win_get_pack_prop.o win_get_pack_event.o win_test_prop.o win_test_event.o win_box_tip_prop.o win_box_tip_event.o win_input_password_prop.o win_input_password_event.o win_admin_prop.o win_admin_event.o TextKeyboard6_prop.o TextKeyboard6_event.o win_cabinet_set_prop.o win_cabinet_set_event.o win_tip_prop.o win_tip_event.o win_box_set_prop.o win_box_set_event.o win_box_operate_prop.o win_box_operate_event.o win_sender_psd_prop.o win_sender_psd_event.o win_wait_tip_prop.o win_wait_tip_event.o win_input_send_tm_prop.o win_input_send_tm_event.o win_input_pnum_type_prop.o win_input_pnum_type_event.o win_save_pack_next_tip_prop.o win_save_pack_next_tip_event.o NumKeyboard3_prop.o NumKeyboard3_event.o win_sys_set_prop.o win_sys_set_event.o win_change_admin_psd_prop.o win_change_admin_psd_event.o win_sys_set_time_prop.o win_sys_set_time_event.o win_sys_reset_prop.o win_sys_reset_event.o win_ad_prop.o win_ad_event.o win_disp_box_status_prop.o win_disp_box_status_event.o win_history_prop.o win_history_event.o win_history_detail_prop.o win_history_detail_event.o __external_c_win.a     -L. -L$(PROG_DIR) -llcrun -lws2_32 $(LCHMIUTILWIN)
	cp lchmifunc.dll ..

main_prop.o:main_prop.c
	echo "编译窗口:main 动态属性(Windows)"
	$(X86CC) $(CFLAGS) -Iinclude -D_WINDOWS -D_WINDOWSGUI -O2 -I$(INCLUDE) -o main_prop.o -c main_prop.c

main_event.o:main_event.c
	echo "编译窗口:main 事件(Windows)"
	$(X86CC) $(CFLAGS) -Iinclude -D_WINDOWS -D_WINDOWSGUI -O2 -I$(INCLUDE) -o main_event.o -c main_event.c

logo_prop.o:logo_prop.c
	echo "编译窗口:logo 动态属性(Windows)"
	$(X86CC) $(CFLAGS) -Iinclude -D_WINDOWS -D_WINDOWSGUI -O2 -I$(INCLUDE) -o logo_prop.o -c logo_prop.c

logo_event.o:logo_event.c
	echo "编译窗口:logo 事件(Windows)"
	$(X86CC) $(CFLAGS) -Iinclude -D_WINDOWS -D_WINDOWSGUI -O2 -I$(INCLUDE) -o logo_event.o -c logo_event.c

win_get_pack_prop.o:win_get_pack_prop.c
	echo "编译窗口:win_get_pack 动态属性(Windows)"
	$(X86CC) $(CFLAGS) -Iinclude -D_WINDOWS -D_WINDOWSGUI -O2 -I$(INCLUDE) -o win_get_pack_prop.o -c win_get_pack_prop.c

win_get_pack_event.o:win_get_pack_event.c
	echo "编译窗口:win_get_pack 事件(Windows)"
	$(X86CC) $(CFLAGS) -Iinclude -D_WINDOWS -D_WINDOWSGUI -O2 -I$(INCLUDE) -o win_get_pack_event.o -c win_get_pack_event.c

win_test_prop.o:win_test_prop.c
	echo "编译窗口:win_test 动态属性(Windows)"
	$(X86CC) $(CFLAGS) -Iinclude -D_WINDOWS -D_WINDOWSGUI -O2 -I$(INCLUDE) -o win_test_prop.o -c win_test_prop.c

win_test_event.o:win_test_event.c
	echo "编译窗口:win_test 事件(Windows)"
	$(X86CC) $(CFLAGS) -Iinclude -D_WINDOWS -D_WINDOWSGUI -O2 -I$(INCLUDE) -o win_test_event.o -c win_test_event.c

win_box_tip_prop.o:win_box_tip_prop.c
	echo "编译窗口:win_box_tip 动态属性(Windows)"
	$(X86CC) $(CFLAGS) -Iinclude -D_WINDOWS -D_WINDOWSGUI -O2 -I$(INCLUDE) -o win_box_tip_prop.o -c win_box_tip_prop.c

win_box_tip_event.o:win_box_tip_event.c
	echo "编译窗口:win_box_tip 事件(Windows)"
	$(X86CC) $(CFLAGS) -Iinclude -D_WINDOWS -D_WINDOWSGUI -O2 -I$(INCLUDE) -o win_box_tip_event.o -c win_box_tip_event.c

win_input_password_prop.o:win_input_password_prop.c
	echo "编译窗口:win_input_password 动态属性(Windows)"
	$(X86CC) $(CFLAGS) -Iinclude -D_WINDOWS -D_WINDOWSGUI -O2 -I$(INCLUDE) -o win_input_password_prop.o -c win_input_password_prop.c

win_input_password_event.o:win_input_password_event.c
	echo "编译窗口:win_input_password 事件(Windows)"
	$(X86CC) $(CFLAGS) -Iinclude -D_WINDOWS -D_WINDOWSGUI -O2 -I$(INCLUDE) -o win_input_password_event.o -c win_input_password_event.c

win_admin_prop.o:win_admin_prop.c
	echo "编译窗口:win_admin 动态属性(Windows)"
	$(X86CC) $(CFLAGS) -Iinclude -D_WINDOWS -D_WINDOWSGUI -O2 -I$(INCLUDE) -o win_admin_prop.o -c win_admin_prop.c

win_admin_event.o:win_admin_event.c
	echo "编译窗口:win_admin 事件(Windows)"
	$(X86CC) $(CFLAGS) -Iinclude -D_WINDOWS -D_WINDOWSGUI -O2 -I$(INCLUDE) -o win_admin_event.o -c win_admin_event.c

TextKeyboard6_prop.o:TextKeyboard6_prop.c
	echo "编译窗口:TextKeyboard6 动态属性(Windows)"
	$(X86CC) $(CFLAGS) -Iinclude -D_WINDOWS -D_WINDOWSGUI -O2 -I$(INCLUDE) -o TextKeyboard6_prop.o -c TextKeyboard6_prop.c

TextKeyboard6_event.o:TextKeyboard6_event.c
	echo "编译窗口:TextKeyboard6 事件(Windows)"
	$(X86CC) $(CFLAGS) -Iinclude -D_WINDOWS -D_WINDOWSGUI -O2 -I$(INCLUDE) -o TextKeyboard6_event.o -c TextKeyboard6_event.c

win_cabinet_set_prop.o:win_cabinet_set_prop.c
	echo "编译窗口:win_cabinet_set 动态属性(Windows)"
	$(X86CC) $(CFLAGS) -Iinclude -D_WINDOWS -D_WINDOWSGUI -O2 -I$(INCLUDE) -o win_cabinet_set_prop.o -c win_cabinet_set_prop.c

win_cabinet_set_event.o:win_cabinet_set_event.c
	echo "编译窗口:win_cabinet_set 事件(Windows)"
	$(X86CC) $(CFLAGS) -Iinclude -D_WINDOWS -D_WINDOWSGUI -O2 -I$(INCLUDE) -o win_cabinet_set_event.o -c win_cabinet_set_event.c

win_tip_prop.o:win_tip_prop.c
	echo "编译窗口:win_tip 动态属性(Windows)"
	$(X86CC) $(CFLAGS) -Iinclude -D_WINDOWS -D_WINDOWSGUI -O2 -I$(INCLUDE) -o win_tip_prop.o -c win_tip_prop.c

win_tip_event.o:win_tip_event.c
	echo "编译窗口:win_tip 事件(Windows)"
	$(X86CC) $(CFLAGS) -Iinclude -D_WINDOWS -D_WINDOWSGUI -O2 -I$(INCLUDE) -o win_tip_event.o -c win_tip_event.c

win_box_set_prop.o:win_box_set_prop.c
	echo "编译窗口:win_box_set 动态属性(Windows)"
	$(X86CC) $(CFLAGS) -Iinclude -D_WINDOWS -D_WINDOWSGUI -O2 -I$(INCLUDE) -o win_box_set_prop.o -c win_box_set_prop.c

win_box_set_event.o:win_box_set_event.c
	echo "编译窗口:win_box_set 事件(Windows)"
	$(X86CC) $(CFLAGS) -Iinclude -D_WINDOWS -D_WINDOWSGUI -O2 -I$(INCLUDE) -o win_box_set_event.o -c win_box_set_event.c

win_box_operate_prop.o:win_box_operate_prop.c
	echo "编译窗口:win_box_operate 动态属性(Windows)"
	$(X86CC) $(CFLAGS) -Iinclude -D_WINDOWS -D_WINDOWSGUI -O2 -I$(INCLUDE) -o win_box_operate_prop.o -c win_box_operate_prop.c

win_box_operate_event.o:win_box_operate_event.c
	echo "编译窗口:win_box_operate 事件(Windows)"
	$(X86CC) $(CFLAGS) -Iinclude -D_WINDOWS -D_WINDOWSGUI -O2 -I$(INCLUDE) -o win_box_operate_event.o -c win_box_operate_event.c

win_sender_psd_prop.o:win_sender_psd_prop.c
	echo "编译窗口:win_sender_psd 动态属性(Windows)"
	$(X86CC) $(CFLAGS) -Iinclude -D_WINDOWS -D_WINDOWSGUI -O2 -I$(INCLUDE) -o win_sender_psd_prop.o -c win_sender_psd_prop.c

win_sender_psd_event.o:win_sender_psd_event.c
	echo "编译窗口:win_sender_psd 事件(Windows)"
	$(X86CC) $(CFLAGS) -Iinclude -D_WINDOWS -D_WINDOWSGUI -O2 -I$(INCLUDE) -o win_sender_psd_event.o -c win_sender_psd_event.c

win_wait_tip_prop.o:win_wait_tip_prop.c
	echo "编译窗口:win_wait_tip 动态属性(Windows)"
	$(X86CC) $(CFLAGS) -Iinclude -D_WINDOWS -D_WINDOWSGUI -O2 -I$(INCLUDE) -o win_wait_tip_prop.o -c win_wait_tip_prop.c

win_wait_tip_event.o:win_wait_tip_event.c
	echo "编译窗口:win_wait_tip 事件(Windows)"
	$(X86CC) $(CFLAGS) -Iinclude -D_WINDOWS -D_WINDOWSGUI -O2 -I$(INCLUDE) -o win_wait_tip_event.o -c win_wait_tip_event.c

win_input_send_tm_prop.o:win_input_send_tm_prop.c
	echo "编译窗口:win_input_send_tm 动态属性(Windows)"
	$(X86CC) $(CFLAGS) -Iinclude -D_WINDOWS -D_WINDOWSGUI -O2 -I$(INCLUDE) -o win_input_send_tm_prop.o -c win_input_send_tm_prop.c

win_input_send_tm_event.o:win_input_send_tm_event.c
	echo "编译窗口:win_input_send_tm 事件(Windows)"
	$(X86CC) $(CFLAGS) -Iinclude -D_WINDOWS -D_WINDOWSGUI -O2 -I$(INCLUDE) -o win_input_send_tm_event.o -c win_input_send_tm_event.c

win_input_pnum_type_prop.o:win_input_pnum_type_prop.c
	echo "编译窗口:win_input_pnum_type 动态属性(Windows)"
	$(X86CC) $(CFLAGS) -Iinclude -D_WINDOWS -D_WINDOWSGUI -O2 -I$(INCLUDE) -o win_input_pnum_type_prop.o -c win_input_pnum_type_prop.c

win_input_pnum_type_event.o:win_input_pnum_type_event.c
	echo "编译窗口:win_input_pnum_type 事件(Windows)"
	$(X86CC) $(CFLAGS) -Iinclude -D_WINDOWS -D_WINDOWSGUI -O2 -I$(INCLUDE) -o win_input_pnum_type_event.o -c win_input_pnum_type_event.c

win_save_pack_next_tip_prop.o:win_save_pack_next_tip_prop.c
	echo "编译窗口:win_save_pack_next_tip 动态属性(Windows)"
	$(X86CC) $(CFLAGS) -Iinclude -D_WINDOWS -D_WINDOWSGUI -O2 -I$(INCLUDE) -o win_save_pack_next_tip_prop.o -c win_save_pack_next_tip_prop.c

win_save_pack_next_tip_event.o:win_save_pack_next_tip_event.c
	echo "编译窗口:win_save_pack_next_tip 事件(Windows)"
	$(X86CC) $(CFLAGS) -Iinclude -D_WINDOWS -D_WINDOWSGUI -O2 -I$(INCLUDE) -o win_save_pack_next_tip_event.o -c win_save_pack_next_tip_event.c

NumKeyboard3_prop.o:NumKeyboard3_prop.c
	echo "编译窗口:NumKeyboard3 动态属性(Windows)"
	$(X86CC) $(CFLAGS) -Iinclude -D_WINDOWS -D_WINDOWSGUI -O2 -I$(INCLUDE) -o NumKeyboard3_prop.o -c NumKeyboard3_prop.c

NumKeyboard3_event.o:NumKeyboard3_event.c
	echo "编译窗口:NumKeyboard3 事件(Windows)"
	$(X86CC) $(CFLAGS) -Iinclude -D_WINDOWS -D_WINDOWSGUI -O2 -I$(INCLUDE) -o NumKeyboard3_event.o -c NumKeyboard3_event.c

win_sys_set_prop.o:win_sys_set_prop.c
	echo "编译窗口:win_sys_set 动态属性(Windows)"
	$(X86CC) $(CFLAGS) -Iinclude -D_WINDOWS -D_WINDOWSGUI -O2 -I$(INCLUDE) -o win_sys_set_prop.o -c win_sys_set_prop.c

win_sys_set_event.o:win_sys_set_event.c
	echo "编译窗口:win_sys_set 事件(Windows)"
	$(X86CC) $(CFLAGS) -Iinclude -D_WINDOWS -D_WINDOWSGUI -O2 -I$(INCLUDE) -o win_sys_set_event.o -c win_sys_set_event.c

win_change_admin_psd_prop.o:win_change_admin_psd_prop.c
	echo "编译窗口:win_change_admin_psd 动态属性(Windows)"
	$(X86CC) $(CFLAGS) -Iinclude -D_WINDOWS -D_WINDOWSGUI -O2 -I$(INCLUDE) -o win_change_admin_psd_prop.o -c win_change_admin_psd_prop.c

win_change_admin_psd_event.o:win_change_admin_psd_event.c
	echo "编译窗口:win_change_admin_psd 事件(Windows)"
	$(X86CC) $(CFLAGS) -Iinclude -D_WINDOWS -D_WINDOWSGUI -O2 -I$(INCLUDE) -o win_change_admin_psd_event.o -c win_change_admin_psd_event.c

win_sys_set_time_prop.o:win_sys_set_time_prop.c
	echo "编译窗口:win_sys_set_time 动态属性(Windows)"
	$(X86CC) $(CFLAGS) -Iinclude -D_WINDOWS -D_WINDOWSGUI -O2 -I$(INCLUDE) -o win_sys_set_time_prop.o -c win_sys_set_time_prop.c

win_sys_set_time_event.o:win_sys_set_time_event.c
	echo "编译窗口:win_sys_set_time 事件(Windows)"
	$(X86CC) $(CFLAGS) -Iinclude -D_WINDOWS -D_WINDOWSGUI -O2 -I$(INCLUDE) -o win_sys_set_time_event.o -c win_sys_set_time_event.c

win_sys_reset_prop.o:win_sys_reset_prop.c
	echo "编译窗口:win_sys_reset 动态属性(Windows)"
	$(X86CC) $(CFLAGS) -Iinclude -D_WINDOWS -D_WINDOWSGUI -O2 -I$(INCLUDE) -o win_sys_reset_prop.o -c win_sys_reset_prop.c

win_sys_reset_event.o:win_sys_reset_event.c
	echo "编译窗口:win_sys_reset 事件(Windows)"
	$(X86CC) $(CFLAGS) -Iinclude -D_WINDOWS -D_WINDOWSGUI -O2 -I$(INCLUDE) -o win_sys_reset_event.o -c win_sys_reset_event.c

win_ad_prop.o:win_ad_prop.c
	echo "编译窗口:win_ad 动态属性(Windows)"
	$(X86CC) $(CFLAGS) -Iinclude -D_WINDOWS -D_WINDOWSGUI -O2 -I$(INCLUDE) -o win_ad_prop.o -c win_ad_prop.c

win_ad_event.o:win_ad_event.c
	echo "编译窗口:win_ad 事件(Windows)"
	$(X86CC) $(CFLAGS) -Iinclude -D_WINDOWS -D_WINDOWSGUI -O2 -I$(INCLUDE) -o win_ad_event.o -c win_ad_event.c

win_disp_box_status_prop.o:win_disp_box_status_prop.c
	echo "编译窗口:win_disp_box_status 动态属性(Windows)"
	$(X86CC) $(CFLAGS) -Iinclude -D_WINDOWS -D_WINDOWSGUI -O2 -I$(INCLUDE) -o win_disp_box_status_prop.o -c win_disp_box_status_prop.c

win_disp_box_status_event.o:win_disp_box_status_event.c
	echo "编译窗口:win_disp_box_status 事件(Windows)"
	$(X86CC) $(CFLAGS) -Iinclude -D_WINDOWS -D_WINDOWSGUI -O2 -I$(INCLUDE) -o win_disp_box_status_event.o -c win_disp_box_status_event.c

win_history_prop.o:win_history_prop.c
	echo "编译窗口:win_history 动态属性(Windows)"
	$(X86CC) $(CFLAGS) -Iinclude -D_WINDOWS -D_WINDOWSGUI -O2 -I$(INCLUDE) -o win_history_prop.o -c win_history_prop.c

win_history_event.o:win_history_event.c
	echo "编译窗口:win_history 事件(Windows)"
	$(X86CC) $(CFLAGS) -Iinclude -D_WINDOWS -D_WINDOWSGUI -O2 -I$(INCLUDE) -o win_history_event.o -c win_history_event.c

win_history_detail_prop.o:win_history_detail_prop.c
	echo "编译窗口:win_history_detail 动态属性(Windows)"
	$(X86CC) $(CFLAGS) -Iinclude -D_WINDOWS -D_WINDOWSGUI -O2 -I$(INCLUDE) -o win_history_detail_prop.o -c win_history_detail_prop.c

win_history_detail_event.o:win_history_detail_event.c
	echo "编译窗口:win_history_detail 事件(Windows)"
	$(X86CC) $(CFLAGS) -Iinclude -D_WINDOWS -D_WINDOWSGUI -O2 -I$(INCLUDE) -o win_history_detail_event.o -c win_history_detail_event.c

__external_c_win.a:__external_c_win_file0.o __external_c_win_file1.o __external_c_win_file2.o 
	rm -f __external_c_win.a 
	$(X86AR) rcs __external_c_win.a __external_c_win_file0.o __external_c_win_file1.o __external_c_win_file2.o 

__external_c_win_file0.o:D:/SProgram\ Files/LinCon/project/hkfl_5/hkfl\src\GPRS.c
	echo "编译源文件(Windows):D:/SProgram\ Files/LinCon/project/hkfl_5/hkfl\src\GPRS.c"
	$(X86CC) $(CFLAGS) -Iinclude -D_WINDOWS -D_WINDOWSGUI -O2 -I$(INCLUDE) -o __external_c_win_file0.o -c D:/SProgram\ Files/LinCon/project/hkfl_5/hkfl\src\GPRS.c

__external_c_win_file1.o:D:/SProgram\ Files/LinCon/project/hkfl_5/hkfl\src\user_function.c
	echo "编译源文件(Windows):D:/SProgram\ Files/LinCon/project/hkfl_5/hkfl\src\user_function.c"
	$(X86CC) $(CFLAGS) -Iinclude -D_WINDOWS -D_WINDOWSGUI -O2 -I$(INCLUDE) -o __external_c_win_file1.o -c D:/SProgram\ Files/LinCon/project/hkfl_5/hkfl\src\user_function.c

__external_c_win_file2.o:D:/SProgram\ Files/LinCon/project/hkfl_5/hkfl\src\box_info.c
	echo "编译源文件(Windows):D:/SProgram\ Files/LinCon/project/hkfl_5/hkfl\src\box_info.c"
	$(X86CC) $(CFLAGS) -Iinclude -D_WINDOWS -D_WINDOWSGUI -O2 -I$(INCLUDE) -o __external_c_win_file2.o -c D:/SProgram\ Files/LinCon/project/hkfl_5/hkfl\src\box_info.c

libhmiuserfun.so:$(LCHMIFUNC_M) __hmi_funcs.c main_prop_hmi.o main_event_hmi.o logo_prop_hmi.o logo_event_hmi.o win_get_pack_prop_hmi.o win_get_pack_event_hmi.o win_test_prop_hmi.o win_test_event_hmi.o win_box_tip_prop_hmi.o win_box_tip_event_hmi.o win_input_password_prop_hmi.o win_input_password_event_hmi.o win_admin_prop_hmi.o win_admin_event_hmi.o TextKeyboard6_prop_hmi.o TextKeyboard6_event_hmi.o win_cabinet_set_prop_hmi.o win_cabinet_set_event_hmi.o win_tip_prop_hmi.o win_tip_event_hmi.o win_box_set_prop_hmi.o win_box_set_event_hmi.o win_box_operate_prop_hmi.o win_box_operate_event_hmi.o win_sender_psd_prop_hmi.o win_sender_psd_event_hmi.o win_wait_tip_prop_hmi.o win_wait_tip_event_hmi.o win_input_send_tm_prop_hmi.o win_input_send_tm_event_hmi.o win_input_pnum_type_prop_hmi.o win_input_pnum_type_event_hmi.o win_save_pack_next_tip_prop_hmi.o win_save_pack_next_tip_event_hmi.o NumKeyboard3_prop_hmi.o NumKeyboard3_event_hmi.o win_sys_set_prop_hmi.o win_sys_set_event_hmi.o win_change_admin_psd_prop_hmi.o win_change_admin_psd_event_hmi.o win_sys_set_time_prop_hmi.o win_sys_set_time_event_hmi.o win_sys_reset_prop_hmi.o win_sys_reset_event_hmi.o win_ad_prop_hmi.o win_ad_event_hmi.o win_disp_box_status_prop_hmi.o win_disp_box_status_event_hmi.o win_history_prop_hmi.o win_history_event_hmi.o win_history_detail_prop_hmi.o win_history_detail_event_hmi.o __external_c_hmi.a 
	$(HMICC) $(CFLAGS) -D_LINUX -fPIC  -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp  -O2 -I$(SYS_HMI_INCLUDE) -I$(INCLUDE) -shared -o libhmiuserfun.so $(LCHMIFUNC) __hmi_funcs.c main_prop_hmi.o main_event_hmi.o logo_prop_hmi.o logo_event_hmi.o win_get_pack_prop_hmi.o win_get_pack_event_hmi.o win_test_prop_hmi.o win_test_event_hmi.o win_box_tip_prop_hmi.o win_box_tip_event_hmi.o win_input_password_prop_hmi.o win_input_password_event_hmi.o win_admin_prop_hmi.o win_admin_event_hmi.o TextKeyboard6_prop_hmi.o TextKeyboard6_event_hmi.o win_cabinet_set_prop_hmi.o win_cabinet_set_event_hmi.o win_tip_prop_hmi.o win_tip_event_hmi.o win_box_set_prop_hmi.o win_box_set_event_hmi.o win_box_operate_prop_hmi.o win_box_operate_event_hmi.o win_sender_psd_prop_hmi.o win_sender_psd_event_hmi.o win_wait_tip_prop_hmi.o win_wait_tip_event_hmi.o win_input_send_tm_prop_hmi.o win_input_send_tm_event_hmi.o win_input_pnum_type_prop_hmi.o win_input_pnum_type_event_hmi.o win_save_pack_next_tip_prop_hmi.o win_save_pack_next_tip_event_hmi.o NumKeyboard3_prop_hmi.o NumKeyboard3_event_hmi.o win_sys_set_prop_hmi.o win_sys_set_event_hmi.o win_change_admin_psd_prop_hmi.o win_change_admin_psd_event_hmi.o win_sys_set_time_prop_hmi.o win_sys_set_time_event_hmi.o win_sys_reset_prop_hmi.o win_sys_reset_event_hmi.o win_ad_prop_hmi.o win_ad_event_hmi.o win_disp_box_status_prop_hmi.o win_disp_box_status_event_hmi.o win_history_prop_hmi.o win_history_event_hmi.o win_history_detail_prop_hmi.o win_history_detail_event_hmi.o __external_c_hmi.a    -L. -L$(PROG_DIR) $(LCHMIUTIL)
	$(HMISTRIP) libhmiuserfun.so
	cp libhmiuserfun.so ..

main_prop_hmi.o:main_prop.c
	echo "编译窗口:main 动态属性(HMI)"
	$(HMICC)  $(CFLAGS) -D_LINUX  -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp  -O2 -fPIC -I$(INCLUDE) -I$(SYS_HMI_INCLUDE)  -o main_prop_hmi.o -c main_prop.c

main_event_hmi.o:main_event.c
	echo "编译窗口:main 事件(HMI)"
	$(HMICC)  $(CFLAGS) -D_LINUX  -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp  -O2 -fPIC -I$(INCLUDE) -I$(SYS_HMI_INCLUDE) -o main_event_hmi.o -c main_event.c

logo_prop_hmi.o:logo_prop.c
	echo "编译窗口:logo 动态属性(HMI)"
	$(HMICC)  $(CFLAGS) -D_LINUX  -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp  -O2 -fPIC -I$(INCLUDE) -I$(SYS_HMI_INCLUDE)  -o logo_prop_hmi.o -c logo_prop.c

logo_event_hmi.o:logo_event.c
	echo "编译窗口:logo 事件(HMI)"
	$(HMICC)  $(CFLAGS) -D_LINUX  -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp  -O2 -fPIC -I$(INCLUDE) -I$(SYS_HMI_INCLUDE) -o logo_event_hmi.o -c logo_event.c

win_get_pack_prop_hmi.o:win_get_pack_prop.c
	echo "编译窗口:win_get_pack 动态属性(HMI)"
	$(HMICC)  $(CFLAGS) -D_LINUX  -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp  -O2 -fPIC -I$(INCLUDE) -I$(SYS_HMI_INCLUDE)  -o win_get_pack_prop_hmi.o -c win_get_pack_prop.c

win_get_pack_event_hmi.o:win_get_pack_event.c
	echo "编译窗口:win_get_pack 事件(HMI)"
	$(HMICC)  $(CFLAGS) -D_LINUX  -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp  -O2 -fPIC -I$(INCLUDE) -I$(SYS_HMI_INCLUDE) -o win_get_pack_event_hmi.o -c win_get_pack_event.c

win_test_prop_hmi.o:win_test_prop.c
	echo "编译窗口:win_test 动态属性(HMI)"
	$(HMICC)  $(CFLAGS) -D_LINUX  -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp  -O2 -fPIC -I$(INCLUDE) -I$(SYS_HMI_INCLUDE)  -o win_test_prop_hmi.o -c win_test_prop.c

win_test_event_hmi.o:win_test_event.c
	echo "编译窗口:win_test 事件(HMI)"
	$(HMICC)  $(CFLAGS) -D_LINUX  -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp  -O2 -fPIC -I$(INCLUDE) -I$(SYS_HMI_INCLUDE) -o win_test_event_hmi.o -c win_test_event.c

win_box_tip_prop_hmi.o:win_box_tip_prop.c
	echo "编译窗口:win_box_tip 动态属性(HMI)"
	$(HMICC)  $(CFLAGS) -D_LINUX  -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp  -O2 -fPIC -I$(INCLUDE) -I$(SYS_HMI_INCLUDE)  -o win_box_tip_prop_hmi.o -c win_box_tip_prop.c

win_box_tip_event_hmi.o:win_box_tip_event.c
	echo "编译窗口:win_box_tip 事件(HMI)"
	$(HMICC)  $(CFLAGS) -D_LINUX  -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp  -O2 -fPIC -I$(INCLUDE) -I$(SYS_HMI_INCLUDE) -o win_box_tip_event_hmi.o -c win_box_tip_event.c

win_input_password_prop_hmi.o:win_input_password_prop.c
	echo "编译窗口:win_input_password 动态属性(HMI)"
	$(HMICC)  $(CFLAGS) -D_LINUX  -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp  -O2 -fPIC -I$(INCLUDE) -I$(SYS_HMI_INCLUDE)  -o win_input_password_prop_hmi.o -c win_input_password_prop.c

win_input_password_event_hmi.o:win_input_password_event.c
	echo "编译窗口:win_input_password 事件(HMI)"
	$(HMICC)  $(CFLAGS) -D_LINUX  -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp  -O2 -fPIC -I$(INCLUDE) -I$(SYS_HMI_INCLUDE) -o win_input_password_event_hmi.o -c win_input_password_event.c

win_admin_prop_hmi.o:win_admin_prop.c
	echo "编译窗口:win_admin 动态属性(HMI)"
	$(HMICC)  $(CFLAGS) -D_LINUX  -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp  -O2 -fPIC -I$(INCLUDE) -I$(SYS_HMI_INCLUDE)  -o win_admin_prop_hmi.o -c win_admin_prop.c

win_admin_event_hmi.o:win_admin_event.c
	echo "编译窗口:win_admin 事件(HMI)"
	$(HMICC)  $(CFLAGS) -D_LINUX  -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp  -O2 -fPIC -I$(INCLUDE) -I$(SYS_HMI_INCLUDE) -o win_admin_event_hmi.o -c win_admin_event.c

TextKeyboard6_prop_hmi.o:TextKeyboard6_prop.c
	echo "编译窗口:TextKeyboard6 动态属性(HMI)"
	$(HMICC)  $(CFLAGS) -D_LINUX  -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp  -O2 -fPIC -I$(INCLUDE) -I$(SYS_HMI_INCLUDE)  -o TextKeyboard6_prop_hmi.o -c TextKeyboard6_prop.c

TextKeyboard6_event_hmi.o:TextKeyboard6_event.c
	echo "编译窗口:TextKeyboard6 事件(HMI)"
	$(HMICC)  $(CFLAGS) -D_LINUX  -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp  -O2 -fPIC -I$(INCLUDE) -I$(SYS_HMI_INCLUDE) -o TextKeyboard6_event_hmi.o -c TextKeyboard6_event.c

win_cabinet_set_prop_hmi.o:win_cabinet_set_prop.c
	echo "编译窗口:win_cabinet_set 动态属性(HMI)"
	$(HMICC)  $(CFLAGS) -D_LINUX  -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp  -O2 -fPIC -I$(INCLUDE) -I$(SYS_HMI_INCLUDE)  -o win_cabinet_set_prop_hmi.o -c win_cabinet_set_prop.c

win_cabinet_set_event_hmi.o:win_cabinet_set_event.c
	echo "编译窗口:win_cabinet_set 事件(HMI)"
	$(HMICC)  $(CFLAGS) -D_LINUX  -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp  -O2 -fPIC -I$(INCLUDE) -I$(SYS_HMI_INCLUDE) -o win_cabinet_set_event_hmi.o -c win_cabinet_set_event.c

win_tip_prop_hmi.o:win_tip_prop.c
	echo "编译窗口:win_tip 动态属性(HMI)"
	$(HMICC)  $(CFLAGS) -D_LINUX  -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp  -O2 -fPIC -I$(INCLUDE) -I$(SYS_HMI_INCLUDE)  -o win_tip_prop_hmi.o -c win_tip_prop.c

win_tip_event_hmi.o:win_tip_event.c
	echo "编译窗口:win_tip 事件(HMI)"
	$(HMICC)  $(CFLAGS) -D_LINUX  -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp  -O2 -fPIC -I$(INCLUDE) -I$(SYS_HMI_INCLUDE) -o win_tip_event_hmi.o -c win_tip_event.c

win_box_set_prop_hmi.o:win_box_set_prop.c
	echo "编译窗口:win_box_set 动态属性(HMI)"
	$(HMICC)  $(CFLAGS) -D_LINUX  -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp  -O2 -fPIC -I$(INCLUDE) -I$(SYS_HMI_INCLUDE)  -o win_box_set_prop_hmi.o -c win_box_set_prop.c

win_box_set_event_hmi.o:win_box_set_event.c
	echo "编译窗口:win_box_set 事件(HMI)"
	$(HMICC)  $(CFLAGS) -D_LINUX  -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp  -O2 -fPIC -I$(INCLUDE) -I$(SYS_HMI_INCLUDE) -o win_box_set_event_hmi.o -c win_box_set_event.c

win_box_operate_prop_hmi.o:win_box_operate_prop.c
	echo "编译窗口:win_box_operate 动态属性(HMI)"
	$(HMICC)  $(CFLAGS) -D_LINUX  -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp  -O2 -fPIC -I$(INCLUDE) -I$(SYS_HMI_INCLUDE)  -o win_box_operate_prop_hmi.o -c win_box_operate_prop.c

win_box_operate_event_hmi.o:win_box_operate_event.c
	echo "编译窗口:win_box_operate 事件(HMI)"
	$(HMICC)  $(CFLAGS) -D_LINUX  -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp  -O2 -fPIC -I$(INCLUDE) -I$(SYS_HMI_INCLUDE) -o win_box_operate_event_hmi.o -c win_box_operate_event.c

win_sender_psd_prop_hmi.o:win_sender_psd_prop.c
	echo "编译窗口:win_sender_psd 动态属性(HMI)"
	$(HMICC)  $(CFLAGS) -D_LINUX  -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp  -O2 -fPIC -I$(INCLUDE) -I$(SYS_HMI_INCLUDE)  -o win_sender_psd_prop_hmi.o -c win_sender_psd_prop.c

win_sender_psd_event_hmi.o:win_sender_psd_event.c
	echo "编译窗口:win_sender_psd 事件(HMI)"
	$(HMICC)  $(CFLAGS) -D_LINUX  -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp  -O2 -fPIC -I$(INCLUDE) -I$(SYS_HMI_INCLUDE) -o win_sender_psd_event_hmi.o -c win_sender_psd_event.c

win_wait_tip_prop_hmi.o:win_wait_tip_prop.c
	echo "编译窗口:win_wait_tip 动态属性(HMI)"
	$(HMICC)  $(CFLAGS) -D_LINUX  -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp  -O2 -fPIC -I$(INCLUDE) -I$(SYS_HMI_INCLUDE)  -o win_wait_tip_prop_hmi.o -c win_wait_tip_prop.c

win_wait_tip_event_hmi.o:win_wait_tip_event.c
	echo "编译窗口:win_wait_tip 事件(HMI)"
	$(HMICC)  $(CFLAGS) -D_LINUX  -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp  -O2 -fPIC -I$(INCLUDE) -I$(SYS_HMI_INCLUDE) -o win_wait_tip_event_hmi.o -c win_wait_tip_event.c

win_input_send_tm_prop_hmi.o:win_input_send_tm_prop.c
	echo "编译窗口:win_input_send_tm 动态属性(HMI)"
	$(HMICC)  $(CFLAGS) -D_LINUX  -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp  -O2 -fPIC -I$(INCLUDE) -I$(SYS_HMI_INCLUDE)  -o win_input_send_tm_prop_hmi.o -c win_input_send_tm_prop.c

win_input_send_tm_event_hmi.o:win_input_send_tm_event.c
	echo "编译窗口:win_input_send_tm 事件(HMI)"
	$(HMICC)  $(CFLAGS) -D_LINUX  -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp  -O2 -fPIC -I$(INCLUDE) -I$(SYS_HMI_INCLUDE) -o win_input_send_tm_event_hmi.o -c win_input_send_tm_event.c

win_input_pnum_type_prop_hmi.o:win_input_pnum_type_prop.c
	echo "编译窗口:win_input_pnum_type 动态属性(HMI)"
	$(HMICC)  $(CFLAGS) -D_LINUX  -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp  -O2 -fPIC -I$(INCLUDE) -I$(SYS_HMI_INCLUDE)  -o win_input_pnum_type_prop_hmi.o -c win_input_pnum_type_prop.c

win_input_pnum_type_event_hmi.o:win_input_pnum_type_event.c
	echo "编译窗口:win_input_pnum_type 事件(HMI)"
	$(HMICC)  $(CFLAGS) -D_LINUX  -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp  -O2 -fPIC -I$(INCLUDE) -I$(SYS_HMI_INCLUDE) -o win_input_pnum_type_event_hmi.o -c win_input_pnum_type_event.c

win_save_pack_next_tip_prop_hmi.o:win_save_pack_next_tip_prop.c
	echo "编译窗口:win_save_pack_next_tip 动态属性(HMI)"
	$(HMICC)  $(CFLAGS) -D_LINUX  -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp  -O2 -fPIC -I$(INCLUDE) -I$(SYS_HMI_INCLUDE)  -o win_save_pack_next_tip_prop_hmi.o -c win_save_pack_next_tip_prop.c

win_save_pack_next_tip_event_hmi.o:win_save_pack_next_tip_event.c
	echo "编译窗口:win_save_pack_next_tip 事件(HMI)"
	$(HMICC)  $(CFLAGS) -D_LINUX  -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp  -O2 -fPIC -I$(INCLUDE) -I$(SYS_HMI_INCLUDE) -o win_save_pack_next_tip_event_hmi.o -c win_save_pack_next_tip_event.c

NumKeyboard3_prop_hmi.o:NumKeyboard3_prop.c
	echo "编译窗口:NumKeyboard3 动态属性(HMI)"
	$(HMICC)  $(CFLAGS) -D_LINUX  -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp  -O2 -fPIC -I$(INCLUDE) -I$(SYS_HMI_INCLUDE)  -o NumKeyboard3_prop_hmi.o -c NumKeyboard3_prop.c

NumKeyboard3_event_hmi.o:NumKeyboard3_event.c
	echo "编译窗口:NumKeyboard3 事件(HMI)"
	$(HMICC)  $(CFLAGS) -D_LINUX  -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp  -O2 -fPIC -I$(INCLUDE) -I$(SYS_HMI_INCLUDE) -o NumKeyboard3_event_hmi.o -c NumKeyboard3_event.c

win_sys_set_prop_hmi.o:win_sys_set_prop.c
	echo "编译窗口:win_sys_set 动态属性(HMI)"
	$(HMICC)  $(CFLAGS) -D_LINUX  -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp  -O2 -fPIC -I$(INCLUDE) -I$(SYS_HMI_INCLUDE)  -o win_sys_set_prop_hmi.o -c win_sys_set_prop.c

win_sys_set_event_hmi.o:win_sys_set_event.c
	echo "编译窗口:win_sys_set 事件(HMI)"
	$(HMICC)  $(CFLAGS) -D_LINUX  -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp  -O2 -fPIC -I$(INCLUDE) -I$(SYS_HMI_INCLUDE) -o win_sys_set_event_hmi.o -c win_sys_set_event.c

win_change_admin_psd_prop_hmi.o:win_change_admin_psd_prop.c
	echo "编译窗口:win_change_admin_psd 动态属性(HMI)"
	$(HMICC)  $(CFLAGS) -D_LINUX  -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp  -O2 -fPIC -I$(INCLUDE) -I$(SYS_HMI_INCLUDE)  -o win_change_admin_psd_prop_hmi.o -c win_change_admin_psd_prop.c

win_change_admin_psd_event_hmi.o:win_change_admin_psd_event.c
	echo "编译窗口:win_change_admin_psd 事件(HMI)"
	$(HMICC)  $(CFLAGS) -D_LINUX  -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp  -O2 -fPIC -I$(INCLUDE) -I$(SYS_HMI_INCLUDE) -o win_change_admin_psd_event_hmi.o -c win_change_admin_psd_event.c

win_sys_set_time_prop_hmi.o:win_sys_set_time_prop.c
	echo "编译窗口:win_sys_set_time 动态属性(HMI)"
	$(HMICC)  $(CFLAGS) -D_LINUX  -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp  -O2 -fPIC -I$(INCLUDE) -I$(SYS_HMI_INCLUDE)  -o win_sys_set_time_prop_hmi.o -c win_sys_set_time_prop.c

win_sys_set_time_event_hmi.o:win_sys_set_time_event.c
	echo "编译窗口:win_sys_set_time 事件(HMI)"
	$(HMICC)  $(CFLAGS) -D_LINUX  -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp  -O2 -fPIC -I$(INCLUDE) -I$(SYS_HMI_INCLUDE) -o win_sys_set_time_event_hmi.o -c win_sys_set_time_event.c

win_sys_reset_prop_hmi.o:win_sys_reset_prop.c
	echo "编译窗口:win_sys_reset 动态属性(HMI)"
	$(HMICC)  $(CFLAGS) -D_LINUX  -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp  -O2 -fPIC -I$(INCLUDE) -I$(SYS_HMI_INCLUDE)  -o win_sys_reset_prop_hmi.o -c win_sys_reset_prop.c

win_sys_reset_event_hmi.o:win_sys_reset_event.c
	echo "编译窗口:win_sys_reset 事件(HMI)"
	$(HMICC)  $(CFLAGS) -D_LINUX  -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp  -O2 -fPIC -I$(INCLUDE) -I$(SYS_HMI_INCLUDE) -o win_sys_reset_event_hmi.o -c win_sys_reset_event.c

win_ad_prop_hmi.o:win_ad_prop.c
	echo "编译窗口:win_ad 动态属性(HMI)"
	$(HMICC)  $(CFLAGS) -D_LINUX  -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp  -O2 -fPIC -I$(INCLUDE) -I$(SYS_HMI_INCLUDE)  -o win_ad_prop_hmi.o -c win_ad_prop.c

win_ad_event_hmi.o:win_ad_event.c
	echo "编译窗口:win_ad 事件(HMI)"
	$(HMICC)  $(CFLAGS) -D_LINUX  -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp  -O2 -fPIC -I$(INCLUDE) -I$(SYS_HMI_INCLUDE) -o win_ad_event_hmi.o -c win_ad_event.c

win_disp_box_status_prop_hmi.o:win_disp_box_status_prop.c
	echo "编译窗口:win_disp_box_status 动态属性(HMI)"
	$(HMICC)  $(CFLAGS) -D_LINUX  -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp  -O2 -fPIC -I$(INCLUDE) -I$(SYS_HMI_INCLUDE)  -o win_disp_box_status_prop_hmi.o -c win_disp_box_status_prop.c

win_disp_box_status_event_hmi.o:win_disp_box_status_event.c
	echo "编译窗口:win_disp_box_status 事件(HMI)"
	$(HMICC)  $(CFLAGS) -D_LINUX  -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp  -O2 -fPIC -I$(INCLUDE) -I$(SYS_HMI_INCLUDE) -o win_disp_box_status_event_hmi.o -c win_disp_box_status_event.c

win_history_prop_hmi.o:win_history_prop.c
	echo "编译窗口:win_history 动态属性(HMI)"
	$(HMICC)  $(CFLAGS) -D_LINUX  -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp  -O2 -fPIC -I$(INCLUDE) -I$(SYS_HMI_INCLUDE)  -o win_history_prop_hmi.o -c win_history_prop.c

win_history_event_hmi.o:win_history_event.c
	echo "编译窗口:win_history 事件(HMI)"
	$(HMICC)  $(CFLAGS) -D_LINUX  -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp  -O2 -fPIC -I$(INCLUDE) -I$(SYS_HMI_INCLUDE) -o win_history_event_hmi.o -c win_history_event.c

win_history_detail_prop_hmi.o:win_history_detail_prop.c
	echo "编译窗口:win_history_detail 动态属性(HMI)"
	$(HMICC)  $(CFLAGS) -D_LINUX  -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp  -O2 -fPIC -I$(INCLUDE) -I$(SYS_HMI_INCLUDE)  -o win_history_detail_prop_hmi.o -c win_history_detail_prop.c

win_history_detail_event_hmi.o:win_history_detail_event.c
	echo "编译窗口:win_history_detail 事件(HMI)"
	$(HMICC)  $(CFLAGS) -D_LINUX  -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp  -O2 -fPIC -I$(INCLUDE) -I$(SYS_HMI_INCLUDE) -o win_history_detail_event_hmi.o -c win_history_detail_event.c

__external_c_hmi.a:__external_c_hmi_file0.o __external_c_hmi_file1.o __external_c_hmi_file2.o 
	rm -f __external_c_hmi.a 
	$(HMIAR) rcs __external_c_hmi.a __external_c_hmi_file0.o __external_c_hmi_file1.o __external_c_hmi_file2.o 

__external_c_hmi_file0.o:D:/SProgram\ Files/LinCon/project/hkfl_5/hkfl\src\GPRS.c
	echo "编译源文件(HMI):D:/SProgram\ Files/LinCon/project/hkfl_5/hkfl\src\GPRS.c"
	$(HMICC) $(CFLAGS) -D_LINUX  -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp  -O2 -fPIC -I$(INCLUDE) -I$(SYS_HMI_INCLUDE) -o __external_c_hmi_file0.o -c D:/SProgram\ Files/LinCon/project/hkfl_5/hkfl\src\GPRS.c

__external_c_hmi_file1.o:D:/SProgram\ Files/LinCon/project/hkfl_5/hkfl\src\user_function.c
	echo "编译源文件(HMI):D:/SProgram\ Files/LinCon/project/hkfl_5/hkfl\src\user_function.c"
	$(HMICC) $(CFLAGS) -D_LINUX  -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp  -O2 -fPIC -I$(INCLUDE) -I$(SYS_HMI_INCLUDE) -o __external_c_hmi_file1.o -c D:/SProgram\ Files/LinCon/project/hkfl_5/hkfl\src\user_function.c

__external_c_hmi_file2.o:D:/SProgram\ Files/LinCon/project/hkfl_5/hkfl\src\box_info.c
	echo "编译源文件(HMI):D:/SProgram\ Files/LinCon/project/hkfl_5/hkfl\src\box_info.c"
	$(HMICC) $(CFLAGS) -D_LINUX  -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp  -O2 -fPIC -I$(INCLUDE) -I$(SYS_HMI_INCLUDE) -o __external_c_hmi_file2.o -c D:/SProgram\ Files/LinCon/project/hkfl_5/hkfl\src\box_info.c

