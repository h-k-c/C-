#include "devil.hpp"
using namespace _home;
int findSort(string name,Sort sort[],int sNum);
int findSort(string name,Sort sort[],int sNum){
    int i=0;
    for(i;i<=sNum;i++){
        if(sort[i].getsName()==name){
            return i+1;
        }
    }
    return -1;
}
int checkNeed(Task task[],int Tasknum,int num,Sort sort[],Robot robot,InfoCons cons_notnot[],int cons_notnot_Max){
    int need=0;
    for(int h=0;h<=cons_notnot_Max;h++){
        //如果盘子里的是约束条件的话就不放下
        if(cons_notnot[h].getState()=="plate"&&cons_notnot[h].getNamex()==sort[robot.getPlate()-1].getsName()&&cons_notnot[h].getColorx()==sort[robot.getPlate()-1].getsColor()){
                need=1;
                return need;
        }
        for(int x=0;x<=Tasknum;x++){
            if(task[x].getTaskNamex()==sort[robot.getPlate()-1].getsName()&&task[x].getTaskColorx()==sort[robot.getPlate()-1].getsColor()){
                need=1;
            }
        }
    }
    return need;
}
void Devil::dealWithTask(std::vector<Btree*> Tasktree,Task task[],int Tasknum,Robot &robot,Sort sort[],int sNum,InfoCons cons_notnot[],int cons_notnot_Max,InfoCons cons_not[],int cons_not_Max){
    //通过循环来遍历容器中的节点，然后当便利到一个节点的时候就执行节点里面里面的动作。
   // cout<<"开始执行动作"<<endl;
    std::vector<Btree*>::iterator testit;//用来遍历容器中的节点；
    std::multimap<int,multimap<int,string> >::iterator testis;//用来遍历结构体中的multimap；
    std::multimap<int,string>::iterator testisc;//用来遍历map中的second；
    int i=1;
    int need=0,needPlate=0;
    for(testit=Tasktree.begin();testit!=Tasktree.end();testit++){
     //   cout<<"执行第"<<i<<"个节点的任务"<<endl;
        if((*testit)->sortNum==0){
            continue;
        }
 //首先把机器人手中的物体放下，在不违反约束的情况下；
        if(robot.getHold()!=0&&i==1){
                PutDown(robot.getHold());
                sort[robot.getHold()-1].setsLoc(robot.getLoc());
                robot.setHold(0);
        }
        //把机器人盘子中的东西放下，如果有东西的话
      /* if(robot.getPlate()!=0&&i==1){
           needPlate=checkNeed(task,Tasknum,robot.getPlate(),sort,robot,cons_notnot,cons_notnot_Max);
           if(needPlate==0){
               if(robot.getHold()==0){
                    FromPlate(robot.getPlate());
                    PutDown(robot.getPlate());
                    sort[robot.getPlate()-1].setsLoc(robot.getLoc());
                    robot.setPlate(0);
                    robot.setHold(0);
                }
               else{
                  PutDown(robot.getHold());
                   int copyrobot=robot.getHold();
                   robot.setHold(0);
                   FromPlate(robot.getPlate());
                   PutDown(robot.getPlate());
                   robot.setHold(0);
                   robot.setPlate(0);
                   PickUp(copyrobot);
                   robot.setHold(copyrobot);
               }
           }
           else{
               cout<<"这个物体任务需要我就不需要放下了"<<endl;
           }
       }*/
        //添加特殊情况；就是机器人在任务物体的位置的时候，先执行任务，执行过后就打上标记；
        //主要的思想就是用一节点来保存需要放到第一个的元素，然后给那个元素打上标记； 
      while(*testit!=NULL){
            for(testis=(*testit)->taskmultimap.begin();testis!=(*testit)->taskmultimap.end();testis++){
                for(testisc=testis->second.begin();testisc!=testis->second.end();testisc++){
       //             cout<<"HKHKHKHKHKKHKHKH"<<endl;
                    //首先让机器人走到指定节点的位置，也就是节点的testis->first;
                    
                    if(robot.getLoc()!=testis->first){
         //                    cout<<"机器人没有在"<<testis->first<<"这个位置"<<endl;
                             Move(testis->first);
                             robot.setLoc(testis->first);
           //                  cout<<"机器人走到了"<<testis->first<<"这个位置"<<endl; 
                    }
                    //然后判断动作进行执行
                    if(testisc->second=="pickup"){
             //           cout<<"准备执行pickup"<<testisc->first<<"的动作"<<endl;
                        //执行pickup的动作，pickup里面的是testisc->first；
                        if(robot.getHold()==testisc->first||robot.getPlate()==testisc->first){
               //             cout<<"物体已经在我的手上"<<endl;
                        }
                        else if(robot.getHold()!=testisc->first&&robot.getHold()!=0&&robot.getPlate()==0){
                 //           cout<<"机器人手中有东西，把他放到盘子上"<<endl;
                            //把物体放到盘子上
                            ToPlate(robot.getHold()); 
                            robot.setPlate(robot.getHold());
                            robot.setHold(0);
                            PickUp(testisc->first);
                             robot.setHold(testisc->first);
                   //         cout<<"已经把手中的东西放到了盘子上"<<endl;
                            //更新状态
                        }
                       else if(sort[testisc->first-1].getsInside()!=-1&&robot.getHold()==0){
                                if(sort[testis->first-1].getsClosed()){
                                    Open(sort[testisc->first-1].getsInside());
                                    sort[sort[testisc->first-1].getsInside()-1].setsClosed("opened");
                     //               cout<<"容器是关着的，我已经打开了"<<endl;
                                }
                                TakeOut(testisc->first,sort[testisc->first-1].getsInside());
                                sort[testisc->first-1].setsInside(-1);
                                robot.setHold(testisc->first);
                       //         cout<<"已经把物体从容器中取出"<<endl;
                        }
                       else if(robot.getHold()==0){
                                PickUp(testisc->first);
                                robot.setHold(testisc->first);
                         //       cout<<"机器人pickup"<<testisc->first<<"成功"<<endl;
                        }
                    }
                    if(testisc->second=="putdown"){
                        //执行putdown的动作，putdown的物体是testisc->first;,如果东西在盘子里那就取盘子里的东西
                        //更新物体的位置
                        //如果机器人需要放下的物体在盘子中
                        //cout<<"准备执行putdown"<<testisc->first<<"动作"<<endl;
                        if(robot.getPlate()==testisc->first&&robot.getHold()!=0){
                          //  cout<<"机器人需要的东西在盘子上,准备从盘子上拿"<<endl;
                            PutDown(robot.getHold());
                            int coppy=robot.getHold();
                            FromPlate(testisc->first);
                            robot.setHold(testisc->first);
                            robot.setPlate(0);
                            PutDown(testisc->first);
                            PickUp(coppy);
                            robot.setHold(coppy);
                        //    cout<<"已经把物体拿到手上"<<endl;
                        }
                        else if(robot.getHold()==0&&robot.getPlate()==testisc->first){
                            FromPlate(testisc->first);
                            robot.setPlate(0);
                            robot.setHold(testisc->first);
                            PutDown(testisc->first);
                            sort[testisc->first-1].setsLoc(testis->first);
                            robot.setHold(0);
                          //  cout<<"手中的东西已经放下"<<endl;
                        }
                        else{
                            PutDown(testisc->first);
                            robot.setHold(0);
                            sort[testisc->first-1].setsLoc(testis->first);
                        }
                    }
                    if(testisc->second=="putin"){
                        //执行putin动作，putin的物体是testisc-first;
                        //更新物体的位置
                        //cout<<"准备执行putin动作"<<endl;
                        if(sort[testis->first-1].getsClosed()){
                            if(robot.getHold()!=0){
                                PutDown(robot.getHold());
                          //     cout<<"这个容器是关着的,我把它打开"<<endl;
                               Open(testis->first);
                               sort[testis->first-1].setsClosed("opened");
                                PickUp(robot.getHold());
                                robot.setHold(robot.getHold());
                            }
                            else{
                            //    cout<<"这个容器是关着的,我把它打开"<<endl;
                                Open(testis->first);
                                sort[testis->first-1].setsClosed("opened");
                             //   cout<<"我已经把"<<testis->first<<"打开了"<<endl;
                            }
                        }
                         if(robot.getPlate()==testisc->first&&robot.getHold()!=0){
                            PutDown(robot.getHold());
                            FromPlate(testisc->first);
                            PutIn(testisc->first,testis->first);
                            sort[testisc->first-1].setsLoc(testis->first);
                            sort[testisc->first-1].setsInside(testis->first);
                            PickUp(robot.getHold());
                        }
                        if(sort[testisc->first-1].getsInside()==testis->first){
                           // cout<<"我已经在里面了"<<endl;
                        }
                        if(robot.getHold()==0&&robot.getPlate()==testisc->first){
                            FromPlate(testisc->first);
                            robot.setHold(testisc->first);
                            PutIn(testisc->first,testis->first);
                            sort[testisc->first-1].setsInside(testis->first);
                            robot.setPlate(0);
                            robot.setHold(0);
                        }
                       if(robot.getHold()==testisc->first){
                            PutIn(testisc->first,testis->first);
                            sort[testisc->first-1].setsLoc(testis->first);
                            sort[testisc->first-1].setsInside(testis->first);
                            robot.setHold(0);
                           // cout<<"我把"<<testisc->first<<"放到了"<<testis->first<<"中"<<endl;
                        }
                    }
                    if(testisc->second=="takeout"){
                        //执行takeout动作，takeout的物体是testisc->first;
                        //更新物体的状态
                        //如果手中有物体的话先把他放在盘子里
                       // cout<<"准备执行takeout动作"<<endl;
                        if(robot.getHold()==testisc->first||robot.getPlate()==testisc->first){
                         //   cout<<"已经在我的盘子里或者手上"<<endl;
                        }
                        else if(sort[testisc->first-1].getsInside()==-1&&sort[testisc->first-1].getsLoc()==testis->first){
                           // cout<<"物体已经被取出"<<endl;
                            PickUp(testisc->first);
                            robot.setHold(testisc->first);
                        }
                        else if(robot.getHold()!=0&&robot.getPlate()==0){
                          //  cout<<"我手中有东西，我先把他放到盘子里"<<endl;
                            ToPlate(robot.getHold());
                            robot.setPlate(robot.getHold());
                            robot.setHold(0);
                          //  cout<<"我的手上没有东西了，准备执行takeout动作"<<endl;
                              if(sort[testis->first-1].getsClosed()){
                            //    cout<<"容器是关着的，我要把它打开"<<endl;
                                Open(testis->first);
                                sort[testis->first-1].setsClosed("opened");
                            //    cout<<"已经把容器打开"<<endl;
                            }
                                TakeOut(testisc->first,testis->first);
                                sort[testisc->first-1].setsInside(-1);
                                robot.setHold(testisc->first);
                            // cout<<"执行takeout成功"<<endl;
                        }
                        else if(robot.getHold()==0&&robot.getPlate()!=0){
                            if(sort[testis->first-1].getsClosed()){
                                Open(testis->first);
                                sort[testis->first-1].setsClosed("opened");
                            }
                                 TakeOut(testisc->first,testis->first);
                                sort[testisc->first-1].setsInside(0);
                                robot.setHold(testisc->first);
                        }
                        else if(robot.getHold()==0&&robot.getPlate()==0){
                                if(sort[testis->first-1].getsClosed()){
                                Open(testis->first);
                                sort[testis->first-1].setsClosed("opened");
                            }
                                TakeOut(testisc->first,testis->first);
                                sort[testisc->first-1].setsInside(-1);
                                robot.setHold(testisc->first);
                        }
                    }
                    /*if(testisc->second=="goto"){
                        cout<<"准备执行goto的动作"<<endl;
                        //执行goto的动作，goto的目的是testisc->first;
                        //更新机器人的位置
                        if(robot.getLoc()==testisc->first){
                            cout<<"I am already here"<<endl;
                        }
                        else{
                             Move(testisc->first);
                             robot.setLoc(testisc->first);
                             cout<<"已经走到"<<testisc->first<<"这个地方"<<endl;
                        }
                    }*/
                    if(testisc->second=="open"){
                       // cout<<"准备执行open动作"<<endl;
                        //执行open的动作，open的物体是testisc->first;
                        //open动作是最先执行的
                        //更新状态
                        if(!sort[testisc->first-1].getsClosed()){
                        //    cout<<"I already opened"<<endl;
                        }
                        if(sort[testisc->first-1].getsClosed()){
                            if(robot.getHold()!=0){
                                PutDown(robot.getHold());
                                Open(testisc->first);
                                PickUp(robot.getHold());
                                sort[testisc->first-1].setsClosed("opened");
                            }
                            else{
                                Open(testisc->first);
                                sort[testisc->first-1].setsClosed("opened");
                            }
                        }
                       // cout<<"已经打开了"<<testisc->first<<endl;
                    }
                    if(testisc->second=="close"){//这里先写的只关闭的动作。
                        //执行close的动作是最后
                        //更新状态
                        //如果只是个单个的任务不涉及到其他的任务的话就是关闭这个容器，如果涉及到其他的容器的话就要最后执行；
                       // cout<<"准备执行close动作"<<endl;
                        if(sort[testisc->first-1].getsClosed()!=true){
                             Close(testisc->first);
                             sort[testisc->first-1].setsClosed("true"); 
                         //    cout<<testisc->first<<"已经关闭了"<<endl;
                        }
                        else{
                          //  cout<<"我已经是关闭状态"<<endl;
                         }
                    }
                }
            }
            *testit=(*testit)->next;
       }
        //释放节点空间
       // if((*testit)->next!=NULL){
        //    delete (*testit)->next;
        //}
       // delete *testit;
      //  *testit=NULL;
       // testit=Tasktree.erase(testit);
       // cout<<"第"<<i<<"个节点已经释放"<<endl;
        i++;
    }
    //单独处理close
    for(int z=0;z<=Tasknum;z++){
        if(task[z].getTaskAction()=="close"){
           // cout<<"*********************"<<task[z].getTaskNamex()<<"***************"<<endl;
            if(task[z].getTaskNamex()=="container"){
                task[z].setTaskAction(" "," "," ");
                continue;
            }
            int f=findSort(task[z].getTaskNamex(),sort,sNum);
            if(sort[f-1].getsClosed()){
                continue;
            }
            if(robot.getLoc()==f){
                if(robot.getHold()!=0&&robot.getPlate()!=0){
                    PutDown(robot.getHold());
                    int copyNum=robot.getHold();
                    robot.setHold(0);
                    Close(f);
                    PickUp(copyNum);
                    robot.setHold(copyNum);
                }
                else if(robot.getHold()!=0&&robot.getPlate()==0){
                    ToPlate(robot.getHold());
                    robot.setPlate(robot.getHold());
                    robot.setHold(0);
                    Close(f);
                  //  FromPlate(robot.getPlate());
                }
                else if(robot.getHold()==0){
                    Close(f);
                }
            }
            else{
                 Move(f);
                 robot.setLoc(f);
		        if(robot.getHold()!=0&&robot.getPlate()!=0){
                    PutDown(robot.getHold());
                    int copyNum=robot.getHold();
                    robot.setHold(0);
                    Close(f);
                    PickUp(copyNum);
                }
                else if(robot.getHold()!=0&&robot.getPlate()==0){
                    ToPlate(robot.getHold());
                    robot.setPlate(robot.getHold());
                    robot.setHold(0);
                    Close(f);
                   // FromPlate(robot.getPlate());
                }
                else if(robot.getHold()==0){
                    Close(f);
                }
            }
        }
    }
    //cout<<"开始执行goto操作"<<endl;
    for(int k=0;k<=Tasknum;k++){
    //如果所有的任务都执行完了，看看任务的最后一个是不是goto如果是的话就执行
        if(task[k].getTaskAction()=="goto"){
            if(task[k].getTaskNamex()=="container"){
                task[k].setTaskAction(" ", " "," ");
                continue;
            }
            int j=findSort(task[k].getTaskNamex(),sort,sNum);
            if(robot.getLoc()==j){
      //          cout<<"我已经在这里了"<<endl;
            }
            else{
                Move(j);
        //        cout<<"移动到"<<j<<"号物体成功"<<endl;
            }
        }
    }
    //添加一个释放所有的内存，用delete来实现
    for(std::vector<Btree*>::reverse_iterator it=Tasktree.rbegin();it!=Tasktree.rend();it++){
        //cout<<"hkhkhkhkhk"<<endl;
       // if((*it)->next!=NULL){
        //    cout<<"进入if语句了"<<endl;
        //    delete (*it)->next;
       // } 
        delete *it;
        *it=NULL;
        //cout<<"delete成功"<<endl;
        //it=Tasktree.erase(it);
    }
    //cout<<"容器中所有的指针已经释放"<<endl;
    //cout<<"所有的任务已经完成"<<endl;
}
