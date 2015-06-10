/*************************************************************************
	> File Name: yc_interview.c
	> Author: yangchao
	> Mail: yangchao9264@126.com
	> Created Time: 2015年05月31日 星期日 22时11分02秒
 ************************************************************************/

#include "yc_hash.h"
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>



int main()
{
    HASH_TABLE *hashTb = NULL;
    int fd = -1,rdsize;
    char buff[SIZE_BUF] = { 0 };
      
    char *file_path = "/home/yangchao/workspace/interview/testForTop10.txt";
    unsigned long int Query_num = 0;   //记录关键字的个数，通常较大（数亿个）

    hashTb = yc_hash_table_init();

    if(-1 == (fd = open(file_path,O_RDONLY))){
        printf("OPEN ERROR\n");
        return -1;
    }
    printf("OPEN Successfully!\n");
    while(rdsize = (int)read(fd,buff,SIZE_BUF)){
        yc_insert_data_into_hash_table( hashTb, buff, rdsize ); //构建散列表，同时会打印出建表过程
        Query_num++;
    }
    printf("th Query number is %ld\n",Query_num);  //打印 "查询关键字" 个数
    yc_output_result(hashTb); //打印散列表各个已排序的链表，同时输出频率前十的关键字和对应频率
    return 0;

}
