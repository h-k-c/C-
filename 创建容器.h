#ifndef __home_createTree_h__
#define __home_createTree_h__
#include<iostream>
#include<string.h>
#include<map>
#include<vector>
#include"Task.h"
#include"Sort.h"
#include"devil.hpp"
#include<stdlib.h>
#define MAX 10
using namespace std;
struct tNode{
    int NodeNum;//用于表示物体的确切的位置
    int sortNum;//用于表示物体的编号
    multimap<int,multimap<int,string> > taskmultimap;//用于存储任务中涉及到的物体
    struct tNode *next;//用于指向下一个物体
};
vector<tNode*> taskTree;
int findSortByName(string name,string color,int sNum,Sort sort[]);
int findStateByName(int sortNum,int sNum,Sort sort[]);
int findHuman(Sort sort[],int sNum);
void CreateAndPut(vector<tNode*> taskTree,Task task[],Sort sort[],int sNum,int taskNum);
#endif
