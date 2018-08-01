#include "Task.h"

Task::Task()
{
    No = -1;
    Action="";
    Act1=0;
    Act2=0;
    Namex="";
    Namey="";
    Colorx=" ";
    Colory=" ";
    Containerx = false;
    Containery = false;
    Closedx=false;
    Closedy=false;
    _priority=-1;
    _locx=-1;
    _locy=-1;
    success=0;
    needAnalyze=0;
	used = 0;
    obj1fsort = false;
    obj1fcolor = false;
    obj2fsort = false;
    obj2fcolor = false;

	errorCount = 3;//最多询问不超过3次
}
Task::~Task()
{

}

void Task::setTaskNo(int n)
{
    No=n;
}
void Task::setTaskAction(string act,int  act1,int act2)
{
    Action=act;
    Act1=act1;
    Act2=act2;
    if( act=="pickup"||act=="give"|| act=="puton" ||act=="putdown"||act=="putin"||act=="takeout")
    {
        needAnalyze=1;
    }
	if(act == "putdown")
	  _priority = 1;
	if(act == "goto")
	  _priority = 5;
}
void Task::setTaskAction(string act,string act1,string act2)
{
    Action=act;
	if(act == "putdown")
	  _priority = 1; //设定优先级
    if(act1=="X")
        Act1=0;
    if(act=="Y")
        Act2=0;
}
void Task::setTaskAct1(int act1)
{
    Act1=act1;

}
void Task::setTaskAct2(int  act2)
{
    Act2=act2;
}
void Task::setTaskNamex(string namx)
{
    Namex=namx;
    setTaskContainerx(namx);
    obj1fsort = true;

}
void Task::setTaskNamey(string namy)
{
    Namey=namy;
    setTaskContainery(namy);
    obj2fsort = true;
}
void Task::setTaskColorx(string colx)
{
    Colorx=colx;
    obj1fcolor = true;
}
void Task::setTaskColory(string coly)
{
    Colory=coly;
    obj2fcolor = true;
}
void Task::setTaskLocx(int locx)
{
    _locx=locx;
}
void Task::setTaskLocy(int locy)
{
    _locy=locy;
}
void Task::setTaskContainerx(string name)
{
    if(name == "refrigerator"|| name=="cupboard"||name == "washmachine"||name =="closet"||name=="microwave")
    {
        Containerx=true;
    }
}
void Task::setTaskContainery(string name)
{
    if(name=="refrigerator"||name=="cupboard"||name == "washmachine"||name =="closet"||name=="microwave")
    {
        Containery = true;
    }
}
void Task::setTaskClosed1()
{
    Closedx=true;
}
void Task::setTaskClosed2()
{
    Closedy=true;
}
void  Task::setTaskSuccess(int succ)
{
    success=succ;
}
int Task::getTaskSuccess()
{
    return success;
}
int Task::getTaskNo()
{
    return No;
}

string Task::getTaskAction()
{
    return Action;
}
int Task::getTaskAct1()
{
    return Act1;
}
int Task::getTaskAct2()
{
    return Act2;
}
string Task::getTaskNamex()
{
    return Namex;
}
string Task::getTaskNamey()
{
    return Namey;
}
string Task::getTaskColorx()
{
    return Colorx;
}
string Task::getTaskColory()
{
    return Colory;
}
int Task::getTaskPriority()
{
    return _priority;
}
bool Task::getTaskContainerx()
{
    return Containerx;
}
bool Task::getTaskContainery()
{
    return Containery;
}
bool Task::getTaskClosed1()
{
    return Closedx;
}
bool Task::getTaskClosed2()
{
    return Closedy;
}

int Task::getTaskAnalyze()
{
    return needAnalyze;
}
int Task::getTaskLocx()
{
    return _locx;
}
int Task::getTaskLocy()
{
    return _locy;
}
bool Task::seeobj1fcolor()
{
    return obj1fcolor;
}
bool Task::seeobj2fcolor()
{
    return obj2fcolor;
}
bool Task::seeobj1fsort()
{
    return obj1fsort;
}
bool Task::seeobj2fsort()
{
    return obj2fsort;
}

