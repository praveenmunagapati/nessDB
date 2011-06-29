#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "vm.h"
#include "lru.h"
#include "debug.h"

static int LOOP=5;

void vm_init_test(int lru)
{
	vm_init(lru);
	INFO("---init---");
}

void vm_load_data_test()
{
	double cost;
	clock_t begin,end;
	begin=clock();
	vm_load_data();
	end=clock();
	cost=(double)(end-begin);
	printf("---load cost:%lf\n",cost);
}

void vm_put_test()
{
	int i;
	double cost;
	clock_t begin,end;
	begin=clock();
	char key[256]="key1";
	char value[256]="val1";

	for(i=0;i<LOOP;i++)
	{
		LOG("%d",i);
		sprintf(key,"%dxxxxxxxxxx",i);
		sprintf(value,"%dxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",i);
		vm_put(key,value);
	}
	end=clock();
	cost=(double)(end-begin);
	printf("---put cost:%lf\n",cost);
	INFO("---vm put ---");
	
}

	

void vm_get_test()
{
	double cost;
	char key[256]="xxxxxxxxxxxxxxxxx2";
	char value[256]={0};
	int i;
	clock_t begin,end;
	begin=clock();
	for(i=1;i<LOOP;i++)
	{
		sprintf(key,"%dxxxxxxxxxx",rand()%i);
		int  ret=vm_get(key,value);
		if(ret)
			LOG("v is:%s----%s",key,value);
		else
			INFO("nofound!");
	}
	end=clock();
    cost=(double)(end-begin);
	printf("get cost:%lf\n",cost);
}


int main(int argc,char**argv)
{
	int lru=0;
	if(argc!=4)
	{
		printf("arg error,format--->loopcount opt lru...\n");
		return 1;
	}
	LOOP=atoi(argv[1]);

	if(strcmp(argv[3],"lru")==0)
		lru=1;

	vm_init_test(lru);

	if(strcmp(argv[2],"put")==0)
		vm_put_test();

	if(strcmp(argv[2],"load")==0)
		vm_load_data_test();

	vm_get_test();
	return (1);
}
