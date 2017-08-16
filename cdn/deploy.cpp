#include "deploy.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>



using namespace std;

#define netnodeMaxNum 1000
#define consumerMaxNum 500
#define INFINITY  100000
//dshfjhkdsfjksdfjkdfs
//------testing-----------github--------
//--------------------------------------------------------------------stack------------------------------------------------------------------------------
typedef struct SNode *myStack;
struct SNode{
int  *data;
int top;
int maxSize;
};
myStack create_stack(int maxSize)
{
    myStack s=(myStack)malloc(sizeof(struct SNode));
    s->data=(int *)malloc(maxSize*sizeof(int));
    s->top=-1;
    s->maxSize=maxSize;
    return s;
}
void push(myStack s,int x)
{
    s->data[++(s->top)]=x;
}
bool is_empty_stack(myStack s)
{
    return (s->top==-1);
}
int pop(myStack s)
{
    return (s->data[s->top--]);
}
//--------------------------------------------------------------------stack------------------------------------------------------------------------------

//-------------------------------------------------------------------------Graph define-------------------------------------------------------------------
typedef struct ENode *Edge;
struct ENode{
    int netIndex1,netIndex2;
    int bpsMax;
    int costPerGB;
};

typedef struct consumer_Flag{
    int need;
    int netnodeIndex;
}cF[consumerMaxNum];

typedef struct GNode *MGraph;
struct GNode{
    int vertexNum;
    int edgeNum;
    int Gcost[netnodeMaxNum][netnodeMaxNum];
    int Gbps[netnodeMaxNum][netnodeMaxNum];
 //   int consumerFlag[consumerMaxNum]
    cF consumerFlag;
};

typedef struct AdjNode *PTnetnode;
struct AdjNode{
    int costPerGB;
    int bpsMax;
    PTnetnode next;
};

MGraph creat_graph(int vertex_Num)
{
    int i,j;
    MGraph graph=NULL;

    graph=(MGraph)malloc(sizeof(struct GNode));
    graph->vertexNum=vertex_Num;
    graph->edgeNum=0;
    for(i=0;i<graph->vertexNum;i++)
    {
        for(j=0;j<graph->vertexNum;j++)
        {
			graph->Gcost[i][j]=INFINITY;
			graph->Gbps[i][j]=0;

        }
    }
    return graph;
}

void insert_edge(MGraph graph,Edge e)
{
    graph->Gcost[e->netIndex1][e->netIndex2]=e->costPerGB;
    graph->Gcost[e->netIndex2][e->netIndex1]=e->costPerGB;

    graph->Gbps[e->netIndex1][e->netIndex2]=e->bpsMax;
    graph->Gbps[e->netIndex2][e->netIndex1]=e->bpsMax;
}
//-------------------------------------------------------------------------Graph define-------------------------------------------------------------------

//-------------------------------------------------------------------increasing list------------------------------------------------------------------------
PTnetnode insert_list(PTnetnode head,PTnetnode newone)
{
    PTnetnode temp=head;
    PTnetnode pre=head;

        if( newone->costPerGB < head->costPerGB)
        {
            newone->next=head;
            head=newone;
            return head;
        }
        else
        {
            temp=head->next;
            while(temp!=NULL)
            {
                if( newone->costPerGB < temp->costPerGB)
                {
                    newone->next=temp;
                    pre->next=newone;
                    return head;
                }
                else
                {
                    temp=temp->next;
                    pre=pre->next;
                }
            }
            pre->next=newone;
            return head;

        }

}
void delete_list(PTnetnode head)
{
    PTnetnode temp=head;
    while(head!=NULL)
    {
        temp=head;
        head=head->next;
        free(temp);
    }
}
//-------------------------------------------------------------------------------increasing list------------------------------------------------------------------------------
int find_consumerIndexConnected_netnoed(cF consumerFlag,int netnode)
{
    int tempIndex=-1;
    for(int i=0;i<consumerMaxNum;i++)
    {
        if(consumerFlag[i].netnodeIndex==netnode)
        {
            tempIndex=i;
            break;
        }
    }
    return tempIndex;
}

