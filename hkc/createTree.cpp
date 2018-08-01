/*************************************************************************
	> File Name: createTree.cpp
	> Author:hkc 
    > Mail: 2605245956@qq.com
	> Created Time: 2018年07月25日 星期三 11时23分41秒
 ************************************************************************/
#include "devil.hpp"
using namespace _home;
void  ReintegrationTask(vector<Btree*> taskLin);
int findSortByName(string name,string color,int sNum,Sort sort[]);
int findStateByName(int sortNum,int sNum,Sort sort[]);
int findHuman(Sort sort[],int sNum);
int findSortByName(string name,string color,int sNum,Sort sort[]){
    int i;
    for(i=0;i<sNum;i++){
        if(sort[i].getsName()==name&&sort[i].getsColor()==color){
            return i+1;
        }
    }
    return -1;
}
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



void  ReintegrationTask(vector<Btree*> taskLin){
    //还需要写一个遍历的函数，用来检查是否有相同的节点
    multimap<int,multimap<int,string> >::iterator it;
    vector<Btree*>::iterator is;
    vector<Btree*>::iterator isc;
    multimap<int,string>::iterator ite;
    int i=1;
    cout<<"---------------------------4---------------------------------"<<endl;
    //这个循环就是用来整合创建好的所有的节点
    //有问题的地方，就是的得到结构体中的multimap后，在通过循环来查找节点的时候无法获得节点的位置就是multimap中的key值；我的暂时的解决方法是用begin()方法，因为此方法是使用的第一个值。正常情况下的一个节点只有一个动作
    for(is=taskLin.begin();is!=taskLin.end();is++){
        cout<<"开始遍历第"<<i<<"个"<<endl<<endl<<endl;
        for(isc=is+1;isc!=taskLin.end();isc++){
            cout<<"从第"<<i+1<<"个节点开始遍历"<<endl;
            if((*is)->next==NULL&&(*isc)->next!=NULL){
                cout<<"如果第一个只有一个任务节点，相关的有两个任务节点"<<endl;
                if(((*is)->taskmultimap.begin())->first==((*isc)->taskmultimap.begin())->first){
                    cout<<"如果第一个节点中的第一个任务节点的值和第二个节点的第一个任务节点的值相同"<<endl;
                    //当2,2-->10，这种情况时；
                    //处理的方法就是直接把2节点给删除掉，把节点的动作添加到另一个节点上去；
                    ((*isc)->taskmultimap).insert(make_pair(((*is)->taskmultimap.begin())->first,((*is)->taskmultimap.begin())->second));
                    cout<<"已经把"<<((*is)->taskmultimap.begin())->first<<"位置的动作给复制到下一个节点的第一个任务节点"<<endl;
                    (*is)->sortNum=0;
                    cout<<"已经把第一个节点打上了标记"<<endl;
                }
                if(((*is)->taskmultimap.begin())->first==(((*isc)->next)->taskmultimap.begin())->first){
                    cout<<"如果第一个节点的任务节点的值和第二个节点的第二个任务节点一样"<<endl;
                    //当是2,10-->2这种情况时；
                    //处理的方法就是直接把2节点删除，把节点的动作添加到另一个节点上去；
                    (((*isc)->next)->taskmultimap).insert(make_pair((((*isc)->next)->taskmultimap.begin())->first,((*is)->taskmultimap.begin())->second));
                    cout<<"已经把"<<((*is)->taskmultimap.begin())->first<<"位置的动作给复制到下一个节点的第二个任务节点"<<endl;
                    //taskLin.erase(is);
                    (*is)->sortNum=0;
                    cout<<"已经把第一个节点打上了标记"<<endl;
                }
            }
            if((*is)->next!=NULL&&(*isc)->next==NULL){
                cout<<"如果第一个节点有两个任务节点，相关的只有一个节点"<<endl;
                if(((*is)->taskmultimap.begin())->first==((*isc)->taskmultimap.begin())->first){
                    cout<<"如果第一个节点的第一个任务节点的值和相关的节点的任务节点的值相同"<<endl;
                    //当2-->10,2这种情况时；
                    //把2节点的任务复制给节点一，然后在删除二号节点；
                    ((*is)->taskmultimap).insert(make_pair(((*is)->taskmultimap.begin())->first,((*isc)->taskmultimap.begin()->second)));
                    cout<<"已经把"<<((*isc)->taskmultimap.begin())->first<<"节点的值复制给第一个节点的第一个任务节点"<<endl;
                    //taskLin.erase(isc);
                    (*isc)->sortNum=0;
                    cout<<"已经把第二个节点打上了标记"<<endl;
                }
                if((((*is)->next)->taskmultimap.begin())->first==((*isc)->taskmultimap.begin())->first){
                    cout<<"如果第一个节点的第二个任务节点和相关的节点的任务节点的值相同"<<endl;
                    //如果是2-->10,10这种情况时，就是把节点二的任务复制给节点一的第一个节点；
                    //然后再删除任务二的节点
                    (((*is)->next)->taskmultimap).insert(make_pair((((*is)->next)->taskmultimap.begin())->first,((*isc)->taskmultimap.begin())->second));
                    cout<<"已经把"<<((*is)->taskmultimap.begin())->first<<"这个节点值复制给第一个节点的第二个任务节点了"<<endl;
                    //taskLin.erase(isc);
                    (*isc)->sortNum=0;
                    cout<<"已经把第二个节点打上了标记"<<endl;
                }
            }
            if((*is)->next!=NULL&&(*isc)->next!=NULL){
                cout<<"如果两个节点都有两个任务节点"<<endl;
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
                if(((*is)->taskmultimap.begin())->first==(((*isc)->next)->taskmultimap.begin())->first){
                    cout<<"如果第一个节点的第二个任务节点的值和相关的节点的第二个任务节点相同"<<endl;
                    //当情况是2-->10,8-->2;时候
                    //把第一个节点的值给复制到第二个节的第二个值，就是8-->2-->10；
                    //然后再删除节点；
                    (((*isc)->next)->taskmultimap).insert(make_pair((((*isc)->next)->taskmultimap.begin())->first,((*is)->taskmultimap.begin())->second));
                    cout<<"已经把"<<((*is)->taskmultimap.begin())->first<<"这个节点的第二个任务节点复制给相关节点的第一个任务节点"<<endl;
                    ((*isc)->next)->next=(*is)->next;
                    cout<<"更新了指针，相关的节点的第二个任务节点指向了第一个节点的第二个任务节点"<<endl;
                    //taskLin.erase(is);
                    (*is)->sortNum=0;
                    cout<<"已经把第一个节点打上了标记"<<endl;
                }
                if((((*is)->next)->taskmultimap.begin())->first==((*isc)->taskmultimap.begin())->first){
                    cout<<"如果第一个节点的第二个任务节点的值和相关的节点的第一个任务节点的值相同"<<endl;
                   //当情况是2-->10，10-->8这种情况的时候
                    //把第二个节点的第一个节点的任务复制到第一个节点的第二个节点上去，然后更新指针的值
                   (((*is)->next)->taskmultimap).insert(make_pair((((*is)->next)->taskmultimap.begin())->first,((*isc)->taskmultimap.begin())->second));
                    cout<<"已经把"<<((*isc)->taskmultimap.begin())->first<<"位置的动作复制给了第一个节点的第二个任务节点上"<<endl;
                    ((*is)->next)->next=(*isc)->next;
                    cout<<"更新指针，已经把第一个节点的第二个任务节点指向了相关的节点的第二个任务节点"<<endl;
                    //taskLin.erase(isc);
                    (*isc)->sortNum=0;
                    cout<<"已经把第二个节点打上了标记"<<endl;
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
    cout<<"-------------------------------------------------------"<<endl;
    //进行简单遍历；
    int j=1;
    vector<Btree*>::iterator iis;
    multimap<int,multimap<int,string> >::iterator iit;
    multimap<int,string>::iterator iite;
    for(iis=taskLin.begin();iis!=taskLin.end();iis++){
        cout<<j<<endl;
        if((*iis)->sortNum==0) continue;
        while((*iis)!=NULL){
            for(iit=(*iis)->taskmultimap.begin();iit!=(*iis)->taskmultimap.end();iit++){
                for(iite=iit->second.begin();iite!=iit->second.end();iite++){
                    cout<<(iit->first)<<" "<<(iite->first)<<"("<<(iite->second)<<")"<<endl;
                    if(iit->first!=0){
                        cout<<"在"<<iit->first<<"位置执行了"<<iite->second<<"-->"<<iite->first<<"的动作"<<endl;      
                    }
                }
            }
            (*iis)=(*iis)->next;
        }
        j++;
    }
}


//函数的主要目的是创建节点找到节点的关系，然后放到把第一个节点放到容器中；
void Devil::CreateAndPut(vector<Btree*> &taskTree,Task task[],Sort sort[],int sNum,int taskNum){
    //Btree *b1=new Btree();
  //  Btree *b2=new Btree();
    multimap<int,multimap<int,string> >  copy;
    cout<<"创建两个节点"<<endl;
    int i;
    for(i=0;i<=taskNum;i++){
        Btree *b1=new Btree();
        Btree *b2=new Btree();
    //b1=(Btree *)malloc(sizeof(Btree));
    //b1->next=(Btree *)malloc(sizeof(Btree));
    //b2=(Btree *)malloc(sizeof(Btree));
    //b2->next=(Btree *)malloc(sizeof(Btree));
        cout<<"新增两个节点"<<endl;
        if(task[i].getTaskNamex()!=""&&task[i].getTaskNamey()!=""){
            cout<<"这是涉及到两个物体的任务"<<endl;
            multimap<int,string> task1;
            multimap<int,string> task2;
            //找到物体的编号
            int sortNum1=findSortByName(task[i].getTaskNamex(),task[i].getTaskColorx(),sNum,sort);
            int sortNum2=findSortByName(task[i].getTaskNamey(),task[i].getTaskColory(),sNum,sort);
            cout<<"物体的编号分别是"<<sortNum1<<"--->"<<sortNum2<<endl;
            //找到物体的准确的位置
            int state1=findStateByName(sortNum1,sNum,sort);
            int state2=findStateByName(sortNum2,sNum,sort);
            cout<<"物体的准确位置是："<<state1<<"-->"<<state2<<endl;
            b1->NodeNum=state1;
            b1->sortNum=sortNum1;
            b2->NodeNum=state2;
            b2->sortNum=sortNum2;
            cout<<"给节点赋值"<<endl;
            if(task[i].getTaskAction()=="puton"){
                //如果物体在容器中就要把pickup改成takeout
                if(sort[sortNum1-1].getsInside()!=-1){
		            cout<<"这个物体在容器中我需要先把他从容器中取出"<<endl;
                    task1.insert(make_pair(b1->sortNum,"takeout"));
                    b1->taskmultimap.insert(make_pair(b1->NodeNum,task1));
		            cout<<"在"<<b1->NodeNum<<"处takeout"<<"-->"<<b1->sortNum<<endl;
                    task2.insert(make_pair(b1->sortNum,"putdown"));
                    b2->taskmultimap.insert(make_pair(b2->NodeNum,task2));
                    b2->next=NULL;
                    b1->next=b2;
		            cout<<"在"<<b2->NodeNum<<"号位置"<<"执行putdown"<<"-->"<<b1->sortNum<<"的动作"<<endl;
                }
		        else{
                    task1.insert(make_pair(b1->sortNum,"pickup"));
                    b1->taskmultimap.insert(make_pair(b1->NodeNum,task1));
		            cout<<"在"<<b1->NodeNum<<"号位置"<<"执行pickup"<<"-->"<<b1->sortNum<<"的动作"<<endl;
                    task2.insert(make_pair(b1->sortNum,"putdown"));
                    b2->taskmultimap.insert(make_pair(b2->NodeNum,task2));//主要的问题是在使用Map的过程中假如key值是一样的不知道是覆盖还是把新的动作添加到新的容器中
                    b2->next=NULL;
                    b1->next=b2;
		            cout<<"在"<<b2->NodeNum<<"号位置"<<"执行putdown"<<"-->"<<b1->sortNum<<"的动作"<<endl;
		        }
            }
            if(task[i].getTaskAction()=="putin"){
		//如果物体在容器中就要把pickup改成takeout
                if(sort[sortNum1-1].getsInside()!=-1){
                    task1.insert(make_pair(b1->sortNum,"takeout"));
                    b1->taskmultimap.insert(make_pair(b1->NodeNum,task1));
		            cout<<"在"<<b1->NodeNum<<"处takeout"<<"-->"<<b1->sortNum<<endl;
                    task2.insert(make_pair(b1->sortNum,"putin"));
                    b2->taskmultimap.insert(make_pair(b2->NodeNum,task2));
                    b2->next=NULL;
                    b1->next=b2;
		            cout<<"在"<<b2->NodeNum<<"号位置"<<"执行putdown"<<"-->"<<b1->sortNum<<"的动作"<<endl;
                }
		        else{
                    task1.insert(make_pair(b1->sortNum,"pickup"));
                    b1->taskmultimap.insert(make_pair(b1->NodeNum,task1));
		            cout<<"在"<<b1->NodeNum<<"号位置"<<"执行pickup"<<"-->"<<b1->sortNum<<"的动作"<<endl;
                    task2.insert(make_pair(b1->sortNum,"putin"));
                    b2->taskmultimap.insert(make_pair(b2->NodeNum,task2));
                    b1->next=b2;
                    b2->next=NULL;
		            cout<<"在"<<b2->NodeNum<<"号位置"<<"执行putdown"<<"-->"<<b1->sortNum<<"的动作"<<endl;
		        }
            }
            if(task[i].getTaskAction()=="takeout"){
                cout<<"这是处理takeout的动作"<<endl;
                task1.insert(make_pair(b1->sortNum,"takeout"));
                b1->taskmultimap.insert(make_pair(b1->NodeNum,task1));
                task2.insert(make_pair(b1->sortNum,"takeout"));
                b2->taskmultimap.insert(make_pair(b2->NodeNum,task2));
                b1=b2;
                b1->next=NULL;
                cout<<"在"<<b2->NodeNum<<"处执行takeout"<<"-->"<<b1->sortNum<<"的动作"<<endl;
            }
        }
        if(task[i].getTaskNamex()!=""&&task[i].getTaskNamey()==""){
            multimap<int,string> task1;
            int sortNum1=findSortByName(task[i].getTaskNamex(),task[i].getTaskColorx(),sNum,sort);
            int state1=findStateByName(sortNum1,sNum,sort);
            b1->NodeNum=state1;
            b1->sortNum=sortNum1;
            cout<<"这是一个只关于一个物体的任务，这个物体的编号是:"<<b1->sortNum<<endl; 
            if(task[i].getTaskAction()=="goto"||task[i].getTaskAction()=="open"||task[i].getTaskAction()=="closed"){
                cout<<"这是处理"<<task[i].getTaskAction()<<"的动作"<<endl;
                task1.insert(make_pair(b1->sortNum,task[i].getTaskAction()));
               b1->taskmultimap.insert(make_pair(b1->NodeNum,task1));
               cout<<"执行"<<task[i].getTaskAction()<<"-->"<<b1->sortNum<<"的动作"<<endl;
            }
            if(task[i].getTaskAction()=="give"){
                cout<<"这是处理give的动作"<<endl;
                multimap<int,string> task2;
                int state2=findHuman(sort,sNum);//找到人的位置
                cout<<"Hunman的位置在"<<state2<<endl;
                task2.insert(make_pair(b1->sortNum,"pickup"));
                task1.insert(make_pair(b1->sortNum,"putdown"));
                b1->taskmultimap.insert(make_pair(b1->NodeNum,task2));
                b2->taskmultimap.insert(make_pair(state2,task1));
                b1->next=b2;
                b2->next=NULL;
                cout<<"执行了"<<"give  human  "<<"-->"<<b1->sortNum<<"的动作"<<endl;
            }
        }
            //每一个任务的节点都完成后，就可以把每一个先访问的节点放到容器中；
            taskTree.push_back(b1);
    }
    //基本场景录入进之后，就开始重新整合容器中的任务
    ReintegrationTask(taskTree);
}

