#ifndef __home_readyadvence_h__
#define __home_redayadvence_h__
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <iomanip>
#include <map>
#include <vector>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include "Sort.h"
#include "Robot.h"
#include "Task.h"
#include "InfoCons.h"
using namespace std;
void dealwithtask(const string &TASK,Task task[], int &taskMaxnum);
void dealwithsence(const string &STR,Sort sort[],Robot &robot, int &senceMax);
void dealwithInfoCons(const string &TASK,InfoCons info_cons[],int &numMax,string SIGN);
void updateTask(Sort sort[],Task task[],int sortNum,int taskNum,Robot &robot);
void dealwithInfoCons(const string &TASK,InfoCons info_cons[],int &numMax,string SIGN);
void updateSenceByCons(Sort sort[],InfoCons con[],Robot &robot,int sortNum,int consNum);
void updateSenceByInfo(Sort sort[],InfoCons info[],Robot robot,int SNum,int infoNum);
void printTask(Task task[],int count);
int findSortByName(int sNum,string name,string color,Sort sort[]);
int findSortByName(int sNum,string name,Sort sort[]);
void printScence(Robot  robot,Sort sort[],int count);
void printInfoCons(InfoCons info[],int count,string SIGN);
#endif
