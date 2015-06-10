/*************************************************************************
	> File Name: yc_hash.c
	> Author: yangchao
	> Mail: yangchao9264@126.com
	> Created Time: 2015年06月01日 星期一 09时18分23秒
 ************************************************************************/

#include"yc_hash.h"

unsigned int yc_hash_function(char * str,int str_len) 
{
    unsigned int hash;
    unsigned char *p;
    int i;
    for(i = 0,hash = 0,p = (unsigned char *)str; i < str_len && p;i++,p++){
        hash = 31 * hash + *p;
    }
    return (hash & 0x7FFFFFFF);
}

HASH_TABLE * yc_hash_table_init()
{
    HASH_TABLE * hashTB = NULL;
    hashTB = (HASH_TABLE *)malloc(sizeof(HASH_TABLE) * BUCKET_LEN);
    if( NULL == hashTB ){
        printf("create HASH TABLE error!\n");
        return NULL;
    }
    memset(hashTB, 0,sizeof(HASH_TABLE) * BUCKET_LEN);
    return hashTB;
}

NODE * yc_find_data_from_hash_tabel(HASH_TABLE * hashTB,type key,int key_len)
{
        if( NULL == hashTB ){
        printf("NO chain when find data!\n");
        return NULL;
    }
    unsigned int hash_value;
    NODE * pNode;
    hash_value = yc_hash_function(key, key_len) % BUCKET_LEN;//将字符串映射成一个int型hash值
    pNode = hashTB[hash_value].keys_chain;
    for(; pNode ;){
        if(yc_strcmp(key, pNode->key, key_len, pNode->key_len) == 0){
            pNode->occur_num++;
            return pNode;
        }
        pNode = pNode->next;
    }
    return NULL;
}

STATUS yc_insert_data_into_hash_table(HASH_TABLE * hashTB, type key,int key_len)
{
    if(NULL == hashTB){
        printf("NO chain when find data!\n");
        return FALSE;
    }
    unsigned int hash_value;
    NODE * pNode, * pNewNode;
    hash_value = yc_hash_function(key, key_len) % BUCKET_LEN;
    printf("hash value is %d\t when key is ",hash_value);//打印构建散列表过程
    yc_print_str(key,key_len);
    
    hashTB[hash_value].hit_num++;
    pNode = hashTB[hash_value].keys_chain;

    if(NULL == pNode){
        if( NULL == (pNewNode = (NODE*)malloc(sizeof(NODE))) ){
	    printf("allocate NODE error");
            return FALSE;
	}

        if(NULL == (pNewNode->key = (char *)malloc(key_len * sizeof(NODE)))){
            printf("allocate key");
            return FALSE;
        }
        yc_cpy_str(pNewNode->key, key, key_len);
        pNewNode->key_len = key_len;
        pNewNode->next = NULL;
        pNewNode->occur_num = 1;
        hashTB[hash_value].keys_chain = pNewNode;

        return TRUE;
    }
    if(NULL !=(yc_find_data_from_hash_tabel(hashTB, key, key_len))){
        return FALSE;//如果发现需插入的值在链表中存在，则occur_num + 1,返回FALSE
    }
    //如果查询关键字在现有的链表中不存在，在链表尾插入
    for(; pNode->next ;){
        pNode = pNode->next;
    }
    if(NULL == (pNewNode = (NODE *)malloc(sizeof(NODE)))){
        printf("allocate NODE error ");
        return FALSE;
    }
    if(NULL == (pNewNode->key = (char *)malloc(key_len * sizeof(char)))){
        printf("allocate key");
        return FALSE;
    }
    yc_cpy_str(pNewNode->key, key ,key_len);
    pNewNode->key_len = key_len;
    pNewNode->next = NULL;
    pNewNode->occur_num = 1;
    pNode->next = pNewNode;
    return TRUE;
}
void yc_cpy_str(char * dst,char * src,int str_len)
{
    int i;
    for(i = 0 ;i < str_len; i++){
        *(dst + i) = *( src +i );
    }
}
void yc_output_result(HASH_TABLE * hashTB)
{
    
    int i;
    NODE * pNode;
    for( i = 0; i < BUCKET_LEN; i++ ){
        printf("\nthe BUCKET number ： %d   --hit_num is %d\n",i,hashTB[i].hit_num);
        //hashTB[i].keys_chain = BubbleSort(hashTB[i].keys_chain);    //对链表进行冒泡排序（从大到小）
         QuickSort( hashTB[i].keys_chain, NULL );    //使用链表快速排序（从大到小）
        for(pNode = hashTB[i].keys_chain; pNode ;pNode = pNode->next){    
            printf("\t BUCKET: %d key is ",i);
            yc_print_str(pNode->key,pNode->key_len); //打印第i个hash数组（第i个链表）的关键字和对应的出现频率
            printf("\t BUCKET: %d key_occur frequency is %d\n",i,pNode->occur_num);         
        }
    }
    printf("频率最高的关键字：");
    int j;
    NODE * max_key ;
    max_key->occur_num = 0;
    for( j =0; j < NUM; j++ ){
	for(i = 0;i < BUCKET_LEN ;i++){
	    if(max_key->occur_num < hashTB[i].keys_chain->occur_num){
                max_key->occur_num  = hashTB[i].keys_chain->occur_num;
		max_key->key = hashTB[i].keys_chain->key;
	    }
	}
     }
     printf("  key is ");
     yc_print_str(max_key->key,SIZE_BUF);       //打印频率最高的关键字和对应的出现频率
     printf(" key_occur frequency is %d\n",max_key->occur_num);         
}

