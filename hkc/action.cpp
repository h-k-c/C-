#include "devil.hpp"
using namespace _home;

int getAskLoc(string str,Sort sort[])
{
	int loc = -1;
	int left = 0,right = 0, mid = 0;
	int obj1,obj2;
	if( str == "not_known")
	{
		return -1;
	}
	string str1,str2,str3;
	left = str.find("(");
	mid = str.find(",");
	right = str.find(")");
	str1 = str.substr(0,left);
	str2 = str.substr(left+1,mid-left-1);
	str3 = str.substr(mid+1,right-mid-1);
	if(str1 == "inside")
	{
		obj2 = atoi(str3.c_str());
		obj1 = atoi(str2.c_str());

		loc = sort[obj2-1].getsLoc();
		if(sort[obj1-1].getsLoc() == loc)
		{
			// //cout<<"same loc error, i will return in inside\n";
			// //cout<<"This is askloc i can't get location :( \n";
			return -1;
		}
		sort[obj1-1].setsInside(obj2);
		// //cout<<"getinside "<<obj1<<" "<<sort[obj1-1].getsInside()<<endl;
		sort[obj2-1].sinsideD.push_back(obj1);
//		loc = sort[obj2-1].getsLoc();
		sort[obj1-1].setsLoc(loc); //此行有bug不知道为什么
		// //cout<<"This is askloc i get location :) \n";
		// //cout<<obj1<<" location is "<<sort[obj1-1].getsLoc()<<endl;

	}
	if(str1 == "at")
	{
		loc = atoi(str3.c_str());
		obj1 = atoi(str2.c_str());
		// if(sort[obj1-1].getsLoc() == loc)
		// {
		// 	// //cout<<"same loc error, i will return in at\n";
		// 	// //cout<<"This is askloc i can't get location :( \n";
		// }
		sort[obj1-1].setsLoc(loc);//同上面一行一样
		sort[obj1-1].setsInside(-1);
		// //cout<<"This is askloc i get location :) \n";
		// //cout<<obj1<<" location is "<<sort[obj1-1].getsLoc()<<endl;
	}
	return loc;
}
int checkTakeout(int sotx,int soty,Graph G)
{
	return G.getDirection(sotx,soty);
}
int checkConnectionBig(int sot,Graph G,int taskCode,int present)
{
	int i = 0;
	// //cout<<"This is checkConnectionBig()\n";
	for( i=0; i < maxNode; i++)
	{
        if( i == present)
            continue;
		if(G.getDirection(i,sot) == taskCode && G.getStatus(i,sot)==1)
		{
			return i;
 		}
 	}
	// //cout<<"checkConnectionBig() is over!()\n";
	return 0;
} 
int checkConnectionLoc(int sot,Graph G)
{
	for(int i=0; i<maxNode;i++)
	{
		if(G.getStatus(sot,i)==1)
			return i;
	}
}
int checkConnectionSmall(int sot,Graph G)
{
    int i=0;
    for(i=0; i<maxNode; i++)
     {
        if(G.getStatus(sot,i)==1)
         {
            // //cout<<sot<<" connection with "<< i <<endl;
            return G.getDirection(sot,i);
     	}    
    }
    return 0;
} 
int checkConnectionSmall(int sot[],Sort sort[],Graph G,int count)
{
	int i = 0,j=0;
	for(i=0; i<count;i++)
  	{
		if(sot[i]==0)
			return 0;
		
		for(j=0;j<maxNode;j++)
  		{
			//若有需要可以增加对任务的判断
			if(G.getStatus(sot[i],j)==1)
			{
				if(sort[sot[i]-1].getsLoc() == sort[sot[0]-1].getsLoc() && sot[i]!=sot[0])
				{	
					// //cout<<"sot[i] ->"<<sot[i]<<" j -> "<<j<<endl;	
					return sot[i];
				}
			}
		}
	}
	return 0;
}
//第一个参数为大物体编号
int Devil::checkContainer(Robot &robot,int sot,Sort sort[],Graph &G)
{
	int smallSort[5] = {0};
	int flag = 0;
	vector<unsigned int> sense;
	Sense(sense);
	deleteErrorLoc(robot,sense,sort);
	for(vector<unsigned int>::iterator it = sense.begin();it!=sense.end();it++)
	{
		// //cout<<"I can see "<<*it<<endl;
		sort[*it - 1].suchSense = 1;
		sort[*it - 1].setsLoc(robot.getLoc());
		if(sort[*it-1].getsInside() != -1)
		{
			// //cout<<"I am in container\n";
			int obj2 = sort[*it -1].getsInside();
			if(sort[*it-1].getsLoc() != sort[obj2-1].getsLoc())
			{
				// //cout<<"I'm in a fault container\n";
				sort[*it-1].setsInside(-1);
			}
		}
	}
	getVector(smallSort,sense);
//	smallSort = sort[sot-1].sinsideD;
	// //cout<<"This is checkContainer ,check: "<<sot<<" get -> ";
//	printVector(sense);
	//<<smallSort<<endl;
	if(smallSort[0] == 0)
	{
		return 0;
 	}
	flag = checkConnectionSmall(smallSort,sort,G,5);
	if(flag == robot.getHold()||robot.getPlate())
	{
		// //cout<<"THis sort in body,"<<flag<<endl;
		flag = 0;
	}
	// //cout<<"flag -> "<<flag<<endl;
	// //cout<"checkContainer is over\n";
	return flag;
}
int Devil::move(int sot,Sort sort[],Robot &robot)
{
	// //cout<<"this is move\n";
	bool flag=0;
	string loc;
	// //cout<<"sot's loc "<<sort[sot-1].getsLoc()<<endl;
	if(sort[sot-1].getsLoc()==-1)
	{
		// //cout<<"this loc is error,move over\n";
		return 0;
	}
	
	if(robot.getLoc()!= sort[sot-1].getsLoc())
 	{
		 flag=Move(sort[sot-1].getsLoc());
		//  //cout<<"I will move "<<sort[sot-1].getsLoc()<<endl;
		robot.setLoc(sort[sot-1].getsLoc());
		if(robot.getHold()!=0)
            sort[robot.getHold()-1].setsLoc(robot.getLoc());
        if(robot.getPlate()!=0)
            sort[robot.getPlate()-1].setsLoc(robot.getLoc());
	}

	// //cout<<"robot's loc "<<robot.getLoc()<<endl;
	// //cout<<"\nmove over\n";
	if(flag == 1)
	{
		countMove++;
	}
	return flag;
}
void Devil::checkPlate(Robot &robot,Graph &G)
{
	// //cout<<"This is checkPlate\n";
	int plate = robot.getPlate();
	if(plate == 0) {
		return;
	} else {
		if(checkConnectionSmall(plate,G)==0)
		{
			FromPlate(plate);
			robot.setPlate(0);
			PutDown(plate);
			// //cout<<"This sort in my plate is useless i will putdown\n";
		}
	}

	// //cout<<"checkPlate()\n";
}
void Devil::checkHold(Robot &robot,Graph &G)
{
	// //cout<<"{{{{{{{{{{{{{This is checkHold}}}}}}}}}}}}}}}\n";
	int hold = robot.getHold();
	int flag = 0;
	if(hold == 0)
	{
		return;
	}
	else
	{
		// //cout<<"robot.getUseHold()->"<<robot.getUsehold()<<endl
		// 	<<"robot.getUseplate()->"<<robot.getUseplate()<<endl;
		if(robot.getUsehold() == 0 && robot.getUseplate() == 0)
		{
			if(checkConnectionSmall(hold,G) == 0)
			{
				PutDown(hold);
				robot.setHold(0);
				// //cout<<"This sort in my hand is useless i will putdown "<<hold<<endl;
			}
			if(checkConnectionSmall(hold,G)==4)
			{
				G.setStatus(hold,0,PutDown(hold));
				robot.setHold(0);
				// //cout<<"This sort i need putdown"<<endl;
			}
		}
		else if(robot.getUsehold() == 1 && robot.getUseplate() == 0)
		{
			ToPlate(hold);
			robot.setPlate(hold);
			robot.setHold(0);
			robot.setUseplate(4);
			robot.setUsehold(0);
		}
	}
	// //cout<<"{{{{{{{{{{{{{{{{{{{{{{{{{{checkHold is over}}}}}}}}}}}}}}}}}}\n";

}
int checkOpen(int sot,Sort sort[])
{
	int flag = 0;
	if(sort[sot-1].getsClosed()== false)
	{
		flag = 1;
	}
	return flag;
}

