/*************************************************************************
	> File Name: createTree.cpp
	> Author:hkc 
    > Mail: 2605245956@qq.com
	> Created Time: 2018年07月25日 星期三 11时23分41秒
 ************************************************************************/
#include "createTree.h"
using namespace std;
int findSortByName(string name,string color,int sNum,Sort sort[]);
int findStateByName(int sortNum,int sNum,Sort sort[]);
int findHuman(Sort sort[],int sNum);
int findSortByName(string name,string color,int sNum,Sort sort[]){
    int i;
    for(i=0;i<sNum;i++){
        if(sort[i].getsName()==name&&sort[i].getsColor()==color){
            return i;
        }
    }
    return -1;
}
int findSateByName(int sortNum,int sNum,Sort sort[]){
    int i;
    for(i=0;i<sortNum;i++){
        if(sort[i].getsNum()==sNum){
            return sort[i].getsLoc();
        }
    }
    return -1;
}
int findHuman(Sort sort[],int sNum){
    int i;
    for(i=0;i<sNum;i++){
        if(sort[i].getsName()=="human"){
            return i;
        }
    }
    return -1;
}
//函数的主要目的是创建节点找到节点的关系，然后放到把第一个节点放到容器中；
void CreateAndPut(vector<tNode*> taskTree,Task task[],Sort sort[],int sNum,int taskNum){
    tNode *b1;
    tNode *b2;
    int i;
    for(i=0;i<taskNum;i++){
        if(task[i].getTaskNamex()!=""&&task[i].getTaskNamey()!=""){
            multimap<int,string> task1;
            multimap<int,string> task2;
            //找到物体的编号
            int sortNum1=findSortByName(task[i].getTaskNamex(),task[i].getTaskColorx(),sNum,sort);
            int sortNum2=findSortByName(task[i].getTaskNamey(),task[i].getTaskColory(),sNum,sort);
            //找到物体的准确的位置
            int state1=findStateByName(sortNum1,sNum,sort);
            int state2=findStateByName(sortNum2,sNum,sort);
            b1->NodeNum=state1;
            b1->sortNum=sortNum1;
            b2->NodeNum=state2;
            b2->sortNum=sortNum2;
            cout<<"找到了任务的两个物体，位置是："<<b1->NodeNum<<"--->"<<b2->NodeNum<<endl;
            if(task[i].getTaskAction()=="puton"){
                task1.insert(make_pair(b1->sortNum,"pickup"));
                b1->taskmultimap.insert(make_pair(b1->NodeNum,task1));
                task2.insert(make_pair(b1->sortNum,"putdown"));
                b2->taskmultimap.insert(make_pair(b2->NodeNum,task2));//主要的问题是在使用Map的过程中假如key值是一样的不知道是覆盖还是把新的动作添加到新的容器中
                b2->next=NULL;
                b1->next=b2;
            }
            if(task[i].getTaskAction()=="putin"){
               task1.insert(make_pair(b1->sortNum,"pickup"));
               b1->taskmultimap.insert(make_pair(b1->NodeNum,task1));
               task2.insert(make_pair(b1->sortNum,"putin"));
               b2->taskmultimap.insert(make_pair(b2->NodeNum,task2));
               b1->next=b2;
               b2->next=NULL;
            }
            if(task[i].getTaskAction()=="takeout"){
                task1.insert(make_pair(b1->sortNum,"takeout"));
                b1->taskmultimap.insert(make_pair(b1->NodeNum,task1));
                task2.insert(make_pair(b1->sortNum,"takeout"));
                b2->taskmultimap.insert(make_pair(b2->NodeNum,task2));
                b1=b2;
                b1->next=NULL;
            }
        }
        if(task[i].getTaskNamex()!=""||task[i].getTaskNamey()==""){
            multimap<int,string> task1;
            int sortNum1=findSortByName(task[i].getTaskNamex(),task[i].getTaskColorx(),sNum,sort);
            int state1=findStateByName(sortNum1,sNum,sort);
            b1->NodeNum=state1;
            b1->sortNum=sortNum1;
            cout<<"这是一个只关于一个物体的任务，这个物体是:"<<b1->NodeNum<<endl; 
            if(task[i].getTaskAction()=="goto"||task[i].getTaskAction()=="open"||task[i].getTaskAction()=="close"){
               task1.insert(make_pair(b1->sortNum,task[i].getTaskAction()));
               b1->taskmultimap.insert(make_pair(b1->NodeNum,task1));
            }
            if(task[i].getTaskAction()=="give"){
                multimap<int,string> task2;
                int state2=findHuman(sort,sNum);//找到人的位置
                task2.insert(make_pair(b1->NodeNum,"pickup"));
                task1.insert(make_pair(b1->sortNum,"putdown"));
                b1->taskmultimap.insert(make_pair(b1->NodeNum,task2));
                b2->taskmultimap.insert(make_pair(state2,task1));
                b1->next=b2;
                b2->next=NULL;
            }
        }
            //每一个任务的节点都完成后，就可以把每一个先访问的节点放到容器中；
            taskTree.push_back(b1);
    }
}
