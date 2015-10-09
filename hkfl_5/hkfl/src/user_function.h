#ifndef __USER_FUNCTION_H
#define __USER_FUNCTION_H

#define write_box_msglib()      $box_msg.station_num = box_info.station_num
    /*$box_msg.station_port = box_info.station_port;\
    memcpy($box_msg.virtualnumber,box_info.virtualnumber,VIRTUAL_NUM_LENGTH);\
    $box_msg.type = box_info.type;\
    $box_msg.status = box_info.status;\
    memcpy($box_msg.user_id,box_info.user_id,USERID_LENGTH);\
    memcpy($box_msg.user_phnum,box_info.user_phnum,USER_PHNUM_LENGTH);\
    memcpy($box_msg.pass_word,box_info.pass_word,USER_PASSWORD_LENGTH);\
    memcpy($box_msg.send_num,box_info.send_num,SEND_NUM_LENGTH);\
    memcpy($box_msg.send_id,box_info.send_id,SENDID_LENGTH)*/
void test_display(char *outbuf , unsigned char *inbuf , int len);
#endif
