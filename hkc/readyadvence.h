#ifndef __home_readyadvence_h__
#define __home_redayadvence_h__
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <iomanip>
#include <vector>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include "Sort.h"
#include "Robot.h"
#include "Task.h"
#include "InfoCons.h"
#include "Tasknum.h"
using namespace std;

void printVector(vector<unsigned int> v);
void getVector(int small[],vector<unsigned int> v);
void dealwithtask(const string &TASK,Task task[], int &taskMaxnum);
void dealwithsence(const string &STR,Sort sort[],Robot &robot, int &senceMax);
void dealwithInfoCons(const string &TASK,InfoCons info_cons[],int &numMax,string SIGN);
int findSortByName(int sNum,string name,Sort sort[]);
void judgewithCons(InfoCons cons_nn[],int consNn,Task task[],int taskNum,Sort sort[],int sortNum);
void updateTaskCons_not_notnot(Sort sort[],Task task[],InfoCons consNn[],InfoCons consn[],Robot robot,int sNum,int tNum,int cNum,int cnNum);
void aboutTaskLackMatch(Task task[],Sort sort[],int sNum,int tNum,Robot &robot);

void updateTask(Sort sort[],Task task[],int sortNum,int taskNum,Robot &robot);
void updateSenceByCons(Sort sort[],InfoCons con[],Robot &robot,int sortNum,int consNum);
void updateSenceByInfo(Sort sort[],InfoCons info[],Robot robot,int SNum,int infoNum);
void releaseSenceByCons(Sort sort[],InfoCons info[],Task task[],Robot &robot,int SNum,int infoNum,int tNum);
void debugTask(Task task[],Sort sort[],int taskNum,int sortNum,Robot &robot);
void buildTasknum(Task task[],Tasknum tasknum[],Sort sort[],int sortNum,int taskNum);
int FindSortAndSave_Info(Sort sort[],int sortNum,string str,bool fstr,string col,bool fcol,bool ftype,int sortnum[]);
int FindBigSortByLoc(Sort sort[],int Loc);
void deleteErrorLoc(Robot &robot,vector<unsigned int> sot,Sort sort[]); //在action.cpp中的sense函数中调用

void printTask(Task task[],int count);
void printScence(Robot  robot,Sort sort[],int count);
void printInfoCons(InfoCons info[],int count,string SIGN);

int judgeIsNotPutDownPlate(Task task[],Sort sort[],int tNum,Robot &robot);
#endif
