#include"Node.h"
#include"Sort.h"
#include"Task.h"
#include"readyadvence.h"
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
        cout<<"-------------------------yyyyy----------------------"<<endl;
        for(isc=is+1;isc!=taskLin.end();isc++){
            cout<<"---------------------zzzzz----------------------"<<endl;
            if((*is)->next==NULL&&(*isc)->next!=NULL){
                cout<<"------------------xxxxxx--------------------"<<endl;
                if(((*is)->taskmultimap.begin())->first==((*isc)->taskmultimap.begin())->first){
                    cout<<"----------------------cccccccccc-----------------"<<endl;
                    //当2,2-->10，这种情况时；
                    //处理的方法就是直接把2节点给删除掉，把节点的动作添加到另一个节点上去；
                    ((*isc)->taskmultimap).insert(make_pair(((*is)->taskmultimap.begin())->first,((*is)->taskmultimap.begin())->second));
                    //taskLin.erase(is);
                    (*is)->sortNum=0;
                }
                if(((*is)->taskmultimap.begin())->first==(((*isc)->next)->taskmultimap.begin())->first){
                    cout<<"-----------------------nnnnnnnnnn------------------"<<endl;
                    //当是2,10-->2这种情况时；
                    //处理的方法就是直接把2节点删除，把节点的动作添加到另一个节点上去；
                    (((*isc)->next)->taskmultimap).insert(make_pair(((*isc)->next)->taskmultimap.begin()->first,((*is)->taskmultimap.begin())->second));
                    //taskLin.erase(is);
                    (*is)->sortNum=0;
                }
            }
            if((*is)->next!=NULL&&(*isc)->next==NULL){
                cout<<"-----------------------------qqqqqqqqqqqqqqqqqqq---------------------"<<endl;
                if(((*is)->taskmultimap.begin())->first==((*isc)->taskmultimap.begin())->first){
                    cout<<"-------------------------------sdsdsdsds----------------------"<<endl;
                    //当2-->10,2这种情况时；
                    //把2节点的任务复制给节点一，然后在删除二号节点；
                    ((*is)->taskmultimap).insert(make_pair(((*is)->taskmultimap.begin())->first,((*isc)->taskmultimap.begin()->second)));
                    //taskLin.erase(isc);
                    (*isc)->sortNum=0;
                }
                if((((*is)->next)->taskmultimap.begin())->first==((*isc)->taskmultimap.begin())->first){
                    cout<<"---------------------oooooooooooooooooooooo------------------------"<<endl;
                    //如果是2-->10,10这种情况时，就是把节点二的任务复制给节点一的第一个节点；
                    //然后再删除任务二的节点
                    (((*is)->next)->taskmultimap).insert(make_pair((((*is)->next)->taskmultimap.begin())->first,((*isc)->taskmultimap.begin())->second));
                    //taskLin.erase(isc);
                    (*isc)->sortNum=0;
                }
            }
            if((*is)->next!=NULL&&(*isc)->next!=NULL){
                cout<<"111111111111111111111111111111111111111111111111111111"<<endl;
                if(((*is)->taskmultimap.begin())->first==((*isc)->taskmultimap.begin())->first){
                    cout<<"2222222222222222222222222222222222222222222222222222"<<endl;
                   //当情况是2-->10,2-->8,这种情况时
                    //处理的方法就是直接把节点二的动作存到节点一的动作中去，然后再设置节点一中的第二个元素指向第二个节点中的第二个元素
                    //然后再删除任务二的节点；
                    ((*is)->taskmultimap).insert(make_pair(((*is)->taskmultimap.begin())->first,((*isc)->taskmultimap.begin())->second));
                    ((*is)->next)->next=(*isc)->next;
                    //taskLin.erase(isc);
                    (*isc)->sortNum=0;
                }
                if(((*is)->taskmultimap.begin())->first==(((*isc)->next)->taskmultimap.begin())->first){
                    cout<<"333333333333333333333333333333333333333333333333333333333333333"<<endl;
                    //当情况是2-->10,8-->2;时候
                    //把第一个节点的值给复制到第二个节的第二个值，就是8-->2-->10；
                    //然后再删除节点；
                    (((*isc)->next)->taskmultimap).insert(make_pair((((*isc)->next)->taskmultimap.begin())->first,((*is)->taskmultimap.begin())->second));
                    ((*isc)->next)->next=(*is)->next;
                    //taskLin.erase(is);
                    (*is)->sortNum=0;
                }
                if((((*is)->next)->taskmultimap.begin())->first==((*isc)->taskmultimap.begin())->first){
                    cout<<"444444444444444444444444444444444444444444444444444444444444"<<endl;
                   //当情况是2-->10，10-->8这种情况的时候
                    //把第二个节点的第一个节点的任务复制到第一个节点的第二个节点上去，然后更新指针的值
                   (((*is)->next)->taskmultimap).insert(make_pair((((*is)->next)->taskmultimap.begin())->first,((*isc)->taskmultimap.begin())->second));
                    ((*is)->next)->next=(*isc)->next;
                    //taskLin.erase(isc);
                    (*isc)->sortNum=0;
                }
                if((((*is)->next)->taskmultimap.begin())->first==(((*isc)->next)->taskmultimap.begin())->first){
                    cout<<"555555555555555555555555555555555555555555555555555555555555"<<endl;
                    //当情况是2-->10，3-->10时，
                    //就把第一个节点的第二个节点复制给第二个节点的第二个节点，转化成2-->3-->10这个样子；
                    //然后再更新节点，删除节点
                    (((*isc)->next)->taskmultimap).insert(make_pair((((*isc)->next)->taskmultimap.begin())->first,(((*is)->next)->taskmultimap.begin())->second));
                    cout<<"6666666666666666666666666666666666666666666666666666666"<<endl;
                    (*is)->next=*isc;
                    //此处不知到有没有错误，因为当你在容器中删除了节点之后，不知道还存不存在这个节点；
                    cout<<"7777777777777777777777777777777777777777777777777777777"<<endl;
                    //copy=isc;
                    //taskLin.erase(copy);
                    //isc++;
                    (*isc)->sortNum=0;
                    cout<<"888888888888888888888888888888888888888888888888888888"<<endl;
                }
            }
        }
    }
    cout<<"-------------------------------------------------------"<<endl;
    //进行简单遍历；
    vector<Btree*>::iterator iis;
    multimap<int,multimap<int,string> >::iterator iit;
    multimap<int,string>::iterator iite;
    for(iis=taskLin.begin();iis!=taskLin.end();iis++){
    //    cout<<"访问第"<<i<<"个任务的第"<<1<<"节点，这个节点的位置是："<<(*is)->Num<<endl;
    //  for(it=(*is)->taskmultimap.begin();it!=(*is)->taskmultimap.end();it++){
    //        for(ite=it->second.begin();ite!=it->second.end();ite++){
    //            cout<<(it->first)<<" "<<(ite->first)<<"("<<(ite->second)<<")"<<endl;
    //            if(it->first!=0){
    //                cout<<"在"<<it->first<<"位置执行了"<<ite->second<<"-->"<<ite->first<<"的动作"<<endl;
    //            }
    //       }
    //    }
    //    cout<<"访问第"<<i<<"个任务的第"<<2<<"节点，这个节点的位置是："<<((*is)->next)->Num<<endl;
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
            i++;
        }
    }
}


