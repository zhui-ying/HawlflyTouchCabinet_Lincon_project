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
static int widget_set_text_13_visible(void *value);
static int widget_set_text_13_enable(void *value);
static int widget_set_text_13_text(void *value);
static int widget_set_text_29_visible(void *value);
static int widget_set_text_29_enable(void *value);
static int widget_set_text_29_text(void *value);
static int widget_set_text_12_visible(void *value);
static int widget_set_text_12_enable(void *value);
static int widget_set_text_12_text(void *value);
static int widget_set_text_11_visible(void *value);
static int widget_set_text_11_enable(void *value);
static int widget_set_text_11_text(void *value);
static int widget_set_text_28_visible(void *value);
static int widget_set_text_28_enable(void *value);
static int widget_set_text_28_text(void *value);
static int widget_set_text_10_visible(void *value);
static int widget_set_text_10_enable(void *value);
static int widget_set_text_10_text(void *value);
static int widget_set_text_8_visible(void *value);
static int widget_set_text_8_enable(void *value);
static int widget_set_text_8_text(void *value);
static int widget_set_text_27_visible(void *value);
static int widget_set_text_27_enable(void *value);
static int widget_set_text_27_text(void *value);
static int widget_set_text_7_visible(void *value);
static int widget_set_text_7_enable(void *value);
static int widget_set_text_7_text(void *value);
static int widget_set_text_25_visible(void *value);
static int widget_set_text_25_enable(void *value);
static int widget_set_text_25_text(void *value);
static int widget_set_button_2_visible(void *value);
static int widget_set_button_2_enable(void *value);
static int widget_set_button_visible(void *value);
static int widget_set_button_enable(void *value);
static int widget_set_text_6_visible(void *value);
static int widget_set_text_6_enable(void *value);
static int widget_set_text_6_text(void *value);
static int widget_set_text_5_visible(void *value);
static int widget_set_text_5_enable(void *value);
static int widget_set_text_5_text(void *value);

hmi_widget_func_t hmi_window_7465737431_prop_funcs[]={
{"text_13_visible",(void *)widget_set_text_13_visible},
{"text_13_enable",(void *)widget_set_text_13_enable},
{"text_13_text",(void *)widget_set_text_13_text},
{"text_29_visible",(void *)widget_set_text_29_visible},
{"text_29_enable",(void *)widget_set_text_29_enable},
{"text_29_text",(void *)widget_set_text_29_text},
{"text_12_visible",(void *)widget_set_text_12_visible},
{"text_12_enable",(void *)widget_set_text_12_enable},
{"text_12_text",(void *)widget_set_text_12_text},
{"text_11_visible",(void *)widget_set_text_11_visible},
{"text_11_enable",(void *)widget_set_text_11_enable},
{"text_11_text",(void *)widget_set_text_11_text},
{"text_28_visible",(void *)widget_set_text_28_visible},
{"text_28_enable",(void *)widget_set_text_28_enable},
{"text_28_text",(void *)widget_set_text_28_text},
{"text_10_visible",(void *)widget_set_text_10_visible},
{"text_10_enable",(void *)widget_set_text_10_enable},
{"text_10_text",(void *)widget_set_text_10_text},
{"text_8_visible",(void *)widget_set_text_8_visible},
{"text_8_enable",(void *)widget_set_text_8_enable},
{"text_8_text",(void *)widget_set_text_8_text},
{"text_27_visible",(void *)widget_set_text_27_visible},
{"text_27_enable",(void *)widget_set_text_27_enable},
{"text_27_text",(void *)widget_set_text_27_text},
{"text_7_visible",(void *)widget_set_text_7_visible},
{"text_7_enable",(void *)widget_set_text_7_enable},
{"text_7_text",(void *)widget_set_text_7_text},
{"text_25_visible",(void *)widget_set_text_25_visible},
{"text_25_enable",(void *)widget_set_text_25_enable},
{"text_25_text",(void *)widget_set_text_25_text},
{"button_2_visible",(void *)widget_set_button_2_visible},
{"button_2_enable",(void *)widget_set_button_2_enable},
{"button_visible",(void *)widget_set_button_visible},
{"button_enable",(void *)widget_set_button_enable},
{"text_6_visible",(void *)widget_set_text_6_visible},
{"text_6_enable",(void *)widget_set_text_6_enable},
{"text_6_text",(void *)widget_set_text_6_text},
{"text_5_visible",(void *)widget_set_text_5_visible},
{"text_5_enable",(void *)widget_set_text_5_enable},
{"text_5_text",(void *)widget_set_text_5_text},
{NULL,NULL}
};

static u8 widget_set_text_13_visible__()
{
	static void *__hmi_var_190_ptr;
	u8 __hmi_var_190 = (*(u8 *)hmidb_get_data_value_by_ptr("picture_ctrl.page_count",&__hmi_var_190_ptr));
	static void *__hmi_var_191_ptr;
	u8 __hmi_var_191 = (*(u8 *)hmidb_get_data_value_by_ptr("sys_set.box_num",&__hmi_var_191_ptr));
	{
#line 1 "控件:text_13,属性:visible"
if((__hmi_var_190*8 + 4) > __hmi_var_191)//箱子编号大于箱子总数
{
    return 0;//不显示
}
return 1;

	}
}

static int widget_set_text_13_visible(void *value)
{
	u8 __hmi_retval = (u8)( widget_set_text_13_visible__());
	if (__hmi_retval != (*(u8 *)value))
	{
		(*(u8 *)value) = __hmi_retval;
		return 1;
	}
	return 0;
}

static u8 widget_set_text_13_enable__()
{
	static void *__hmi_var_192_ptr;
	u8 __hmi_var_192 = (*(u8 *)hmidb_get_data_value_by_ptr("picture_ctrl.page_count",&__hmi_var_192_ptr));
	static void *__hmi_var_193_ptr;
	u8 __hmi_var_193 = (*(u8 *)hmidb_get_data_value_by_ptr("sys_set.box_num",&__hmi_var_193_ptr));
	{
#line 1 "控件:text_13,属性:enable"
if((__hmi_var_192*8 + 4) > __hmi_var_193)//箱子编号大于箱子总数
{
    return 0;//不显示
}
return 1;

	}
}

