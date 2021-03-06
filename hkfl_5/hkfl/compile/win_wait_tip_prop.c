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
static int widget_set_button_visible(void *value);
static int widget_set_button_enable(void *value);
static int widget_set_text_text(void *value);

hmi_widget_func_t hmi_window_77696E5F776169745F746970_prop_funcs[]={
{"button_visible",(void *)widget_set_button_visible},
{"button_enable",(void *)widget_set_button_enable},
{"text_text",(void *)widget_set_text_text},
{NULL,NULL}
};

static int widget_set_button_visible(void *value)
{
	static void *__hmi_var_18_ptr;
	u8 __hmi_var_18 = (*(u8 *)hmidb_get_data_value_by_ptr("picture_ctrl.win_wait_sw",&__hmi_var_18_ptr));
#line 1 "控件:button,属性:visible"
	u8 __hmi_retval = (u8)(__hmi_var_18);
	if (__hmi_retval != (*(u8 *)value))
	{
		(*(u8 *)value) = __hmi_retval;
		return 1;
	}
	return 0;
}

static int widget_set_button_enable(void *value)
{
	static void *__hmi_var_19_ptr;
	u8 __hmi_var_19 = (*(u8 *)hmidb_get_data_value_by_ptr("picture_ctrl.win_wait_sw",&__hmi_var_19_ptr));
#line 1 "控件:button,属性:enable"
	u8 __hmi_retval = (u8)(__hmi_var_19);
	if (__hmi_retval != (*(u8 *)value))
	{
		(*(u8 *)value) = __hmi_retval;
		return 1;
	}
	return 0;
}

static int widget_set_text_text(void *value)
{
	static void *__hmi_var_20_ptr;
	char * __hmi_var_20 = ((char *)hmidb_get_data_value_by_ptr("picture_ctrl.win_wait_tip",&__hmi_var_20_ptr));
#line 1 "控件:text,属性:text"
	char * __hmi_retval = (char *)(__hmi_var_20);
	if ( strcmp(__hmi_retval, (char *)value))
	{
		strncpy(value,__hmi_retval,32);
		((char *)value)[32-1]=0;
		return 1;
	}
	return 0;
}

#endif
