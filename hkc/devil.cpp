/*
 * Simulation@Home Competition
 * File: devil.cpp
 * Author: hkc
 * Affiliation: Multi-Agent Systems Lab.
 *              University of Science and Technology of China
 */

#include "devil.hpp"
#include <iostream>
#include <vector>
using namespace _home;
using namespace std;

//////////////////////////////////////////////////////////////////////////
Devil::Devil() :
Plug("hkc")
{
}

//////////////////////////////////////////////////////////////////////////
void Devil::Plan()
{

  //cout << "#(Devil): Init" << endl;
  //cout << "# EnvDes:\n" << GetEnvDes() << endl;
  //cout << "# TaskDes:\n" << GetTaskDes() << endl;
	Sort sort[30];
	Robot robot;
	Task task[30];
	InfoCons info[30];
    vector<Btree*> taskTree;
	InfoCons cons_not[30];
	InfoCons cons_notnot[30];
    string STR=GetEnvDes();
	string TASK=GetTaskDes();
	int senceMax= 0,taskMax=0,infoMax=0,cons_not_Max=0,cons_notnotMax=0;
	 dealwithsence(STR,sort,robot,senceMax);	
	dealwithtask(TASK,task,taskMax);
	printTask(task,taskMax);
	dealwithInfoCons(TASK,info,infoMax,"info");
	dealwithInfoCons(TASK,cons_not,cons_not_Max,"cons_not");
	dealwithInfoCons(TASK,cons_notnot,cons_notnotMax,"cons_notnot");
	printScence(robot,sort,senceMax);
	updateSenceByInfo(sort,info,robot,senceMax,infoMax);
	printScence(robot,sort,senceMax);
	updateSenceByCons(sort,cons_not,robot,senceMax,cons_not_Max);
    updateTask(sort,task,senceMax,taskMax,robot);
	printTask(task,taskMax);
    CreateAndPut(taskTree,task,sort,senceMax,taskMax);
    cout<<"--------------------开始处理任务----------------------------"<<endl;
    dealWithTask(taskTree,robot,sort);
    //dealWithTask2(robot,sort);
}

void Devil::Fini()
{
    cout << "#(Devil): Fini" << endl;
}   