static int widget_set_text_13_enable(void *value)
{
	u8 __hmi_retval = (u8)( widget_set_text_13_enable__());
	if (__hmi_retval != (*(u8 *)value))
	{
		(*(u8 *)value) = __hmi_retval;
		return 1;
	}
	return 0;
}

static char * widget_set_text_13_text__()
{
	static void *__hmi_var_194_ptr;
	u8 __hmi_var_194 = (*(u8 *)hmidb_get_data_value_by_ptr("picture_ctrl.page_count",&__hmi_var_194_ptr));
	static void *__hmi_var_195_ptr;
	char * __hmi_var_195 = ((char *)hmidb_get_data_value_by_ptr("picture_ctrl.box_idle",&__hmi_var_195_ptr));
	static void *__hmi_var_196_ptr;
	char * __hmi_var_196 = ((char *)hmidb_get_data_value_by_ptr("picture_ctrl.box_use",&__hmi_var_196_ptr));
	static void *__hmi_var_197_ptr;
	char * __hmi_var_197 = ((char *)hmidb_get_data_value_by_ptr("picture_ctrl.box_lock",&__hmi_var_197_ptr));
	static void *__hmi_var_198_ptr;
	char * __hmi_var_198 = ((char *)hmidb_get_data_value_by_ptr("picture_ctrl.box_err",&__hmi_var_198_ptr));
	{
#line 1 "控件:text_13,属性:text"
u8 box_index;
BOX_MSG box_info;

box_index = __hmi_var_194*8 + 4;
read_box_info_station_num(box_index , &box_info);
if(box_info.status == BOX_IDLE)
{
    return __hmi_var_195;
}
if(box_info.status == BOX_USED)
{
    return __hmi_var_196;
}
if(box_info.status == BOX_LOCK)
{
    return __hmi_var_197;
}
return __hmi_var_198;

	}
}

static int widget_set_text_13_text(void *value)
{
	char * __hmi_retval = (char *)( widget_set_text_13_text__());
	if ( strcmp(__hmi_retval, (char *)value))
	{
		strncpy(value,__hmi_retval,32);
		((char *)value)[32-1]=0;
		return 1;
	}
	return 0;
}

static u8 widget_set_text_29_visible__()
{
	static void *__hmi_var_199_ptr;
	u8 __hmi_var_199 = (*(u8 *)hmidb_get_data_value_by_ptr("picture_ctrl.page_count",&__hmi_var_199_ptr));
	static void *__hmi_var_200_ptr;
	u8 __hmi_var_200 = (*(u8 *)hmidb_get_data_value_by_ptr("sys_set.box_num",&__hmi_var_200_ptr));
	{
#line 1 "控件:text_29,属性:visible"
if((__hmi_var_199*8 + 4) > __hmi_var_200)//箱子编号大于箱子总数
{
    return 0;//不显示
}
return 1;

	}
}

static int widget_set_text_29_visible(void *value)
{
	u8 __hmi_retval = (u8)( widget_set_text_29_visible__());
	if (__hmi_retval != (*(u8 *)value))
	{
		(*(u8 *)value) = __hmi_retval;
		return 1;
	}
	return 0;
}

static u8 widget_set_text_29_enable__()
{
	static void *__hmi_var_201_ptr;
	u8 __hmi_var_201 = (*(u8 *)hmidb_get_data_value_by_ptr("picture_ctrl.page_count",&__hmi_var_201_ptr));
	static void *__hmi_var_202_ptr;
	u8 __hmi_var_202 = (*(u8 *)hmidb_get_data_value_by_ptr("sys_set.box_num",&__hmi_var_202_ptr));
	{
#line 1 "控件:text_29,属性:enable"
if((__hmi_var_201*8 + 4) > __hmi_var_202)//箱子编号大于箱子总数
{
    return 0;//不显示
}
return 1;

	}
}

static int widget_set_text_29_enable(void *value)
{
	u8 __hmi_retval = (u8)( widget_set_text_29_enable__());
	if (__hmi_retval != (*(u8 *)value))
	{
		(*(u8 *)value) = __hmi_retval;
		return 1;
	}
	return 0;
}

static char * widget_set_text_29_text__()
{
	static void *__hmi_var_203_ptr;
	u8 __hmi_var_203 = (*(u8 *)hmidb_get_data_value_by_ptr("picture_ctrl.page_count",&__hmi_var_203_ptr));
	static void *__hmi_var_204_ptr;
	char * __hmi_var_204 = ((char *)hmidb_get_data_value_by_ptr("picture_ctrl.box_min",&__hmi_var_204_ptr));
	static void *__hmi_var_205_ptr;
	char * __hmi_var_205 = ((char *)hmidb_get_data_value_by_ptr("picture_ctrl.box_mid",&__hmi_var_205_ptr));
	static void *__hmi_var_206_ptr;
	char * __hmi_var_206 = ((char *)hmidb_get_data_value_by_ptr("picture_ctrl.box_max",&__hmi_var_206_ptr));
	static void *__hmi_var_207_ptr;
	char * __hmi_var_207 = ((char *)hmidb_get_data_value_by_ptr("picture_ctrl.box_err",&__hmi_var_207_ptr));
	{
#line 1 "控件:text_29,属性:text"
u8 box_index;
BOX_MSG box_info;


box_index = __hmi_var_203*8 + 4;
read_box_info_station_num(box_index , &box_info);
if(box_info.type == BOX_TYPE_MIN)
{
    return __hmi_var_204;
}
if(box_info.type == BOX_TYPE_MID)
{
    return __hmi_var_205;
}
if(box_info.type == BOX_TYPE_MAX)
{
    return __hmi_var_206;
}
return __hmi_var_207;

	}
}

static int widget_set_text_29_text(void *value)
{
	char * __hmi_retval = (char *)( widget_set_text_29_text__());
	if ( strcmp(__hmi_retval, (char *)value))
	{
		strncpy(value,__hmi_retval,32);
		((char *)value)[32-1]=0;
		return 1;
	}
	return 0;
}

