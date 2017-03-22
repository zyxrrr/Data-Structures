#include "deploy.h"
#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <iostream>

using namespace std;

#define netnodeMaxNum 1000
#define consumerMaxNum 500
#define INFINITY  100000
//Graph define
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
            graph->Gbps[i][j]=INFINITY;
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
	c=topo[0];

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

	for(int i=4;i<4+edgeNum;i++)
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

	}

	free(etemp);
	//free(graph);


	for(int i=1;i<consumerNum+1;i++)
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
    graph->consumerFlag[netIndex1].netnodeIndex=netIndex2;
	}


    free(graph);


	// 需要输出的内容
	char * topo_file = (char *)"17\n\n0 8 0 20\n21 8 0 20\n9 11 1 13\n21 22 2 20\n23 22 2 8\n1 3 3 11\n24 3 3 17\n27 3 3 26\n24 3 3 10\n18 17 4 11\n1 19 5 26\n1 16 6 15\n15 13 7 13\n4 5 8 18\n2 25 9 15\n0 7 10 10\n23 24 11 23";

	// 直接调用输出文件的方法输出到指定文件中(ps请注意格式的正确性，如果有解，第一行只有一个数据；第二行为空；第三行开始才是具体的数据，数据之间用一个空格分隔开)
	write_result(topo_file, filename);

}
