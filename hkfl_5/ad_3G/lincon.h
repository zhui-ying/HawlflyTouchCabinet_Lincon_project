#ifndef __LINCON_H
#define __LINCON_H

//all defines...

//rtdb data type
#define UNKNOWN_TYPE	0
#define BIT_TYPE	1
#define CHAR_TYPE	2
#define UCHAR_TYPE	3
#define SHORT_TYPE	4
#define USHORT_TYPE	5
#define LONG_TYPE	6
#define ULONG_TYPE	7
#define FWORD_TYPE	8
#define FLOAT_TYPE	9
#define DOUBLE_TYPE	10
#define STRING_TYPE	11
#define ARRAY_TYPE	12
#define DATE_TYPE	13
#define VAR_TYPE	14

typedef unsigned char u8;
typedef signed char i8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef u8 data_type_t;

//serial.
#define SERIAL_FLUSH_TX		1
#define SERIAL_FLUSH_RX		2

#define SERIAL_PARITY_NO        0
#define SERIAL_PARITY_ODD       1
#define SERIAL_PARITY_EVENT     2

#define SERIAL_STOPBIT_ONE      1
#define SERIAL_STOPBIT_TWO      2

//rtdb log
#define RTDB_LOG_REC_TYPE_TIME_SEC		0
#define RTDB_LOG_REC_TYPE_DATA			1	

#define LOG_FILE_SAVE_DIR_INTERNAL	0
#define LOG_FILE_SAVE_DIR_CF				1

//malloc
#define sys_malloc	malloc
#define sys_calloc  calloc
#define sys_strdup	strdup
#define sys_free	free
#define sys_realloc	realloc
#define sys_alloca	alloca

//all structures
//control io.
typedef struct _ctrl_io_driver_t
{
	struct _ctrl_io_driver_t *next;
	char *name;
	int (*init)();
	int (*run)();
	void (*release)();
}ctrl_io_driver_t;

//rtdb log
typedef struct _usr_log_file_var_info_t
{
	int rec_type;
	unsigned char var_type;
	int var_len;
	char *var_name;
	void *data_buf;		//data_size * var_len
}usr_log_file_var_info_t;

typedef struct _usr_log_file_info_t
{
	char *logname;
	int var_count;
	int data_size;
	usr_log_file_var_info_t *vars;	//var_count
}usr_log_file_info_t;

//time
#ifdef _WINDOWS
#include <time.h>
typedef struct  _timeval_t {
        long    tv_sec;         /* seconds */
        long    tv_usec;        /* and microseconds */
}timeval_t;
#endif

#ifdef _LINUX
#include <sys/time.h>
#include <unistd.h>
typedef struct timeval timeval_t;
#endif

//for socket.
#if defined(_WINDOWS)
#ifndef _WINSOCKAPI_
#define _WINSOCKAPI_
#include <winsock2.h>
#endif
#else
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#define INVALID_SOCKET	-1
#define SOCKET_ERROR	-1
#define closesocket close
#endif

//for history
typedef struct
{
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
	int usec;
}sys_time_t;

typedef struct 
{
	char *varname;
	u8 *data_buf;
}history_data_buf_t;

typedef void* sync_lock_t;

//functions.
#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

//data convert.
int data_convert_to_float(data_type_t type,void *data_value,float *result);
char *data_convert_to_string(data_type_t type,void *data_value);
int data_convert_to_double(data_type_t type,void *data_value,double *result);
int data_convert_to_short(data_type_t type,void *data_value,short *result);
int data_convert_to_long(data_type_t type,void *data_value,long *result);
long str2long(char *value);
unsigned long str2ulong(char *value);

//control io
int control_io_register_driver(ctrl_io_driver_t *io_driver);

//serial
int serial_open(const char *device,int baud,int parity,int data_bits,int stop_bits,int timeout);
int serial_close(int serial_id);
int serial_flush(int serial_id,int flag);
int serial_write(int serial_id,char *buf,int size);
int serial_clear_read(int serial_id,int timeout);
int serial_read(int serial_id,char *buf,int size);
int serial_poll(int serial_id,int timeout);

//rtdb
int rtdb_set_data_value_by_name(char *dbname,char *dataname,void *data_value);
int rtdb_get_data_value_by_name(char *dbname,char *dataname,void *data_value);

//system
void sys_sleep(unsigned long ms);

//rtdb log
int rtdb_log_save_file(char *logname,int save_dir,char *filename);
int rtdb_log_save_usr_file(usr_log_file_info_t *usr_log,int save_dir,char *filename);
int rtdb_get_log_data(char *logname,char *dataname,u8 *buf,int log_number);
int rtdb_get_log_data_from_file(int file_path,char *filename,char *dataname,u8 *buf,int log_number,int start_pt);

//time
int time_get(timeval_t *t);
int time_sub(timeval_t *res, timeval_t *t1, timeval_t *t2);
long double time_to_ld(timeval_t *t);
int setsystime(int year,int month,int day,int hour,int minu,int sec);
int gettimeinfo(unsigned long cur_datetime,int *year,int *month,int *day,int *hour,int *minu,int *sec);
int datetime_add(int *year,int *month,int *day,int *hour,int *min,int *sec,int add_seconds);

#ifdef _WINDOWS
struct tm *localtime_r (const time_t *t, struct tm *tp);
#endif

//thread
int sys_create_thread(int (*thread_func)(void *),void *arg);

//file & directory
const char *hmi_get_usr_data_dir();
const char *hmi_get_cfcard_dir();
const char *hmi_get_usb_dir();
const char *hmi_get_project_dir();

//debug
void debug_set_ip(const char *ip);
void debug_printf(const char *format,...);

//history
int history_get_data_value_by_time(history_data_buf_t *his_data_buf,int his_data_count,
			sys_time_t *start_time,sys_time_t *end_time,int points_num,sys_time_t *all_pt_time,
			char *history_name);

void *history_query_open(char *history_name,char *query_var_name,sys_time_t *start_time,sys_time_t *end_time);
void history_query_close(void *query_handle);
int history_query_next_record(void *query_handle,sys_time_t *rec_time);
int history_delete_files(char *history_name,sys_time_t *start_time,sys_time_t *end_time);

int read_io_data_to_buffer(const char *link_name, const char *device_name, const char *reg_name, u32 start_addr, u32 count, void *buffer, u32 buf_size);
int write_io_data_from_buffer(const char *link_name, const char *device_name, const char *reg_name, u32 start_addr, u32 count, const void *buffer);

//execute program
int sys_exec_program(char *program,int wait);

//for audio play
int audio_play_wav(char *filename,int wait);
int audio_stop_play();

//for thread lock
int sync_mutex_init(sync_lock_t *lock);
void sync_mutex_lock(sync_lock_t lock);
void sync_mutex_unlock(sync_lock_t lock);
void sync_mutex_delete(sync_lock_t lock);


#ifdef __cplusplus
}
#endif  /* __cplusplus */


#endif