static u8 widget_set_text_12_visible__()
{
	static void *__hmi_var_208_ptr;
	u8 __hmi_var_208 = (*(u8 *)hmidb_get_data_value_by_ptr("picture_ctrl.page_count",&__hmi_var_208_ptr));
	static void *__hmi_var_209_ptr;
	u8 __hmi_var_209 = (*(u8 *)hmidb_get_data_value_by_ptr("sys_set.box_num",&__hmi_var_209_ptr));
	{
#line 1 "控件:text_12,属性:visible"
if((__hmi_var_208*8 + 4) > __hmi_var_209)//箱子编号大于箱子总数
{
    return 0;//不显示
}
return 1;

	}
}

static int widget_set_text_12_visible(void *value)
{
	u8 __hmi_retval = (u8)( widget_set_text_12_visible__());
	if (__hmi_retval != (*(u8 *)value))
	{
		(*(u8 *)value) = __hmi_retval;
		return 1;
	}
	return 0;
}

static u8 widget_set_text_12_enable__()
{
	static void *__hmi_var_210_ptr;
	u8 __hmi_var_210 = (*(u8 *)hmidb_get_data_value_by_ptr("picture_ctrl.page_count",&__hmi_var_210_ptr));
	static void *__hmi_var_211_ptr;
	u8 __hmi_var_211 = (*(u8 *)hmidb_get_data_value_by_ptr("sys_set.box_num",&__hmi_var_211_ptr));
	{
#line 1 "控件:text_12,属性:enable"
if((__hmi_var_210*8 + 4) > __hmi_var_211)//箱子编号大于箱子总数
{
    return 0;//不显示
}
return 1;

	}
}

static int widget_set_text_12_enable(void *value)
{
	u8 __hmi_retval = (u8)( widget_set_text_12_enable__());
	if (__hmi_retval != (*(u8 *)value))
	{
		(*(u8 *)value) = __hmi_retval;
		return 1;
	}
	return 0;
}

static char * widget_set_text_12_text__()
{
	static void *__hmi_var_212_ptr;
	u8 __hmi_var_212 = (*(u8 *)hmidb_get_data_value_by_ptr("picture_ctrl.page_count",&__hmi_var_212_ptr));
	{
#line 1 "控件:text_12,属性:text"
static char box_vir_num[5];
u8 box_index;
BOX_MSG box_info;

memset(box_vir_num , 0 , 5);
box_index = __hmi_var_212*8 + 4;
if(1 == read_box_info_station_num(box_index , &box_info))
{
    memcpy(box_vir_num , box_info.virtualnumber,4);
}
return box_vir_num;

	}
}

static int widget_set_text_12_text(void *value)
{
	char * __hmi_retval = (char *)( widget_set_text_12_text__());
	if ( strcmp(__hmi_retval, (char *)value))
	{
		strncpy(value,__hmi_retval,32);
		((char *)value)[32-1]=0;
		return 1;
	}
	return 0;
}

static u8 widget_set_text_11_visible__()
{
	static void *__hmi_var_213_ptr;
	u8 __hmi_var_213 = (*(u8 *)hmidb_get_data_value_by_ptr("picture_ctrl.page_count",&__hmi_var_213_ptr));
	static void *__hmi_var_214_ptr;
	u8 __hmi_var_214 = (*(u8 *)hmidb_get_data_value_by_ptr("sys_set.box_num",&__hmi_var_214_ptr));
	{
#line 1 "控件:text_11,属性:visible"
if((__hmi_var_213*8 + 3) > __hmi_var_214)//箱子编号大于箱子总数
{
    return 0;//不显示
}
return 1;

	}
}

static int widget_set_text_11_visible(void *value)
{
	u8 __hmi_retval = (u8)( widget_set_text_11_visible__());
	if (__hmi_retval != (*(u8 *)value))
	{
		(*(u8 *)value) = __hmi_retval;
		return 1;
	}
	return 0;
}

static u8 widget_set_text_11_enable__()
{
	static void *__hmi_var_215_ptr;
	u8 __hmi_var_215 = (*(u8 *)hmidb_get_data_value_by_ptr("picture_ctrl.page_count",&__hmi_var_215_ptr));
	static void *__hmi_var_216_ptr;
	u8 __hmi_var_216 = (*(u8 *)hmidb_get_data_value_by_ptr("sys_set.box_num",&__hmi_var_216_ptr));
	{
#line 1 "控件:text_11,属性:enable"
if((__hmi_var_215*8 + 3) > __hmi_var_216)//箱子编号大于箱子总数
{
    return 0;//不显示
}
return 1;

	}
}

static int widget_set_text_11_enable(void *value)
{
	u8 __hmi_retval = (u8)( widget_set_text_11_enable__());
	if (__hmi_retval != (*(u8 *)value))
	{
		(*(u8 *)value) = __hmi_retval;
		return 1;
	}
	return 0;
}

static char * widget_set_text_11_text__()
{
	static void *__hmi_var_217_ptr;
	u8 __hmi_var_217 = (*(u8 *)hmidb_get_data_value_by_ptr("picture_ctrl.page_count",&__hmi_var_217_ptr));
	static void *__hmi_var_218_ptr;
	char * __hmi_var_218 = ((char *)hmidb_get_data_value_by_ptr("picture_ctrl.box_idle",&__hmi_var_218_ptr));
	static void *__hmi_var_219_ptr;
	char * __hmi_var_219 = ((char *)hmidb_get_data_value_by_ptr("picture_ctrl.box_use",&__hmi_var_219_ptr));
	static void *__hmi_var_220_ptr;
	char * __hmi_var_220 = ((char *)hmidb_get_data_value_by_ptr("picture_ctrl.box_lock",&__hmi_var_220_ptr));
	static void *__hmi_var_221_ptr;
	char * __hmi_var_221 = ((char *)hmidb_get_data_value_by_ptr("picture_ctrl.box_err",&__hmi_var_221_ptr));
	{
#line 1 "控件:text_11,属性:text"
u8 box_index;
BOX_MSG box_info;

box_index = __hmi_var_217*8 + 3;
read_box_info_station_num(box_index , &box_info);
if(box_info.status == BOX_IDLE)
{
    return __hmi_var_218;
}
if(box_info.status == BOX_USED)
{
    return __hmi_var_219;
}
if(box_info.status == BOX_LOCK)
{
    return __hmi_var_220;
}
return __hmi_var_221;

	}
}

