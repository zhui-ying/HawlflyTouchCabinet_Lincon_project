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
static int widget_set_button_5_font_color(void *value);
static int widget_set_button_4_font_color(void *value);
static int widget_set_button_3_font_color(void *value);

hmi_widget_func_t hmi_window_77696E5F696E7075745F706E756D5F74797065_prop_funcs[]={
{"button_5_font_color",(void *)widget_set_button_5_font_color},
{"button_4_font_color",(void *)widget_set_button_4_font_color},
{"button_3_font_color",(void *)widget_set_button_3_font_color},
{NULL,NULL}
};

static int widget_set_button_5_font_color(void *value)
{
	static void *__hmi_var_25_ptr;
	u8 __hmi_var_25 = (*(u8 *)hmidb_get_data_value_by_ptr("picture_ctrl.win_type_max",&__hmi_var_25_ptr));
#line 1 "控件:button_5,属性:font_color"
	u32 __hmi_retval = (u32)((__hmi_var_25)?0xff:0xffaaaa);
	if (__hmi_retval != (*(u32 *)value))
	{
		(*(u32 *)value) = __hmi_retval;
		return 1;
	}
	return 0;
}

static int widget_set_button_4_font_color(void *value)
{
	static void *__hmi_var_32_ptr;
	u8 __hmi_var_32 = (*(u8 *)hmidb_get_data_value_by_ptr("picture_ctrl.win_type_mid",&__hmi_var_32_ptr));
#line 1 "控件:button_4,属性:font_color"
	u32 __hmi_retval = (u32)((__hmi_var_32)?0xff:0xffaaaa);
	if (__hmi_retval != (*(u32 *)value))
	{
		(*(u32 *)value) = __hmi_retval;
		return 1;
	}
	return 0;
}

static int widget_set_button_3_font_color(void *value)
{
	static void *__hmi_var_39_ptr;
	u8 __hmi_var_39 = (*(u8 *)hmidb_get_data_value_by_ptr("picture_ctrl.win_type_min",&__hmi_var_39_ptr));
#line 1 "控件:button_3,属性:font_color"
	u32 __hmi_retval = (u32)((__hmi_var_39)?0x51cc7:0xffaaaa);
	if (__hmi_retval != (*(u32 *)value))
	{
		(*(u32 *)value) = __hmi_retval;
		return 1;
	}
	return 0;
}

#endif
