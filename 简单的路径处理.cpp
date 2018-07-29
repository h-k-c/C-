/*************************************************************************
	> File Name: test.cpp
	> Author: 
	> Mail: 
	> Created Time: 2018年07月25日 星期三 16时41分05秒
 ************************************************************************/

#include<iostream>
#include<map>
#include<stdlib.h>
#include<vector>
#include<iostream>
using namespace std;
typedef struct Node{
   int Num;
   multimap<int,multimap<int,string> > taskmultimap;
    struct Node *next;
}Btree;
int main(){
    Btree *b1,*b2,*b3,*b4;
    b1=(Btree *)malloc(sizeof(Btree));
    b2=(Btree *)malloc(sizeof(Btree));
    b3=(Btree *)malloc(sizeof(Btree));
    b4=(Btree *)malloc(sizeof(Btree));
   // copy=(Btree *)malloc(sizeof(Btree));
    cout<<"-----------------------------1--------------------------------"<<endl;
    vector<Btree*> taskLin;
    b1->Num=10;
    b2->Num=20;
    b3->Num=30;
    b4->Num=20;
    multimap<int,multimap<int,string> >nextmultimap;
    multimap<int,string> nexttwomultimap;
    multimap<int,multimap<int,string> > Onemultimap;
    multimap<int,string> twomultimap;
    multimap<int,multimap<int,string> > threemultimap;
    multimap<int,string> nextThreemultimap;
    multimap<int,multimap<int,string> > fourmultimap;
    multimap<int,string> nextfour;
    cout<<"----------------------------2--------------------------------"<<endl;
    twomultimap.insert(make_pair(10,"pickup"));
    nexttwomultimap.insert(make_pair(10,"putdown"));
    Onemultimap.insert(make_pair(10,twomultimap));
    nextmultimap.insert(make_pair(20,nexttwomultimap));
    nextThreemultimap.insert(make_pair(30,"pickup"));
    threemultimap.insert(make_pair(20,nextThreemultimap));
    nextfour.insert(make_pair(30,"putdown"));
    fourmultimap.insert(make_pair(40,nextfour));
    b1->taskmultimap=Onemultimap;
    b2->taskmultimap=nextmultimap;
    b3->taskmultimap=threemultimap;
    b4->taskmultimap=fourmultimap;
    b1->next=b2;
    b2->next==NULL;
    b3->next=b4;
    b4->next=NULL;
    taskLin.push_back(b1);
    taskLin.push_back(b3);
    cout<<"---------------------------3----------------------------------"<<endl;
    //taskLin.push_back(b2);
    //还需要写一个遍历的函数，用来检查是否有相同的节点
    multimap<int,multimap<int,string> >::iterator it;
    vector<Btree*>::iterator is;
    vector<Btree*>::iterator isc;
    multimap<int,string>::iterator ite;
    int i=1;
    vector<Btree*>::iterator copy;
    cout<<"---------------------------4---------------------------------"<<endl;
    //这个循环就是用来整合创建好的所有的节点
    //有问题的地方，就是的得到结构体中的multimap后，在通过循环来查找节点的时候无法获得节点的位置就是multimap中的key值；我的暂时的解决方法是用begin()方法，因为此方法是使用的第一个值。正常情况下的一个节点只有一个动作
    for(is=taskLin.begin();is!=taskLin.end();){
        cout<<"-------------------------yyyyy----------------------"<<endl;
        for(isc=is+1;isc!=taskLin.end();){
            cout<<"---------------------zzzzz----------------------"<<endl;
            if((*is)->next==NULL&&(*isc)->next!=NULL){
                cout<<"------------------xxxxxx--------------------"<<endl;
                if(((*is)->taskmultimap.begin())->first==((*isc)->taskmultimap.begin())->first){
                    cout<<"----------------------cccccccccc-----------------"<<endl;
                    //当2,2-->10，这种情况时；
                    //处理的方法就是直接把2节点给删除掉，把节点的动作添加到另一个节点上去；
                    ((*isc)->taskmultimap).insert(make_pair(((*is)->taskmultimap.begin())->first,((*is)->taskmultimap.begin())->second));
                    //taskLin.erase(is);
                    (*is)->Num=0;
                }
                if(((*is)->taskmultimap.begin())->first==(((*isc)->next)->taskmultimap.begin())->first){
                    cout<<"-----------------------nnnnnnnnnn------------------"<<endl;
                    //当是2,10-->2这种情况时；
                    //处理的方法就是直接把2节点删除，把节点的动作添加到另一个节点上去；
                    (((*isc)->next)->taskmultimap).insert(make_pair(((*isc)->next)->taskmultimap.begin()->first,((*is)->taskmultimap.begin())->second));
                    //taskLin.erase(is);
                    (*is)->Num=0;
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
                    (*isc)->Num=0;
                }
                if((((*is)->next)->taskmultimap.begin())->first==((*isc)->taskmultimap.begin())->first){
                    cout<<"---------------------oooooooooooooooooooooo------------------------"<<endl;
                    //如果是2-->10,10这种情况时，就是把节点二的任务复制给节点一的第一个节点；
                    //然后再删除任务二的节点
                    (((*is)->next)->taskmultimap).insert(make_pair((((*is)->next)->taskmultimap.begin())->first,((*isc)->taskmultimap.begin())->second));
                    //taskLin.erase(isc);
                    (*isc)->Num=0;
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
                    (*isc)->Num=0;
                }
                if(((*is)->taskmultimap.begin())->first==(((*isc)->next)->taskmultimap.begin())->first){
                    cout<<"333333333333333333333333333333333333333333333333333333333333333"<<endl;
                    //当情况是2-->10,8-->2;时候
                    //把第一个节点的值给复制到第二个节的第二个值，就是8-->2-->10；
                    //然后再删除节点；
                    (((*isc)->next)->taskmultimap).insert(make_pair((((*isc)->next)->taskmultimap.begin())->first,((*is)->taskmultimap.begin())->second));
                    ((*isc)->next)->next=(*is)->next;
                    //taskLin.erase(is);
                    (*is)->Num=0;
                }
                if((((*is)->next)->taskmultimap.begin())->first==((*isc)->taskmultimap.begin())->first){
                    cout<<"444444444444444444444444444444444444444444444444444444444444"<<endl;
                   //当情况是2-->10，10-->8这种情况的时候
                    //把第二个节点的第一个节点的任务复制到第一个节点的第二个节点上去，然后更新指针的值
                   (((*is)->next)->taskmultimap).insert(make_pair((((*is)->next)->taskmultimap.begin())->first,((*isc)->taskmultimap.begin())->second));
                    ((*is)->next)->next=(*isc)->next;
                    //taskLin.erase(isc);
                    (*isc)->Num=0;
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
                    (*isc)->Num=0;
                    cout<<"888888888888888888888888888888888888888888888888888888"<<endl;
                }
            }
            isc++;
        }
        is++;
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
        if((*iis)->Num==0) continue;
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
    return 0;
}
