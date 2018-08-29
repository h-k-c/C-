/*************************************************************************
	> File Name: createTree.cpp
	> Author:hkc 
    > Mail: 2605245956@qq.com
	> Created Time: 2018年07月25日 星期三 11时23分41秒
 ************************************************************************/
#include "devil.hpp"
using namespace _home;
void  ReintegrationTask(std::vector<Btree*> taskLin);
int findStateByName(int sortNum,int sNum,Sort sort[]);
int findHuman(Sort sort[],int sNum);
int findBigSort(string name,Sort sort,int sNum);
int findBigSort(string name,Sort sort[],int sNum){
    int i=0;
    for(i;i<sNum;i++){
        if(sort[i].getsName()==name){
            return sort[i].getsLoc();
        }
    }
    return -1;
}
int Devil::findSortByName(string name,string color,int sNum,int taskNum,Task task[],Sort sort[],InfoCons cons_not[],int cons_not_Max,InfoCons cons_notnot[],int cons_notnotMax,Robot robot){
    for(int h=0;h<=sNum;h++){
        for(int k=0;k<=cons_not_Max;k++){
           // cout<<cons_not[k].getNamex()<<cons_not[k].getColorx()<<endl;
            if(sort[h].getsName()==cons_not[k].getNamex()&&sort[h].getsColor()==cons_not[k].getColorx()&&cons_not[k].getColorx()!=" "&&cons_not[k].getNamey()!=" "&&(cons_not[k].getState()=="takeout"||cons_not[k].getState()=="inside")){
             //   cout<<cons_not[k].getNamex()<<cons_not[k].getColorx()<<endl;
              //  cout<<"约束物体处理成功"<<endl;
                sort[h].setsLockSort(1);
            }
            if(sort[h].getsName()==cons_not[k].getNamex()&&sort[h].getsColor()==cons_not[k].getColorx()&&cons_not[k].getNamey()==" "&&cons_not[k].getColorx()!=" "&&(cons_not[k].getState()=="putdown"||cons_not[k].getState()=="pickup")) {
                sort[h].setsLockSort(1);
            }
        }
    }
    for(int y=0;y<=sNum;y++){
        for(int z=0;z<=cons_notnotMax;z++){
            //cout<<cons_notnot[z].getNamex()<<cons_notnot[z].getColorx()<<endl;
            if(cons_notnot[z].getNamex()==sort[y].getsName()&&cons_notnot[z].getColorx()==sort[y].getsColor()&&cons_notnot[z].getNamey()==" "&&cons_notnot[z].getState()=="plate"){
              //  cout<<"bububu"<<endl;
                sort[y].setsLockSort(1);
            }
            if(cons_notnot[z].getNamex()==sort[y].getsName()&&cons_notnot[z].getColorx()==sort[y].getsColor()&&cons_notnot[z].getNamey()!=" "&&(cons_notnot[z].getState()=="on"||cons_notnot[z].getState()=="inside")){
                sort[y].setsLockSort(1);
            }
        }
    }
        
    if(color==" "&&(name!="plant"||name!="closet"||name!="washmachine"||name!="desk"||name!="table"||name!="microwave"||name!="chair"||name!="human"||name!="couch"||name!="sofa"||name!="worktable"||name!="refigerator"||name!="television"||name!="airconditioner"||name!="refrigerator"&&name!="teapoy"||name!="cupboard")){
        //就遍历任务中的物体把有name和color的物体打上标记，防止被占用；
        for(int j=0;j<=taskNum;j++){
            for(int i=0;i<=sNum;i++){
                if(task[j].getTaskNamex()==sort[i].getsName()&&task[j].getTaskColorx()==sort[i].getsColor()&&task[j].getTaskColorx()!=" "&&sort[i].getsLockSort()!=1){
                    sort[i].setsLockSort(1);
                    sort[i].setIsTask(1);
                }
            }
        }
    }
    int k;
    for(k=0;k<=sNum;k++){
         if(sort[k].getsName()==name){
             if(sort[k].getsColor()==" "&&sort[k].getsName()==name){
                return k+1;
             }
             /*if(sort[robot.getPlate()-1].getsName()==name&&color==" "&&sort[robot.getPlate()-1].getsLockSort()!=1){
                return robot.getPlate();
             }*/
             if(sort[k].getsName()==name&&sort[k].getsColor()==color&&color!=" "&&(sort[k].getsLockSort()!=1||sort[k].getIsTask()==1)){
                sort[k].setsLockSort(1);
                return k+1; 
            }
             if(sort[k].getsName()==name&&color==" "&&sort[k].getsLockSort()!=1){
              //   cout<<"正在挑选物体"<<endl;
                 if(sort[k].getsName()==name&&color==" "&&sort[k].getsLockSort()!=1&&sort[k].getsLoc()!=-1){
                   k=k; 
                //   cout<<"挑选第一个成功"<<endl;
                 }
                 else if(sort[k+1].getsName()==name&&color==" "&&sort[k+1].getsLockSort()!=1&&sort[k+1].getsLoc()!=-1&&sort[k+1].getsInside()==-1){
                //    cout<<"挑选第二个成功"<<endl;
                    k=k+1;
                 }
                 else if(sort[k+2].getsName()==name&&color==" "&&sort[k+2].getsLockSort()!=1&&sort[k+2].getsLoc()!=1&&sort[k+2].getsInside()==-1){
                    k=k+2;
                 }
                 else if(sort[k+3].getsName()==name&&color==" "&&sort[k+3].getsLockSort()!=1&&sort[k+3].getsLoc()!=-1&&sort[k+3].getsInside()==-1){
                    k=k+3; 
                 }
               //  cout<<"挑选原始的成功"<<endl;
                 sort[k].setsLockSort(1);
                 return k+1;
             }
        }
    }
    return -1;
}
/*int findSortByName(std::string name,std::string color,int sNum,Sort sort[]){
    int i=0;
    for(i=0;i<sNum;i++){
        if(sort[i].getsName()==name&&sort[i].getsColor()==color){
            return i+1;
        }
    }
    return -1;
}*/
int findStateByName(int sortNum,int sNum,Sort sort[]){
    int i;
    for(i=0;i<sNum;i++){
        if(sort[i].getsNum()==sortNum){
            return sort[i].getsLoc();
        }
    }
    return -1;
}
int findHuman(Sort sort[],int sNum){
    int i;
    for(i=0;i<sNum;i++){
        if(sort[i].getsName()=="human"){
            return i+1;
        }
    }
    return -1;
}