static int widget_set_text_11_text(void *value)
{
	char * __hmi_retval = (char *)( widget_set_text_11_text__());
	if ( strcmp(__hmi_retval, (char *)value))
	{
		strncpy(value,__hmi_retval,32);
		((char *)value)[32-1]=0;
		return 1;
	}
	return 0;
}

static u8 widget_set_text_28_visible__()
{
	static void *__hmi_var_222_ptr;
	u8 __hmi_var_222 = (*(u8 *)hmidb_get_data_value_by_ptr("picture_ctrl.page_count",&__hmi_var_222_ptr));
	static void *__hmi_var_223_ptr;
	u8 __hmi_var_223 = (*(u8 *)hmidb_get_data_value_by_ptr("sys_set.box_num",&__hmi_var_223_ptr));
	{
#line 1 "控件:text_28,属性:visible"
if((__hmi_var_222*8 + 3) > __hmi_var_223)//箱子编号大于箱子总数
{
    return 0;//不显示
}
return 1;

	}
}

static int widget_set_text_28_visible(void *value)
{
	u8 __hmi_retval = (u8)( widget_set_text_28_visible__());
	if (__hmi_retval != (*(u8 *)value))
	{
		(*(u8 *)value) = __hmi_retval;
		return 1;
	}
	return 0;
}

static u8 widget_set_text_28_enable__()
{
	static void *__hmi_var_224_ptr;
	u8 __hmi_var_224 = (*(u8 *)hmidb_get_data_value_by_ptr("picture_ctrl.page_count",&__hmi_var_224_ptr));
	static void *__hmi_var_225_ptr;
	u8 __hmi_var_225 = (*(u8 *)hmidb_get_data_value_by_ptr("sys_set.box_num",&__hmi_var_225_ptr));
	{
#line 1 "控件:text_28,属性:enable"
if((__hmi_var_224*8 + 3) > __hmi_var_225)//箱子编号大于箱子总数
{
    return 0;//不显示
}
return 1;

	}
}

static int widget_set_text_28_enable(void *value)
{
	u8 __hmi_retval = (u8)( widget_set_text_28_enable__());
	if (__hmi_retval != (*(u8 *)value))
	{
		(*(u8 *)value) = __hmi_retval;
		return 1;
	}
	return 0;
}

static char * widget_set_text_28_text__()
{
	static void *__hmi_var_226_ptr;
	u8 __hmi_var_226 = (*(u8 *)hmidb_get_data_value_by_ptr("picture_ctrl.page_count",&__hmi_var_226_ptr));
	static void *__hmi_var_227_ptr;
	char * __hmi_var_227 = ((char *)hmidb_get_data_value_by_ptr("picture_ctrl.box_min",&__hmi_var_227_ptr));
	static void *__hmi_var_228_ptr;
	char * __hmi_var_228 = ((char *)hmidb_get_data_value_by_ptr("picture_ctrl.box_mid",&__hmi_var_228_ptr));
	static void *__hmi_var_229_ptr;
	char * __hmi_var_229 = ((char *)hmidb_get_data_value_by_ptr("picture_ctrl.box_max",&__hmi_var_229_ptr));
	static void *__hmi_var_230_ptr;
	char * __hmi_var_230 = ((char *)hmidb_get_data_value_by_ptr("picture_ctrl.box_err",&__hmi_var_230_ptr));
	{
#line 1 "控件:text_28,属性:text"
u8 box_index;
BOX_MSG box_info;


box_index = __hmi_var_226*8 + 3;
read_box_info_station_num(box_index , &box_info);
if(box_info.type == BOX_TYPE_MIN)
{
    return __hmi_var_227;
}
if(box_info.type == BOX_TYPE_MID)
{
    return __hmi_var_228;
}
if(box_info.type == BOX_TYPE_MAX)
{
    return __hmi_var_229;
}
return __hmi_var_230;

	}
}

static int widget_set_text_28_text(void *value)
{
	char * __hmi_retval = (char *)( widget_set_text_28_text__());
	if ( strcmp(__hmi_retval, (char *)value))
	{
		strncpy(value,__hmi_retval,32);
		((char *)value)[32-1]=0;
		return 1;
	}
	return 0;
}

static u8 widget_set_text_10_visible__()
{
	static void *__hmi_var_231_ptr;
	u8 __hmi_var_231 = (*(u8 *)hmidb_get_data_value_by_ptr("picture_ctrl.page_count",&__hmi_var_231_ptr));
	static void *__hmi_var_232_ptr;
	u8 __hmi_var_232 = (*(u8 *)hmidb_get_data_value_by_ptr("sys_set.box_num",&__hmi_var_232_ptr));
	{
#line 1 "控件:text_10,属性:visible"
if((__hmi_var_231*8 + 3) > __hmi_var_232)//箱子编号大于箱子总数
{
    return 0;//不显示
}
return 1;

	}
}

static int widget_set_text_10_visible(void *value)
{
	u8 __hmi_retval = (u8)( widget_set_text_10_visible__());
	if (__hmi_retval != (*(u8 *)value))
	{
		(*(u8 *)value) = __hmi_retval;
		return 1;
	}
	return 0;
}

static u8 widget_set_text_10_enable__()
{
	static void *__hmi_var_233_ptr;
	u8 __hmi_var_233 = (*(u8 *)hmidb_get_data_value_by_ptr("picture_ctrl.page_count",&__hmi_var_233_ptr));
	static void *__hmi_var_234_ptr;
	u8 __hmi_var_234 = (*(u8 *)hmidb_get_data_value_by_ptr("sys_set.box_num",&__hmi_var_234_ptr));
	{
#line 1 "控件:text_10,属性:enable"
if((__hmi_var_233*8 + 3) > __hmi_var_234)//箱子编号大于箱子总数
{
    return 0;//不显示
}
return 1;

	}
}

static int widget_set_text_10_enable(void *value)
{
	u8 __hmi_retval = (u8)( widget_set_text_10_enable__());
	if (__hmi_retval != (*(u8 *)value))
	{
		(*(u8 *)value) = __hmi_retval;
		return 1;
	}
	return 0;
}

