/*
 * Simulation@Home Competition
 * File: devil.hpp
 * Author: Ranran Li
 * E-mail: 921090271@qq.com.
 * Affiliation: Innovation Lab.
 *              HeFei Normal University.
 */

#ifndef __home_devil_HPP__
#define __home_devil_HPP__

#include "cserver/plug.hpp"
#include "class.h"
#include "Node.h"
#include <vector>
int checkConnectionSmall(int sot,Graph G);
namespace _home
{

    class Devil : public Plug
    {
    public:
        Devil();
		int countMove;
       		 void planWithtask(Task task[],Sort sort[],int taskNum,int sortNum,Robot &robot,Graph &G);
		int move(int sot,Sort sort[],Robot &robot);
		int open(int sot,Sort sort[],Robot &robot,Graph &G);
		int takeout(int sot,Sort sort[],Robot &robot,Graph &G);
		int puton(int sotx,int soty,Sort sort[],Robot &robot,Graph &G);
		void planwithcons_not_info(InfoCons cons_not[],Task task[],Sort sort[],Robot &robot,int consnotNum, int taskNum);
		void planwithcons_notnot_info(InfoCons cons_notnot[],Task task[],Sort sort[],Robot &robot,int consnotnotNum,int taskNum);
		int checkContainer(Robot &robot,int sot,Sort sort[],Graph &G);
		void dealAlreadySenseNullTask(Robot &robot,Sort sort[],Task task[],int taskNum,Graph &G);
		void sense(Robot robot);
		int findErrorSort(Robot &robot,Sort sort[],int target,Graph &G);
		int sense(Robot &robot,int target,Sort sort[],Graph &G);
		int close(int sot,Sort sort[],Robot &robot,Graph &G);
		int getSort(int sot,Sort sort[],Robot &robot,Graph &G);
		int putin(int smallsot,int sot,Sort sort[],Robot &robot,Graph &G);
		int putdown(int sot,Sort sort[],Robot &robot,Graph &G);
		int pickup(int sot,Sort sort[],Robot &robot,Graph &G);
		void dealwithputdown(Task task[],int taskNum,Sort sort[],Robot &robot);
		void dealWithClose(Task task[],int taskNum,Sort sort[],Robot &robot,Graph &G);
		void dealwithgoto(Task task[],int taskNum,Sort sort[],Robot &robot);
		void dealwithpickup(Task task[],int taskNum,Sort sort[],Robot &robot,Graph &G);
		void dealWithErrorInfo(Task task[],int taskNum,Sort sort[]);
		void checkHold(Robot &robot,Graph &G);
		void checkPlate(Robot &plate,Graph &G);
        	void CreateAndPut(std::vector<Btree*> &Tasktree,Task task[],Sort sort[],Robot &robot,int Num,int taskNum,InfoCons cons_not[],int cons_not_Max,InfoCons cons_notnot[],int cons_notnotMax); 
int findSortByName(string name,string color,int sNum,int taskNum,Task task[],Sort sort[],InfoCons cons_not[],int cons_not_Max,InfoCons cons_notnot[],int cons_notnotMax,Robot robot); 
        	void dealWithTask(std::vector<Btree*> Tasktree,Task task[],int taskMax,Robot &robot,Sort sort[],int sNum,InfoCons cons_notnot[],int cons_notnotMax,InfoCons cons_not[],int cons_not_Max);
        void Plan();
		void getLostLocFromTask(Task task[],int taskNum,Sort sort[]);
        void Fini();
    };//Plug

}//_home

#endif//__home_devil_HPP__
//end of file