int Devil::open(int sot,Sort sort[],Robot &robot,Graph &G)
{
	// //cout<<"\n==================================================="<<endl;
	int flag = 0;
	if(sort[sot-1].getsType() != "container")
	{
		// //cout<<"this is not container\n";
		return 1;
	}
	if(!sort[sot-1].getsClosed())
	{
		// //cout<<"No."<<sot<<" closed "<<sort[sot-1].getsClosed()<<endl;
		// //cout<<"==================================================="<<endl;
		return 1;
	}
//	if(G.getStatus(sot,0)==0)
//	  return 1;
	int checkHold = 0, checkPlate=0;
	//cout<<"\nthis is open, i will checkHold\n";
	checkHold = checkConnectionSmall(robot.getHold(),G);
	//cout<<"\nthis is open, checkHold is over\n";
	//cout<<"\nthis is open, i will checkPlate\n";
	checkPlate = checkConnectionSmall(robot.getPlate(),G);
	// //cout<<"\nthis is open, checkPlate is over\n";
	if(robot.getUsehold()==0&&robot.getUseplate()==0)
    {
		//cout<<"deal with something in open()\n";
		if(checkHold!=0&&robot.getHold()!=0&&robot.getPlate()==0)
		{
			//cout<<"Before open big sort,my hand have other sort, i need it->"<<robot.getHold()<<" put it in plate\n";
			ToPlate(robot.getHold());
			robot.setPlate(robot.getHold());
			robot.setHold(0);
		}
		if(checkHold!=0&&checkPlate!=0&&robot.getHold()!=0&&robot.getPlate()!=0)
		{
			//cout<<"In my hand and plate sort i need they,so i will putdown hand->"<<robot.getHold()<<endl;
			PutDown(robot.getHold());
			robot.setHold(0);
		}
		if(checkHold!=0&&checkPlate==0&&robot.getHold()!=0&&robot.getPlate()!=0)
		{
			//cout<<"I need my hand and i don't need my plate,so i will putdown my plate,let my hand to my plate"<<endl;
		//	//cout<<"这个地方步骤有些多余,还可以省略"<<endl;
			PutDown(robot.getHold());
		//	FromPlate(robot.getPlate());
		//	PutDown(robot.getPlate());
		//	PickUp(robot.getHold());
		//	ToPlate(robot.getHold());

		//	robot.setPlate(robot.getHold());
			robot.setHold(0);
		}
  //      if(checkConnectionSmall(robot.getHold(),G)!= 0 && robot.getHold()!=0)
  //    {
  //          //cout<<"Befor open big sort,my hand have other sort, i need it -> "<<robot.getHold()<<" i will put it in my plate"<<endl;
  //          ToPlate(robot.getHold());
  //          robot.setPlate(robot.getHold());
  //          robot.setHold(0);
 //       }
 		if(checkHold==0&&robot.getHold()!=0)
		{
			//cout<<"Before open action,my hand has a useless sort,i will putdown ->"<<robot.getHold()<<endl;
			

			PutDown(robot.getHold());
			robot.setHold(0);
		}
  //      else if(checkConnectionSmall(robot.getHold(),G)==0&&robot.getHold()!=0)
   //    {
   //         //cout<<"Before open big sort,my hand have other sort, i need pudown it -> "<<robot.getHold()<<endl;
   //         PutDown(robot.getHold());
   //         robot.setHold(0);
    //    }
    }
    //此处对约束进行处理
    if(robot.getUsehold()==1)
    {
		//cout<<"this is open, robot.getUsehold == 1"<<endl;
		if(robot.getHold() != 0 && robot.getPlate() == 0)
		{
		   	ToPlate(robot.getHold());
      	    robot.setPlate(robot.getHold());
       	    robot.setHold(0);
       	    robot.setUsehold(0);
      	    robot.setUseplate(1);
		}
		if(robot.getHold() == 0 )
		{
			robot.setUsehold(0);
		}
    }
    if(robot.getUseplate()==1&&robot.getHold()!=0)
    {
           PutDown(robot.getHold());
           robot.setHold(0);
    }

	if(checkOpen(sot,sort)==0)
	{
		flag = Open(sot);

			sort[sot -1].setsClosed(0);

		//cout<<"Sir,I'm open :"<<sot<<" statue :"<<flag
			//<<" checkOpen result :"<<checkOpen(sot,sort)<<endl;	
	} else if(checkOpen(sot,sort)== 1)
	{
        flag = -1;
	}
	//cout<<"open() is over"<<endl;
	//cout<<"====================================================="<<endl;
	return flag;
}