static char * widget_set_text_10_text__()
{
	static void *__hmi_var_235_ptr;
	u8 __hmi_var_235 = (*(u8 *)hmidb_get_data_value_by_ptr("picture_ctrl.page_count",&__hmi_var_235_ptr));
	{
#line 1 "控件:text_10,属性:text"
static char box_vir_num[5];
u8 box_index;
BOX_MSG box_info;

memset(box_vir_num , 0 , 5);
box_index = __hmi_var_235*8 + 3;
if(1 == read_box_info_station_num(box_index , &box_info))
{
    memcpy(box_vir_num , box_info.virtualnumber,4);
}
return box_vir_num;

	}
}

static int widget_set_text_10_text(void *value)
{
	char * __hmi_retval = (char *)( widget_set_text_10_text__());
	if ( strcmp(__hmi_retval, (char *)value))
	{
		strncpy(value,__hmi_retval,32);
		((char *)value)[32-1]=0;
		return 1;
	}
	return 0;
}

static u8 widget_set_text_8_visible__()
{
	static void *__hmi_var_236_ptr;
	u8 __hmi_var_236 = (*(u8 *)hmidb_get_data_value_by_ptr("picture_ctrl.page_count",&__hmi_var_236_ptr));
	static void *__hmi_var_237_ptr;
	u8 __hmi_var_237 = (*(u8 *)hmidb_get_data_value_by_ptr("sys_set.box_num",&__hmi_var_237_ptr));
	{
#line 1 "控件:text_8,属性:visible"
if((__hmi_var_236*8 + 2) > __hmi_var_237)//箱子编号大于箱子总数
{
    return 0;//不显示
}
return 1;

	}
}

static int widget_set_text_8_visible(void *value)
{
	u8 __hmi_retval = (u8)( widget_set_text_8_visible__());
	if (__hmi_retval != (*(u8 *)value))
	{
		(*(u8 *)value) = __hmi_retval;
		return 1;
	}
	return 0;
}

static u8 widget_set_text_8_enable__()
{
	static void *__hmi_var_238_ptr;
	u8 __hmi_var_238 = (*(u8 *)hmidb_get_data_value_by_ptr("picture_ctrl.page_count",&__hmi_var_238_ptr));
	static void *__hmi_var_239_ptr;
	u8 __hmi_var_239 = (*(u8 *)hmidb_get_data_value_by_ptr("sys_set.box_num",&__hmi_var_239_ptr));
	{
#line 1 "控件:text_8,属性:enable"
if((__hmi_var_238*8 + 2) > __hmi_var_239)//箱子编号大于箱子总数
{
    return 0;//不显示
}
return 1;

	}
}

static int widget_set_text_8_enable(void *value)
{
	u8 __hmi_retval = (u8)( widget_set_text_8_enable__());
	if (__hmi_retval != (*(u8 *)value))
	{
		(*(u8 *)value) = __hmi_retval;
		return 1;
	}
	return 0;
}

static char * widget_set_text_8_text__()
{
	static void *__hmi_var_240_ptr;
	u8 __hmi_var_240 = (*(u8 *)hmidb_get_data_value_by_ptr("picture_ctrl.page_count",&__hmi_var_240_ptr));
	static void *__hmi_var_241_ptr;
	char * __hmi_var_241 = ((char *)hmidb_get_data_value_by_ptr("picture_ctrl.box_idle",&__hmi_var_241_ptr));
	static void *__hmi_var_242_ptr;
	char * __hmi_var_242 = ((char *)hmidb_get_data_value_by_ptr("picture_ctrl.box_use",&__hmi_var_242_ptr));
	static void *__hmi_var_243_ptr;
	char * __hmi_var_243 = ((char *)hmidb_get_data_value_by_ptr("picture_ctrl.box_lock",&__hmi_var_243_ptr));
	static void *__hmi_var_244_ptr;
	char * __hmi_var_244 = ((char *)hmidb_get_data_value_by_ptr("picture_ctrl.box_err",&__hmi_var_244_ptr));
	{
#line 1 "控件:text_8,属性:text"
u8 box_index;
BOX_MSG box_info;

box_index = __hmi_var_240*8 + 2;
read_box_info_station_num(box_index , &box_info);
if(box_info.status == BOX_IDLE)
{
    return __hmi_var_241;
}
if(box_info.status == BOX_USED)
{
    return __hmi_var_242;
}
if(box_info.status == BOX_LOCK)
{
    return __hmi_var_243;
}
return __hmi_var_244;

	}
}

static int widget_set_text_8_text(void *value)
{
	char * __hmi_retval = (char *)( widget_set_text_8_text__());
	if ( strcmp(__hmi_retval, (char *)value))
	{
		strncpy(value,__hmi_retval,32);
		((char *)value)[32-1]=0;
		return 1;
	}
	return 0;
}

static u8 widget_set_text_27_visible__()
{
	static void *__hmi_var_245_ptr;
	u8 __hmi_var_245 = (*(u8 *)hmidb_get_data_value_by_ptr("picture_ctrl.page_count",&__hmi_var_245_ptr));
	static void *__hmi_var_246_ptr;
	u8 __hmi_var_246 = (*(u8 *)hmidb_get_data_value_by_ptr("sys_set.box_num",&__hmi_var_246_ptr));
	{
#line 1 "控件:text_27,属性:visible"
if((__hmi_var_245*8 + 2) > __hmi_var_246)//箱子编号大于箱子总数
{
    return 0;//不显示
}
return 1;

	}
}

static int widget_set_text_27_visible(void *value)
{
	u8 __hmi_retval = (u8)( widget_set_text_27_visible__());
	if (__hmi_retval != (*(u8 *)value))
	{
		(*(u8 *)value) = __hmi_retval;
		return 1;
	}
	return 0;
}

static u8 widget_set_text_27_enable__()
{
	static void *__hmi_var_247_ptr;
	u8 __hmi_var_247 = (*(u8 *)hmidb_get_data_value_by_ptr("picture_ctrl.page_count",&__hmi_var_247_ptr));
	static void *__hmi_var_248_ptr;
	u8 __hmi_var_248 = (*(u8 *)hmidb_get_data_value_by_ptr("sys_set.box_num",&__hmi_var_248_ptr));
	{
#line 1 "控件:text_27,属性:enable"
if((__hmi_var_247*8 + 2) > __hmi_var_248)//箱子编号大于箱子总数
{
    return 0;//不显示
}
return 1;

	}
}

