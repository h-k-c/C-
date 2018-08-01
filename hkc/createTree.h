#ifndef __createTree_h__
#define __createTree_h__
#include<iostream>
#include<vector>
#include<map>
#include"Task.h"
#include"Sort.h"
#include"Node.h"
//int findSortByName(string name,string color,int sNum,Sort sort[]);
//int findStateByName(int sortNum,int sNum,Sort sort[]);
//int findHuman(Sort sort[],int sNum);
//void  ReintegrationTask(vector<Btree*> taskLin);
void CreateAndPut(vector<Btree*> taskTree,Task task[],Sort sort[],int sNum,int taskNum);
//void ReintegrationTask(vector<Btree*> taskLin);
#endif
