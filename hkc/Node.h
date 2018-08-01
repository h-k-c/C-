#ifndef __home_tNode_h__
#define __home_tNode_h__
#include<iostream>
#include<stdlib.h>
#include <map>
using namespace std;
typedef struct tNode{
   		 int NodeNum;//用于表示物体的确切的位置
    	 int sortNum;//用于表示物体的编号
         std:: multimap<int,multimap<int,string> > taskmultimap;//用于存储任务中涉及到的物体
    	 struct tNode *next;//用于指向下一个物体
}Btree;;
#endif