static int widget_set_text_27_enable(void *value)
{
	u8 __hmi_retval = (u8)( widget_set_text_27_enable__());
	if (__hmi_retval != (*(u8 *)value))
	{
		(*(u8 *)value) = __hmi_retval;
		return 1;
	}
	return 0;
}

static char * widget_set_text_27_text__()
{
	static void *__hmi_var_249_ptr;
	u8 __hmi_var_249 = (*(u8 *)hmidb_get_data_value_by_ptr("picture_ctrl.page_count",&__hmi_var_249_ptr));
	static void *__hmi_var_250_ptr;
	char * __hmi_var_250 = ((char *)hmidb_get_data_value_by_ptr("picture_ctrl.box_min",&__hmi_var_250_ptr));
	static void *__hmi_var_251_ptr;
	char * __hmi_var_251 = ((char *)hmidb_get_data_value_by_ptr("picture_ctrl.box_mid",&__hmi_var_251_ptr));
	static void *__hmi_var_252_ptr;
	char * __hmi_var_252 = ((char *)hmidb_get_data_value_by_ptr("picture_ctrl.box_max",&__hmi_var_252_ptr));
	static void *__hmi_var_253_ptr;
	char * __hmi_var_253 = ((char *)hmidb_get_data_value_by_ptr("picture_ctrl.box_err",&__hmi_var_253_ptr));
	{
#line 1 "控件:text_27,属性:text"
u8 box_index;
BOX_MSG box_info;


box_index = __hmi_var_249*8 + 2;
read_box_info_station_num(box_index , &box_info);
if(box_info.type == BOX_TYPE_MIN)
{
    return __hmi_var_250;
}
if(box_info.type == BOX_TYPE_MID)
{
    return __hmi_var_251;
}
if(box_info.type == BOX_TYPE_MAX)
{
    return __hmi_var_252;
}
return __hmi_var_253;

	}
}

static int widget_set_text_27_text(void *value)
{
	char * __hmi_retval = (char *)( widget_set_text_27_text__());
	if ( strcmp(__hmi_retval, (char *)value))
	{
		strncpy(value,__hmi_retval,32);
		((char *)value)[32-1]=0;
		return 1;
	}
	return 0;
}

static u8 widget_set_text_7_visible__()
{
	static void *__hmi_var_254_ptr;
	u8 __hmi_var_254 = (*(u8 *)hmidb_get_data_value_by_ptr("picture_ctrl.page_count",&__hmi_var_254_ptr));
	static void *__hmi_var_255_ptr;
	u8 __hmi_var_255 = (*(u8 *)hmidb_get_data_value_by_ptr("sys_set.box_num",&__hmi_var_255_ptr));
	{
#line 1 "控件:text_7,属性:visible"
if((__hmi_var_254*8 + 2) > __hmi_var_255)//箱子编号大于箱子总数
{
    return 0;//不显示
}
return 1;

	}
}

static int widget_set_text_7_visible(void *value)
{
	u8 __hmi_retval = (u8)( widget_set_text_7_visible__());
	if (__hmi_retval != (*(u8 *)value))
	{
		(*(u8 *)value) = __hmi_retval;
		return 1;
	}
	return 0;
}

static u8 widget_set_text_7_enable__()
{
	static void *__hmi_var_256_ptr;
	u8 __hmi_var_256 = (*(u8 *)hmidb_get_data_value_by_ptr("picture_ctrl.page_count",&__hmi_var_256_ptr));
	static void *__hmi_var_257_ptr;
	u8 __hmi_var_257 = (*(u8 *)hmidb_get_data_value_by_ptr("sys_set.box_num",&__hmi_var_257_ptr));
	{
#line 1 "控件:text_7,属性:enable"
if((__hmi_var_256*8 + 2) > __hmi_var_257)//箱子编号大于箱子总数
{
    return 0;//不显示
}
return 1;

	}
}

static int widget_set_text_7_enable(void *value)
{
	u8 __hmi_retval = (u8)( widget_set_text_7_enable__());
	if (__hmi_retval != (*(u8 *)value))
	{
		(*(u8 *)value) = __hmi_retval;
		return 1;
	}
	return 0;
}

static char * widget_set_text_7_text__()
{
	static void *__hmi_var_258_ptr;
	u8 __hmi_var_258 = (*(u8 *)hmidb_get_data_value_by_ptr("picture_ctrl.page_count",&__hmi_var_258_ptr));
	{
#line 1 "控件:text_7,属性:text"
static char box_vir_num[5];
u8 box_index;
BOX_MSG box_info;

memset(box_vir_num , 0 , 5);
box_index = __hmi_var_258*8 + 2;
if(1 == read_box_info_station_num(box_index , &box_info))
{
    memcpy(box_vir_num , box_info.virtualnumber,4);
}
return box_vir_num;

	}
}

static int widget_set_text_7_text(void *value)
{
	char * __hmi_retval = (char *)( widget_set_text_7_text__());
	if ( strcmp(__hmi_retval, (char *)value))
	{
		strncpy(value,__hmi_retval,32);
		((char *)value)[32-1]=0;
		return 1;
	}
	return 0;
}

static u8 widget_set_text_25_visible__()
{
	static void *__hmi_var_259_ptr;
	u8 __hmi_var_259 = (*(u8 *)hmidb_get_data_value_by_ptr("picture_ctrl.page_count",&__hmi_var_259_ptr));
	static void *__hmi_var_260_ptr;
	u8 __hmi_var_260 = (*(u8 *)hmidb_get_data_value_by_ptr("sys_set.box_num",&__hmi_var_260_ptr));
	{
#line 1 "控件:text_25,属性:visible"
if((__hmi_var_259*8 + 1) > __hmi_var_260)//箱子编号大于箱子总数
{
    return 0;//不显示
}
return 1;

	}
}

static int widget_set_text_25_visible(void *value)
{
	u8 __hmi_retval = (u8)( widget_set_text_25_visible__());
	if (__hmi_retval != (*(u8 *)value))
	{
		(*(u8 *)value) = __hmi_retval;
		return 1;
	}
	return 0;
}

