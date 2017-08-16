#include<stdio.h>
#include<stdlib.h>
#define MaxSize 10000
typedef int ElementType;
typedef int SetName;
typedef ElementType SetType[MaxSize];

SetName Find(SetType S, ElementType X){
	for (; S[X] >= 0; X = S[X]);
	return X;
}

void Union(SetType S, SetName Root1, SetName Root2){
//	S[Root2] = Root1;	
	if (S[Root2] < S[Root1]){
		S[Root2] += S[Root1];
		S[Root1] = Root2;
	}
	else
	{
		S[Root1] += S[Root2];
		S[Root2] = Root1;
	}
}

void Initialization(SetType S){
	for (int i = 0; i < MaxSize; i++){
		S[i] = -1;
	}
}

void Input_connection(SetType S){
	ElementType u, v;
	SetName root1, root2;
	scanf("%d %d\n", &u, &v);
	root1 = Find(S, u - 1);
	root2 = Find(S, v - 1);
	if (root1!=root2)
	{
		Union(S, root1, root2);
	}
}

void Check_connection(SetType S){
	ElementType u, v;
	SetName root1, root2;
	scanf("%d %d\n", &u, &v);
	root1 = Find(S, u - 1);
	root2 = Find(S, v - 1);
	if (root1==root2)
	{
		printf("yes\n");
	}
	else
	{
		printf("no\n");
	}
}

void Check_network(SetType S, int n){
	int i, count = 0;
	for (i = 0; i < n; i++){
		if (S[i] < 0)
			count++;

	}
	if (count==1)
	{
		printf("The network is connected.\n");
	}
	else
	{
		printf("There are %d components.\n", count);
	}
}


int main(){
	SetType S;
	int n;
	char in;
	scanf("%d\n", &n);
	Initialization(S);
	do{
		scanf("%c", &in);
		switch (in)
		{
		case 'I':Input_connection(S); break;
		case 'C':Check_connection(S); break;
		case 'S':Check_network(S, n); break;
		}
	} while (in != 'S');
	return 0;
}