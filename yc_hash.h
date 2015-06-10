/*************************************************************************
	> File Name: yc_hash.h
	> Author: yangchao
	> Mail: yangchao9264@126.com
	> Created Time: 2015年05月31日 星期日 22时26分01秒
 ************************************************************************/

#ifndef _YC_HASH_H
#define _YC_HASH_H

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>

#define SIZE_BUF 12 //每一个查询关键字大小为11Byte ，以一个空格分开。
#define BUCKET_LEN 2 //hash散列表的数组--桶的大小，现在仅仅固定,以后考虑动态分配.
                     //一般数据量越大，桶越深；由于测试样本只有1243个，相对于数亿样本集而言，太小。所以本程序中暂定为2。
#define NUM 10 //频率前 NUM 。
typedef char * type; //定义每个查询关键字类型为char

typedef enum{
    FALSE = 0,
    TRUE
}STATUS;

//节点-数据结构定义
typedef struct _NODE{
    type key;
    unsigned int key_len;
    unsigned int occur_num;  //出现次数
    struct _NODE *next;  //链表
}NODE;

//散列表中每个数组元素-数据结构定义
typedef struct _HASH_TABLE{
    unsigned int hit_num; //冲突个数
    NODE * keys_chain;    //节点指针
}HASH_TABLE;

HASH_TABLE* yc_hash_table_init();
unsigned int yc_hash_function(char * str,int str_len);
NODE * yc_find_data_from_hash_table(HASH_TABLE * hashTb, type key, int key_len);
STATUS yc_insert_data_into_hash_table(HASH_TABLE * hashTb, type key,int key_len);
void yc_output_result(HASH_TABLE * hashTb); //打印散列表
void yc_print_str(char * str,int key_len);  //打印字符串
void yc_cpy_str(char * dst, char * src ,int str_len);
int yc_strcmp(char * str1,char * str2,int len1,int len2);//比较字符串（以短字符串为准）

NODE * BubbleSort(NODE * head);  //冒泡链表排序算法
NODE * InsertSort(NODE * head);  //直接插入链表排序算法
void QuickSort( NODE * head, NODE * tail ); //快速链表排序算法

#endif
