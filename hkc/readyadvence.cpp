#include "readyadvence.h"
void dealwithtask(const string &TASK,Task task[], int &taskMaxnum)
{/*{{{*/
    int i=-1,flag=0;  //flag用来判断当前字符串是否属于任务
    string str1="",str2="";
    vector<string> vStr;
    boost::split( vStr, TASK, boost::is_any_of( "( ):" ), boost::token_compress_on );
    for( vector<string>::iterator it = vStr.begin(); it != vStr.end(); it++)
    {
        //cout<<*it<<endl;
        if(*it == "task" && * (it-1)=="cons_not"||*it=="task"&& *(it-1)=="cons_notnot")
           {
               continue;
           }
        if(*it == "task")
        {
            i=i+1;
            flag=1;
            task[i].setTaskNo(i+1);
       //     cout<<"this is task"<<endl;
        } else if(*it == "cons_not"||*it=="cons_notnot"||*it=="info")
        {
            flag=0;
        }
        if(flag&&(*it == "open" || *it =="close"||*it=="takeout"|| *it=="putin"||*it=="goto"||*it=="pickup"
                  ||*it=="putdown"||*it=="give"||*it=="puton"))
        {
            cout<<*it<<endl;
            if(*(it+2)!="Y")
                str2="";
            else
                str2=*(it+2);
            task[i].setTaskAction(*it,*(it+1),str2);
        }
        if(flag&& *it=="sort")
        {
            if(*(it+1)=="X")
                task[i].setTaskNamex(*(it+2));
            else if(*(it+1)=="Y")
                task[i].setTaskNamey(*(it+2));
                cout<<"***"<<task[i].getTaskNamex()<<endl;
        }
        if(flag&& *it=="color")
        {
            if(*(it+1)=="X")
                task[i].setTaskColorx(*(it+2));
            else
                task[i].setTaskColory(*(it+2));
        }
        if(flag && *it =="type")
        {
            if(*(it+1)=="X"&&task[i].getTaskNamex()=="")
                task[i].setTaskNamex(*(it+2));
            else if(*(it+1)=="Y"&&task[i].getTaskNamey()=="")
                task[i].setTaskNamey(*(it+2));
        }
        taskMaxnum=i;
    }
}/*}}}*/
void dealwithsence(const string &STR,Sort sort[],Robot &robot, int &senceMax)
{/*{{{*/
 //   cout<<"this is dealwithsence"<<endl;
    int obj1=0,obj2=0;
    string str1="",str2="";
    vector<string> vStr;
    boost::split( vStr, STR, boost::is_any_of( "( )" ), boost::token_compress_on );
    for( vector<string>::iterator it = vStr.begin(); it != vStr.end(); it++)
    {
        if(*it == "at")
        {
            str1 = *(it+1);
            obj1 = atoi(str1.c_str());
            str2 = *(it +2);
            obj2 = atoi(str2.c_str());
            if(obj1)
            {
                  sort[obj1-1].setsLoc(obj2);
                sort[obj1-1].setsNum(obj1);
            }
            else
                 {
                 	robot.setLoc(obj2);
                 }
        }
		else if(*it == "plate")
        {
                        str1 = *(it+1);
            obj1 = atoi(str1.c_str());
            robot.setPlate(obj1);
        }
		else if(*it == "hold")
        {
                        str1 = *(it+1);
            obj1 = atoi(str1.c_str());
            robot.setHold(obj1);
        }
		else if(*it == "sort")
        {
                str1 = *(it+1);
            obj1 = atoi(str1.c_str());
            sort[obj1-1].setsName(*(it+2));
               sort[obj1-1].setsNum(obj1);
			   sort[obj1-1].setsBigSort(*(it+2));
			   sort[obj1-1].setStatic(*(it+2));
        }
		else if(*it == "size")
        {
                           str1 = *(it+1);
            obj1 = atoi(str1.c_str());
            sort[obj1-1].setsSize(*(it+2));
               sort[obj1-1].setsNum(obj1);
        }
		else if(*it == "color")
        {
                           str1 = *(it+1);
            obj1 = atoi(str1.c_str());
            sort[obj1-1].setsColor(*(it+2));
               sort[obj1-1].setsNum(obj1);
        }
		else if(*it == "inside")
        {
            str1 = *(it+1);
            obj1 = atoi(str1.c_str());
              str2 = *(it +2);
            obj2 = atoi(str2.c_str());
            sort[obj1-1].setsInside(obj2);
               sort[obj1-1].setsNum(obj1);
			sort[obj2-1].sinsideD.push_back(obj1);
        }
		else if(*it == "closed")
        {
		sort[obj1-1].fuckClosed = 1;
             str1 = *(it+1);
             obj1 = atoi(str1.c_str());
             sort[obj1-1].setsClosed(1);
             sort[obj1-1].setsNum(obj1);
        }
		else if(*it == "opened")
		{
			sort[obj1-1].fuckClosed = 1;
			str1 = *(it+1);
			obj1 = atoi(str1.c_str());
			sort[obj1-1].setsClosed(0);
			sort[obj1-1].setsNum(obj1);
		}
		else  if(*it == "type")
        {
              str1 = *(it+1);
            obj1 = atoi(str1.c_str());
            sort[obj1-1].setsType(*(it+2));
               sort[obj1-1].setsNum(obj1);
         }

        if(obj1>senceMax)
         {
            senceMax=obj1;
        }
    }/*}}}*/
}
void dealwithInfoCons(const string &TASK,InfoCons info_cons[],int &numMax,string SIGN)
{/*{{{*/
    cout<<"this is dealwithInfoCons-start.-"<<SIGN<<endl;
    int i=-1;
    int flag=0;
    string str1="",str2="";
    //choice==1,代表info
//choice==2,代表cons
//choice==3,代表cons_not
//SIGN 代表info || cons || cons_nots
    string Flag[4]={"info","task","cons_not","cons_notnot"};
    vector<string> vStr;
    boost::split( vStr, TASK, boost::is_any_of( "( ):" ), boost::token_compress_on );
    for( vector<string>::iterator it = vStr.begin(); it != vStr.end(); it++)
    {
        if(*it == SIGN)
        {

            if(*(it-1)=="cons_not"||*(it-1)=="cons_notnot")
            {
                //此if针对cons_not或cons_notnot后跟着的info
                continue;
            }
            i++;
            info_cons[i].setNo(i+1);
            flag=1;
            cout<<"I'm find it"<<SIGN<<endl;
        }
        for(int j=0;j<4;j++)
        {
            if(*it!=SIGN&&*it==Flag[j])
                flag=0;
        }
            if((*it=="info"||*it=="task")&&*(it-1)==SIGN)
                    flag=1;
        if(flag&&(*it=="at"||*it== "on"||*it=="near"||*it=="plate"||*it=="inside"||*it=="opened"||*it=="closed"||*it=="give"
           ||*it=="puton"||*it=="goto"||*it=="putdown"||*it=="pickup"||*it=="open"||*it=="putin"||*it=="close"||*it=="takeout"))
        {
            cout<<*it<<endl;
            if(*(it+2)!="Y")
                str2="";
            else
                str2=*(it+2);
            info_cons[i].setState(*it);
           info_cons[i].setState1(*(it+1));
           info_cons[i].setState2(str2);
        }
        if(flag&&(*it=="sort"))
        {
            cout<<"this is info-cons-sort "<<*(it+2)<<endl;
                if(*(it+1)=="X")
                    info_cons[i].setNamx(*(it+2));
                else if(*(it+1)=="Y")
                    info_cons[i].setNamy(*(it+2));
        }
        if(flag&&(*it=="color"))
        {
            cout<<"this is info-cons-color "<<*(it+2)<<endl;
            if(*(it+1)=="X")
                info_cons[i].setColorx(*(it+2));
            else if(*(it+1)=="Y")
                info_cons[i].setColory(*(it+2));
        }
        numMax=i;
    }
}/*}}}*/
void updateTask(Sort sort[],Task task[],int sortNum,int taskNum,Robot &robot)
{
	cout<<"\nThis is updateTask\n";
    int i=0,j=0;
	int count = 0;
    for(i=0;i < taskNum + 1;i++)
    {
		count = 0;
        cout<<task[i].getTaskNamey()<<endl;
        for(j=0;j<sortNum;j++)
        {
         //   if(task[i].getTaskNamex()==sort[j].getsName()&&sort[j].getsLocked()==0)
           	if(task[i].getTaskNamex()==sort[j].getsName())
		   	{
               // cout<<"This taskx match "<<task[i].getTaskNamex()<<endl;
                sort[j].needMatch=1;
                    /* if(sort[j].getsStatic(sort[j].getsName())==1&&sort[j].getsLocked()==0)
                    {
                        task[i].setTaskAct1(j+1);
                        task[i].used=1;
                        sort[j].used=1;
                        sort[j].needMatch=0;
                    }*/
                    if(task[i].getTaskColorx()==sort[j].getsColor())
                    {
                        cout<<i<<" "<<j<<" match it "<<sort[j].getsName()<<" "<<sort[j].getsColor()<<endl;
                        task[i].setTaskAct1(j+1);
                        task[i].used=1;
                        sort[j].used=1;
                        sort[j].needMatch=0;
                     }
					if(task[i].used==0&&sort[j].getsStatic(sort[j].getsName())==1&&sort[j].getsLocked()==0)
			 		{
						cout<<"Task."<<task[i].getTaskAction()<<" name."<<task[i].getTaskNamex()
							<<" colorx."<<task[i].getTaskColorx()<<endl;
						cout<<"Sort."<<sort[j].getsName()<<" color."<<sort[j].getsColor()<<endl;
						task[i].setTaskAct1(j+1);
						task[i].used=1;
						sort[j].used=1;
						sort[j].needMatch=0;
					}
					if(task[i].getTaskAction()=="takeout")
					{
						int obj2 = sort[j].getsNum();
						if(sort[obj2-1].getsName()==task[i].getTaskNamey())
						{
							task[i].setTaskAct1(j+1);
							task[i].used=1;
							sort[j].used=1;
							sort[j].needMatch=0;
			 			}
			 		}
            } 
			if(task[i].getTaskNamex()=="container")
			{ 
				if(sort[j].getsType()=="container"&&sort[j].getsLocked()==0)
			 	{
					task[i].setTaskAct1(j+1);
					task[i].used = 1;
					sort[j].used = 1;
					sort[j].needMatch=0;
				}
			}
            if(task[i].getTaskNamey()==sort[j].getsName()&&sort[j].getsLocked()==0)
            { 
                cout<<task[i].getTaskNamey()<<" "<<sort[j].getsName()<<endl;
                    if(sort[j].getsStatic(sort[j].getsName())==1)
                     {
                        task[i].setTaskAct2(j+1);
                        //task[i].used=1;
                        sort[j].used=1;
                        sort[j].needMatch=0;
                    }
                    if(task[i].getTaskColory()==sort[j].getsColor())
                    {
                        task[i].setTaskAct2(j+1);
                        //task[i].used=1;
                        sort[j].used=1;
                        sort[j].needMatch=0;
                     }
					
            }
			if(task[i].getTaskNamey()=="container"&&sort[j].getsType()=="container"  &&count == 0)
			{
				cout<<"\nsdfsd*******************"<<endl;
				task[i].setTaskAct2(j+1);
				cout<<task[i].getTaskAct2()<<endl;
				sort[j].used=1;
				sort[j].needMatch=0;
				count++;
			}
        }
    }
	cout<<"\nupdateTask is over\n";
}
void updateSenceByInfo(Sort sort[],InfoCons info[],Robot robot,int SNum,int infoNum)
{
    cout<<"-----------------this is updateSenceByinfo-------------------------\n";
    cout<<"snum-->"<<SNum<<" infoNUm--> "<<infoNum<<endl;
    int i,j,inside=0,flag;
	int obj1,obj2;
	int hold,plate;
	
	hold = robot.getHold();
	plate = robot.getPlate();

	if( hold != 0 && sort[hold-1].getsLoc() == -1)
	{
		cout<<"this sort in my hold, my locaion is "<<robot.getLoc()<<endl;
		sort[hold-1].setsLoc(robot.getLoc());		
	}
	if(plate !=0 && sort[plate-1].getsLoc() == -1)
	{
		cout<<"this sort in my plate, my location is "<<robot.getLoc()<<endl;
		sort[plate-1].setsLoc(robot.getLoc());
	}
    for( i =0; i<SNum; i++)
    {
        for(j=0; j<=infoNum; j++)
        {

            //若名字和颜色都相等则，赋值
           // if(info[j].getNamex()==sort[i].getsName()&&info[j].getColorx()==sort[i].getsColor()&&sort[i].getsLoc()==-1)
           	if(info[j].getNamex()==sort[i].getsName()&&info[j].getColorx()==sort[i].getsColor())
		   	{

				cout<<sort[i].getsName()<<" "<<sort[i].getsColor()<<"--info--"<<info[j].getNamex()<<" "<<info[j].getColorx()<<endl;
				obj1 = findSortByName(SNum,info[j].getNamex(),info[j].getColorx(),sort);
				obj2 = findSortByName(SNum,info[j].getNamey(),info[j].getColory(),sort);
				if(obj1 == -1)
               	{
					obj1 = findSortByName(SNum,info[j].getNamex(),sort);
				}
				if(obj2 == -1)
				{
					obj2 = findSortByName(SNum,info[j].getNamey(),sort);
				}
                cout<<"obj1 --> "<<obj1<<endl;
                if(info[j].getState()=="near"||info[j].getState()=="on")
                {
                    sort[i].setsLoc(sort[obj1].getsLoc());
                }
           //     cout<<"@@@@@@@@@@@@@@@@@@\n";
                if(info[j].getState()=="inside")
                {
					sort[obj1].setsLoc(sort[obj2].getsLoc());
					sort[obj1].setsInside(sort[obj2].getsNum());
					sort[obj2].sinsideD.push_back(obj1+1);
                    sort[i].setsLoc(sort[obj1].getsLoc());
                    cout<<"this is info -- inside\n";
                }
                if(info[j].getState()=="plate" && sort[i].getsLoc()==-1)
                {
                    sort[i].setsLoc(robot.getLoc());
                }
                if(info[j].getState()=="closed"||info[j].getState()=="opened")
                {
			if(sort[i].fuckClosed == 1)
				continue;		//写于2018年6月1日用于解决info与sence冲突的问题
                    if(info[j].getState()=="opened")
                            flag=0;
                    else
                            flag=1;
					cout<<"This is info judge closed -- "<<flag<<endl;
                    sort[i].setsClosed(flag);
			cout<<"fuck info ==> "<<sort[i].getsName()<<endl;
			cout<<"fuck infoState ==> "<<info[j].getState()<<endl;
                }
            }
        }
        if(sort[i].getsLoc()==-1&&sort[i].getsInside()!=-1)
        {

           inside=sort[i].getsInside();
           sort[i].setsLoc(sort[inside-1].getsLoc());
        }
        if(sort[i].getsNum()==robot.getHold())
        {
            sort[i].setsLoc(robot.getLoc());
        }
    }
	cout<<"----------------updatesenceByinfo is over----------\n";
}/*}}}*/
void printTask(Task task[],int count)
{/*{{{*/
    cout<<"/*************************************task**********************************/\n";
    cout<<setw(7)<<setiosflags(ios::left);
    cout<<"No.";
    cout<<setw(10)<<setiosflags(ios::left);
    cout<<"Action";
    cout<<setw(10)<<setiosflags(ios::left);
    cout<<"Act1.";
    cout<<setw(10)<<setiosflags(ios::left);
    cout<<"Act2.";
    cout<<setw(12)<<setiosflags(ios::left);
    cout<<"Namex.";
    cout<<setw(9)<<setiosflags(ios::left);
    cout<<"Colorx";
     cout<<setw(9)<<setiosflags(ios::left);
     cout<<"Namey.";
    cout<<setw(9)<<setiosflags(ios::left);
    cout<<"Colory"<<endl;
    for(int i=0; i<=count; i++)
    {
    //    if(task[i].getTaskNo()!=-1)
    //cout<<"this is i-->"<<i<<endl;
            cout<<setw(7)<<setiosflags(ios::left);
            cout<<task[i].getTaskNo();
            cout<<setw(10)<<setiosflags(ios::left);
            cout<<task[i].getTaskAction();
            cout<<setw(10)<<setiosflags(ios::left);
            cout<<task[i].getTaskAct1();
            cout<<setw(10)<<setiosflags(ios::left);
            cout<<task[i].getTaskAct2();
            cout<<setw(12)<<setiosflags(ios::left);
            cout<<task[i].getTaskNamex();
            cout<<setw(9)<<setiosflags(ios::left);
            cout<<task[i].getTaskColorx();
            cout<<setw(9)<<setiosflags(ios::left);
            cout<<task[i].getTaskNamey();
            cout<<setw(9)<<setiosflags(ios::left);
            cout<<task[i].getTaskColory()<<endl;
        }

    cout<<"/*************************************task**********************************/\n";
}/*}}}*/