void yc_print_str(char * str,int str_len)
{
    int i;
    for(i = 0; i < str_len; i++){
        printf("%c",*(str + i));
    }
    printf("\n");
}

int yc_strcmp(char * str1 ,char * str2,int len1,int len2) 
{
    int i = 0;
    for(i = 0; i<((len1 < len2)?len1:len2); i++){
        if(*(str1 + i) > *(str2 + i)) return 1;
        else if (*(str1 + i) == *(str2 + i)) continue;
        else return -1;
    }
    if(len1 < len2)
        return -1;
    else if(len1 == len2)
        return 0;
    else 
        return 1;

}
NODE * BubbleSort(NODE * head)
{
    NODE * endpt; /*控制循环比较*/
    NODE * p; /*临时指针变量*/
    NODE * p1;
    NODE * p2;

    p1 = (NODE *)malloc(sizeof(NODE));
    p1->next = head; 
    head = p1; /*让head指向p1节点，排序完成后，我们再把p1节点释放掉*/

    for (endpt = NULL; endpt != head; endpt = p) {
        for (p=p1=head; p1->next->next != endpt; p1=p1->next){
        if (p1->next->occur_num < p1->next->next->occur_num) { /*如果前面的关键字出现频率 比 后面关键字出现频率 小，则交换*/
        p2 = p1->next->next;
        p1->next->next = p2->next; 
        p2->next = p1->next;
        p1->next = p2; 
        p = p1->next->next;
        }
    }
    }

    p1 = head; 
    head = head->next; 
    free(p1); 
    p1 = NULL; /*p1置为NULL，保证不产生“野指针”，即地址不确定的指针变量*/
    return head;
}

NODE *InsertSort(NODE * head)
{
 NODE *first;  
 NODE *t;  
 NODE *p; 
 NODE *q;  
 
 first = head->next;  
 head->next = NULL;  

 while (first != NULL) 
 {
  for (t = first, q = head; ((q != NULL) && (q->occur_num < t->occur_num)); p = q, q = q->next); 
  first = first->next; 
  if (q == head)  head = t;   
  else  p->next = t;  
  t->next = q; /*完成插入动作*/
 }
 return head;
}

void QuickSort( NODE * head, NODE * tail )  
{  
    if ( head->next == tail || head->next->next == tail )  
        return;  
  
    NODE * mid = head->next;  
    NODE * p = head;  
    NODE * q = mid;  
    unsigned int pivot = mid->occur_num;  
    NODE * t = mid->next;  
      
    while ( t != tail )  
    {  
        if ( t->occur_num > pivot )  
            p = p->next = t;  
        else  
            q = q->next = t;  
        t = t->next;  
    }  
    p->next = mid;  
    q->next = tail;  
  
    QuickSort( head, mid );  
    QuickSort( mid, tail );  
}




