int Devil::takeout(int sot,Sort sort[],Robot &robot,Graph &G)
{
	//cout<<"\nthis is takeout\n";
	int flag = 0,checkOpen = 0;
	int act2 = sort[sot-1].getsInside();
	//cout<<"this is my location -> "<<robot.getLoc()<<" the target is "<<act2<<endl
	//	<<" the target location is -> "<<sort[act2-1].getsLoc()<<endl;
	if(robot.getLoc() != sort[act2-1].getsLoc() && act2 != -1)
	{
		move(act2,sort,robot);
	}

//	if(G.getStatus(sot,act2)==0)
//	  return 0;
	//cout<<"This is take -> "<<sot<<" from -> "<<act2<<endl;
	checkOpen = open(act2,sort,robot,G);
	if(checkOpen==1)
	{
		//cout<<"I open this sort ->"<<act2<<endl;
	}
	else if (checkOpen == 0 )
	{
		//cout<<"Sorry, I can't open this sort -> "<<act2<<endl;
	}
	else if(checkOpen == -1)
    {
        //cout<<"door is opened\n";
    }
	if(robot.getHold()!=0 && robot.getPlate() == 0 && robot.getUseplate() == 0)
	{
		ToPlate(robot.getHold());
		robot.setPlate(robot.getHold());
		robot.setHold(0);
	}
	//检查有没有其他的takeout任务，-1代表takeout，详情可见Graph.h
	int checkConnect = checkConnectionBig(act2,G,-1,sot);
	if(checkConnect != 0)
	{
		if(sort[checkConnect -1].getsInside() == act2) {
			//cout<<"checkConnect ===> "<<checkConnect<<endl;
			TakeOut(checkConnect,act2);
			int flag1 = PutDown(checkConnect);
			if(flag1 == 1)
			{
				sort[checkConnect-1].setsInside(-1);
			}
			G.setStatus(checkConnect,act2,flag1);
			//cout<<checkConnect<<" "<<act2<<" "<<G.getStatus(checkConnect,act2)<<endl;
		}
	}
	//takeout前看一下
//	//cout<<"Before takeout, i will look look\n";
//	if(sense(robot,sot,sort,G))
//	{
//		//cout<<" i can takeout it\n";
	if(act2 != -1)
   		flag = TakeOut(sot,act2);
//	}
//	else
//	{
//		findErrorSort(robot,sort,sot,G);
//		//cout<<" i can't takeout it\n";
//	}

	if(flag == 0)
	{
		//cout<<"takeout error!\n";
		//cout<<"this sort's alreadySense:"<<sort[sot-1].alreadySense<<" "<<"the robot's thisLocHaveSort:"<<robot.thisLocHaveSort<<endl;
		if(sort[sot-1].alreadySense == 1 && robot.thisLocHaveSort == 1)
		{
			//cout<<"I will try pickup it\n";
			sort[sot-1].setsInside(-1);
			flag = PickUp(sot);
			//cout<<"pickup result:"<<flag<<endl;
		}
		if(sort[sot-1].suchSense == 1 && flag == 0)
		{
			//cout<<"This is target:"<<sot<<" suchSense == 1\n";
			//cout<<"I will try pickup it\n";
			flag = PickUp(sot);
			//cout<<"pickup result:"<<flag<<endl;
		}
	}
/*	
 *	if(flag == 0)
 *	{
 *		//cout<<"THis is takeout(), i will open :"<<act2<<endl;
 *		Open(act2);
 *		//cout<<"This is takeout(), open is over "<<endl;
 *		flag = TakeOut(sot,act2);
 *	}	
 */
    if(flag == 1)
    {
        robot.setHold(sot);
        sort[sot-1].setsInside(-1);
    }
	//cout<<"Sir, I'm takeout: "<<sot<<" from "<<act2<<endl;
	//cout<<"takeout is over\n";
	return flag;
}

