#include <stdio.h>
#include<stdlib.h>
#define MIN(a,b) (((a)<(b))? (a) :(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
#define N 7
#define MAXINF 999999
#define MININF -999999

//현재 오목판 상태를 전역변수로 설정 
int arr1[6][7]={{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0}};
int count=0; // 공격 주고받은 횟수  
int win=0; //win checking 위해 만들어준 변수 

//상태에 대한 utility값 넣어주기위한 구조체  
typedef struct utilitynode{
	
	int utility;  
	
	struct utilitynode * child[N];

}utilitynode;

//아무 돌도 안놓여있을 상태 check 
int empty_check(int arr[6][7]){
	
	int i,j;
	int n=0;
	for(i=0;i<6;i++){
		for(j=0;j<7;j++){
			if(arr[i][j]==0)
				
				n++;
		}
	}
	if(n==42)
		
		return 1;

	else 
		return 0;
}

//가득차서 더 돌을 넣을 수 없는 상태 check 
int full_check(int a[6][7])
{
	int k=0;
	int i,j;
	for(i=0;i<6;i++){
		for(j=0;j<7;j++){
			if(a[i][j]==0)
				
				++k;
		}
	}	
	if(k==0)
		
		return 1;
	else 
		return 0;
	
}

//해당 상태 출력  
void print_connect4 (int arr[6][7]){
	
	printf("\n");
	int i,j;
	for(i=0;i<6;i++){
		for(j=0;j<7;j++){
			
			printf("|%c",arr[i][j]);
		
		}
		
		printf("|\n");
	}
	
		printf("%2d%2d%2d%2d%2d%2d%2d", 1,2,3,4,5,6,7);
	
	printf("\n");
}

//사용자 공격   
void human_move(int arr[6][7]){

	int num;
	int i=0;
	
	printf("\nHuman turn:");
	scanf("%d",&num);
	
	if((num<1)||(num>7)){
	
		human_move(arr); 
		return ;
	}
	while(i<6){
		
		if(arr[i][num-1]!=0)
			break;
		
		i++;
	}
	
	if((i==0)||(empty_check(arr)&&(num==4))){
	
		human_move(arr);
		
		return;
	}
	
	arr[i-1][num-1]='O';
	
	print_connect4(arr);
	
}

//ai 공격   
void ai_move(int arr[6][7],int j){
	
	int i=0;
	while(i<6){
		
		if(arr[i][j]!=0)
			break;
		
		i++;
	}
	
	arr[i-1][j]='X';
	print_connect4(arr);
}

//수평 four in row check 
void horizontal_check(int arr[6][7]){
	
	int i,j;
	for(i=0;i<6;i++){
		for(j=0;j<4;j++){
			if((arr[i][j]==arr[i][j+1])&&(arr[i][j]==arr[i][j+2])&&(arr[i][j]==arr[i][j+3])&&(arr[i][j]=='O')){
				win++;
			
			}
			else if((arr[i][j]==arr[i][j+1])&&(arr[i][j]==arr[i][j+2])&&(arr[i][j]==arr[i][j+3])&&(arr[i][j]=='X')){
				win++;
			
			}	
		}
	}
}

//수직 four in row check 
void vertical_check(int arr[6][7]){
	
	int i,j;
	for(i=0;i<7;i++){
		for(j=0;j<3;j++){
			if((arr[j][i]==arr[j+1][i])&&(arr[j][i]==arr[j+2][i])&&(arr[j][i]==arr[j+3][i])&&(arr[j][i]=='O')){
				win++;
			
			}
			else if((arr[j][i]==arr[j+1][i])&&(arr[j][i]==arr[j+2][i])&&(arr[j][i]==arr[j+3][i])&&(arr[j][i]=='X')){
				win++;
			
			}
		}
	}
}

//대각선 four in row check 
void diagonal_check(int arr[6][7]){
	
	int i,j;
	for(j=0;j<4;j++)
	{
		for(i=0;i<3;i++){
			if((arr[i][j]==arr[i+1][j+1])&&(arr[i][j]==arr[i+2][j+2])&&(arr[i][j]==arr[i+3][j+3])&&(arr[i][j]=='O')){
				win++;
		
			}
			else if((arr[i][j]==arr[i+1][j+1])&&(arr[i][j]==arr[i+2][j+2])&&(arr[i][j]==arr[i+3][j+3])&&(arr[i][j]=='X')){
				win++;
			
			}
		}
	}
	
	for(j=3;j<7;j++)
	{
		for(i=0;i<3;i++){
			if((arr[i][j]==arr[i+1][j-1])&&(arr[i][j]==arr[i+2][j-2])&&(arr[i][j]==arr[i+3][j-3])&&(arr[i][j]=='O')){
				win++;
				
			}
			else if((arr[i][j]==arr[i+1][j-1])&&(arr[i][j]==arr[i+2][j-2])&&(arr[i][j]==arr[i+3][j-3])&&(arr[i][j]=='X')){
				win++;
			
			}
		}
	}
}

