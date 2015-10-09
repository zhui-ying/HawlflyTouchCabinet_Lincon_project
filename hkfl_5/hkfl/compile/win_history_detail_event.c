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
static void widget_button_16_click(void);
static void widget_window_open(void);

hmi_widget_func_t hmi_window_77696E5F686973746F72795F64657461696C_event_funcs[]={
{"button_16_click",(void *)widget_button_16_click},
{"window_open",(void *)widget_window_open},
{NULL,NULL}
};

static void widget_button_16_click(void)
{
	{
#line 1 "控件:button_16,事件:click"
hmi_window_hide("win_history_detail");
	}
{
}
}

static void widget_window_open(void)
{
	u8 __hmi_var_143 = (*(u8 *)hmidb_get_data_value("picture_ctrl.history_detail_index"));
	u8 __old___hmi_var_143 = __hmi_var_143;
	char __hmi_var_144 = (*(char *)hmidb_get_data_value("box_msg.type"));
	char __old___hmi_var_144 = __hmi_var_144;
	char __hmi_var_145 = (*(char *)hmidb_get_data_value("box_msg.status"));
	char __old___hmi_var_145 = __hmi_var_145;
	char * __hmi_var_146 = ((char *)hmidb_get_data_value("box_msg.virtualnumber"));
		char * __hmi_var_147 = ((char *)hmidb_get_data_value("box_msg.user_id"));
		char * __hmi_var_148 = ((char *)hmidb_get_data_value("box_msg.user_phnum"));
		char * __hmi_var_149 = ((char *)hmidb_get_data_value("box_msg.send_num"));
		char * __hmi_var_150 = ((char *)hmidb_get_data_value("box_msg.send_id"));
		char * __hmi_var_151 = ((char *)hmidb_get_data_value("box_msg.timestr"));
		{
#line 1 "控件:window,事件:open"
u8 index;
HISTORY_MSG history_msg;
index = __hmi_var_143;
if(1 == read_history_info(index , &history_msg))
{
    __hmi_var_144 = history_msg.box_info.type;
    __hmi_var_145 = history_msg.box_info.status;
    memcpy(__hmi_var_146 , history_msg.box_info.virtualnumber , VIRTUAL_NUM_LENGTH);

    memcpy(__hmi_var_147,history_msg.box_info.user_id,USERID_LENGTH);
    memcpy(__hmi_var_148,history_msg.box_info.user_phnum,USER_PHNUM_LENGTH);

    memcpy(__hmi_var_149,history_msg.box_info.send_num,SEND_NUM_LENGTH);
    memcpy(__hmi_var_150,history_msg.box_info.send_id,SENDID_LENGTH);
    memcpy(__hmi_var_151 , datetime2str(history_msg.data_time)+5 , 11);//不显示年
}


	}
{
		hmidb_set_data_value("box_msg.timestr",__hmi_var_151);
		hmidb_set_data_value("box_msg.send_id",__hmi_var_150);
		hmidb_set_data_value("box_msg.send_num",__hmi_var_149);
		hmidb_set_data_value("box_msg.user_phnum",__hmi_var_148);
		hmidb_set_data_value("box_msg.user_id",__hmi_var_147);
		hmidb_set_data_value("box_msg.virtualnumber",__hmi_var_146);
	if(__old___hmi_var_145 != __hmi_var_145)
	{
		hmidb_set_data_value("box_msg.status",&__hmi_var_145);
	}
	if(__old___hmi_var_144 != __hmi_var_144)
	{
		hmidb_set_data_value("box_msg.type",&__hmi_var_144);
	}
	if(__old___hmi_var_143 != __hmi_var_143)
	{
		hmidb_set_data_value("picture_ctrl.history_detail_index",&__hmi_var_143);
	}
}
}

#endif