int Devil::close(int sot,Sort sort[],Robot &robot,Graph &G)
{
	//cout<<"this is close\n";
	int flag = 0,flag2=0;
	int check_container = 0;
	//在关闭前应当检查该物体内部有没有
	//其他任务所需要的物品
	check_container = checkContainer(robot,sot,sort,G);
	//cout<<"check_container ->"<<check_container<<endl;
	//if(check_container != 0 && sense(robot,check_container,sort,G))
	if(check_container != 0 && check_container != sot)
	{
		//cout<<"In this container,have a sort -> ";
	//	printVector(sort[sot-1].sinsideD);
		//cout<<" i need it"<<endl;
		flag2 = takeout(check_container,sort,robot,G);
		if(checkTakeout(check_container,sot,G)==-1)
			G.setStatus(check_container,sot,flag2);
	}
//	if(G.getStatus(sot,0)==0)
//	{
//		return 0;
//	}

	if(robot.getHold()&&checkConnectionSmall(robot.getHold(),G)==0)
	{
		//cout<<"My hand has sort,but I don't need it"<<endl;
		PutDown(robot.getHold());
		robot.setHold(0);
	}

	if(sort[sot-1].getsClosed()==0)
	{
		//此处可以检查一下手上的东西有没有用
		//如果没有用可以扔掉
		if(robot.getHold()!=0&&robot.getPlate()==0)
		{
			ToPlate(robot.getHold());

			robot.setPlate(robot.getHold());
			robot.setHold(0);

			flag=Close(sot);
			//cout<<"Sir, I'm closed the: "<<sot<<endl;
		}
		else if(robot.getHold()!=0 && robot.getPlate()!=0)
		{
			PutDown(robot.getHold());
			flag = Close(sot);
	//		PickUp(robot.getHold());
			robot.setHold(0);
			//cout<<"Sir, I'm closed the: "<<sot<<endl; 
		}
		if(robot.getHold()==0 && flag == 0)
		{
			flag = Close(sot);
			//cout<<"Sir, I'm closed the: "<<sot<<endl;
		}
	}
	sort[sot-1].setsClosed(flag);
	return flag;
}
int Devil::getSort(int sot,Sort sort[],Robot &robot,Graph &G)
{
	//cout<<"\n***************************************\n";
	//cout<<"this is getSort\n";
	if(robot.getHold() == sot)
	{
		//cout<<"getSort is over\n";
		//cout<<"***************************************\n";
		return 1;
	}
	int flag = 0;
	checkHold(robot,G);
	//cout<<"I want get "<<sot<<endl;
    if(robot.getLoc() != sort[sot-1].getsLoc())
    {
        move(sot,sort,robot);
        if(sort[sot-1].getsInside()!=-1)
        {
			//cout<<"This is getSort, i will into takeout\n";
            flag = takeout(sot,sort,robot,G);
			//cout<<"I from takeout() get to getSort()\n";
        }
		else
		{	//cout<<"This is getSort, i will into pickup\n";
            flag = pickup(sot,sort,robot,G);
			//cout<<"I from pickup() get to getSort()\n";
		}
    }
    else
    {
        //cout<<"This sort loc same with me"<<endl;
		if(robot.getHold() !=0 && robot.getHold() != sot)
		{
			PutDown(robot.getHold());
			robot.setHold(0);
		}
        if(sort[sot-1].getsInside()!=-1)  //inside
        {
			//cout<<"I will into takeout()\n";
            flag = takeout(sot,sort,robot,G);
			//cout<<"I get out from takeout()\n";
        }
        if(robot.getHold()!=sot&&robot.getPlate()!=sot)
        {
			//cout<<"I will into pickUp()\n";
            flag = pickup(sot,sort,robot,G);
			//cout<<"I get out from pickup()\n";
        }
    }
	//cout<<"getSort is over\n";
	//cout<<"***************************************\n";
	return flag;
}
int Devil::putin(int smallsot,int sot,Sort sort[],Robot &robot,Graph &G)
{
	int flag = 0,flag2=0;
	int act1;
	//cout<<"\nmy location is -> "<<robot.getLoc()<<endl;
	//cout<<"\nmy sort location is -> "<<sort[smallsot-1].getsLoc()<<endl;
	if(robot.getPlate() != smallsot && robot.getHold() == 0 && robot.getLoc() == sort[smallsot-1].getsLoc())
	{
		PickUp(smallsot);
		robot.setHold(smallsot);
	}
//	open(sot,sort,robot,G);
	if(robot.getHold()==0&&robot.getPlate() == smallsot)
	{
		//cout<<"my plate -> "<<robot.getPlate()<<" now put it to hand"<<endl;
		//cout<<"smallsot -> "<<smallsot<<endl;
		FromPlate(robot.getPlate());
		robot.setHold(robot.getPlate());
		robot.setPlate(0);
	}
	act1 = robot.getHold();
	//cout<<"i will putin"<<act1<<" "<<sot<<" "<<G.getStatus(act1,sot)<<endl;
	if(G.getStatus(act1,sot)==0)
	  return 0;
//	open(sot,sort,robot,G);
	if(act1 == smallsot)	//可能手中不是本次任务所需的物品
		flag = PutIn(act1,sot);
	else
	{
		flag2 = PutIn(act1,sot);
		robot.setHold(0);
		G.setStatus(act1,sot,flag2);
		getSort(smallsot,sort,robot,G);
		flag = PutIn(robot.getHold(),sot);
	}
	if(flag == 0)
	{
		PutDown(robot.getHold());
		Open(sot);
		PickUp(robot.getHold());
		flag = PutIn(robot.getHold(),sot);
	}
	if(flag == 0)
	{
		sense(robot);
	}
	robot.setHold(0);
	sort[act1-1].setsInside(sot);
	//cout<<"Sir, I'm put "<<act1 <<" in "<<sot<<endl;
	return flag;
}
int Devil::puton(int sotx,int soty,Sort sort[],Robot &robot,Graph &G)
{
	//cout<<"\nThis is puton()\n";
	int flag = 0,obj2 = 0;
	getSort(sotx,sort,robot,G);
	//此处obj2为另一个任务中的小物体，其目的地与当前任务相同
/*	留待以后优化，针对题目合肥省赛19.xml
 *	obj2 = checkConnectionBig(soty,G,G.getDirection(sotx,soty),sotx);
	//cout<<"This is puton obj2 --> "<<obj2<<endl;
	if(obj2 != 0 && robot.getPlate()==0)
    {
		//cout<<"\nthis is puton i want to get other sort, i will into getsort\n";
        getSort(obj2,sort,robot,G);
		//cout<<"\n i come from getsort to puton\n";
    }
	else 
	{
		obj2 = 0;
	}
*/
    move(soty,sort,robot);
    if(obj2 == 0)
    {
        //cout<<"puton---only---obj1\n";
       // flag = putdown(robot.getHold(),sort,robot,G); //pickup --bug
	   	flag = putdown(sotx,sort,robot,G);
        robot.setHold(0);
    }
	else
    {
        //cout<<"puton---obj1---obj2\n";
        //cout<<"robot.getHold()---"<<robot.getHold()<<endl;
        putdown(robot.getHold(),sort,robot,G);
        FromPlate(robot.getPlate());
        robot.setHold(robot.getPlate());
        robot.setPlate(0);
        flag = putdown(robot.getHold(),sort,robot,G);

        G.setStatus(obj2,soty,flag);
        //cout<<"checkputon"<<obj2<<"----"<<soty<<"----"<<G.getStatus(obj2,soty)<<endl;
    }
	//cout<<"flag:"<<flag<<endl;
	//cout<<"puton() over!\n";
	return flag;
}
int Devil::putdown(int sot,Sort sort[],Robot &robot,Graph &G)
{

	int act1;
	int flag = 0;
	//cout<<"I will put "<<sort[sot-1].getsName()<<" down"<<endl;
	if(robot.getHold() != sot && robot.getPlate() != sot )
	{
		//cout<<" I don't need putdown\n";
		return 1;
	}
	if(robot.getHold()!=sot&&robot.getPlate()!=sot)
	{
		getSort(sot,sort,robot,G);
	}
	if(robot.getHold()==sot&&robot.getPlate()!=0)
    {
        flag = PutDown(robot.getHold());
    }
	else if(robot.getHold() == sot && robot.getPlate()==0)
	{
		flag = PutDown(robot.getHold());
	}else if(robot.getHold() == 0 && robot.getPlate()==sot)
	{
		FromPlate(robot.getPlate());
		robot.setHold(robot.getPlate());
		robot.setPlate(0);

		flag=PutDown(robot.getHold());
	}else if(robot.getHold() !=0 && robot.getPlate()==sot)
	{
		int flag1 = 0;
		for(int i=0;i<maxNode;i++)
		{
			if(G.getStatus(sot,i)==1)
			{
				flag1 = 1;
				break;
		 	}
		} 
		if(flag1 == 1)
		{
			PutDown(robot.getHold());

			FromPlate(robot.getPlate());
			robot.setHold(robot.getPlate());
			robot.setPlate(0);
			flag = PutDown(robot.getHold());
		} 
	}
	if(flag==1)
		robot.setHold(0);
	return flag;
}
int Devil::pickup(int sot,Sort sort[],Robot &robot,Graph &G)
{
	//cout<<"\n\nthis is pickup()\n\n";
	int flag = 0;
	if(robot.getHold()!=sot&&robot.getHold()!=0&&robot.getUsehold()==0)
	{
		PutDown(robot.getHold());
		//cout<<"i need:"<<sot<<"\t";
		//cout<<"I'm running Pickup ,i need putdown "<<robot.getHold()<<endl;
		robot.setHold(0);
	}
	if(robot.getUsehold()==4&&robot.getHold()!=0)
    {//针对约束
        ToPlate(robot.getHold());
        robot.setPlate(robot.getHold());
        robot.setHold(0);
        robot.setUsehold(0);
        robot.setUseplate(4);
    }
	if(sort[sot-1].getsInside()==-1)
	{
		//cout<<"i will pickup -> "<<sot;
		flag = PickUp(sot);
		//cout<<" result -> "<<flag<<endl;
	}
	else
	{	
		//cout<<" i will takeout -> "<<sot;
		flag = takeout(sot,sort,robot,G);
		//cout<<" result -> "<<flag<<endl;
	}
	if(flag==1)
	{
		robot.setHold(sot);
//		if(robot.getPlate()==0&&checkConnectionSmall(robot.getHold(),G)!=0)
//			{//嵌套的if防止当前物体在任务位置被放进盘子中
				//此处处理的不好，当pickup完后可能会直接放到盘子里
//				int obj2 = checkConnectionLoc(robot.getHold(),G);
//				if(sort[obj2-1].getsLoc()!=robot.getLoc())
//				{
//					//cout<<"This is pickup - ToPlate running :)\n";
//					//cout<<sort[obj2-1].getsName()<<" location is "<<sort[obj2-1].getsLoc()<<endl;
//					//cout<<"robot location is "<<robot.getLoc()<<endl;
//					ToPlate(robot.getHold());
//					robot.setPlate(robot.getHold());
//					robot.setHold(0);
//				}
//			}
	}
	if(flag == 0)
	{
	//	if(sense(robot,sot,sort,G) == 1)
		//cout<<"pickup error!\n";
		//cout<<"this sort's alreadtSense:"<<sort[sot-1].alreadySense<<" "
		//	<<"the robot's thisLocHaveSort:"<<robot.thisLocHaveSort<<endl;
		if(sort[sot-1].alreadySense == 1 && robot.thisLocHaveSort == 1)
		{
			int obj2 = FindBigSortByLoc(sort,robot.getLoc());
			if(obj2 != 0)
			{
				sort[sot-1].setsInside(obj2);
				sort[sot-1].setsLoc(sort[obj2-1].getsLoc());
				flag = takeout(sot,sort,robot,G);
			}
		}
		else if(sort[sot-1].alreadySense == 0 && robot.thisLocHaveSort ==0)
		{
			if(sense(robot,sot,sort,G) ==1 )	
			{
				//cout<<"I see it ,but i can't pick up it, i will try takeout\n";
				//cout<<"I will find big sort by loc\n";
				int obj2 = FindBigSortByLoc(sort,robot.getLoc());
				//cout<<"obj2 ->"<<obj2<<endl;
				//cout<<"find over()\n";
				if(obj2 != 0)
				{
					//cout<<"i find it\n";
					sort[sot-1].setsInside(obj2);
					sort[sot-1].setsLoc(sort[obj2-1].getsLoc());
				}
		//		sort[sot-1].setInside();
				flag = takeout(sot,sort,robot,G);
			}
			if(sort[sot-1].suchSense == 1 && flag == 0)
			{
				//cout<<"This is target:"<<sot<<" suchSense == 1\n";
				//cout<<"i see it, but i can't pickup it, i will try takeout\n";
				//cout<<"I will find big sort by loc\n";
				int obj2 = FindBigSortByLoc(sort,robot.getLoc());
				//cout<<"obj2 ->"<<obj2<<endl;
				//cout<<"find over()\n";
				if(obj2 != 0)
				{
					//cout<<"i find it\n";
					sort[sot-1].setsInside(obj2);
				}
				flag = takeout(sot,sort,robot,G);
				//cout<<"takeout result:"<<flag<<endl;
			}
		}
	/*	vector <unsigned int> obj;
		Sense(obj);
		for(vector<unsigned int>::iterator it =obj.begin();it!=obj.end();it++)
			//cout<<"I can see "<<*it<<" My location is "<<robot.getLoc()<<endl;
	*/
	}

	return flag;
}


