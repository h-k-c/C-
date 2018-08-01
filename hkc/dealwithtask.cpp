#include "devil.hpp"
using namespace _home;
void Devil::dealWithTask(vector<Btree*> Tasktree,Robot &robot,Sort sort[]){
    //通过循环来遍历容器中的节点，然后当便利到一个节点的时候就执行节点里面里面的动作。
    cout<<"开始执行动作"<<endl;
    std::vector<Btree*>::iterator testit;//用来遍历容器中的节点；
    std::multimap<int,multimap<int,string> >::iterator testis;//用来遍历结构体中的multimap；
    std::multimap<int,string>::iterator testisc;//用来遍历map中的second；
    int i=1;
    for(testit=Tasktree.begin();testit!=Tasktree.end();testit++){
        cout<<"执行第"<<i<<"个节点的任务"<<endl;
        if((*testit)->sortNum==0){
            //当符合节点合并后，就会把节点中的sortNum赋值为0，就不会访问这个节点；
            continue;
        }
 //首先把机器人手中的物体放下，在不违反约束的情况下；
        if(robot.getHold()!=0){
            PutDown(robot.getHold());
            robot.setHold(0);
            sort[robot.getHold()-1].setsLoc(robot.getLoc());
        }
        //把机器人盘子中的东西放下，如果有东西的话
     /*   if(robot.getPlate()!=0){
            FromPlate(robot.getPlate());
            PutDown(robot.getPlate());
            robot.setPlate(0);
        }*/
        while((*testit)!=NULL){
            for(testis=(*testit)->taskmultimap.begin();testis!=(*testit)->taskmultimap.end();testis++){
                for(testisc=testis->second.begin();testisc!=testis->second.end();testisc++){
                    //首先让机器人走到指定节点的位置，也就是节点的testis->first;
                    //首先判断机器人是否在那个位置，如果不在就走过去；
                    if(robot.getLoc()!=testis->first){
                        cout<<"机器人没有在"<<testis->first<<"这个位置"<<endl;
                        Move(testis->first);
                        robot.setLoc(testis->first);
                        cout<<"机器人走到了"<<testis->first<<"这个位置"<<endl;
                    }
                    //然后再判断初始化的时候把机器人手上的东西放下，在符合约束条件情况下；
                    //然后判断动作进行执行
                    if(testisc->second=="pickup"){
                        cout<<"准备执行pickup"<<testisc->first<<"的动作"<<endl;
                        //执行pickup的动作，pickup里面的是testisc->first；
                        if(robot.getHold()!=0){
                            cout<<"机器人手中有东西，把他放到盘子上"<<endl;
                            //把物体放到盘子上
                            ToPlate(robot.getHold()); 
                            robot.setPlate(robot.getHold());
                            robot.setHold(0);
                            cout<<"已经把手中的东西放到了盘子上"<<endl;
                            //更新状态
                        }
                        PickUp(testisc->first);
                        robot.setHold(testisc->first);
                        cout<<"机器人pickup"<<testisc->first<<"成功"<<endl;
                    }
                    if(testisc->second=="putdown"){
                        //执行putdown的动作，putdown的物体是testisc->first;,如果东西在盘子里那就取盘子里的东西
                        //更新物体的位置
                        //如果机器人需要放下的物体在盘子中
                        cout<<"准备执行putdown"<<testisc->first<<"动作"<<endl;
                        if(robot.getPlate()==testisc->first&&robot.getHold()!=0){
                            cout<<"机器人需要的东西在盘子上,准备从盘子上拿"<<endl;
                            PutDown(robot.getHold());
                            FromPlate(testisc->first);
                            PutDown(testisc->first);
                            PickUp(robot.getHold());
                            cout<<"已经把物体拿到手上"<<endl;
                        }
                        else{
                            PutDown(testisc->first);
                            sort[testisc->first-1].setsLoc(testis->first);
                            robot.setHold(0);
                            cout<<"已经把手中的"<<testisc->first<<"放下了"<<endl;
                        }
                    }
                    if(testisc->second=="putin"){
                        //执行putin动作，putin的物体是testisc-first;
                        //更新物体的位置
                        cout<<"准备执行putin动作"<<endl;
                        if(sort[testis->first-1].getsClosed()==true){
                            cout<<"这个容器是关着的,我把它打开"<<endl;
                            Open(testis->first);
                            sort[testis->first-1].setsClosed("opened");
                            cout<<"我已经把"<<testis->first<<"打开了"<<endl;
                        }
                        PutIn(testisc->first,testis->first);
                        sort[testisc->first-1].setsLoc(testis->first);
                        sort[testisc->first-1].setsInside(testis->first);
                        robot.setHold(0);
                        cout<<"我把"<<testisc->first<<"放到了"<<testis->first<<"中"<<endl;
                    }
                    if(testisc->second=="takeout"){
                        //执行takeout动作，takeout的物体是testisc->first;
                        //更新物体的状态
                        //如果手中有物体的话先把他放在盘子里
                        cout<<"准备执行takeout动作"<<endl;
                        if(robot.getHold()!=0){
                            cout<<"我手中有东西，我先把他放到盘子里"<<endl;
                            ToPlate(robot.getHold());
                            robot.setPlate(robot.getHold());
                            robot.setHold(0);
                            cout<<"我的手上没有东西了，准备执行takeout动作"<<endl;
                        }
                        if(sort[testis->first-1].getsClosed()==true){
                            cout<<"容器是关着的，我要把它打开"<<endl;
                            Open(testis->first);
                            sort[testis->first-1].setsClosed("opened");
                            cout<<"已经把容器打开"<<endl;
                        }
                        TakeOut(testisc->first,testis->first);
                        sort[testisc->first-1].setsInside(0);
                        robot.setHold(testisc->first);
                        cout<<"takeout执行成功"<<endl;
                    }
                    if(testisc->second=="goto"){
                        cout<<"准备执行goto的动作"<<endl;
                        //执行goto的动作，goto的目的是testisc->first;
                        //更新机器人的位置
                        if(robot.getLoc()==testisc->first){
                            cout<<"I am already here"<<endl;
                        }
                        Move(testisc->first);
                        robot.setLoc(testisc->first);
                        cout<<"已经走到"<<testisc->first<<"这个动作"<<endl;
                    }
                    if(testisc->second=="open"){
                        cout<<"准备执行open动作"<<endl;
                        //执行open的动作，open的物体是testisc->first;
                        //open动作是最先执行的
                        //更新状态
                        if(!sort[testisc->first-1].getsClosed()){
                            cout<<"I already opened"<<endl;
                        }
                        if(sort[testisc->first-1].getsClosed()){
                            Close(testisc->first);
                            sort[testisc->first-1].setsClosed("opened");
                        }
                        cout<<"已经打开了"<<testisc->first<<endl;
                    }
                    if(testisc->second=="close"){//这里先写的只关闭的动作。
                        //执行close的动作是最后
                        //更新状态
                        //如果只是个单个的任务不涉及到其他的任务的话就是关闭这个容器，如果涉及到其他的容器的话就要最后执行；
                        cout<<"准备执行close动作"<<endl;
                        if(sort[testisc->first-1].getsClosed()!=true){
                            Close(testisc->first);
                            sort[testisc->first-1].setsClosed("true");
                        } 
                        cout<<testisc->first<<"已经关闭了"<<endl;
                    }
                }
            }
            *testit=(*testit)->next;
        }
        i++;
    }
}