void printScence(Robot  robot,Sort sort[],int count)
{/*{{{*/
    cout<<"/******************************sence********************************/"<<endl;
    cout<<"robot:"<<endl;

    cout<<"Location: "<<robot.getLoc()<<"  Hold:  "<<robot.getHold()<<"  Plate:  "<<robot.getPlate()<<endl;
    cout<<"/*********************************************************************/"<<endl;
    cout<<setw(7)<<setiosflags(ios::left);
    cout<<"No.";
    cout<<setw(17)<<setiosflags(ios::left);
    cout<<"Sort";
    cout<<setw(8)<<setiosflags(ios::left);
    cout<<"Loc.";
    cout<<setw(8)<<setiosflags(ios::left);
    cout<<"Color.";
    cout<<setw(8)<<setiosflags(ios::left);
    cout<<"Size.";
    cout<<setw(9)<<setiosflags(ios::left);
    cout<<"Closed";
     cout<<setw(9)<<setiosflags(ios::left);
     cout<<"Inside.";
    cout<<setw(9)<<setiosflags(ios::left);
    cout<<"Type";
	cout<<setw(8)<<setiosflags(ios::left);
	cout<<"Lock"<<endl;
    for(int i=0; i<count; i++)
    {
            cout<<setw(1)<<setw(4)<<sort[i].getsNum();
            cout<<setw(1)<<"   "<<setw(17)<<sort[i].getsName();
            cout<<setw(1)<<" "<<setw(7)<<sort[i].getsLoc();
            cout<<setw(8)<<sort[i].getsColor();
            cout<<setw(8)<<sort[i].getsSize();
            cout<<"   "<<setw(7)<<sort[i].getsClosed();
            cout<<setw(7)<<sort[i].getsInside();
            cout<<setw(12)<<sort[i].getsType();
			cout<<setw(8)<<sort[i].getsLocked();
            cout<<endl;
    }
   cout<<"/*********************************************************************/"<<endl;
}/*}}}*/
//
//
//
void printInfoCons(InfoCons info[],int count,string SIGN)
{/*{{{*/
    cout<<"|--------------------------"<<SIGN<<"---------------------------|\n";
    cout<<setw(7)<<setiosflags(ios::left);
    cout<<"No.";
    cout<<setw(10)<<setiosflags(ios::left);
    cout<<"Static";
    cout<<setw(10)<<setiosflags(ios::left);
    cout<<"StaticX.";
    cout<<setw(10)<<setiosflags(ios::left);
    cout<<"StaticY";
    cout<<setw(8)<<setiosflags(ios::left);
    cout<<"NameX";
    cout<<setw(9)<<setiosflags(ios::left);
    cout<<"ColorX";
    cout<<setw(14)<<setiosflags(ios::left);
    cout<<"NameY";
    cout<<setw(9)<<setiosflags(ios::left);
    cout<<"Colory"<<endl;
    cout<<"This is infocount-->"<<count<<endl;
    for(int i=0; i<=count; i++)
    {
        if(info[i].getNo()!=-1){
        cout<<setw(7)<<setiosflags(ios::left);
        cout<<info[i].getNo();
        cout<<setw(10)<<setiosflags(ios::left);
        cout<<info[i].getState();
        cout<<setw(10)<<setiosflags(ios::left);
        cout<<info[i].getState1();
        cout<<setw(10)<<setiosflags(ios::left);
        cout<<info[i].getState2();
        cout<<setw(8)<<setiosflags(ios::left);
        cout<<info[i].getNamex();
        cout<<setw(9)<<setiosflags(ios::left);
        cout<<info[i].getColorx();
        cout<<setw(9)<<setiosflags(ios::left);
        cout<<info[i].getNamey();
        cout<<setw(9)<<setiosflags(ios::left);
        cout<<info[i].getColory();
        cout<<endl;
        }
    }
 cout<<"|---------------------------"<<SIGN<<"--------------------------------|\n";
}
int findSortByName(int sNum,string name,string color,Sort sort[])
{
	int i;
	for(i=0;i<sNum;i++)
	{
		if(sort[i].getsName()==name&&sort[i].getsColor()==color)
		{
			cout<<"this is findSortByName&Color, i find it: "<<sort[i].getsNum()<<endl;
			return i;
		}
	}
	return -1;
}
int findSortByName(int sNum,string name,Sort sort[])
{/*{{{*/
    int i;
    for(i=0; i<sNum; i++)
     {
        if(sort[i].getsName() ==name)
            return i;
    }
    return -1;
}/*}}}*/
/*}}}*/
void updateSenceByCons(Sort sort[],InfoCons con[],Robot &robot,int sortNum,int consNum)
{
    int i,j;
    for(i=0;i<=consNum;i++)
    {
        for(j=0; j < sortNum; j++)
        {
            if(con[i].getNamex()==sort[j].getsName()&&con[i].getColorx()==sort[j].getsColor())
            {
                    sort[j].setsConsnot(con[i].getState());
                    cout<<sort[j].getsNum()<<"---cons----"<<sort[j].getsConsnot()<<endl;
                    robot.setUsehold(sort[j].getsConsnot());
                    robot.setUseplate(sort[j].getsConsnot());
            }
        }
    }
}