void Devil::getLostLocFromTask(Task task[],int taskNum,Sort sort[])
{
	//cout<<"\nThis is getLostLocFromTask()"<<endl;
	int where[30]={0};
	int count = 1;
	int j = -1;
	//mark
	for(int i=0; i<=taskNum;i++)
	{
		if(task[i].getTaskLocx()==-1)
		{
			//cout<<"task_sort:"<<task[i].getTaskAct1()<<" "<<task[i].getTaskLocx()<<endl; 
			where[i] = task[i].getTaskAct1(); //mark
		}
	}
	//find
	for(int i=0; i<30;i++)
	{
		if(where[i] != 0 &&sort[where[i]-1].getsLoc()==-1)
		{
			j =  getAskLoc(AskLoc(where[i]),sort);
			sort[where[i]-1].errorCount--;
			if(j == -1 && sort[where[i]-1].errorCount != 0)
			{
				count++;
				j = getAskLoc(AskLoc(where[i]),sort);
				sort[where[i]-1].errorCount--;
				if(j == -1 && sort[where[i]-1].errorCount != 0)
				{
					count++;
					j = getAskLoc(AskLoc(where[i]),sort);
					sort[where[i]-1].errorCount--;
				}
			}
			task[i].setTaskLocx(j);
			task[i].errorCount -= count;
			sort[task[i].getTaskAct1()-1].setsLoc(j);
			//cout<<"Sort:"<<task[i].getTaskAct1()<<" "<<" loc is "
			//	<<sort[task[i].getTaskAct1()-1].getsLoc()
			//	<<" sort errorCount "<<sort[task[i].getTaskAct1()-1].errorCount
			//	<<" task errorCount "<<task[i].errorCount<<endl;
		}
	}
	//reduction
	//cout<<"getLostLocFromTask() is over"<<endl;
}