void  ReintegrationTask(std::vector<Btree*> taskLin){
    //还需要写一个遍历的函数，用来检查是否有相同的节点
    std::multimap<int,multimap<int,string> >::iterator it;
    std::vector<Btree*>::iterator is;
    std::vector<Btree*>::iterator isc;
    std::multimap<int,string>::iterator ite;
    int i=1;
    //cout<<"---------------------------4---------------------------------"<<endl;
    //这个循环就是用来整合创建好的所有的节点

    for(is=taskLin.begin();is!=taskLin.end();is++){
      //  cout<<"开始遍历第"<<i<<"个"<<endl<<endl<<endl;
        if((*is)->sortNum==0) continue;
        for(isc=is;isc!=taskLin.end();isc++){
            if((*isc)->sortNum==0) continue;
        //    cout<<"从第"<<i+1<<"个节点开始遍历"<<endl;
            /*if((*is)->next==NULL&&(*isc)->next==NULL){
                cout<<"如果两个节点都只有一个任务节点"<<endl;
                if((((*is)->taskmultimap.begin())->second.begin())->second=="close"){
                    (*isc)->next=*is;
                    (*is)->sortNum=0;
                }
                if(((*isc)->taskmultimap.begin()->second.begin())->second=="close"){
                    (*is)->next=*isc;
                    (*isc)->sortNum=0;
                }
            }*/
            if((*is)->next==NULL&&(*isc)->next!=NULL){
          //      cout<<"如果第一个只有一个任务节点，相关的有两个任务节点"<<endl;
                if(((*is)->taskmultimap.begin())->first==((*isc)->taskmultimap.begin())->first&&(*is)->next==NULL&&(*isc)->sortNum!=0){
            //        cout<<"如果第一个节点中的第一个任务节点的值和第二个节点的第一个任务节点的值相同"<<endl;
                    //当2,2-->10，这种情况时；
                    //处理的方法就是直接把2节点给删除掉，把节点的动作添加到另一个节点上去；
                   // ((*isc)->taskmultimap).insert(make_pair(((*is)->taskmultimap.begin())->first,((*is)->taskmultimap.begin())->second));
              //      cout<<"已经把"<<((*is)->taskmultimap.begin())->first<<"位置的动作给复制到下一个节点的第一个任务节点"<<endl;
                    (*is)->next=*isc;
                    (*isc)->sortNum=0;
                    //((*isc)->next)->next=NULL;
                    //delete *is;
                //    cout<<"已经把第一个节点打上了标记"<<endl;
                }
               else if(((*is)->taskmultimap.begin())->first==(((*isc)->next)->taskmultimap.begin())->first&&((*isc)->next)->next==NULL&&(*is)->sortNum!=0){
                  //  cout<<"如果第一个节点的任务节点的值和第二个节点的第二个任务节点一样"<<endl;
                    //当是2,10-->2这种情况时；
                    //处理的方法就是直接把2节点删除，把节点的动作添加到另一个节点上去；
                    (((*isc)->next)->taskmultimap).insert(make_pair((((*isc)->next)->taskmultimap.begin())->first,((*is)->taskmultimap.begin())->second));
                  //  cout<<"已经把"<<((*is)->taskmultimap.begin())->first<<"位置的动作给复制到下一个节点的第二个任务节点"<<endl;
                    //taskLin.erase(is);
                    (*is)->sortNum=0;
                    //((*isc)->next)->next=*is;
                   // delete *is;
                    //(*is)->next=NULL;
                    
                  //  cout<<"已经把第一个节点打上了标记"<<endl;
                }
            }
             if((*is)->next!=NULL&&(*isc)->next==NULL){
               // cout<<"如果第一个节点有两个任务节点，相关的只有一个节点"<<endl;
                if(((*is)->taskmultimap.begin())->first==((*isc)->taskmultimap.begin())->first&&(*is)->next==NULL&&(*is)->sortNum!=0){
               //     cout<<"如果第一个节点的第一个任务节点的值和相关的节点的任务节点的值相同"<<endl;
                    //当2-->10,2这种情况时；
                    //把2节点的任务复制给节点一，然后在删除二号节点；
                    //((*is)->taskmultimap).insert(make_pair(((*is)->taskmultimap.begin())->first,((*isc)->taskmultimap.begin()->second)));
                //    cout<<"已经把"<<((*isc)->taskmultimap.begin())->first<<"节点的值复制给第一个节点的第一个任务节点"<<endl;
                    //taskLin.erase(isc);
                    (*is)->sortNum=0;
                    (*isc)->next=*is;
                    //delete *isc;
                    //((*is)->next)->next=NULL;
                //    cout<<"已经把第一个节点打上了标记"<<endl;
                }
               else if((((*is)->next)->taskmultimap.begin())->first==((*isc)->taskmultimap.begin())->first&&((*is)->next)->next==NULL&&(*isc)->sortNum!=0){
                //    cout<<"如果第一个节点的第二个任务节点和相关的节点的任务节点的值相同"<<endl;
                    //如果是2-->10,10这种情况时，就是把节点二的任务复制给节点一的第一个节点；
                    //然后再删除任务二的节点
                    (((*is)->next)->taskmultimap).insert(make_pair((((*is)->next)->taskmultimap.begin())->first,((*isc)->taskmultimap.begin())->second));
                 //   cout<<"已经把"<<((*is)->taskmultimap.begin())->first<<"这个节点值复制给第一个节点的第二个任务节点了"<<endl;
                    //taskLin.erase(isc);
                    (*isc)->sortNum=0;
                    //((*is)->next)->next=*isc;
                    //(*isc)->next=NULL;
                    //delete *isc
                    //*isc=NULL;
                 //   cout<<"已经把第二个节点打上了标记"<<endl;
                }
            }
            if((*is)->next!=NULL&&(*isc)->next!=NULL){
               // cout<<"如果两个节点都有两个任务节点"<<endl;
            //注释的原因：在使用盘子的时候会大大的降低自己的效率
                /*if(((*is)->taskmultimap.begin())->first==((*isc)->taskmultimap.begin())->first){
                    cout<<"如果第一个节点的第一个任务节点的值和相关的第一个节点的第一个任务节点的值相同"<<endl;
                   //当情况是2-->10,2-->8,这种情况时
                    //处理的方法就是直接把节点二的动作存到节点一的动作中去，然后再设置节点一中的第二个元素指向第二个节点中的第二个元素
                    //然后再删除任务二的节点；
                    ((*is)->taskmultimap).insert(make_pair(((*is)->taskmultimap.begin())->first,((*isc)->taskmultimap.begin())->second));
                    cout<<"已经把"<<((*isc)->taskmultimap.begin())->first<<"这个位置的第一个任务节点的值复制到了相关的节点的第一个任务节点"<<endl;
                    ((*is)->next)->next=(*isc)->next;
                    cout<<"更新了指针，第一个节点的第二个任务节点指向了相关的节点的第二个任务节点"<<endl;
                    //taskLin.erase(isc);
                    (*isc)->sortNum=0;
                    cout<<"已经把第二个节点打上了标记"<<endl;
                }*/
                if(((*is)->taskmultimap.begin())->first==(((*isc)->next)->taskmultimap.begin())->first&&((*isc)->next)->next==NULL&&(*is)->NodeNum!=((*is)->next)->NodeNum&&(*isc)->NodeNum!=((*isc)->next)->NodeNum&&(*is)->sortNum!=0){
                //    cout<<"如果第一个节点的第二个任务节点的值和相关的节点的第二个任务节点相同"<<endl;
                    //当情况是2-->10,8-->2;时候
                    //把第一个节点的值给复制到第二个节的第二个值，就是8-->2-->10；
                    //然后再删除节点；
                    //(((*isc)->next)->taskmultimap).insert(make_pair((((*isc)->next)->taskmultimap.begin())->first,((*is)->taskmultimap.begin())->second));
                 //   cout<<"已经把"<<((*is)->taskmultimap.begin())->first<<"这个节点的第二个任务节点复制给相关节点的第一个任务节点"<<endl;
                    ((*isc)->next)->next=*is;
                 //   cout<<"更新了指针，相关的节点的第二个任务节点指向了第一个节点的第二个任务节点"<<endl;
                    //taskLin.erase(is);
                    (*is)->sortNum=0;
                    //((*is)->next)->next=NULL;
                   // delete *is;
                    //*is=NULL;
                //    cout<<"已经把第一个节点打上了标记"<<endl;
                }
               else if((((*is)->next)->taskmultimap.begin())->first==((*isc)->taskmultimap.begin())->first&&(*is)->NodeNum!=((*is)->next)->NodeNum&&(*isc)->NodeNum!=((*isc)->next)->NodeNum&&((*is)->next)->next==NULL&&(*isc)->sortNum!=0){
                //    cout<<"如果第一个节点的第二个任务节点的值和相关的节点的第一个任务节点的值相同"<<endl;
                   //当情况是2-->10，10-->8这种情况的时候
                    //把第二个节点的第一个节点的任务复制到第一个节点的第二个节点上去，然后更新指针的值
                   //(((*is)->next)->taskmultimap).insert(make_pair((((*is)->next)->taskmultimap.begin())->first,((*isc)->taskmultimap.begin())->second));
                //    cout<<"已经把"<<((*isc)->taskmultimap.begin())->first<<"位置的动作复制给了第一个节点的第二个任务节点上"<<endl;
                    ((*is)->next)->next=*isc;
                //    cout<<"更新指针，已经把第一个节点的第二个任务节点指向了相关的节点的第二个任务节点"<<endl;
                    //taskLin.erase(isc);
                    (*isc)->sortNum=0;
                    //delete *isc;
                    //((*isc)->next)->next=NULL;
                 //   cout<<"已经把第二个节点打上了标记"<<endl;
                }
                /*if((((*is)->next)->taskmultimap.begin())->first==(((*isc)->next)->taskmultimap.begin())->first){
                    cout<<"如果第一个节点的第二个任务节点的值和相关的节点的第二个任务节点的值相同"<<endl;
                    //当情况是2-->10，3-->10时，
                    //就把第一个节点的第二个节点复制给第二个节点的第二个节点，转化成2-->3-->10这个样子；
                    //然后再更新节点，删除节点
                    (((*isc)->next)->taskmultimap).insert(make_pair((((*isc)->next)->taskmultimap.begin())->first,(((*is)->next)->taskmultimap.begin())->second));
                    cout<<"已经把"<<(((*is)->next)->taskmultimap.begin())->first<<"这个位置的动作复制给相关节点的第二个任务节点"<<endl;
                    (*is)->next=*isc;
                    cout<<"更新了指针，把第一个节点的第一个任务节点指向了第二个节点"<<endl;
                    (*isc)->sortNum=0;
                    cout<<"已经把第一个节点打上了标记"<<endl;
                }*/
            }
        }
        i++;
    }
  //  cout<<"-------------------------------------------------------"<<endl;
    //进行简单遍历；
    int j=1;
    std::vector<Btree*>::iterator iis;
    std::multimap<int,multimap<int,string> >::iterator iit;
    std::multimap<int,string>::iterator iite;
    for(iis=taskLin.begin();iis!=taskLin.end();iis++){
    //    cout<<j<<endl;
        if((*iis)->sortNum==0) continue;
        while((*iis)!=NULL){
            for(iit=(*iis)->taskmultimap.begin();iit!=(*iis)->taskmultimap.end();iit++){
                for(iite=iit->second.begin();iite!=iit->second.end();iite++){
      //              cout<<(iit->first)<<" "<<(iite->first)<<"("<<(iite->second)<<")"<<endl;
                    if(iit->first!=0){
        //                cout<<"在"<<iit->first<<"位置执行了"<<iite->second<<"-->"<<iite->first<<"的动作"<<endl;      
                    }
                }
            }
            (*iis)=(*iis)->next;
        }
        j++;
    }
}


