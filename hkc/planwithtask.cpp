#include "devil.hpp"
using namespace _home;
//void setSortAttribute(Task task[],int num,Sort sort[],int senceMax,Robot &robot);
int checkPutdown(int sort, int present,Graph G )
{
	int i;
	for(i=0;i<maxNode;i++)
	{
		if(G.getDirection(sort,i)==present)
			continue;
		if(G.getDirection(sort,i) == 4 && G.getStatus(sort,i)==1)
			return 4;
	}
}
int checkPuton(int sort,int present,Graph G)
{
	int i;
	for(i=0;i<maxNode;i++)
	{
		if(G.getDirection(sort,i)==present)
			continue;
		if(G.getDirection(sort,i) == 5 && G.getStatus(sort,i)==5)
			return 5;
	}

}
int checkGive(int sort,int present,Graph G)
{
	int i;
//	//cout<<"Now have not checkGive"<<endl;
     /*	for(i<maxNode;i++)
	{
		if(G.getDirection(sort,i)==present)
			continue;
		if(G.getDirection(sort,i) == 5 && G.getStatus(sort,i)==5)
			return 5;

	}*/
	return 0;
}
int checkConnection(int sort2,Graph G)
{
	////cout<<"check connection: "<<G.getDirection(sort2,0)<<endl;
	return G.getDirection(sort2,0); //返回大物体
}
int checkInside(int smallSort,Sort sort[])
{
	return sort[smallSort-1].getsInside();
}
int checkPutinFirst(int sort,int present,Graph G)
{
	int i;
	for(i=0;i<maxNode;i++)
	{
		if(G.getDirection(sort,i)==present)
		  continue;
		if(G.getDirection(sort,i)==-1 && G.getStatus(sort,i)==1)
		  return -1;
	}
	return 0;
}
/*
//获取putin任务的小物体的编号
int getPutinSortNum(int sort,Graph G)
{
	//cout<<"\nthis is getPutinSortNum\n";
	int i;
	for(i = 0; i < maxNode; i++)
	{
		if(G.getDirection(i.sort) == 1 && G.getStatus(i,sort) == 1)
		{
		//	//cout<<"i get it -> "<<i<<endl;
			return i;
		}
	}
//	//cout<<"\ngetPutinSortNum is over\n";
}*/
int checkPutin(int sort,int present,int &target,Graph G)
{
//	//cout<<"\nthis is checkPutin\n";
	int i;
//	//cout<<"sort -> "<<sort<<endl;
	for(i = 0;i < maxNode; i++)
	{
	 	if(G.getDirection(i,sort) == present)
	 	{
			continue;
		}
		if(G.getDirection(i,sort) == 1 && G.getStatus(i,sort)==1)
		{
		//	//cout<<"\ncheckPutin is over()\n";
			target = i;
			return 1;
	 	}
	} 
//	//cout<<"\ncheckPutin is over()\n";
	return 0;
}
int checkTakeout(int sort,int present,int &target,Graph G)
{
//	//cout<<"\nthis is checkTakeout\n";
	int i;
	////cout<<"sort -> "<<sort<<endl;
	for(i=0; i< maxNode;i++)
	{
		if(G.getDirection(i,sort) == present)
		{
			continue;
		}
		if(G.getDirection(i,sort) == -1 && G.getStatus(i,sort) == 1)
		{
		//	//cout<<"\ncheckTakeout is over\n";
			target = i;
			return -1;
		}
	}
}
int getPutinSort(int sort,Graph G)
{
	int i;
	for(i=0;i < maxNode;i++)
	{
		if(G.getDirection(sort,i)==-1 && G.getStatus(sort,i)==1)
			return i;
	} 
	return 0;
}
void Devil::planWithtask(Task task[],Sort sort[],int taskNum,int sortNum,Robot &robot,Graph &G)
{
	//cout<<"-----------------------------------------------------------"<<endl;
	int i=0,j=0;
	int errorFlag = 0;
//	G.printMatrix();
	checkHold(robot,G);
	for(i=0;i<maxNode;i++)
	{
		for(j=0;j<maxNode;j++)
		{
			if(G.getStatus(i,j)==0)
			  continue;
			if(G.getDirection(i,j)==4)	//putdown
			{
				//cout<<"\nthis is run putdown\n";
				G.setStatus(i,j,putdown(i,sort,robot,G));
				//cout<<"\nputdown is over\n";
			}
			else if(G.getDirection(i,j)==-4&&G.getStatus(i,j)==1) //puton
			{
				//cout<<"\nThis is run puton action\n";
				//cout<<sort[i-1].getsLoc()<<endl;
				//cout<<robot.getLoc()<<endl;
					move(i,sort,robot);
				//cout<<"i->"<<i<<" j->"<<j<<endl;
				if(sense(robot,i,sort,G) == 1)
				{
					//cout<<"I can see it \n";				
				}
				else
				{
					errorFlag = findErrorSort(robot,sort,i,G);
					//cout<<"errorFlag -> "<<errorFlag<<endl;
					if(errorFlag == -1)
					{
						//cout<<"I can't find it, i will give up this task,i am so sad\n";
						continue;
					}
				}
				if(sort[i-1].getsInside() == -1&&sort[i-1].getsLoc()==sort[j-1].getsLoc())
				{
					G.setStatus(i,j,1);
					//cout<<"This is run puton over\n";
					continue;

				}
				G.setStatus(i,j,puton(i,j,sort,robot,G));
				//cout<<"This is run puton over\n";
			}
			else if(G.getDirection(i,j)==6&&G.getStatus(i,j)==1) //give
			{
				//cout<<"\nThis is run give\n";
				move(i,sort,robot);
				if(sense(robot,i,sort,G) == 1)
				{
					//cout<<"I can see it\n";

				}
				else
				{
					errorFlag = findErrorSort(robot,sort,i,G);
					//cout<<"errorFlag -> "<<errorFlag<<endl;
					if(errorFlag == -1)
					{
						//cout<<"I can't find it, i will give up this task, i am so sad\n";
						continue;
					}
				}
				G.setStatus(i,j,puton(i,j,sort,robot,G));
				//cout<<"This is run give over\n";
			}
			else if(G.getDirection(i,j)==-1 &&G.getStatus(i,j)==1)	//takeout
			{
				
				//cout<<"This is run takeout\n";
				//cout<<i<<" "<<j<<endl;
				//cout<<j<<" "<<checkConnection(j,G)<<endl;
				//cout<<i<<" inside: "<<sort[i-1].getsInside()<<endl;
			//	if(sort[i-1].getsInside() == -1)
			//	{
					move(i,sort,robot);
					//cout<<"========================== this is fuckSence\n";
					if(sense(robot,i,sort,G) == 1)
					{
					
						if(sort[i-1].getsInside() == -1)
						{
							//cout<<"I see it, it not inside,takeout over()"<<endl;
							continue;
						}

					}
					else
					{
						errorFlag =	findErrorSort(robot,sort,i,G);
						if(errorFlag == -1)
						{
							//cout<<"errorFlag -> "<<errorFlag<<endl;
							if(errorFlag == -1)
							{
								//cout<<"I can't find it, i will give up this task, i am so sad\n";
								continue;
							}
						}
					}
			//	}
				//cout<<"================================== fuck sense is over\n";
				//cout<<"==================================fuck takeout\n";
				if(sort[i-1].getsInside()!=-1)	//确定为takeout
				{
				/*	if(sort[i].getsInside() != j)
					{
						//cout<<"Task,error!\n";
						G.setStatus(i,j,1);
						continue;
					}
				*/
					Devil::move(i,sort,robot);
					G.setStatus(i,j,Devil::takeout(i,sort,robot,G));
					//cout<<"=============== this is from fuck takeout\n";
					if(robot.getHold() == i && checkConnectionSmall(i,G) == 0)
					{
						PutDown(i);
						robot.setHold(0);
					}
				}
			//	if(checkConnection(j,G)==2)	//close
			//	{
			//		//cout<<"j->: "<<j<<endl;
			//		G.setStatus(j,0,close(j,sort,robot,G));
			//	}
				//cout<<"smallSort loc: "<<sort[i-1].getsLoc()<<endl;
				//cout<<"run takout over\n";
			}
			else if(G.getDirection(i,j)==1)	//putin
			{ 
				//cout<<"\n\nthis is putin action  "<<i<<" "<<j<<endl;
				move(i,sort,robot);
				if(sense(robot,i,sort,G) == 1)
				{
					//cout<<"I can see it\n";
				}
				else
				{
					errorFlag = findErrorSort(robot,sort,i,G);
					//cout<<"errorFlag -> "<<errorFlag<<endl;
					if(errorFlag == -1)
					{
						//cout<<"I can't find it, i will give up this task,i am so sad\n";
						continue;
					}
				}
				if(sort[i-1].getsInside() == j)
				{
					//cout<<"i have already in it\n";
					G.setStatus(i,j,1);	//设此任务为完成，修改于2018年4月27日
					continue;
				}
				//cout<<G.getStatus(i,j)<<endl;
				int signedTask = checkPutinFirst(i,G.getDirection(i,j),G);
				//cout<<"I have other task "<<signedTask<<endl;
				if(signedTask == -1) //takeout_fisrt
				{
					//cout<<"asd"<<endl;
					move(i,sort,robot);
					G.setStatus(i,sort[i-1].getsInside(),Devil::takeout(i,sort,robot,G));
				}
				if(checkPutinFirst(i,G.getDirection(i,j),G) == 0) //only_putin
				{
					//cout<<" checkPutInFirst -> "<<"0"<<endl;
					getSort(i,sort,robot,G);
					move(j,sort,robot);
					//cout<<"this putin I'm move"<<endl;
					open(j,sort,robot,G);
					G.setStatus(i,j,putin(i,j,sort,robot,G));
				}
				//cout<<G.getStatus(10,3)<<endl;
				//cout<<"This is putin action run over\n";
			}
			else if(G.getDirection(i,j)==2 && G.getStatus(i,j) == 1)	//close.低级处理
			{
				/*
				//cout<<"\nThis is run close\n";
				int smallsort = 0;
				int signedTask = checkPutin(i,2,smallsort,G);
				if(signedTask == 1)
				{		
				
					//cout<<"Before close, i have another task -> "<<signedTask<<endl;
					//cout<<" put "<<smallsort<<" in "<<i<<endl;
					move(smallsort,sort,robot);
					if(sense(robot,smallsort,sort,G) == 1)
					{
						//cout<<"I can see it\n";
					}
					else
					{
						errorFlag = findErrorSort(robot,sort,smallsort,G);
						//cout<<"errorFlag -> "<<errorFlag<<endl;
					}
					if(errorFlag != -1)
					{
						getSort(smallsort,sort,robot,G);
						move(i,sort,robot);
						open(i,sort,robot,G);
						G.setStatus(smallsort,i,putin(smallsort,i,sort,robot,G));
					}
					else
					{
						//cout<<"I can't dealwith it\n";
					}
				}
				if(sort[i-1].getsClosed() == 1)
				{	
					//cout<<"Now, is closed, i will continued;\n";
					continue;
				}
				if(sort[i-1].getsClosed() == 0)
					move(i,sort,robot);
				G.setStatus(i,j,close(i,sort,robot,G));
				//cout<<"\nrun close over\n";
				*/
			}
			else if(G.getDirection(i,j)==-2 && G.getStatus(i,j) == 1) //open
			{
				//cout<<"This is run open\n";
				int smallsort = 0;
				int signedTask = checkTakeout(i,-2,smallsort,G);
				if(signedTask == -1)
				{
					//cout<<"Before close, i have another task -> "<<signedTask<<endl;
					//cout<<" take "<<smallsort<<" out "<<i<<endl;
					move(i,sort,robot);
					if(sense(robot,smallsort,sort,G) == 1)
					{
						if(sort[smallsort-1].getsInside() == -1)
						{
							//cout<<"I see it,it not inside,takeout over\n";
							errorFlag = -1;
						}
					}
					else
					{
						if(sort[i-1].haveSmallSort != 0)
						{
							
							errorFlag = findErrorSort(robot,sort,smallsort,G);
							if(errorFlag == -1)
							{
								//cout<<"I can't find it,i will give up this task\n";
							}
						}
						else
						{
							errorFlag = -1;
						}
					}
					if(errorFlag != -1)
					{
						G.setStatus(smallsort,i,takeout(smallsort,sort,robot,G));
					}
				}
				if(sort[i-1].getsClosed() == 0)
				{
					G.setStatus(i,j,1);
					continue;
				}
				move(i,sort,robot);
				G.setStatus(i,j,open(i,sort,robot,G));
				//cout<<"\nrun open is over\n";
			}
			else if(G.getDirection(i,j)==5 && G.getStatus(i,j) == 1)	//pickup
			{
			/*	//cout<<G.getStatus(i,j)<<" pickup "<<endl;
				if(checkPutdown(robot.getHold(),i,G) == 4)
				{

					//先执行putdown
						int hold = robot.getHold();
						G.setStatus(hold,0,putdown(hold,sort,robot,G));
				}
				if(checkPutdown(robot.getPlate(),i,G)==4)
				{
					int plate = robot.getPlate();
					G.setStatus(plate,0,putdown(plate,sort,robot,G));
				}
				if(checkPuton(robot.getHold(),i,G) == 5)
				{
					//puton
					//暂不处理
				}
				if(checkPutinFirst(robot.getHold(),i,G)==-1)
				{
					int act2 = getPutinSort(robot.getHold(),G);
					move(act2,sort,robot);
					open(act2,sort,robot,G);
					G.setStatus(robot.getHold(),act2,putin(robot.getHold(),act2,sort,robot,G));
				}
				if(checkPutinFirst(robot.getPlate(),i,G)==-1)
				{
					int act2 = getPutinSort(robot.getPlate(),G);
					move(act2,sort,robot);
					open(act2,sort,robot,G);
					G.setStatus(robot.getHold(),act2,putin(robot.getHold(),act2,sort,robot,G));
				}
				move(i,sort,robot);
				G.setStatus(i,j,pickup(i,sort,robot,G));
		*/
			}
		   
		}
 	}
	//cout<<"===> planwithtask is over";
}