void Devil::dealwithpickup(Task task[],int taskNum,Sort sort[],Robot &robot,Graph &G)
{
	//cout<<"\nthis is dealwithpickup() \n";
	int errorFlag = -1;
	for(int i = 0; i <= taskNum; i++)
	{
		if(task[i].getTaskAction()=="pickup")
		{
			if(robot.getHold() == task[i].getTaskAct1() || robot.getPlate()== task[i].getTaskAct1())
			{
				break;
			}
			//cout<<"sort's Loc: "
			//	<<sort[task[i].getTaskAct1()-1].getsLoc()<<endl;
			move(task[i].getTaskAct1(),sort,robot);
			if(sense(robot,task[i].getTaskAct1(),sort,G) == 1)
			{
				//cout<<"I can see it\n";
				//cout<<"I will get into dealAlreadySenseNullTask\n";
				dealAlreadySenseNullTask(robot,sort,task,taskNum,G);
			}
			else
			{
				errorFlag = findErrorSort(robot,sort,task[i].getTaskAct1(),G);
				//cout<<"errorFlag -> "<<errorFlag<<endl;
				//cout<<"I will get into dealAlreadySenseNullTask\n";
				dealAlreadySenseNullTask(robot,sort,task,taskNum,G);
				if(errorFlag == -1)
				{
					//cout<<"I can't find it, i will give up this task, i am so sad\n";		
					continue;
				}
			}
			//cout<<"I'm from dealwithpickup to getSort()\n ";
			getSort(task[i].getTaskAct1(),sort,robot,G);
		/*	
		 	move(task[i].getTaskAct1(),sort,robot);
			if(robot.getHold() != 0 && robot.getPlate() == 0)
			{
				ToPlate(robot.getHold());
				robot.setHold(0);
			}
			else if(robot.getHold() !=0 && robot.getPlate() != 0)
			{
				PutDown(robot.getHold());
				robot.setHold(0);
			}

			PickUp(task[i].getTaskAct1());
			robot.setHold(task[i].getTaskAct1());
		*/
		}
	}
	//cout<<"\ndealwithpickup is over\n";
}
void Devil::dealwithgoto(Task task[],int taskNum,Sort sort[],Robot &robot)
{
	for(int i = 0;i<=taskNum;i++)
 	{
		if(task[i].getTaskAction()=="goto")
		{
			move(task[i].getTaskAct1(),sort,robot);
 		}
	}
}