static u8 widget_set_text_25_enable__()
{
	static void *__hmi_var_261_ptr;
	u8 __hmi_var_261 = (*(u8 *)hmidb_get_data_value_by_ptr("picture_ctrl.page_count",&__hmi_var_261_ptr));
	static void *__hmi_var_262_ptr;
	u8 __hmi_var_262 = (*(u8 *)hmidb_get_data_value_by_ptr("sys_set.box_num",&__hmi_var_262_ptr));
	{
#line 1 "控件:text_25,属性:enable"
if((__hmi_var_261*8 + 1) > __hmi_var_262)//箱子编号大于箱子总数
{
    return 0;//不显示
}
return 1;

	}
}

static int widget_set_text_25_enable(void *value)
{
	u8 __hmi_retval = (u8)( widget_set_text_25_enable__());
	if (__hmi_retval != (*(u8 *)value))
	{
		(*(u8 *)value) = __hmi_retval;
		return 1;
	}
	return 0;
}

static char * widget_set_text_25_text__()
{
	static void *__hmi_var_263_ptr;
	u8 __hmi_var_263 = (*(u8 *)hmidb_get_data_value_by_ptr("picture_ctrl.page_count",&__hmi_var_263_ptr));
	static void *__hmi_var_264_ptr;
	char * __hmi_var_264 = ((char *)hmidb_get_data_value_by_ptr("picture_ctrl.box_min",&__hmi_var_264_ptr));
	static void *__hmi_var_265_ptr;
	char * __hmi_var_265 = ((char *)hmidb_get_data_value_by_ptr("picture_ctrl.box_mid",&__hmi_var_265_ptr));
	static void *__hmi_var_266_ptr;
	char * __hmi_var_266 = ((char *)hmidb_get_data_value_by_ptr("picture_ctrl.box_max",&__hmi_var_266_ptr));
	{
#line 1 "控件:text_25,属性:text"
u8 box_index;
BOX_MSG box_info;


box_index = __hmi_var_263*8 + 1;
read_box_info_station_num(box_index , &box_info);
if(box_info.type == BOX_TYPE_MIN)
{
    return __hmi_var_264;
}
if(box_info.type == BOX_TYPE_MID)
{
    return __hmi_var_265;
}
if(box_info.type == BOX_TYPE_MAX)
{
    return __hmi_var_266;
}

	}
}

static int widget_set_text_25_text(void *value)
{
	char * __hmi_retval = (char *)( widget_set_text_25_text__());
	if ( strcmp(__hmi_retval, (char *)value))
	{
		strncpy(value,__hmi_retval,32);
		((char *)value)[32-1]=0;
		return 1;
	}
	return 0;
}

static u8 widget_set_button_2_visible__()
{
	static void *__hmi_var_267_ptr;
	u8 __hmi_var_267 = (*(u8 *)hmidb_get_data_value_by_ptr("picture_ctrl.page_count",&__hmi_var_267_ptr));
	static void *__hmi_var_268_ptr;
	u8 __hmi_var_268 = (*(u8 *)hmidb_get_data_value_by_ptr("sys_set.box_num",&__hmi_var_268_ptr));
	{
#line 1 "控件:button_2,属性:visible"
if(((__hmi_var_267+1)*8) >= __hmi_var_268)
{
    return 0;
}
return 1;

	}
}

static int widget_set_button_2_visible(void *value)
{
	u8 __hmi_retval = (u8)( widget_set_button_2_visible__());
	if (__hmi_retval != (*(u8 *)value))
	{
		(*(u8 *)value) = __hmi_retval;
		return 1;
	}
	return 0;
}

static u8 widget_set_button_2_enable__()
{
	static void *__hmi_var_269_ptr;
	u8 __hmi_var_269 = (*(u8 *)hmidb_get_data_value_by_ptr("picture_ctrl.page_count",&__hmi_var_269_ptr));
	static void *__hmi_var_270_ptr;
	u8 __hmi_var_270 = (*(u8 *)hmidb_get_data_value_by_ptr("sys_set.box_num",&__hmi_var_270_ptr));
	{
#line 1 "控件:button_2,属性:enable"
if(((__hmi_var_269+1)*8) >= __hmi_var_270)
{
    return 0;
}
return 1;

	}
}

static int widget_set_button_2_enable(void *value)
{
	u8 __hmi_retval = (u8)( widget_set_button_2_enable__());
	if (__hmi_retval != (*(u8 *)value))
	{
		(*(u8 *)value) = __hmi_retval;
		return 1;
	}
	return 0;
}

static u8 widget_set_button_visible__()
{
	static void *__hmi_var_272_ptr;
	u8 __hmi_var_272 = (*(u8 *)hmidb_get_data_value_by_ptr("picture_ctrl.page_count",&__hmi_var_272_ptr));
	{
#line 1 "控件:button,属性:visible"
if(__hmi_var_272 == 0)
{
    return 0;
}
return 1;
	}
}

static int widget_set_button_visible(void *value)
{
	u8 __hmi_retval = (u8)( widget_set_button_visible__());
	if (__hmi_retval != (*(u8 *)value))
	{
		(*(u8 *)value) = __hmi_retval;
		return 1;
	}
	return 0;
}

static u8 widget_set_button_enable__()
{
	static void *__hmi_var_273_ptr;
	u8 __hmi_var_273 = (*(u8 *)hmidb_get_data_value_by_ptr("picture_ctrl.page_count",&__hmi_var_273_ptr));
	{
#line 1 "控件:button,属性:enable"
if(__hmi_var_273 == 0)
{
    return 0;
}
return 1;
	}
}

static int widget_set_button_enable(void *value)
{
	u8 __hmi_retval = (u8)( widget_set_button_enable__());
	if (__hmi_retval != (*(u8 *)value))
	{
		(*(u8 *)value) = __hmi_retval;
		return 1;
	}
	return 0;
}

