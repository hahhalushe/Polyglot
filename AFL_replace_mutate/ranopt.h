#ifndef _HAVE_RANOPT_H
#define _HAVE_RANOPT_H

#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>
#include<time.h>

#include<iostream>
using namespace std;

#define ODD 0.01//增加/减少的概率
#define N 213;
//定义编译选项结构体
typedef struct o_compile
{
    char compile[50];//编译选项(大小)
    float odds;//编译选项出现的概率
} Compile;
int x = 0;//随机产生的编译选项个数
Compile all_compile[214]; //存放所有的编译选项
Compile ran_compile[214]; //存放随机产生的x个编译选项 
Compile high_compile[214]; //存放概率高的编译选项
Compile low_compile[214]; //存放概率低的编译选项
double acc = 0.0;
int total = 1;
/*从文件中获取编译选项*/
int Read()//函数将文件中的编译选项读取到数组中 
{
	FILE* fpread;
	fpread = fopen("/home/huan/Desktop/P/AFL_replace_mutate/1.txt", "r");
	if (fpread == NULL)//文件不存在
	{
		printf("\nfile is error.\n");
		return -1;
	}
	
	for (int i = 0; i < N; i++)//文件存在将文件中数据读入到数组中 
	{
		fscanf(fpread, "%s",all_compile[i].compile);
		// printf("11\n");
	}
	
	fclose(fpread);//关闭文件 
    
	return 0;
}

void ded(int &b){   //去重  
	if(ran_compile[b].compile == NULL){
		(b)--;
		return;
	}
	for(int i = 0;i < b;i++){
		if(strcmp(ran_compile[i].compile,ran_compile[b].compile) == 0){
			(b)--;
		}
	}
} 

/*返回[left, right]的随机数*/
int randNext(int left, int right)
{
  static unsigned int seed = 0;
  seed++;
  srand((unsigned) time(NULL) + seed * seed);
  return rand() % (right - left + 1) + left;
}

void ranProbability(){ //产生随机化组编译选项，返回一个指向结构体一元数组的指针，即产生的随机化组编译选项

	Read();//函数将文件中的编译选项读取到数组中
	x = randNext(0,N); //随机化产生一个x
	int f = 0;
	int i,j,h,l,k,p; 
	float sum,n,average; //average为概率的平均值,sum为所有编译选项概率的和
	h=0;l=0;sum=0,k = 0;
	
	//概率初始化
	for(i=0,n=1;i<N;i++){
		all_compile[i].odds=n;
		n++;
	}
	
	//从所有编译选项中随机选出X个编译选项: 开始让高概率和低概率相结合，到高概率组的编译选项的个数大于低概率组的个数时，只从高概率组随机选择
	for(j=0; j<N; j++){ //计算出所有编译选项概率(权重)的平均值
		sum=sum + all_compile[j].odds;
	}
	average=sum/(N+1);//概率的平均值

	//以概率平均值为指标，将所有编译选项分为高概率和低概率两组
	for(i=0; i<N; i++){
		if(all_compile[i].odds > average){
			high_compile[h]=all_compile[i];
			// printf("h=%d i=%d high++++++%s  all-----%s\n",h,i,high_compile[h].compile,all_compile[i].compile);
			h++;
		}
		else{
			low_compile[l]=all_compile[i];
			// printf("l=%d i=%d low++++++%s  all-----%s\n",l,i,low_compile[l].compile,all_compile[i].compile);
			l++;
		}
	}
	
	

	if(h<l){//如果高概率组的编译选项的个数小于低概率组的个数，则分别在高概率和低概率两组中随机选择编译选项
		for(k=0; k<x/2; k++){
			if(high_compile[0].compile == NULL){
				printf("high kong\n");
				break;
			}
			f = randNext(0,h-1);
			// ran_compile[k]=high_compile[randNext(0,213)];
			ran_compile[k]=high_compile[f]; 
			// printf("1k = %d, rand = %d\n",k,f);
//			printf("++++++%s-----%s\n",ran_compile[k].compile,"12344333222");
			ded(k);
		}
		if(high_compile[0].compile == NULL){
			k = 0;
		}
//		printf("--k = %d\n",k);
		for(p=k; p<x; p++){
			if(low_compile[0].compile == NULL){
//				printf("lowΪ��\n");
				break;
			}

			f = randNext(0,l-1);
			// ran_compile[p]=low_compile[randNext(0,213)]; 
			ran_compile[p]=low_compile[f];
			// printf(" 2k = %d, rand = %d\n",p,f);
//			printf("ran_[%d]++++++%s-----%s\n",p,ran_compile[p].compile,"12344333222");
			ded(p);
		}
	}
	else{//如果高概率组的编译选项的个数大于低概率组的个数，只在高概率组中选择x个编译选项
		for(k=0; k<x; k++){
			if(high_compile[0].compile == NULL){
				break;
			}

			f = randNext(0,N);
			// ran_compile[k]=high_compile[randNext(0,213)]; 
			ran_compile[k]=high_compile[f];
			// printf(" 3k = %d, rand = %d\n",k,f);

			ded(k);
		}
	}
}

/*当触发新的覆盖，调整权重*/
void add_opt() { 

	float n = ODD;
		for(int i = 0;i < x;i++){
				ran_compile[i].odds += n;  //n是增加的概率
		}
	for(int j = 0;j < x;j++){
		for(int i = 0;i < N;i++){
			if(strcmp(all_compile[i].compile,ran_compile[j].compile) == 0)	{
				all_compile[i].odds = ran_compile[j].odds;
			}
		}
	}	
} 
/*减少相应权重*/
void de_opt(){   
	float s = ODD;
	for(int i = 0;i < x;i++){
			ran_compile[i].odds -= s;  
	}
	for(int j = 0;j < x;j++){
		for(int i = 0;i < N;i++){ 
			if(strcmp(all_compile[i].compile,ran_compile[j].compile) == 0)	{
				all_compile[i].odds = ran_compile[j].odds;
			}
		}
	}	
}

/*Incorporate strings into parameters*/
char** add(int x,char** argv0){
	/*make dis*/
	/*初始化*/
	char** p =  argv0;
	char** p_argv;
	int m = 0;
	int d = 0;
	/*计算argv0数组元素个数*/
	while(*p != NULL){
		m++;
		p++;	
	}
/*分配内存*/
	p = (char**)realloc(p_argv,sizeof(char*)*(x+m+1));
	if(p == NULL){  
		printf("add error\n");
		return p;
	}
	p_argv = p;
	/*Allocate memory*/
	for(int i = 0;i < (x+m);i++){
		p_argv[i] = (char*)malloc(sizeof(char)*60);
	}
	p = argv0;
/*add 3*/
/*将argv0数组中的元素传给p_argv*/
	while(*p != '\0'){
		p_argv[d] = *p; 
		d++;
		p = p + 1;
	}
/*将随机选出的编译选项传给p_argv*/
	for (int i = m; i < (x+m); i++)
	{
		/* code */

		p_argv[i] = ran_compile[i-m].compile;

	}
	/*x是随机产生编译选项的个数，m是argv0数组元素个数*/
	printf("-------------over---------       x=%d m=%d x+m=%d\n",x,m,x+m);
	p_argv[x+m] = NULL;
	p = p_argv;
	m = 0;
	/*打印p_argv数组中的元素*/
	while(*p != NULL){
		printf("pp = %s\n",p_argv[m]);
		m++;
		p++;
	}
	return p_argv;
	
}



#endif /*! _HAVE_RANOPT_H*/