//函数的主要目的是创建节点找到节点的关系，然后放到把第一个节点放到容器中；
void Devil::CreateAndPut(std::vector<Btree*> &taskTree,Task task[],Sort sort[],Robot &robot,int sNum,int taskNum,InfoCons cons_not[],int cons_not_Max,InfoCons cons_notnot[],int cons_notnotMax){
    //Btree *b1=new Btree();
  //  Btree *b2=new Btree();
    std::string askloc;//用来存储询问结果
    std::string str1;
    std::string str2;
   // cout<<"创建两个节点"<<endl;
    int i;
    if(taskNum<(cons_notnotMax+cons_not_Max)&&taskNum>=2){
        for(int x=0;x<=taskNum;x++){
            if(task[x].getTaskAction()=="goto"||task[x].getTaskAction()=="close"){
                continue;
            }
            task[x].setTaskAction(" "," "," ");
        }
    }
    //先检查手里的东西是否需要，就是先处理手里的东西
    for(int v=0;v<=taskNum;v++){
        //增加一个判断，就是对于手中的物体是否满足约束的判断
        for(int c=0;c<=cons_not_Max;c++){
            if(robot.getHold()!=0){
     //           cout<<"这个物体是："<<robot.getHold()<<endl;
                if(cons_not[c].getNamex()==sort[robot.getHold()-1].getsName()&&cons_not[c].getColorx()==sort[robot.getHold()-1].getsColor()&&sort[robot.getHold()-1].getsColor()!=" "){
                 //如果盘子里的是约束的物体的话就直接放下
                    PutDown(robot.getHold());
                    sort[robot.getHold()-1].setsLoc(robot.getLoc());
                    robot.setHold(0);
                }
            }
        }
        if(task[v].getTaskNamex()==sort[robot.getHold()-1].getsName()&&task[v].getTaskColorx()==" "){
            //sort[robot.getHold()-1].setsLockSort(1);
            if(task[v].getTaskAction()=="give"&&task[v].getTaskColorx()==" "){
                sort[robot.getHold()-1].setsLockSort(1);
                int d=findHuman(sort,sNum);
                if(robot.getLoc()==d){
                    PutDown(robot.getHold());
                    sort[robot.getHold()-1].setsLoc(d);
                    robot.setHold(0);
                }
                else{
                    Move(d);
                    if(robot.getPlate()!=0){
                        sort[robot.getPlate()-1].setsLoc(d);
                    }
                    robot.setLoc(d);
                    PutDown(robot.getHold());
                    sort[robot.getHold()-1].setsLoc(d);
                    robot.setHold(0);
                }
                task[v].setTaskAction(" "," "," ");
            }
            int loc=findBigSort(task[v].getTaskNamey(),sort,sNum);
            if(task[v].getTaskAction()=="puton"){
                if(robot.getLoc()==loc){
                    PutDown(robot.getHold());
                    sort[robot.getHold()-1].setsLoc(robot.getLoc());
                    robot.setHold(0);
                }
                else{
                    Move(loc);
                    if(robot.getPlate()!=0){
                        sort[robot.getPlate()-1].setsLoc(loc);
                    }
                    robot.setLoc(loc);
                    PutDown(robot.getHold());
                    sort[robot.getHold()-1].setsLoc(robot.getLoc());
                    robot.setHold(0);
                }
                task[v].setTaskAction(" "," "," ");
            }
            if(task[v].getTaskAction()=="putin"){
                if(robot.getLoc()==loc){
                    if(sort[robot.getLoc()-1].getsClosed()){
                        PutDown(robot.getHold());
                        Open(loc);
                        sort[loc-1].setsClosed("opened");
                        PickUp(robot.getHold());
                        PutIn(robot.getHold(),loc);
                        sort[robot.getHold()-1].setsInside(loc);
                        sort[robot.getHold()-1].setsLoc(loc);
                        robot.setHold(0);
                    }
                    else{
                        PutIn(robot.getHold(),loc);
                        sort[robot.getHold()-1].setsInside(loc);
                        sort[robot.getHold()-1].setsLoc(loc);
                        robot.setHold(0);
                    }
                }
                else{
                    Move(loc);
                    if(robot.getPlate()!=0){
                        sort[robot.getPlate()-1].setsLoc(loc);
                    }
                    robot.setLoc(loc);
                    if(sort[robot.getLoc()-1].getsClosed()){
                        PutDown(robot.getHold());
                        Open(loc);
                        sort[loc-1].setsClosed("opened");
                        PickUp(robot.getHold());
                        PutIn(robot.getHold(),loc);
                        sort[robot.getHold()-1].setsInside(loc);
                        sort[robot.getHold()-1].setsLoc(loc);
                        robot.setHold(0);
                    }
                    else{
                        PutIn(robot.getHold(),loc);
                        sort[robot.getHold()-1].setsInside(loc);
                        sort[robot.getHold()-1].setsLoc(loc);
                        robot.setHold(0);
                    }
                task[v].setTaskAction(" "," "," ");
            }
        }
    }
        if(robot.getHold()!=0&&task[v].getTaskNamex()==sort[robot.getHold()-1].getsName()&&task[v].getTaskColorx()==sort[robot.getHold()-1].getsColor()&&task[v].getTaskColorx()!=" "){
            //sort[robot.getHold()-1].setsLockSort(1);
        //先执行这个动作
            int l=findBigSort(task[v].getTaskNamey(),sort,sNum);
            if(task[v].getTaskAction()=="putdown"){
                sort[robot.getHold()-1].setsLockSort(1);
                PutDown(robot.getHold());
                sort[robot.getHold()-1].setsLoc(robot.getLoc());
                robot.setHold(0);
                task[v].setTaskAction(" "," "," ");
            }
            if(task[v].getTaskAction()=="putin"){
                sort[robot.getHold()-1].setsLockSort(1);
                if(robot.getHold()==l){
                    if(sort[l-1].getsClosed()){
                        PutDown(robot.getHold());
                        Open(l);
                        PickUp(robot.getHold());
                        sort[l-1].setsClosed("opened");
                        PutIn(robot.getHold(),l);
                        sort[robot.getHold()-1].setsInside(l);
                        robot.setHold(0);
                    }
                    else{
                        PutIn(robot.getHold(),l);
                        sort[robot.getHold()-1].setsInside(l);
                        robot.setHold(0);
                    }
                }
                else{
                    Move(l);
                    robot.setLoc(l);
	                if(sort[l-1].getsClosed()){
                        PutDown(robot.getHold());
                        Open(l);
                        PickUp(robot.getHold());
                        sort[l-1].setsClosed("opened");
                        PutIn(robot.getHold(),l);
                        sort[robot.getHold()-1].setsInside(l);
                        robot.setHold(0);
                    }
                    else{
                        PutIn(robot.getHold(),l);
                        sort[robot.getHold()-1].setsInside(l);
                        robot.setHold(0);
                    }
                }
                task[v].setTaskAction(" "," "," ");
            }
            if(task[v].getTaskAction()=="puton"){
                sort[robot.getHold()-1].setsLockSort(1);
                if(robot.getLoc()==l){
                    PutDown(robot.getHold());
                    sort[robot.getHold()-1].setsLoc(l);
                    robot.setHold(0);
                }
                else{
                    Move(l);
                    robot.setLoc(l);
                    PutDown(robot.getHold());
                    sort[robot.getHold()-1].setsLoc(l);
                    robot.setHold(0);
                }
                task[v].setTaskAction(" "," "," ");
            }
            int humanloc=findHuman(sort,sNum);
            if(task[v].getTaskAction()=="give"){
                sort[robot.getHold()-1].setsLockSort(1);
                if(robot.getLoc()==humanloc){
                    PutDown(robot.getHold());
                    sort[robot.getHold()-1].setsLoc(humanloc);
                    robot.setHold(0);
                }
                else{
                    Move(humanloc);
                    robot.setLoc(humanloc);
                    PutDown(robot.getHold());
                    sort[robot.getHold()-1].setsLoc(humanloc);
                    robot.setHold(0);
                }
            task[v].setTaskAction("","","");
            }
        }
    }
    if(robot.getHold()!=0){
        PutDown(robot.getHold());
        sort[robot.getHold()-1].setsLoc(robot.getLoc());
        robot.setHold(0);
    }
   // cout<<"************************************************************"<<robot.getPlate()<<endl;
    if(robot.getPlate()!=0){
        //通过一个循环来判断盘子中的物体是否不让被拿起
        for(int u=0;u<=taskNum;u++){
            for(int m=0;m<=cons_notnotMax;m++){
                if(cons_notnot[m].getState()=="plate"&&cons_notnot[m].getNamex()==task[u].getTaskNamex()&&cons_notnot[m].getColorx()==task[u].getTaskColorx()&&task[u].getTaskColorx()!=" "){
                    task[m].setTaskAction(" "," "," ");
                    break;
                }
            }
            //先处理任务中的物体是不是有颜色
            if(task[u].getTaskNamex()==sort[robot.getPlate()-1].getsName()&&task[u].getTaskColorx()==" "){
               // sort[robot.getPlate()-1].setsLockSort(1);
                if(task[u].getTaskAction()=="give"){
                    sort[robot.getPlate()-1].setsLockSort(1);
                    int findman=findHuman(sort,sNum);
                    if(robot.getLoc()==findman){
                        FromPlate(robot.getPlate());
                        PutDown(robot.getPlate());
                        robot.setHold(0);
                        robot.setPlate(0);
                    }
                    else{
                        Move(findman);
                        robot.setLoc(findman);
                        FromPlate(robot.getPlate());
                        PutDown(robot.getPlate());
                        robot.setHold(0);
                        robot.setPlate(0);
                    }
                    task[u].setTaskAction(" ", " "," ");
                }
                if(task[u].getTaskAction()=="putdown"){
                    sort[robot.getPlate()-1].setsLockSort(1);
                    FromPlate(robot.getPlate());
                    PutDown(robot.getPlate());
                    sort[robot.getPlate()-1].setsLoc(robot.getLoc());
                    robot.setPlate(0);
                 task[u].setTaskAction(" "," "," ");
                }
                int loc1=findBigSort(task[u].getTaskNamey(),sort,sNum);
                if(task[u].getTaskAction()=="puton"){
                    sort[robot.getPlate()-1].setsLockSort(1);
                    if(robot.getLoc()==loc1){
                        FromPlate(robot.getPlate());
                        PutDown(robot.getPlate());
                        sort[robot.getPlate()-1].setsLoc(robot.getLoc());
                        robot.setPlate(0);
                    }
                    else{
                        Move(loc1);
                        robot.setLoc(loc1);
                        FromPlate(robot.getPlate());
                        PutDown(robot.getPlate());
                        sort[robot.getPlate()-1].setsLoc(loc1);
                        robot.setPlate(0);
                    }
                    task[u].setTaskAction(" "," "," ");
                }
                if(task[u].getTaskAction()=="putin"){
                    sort[robot.getPlate()-1].setsLockSort(1);
                    if(robot.getLoc()==loc1){
                        if(sort[loc1-1].getsClosed()){
                            Open(loc1);
                            sort[loc1-1].setsClosed("opened");
                            FromPlate(robot.getPlate());
                            PutIn(robot.getPlate(),loc1);
                            sort[robot.getPlate()-1].setsLoc(loc1);
                            robot.setPlate(0);
                            robot.setHold(0);
                        }
                        else{
                            FromPlate(robot.getPlate());
                            PutIn(robot.getPlate(),loc1);
                            sort[robot.getPlate()-1].setsLoc(loc1);
                            robot.setPlate(0);
                            robot.setHold(0);
                        }
                    }
                    else{
                        Move(loc1);
                        robot.setLoc(loc1);
                        if(sort[loc1-1].getsClosed()){
                            Open(loc1);
                            sort[loc1-1].setsClosed("opened");
                            FromPlate(robot.getPlate());
                            PutIn(robot.getPlate(),loc1);
                            sort[robot.getPlate()-1].setsLoc(loc1);
                            robot.setPlate(0);
                            robot.setHold(0);
                        }
                        else{
                            FromPlate(robot.getPlate());
                            PutIn(robot.getPlate(),loc1);
                            sort[robot.getPlate()-1].setsLoc(loc1);
                            robot.setPlate(0);
                            robot.setHold(0);
                        }
                    }
                    task[u].setTaskAction(" "," "," ");
                }
            }
            //在处理任务中的物体有颜色的
            if(task[u].getTaskNamex()==sort[robot.getPlate()-1].getsName()&&task[u].getTaskColorx()==sort[robot.getPlate()-1].getsColor()&&task[u].getTaskColorx()!=" "){
                //sort[robot.getPlate()-1].setsLockSort(1);
     //           cout<<"已经把盘子中的物体加上锁"<<endl;
                if(task[u].getTaskAction()=="putdown"){
                    sort[robot.getPlate()-1].setsLockSort(1);
       //             cout<<"处理盘子里物体的动作"<<endl;
                    if(robot.getHold()==0){
                        FromPlate(robot.getPlate());
                        PutDown(robot.getPlate());
                        sort[robot.getPlate()-1].setsLoc(robot.getLoc());
                        robot.setPlate(0);
                        robot.setHold(0);
                    }
                    task[u].setTaskAction(" "," "," ");
                }
                if(task[u].getTaskAction()=="give"){
                    sort[robot.getPlate()-1].setsLockSort(1);
                   int human=findHuman(sort,sNum);
                    if(robot.getLoc()==human){
                        FromPlate(robot.getPlate());
                        PutDown(robot.getPlate());
                        robot.setPlate(0);
                        robot.setHold(0);
                    }
                    else{
                        Move(human);
                        robot.setLoc(human);
                        FromPlate(robot.getPlate());
                        PutDown(robot.getPlate());
                        robot.setHold(0);
                        robot.setPlate(0);
                    }
                    task[u].setTaskAction(" "," "," ");
                }
                int loc2=findBigSort(task[u].getTaskNamey(),sort,sNum);
                if(task[u].getTaskAction()=="puton"){
                    sort[robot.getPlate()-1].setsLockSort(1);
                    if(robot.getLoc()==loc2){
                        FromPlate(robot.getPlate());
                        PutDown(robot.getHold());
                        sort[robot.getPlate()-1].setsLoc(robot.getLoc());
                        robot.setPlate(0);
                        robot.setHold(0);
                    }
                    else{
                        Move(loc2);
                        robot.setLoc(loc2);
                        FromPlate(robot.getPlate());
                        PutDown(robot.getPlate());
                        sort[robot.getPlate()-1].setsLoc(loc2);
                        robot.setPlate(0);
                    }
                    task[u].setTaskAction(" "," "," ");
                }
                if(task[u].getTaskAction()=="putin"){
                    sort[robot.getPlate()-1].setsLockSort(1);
                    if(robot.getLoc()==loc2){
                        if(sort[loc2-1].getsClosed()){
                            Open(loc2);
                            sort[loc2-1].setsClosed("opened");
                            FromPlate(robot.getPlate());
                            PutIn(robot.getPlate(),loc2);
                            sort[robot.getPlate()-1].setsLoc(loc2);
                            robot.setPlate(0);
                            robot.setHold(0);
                        }
                        else{
                            FromPlate(robot.getPlate());
                            PutIn(robot.getPlate(),loc2);
                            sort[robot.getPlate()-1].setsLoc(loc2);
                            robot.setPlate(0);
                            robot.setHold(0);
                        }
                    }
                    else{
                        Move(loc2);
                        robot.setLoc(loc2);
                        if(sort[loc2-1].getsClosed()){
                            Open(loc2);
                            sort[loc2-1].setsClosed("opened");
                            FromPlate(robot.getPlate());
                            PutIn(robot.getPlate(),loc2);
                            sort[robot.getPlate()-1].setsLoc(loc2);
                            robot.setPlate(0);
                            robot.setHold(0);
                        }
                        else{
                            FromPlate(robot.getPlate());
                            PutIn(robot.getPlate(),loc2);
                            sort[robot.getPlate()-1].setsLoc(loc2);
                            robot.setPlate(0);
                            robot.setHold(0);
                        }
                    }
                    task[u].setTaskAction(" "," "," ");
                }
            }
        }
    }
   // cout<<"************************************************************************"<<robot.getPlate()<<endl;
   // cout<<"如果机器人盘子中的东西没有处理就放下"<<endl;
    int isput=0;
    for(int l=0;l<=taskNum;l++){
        if(task[l].getTaskAction()=="pickup"){
            isput++;
        }
    }
    if(robot.getPlate()!=0&&isput>0){
     //   cout<<"盘子中有东西,准备处理"<<endl;
        FromPlate(robot.getPlate());
        PutDown(robot.getPlate());
        sort[robot.getPlate()-1].setsLoc(robot.getLoc());
        robot.setHold(0);
        robot.setPlate(0);
    }
    //执行之前判断机器人手中是否有物体如果有的话就把物体的位置更新；
  /*  if(robot.getHold()!=0){
        sort[robot.getHold()-1].setsLoc(robot.getLoc());
    }
    if(robot.getPlate()!=0){
        sort[robot.getPlate()-1].setsLoc(robot.getLoc());
    }*/
    for(i=0;i<=taskNum;i++){
        if(task[i].getTaskAction()==" "||task[i].getTaskAction()=="goto"||task[i].getTaskAction()=="close"||task[i].getTaskAction()=="putdown"){
            continue;
        }
         Btree *b1=new Btree();
         Btree *b2=new Btree();
      //  cout<<"新增两个节点"<<endl;
        if(task[i].getTaskNamex()!=""&&task[i].getTaskNamey()!=""){
       //     cout<<"这是涉及到两个物体的任务"<<endl;
            std::multimap<int,string> task1;
            std::multimap<int,string> task2;
            //找到物体的编号
            int sortNum2;
            int sortNum1=findSortByName(task[i].getTaskNamex(),task[i].getTaskColorx(),sNum,taskNum,task,sort,cons_not,cons_not_Max,cons_notnot,cons_notnotMax,robot);
            if(task[i].getTaskNamey()=="closet"||task[i].getTaskNamey()=="washmachine"||task[i].getTaskNamey()=="desk"||task[i].getTaskNamey()=="table"||task[i].getTaskNamey()=="microwave"||task[i].getTaskNamey()=="chair"||task[i].getTaskNamey()=="couch"||task[i].getTaskNamey()=="sofa"||task[i].getTaskNamey()=="worktable"||task[i].getTaskNamey()=="refigerator"||task[i].getTaskNamey()=="television"||task[i].getTaskNamey()=="airconditioner"||task[i].getTaskNamey()=="refrigerator"||task[i].getTaskNamey()=="teapoy"||task[i].getTaskNamey()=="cupboard"){
                sortNum2=findBigSort(task[i].getTaskNamey(),sort,sNum);
            }
            else{
                sortNum2=findSortByName(task[i].getTaskNamey(),task[i].getTaskColory(),sNum,taskNum,task,sort,cons_not,cons_not_Max,cons_notnot,cons_notnotMax,robot);
            }
            //找到物体的准确的位置
            if(sortNum1==-1){
         //       cout<<"什么都没得到"<<endl;
                task[i].setTaskAction(" "," "," ");
                continue;
            }
            if(sort[sortNum1-1].getsLoc()==-1){
                 askloc=AskLoc(sortNum1);
                if(askloc==""){
                    task[i].setTaskAction(" "," "," ");
                    continue;
                }
		         if(askloc=="not_known"){
                     //如果没得到答案，就再次询问，也只最后一次询问
                     askloc=AskLoc(sortNum1);
                     //如果没得到答案，就可能在机器人的盘子里或者手里
                     if(robot.getHold()==sortNum1){
                         sort[robot.getHold()-1].setsLoc(robot.getLoc());
                     }
                     if(robot.getPlate()==sortNum1){
                         sort[robot.getPlate()-1].setsLoc(robot.getLoc());
                     }
                 }
                 str1=askloc.substr(0,askloc.find("("));
           //      cout<<str1<<endl;
                 if(str1=="inside"){
                     str2=askloc.substr(askloc.find(",")+1,askloc.find(")")-askloc.find(",")-1);
             //        cout<<str2<<endl;
                     sort[sortNum1-1].setsInside(atoi(str2.c_str()));
                     sort[sortNum1-1].setsLoc(atoi(str2.c_str()));
                }
                 if(str1=="at"){
                     str2=askloc.substr(askloc.find(",")+1,askloc.find(")")-askloc.find(",")-1);
               //      cout<<str2<<endl;
                     sort[sortNum1-1].setsLoc(atoi(str2.c_str()));
                    }
            }
            if(sort[sortNum2-1].getsLoc()==-1){
                 askloc=AskLoc(sortNum2);
		         if(askloc=="unknown"){
                     //如果没得到答案，就再次询问，也只最后一次询问
                     askloc=AskLoc(sortNum2);
                 }
                 str1=askloc.substr(0,askloc.find("("));
              //   cout<<str1<<endl;
                 if(str1=="inside"){
                     str2=askloc.substr(askloc.find(",")+1,askloc.find(")")-askloc.find(",")-1);
              //       cout<<str2<<endl;
                     sort[sortNum2-1].setsInside(atoi(str2.c_str()));
                     sort[sortNum2-1].setsLoc(atoi(str2.c_str()));
                }
                 if(str1=="at"){
                     str2=askloc.substr(askloc.find(",")+1,askloc.find(")")-askloc.find(",")-1);
                //     cout<<str2<<endl;
                     sort[sortNum2-1].setsLoc(atoi(str2.c_str()));
                    }
            }
        int state1=findStateByName(sortNum1,sNum,sort);
        int flag=0;	            
        for(int m=0;m<=cons_not_Max;m++){
                    if(cons_not[m].getNamex()==sort[state1-1].getsName()&&cons_not[m].getNamey()==""&&cons_not[m].getColorx()==" "&&(cons_not[m].getState()=="opened"||cons_not[m].getState()=="goto")){
                        if(cons_not[m].getState()=="opened"&&sort[sortNum1-1].getsInside()!=state1){
                            flag=0;
                        }
                        else{
                  //          cout<<"物体的位置是在约束内，所以不能执行"<<endl;
                            flag=1;
                            break;
                        }
                    }
                }
        for(int g=0;g<=cons_notnotMax;g++){
            if(cons_notnot[g].getNamex()==sort[sortNum1-1].getsName()&&cons_notnot[g].getColorx()==" "&&cons_notnot[g].getNamey()==" "&&(cons_notnot[g].getState()=="goto"||cons_notnot[g].getState()=="opened")){
                flag=1;
                break;
            }
        }
        if(flag==1) task[i].setTaskAction(" "," "," ");
           /*     sortNum1=findSortByName(task[i].getTaskNamex(),task[i].getTaskColorx(),sNum,taskNum,task,sort,cons_not,cons_not_Max,cons_notnot,cons_notnotMax,robot);
            if(sort[sortNum1-1].getsLoc()==-1){
                     askloc=AskLoc(sortNum1);
                    if(askloc=="not_known"){
                     //如果没得到答案，就再次询问，也只最后一次询问
                     askloc=AskLoc(sortNum1);
                     //如果没得到答案，就可能在机器人的盘子里或者手里
                     if(robot.getHold()==sortNum1){
                         sort[robot.getHold()-1].setsLoc(robot.getLoc());
                     }
                     if(robot.getPlate()==sortNum1){
                         sort[robot.getPlate()-1].setsLoc(robot.getLoc());
                     }
                 }
                 str1=askloc.substr(0,askloc.find("("));
                 cout<<str1<<endl;
                 if(str1=="inside"){
                     str2=askloc.substr(askloc.find(",")+1,askloc.find(")")-askloc.find(",")-1);
                     cout<<str2<<endl;
                     sort[sortNum1-1].setsInside(atoi(str2.c_str()));
                     sort[sortNum1-1].setsLoc(atoi(str2.c_str()));
                }
                 if(str1=="at"){
                     str2=askloc.substr(askloc.find(",")+1,askloc.find(")")-askloc.find(",")-1);
                     cout<<str2<<endl;
                     sort[sortNum1-1].setsLoc(atoi(str2.c_str()));
                    }
            }
        }*/
            state1=findStateByName(sortNum1,sNum,sort);
            int state2=findStateByName(sortNum2,sNum,sort);
            //cout<<"物体的编号是"<<sortNum1<<"-->"<<sortNum2<<endl;
           // cout<<"物体的准确位置是："<<state1<<"-->"<<state2<<endl;
            b1->NodeNum=state1;
            b1->sortNum=sortNum1;
            b2->NodeNum=state2;
            b2->sortNum=sortNum2;
            //cout<<"给节点赋值"<<endl;
            if(task[i].getTaskColorx()==" "){
                task[i].setTaskColorx(sort[sortNum1-1].getsColor());
            }
            if(task[i].getTaskAction()=="puton"){
                //如果物体在容器中就要把pickup改成takeout
                if(sort[sortNum1-1].getsInside()!=-1){
		     //       cout<<"这个物体在容器中我需要先把他从容器中取出"<<endl;
                    task1.insert(make_pair(b1->sortNum,"takeout"));
                    b1->taskmultimap.insert(make_pair(b1->NodeNum,task1));
		      //      cout<<"在"<<b1->NodeNum<<"处takeout"<<"-->"<<b1->sortNum<<endl;
                    task2.insert(make_pair(b1->sortNum,"putdown"));
                    b2->taskmultimap.insert(make_pair(b2->NodeNum,task2));
                    b2->next=NULL;
                    b1->next=b2;
		        //    cout<<"在"<<b2->NodeNum<<"号位置"<<"执行putdown"<<"-->"<<b1->sortNum<<"的动作"<<endl;
                }
		        else{
                    task1.insert(make_pair(b1->sortNum,"pickup"));
                    b1->taskmultimap.insert(make_pair(b1->NodeNum,task1));
		          //  cout<<"在"<<b1->NodeNum<<"号位置"<<"执行pickup"<<"-->"<<b1->sortNum<<"的动作"<<endl;
                    task2.insert(make_pair(b1->sortNum,"putdown"));
                    b2->taskmultimap.insert(make_pair(b2->NodeNum,task2));//主要的问题是在使用Map的过程中假如key值是一样的不知道是覆盖还是把新的动作添加到新的容器中
                    b2->next=NULL;
                    b1->next=b2;
		          //  cout<<"在"<<b2->NodeNum<<"号位置"<<"执行putdown"<<"-->"<<b1->sortNum<<"的动作"<<endl;
		        }
            }
            if(task[i].getTaskAction()=="putin"){
		//如果物体在容器中就要把pickup改成takeout
                if(sort[sortNum1-1].getsInside()!=-1){
                    task1.insert(make_pair(b1->sortNum,"takeout"));
                    b1->taskmultimap.insert(make_pair(b1->NodeNum,task1));
		         //   cout<<"在"<<b1->NodeNum<<"处takeout"<<"-->"<<b1->sortNum<<endl;
                    task2.insert(make_pair(b1->sortNum,"putin"));
                    b2->taskmultimap.insert(make_pair(b2->NodeNum,task2));
                    b2->next=NULL;
                    b1->next=b2;
		         //   cout<<"在"<<b2->NodeNum<<"号位置"<<"执行putin"<<"-->"<<b1->sortNum<<"的动作"<<endl;
                }
		        else{
                    task1.insert(make_pair(b1->sortNum,"pickup"));
                    b1->taskmultimap.insert(make_pair(b1->NodeNum,task1));
		          //  cout<<"在"<<b1->NodeNum<<"号位置"<<"执行pickup"<<"-->"<<b1->sortNum<<"的动作"<<endl;
                    task2.insert(make_pair(b1->sortNum,"putin"));
                    b2->taskmultimap.insert(make_pair(b2->NodeNum,task2));
                    b1->next=b2;
                    b2->next=NULL;
		           // cout<<"在"<<b2->NodeNum<<"号位置"<<"执行putdown"<<"-->"<<b1->sortNum<<"的动作"<<endl;
		        }
            }
            if(task[i].getTaskAction()=="takeout"){
                if(sort[sortNum1-1].getsLoc()!=b2->NodeNum&&sort[sortNum1-1].getsInside()!=b2->NodeNum){
                task[i].setTaskAction(" "," "," ");
                continue;
                }
               // cout<<"这是处理takeout的动作"<<endl;
                task1.insert(make_pair(b1->sortNum,"takeout"));
                b1->taskmultimap.insert(make_pair(b2->NodeNum,task1));
                task2.insert(make_pair(b1->sortNum,"putdown"));
                b2->taskmultimap.insert(make_pair(b2->NodeNum,task2));
                b1->next=b2;
                b2->next=NULL;
               // cout<<"在"<<b2->NodeNum<<"处执行takeout"<<"-->"<<b1->sortNum<<"的动作"<<endl;
               // cout<<"在"<<b2->NodeNum<<"处执行putdown"<<"-->"<<b1->sortNum<<"的动作"<<endl;
            }
        }
/*************************************************************************************************/
        if(task[i].getTaskNamex()!=""&&task[i].getTaskNamey()==""){
            std::multimap<int,string> task1;
           // cout<<task[i].getTaskColorx()<<task[i].getTaskNamex()<<endl;
            int sortNum1=findSortByName(task[i].getTaskNamex(),task[i].getTaskColorx(),sNum,taskNum,task,sort,cons_not,cons_not_Max,cons_notnot,cons_notnotMax,robot);
           // cout<<sortNum1<<endl;
           // cout<<"*******************************************处理没找到物体的情况****************************************"<<endl;
            if(sortNum1==-1){
                task[i].setTaskAction(" "," "," ");
                continue;
            }
           // cout<<"**************************************物体有编号*******************************"<<endl;
		if(sort[sortNum1-1].getsLoc()==-1){
                 askloc=AskLoc(sortNum1);
                if(askloc==""){
                    task[i].setTaskAction(" "," "," ");
                    continue;
                 }
		         if(askloc=="unknown"){
                     //如果没得到答案，就再次询问，也只最后一次询问
                     askloc=AskLoc(sortNum1);
                     if(robot.getHold()==sortNum1){
                        sort[robot.getHold()-1].setsLoc(robot.getHold());
                     }
                     if(robot.getPlate()==sortNum1){
                        sort[robot.getPlate()-1].setsLoc(robot.getLoc());
                     }
                 }
                 str1=askloc.substr(0,askloc.find("("));
             //    cout<<str1<<endl;
                 if(str1=="inside"){
                     str2=askloc.substr(askloc.find(",")+1,askloc.find(")")-askloc.find(",")-1);
               //      cout<<str2<<endl;
                     sort[sortNum1-1].setsInside(atoi(str2.c_str()));
                     sort[sortNum1-1].setsLoc(atoi(str2.c_str()));
                }
                 if(str1=="at"){
                     str2=askloc.substr(askloc.find(",")+1,askloc.find(")")-askloc.find(",")-1);
                 //    cout<<str2<<endl;
                     sort[sortNum1-1].setsLoc(atoi(str2.c_str()));
                    }
            }
            int state1=findStateByName(sortNum1,sNum,sort);
	         int flag1=0;	            
   /*         for(int m=0;m<=cons_not_Max;m++){
                    if(cons_not[m].getNamex()==sort[state1-1].getsName()||(cons_not[m].getNamex()==sort[sortNum1-1].getsName()&&cons_not[m].getColorx()==sort[sortNum1-1].getsColor())){
                        flag1=1;
                        break;
                    }
                }*/
            for(int v=0;v<=cons_notnotMax;v++){
                if(cons_notnot[v].getColorx()==sort[sortNum1-1].getsColor()&&cons_notnot[v].getNamex()==sort[i].getsName()){
                        flag1=1;
                    break;
                }
            }
            if(flag1==1) task[i].setTaskAction("","","");
            //int state1=findStateByName(sortNum1,sNum,sort);
            b1->NodeNum=state1;
            b1->sortNum=sortNum1;
            //cout<<"这是一个只关于一个物体的任务"<<task[i].getTaskAction()<<"，这个物体的编号是:"<<b1->sortNum<<endl; 
           // cout<<"这个物体所在的位置是"<<state1<<endl;
            if(task[i].getTaskAction()=="open"||task[i].getTaskAction()=="pickup"){
                delete b2;
             //   cout<<"这是处理"<<task[i].getTaskAction()<<"的动作"<<endl;
                task1.insert(make_pair(b1->sortNum,task[i].getTaskAction()));
                b1->taskmultimap.insert(make_pair(b1->NodeNum,task1)); 
              // cout<<"执行"<<task[i].getTaskAction()<<"-->"<<b1->sortNum<<"的动作"<<endl;
            }
            /*if(task[i].getTaskAction()=="goto"){
                delete b2;
                cout<<"这是处理goto的动作"<<endl;
                task1.insert(make_pair(b1->sortNum,task[i].getTaskAction()));
                b1->taskmultimap.insert(make_pair(b1->NodeNum,task1));
            }*/
            if(task[i].getTaskAction()=="give"){
            //    cout<<"这是处理give的动作"<<endl;
                std::multimap<int,string> task2;
                int state2=findHuman(sort,sNum);//找到人的位置
             //   cout<<"Hunman的位置在"<<state2<<endl;
                task2.insert(make_pair(b1->sortNum,"pickup"));
                task1.insert(make_pair(b1->sortNum,"putdown"));
                b1->taskmultimap.insert(make_pair(b1->NodeNum,task2));
                b2->taskmultimap.insert(make_pair(state2,task1));
                b1->next=b2;
                b2->next=NULL;
            //    cout<<"执行了"<<"give  human  "<<"-->"<<b1->sortNum<<"的动作"<<endl;
            }
        }
            //每一个任务的节点都完成后，就可以把每一个先访问的节点放到容器中；
            taskTree.push_back(b1);
    }
    //基本场景录入进之后，就开始重新整合容器中的任务
  ReintegrationTask(taskTree);
}