// 승패 가려진 상태 check 
int end_check(int a[6][7],char c){
	
	int k=0;
	int i,j;
	for(i=0;i<6;i++){
		for(j=0;j<4;j++){
			
			 if((a[i][j]==a[i][j+1])&&(a[i][j]==a[i][j+2])&&(a[i][j]==a[i][j+3])&&(a[i][j]==c))
				++k;
		}
	}
	for(i=0;i<7;i++){
		for(j=0;j<3;j++){
		
			 if((a[j][i]==a[j+1][i])&&(a[j][i]==a[j+2][i])&&(a[j][i]==a[j+3][i])&&(a[j][i]==c))
				++k;
		}
	}
	for(j=0;j<4;j++)
	{
		for(i=0;i<3;i++){
			
			 if((a[i][j]==a[i+1][j+1])&&(a[i][j]==a[i+2][j+2])&&(a[i][j]==a[i+3][j+3])&&(a[i][j]==c))
				++k;
		}
	}
	for(j=3;j<7;j++)
	{
		for(i=0;i<3;i++){
			 if((a[i][j]==a[i+1][j-1])&&(a[i][j]==a[i+2][j-2])&&(a[i][j]==a[i+3][j-3])&&(a[i][j]==c))
				++k;
		}
	}
	
	if(k==0)
		
		return 0;
	else 
		return 1;
}

//승패 판결  
void who_win(int arr[6][7]){
	
	horizontal_check(arr);
	vertical_check(arr);
	diagonal_check(arr);

}

//각 state의  utility값으로 들어갈 score 구하는 function 
int score_check( int a[6][7],int arr[6][7],char c,int depth){
	
	int i,j,l;
	int k=0;
	if(end_check(arr,c)){
	
		k+=MAXINF/depth;
		return k;
	}
	
	for(l=0;l<7;l++){
	
		for(i=0;i<6;i++){
			
			for(j=0;j<7;j++){
				
				a[i][j]=arr[i][j];
			}
		}
	
		int m=0;
		while(m<6){
			if(a[m][l]!=0)
				break;
			m++;
		}
		
		if (m==0)
			continue;
		
		a[m-1][l]=c;
	
	
		if(end_check(a,c))
			k+=10000/depth;
	
	}	
	
	for(i=0;i<6;i++){
	
		for(j=0;j<7;j++){
			
			a[i][j]=arr[i][j];
		}
	}
	
	for(i=0;i<6;i++){
		
		for(j=0;j<7;j++){
			
			if(a[i][j]==0)
				a[i][j]=c;
		}
	}
	
	for(i=0;i<6;i++){
		for(j=0;j<4;j++){
			
			 if((a[i][j]==a[i][j+1])&&(a[i][j]==a[i][j+2])&&(a[i][j]==a[i][j+3])&&(a[i][j]==c))
				++k;
		}
	}//horizontal check
	
	for(i=0;i<7;i++){
		for(j=0;j<3;j++){
		
			 if((a[j][i]==a[j+1][i])&&(a[j][i]==a[j+2][i])&&(a[j][i]==a[j+3][i])&&(a[j][i]==c))
				++k;
		}
	}//vertical check
	
	for(j=0;j<4;j++)
	{
		for(i=0;i<3;i++){
			
			 if((a[i][j]==a[i+1][j+1])&&(a[i][j]==a[i+2][j+2])&&(a[i][j]==a[i+3][j+3])&&(a[i][j]==c))
				++k;
		}
	}//diagonal check on right

	for(j=3;j<7;j++)
	{
		for(i=0;i<3;i++){
			 if((a[i][j]==a[i+1][j-1])&&(a[i][j]==a[i+2][j-2])&&(a[i][j]==a[i+3][j-3])&&(a[i][j]==c))
				++k;
		}
	}//diagonal check on left
	
	return k;

}

// human 과 ai의 score 차이를 구하여 최종 utility값으로 설정  
int scoref(int a[6][7],int arr[6][7],int depth){
	
	int aiscore,humscore;
	int score;
	
	aiscore=score_check(a,arr,'X',depth);

	humscore=score_check(a,arr,'O',depth);

	score=aiscore-humscore;

	return score;
	
}

//https://www.geeksforgeeks.org/serialize-deserialize-n-ary-tree/ 참고 
//utilitynode 할당 함수  
utilitynode *newNode(int arr[6][7],int b[6][7],int depth)  
{ 
    utilitynode *temp = (utilitynode*) malloc(sizeof(utilitynode)); 
	temp->utility = scoref(b,arr,depth); 
    int i;
	for ( i = 0; i < N; i++) 
        temp->child[i] = NULL; 
    return temp; 
} 

