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
static int widget_set_mulpicture_index(void *value);

hmi_widget_func_t hmi_window_77696E5F6164_prop_funcs[]={
{"mulpicture_index",(void *)widget_set_mulpicture_index},
{NULL,NULL}
};

static int widget_set_mulpicture_index(void *value)
{
	static void *__hmi_var_106_ptr;
	u8 __hmi_var_106 = (*(u8 *)hmidb_get_data_value_by_ptr("picture_ctrl.win_ad_pic_ctrol_count",&__hmi_var_106_ptr));
#line 1 "�ؼ�:mulpicture,����:index"
	u8 __hmi_retval = (u8)(__hmi_var_106);
	if (__hmi_retval != (*(u8 *)value))
	{
		(*(u8 *)value) = __hmi_retval;
		return 1;
	}
	return 0;
}

#endif