bool is_all_satisfied(bool satisfied[],int consumerNum)
{
    bool temp=true;
    for(int i=0;i<consumerNum;i++)
    {
        if(satisfied[i]==false)
        {
            temp=false;
        }
    }
    return temp;
}
bool is_no_path(bool satisfied[],int dist[][netnodeMaxNum],int consumerNum,int videoPos[],int serverNum,MGraph graph)
{
 //   bool temp,t;
 //   int flag=0;
 //printf("is no path func is 22 ------->21 dist %d\n",dist[22][21]);
    int j;
    for(int i=0;i<consumerNum;i++)
    {
 //   flag=0;
 //       temp=true;
        if(!satisfied[i])
        {
            for(j=0;j<serverNum;j++)
            {
     //           printf("is no path func is %d -------------------------> %d dist is %d\n",videoPos[j], graph->consumerFlag[i].netnodeIndex, dist[videoPos[j]][graph->consumerFlag[i].netnodeIndex]);

                if(dist[videoPos[j]][graph->consumerFlag[i].netnodeIndex]<INFINITY)
                {//temp=false;
//                printf("dist is %d\n",dist[videoPos[j]][graph->consumerFlag[i].netnodeIndex]);
                return false;
                }
            }
            /*
            if(flag==0)
            {t=temp;}
            else
            {t=t||temp;
            flag=1;}
*/
        }
    }
    return true;
}

int find_min_dist(MGraph graph,int dist[],bool collected[])
{
    int minV,v;
    v=0;
    minV=0;
    int minDist=INFINITY;

    for(v=0;v<graph->vertexNum;v++)
    {
        if(collected[v]==false && dist[v]<minDist)
        {
            minDist=dist[v];
            minV=v;
        }
    }
    if(minDist<INFINITY)
    {
        return minV;
    }
    else
    {
        return -1;
    }
}
void dijkstra(MGraph graph,int dist[],int path[],int s)
{
    bool collected[netnodeMaxNum];
    int v,w;
    for(v=0;v<graph->vertexNum;v++)
    {
        collected[v]=false;
        dist[v]=graph->Gcost[s][v];
        if(dist[v]<INFINITY)
        {
            path[v]=s;
        }
        else
        {
            path[v]=-1;
        }
    }
    dist[s]=0;
    collected[s]=true;
    while(true)
    {
        v=find_min_dist(graph,dist,collected);
        if(v==-1)//not find min;break
        {
            break;
        }
        collected[v]=true;
        for(w=0;w<graph->vertexNum;w++)
        {
            if(collected[w]==false && graph->Gcost[v][w]<INFINITY)
            {
                if(dist[v]+graph->Gcost[v][w]<dist[w])
                {
                    dist[w]=dist[v]+graph->Gcost[v][w];
                    path[w]=v;
                }
            }
        }
    }
  //  return true;
}
int get_flows(int residue[][netnodeMaxNum],int path[][netnodeMaxNum],int videoPos,int consumerPos,myStack s,int dist[][netnodeMaxNum])
{
    push(s,consumerPos);

    int pre,next,flowMin,temp;
     pre=path[videoPos][consumerPos];
     next=consumerPos;
     flowMin=residue[pre][next];
     push(s,pre);

    while( pre!=videoPos){
     next=pre;
     pre=path[videoPos][next];
     temp=residue[pre][next];
//if(temp==0){dist[pre][next]=INFINITY;}
     push(s,pre);
     if(temp<flowMin)
     {
        flowMin=temp;
     }
    }
  //  printf("folws min is %d\n",flowMin);
    return flowMin;
}

//---------------------------------------------------------------------------------MinHeap-------------------------------------------------------------------------------
typedef struct distNode{
int dist;
int serverPos;
int consumerPos;
}distEle;
typedef struct HNode *minHeap;
struct HNode{
distEle *data;
int num;
int capacity;
};

