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

/*以下为所有的编译选项*/
char str[][50] = {"-faggressive-loop-optimizations","-falign-functions","-falign-jumps","-falign-labels","-falign-loops","-fassociative-math","-fasynchronous-unwind-tables","-fauto-inc-dec","-fbranch-count-reg","-fbranch-probabilities",
"-fbranch-target-load-optimize","-fbranch-target-load-optimize2","-fbtr-bb-exclusive","-fcaller-saves","-fcode-hoisting","-fcombine-stack-adjustments","-fcompare-elim","-fconserve-stack","-fcprop-registers","-fcrossjumping",
"-fcse-follow-jumps","-fcx-fortran-rules","-fcx-limited-range","-fdce","-fdefer-pop","-fdelayed-branch","-fdelete-dead-exceptions","-fdelete-null-pointer-checks","-fdevirtualize","-fdevirtualize-speculatively",
"-fdse","-fearly-inlining","-fexceptions","-fexpensive-optimizations","-ffinite-math-only","-ffloat-store","-fforward-propagate","-ffp-int-builtin-inexact","-ffunction-cse","-fgcse",
"-fgcse-after-reload","-fgcse-las","-fgcse-lm","-fgcse-sm","-fgraphite","-fgraphite-identity","-fguess-branch-probability","-fhoist-adjacent-loads","-fif-conversion","-fif-conversion2",
"-findirect-inlining","-finline","-finline-atomics","-finline-functions","-finline-functions-called-once","-finline-small-functions","-fipa-bit-cp","-fipa-cp","-fipa-cp-clone","-fipa-icf",
"-fipa-icf-functions","-fipa-icf-variables","-fipa-profile","-fipa-pta","-fipa-pure-const","-fipa-ra","-fipa-reference","-fipa-sra","-fipa-vrp","-fira-hoist-pressure",
"-fira-loop-pressure","-fira-region=[one|all|mixed][default]","-fira-share-save-slots","-fira-share-spill-slots","-fisolate-erroneous-paths-attribute","-fisolate-erroneous-paths-dereference","-fivopts","-fjump-tables","-fkeep-gc-roots-live","-flifetime-dse",
"-flimit-function-alignment","-flive-range-shrinkage","-floop-nest-optimize","-floop-parallelize-all","-flra-remat","-fmath-errno","-fmodulo-sched","-fmodulo-sched-allow-regmoves","-fmove-loop-invariants","-fnon-call-exceptions",
"-fnothrow-opt","-fomit-frame-pointer","-fopt-info","-foptimize-sibling-calls","-foptimize-strlen","-fpack-struct","-fpartial-inlining","-fpeel-loops","-fpeephole","-fpeephole2",
"-fplt","-fpredictive-commoning","-fprefetch-loop-arrays","-fprintf-return-value","-freciprocal-math","-freg-struct-return","-frename-registers","-freorder-blocks","-freorder-blocks-and-partition","-freorder-functions",
"-frerun-cse-after-loop","-freschedule-modulo-scheduled-loops","-frounding-math","-frtti","-fsched-critical-path-heuristic","-fsched-dep-count-heuristic","-fsched-group-heuristic","-fsched-interblock","-fsched-last-insn-heuristic","-fsched-pressure",
"-fsched-rank-heuristic","-fsched-spec","-fsched-spec-insn-heuristic","-fsched-spec-load","-fsched-spec-load-dangerous","-fsched-stalled-insns","-fsched-stalled-insns-dep","-fsched2-use-superblocks","-fschedule-fusion","-fschedule-insns",
"-fschedule-insns2","-fsection-anchors","-fsel-sched-pipelining","-fsel-sched-pipelining-outer-loops","-fsel-sched-reschedule-pipelined","-fselective-scheduling","-fselective-scheduling2","-fshort-enums","-fshort-wchar","-fshrink-wrap",
"-fshrink-wrap-separate","-fsignaling-nans","-fsigned-zeros","-fsingle-precision-constant","-fsplit-ivs-in-unroller","-fsplit-loops","-fsplit-paths","-fsplit-wide-types","-fssa-backprop","-fssa-phiopt",
"-fstack-protector","-fstack-protector-all","-fstack-protector-explicit","-fstack-protector-strong","-fstdarg-opt","-fstore-merging","-fstrict-aliasing","-fstrict-enums","-fstrict-overflow","-fstrict-volatile-bitfields",
"-fthread-jumps","-fno-threadsafe-statics","-ftracer","-ftrapping-math","-ftrapv","-ftree-bit-ccp","-ftree-builtin-call-dce","-ftree-ccp","-ftree-ch","-ftree-coalesce-vars",
"-ftree-copy-prop","-ftree-cselim","-ftree-dce","-ftree-dominator-opts","-ftree-dse","-ftree-forwprop","-ftree-fre","-ftree-loop-distribute-patterns","-ftree-loop-distribution","-ftree-loop-if-convert",
"-ftree-loop-im","-ftree-loop-ivcanon","-ftree-loop-optimize","-ftree-loop-vectorize","-ftree-lrs","-ftree-partial-pre","-ftree-phiprop","-ftree-pre","-ftree-pta","-ftree-reassoc",
"-ftree-scev-cprop","-ftree-sink","-ftree-slp-vectorize","-ftree-slsr","-ftree-sra","-ftree-switch-conversion","-ftree-tail-merge","-ftree-ter","-ftree-vectorize","-ftree-vrp",
"-funconstrained-commons","-funroll-all-loops","-funroll-loops","-funsafe-math-optimizations","-funswitch-loops","-funwind-tables","-fvar-tracking","-fvar-tracking-assignments","-fvar-tracking-assignments-toggle","-fvar-tracking-uninit",
"-fvariable-expansion-in-unroller","-fvpt","-fweb","-fwrapv"};
/*以下为失能的编译选项*/
char reenable[95][50] = {"-falign-labels","-fno-branch-count-reg","-fno-caller-saves","-fno-code-hoisting","-fno-combine-stack-adjustments","-fno-compare-elim","-fno-cprop-registers","-fno-crossjumping","-fno-cse-follow-jumps",
	"-fno-dce","-fno-defer-pop","-fno-devirtualize","-fno-devirtualize-speculatively","-fno-dse","-fno-expensive-optimizations","-fno-forward-propagate","-fno-gcse","-fno-gcse-after-reload","-fno-guess-branch-probability","-fno-hoist-adjacent-loads",
	"-fno-if-conversion","-fno-if-conversion2","-fno-indirect-inlining","-fno-inline","-fno-inline-functions","-fno-inline-functions-called-once","-fno-inline-small-functions","-fno-ipa-bit-cp","-fno-ipa-cp-clone","-fno-ipa-icf","-fno-ipa-icf-functions",
	"-fno-ipa-icf-variables","-fno-ipa-profile","-fno-ipa-pure-const","-fno-ipa-ra","-fno-ipa-reference","-fno-ipa-sra","-fno-ipa-vrp","-fno-isolate-erroneous-paths-dereference","-fno-jump-tables","-fno-ipa-cp","-fno-lra-remat","-fno-move-loop-invariants",
	"-fno-omit-frame-pointer","-fno-optimize-sibling-calls","-fno-optimize-strlen","-fno-partial-inlining","-fno-peel-loops","-fno-peephole2","-fno-predictive-commoning","-fno-printf-return-value","-fno-rename-registers","-fno-reorder-blocks",
	"-fno-reorder-blocks-and-partition","-fno-reorder-functions","-fno-rerun-cse-after-loop","-fno-rtti","-fno-schedule-insns2","-fno-short-enums","-fno-shrink-wrap","-fno-split-loops","-fno-split-paths","-fno-ssa-phiopt","-fno-store-merging",
	"-fno-strict-aliasing","-fno-strict-overflow","-fno-thread-jumps","-fthreadsafe-statics","-fno-tree-bit-ccp","-fno-tree-builtin-call-dce","-fno-tree-ccp","-fno-tree-ch","-fno-tree-coalesce-vars","-fno-tree-copy-prop","-fno-tree-dce","-fno-tree-dominator-opts",
	"-fno-tree-dse","-fno-tree-fre","-fno-tree-loop-distribute-patterns","-fno-tree-loop-vectorize","-fno-tree-partial-pre","-fno-tree-pre","-fno-tree-pta","-fno-tree-sink","-fno-tree-slp-vectorize","-fno-tree-slsr","-fno-tree-sra","-fno-tree-switch-conversion",
	"-fno-tree-tail-merge","-fno-tree-ter","-fno-tree-vrp","-fno-unswitch-loops","-fno-var-tracking","-fno-var-tracking-assignments","-fno-web"};