void Devil::dealwithputdown(Task task[],int taskNum,Sort sort[],Robot &robot)
{
	//cout<<"\n\nThis is dealwithputdown()\n\n";
	int i,j;
	int hold = robot.getHold();
	int plate = robot.getPlate();
	int flag1 = 0, flag2 = 0;
	for(i = 0; i <= taskNum; i++)
	{
		if(robot.getUsehold() == 0 && robot.getUseplate() == 0)
		{
			//cout<<"i -> "<<i<<" flag1 -> "<<flag1
			//	<<" flag2 -> "<<flag2<<endl;
			if( hold == 0 && plate == 0)
			{ 
				break;		
			}
			if( hold == task[i].getTaskAct1())
			{
				//cout<<"this is hold "<<task[i].getTaskAct1()<<endl;
					flag1 = 1;
			}
			if(plate == task[i].getTaskAct1())
			{
				//cout<<"this is plate "<<task[i].getTaskAct1()<<endl;
					flag2 = 1;
	 		}
			
			
		}
	}


	if(hold !=0 && plate != 0 && flag1 == 0 && flag2 == 0)
	{
		//cout<<"i will putdown "<<hold<<" "<<plate<<endl;
		PutDown(hold);
		robot.setHold(0);
	//	FromPlate(plate);
	//	PutDown(plate);
	//	robot.setPlate(0);
	}
	if( hold != 0 && flag1 == 0 && flag2 == 1)
	{
		//cout<<"i will putdown "<<hold<<endl;
		PutDown(hold);
		robot.setHold(0);
	} 

	//cout<<"\n\ndealwithputdown() is over\n"<<endl;
}

void Devil::sense(Robot robot)
{
	vector <unsigned int> sort;
	Sense(sort);
//	for(vector<unsigned int>::iterator it = sort.begin();it!=sort.end();it++)
		//cout<<"I can see "<<*it<<" My location is "<<robot.getLoc()<<endl;
}
int Devil::sense(Robot &robot,int target,Sort sort[],Graph &G)
{
	//cout<<"This is sense\n";
	int flag = 0;
	int obj2;
	int count = 0;
	robot.thisLocHaveSort = 0;
	if(sort[target - 1].suchSense == 1)
	{
		//cout<<"this target i have sensed\n";
		return 1;
	}
	if(robot.getHold() == target || robot.getPlate() == target)
	{
		//cout<<"target is in my body, sense over()\n";
		return 1;
	}
	vector <unsigned int> sot;
	if(sort[target-1].getsInside()!=-1)
	{
		obj2 = sort[target-1].getsInside();
		open(obj2,sort,robot,G);
	}
	
	//5.10 位置一般可以用大物体来表示
	//用于解决error的情况，例如原本是inside结果询问后是at
	int bigSort = robot.getLoc();
	if(sort[bigSort-1].getsType() == "container")
	{
		open(bigSort,sort,robot,G);
	}

//	open(target,sort,robot,G);
	Sense(sot);
	for(vector<unsigned int>::iterator it = sot.begin();it!=sot.end();it++)
	{
		//cout<<"I can see "<<*it<<endl;
		sort[*it - 1].suchSense = 1;	//记录该物体已被记录
		sort[*it - 1].setsLoc(robot.getLoc());	//重新记录该物体位置
		if(sort[*it-1].getsInside() != -1 )
		{
			//cout<<"I am in container\n";
			int obj2 = sort[*it -1].getsInside();
			if(sort[*it-1].getsLoc() != sort[obj2-1].getsLoc())
			{
				//cout<<"I am in a fault container\n";
				sort[*it-1].setsInside(-1);
			}
		}
		if(*it == target)
		{
			flag = 1;
			sort[target - 1].alreadySense = 1;
			robot.thisLocHaveSort = 1;
		}
		count++;
	}
	if(flag == 0)
	{
		sort[target - 1].setsLoc(-1);
		sort[target - 1].setsInside(-1);
		int checkTakeOut  = checkTakeout(target,robot.getLoc(),G);
		if( checkTakeOut == -1)
		{
			if(count == 1)
			{
				sort[robot.getLoc()-1].haveSmallSort = 0;	//当前大物体中没有小物体
			}
			//cout<<"the takeout is error\n";
			G.setStatus(target,robot.getLoc(),1);
		}
	}
	deleteErrorLoc(robot,sot,sort);
	//cout<<"My location is "<<robot.getLoc()<<endl;
	//cout<<"sense is over() flag->"<<flag<<endl;
	return flag;
}
//针对第二阶段出现的错误设立
void Devil::dealWithErrorInfo(Task task[],int taskNum,Sort sort[])
{
	
}