minHeap creat_heap(int maxSize)
{
    minHeap h=(minHeap)malloc(sizeof(struct HNode));
    h->data=(distEle *)malloc((maxSize+1)*sizeof(distEle));
    h->num=0;
    h->capacity=maxSize;
    h->data[0].dist=-1;
    return h;
}
bool is_full(minHeap h)
{
    return (h->num==h->capacity);
}
void insert_heap(minHeap h,distEle x)
{
  //  printf("function insert is %d %d %d\n",x.serverPos,x.consumerPos,x.dist);
    int i;
    h->num++;
    i=h->num;
    for(;h->data[i/2].dist>x.dist;i/=2)
    {
        h->data[i]=h->data[i/2];
    }
    h->data[i]=x;
  //  printf("function data is %d %d %d\n",h->data[i].serverPos,h->data[i].consumerPos,h->data[i].dist);
}
bool is_empty_heap(minHeap h)
{
    return (h->num==0);
}
distEle delete_min(minHeap h)
{
    int parent,child;
    distEle minItem,x;
    minItem=h->data[1];
    x=h->data[h->num];
    h->num--;
    for(parent=1;parent*2<=h->num;parent=child)
    {
        child=parent*2;
        if((child!=h->num)  && (h->data[child].dist>h->data[child+1].dist))
        {
            child++;
        }
        if(x.dist<=h->data[child].dist)
        {break;}
        else
        {
            h->data[parent]=h->data[child];
        }
    }
    h->data[parent]=x;
  //  printf("minDist is %d %d %d\n",minItem.serverPos,minItem.consumerPos,minItem.dist);
    return minItem;
}
//---------------------------------------------------------------------------------MinHeap-------------------------------------------------------------------------------
void handler()
{
    printf("exit\n");
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//你要完成的功能总入口
void deploy_server(char * topo[MAX_EDGE_NUM], int line_num,char * filename)
{
	int consumerNum=0;
	int netnodeNum=0;
	int edgeNum=0;
	int videonetCost=0;
	int netIndex1=0;
	int netIndex2=0;
	int bps=0;
	int costPerGB=0;
	int need=0;
	char *c=NULL;
	int spaceCount=0;
	int netnode=0;
	int netnodeBpsSum,netnodeCostSum=0;
	int i,j=0;
 //   int consumerIndex=0;
    int videoServerNum=0;
    int bpsCount=0;
    int serverPos=0;
    int consumerPos=0;
    int offset=0;
    int flowsNum=0;
    PTnetnode nodePointer=NULL;
    PTnetnode newNode=NULL;
    PTnetnode temp=NULL;
    minHeap h=NULL;
	c=topo[0];
    int flowsGB=0;
    int sumCost=0;
int flowsNumMin;
    static int netnodeToConsumer[netnodeMaxNum];
    for(i=0;i<netnodeMaxNum;i++)
    {
        netnodeToConsumer[i]=-1;
    }
    static int videonetPosition[consumerMaxNum];
    for(i=0;i<consumerMaxNum;i++)
    {
        videonetPosition[i]=-1;
    }
    static bool satisfied[consumerMaxNum];
    for(i=0;i<consumerMaxNum;i++)
    {
        satisfied[i]=false;
    }
    static char a[10000];
    sprintf(a,"\n\n");
    string res=a;
    string resHead;

   static int residueGB[netnodeMaxNum][netnodeMaxNum];
   for(i=0;i<netnodeMaxNum;i++){residueGB[i][i]=INFINITY;}
   static int path[netnodeMaxNum][netnodeMaxNum];
   static int dist[netnodeMaxNum][netnodeMaxNum];

    //static int needed[consumerMaxNum];
//----------------------------------------------------------read data   ;   build graph-------------------------------------------------------------------------------------
	while(*c !='\0' && *c!='\n' && *c!='\r')
	{
        if(*c==' ')
        {
            c++;
            spaceCount++;
            continue;
        }
        if(spaceCount==0)
        {
            netnodeNum=*c-'0'+netnodeNum*10;
        }
        else if(spaceCount==1)
        {
            edgeNum=*c-'0'+edgeNum*10;
        }
        else if(spaceCount==2)
        {
            consumerNum = *c - '0' + consumerNum * 10;
        }
        c++;
	}

	MGraph graph=creat_graph(netnodeNum);
	Edge etemp=(Edge)malloc(sizeof(struct ENode));
//	int G[netnodeNum];
//printf("netnodeNum is :%d edgeNum is %d sonsumerNum is %d\n",netnodeNum,edgeNum,consumerNum);//test the read
	c=topo[2];
	while(*c!='\0' && *c!='\n' && *c!='\r')
	{
        videonetCost=*c-'0'+videonetCost*10;
        c++;
	}
	//printf("videonetCost is : %d\n",videonetCost);//test the read

	for(i=4;i<4+edgeNum;i++)
	{
		c=topo[i];
        spaceCount=0;
        netIndex1=0;
        netIndex2=0;
        bps=0;
        costPerGB=0;
        while(*c !='\0' && *c!='\n' && *c!='\r')
	{
        if(*c==' ')
        {
            c++;
            spaceCount++;
            continue;
        }
        if(spaceCount==0)
        {
            netIndex1=*c-'0'+netIndex1*10;
        }
        else if(spaceCount==1)
        {
            netIndex2=*c-'0'+netIndex2*10;
        }
        else if(spaceCount==2)
        {
            bps = *c - '0' + bps * 10;
        }
        else if(spaceCount==3)
        {
            costPerGB = *c - '0' + costPerGB * 10;
        }
        c++;
	}
//printf("net1 is :%d net2 is %d bps is: %d costPerGB is:%d\n",netIndex1,netIndex2,bps,costPerGB);//test the read
    etemp->netIndex1=netIndex1;
    etemp->netIndex2=netIndex2;
    etemp->bpsMax=bps;
    etemp->costPerGB=costPerGB;
    insert_edge(graph,etemp);

    residueGB[netIndex1][netIndex2]=bps;
    residueGB[netIndex2][netIndex1]=bps;


	}

	free(etemp);
	//free(graph);


	for(i=1;i<consumerNum+1;i++)
	{
        c=topo[line_num-i];
        spaceCount=0;
        netIndex1=0;
        netIndex2=0;
        need=0;
        while(*c !='\0' && *c!='\n' && *c!='\r')
	{
        if(*c==' ')
        {
            c++;
            spaceCount++;
            continue;
        }
        if(spaceCount==0)
        {
            netIndex1=*c-'0'+netIndex1*10;
        }
        else if(spaceCount==1)
        {
            netIndex2=*c-'0'+netIndex2*10;
        }
        else if(spaceCount==2)
        {
            need = *c - '0' + need * 10;
        }
        c++;
	}
//printf("net1 is: %d net2 is %d need is %d\n",netIndex1,netIndex2,need);//test the read

//the index of comsumerFlag is the comsumerNum; store the index of the connected netnode and the video need
    graph->consumerFlag[netIndex1].need=need;
   // needed[i]=need;
    graph->consumerFlag[netIndex1].netnodeIndex=netIndex2;
    netnodeToConsumer[netIndex2]=netIndex1;//index is netnode;store is connected consumer
	}

	//----------------------------------------------------------read data   ;   build graph-------------------------------------------------------------------------------------


    nodePointer=(PTnetnode)malloc(sizeof(struct AdjNode));



//---------------------------------------------------------------find the consumer should connected with netnode directly-------------------------------------------------
    for(i=0;i<consumerNum;i++)
    {
        bpsCount=0;
        netnodeBpsSum=0;
        netnodeCostSum=0;
        need=graph->consumerFlag[i].need;
        netIndex1=graph->consumerFlag[i].netnodeIndex;
        for(j=0;j<netnodeNum;j++)
        {
        if(j==0)
        {
            nodePointer->costPerGB=graph->Gcost[netIndex1][j];
            nodePointer->bpsMax=graph->Gbps[netIndex1][j];
            nodePointer->next=NULL;
        }
        else
        {
            newNode=(PTnetnode)malloc(sizeof(struct AdjNode));
            newNode->costPerGB=graph->Gcost[netIndex1][j];
            newNode->bpsMax=graph->Gbps[netIndex1][j];
            newNode->next=NULL;
            nodePointer=insert_list(nodePointer,newNode);
        }
            netnodeBpsSum+=graph->Gbps[netIndex1][j];

        }


        if(netnodeBpsSum<need)//put a video server connected with comsumer directly
        {
            videonetPosition[videoServerNum]=netIndex1;
            videoServerNum++;
            satisfied[i]=true;
            graph->consumerFlag[i].need=0;
            sprintf(a,"%d %d %d",netIndex1,i,need);
            flowsNum++;
            res+=a;
            if(!is_all_satisfied(satisfied,consumerNum))
            {
                res+="\n";
            }

        }
        else
        {
            temp=nodePointer;
            while(bpsCount<need && temp!=NULL)
            {
                if(temp->bpsMax < need-bpsCount)
                {
                     bpsCount+=temp->bpsMax;
                     netnodeCostSum+=temp->costPerGB * temp->bpsMax;
                     temp=temp->next;
                }
                else
                {
                    netnodeCostSum+=temp->costPerGB * (need-bpsCount);
                    bpsCount=need;

                }

            }
            if(netnodeCostSum>videonetCost)
            {
                videonetPosition[videoServerNum]=netIndex1;
                videoServerNum++;
                satisfied[i]=true;
      //          needed[i]=0;
                graph->consumerFlag[i].need=0;
                sprintf(a,"%d %d %d",netIndex1,i,need);
                flowsNum++;
                res+=a;
                if(!is_all_satisfied(satisfied,consumerNum))
                {
                    res+="\n";
                }
            }
        }

        newNode=nodePointer->next;
        nodePointer->next=NULL;
        delete_list(newNode);
    }
    //---------------------------------------------------------------find the consumer should connected with netnode directly-------------------------------------------------
//test add some server try 20 12 22 37 15 48 26
/*
videonetPosition[videoServerNum++]=20;
videonetPosition[videoServerNum++]=37;
videonetPosition[videoServerNum++]=15;
videonetPosition[videoServerNum++]=48;
videonetPosition[videoServerNum++]=26;
videonetPosition[videoServerNum++]=22;
*/
//test add some server try


        delete_list(nodePointer);

        myStack s=create_stack(netnodeNum);
        h=creat_heap(netnodeMaxNum*consumerNum);
        distEle tempDist;
        distEle x;
        int tempPos,tempPre;
        tempPos=0;
        bool allSatisfied=false;
        bool noPath=false;
		string resOut=res;
		string tempString;

		//--------------------------------rand--------------------------------------------------------------------------
		static int tempRes[netnodeMaxNum][netnodeMaxNum];
		static int tempGcost[netnodeMaxNum][netnodeMaxNum];
		static bool tempSatisfied[consumerMaxNum];
		static int tempNeed[consumerMaxNum];
		for(i=0;i<netnodeNum;i++)
		{
			for(j=0;j<netnodeNum;j++)
			{
				tempRes[i][j]=residueGB[i][j];
				tempGcost[i][j]=graph->Gcost[i][j];
			}
		}
		for(i=0;i<consumerNum;i++)
		{
            tempSatisfied[i]=satisfied[i];
            tempNeed[i]=graph->consumerFlag[i].need;
		}
	//	alarm(9);
	//	    signal(SIGALRM, handler);
   // alarm(90);
		int temp_bool,timeLeft;
		bool videoPosFlag[netnodeMaxNum];
		bool firstRand=true;
		int sumCostMin=100000;
		int tempSerNum=videoServerNum;
		int tempFlowsNum=flowsNum;
		int loopCount=0;

			srand((unsigned)time(NULL));

clock_t start = clock();

		//-------------------------------------------------rand loop-----------------------------------------------------------------------
		do{
loopCount++;
		sumCost=0;
            h->num=0;
			flowsNum=tempFlowsNum;
			videoServerNum=tempSerNum;
			res=resOut;
			for(i=0;i<netnodeNum;i++)
			{
				for(j=0;j<netnodeNum;j++)
				{
					residueGB[i][j]=tempRes[i][j];
					graph->Gcost[i][j]=tempGcost[i][j];
				}
			}
			for(i=0;i<consumerNum;i++)
            {
                satisfied[i]=tempSatisfied[i];
                graph->consumerFlag[i].need=tempNeed[i];
            }

   // signal(SIGALRM, handler);
  //  alarm(5);
  /*
  if(loopCount==9)
  {
  //break;
  			srand((unsigned)time(NULL));

            timeLeft = alarm(0);
	//		printf("time left is %d\n",timeLeft);
			if(timeLeft<10){break;}
			alarm(timeLeft);
			loopCount=0;
  }
*/


			for(i=0;i<netnodeNum-videoServerNum;i++)
			{
				temp_bool=rand()%2;
				videoPosFlag[i]=temp_bool?true:false;

			}
/*			for(i=0;i<videoServerNum;i++)
			{
				videoPosFlag[videonetPosition[i]]=true;
			}*/
//			videoServerNum=0;
			for(i=0;i<netnodeNum-videoServerNum;i++)
			{
				if(videoPosFlag[i])
				{
					videonetPosition[videoServerNum++]=i;
				}
			}





while(true)
{

//printf("waicheng ==============\n");
    //----------------------------------------------------------------dijkstra------------------------------------------------------------------------------------
        for(i=0;i<videoServerNum;i++)
        {
            serverPos=videonetPosition[i];//server position
            dijkstra(graph,dist[serverPos],path[serverPos],serverPos);
        }

            allSatisfied=is_all_satisfied(satisfied,consumerNum);
            noPath=is_no_path(satisfied,dist,consumerNum,videonetPosition,videoServerNum,graph);

    if(allSatisfied)
    {
  //  printf("satisfied\n");
    break;
    }
    if(noPath)
    {
    //    printf("unsatisfied\n");
        break;
    }


        for(i=0;i<videoServerNum;i++)
        {
  //      printf("insert heap loop is %d\n",i);
            serverPos=videonetPosition[i];
            for(j=0;j<consumerNum;j++)
            {
                if(!satisfied[j])
                {
                    consumerPos=graph->consumerFlag[j].netnodeIndex;
                    if(dist[serverPos][consumerPos]<INFINITY)
                    {
                        tempDist.consumerPos=consumerPos;
                        tempDist.dist=dist[serverPos][consumerPos];
                        tempDist.serverPos=serverPos;
                        insert_heap(h,tempDist);
        //                printf("insert is %d %d %d\n",serverPos,consumerPos,dist[serverPos][consumerPos]);
      //                  flowsGB=get_flows(residueGB,path,serverPos,consumerPos);
                    }
                }
            }
        }


    //    i=0;
        while(true)
        {
            if(is_empty_heap(h)){break;}
            x=delete_min(h);
  //          printf("min dist is%d %d %d\n",x.serverPos,x.consumerPos,x.dist);
            i=0;
            offset=0;
            if(!satisfied[ netnodeToConsumer[x.consumerPos] ])
            {

            //directly connect
            if(x.serverPos==x.consumerPos)//directly connect
            {
                j=netnodeToConsumer[x.consumerPos];
                sprintf(a,"%d %d %d",x.serverPos,j,graph->consumerFlag[j].need);
                graph->consumerFlag[j].need=0;
                satisfied[j]=true;
                res+=a;
                flowsNum++;
                if(!is_all_satisfied(satisfied,consumerNum))
                {
                    res+="\n";
                    continue;
                }
                else
                {break;}
     //           while(!is_empty_stack(s))
       //         {tempPos=pop(s);}

            }
            //directly connect

                flowsGB=get_flows(residueGB,path,x.serverPos,x.consumerPos,s,dist);
                need=graph->consumerFlag[ netnodeToConsumer[x.consumerPos] ].need;
 //              printf("flowsGB is :%d %d\n",flowsGB,need);
                if(flowsGB>=need)
                {
                i=0;
                    while(!is_empty_stack(s))
                    {
                        i++;
                        tempPre=tempPos;
                        tempPos=pop(s);
                        offset+=sprintf(a+offset,"%d ",tempPos);
                        if(i!=1){
                        residueGB[tempPre][tempPos]-=need;

                        if(residueGB[tempPre][tempPos]==0){graph->Gcost[tempPre][tempPos]=INFINITY;}
                        }
                    }
                    sumCost+=need*dist[x.serverPos][x.consumerPos];
                    tempPos=netnodeToConsumer[x.consumerPos];
                    satisfied[tempPos]=true;
                    graph->consumerFlag[tempPos].need=0;
  //                  printf("------------------------------------------------need is %d\n",need);

                    offset+=sprintf(a+offset,"%d ",tempPos);
                    offset+=sprintf(a+offset,"%d",need);
                    res+=a;
                    flowsNum++;
                    if(!is_all_satisfied(satisfied,consumerNum))
                    {
                    res+="\n";
                    }
                    else
                    {break;}

            }
            else if(flowsGB>0)
            {
            i=0;
                    while(!is_empty_stack(s))
                    {
                        i++;
                        tempPre=tempPos;
                        tempPos=pop(s);
                        offset+=sprintf(a+offset,"%d ",tempPos);
                        if(i!=1){
                        residueGB[tempPre][tempPos]-=flowsGB;
                        if(residueGB[tempPre][tempPos]==0){graph->Gcost[tempPre][tempPos]=INFINITY;}
                        }
                    }
                    sumCost+=flowsGB*dist[x.serverPos][x.consumerPos];
                    tempPos=netnodeToConsumer[x.consumerPos];
     //               needed[tempPos]-=flowsGB;
                    graph->consumerFlag[tempPos].need-=flowsGB;
                    if(graph->consumerFlag[tempPos].need==0){satisfied[tempPos]=true;}
//printf("------------------------------------------------flows is %d\n",flowsGB);
                    offset+=sprintf(a+offset,"%d ",tempPos);
                    offset+=sprintf(a+offset,"%d",flowsGB);
                    res+=a;
                    flowsNum++;
                    if(!is_all_satisfied(satisfied,consumerNum))
                    {
                    res+="\n";
                    }
                    else{break;}
            }
            else
            {
                while(!is_empty_stack(s))
                {tempPos=pop(s);
                  //  printf("pop is %d\n",tempPos);
                }
            }

            }


        }

}


 sumCost+=videoServerNum*videonetCost;
//printf("sum cost is %d\n",sumCost);

if(firstRand && allSatisfied)
{
	sumCostMin=sumCost;
	tempString=res;
	firstRand=false;
	flowsNumMin=flowsNum;
}
else
{
	if(sumCost<sumCostMin && allSatisfied)
	{
		tempString=res;
		sumCostMin=sumCost;
		flowsNumMin=flowsNum;
	}
}



		}while((clock()-start)  < 80*CLOCKS_PER_SEC);
/*
//test
for(j=0;j<videoServerNum;j++){
printf("%d\n\n",videonetPosition[j]);
    for(i=0;i<netnodeNum;i++)
    {
        printf("%d %d\n",dist[videonetPosition[j]][i],path[videonetPosition[j]][i]);
    }
}
//test
*/
 free(graph);
         free(s->data);
         free(s);
         free(h->data);
         free(h);



 //sumCost+=videoServerNum*videonetCost;
//printf("min sum cost is %d\n",sumCostMin);
//printf("loop times is %d\n",loopCount);


//printf("the directy connect is %d %d %d\n",videonetPosition[0],videonetPosition[1],videonetPosition[2]);
//printf("video server num is :%d\n",videoServerNum);

	// 需要输出的内容
	if(firstRand)
	{
	sprintf(a, "%d\n\n",consumerNum);
    res = a;
        for (i = 1; i < consumerNum+1; i++)
    {
        c = topo[line_num-i];
        netnode = need = spaceCount = 0;
        while (*c != '\0' && *c != '\n' && *c != '\r')
        {
            if (*c == ' ')
            {
                c++;
                spaceCount++;
                continue;
            }
            if (spaceCount == 1)
            {
                netnode = *c - '0' + netnode * 10;
            }
            else if (spaceCount == 2)
            {
                need = *c - '0' + need * 10;
            }
            c++;
        }
        sprintf(a, "%d %d %d",netnode,consumerNum-i,need);
        res += a;
        if (i != consumerNum)
        {
            res += "\n";
        }
    }

	}
	else
	{
        sprintf(a,"%d",flowsNumMin);
        resHead=a;
        res=resHead+tempString;
	}


	char * topo_file=(char *)res.c_str();

	// 直接调用输出文件的方法输出到指定文件中(ps请注意格式的正确性，如果有解，第一行只有一个数据；第二行为空；第三行开始才是具体的数据，数据之间用一个空格分隔开)
	write_result(topo_file, filename);

}