void ded(int &b){   //去重  
	if(ran_compile[b].compile[0] == '\0'){
		(b)--;
		return;
	}
	for(int i = 0;i < b;i++){
		if(strcmp(ran_compile[i].compile,ran_compile[b].compile) == 0){
			(b)--;
		}
	}
} 


void ranProbability(){ //产生随机化组编译选项，返回一个指向结构体一元数组的指针，即产生的随机化组编译选项
	
	//组编译选项数组初始化
	for(int k = 0;k < 214;k++){
		strcpy(all_compile[k].compile,str[k]);//将str中的字符串，复制给all_compile.compile
	}

	srand((unsigned)time(NULL)); //产生随机化的种子
	x = rand()%214; //随机化产生一个x
	int i,j,h,l,k,p; 
	float sum,n,average; //average为概率的平均值,sum为所有编译选项概率的和
	h=0;l=0;sum=0,k = 0;
	
	//概率初始化
	for(i=0,n=1;i<214;i++){
		all_compile[i].odds=n;
		n++;
	}
	
	//从所有编译选项中随机选出X个编译选项: 开始让高概率和低概率相结合，到高概率组的编译选项的个数大于低概率组的个数时，只从高概率组随机选择
	for(j=0; j<214; j++){ //计算出所有编译选项概率(权重)的平均值
		sum=sum + all_compile[j].odds;
	}
	average=sum/214;//概率的平均值

	//以概率平均值为指标，将所有编译选项分为高概率和低概率两组
	for(i=0; i<214; i++){
		if(all_compile[i].odds > average){
			high_compile[h]=all_compile[i];
//			printf("++++++%s-----%s\n",high_compile[h].compile,all_compile[i].compile);
			h++;
		}
		else{
			low_compile[l]=all_compile[i];
//			printf("++++++%s-----%s\n",low_compile[l].compile,all_compile[i].compile);
			l++;
		}
	}
	
	if(h<l){//如果高概率组的编译选项的个数小于低概率组的个数，则分别在高概率和低概率两组中随机选择编译选项
		for(k=0; k<x/2; k++){
			if(high_compile[0].compile[0] == '\0'){
//				printf("highΪ��\n");
				break;
			}
			ran_compile[k]=high_compile[rand()%214]; 
//			printf("++++++%s-----%s\n",ran_compile[k].compile,"12344333222");
			ded(k);
		}
		if(high_compile[0].compile[0] == '\0'){
			k = 0;
		}
//		printf("--k = %d\n",k);
		for(p=k; p<x; p++){
			if(low_compile[0].compile[0] == '\0'){
//				printf("lowΪ��\n");
				break;
			}
			ran_compile[p]=low_compile[rand()%214]; 
//			printf("ran_[%d]++++++%s-----%s\n",p,ran_compile[p].compile,"12344333222");
			ded(p);
		}
	}
	else{//如果高概率组的编译选项的个数大于低概率组的个数，只在高概率组中选择x个编译选项
		for(k=0; k<x; k++){
			if(high_compile[0].compile[0] == '\0'){
				break;
			}
			ran_compile[k]=high_compile[rand()%214]; 
			ded(k);
		}
	}
}