int Devil::findErrorSort(Robot &robot,Sort sort[],int target,Graph &G)
{
	//cout<<"\nThis is findErrorSort()\n";
	int j = -1;
	int flag = 0;
//	while(sort[target-1].errorCount--)
//	{
		if(sort[target-1].errorCount != 0 )
		{
			//cout<<"this is first askloc\n";
			j = getAskLoc(AskLoc(target),sort);
			sort[target-1].errorCount--;
		}
		if(j != -1)
		{	
			move(target,sort,robot);
			flag = sense(robot,target,sort,G);
			//cout<<"this is first sense flag ->"<<flag<<endl;
			//cout<<" j == -1 || flag == 0) && sort[target - 1].errorCount != 0 result:"<<((j == -1 || flag == 0) && (sort[target - 1].errorCount != 0))<<endl;
		} 

		if((j == -1 || flag == 0) && sort[target - 1].errorCount)
		{
			//cout<<"this is second askloc\n";
			j = getAskLoc(AskLoc(target),sort);
			sort[target-1].errorCount--;
			if(j != -1)
			{
				move(target,sort,robot);
				flag = sense(robot,target,sort,G);
				//cout<<"this is second sense flag ->"<<flag<<endl;
			}  
			if((j == -1 || flag == 0) && sort[target - 1].errorCount)
			{
				//cout<<"this is third askloc\n";
				j = getAskLoc(AskLoc(target),sort);
				sort[target-1].errorCount--;
				if(j != -1)
				{
					move(target,sort,robot);
					flag = sense(robot,target,sort,G);
					//cout<<"this is third sense flag ->"<<flag<<endl;  
				} 
				if(j == -1 || flag == 0 )
				{
					//cout<<"I am so sad, i can't find this obj\n";
					j = -1;
				}  
			}   
		}
//	}
	if(flag == 0)
	{	
		//cout<<"finial sense result :"<<flag<<endl;
		j = -1;
	}
	//cout<<"findErrorSor is over()\n";
	return j;
 }
void Devil::dealWithClose(Task task[],int taskNum,Sort sort[],Robot &robot,Graph &G)
{
	int i=0;
	//cout<<"\n\nThis is dealwithclose\n";
	int obj = 0;
	for(int i = 0; i<= taskNum;i++)
	{
		if(task[i].getTaskAction()=="close")
		{
			obj = task[i].getTaskAct1();
			if(sort[obj-1].getsClosed() == 1)
			{
				continue;
			}
			move(obj,sort,robot);
			close(obj,sort,robot,G);

		}
	}
	//cout<<"\n\ndealwithclose() is over\n";
}

/*
 *此函数功能为：
 *处理在此地看到的物体如果有任务但没有被执行的情况
 */
void Devil::dealAlreadySenseNullTask(Robot &robot,Sort sort[],Task task[],int taskNum,Graph &G)
{
	//cout<<"this is dealAlreadySenseNullTask"<<endl; 
	int i;
	int obj1,obj2;
	for( i = 0; i < taskNum + 1; i++)
	 {
		obj1 = task[i].getTaskAct1();
		obj2 = task[i].getTaskAct2();
		//cout<<"obj1 ->"<<obj1<<" obj2 ->"<<obj2<<endl;
		//cout<<"taskNo."<<G.getStatus(obj1,obj2)<<endl;
		if(G.getStatus(obj1,obj2) == 0)
		{
			continue;
	 	}
		else
	 	{
			if(sort[obj1 - 1].suchSense == 0)
			{
				//cout<<"<><><><><><><><><><><><><>\n";
				continue;
			}
			else if(sort[obj1 - 1].suchSense == 1)
			{
				if(G.getDirection(obj1,obj2) == -1)
				{
					//takeout
					move(obj1,sort,robot);
					obj2 = FindBigSortByLoc(sort,robot.getLoc());
					if(obj2 != 0)
					{
						sort[obj1-1].setsInside(obj2);
				
						G.setStatus(obj1,obj2,takeout(obj1,sort,robot,G));
					
					}
				}
				else if(G.getDirection(obj1,obj2) == 1)
				{
					//putin
					getSort(obj1,sort,robot,G);
					move(obj2,sort,robot);
					open(obj2,sort,robot,G);
					G.setStatus(obj1,obj2,putin(obj1,obj2,sort,robot,G));
				}
				else if(G.getDirection(obj1,obj2) == -4)
				{
					//puton
					G.setStatus(obj1,obj2,puton(obj1,obj2,sort,robot,G));
				}
				else if(G.getDirection(obj1,obj2) == 6)
				{

					//give
					G.setStatus(obj1,obj2,puton(obj1,obj2,sort,robot,G));
				}
				else
				{
					//cout<<"//////////////////////////////////////\n";
				}
					
			}
		}
			
	}
	//cout<<"dealAlreadySenseNullTask is over\n";
}
