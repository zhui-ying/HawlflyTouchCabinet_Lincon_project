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
static void widget_window_open(void);

hmi_widget_func_t hmi_window_4E756D4B6579626F61726433_event_funcs[]={
{"window_open",(void *)widget_window_open},
{NULL,NULL}
};

static void widget_window_open(void)
{
	char * __hmi_var_100 = ((char *)hmidb_get_data_value("syskeyboard.KeyboardBuffer"));
		{
#line 1 "�ؼ�:window,�¼�:open"
__hmi_var_100 = "\0";
	}
{
		hmidb_set_data_value("syskeyboard.KeyboardBuffer",__hmi_var_100);
}
}

#endif
