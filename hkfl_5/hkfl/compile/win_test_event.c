/*
 * This file is automatically generated by func_gen.c,don't edit
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lincon.h"
#include "linconhmi.h"
#include "userfunc.h"

#ifndef HMI_GEN_FUNC_FILE
static void widget_button_3_click(void);
static void widget_button_5_click(void);
static void widget_button_click(void);
static void widget_window_open(void);

hmi_widget_func_t hmi_window_77696E5F74657374_event_funcs[]={
{"button_3_click",(void *)widget_button_3_click},
{"button_5_click",(void *)widget_button_5_click},
{"button_click",(void *)widget_button_click},
{"window_open",(void *)widget_window_open},
{NULL,NULL}
};

static void widget_button_3_click(void)
{
	{
#line 1 "�ؼ�:button_3,�¼�:click"
sys_shutdown(3);

	}
{
}
}

static void widget_button_5_click(void)
{
	{
#line 1 "�ؼ�:button_5,�¼�:click"
hmi_window_hide("win_test");
hmi_window_hide("win_box_tip");

	}
{
}
}

static void widget_button_click(void)
{
	u8 __hmi_var_8 = (*(u8 *)hmidb_get_data_value("test_parm.station_num"));
	u8 __old___hmi_var_8 = __hmi_var_8;
	u8 __hmi_var_9 = (*(u8 *)hmidb_get_data_value("test_parm.station_port"));
	u8 __old___hmi_var_9 = __hmi_var_9;
	char * __hmi_var_10 = ((char *)hmidb_get_data_value("test_parm.virtualnumber"));
		char * __hmi_var_11 = ((char *)hmidb_get_data_value("test_parm.type"));
		char * __hmi_var_12 = ((char *)hmidb_get_data_value("test_parm.status"));
		char * __hmi_var_13 = ((char *)hmidb_get_data_value("test_parm.user_id"));
		char * __hmi_var_14 = ((char *)hmidb_get_data_value("test_parm.user_phnum"));
		char * __hmi_var_15 = ((char *)hmidb_get_data_value("test_parm.pass_word"));
		char * __hmi_var_16 = ((char *)hmidb_get_data_value("test_parm.send_num"));
		char * __hmi_var_17 = ((char *)hmidb_get_data_value("test_parm.send_id"));
		{
#line 1 "�ؼ�:button,�¼�:click"
BOX_MSG box_info;
if(1 == read_box_info_station_num(__hmi_var_8 , &box_info))
{
    __hmi_var_9 = box_info.station_port;
    memcpy(__hmi_var_10 , box_info.virtualnumber , 4);
    memcpy(__hmi_var_11,&box_info.type,1);
    memcpy(__hmi_var_12,&box_info.status,1);

    memcpy(__hmi_var_13,box_info.user_id,USERID_LENGTH);
    memcpy(__hmi_var_14,box_info.user_phnum,USER_PHNUM_LENGTH);
    memcpy(__hmi_var_15,box_info.pass_word,USER_PASSWORD_LENGTH);
    memcpy(__hmi_var_16,box_info.send_num,SEND_NUM_LENGTH);
    memcpy(__hmi_var_17,box_info.send_id,SENDID_LENGTH);
}




	}
{
		hmidb_set_data_value("test_parm.send_id",__hmi_var_17);
		hmidb_set_data_value("test_parm.send_num",__hmi_var_16);
		hmidb_set_data_value("test_parm.pass_word",__hmi_var_15);
		hmidb_set_data_value("test_parm.user_phnum",__hmi_var_14);
		hmidb_set_data_value("test_parm.user_id",__hmi_var_13);
		hmidb_set_data_value("test_parm.status",__hmi_var_12);
		hmidb_set_data_value("test_parm.type",__hmi_var_11);
		hmidb_set_data_value("test_parm.virtualnumber",__hmi_var_10);
	if(__old___hmi_var_9 != __hmi_var_9)
	{
		hmidb_set_data_value("test_parm.station_port",&__hmi_var_9);
	}
	if(__old___hmi_var_8 != __hmi_var_8)
	{
		hmidb_set_data_value("test_parm.station_num",&__hmi_var_8);
	}
}
}

static void widget_window_open(void)
{
	u16 __hmi_var_18 = (*(u16 *)hmidb_get_data_value("ARM_info.send_id_flag"));
	u16 __old___hmi_var_18 = __hmi_var_18;
	char * __hmi_var_19 = ((char *)hmidb_get_data_value("test_parm.recv_buf"));
		{
#line 1 "�ؼ�:window,�¼�:open"
__hmi_var_18 = 0;
memset(__hmi_var_19 , 0 , 30);

	}
{
		hmidb_set_data_value("test_parm.recv_buf",__hmi_var_19);
	if(__old___hmi_var_18 != __hmi_var_18)
	{
		hmidb_set_data_value("ARM_info.send_id_flag",&__hmi_var_18);
	}
}
}

#endif