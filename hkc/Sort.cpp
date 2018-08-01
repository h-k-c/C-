#include "Sort.h"
int Sort::book = 0;
int Sort::can = 0;
int Sort::remotecontrol = 0;
int Sort::bottle = 0;
int Sort::cup=0;
int Sort::count=0;
Sort::Sort()
{
    snum=-1;
    sloc=-1;

    sinside=-1;
	haveSmallSort = 0;
	//sinsideD=0;

    sname="N_N";
    ssize="N_S";
    scolor=" ";
 
    scontainer=false;
    sclosed=true;
    slock=false;
    cons_not = 0;
	bigSort = 1;
	used = 0;
	needMatch = 0;
	taskLock = 0;
	errorCount = 3;
	alreadySense = 0;
	suchSense = 0;
	fuckClosed = -1;
}


void Sort::setsNum(int num)
{
    snum=num;
}
void Sort::setsLoc(int Loc)
{
    sloc=Loc;
}
void Sort::setsInside(int inside)
{
    sinside=inside;
}
void Sort::setsSize(string _size)
{
    ssize=_size;
}
void Sort::setsColor(string color)
{
    scolor=color;
}
void Sort::setsName(string name)
{
    sname=name;
}
void Sort::setsClosed(string closed)
{
    if(closed=="closed")
        sclosed=true;
	else if(closed == "opened")
	{
		sclosed = false;
	}
}
void Sort::setsClosed(int closed)
{
    if(closed==1)
        sclosed=true;
    else
        sclosed=false;
}
void Sort::setsType(string type)
{
    if(type=="container")
            scontainer=true;
}
void Sort::setsLock()
{
	if(ssize == "small")
    	slock = true;
}
void Sort::setsConsnot(string action)
{
    if(action == "putdown")
    {
        cons_not  = 4;
    }
    if(action == "open")
    {
        cons_not = -2;
    }
    if(action == "close")
    {
        cons_not = 2;
    }
    if(action == "goto")
    {
        cons_not = 3;
    }
    if(action == "pickup")
    {
        cons_not = 5;
    }
}
void Sort::setsBigSort(string name)
{
	if(name == "plant"||name == "book"||name == "can"||name=="remotecontrol"||
name == "bottle"||name=="cup")
	{
		bigSort=0;
	}
}
////////////////////////////
int Sort::getsNum()
{
    return snum;
}
int Sort::getsLoc()
{
    return sloc;
}
int Sort::getsInside()
{
    return sinside;
}
string Sort::getsName()
{
    return sname;
}
string Sort::getsColor()
{
    return scolor;
}
string Sort::getsSize()
{
    return ssize;
}
string Sort::getsType()
{
    if(scontainer)
        return "container";
    else
        return "";
}
bool Sort::getsClosed()

{
    return sclosed;
}
bool Sort::getsLocked()
{
    return slock;
}
int Sort::getsConsnot()
{
    return cons_not;
}
void Sort::setStatic(string name)
{
	if(name=="book")
		book++;
	if(name=="can")
		can++;
	if(name=="remotecontrol")
		remotecontrol++;
	if(name=="bottle")
		bottle++;
	if(name=="cup")
		cup++;
}
void Sort::reduce(string name)
{
	if(name=="book")
		book--;
	if(name=="can")
		can--;
	if(name=="remotecontrol")
		remotecontrol--;
	if(name=="bottle")
		bottle--;
	if(name=="cup")
		cup--;
}
int Sort::getsStatic(string name)
{
	if(name=="book")
		return book;
	if(name=="can")
		return can;
	if(name=="remotecontrol")
		return remotecontrol;
	if(name=="bottle")
		return bottle;
	if(name=="cup")
		return cup;
}