static u8 widget_set_text_6_visible__()
{
	static void *__hmi_var_275_ptr;
	u8 __hmi_var_275 = (*(u8 *)hmidb_get_data_value_by_ptr("picture_ctrl.page_count",&__hmi_var_275_ptr));
	static void *__hmi_var_276_ptr;
	u8 __hmi_var_276 = (*(u8 *)hmidb_get_data_value_by_ptr("sys_set.box_num",&__hmi_var_276_ptr));
	{
#line 1 "控件:text_6,属性:visible"
if((__hmi_var_275*8 + 1) > __hmi_var_276)//箱子编号大于箱子总数
{
    return 0;//不显示
}
return 1;

	}
}

static int widget_set_text_6_visible(void *value)
{
	u8 __hmi_retval = (u8)( widget_set_text_6_visible__());
	if (__hmi_retval != (*(u8 *)value))
	{
		(*(u8 *)value) = __hmi_retval;
		return 1;
	}
	return 0;
}

static u8 widget_set_text_6_enable__()
{
	static void *__hmi_var_277_ptr;
	u8 __hmi_var_277 = (*(u8 *)hmidb_get_data_value_by_ptr("picture_ctrl.page_count",&__hmi_var_277_ptr));
	static void *__hmi_var_278_ptr;
	u8 __hmi_var_278 = (*(u8 *)hmidb_get_data_value_by_ptr("sys_set.box_num",&__hmi_var_278_ptr));
	{
#line 1 "控件:text_6,属性:enable"
if((__hmi_var_277*8 + 1) > __hmi_var_278)//箱子编号大于箱子总数
{
    return 0;//不显示
}
return 1;

	}
}

static int widget_set_text_6_enable(void *value)
{
	u8 __hmi_retval = (u8)( widget_set_text_6_enable__());
	if (__hmi_retval != (*(u8 *)value))
	{
		(*(u8 *)value) = __hmi_retval;
		return 1;
	}
	return 0;
}

static char * widget_set_text_6_text__()
{
	static void *__hmi_var_279_ptr;
	u8 __hmi_var_279 = (*(u8 *)hmidb_get_data_value_by_ptr("picture_ctrl.page_count",&__hmi_var_279_ptr));
	static void *__hmi_var_280_ptr;
	char * __hmi_var_280 = ((char *)hmidb_get_data_value_by_ptr("picture_ctrl.box_idle",&__hmi_var_280_ptr));
	static void *__hmi_var_281_ptr;
	char * __hmi_var_281 = ((char *)hmidb_get_data_value_by_ptr("picture_ctrl.box_use",&__hmi_var_281_ptr));
	static void *__hmi_var_282_ptr;
	char * __hmi_var_282 = ((char *)hmidb_get_data_value_by_ptr("picture_ctrl.box_lock",&__hmi_var_282_ptr));
	{
#line 1 "控件:text_6,属性:text"
u8 box_index;
BOX_MSG box_info;

box_index = __hmi_var_279*8 + 1;
read_box_info_station_num(box_index , &box_info);
if(box_info.status == BOX_IDLE)
{
    return __hmi_var_280;
}
if(box_info.status == BOX_USED)
{
    return __hmi_var_281;
}
if(box_info.status == BOX_LOCK)
{
    return __hmi_var_282;
}

	}
}

static int widget_set_text_6_text(void *value)
{
	char * __hmi_retval = (char *)( widget_set_text_6_text__());
	if ( strcmp(__hmi_retval, (char *)value))
	{
		strncpy(value,__hmi_retval,32);
		((char *)value)[32-1]=0;
		return 1;
	}
	return 0;
}

static u8 widget_set_text_5_visible__()
{
	static void *__hmi_var_283_ptr;
	u8 __hmi_var_283 = (*(u8 *)hmidb_get_data_value_by_ptr("picture_ctrl.page_count",&__hmi_var_283_ptr));
	static void *__hmi_var_284_ptr;
	u8 __hmi_var_284 = (*(u8 *)hmidb_get_data_value_by_ptr("sys_set.box_num",&__hmi_var_284_ptr));
	{
#line 1 "控件:text_5,属性:visible"
if((__hmi_var_283*8 + 1) > __hmi_var_284)//箱子编号大于箱子总数
{
    return 0;//不显示
}
return 1;

	}
}

static int widget_set_text_5_visible(void *value)
{
	u8 __hmi_retval = (u8)( widget_set_text_5_visible__());
	if (__hmi_retval != (*(u8 *)value))
	{
		(*(u8 *)value) = __hmi_retval;
		return 1;
	}
	return 0;
}

static u8 widget_set_text_5_enable__()
{
	static void *__hmi_var_285_ptr;
	u8 __hmi_var_285 = (*(u8 *)hmidb_get_data_value_by_ptr("picture_ctrl.page_count",&__hmi_var_285_ptr));
	static void *__hmi_var_286_ptr;
	u8 __hmi_var_286 = (*(u8 *)hmidb_get_data_value_by_ptr("sys_set.box_num",&__hmi_var_286_ptr));
	{
#line 1 "控件:text_5,属性:enable"
if((__hmi_var_285*8 + 1) > __hmi_var_286)//箱子编号大于箱子总数
{
    return 0;//不显示
}
return 1;

	}
}

static int widget_set_text_5_enable(void *value)
{
	u8 __hmi_retval = (u8)( widget_set_text_5_enable__());
	if (__hmi_retval != (*(u8 *)value))
	{
		(*(u8 *)value) = __hmi_retval;
		return 1;
	}
	return 0;
}

static char * widget_set_text_5_text__()
{
	static void *__hmi_var_287_ptr;
	u8 __hmi_var_287 = (*(u8 *)hmidb_get_data_value_by_ptr("picture_ctrl.page_count",&__hmi_var_287_ptr));
	{
#line 1 "控件:text_5,属性:text"
static char box_vir_num[5];
u8 box_index;
BOX_MSG box_info;

memset(box_vir_num , 0 , 5);
box_index = __hmi_var_287*8 + 1;
read_box_info_station_num(box_index , &box_info);
memcpy(box_vir_num , box_info.virtualnumber,4);
return box_vir_num;

	}
}

static int widget_set_text_5_text(void *value)
{
	char * __hmi_retval = (char *)( widget_set_text_5_text__());
	if ( strcmp(__hmi_retval, (char *)value))
	{
		strncpy(value,__hmi_retval,32);
		((char *)value)[32-1]=0;
		return 1;
	}
	return 0;
}

#endif
