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
static void widget_button_2_click(void);
static void widget_button_click(void);
static void widget_button_12_click(void);
static void widget_window_open(void);

hmi_widget_func_t hmi_window_77696E5F646973705F626F785F737461747573_event_funcs[]={
{"button_2_click",(void *)widget_button_2_click},
{"button_click",(void *)widget_button_click},
{"button_12_click",(void *)widget_button_12_click},
{"window_open",(void *)widget_window_open},
{NULL,NULL}
};

static void widget_button_2_click(void)
{
	u8 __hmi_var_4 = (*(u8 *)hmidb_get_data_value("picture_ctrl.page_count"));
	u8 __old___hmi_var_4 = __hmi_var_4;
	{
#line 1 "控件:button_2,事件:click"
__hmi_var_4++;

	}
{
	if(__old___hmi_var_4 != __hmi_var_4)
	{
		hmidb_set_data_value("picture_ctrl.page_count",&__hmi_var_4);
	}
}
}

static void widget_button_click(void)
{
	u8 __hmi_var_7 = (*(u8 *)hmidb_get_data_value("picture_ctrl.page_count"));
	u8 __old___hmi_var_7 = __hmi_var_7;
	{
#line 1 "控件:button,事件:click"
__hmi_var_7--;

	}
{
	if(__old___hmi_var_7 != __hmi_var_7)
	{
		hmidb_set_data_value("picture_ctrl.page_count",&__hmi_var_7);
	}
}
}

static void widget_button_12_click(void)
{
	{
#line 1 "控件:button_12,事件:click"
hmi_window_hide("win_disp_box_status");
	}
{
}
}

static void widget_window_open(void)
{
	u8 __hmi_var_190 = (*(u8 *)hmidb_get_data_value("picture_ctrl.page_count"));
	u8 __old___hmi_var_190 = __hmi_var_190;
	{
#line 1 "控件:window,事件:open"
__hmi_var_190 = 0;


	}
{
	if(__old___hmi_var_190 != __hmi_var_190)
	{
		hmidb_set_data_value("picture_ctrl.page_count",&__hmi_var_190);
	}
}
}

#endif
