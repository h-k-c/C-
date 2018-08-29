#include "devil.hpp"
#include <iostream>
#include <fstream>
using namespace _home;
using namespace std;

//////////////////////////////////////////////////////////////////////////
Devil::Devil() :
 Plug("emmmm")
{
	countMove = 0;
}

//////////////////////////////////////////////////////////////////////////
void Devil::Plan()
{
    //cout << "#(Devil): Init" << endl;
//    cout << "# EnvDes:\n" << GetEnvDes() << endl;
  //  cout << "# TaskDes:\n" << GetTaskDes() << endl;
    Sort sort[30];
    Robot robot;
    Task task[30];
    InfoCons info[30];
    InfoCons cons_not[30];
    InfoCons cons_notnot[30];
    Graph G;
    std::vector<Btree*> taskTree;
    Tasknum tasknum[15];
    string STR=GetEnvDes();
    string TASK=GetTaskDes();
    if(TASK.find("(:")==-1)
    {
       TASK = Translate(TASK);
    }
    int senceMax= 0,taskMax=0,infoMax=0,cons_not_Max=0,cons_notnotMax=0;
    int i=0,j=0;
    dealwithsence(STR,sort,robot,senceMax);
    printScence(robot,sort,senceMax);
    dealwithtask(TASK,task,taskMax);
    dealwithInfoCons(TASK,info,infoMax,"info");
    Sort::count = senceMax;
    dealwithInfoCons(TASK,cons_not,cons_not_Max,"cons_not");
    dealwithInfoCons(TASK,cons_notnot,cons_notnotMax,"cons_notnot");
    updateSenceByInfo(sort,info,robot,senceMax,infoMax);
    judgewithCons(cons_not,cons_not_Max,task,taskMax,sort,senceMax);
    judgewithCons(cons_notnot,cons_notnotMax,task,taskMax,sort,senceMax);
    updateTaskCons_not_notnot(sort,task,cons_notnot,cons_not,robot,senceMax,taskMax,cons_not_Max,cons_notnotMax);
    updateSenceByCons(sort,cons_not,robot,senceMax,cons_not_Max);
    updateTask(sort,task,senceMax,taskMax,robot);
    releaseSenceByCons(sort,cons_not,task,robot,senceMax,cons_not_Max,taskMax);
    planwithcons_not_info(cons_not,task,sort,robot,cons_not_Max,taskMax);
    planwithcons_notnot_info(cons_notnot,task,sort,robot,cons_notnotMax,taskMax);
    printTask(task,taskMax);
    CreateAndPut(taskTree,task,sort,robot,senceMax,taskMax,cons_not,cons_not_Max,cons_notnot,cons_notnotMax);

   // cout<<"--------------------开始处理任务----------------------------"<<endl;
    dealWithTask(taskTree,task,taskMax,robot,sort,senceMax,cons_notnot,cons_notnotMax,cons_not,cons_not_Max);
}

void Devil::Fini()
{
    cout << "#(Maricle-test): Fini" << endl;
}
