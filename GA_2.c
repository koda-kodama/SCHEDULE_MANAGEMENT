#include<stdio.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>

//作り直し　先生のアルゴリズムをもとに
//遺伝子はとりあえずランダムに入れる


//配列の中身をシャッフルして適応度を求めていく　繰り返して適応度が高いものを記録

//評価関数作成
//シャッフルがやばい　書き直そう

#define MAX_FRAME 42



typedef struct task TASK;

struct task{
	int frame;//コマ数
	double deadline;//締め切り
	int cost;//優先度
	char name[20];
};





//配列をシャッフル

void shuffle(int array[],int size){

	srand((unsigned)time(NULL));

	//printf("RAND_MAX=%d\n",RAND_MAX);
	//printf("size=%d\n",size);
	for(int i = 0; i < size; i++) {
        int j = rand()%size;
        int t = array[i];
        //printf("j=%d\n",j);
        array[i] = array[j];
        array[j] = t;
    }
}



double GA(TASK tasks[],int size){
	int gene[MAX_FRAME]={},i=0,j=0,k=0;
	int result[MAX_FRAME]={};//結果を格納
	int tmp[MAX_FRAME]={};//shuffle用
	int exchange[MAX_FRAME]={};//配列の移動用
	double days;
	int penalty=0,number=0,fitness=10000;
	int maxfitness=0;
	int count=0;//配列生成用



//配列の中身をとりあえず作る
	for(i=0; i<size; i++){
			while(count<tasks[k].frame){
			gene[j]=i;
			count++;
			j++;
		}
		k++;
		count=0;
	}


	for(i=0; i<size; i++){
		printf("%d",gene[i]);
	}

 //評価

 	for(i=0; i<size; i++){


 		for(number=0; number<10; number++){
 			//不要部分を抜いてシャッフル

 			for(j=i; j<size; j++){
 				tmp[j]=gene[j];
 			}
 			

 			shuffle(tmp,size-i);

 			//配列の再生成
 			for(j=0; j<size-i; j++){
 				gene[j]=tmp[j];
 			}


 			/*printf("再生成した配列の表示\n");

 			for(j=0; j<size-i; j++){
 				printf("%d",gene[j]);
 			}

 			printf("\n");
 			*/
 			
//fprintf( stderr, "Check\n" );
	 	//タスクが並んでいたら＋
		 	if(gene[i]==gene[i+1]){
	 			fitness+=30;
	 		}

	 		fitness+=tasks[gene[i]].frame*5;
	 		
	//6で割った賞を使って残り日数と比較[
	 		
	 	
	 		//１日目
	 		if(i<6){

	 			if(tasks[gene[i]].deadline <3){
	 				penalty+=500;
	 					if(tasks[gene[i]].deadline <1){
	 						penalty+=1000;
	 					}
	 				}
	 			}



	 		if(i>6 && i<12){

	 			if(tasks[gene[i]].deadline <4){
	 				penalty+=500;
	 					if(tasks[gene[i]].deadline <2){
	 						penalty+=1000;
	 					}
	 				}
	 			}
	 			
	 		

	 		if(i>12 && i<18){
	 			if(tasks[gene[i]].deadline <5){
	 				penalty+=500;
	 					if(tasks[gene[i]].deadline <3){
	 						penalty+=1000;
	 					}
	 				}
	 			}



	 		if(i>18 && i<24){
	 			if(tasks[gene[i]].deadline <6){
	 				penalty+=500;
	 					if(tasks[gene[i]].deadline <4){
	 						penalty+=1000;
	 					}
	 				}
	 			}

	 		

	 		if(i>24 && i<30){

	 			if(tasks[gene[i]].deadline <7){
	 				penalty+=500;
	 					if(tasks[gene[i]].deadline <5){
	 						penalty+=1000;
	 					}
	 				}
	 			}



	 		if(i>30 && i<36){

	 			if(tasks[gene[i]].deadline <8){
	 				penalty+=500;
	 					if(tasks[gene[i]].deadline <6){
	 						penalty+=1000;
	 					}
	 				}
	 			}

	 		
	 		if(i>36 && i<42){


	 			if(tasks[gene[i]].deadline <9){
	 				penalty+=500;
	 					if(tasks[gene[i]].deadline <7){
	 						penalty+=1000;
	 					}
	 				}
	 			}


	 			fitness=fitness-penalty;//適応度

	 			if(maxfitness<fitness){
	 				maxfitness=fitness;
	 				result[i]=gene[i];//最適解を保存

	 		}

	 	}


 	}

 	 	for(i=0; i<size; i++){
	 		printf("%d\n",result[i]);
	 	}



	 	for(i=0; i<size; i++){
	 		printf("%s \n",tasks[result[i]].name);
	 	}

 
}

double show_time(){//締め切りまでの日数計算
	time_t now,dat;
	struct tm ts={0};
	double diff,number;
	char *timedat=malloc(8);

	//char *timedat = "20180631";
	
	printf("入力例：20180530");
	scanf("%s",timedat);

	now=time(NULL);

	sscanf(timedat ,"%4d%2d%2d",&(ts.tm_year),&(ts.tm_mon),&(ts.tm_mday));
	ts.tm_year -= 1900;
	ts.tm_mon -= 1;
	dat = mktime(&ts);

	diff = difftime(dat, now);
	number = diff / (60*60*24);

	//printf("日数%f",number); //日数の確認用

	free(timedat);

	return number;


}



double cost(TASK tasks){
	double cc=0,max=1000;//コストの計算
	double fitness;//適応度の計算　
	


	cc=1000.0/tasks.deadline+tasks.frame*5;//コストが一番たかい
	//fitness=max-ccの式は後程実装
	//printf("%d",cc);
	
	return cc;


}


void show_priority(TASK tasks[],int n){//優先度が高いものから表示
	int i=0,j=0;
	TASK tmp;

	for(i=0; i<n; i++){
		for(j=i+1; j<n; j++){
			if(tasks[i].cost<tasks[j].cost){
				tmp=tasks[i];
				tasks[i]=tasks[j];
				tasks[j]=tmp;

			}
		}
	}

	for(i=0; i<n; i++){
		printf("%s \n",tasks[i].name);
	}


}





int main(void){
	struct task tasks[10];
	int n=0,i=0,day;
	int size=0;//遺伝子の長さ（コマ数の合計）

	printf("SCHEDULE MANAGMENT\n");


	printf("入力するタスクの数:");
	scanf("%d",&n);

	printf("taskの入力\n");

	for(i=0; i<n; i++){
	printf("task名:");
	scanf("%s",tasks[i].name);

	printf("コマ数:");
	scanf("%d",&tasks[i].frame);

	size+=tasks[i].frame;//遺伝子の長さを計算

	printf("締め切りの入力：");

	tasks[i].deadline=show_time();//締め切りまでの日数

	tasks[i].cost=cost(tasks[i]);
	
	}

	printf("遺伝子の長さ　%d\n",size);

//入力確認
	printf("\n\n--------入力確認-----------");
	for(i=0; i<n; i++){
		printf("\n task名：%s \n コマ数:%d \n 締め切りまでの日数：%f \n",tasks[i].name,tasks[i].frame,tasks[i].deadline);
	}


	printf("\n\n-----------------");
	printf("\n 優先度の表示\n");


	GA(tasks,size);

	return 0;
}