//https://en.wikipedia.org/wiki/Alpha%E2%80%93beta_pruning 참고
//alpha-beta pruning 
int alphabeta(utilitynode * node,int depth,int alpha,int beta,int maximizingplayer,int arr[6][7]){  
	
	int value;
	int b[7][6][7];
	int a[6][7];
	
	if ((depth==0)||end_check(arr,'O')||end_check(arr,'X')||full_check(arr))
		
		return node->utility;
	
	if (maximizingplayer){
		int j;
		
		value=MININF;
		for(j=0;j<7;j++){
			int i=0;
			while(i<6){
				if(arr[i][j]!=0)
					break;
				i++;
			}
			if((i==0)||((empty_check(arr))&&(j==3))){
				
				continue;
			}
			int k,l;
			for(k=0;k<6;k++){
				for(l=0;l<7;l++){
					b[j][k][l]=arr[k][l];
				}
			}
			b[j][i-1][j]='X';
			
			
			node->child[j]=newNode(b[j],a,10-depth);
		
		
			value=MAX(value,alphabeta(node->child[j],depth-1,alpha,beta,0,b[j]));
			alpha=MAX(alpha,value);
			if(alpha>=beta)
				break;
		
			
		}
		return value;
	}
	else {
	
		int j;
		
		value=MAXINF;
		for(j=0;j<7;j++){
			int i=0;
			while(i<6){
				if(arr[i][j]!=0)
					break;
				i++;
			}
			if((i==0)){
				
				continue;
			}
			int k,l;
			for(k=0;k<6;k++){
				for(l=0;l<7;l++){
					b[j][k][l]=arr[k][l];
				}
			}
			b[j][i-1][j]='O';
			
			
			node->child[j]=newNode(b[j],a,10-depth);
		
		
			value=MIN(value,alphabeta(node->child[j],depth-1,alpha,beta,1,b[j]));
			beta=MIN(beta,value);
			if(alpha>=beta)
				break;
		
			
		}
		return value;
	}
	
}


int main(){
	
	int num,value;
	
	printf("1.AI  2.Human\n");
	printf("선공 선택:");
	scanf("%d",&num);
	
	int a[6][7];
	
	utilitynode*root;
	int DEPTH=7;
	
	if(num==1){
		while(count<21){
			
			int j;
			int c[7][6][7]={{{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0}},
							{{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0}},
							{{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0}},
							{{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0}},
							{{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0}},
							{{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0}},
							{{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0}}};
			printf("\n AI is thinking...\n");
			value=alphabeta(root,DEPTH,MININF,MAXINF,1,arr1);
			
			for(j=0;j<7;j++){
				int i=0;
				while(i<6){
					if(arr1[i][j]!=0)
						break;
					i++;
				}
				if ((i==0)||(empty_check(arr1)&&j==3))continue;
				int k,l;
				for(k=0;k<6;k++){
					for(l=0;l<7;l++){
						c[j][k][l]=arr1[k][l];
					}
				}
				c[j][i-1][j]='X';
			
			}
			for(j=0;j<7;j++){
				if ((empty_check(arr1)&&j==3)||(empty_check(c[j])))continue;
				
				if(alphabeta(newNode(c[j],a,10-DEPTH),DEPTH-1,MININF,MAXINF,0,c[j])==value)
					break;
			}
		
			printf("\n해당 state에서 %d-depth alpha-beta pruning algorithm에 의해 score 값으로 %d 를 가져 다음의 수를 둔다\n",DEPTH,value);
			ai_move(arr1,j);
			who_win(arr1);
			
		
			if(win>=1){
				printf("AI win!");
				break;
			}
			
			
			human_move(arr1);
			who_win(arr1);
			if(win>=1)
			{
				printf("Human win!");
				break;
				
			}
			count++;
			
		}
	}else if(num==2){
			while(count<21){
			
				human_move(arr1);
				who_win(arr1);
				if(win>=1)
				{
					printf("Human win!");
					break;
				
				}
		
				int j;
				int c[7][6][7]={{{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0}},
							{{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0}},
							{{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0}},
							{{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0}},
							{{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0}},
							{{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0}},
							{{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0}}};
				printf("\n AI is thinking...\n");
				value=alphabeta(root,DEPTH,MININF,MAXINF,1,arr1);
	
				for(j=0;j<7;j++){
					int i=0;
					while(i<6){
						if(arr1[i][j]!=0)
							break;
						i++;
					}
				if (i==0)continue;
				int k,l;
				for(k=0;k<6;k++){
					for(l=0;l<7;l++){
						c[j][k][l]=arr1[k][l];
						}
					}
				c[j][i-1][j]='X';
			
				}
			
				for(j=0;j<7;j++){
					if(empty_check(c[j]) ) continue;
					if(alphabeta(newNode(c[j],a,10-DEPTH),DEPTH-1,MININF,MAXINF,0,c[j])==value)
						break;
				}
			
				printf("\n해당state에서 alpha-beta pruning algorithm에 의해 score 값으로 %d를 가져 다음의수를 둔다\n",value);
				ai_move(arr1,j);
				who_win(arr1);
		
				if(win>=1){
					printf("AI win!");
					break;
				}
		
				count++;
		
		
				}
			}
	
	if(count==21)
		printf("draw!");

	return 0;
 
	
}