/*当触发新的覆盖，调整权重*/
void add_opt() { 

	float n = ODD;
		for(int i = 0;i < x;i++){
			if(ran_compile[i].odds + n < 1){
				ran_compile[i].odds += n;  //n是增加的概率
			}
			
		}
	for(int j = 0;j < x;j++){
		for(int i = 0;i < 214;i++){
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
		if(ran_compile[i].odds - s > 0){
			ran_compile[i].odds -= s;  
		}
	}
	for(int j = 0;j < x;j++){
		for(int i = 0;i < 214;i++){ 
			if(strcmp(all_compile[i].compile,ran_compile[j].compile) == 0)	{
				all_compile[i].odds = ran_compile[j].odds;
			}
		}
	}	
}

/*Incorporate strings into parameters*/
char** add(int m,char** argv0){
	/*make dis*/
	char** p =  argv0;
	char** p_argv;

	int x = 0;
	int d = 0;
	int disen = 95;
	while(*p != '\0'){

		x++;
		cout<<"----------argv----------"<<endl;
		cout<<*p<<endl;
		p = p + 1;
	}

	//p = (char**)realloc(p_argv,sizeof(char*)*(disen+x+m+1));
	p = (char**)realloc(p_argv,sizeof(char*)*(disen+x+m+1));
	if(p == NULL){  
		//argv0 = p;
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
	while(*p != '\0'){
		p_argv[d] = *p; 
		d++;
		p = p + 1;
	}
	/*add disen*/
	for(int i = x;i < disen+x;i++){
		p_argv[i] = reenable[i-x];
	}

	for (int i = x+disen; i < (disen+x+m); i++)
	{
		/* code */

		p_argv[i] = ran_compile[i-x-disen].compile;

//		printf("------dayin------- : x = %d   %s\n",i-x,p_argv[i]);

	}

	

	printf("-------------over---------       m=%d x=%d x+m=%d\n",x,m,x+m);
	p_argv[x+m+disen] = NULL;
	p = p_argv;
	x = 0;
	while(*p != NULL){
		printf("pp = %s\n",p_argv[x]);
		x++;
		p++;
	}
	return p_argv;
	
}



#endif /*! _HAVE_RANOPT_H*/