//函数的主要目的是创建节点找到节点的关系，然后放到把第一个节点放到容器中；
void CreateAndPut(vector<Btree*> taskTree,Task task[],Sort sort[],int sNum,int taskNum){
    Btree *b1;
    Btree *b2;
    multimap<int,multimap<int,string> >  copy;
    cout<<"创建两个节点"<<endl;
    int i;
    for(i=0;i<taskNum;i++){
    b1=(Btree *)malloc(sizeof(Btree));
    b2=(Btree *)malloc(sizeof(Btree));
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
            cout<<"找到了任务的两个物体，位置是："<<b1->NodeNum<<"--->"<<b2->NodeNum<<endl;
            if(task[i].getTaskAction()=="puton"){
                cout<<"这是处理pution的动作"<<endl;
                task1.insert(make_pair(b1->sortNum,"pickup"));
                cout<<"task1插入成功"<<endl;
                b1->taskmultimap.insert(pair<int,multimap<int,string> >(b1->NodeNum,task1));
                cout<<"节点一存入成功"<<endl;
                task2.insert(make_pair(b1->sortNum,"putdown"));
             //不知道因为什么访问不到结构体中的multimap，但是里面的其他属性能访问到；
                b2->taskmultimap.insert(make_pair(b2->NodeNum,task2));//主要的问题是在使用Map的过程中假如key值是一样的不知道是覆盖还是把新的动作添加到新的容器中
                b2->next=NULL;
                b1->next=b2;
                cout<<"处理成功"<<endl;
            }
            if(task[i].getTaskAction()=="putin"){
                cout<<"这是处理putin的任务"<<endl;
               task1.insert(make_pair(b1->sortNum,"pickup"));
               b1->taskmultimap.insert(make_pair(b1->NodeNum,task1));
               task2.insert(make_pair(b1->sortNum,"putin"));
               b2->taskmultimap.insert(make_pair(b2->NodeNum,task2));
               b1->next=b2;
               b2->next=NULL;
                cout<<"处理成功"<<endl;
            }
            if(task[i].getTaskAction()=="takeout"){
                cout<<"这是处理takeout的动作"<<endl;
                task1.insert(make_pair(b1->sortNum,"takeout"));
                b1->taskmultimap.insert(make_pair(b1->NodeNum,task1));
                task2.insert(make_pair(b1->sortNum,"takeout"));
                b2->taskmultimap.insert(make_pair(b2->NodeNum,task2));
                b1=b2;
                b1->next=NULL;
                cout<<"处理成功"<<endl;
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
               task1.insert(make_pair(b1->sortNum,task[i].getTaskAction()));
               b1->taskmultimap.insert(make_pair(b1->NodeNum,task1));
            }
            if(task[i].getTaskAction()=="give"){
                cout<<"这是处理give的动作"<<endl;
                multimap<int,string> task2;
                int state2=findHuman(sort,sNum);//找到人的位置
                task2.insert(make_pair(b1->NodeNum,"pickup"));
                task1.insert(make_pair(b1->sortNum,"putdown"));
                b1->taskmultimap.insert(make_pair(b1->NodeNum,task2));
                b2->taskmultimap.insert(make_pair(state2,task1));
                b1->next=b2;
                b2->next=NULL;
                cout<<"处理成功"<<endl;
            }
        }
            //每一个任务的节点都完成后，就可以把每一个先访问的节点放到容器中；
            taskTree.push_back(b1);
    }
    //基本场景录入进之后，就开始重新整合容器中的任务
    ReintegrationTask(taskTree);
}
int main(){
    Sort sort[30];
	Robot robot;
	Task task[30];
	InfoCons info[30];
    vector<Btree*> taskTree;
	InfoCons cons_not[30];
	InfoCons cons_notnot[30];
    string STR=" (hold 0) (plate 16) (at 0 5) (sort 1 worktable) (size 1 big) (at 1 1)(sort 2 closet) (size 2 big) (at 2 2) (type 2 container) (closed 2)(sort 3 microwave) (size 3 big) (at 3 3) (type 3 container) (opened 3)(sort 4 plant) (size 4 big) (at 4 4)(sort 5 sofa) (size 5 big) (at 5 5) (sort 6 human) (size 6 big) (at 6 6)(sort 7 teapoy) (size 7 big) (at 7 7) (sort 8 can) (size 8 small) (color 8 red) (sort 9 can) (size 9 small) (color 9 green) (sort 10 can) (size 10 small) (color 10 black) (sort 11 can) (size 11 small) (color 11 white) (sort 12 bottle) (size 12 small) (color 12 red) (sort 13 bottle) (size 13 small) (color 13 blue) (sort 14 book) (size 14 small) (color 14 red) (sort 15 book) (size 15 small) (color 15 yellow) (inside 15 2)(sort 16 book) (size 16 small) (color 16 black)";
    string TASK="(:task (closed X) (:cond (sort X microwave))) (:task (puton X Y) (:cond (sort X can) (color X green) (sort Y sofa))) (:task (give human X) (:cond (sort X book) (color X red))) (:task (puton X Y) (:cond (sort X book) (color X yellow) (sort Y worktable))) (:task (putin X Y) (:cond (sort X bottle) (color X red) (sort Y closet))) (:task (putin X Y) (:cond (sort X can) (color X red) (sort Y microwave))) (:task (puton X Y) (:cond (sort X can) (color X black) (sort Y plant)))";
	int senceMax= 0,taskMax=0,infoMax=0,cons_not_Max=0,cons_notnotMax=0;
	 dealwithsence(STR,sort,robot,senceMax);	
	dealwithtask(TASK,task,taskMax);
	printTask(task,taskMax);
	dealwithInfoCons(TASK,info,infoMax,"info");
	dealwithInfoCons(TASK,cons_not,cons_not_Max,"cons_not");
	dealwithInfoCons(TASK,cons_notnot,cons_notnotMax,"cons_notnot");
	printScence(robot,sort,senceMax);
	updateSenceByInfo(sort,info,robot,senceMax,infoMax);
	printScence(robot,sort,senceMax);
	updateSenceByCons(sort,cons_not,robot,senceMax,cons_not_Max);
    	updateTask(sort,task,senceMax,taskMax,robot);
	printTask(task,taskMax);
    	CreateAndPut(taskTree,task,sort,senceMax,taskMax);
        cout<<"--------------------开始处理任务----------------------------"<<endl;
    return 0;
}
