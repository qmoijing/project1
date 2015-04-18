#include "Sudoku.h"
using namespace std;
void Sudoku::GiveQuestion()
{
    int question[12][12]={{ 4, 2, 6, 8, 7, 3, 9, 5, 1,-1,-1,-1},
                          { 0, 0, 3, 9, 5, 0, 6, 0, 4,-1,-1,-1},
                          { 9, 0, 1, 6, 2, 4, 8, 0, 0,-1,-1,-1},
                          {-1,-1,-1, 1, 3, 2, 0, 8, 7, 9, 5, 6},
                          {-1,-1,-1, 0, 8, 0, 1, 9, 0, 4, 2, 0},
                          {-1,-1,-1, 4, 9, 6, 2, 3, 0, 8, 7, 1},
                          { 1, 0, 0, 0, 4, 0,-1,-1,-1, 6, 9, 5},
                          { 0, 0, 4, 0, 6, 0,-1,-1,-1, 1, 3, 7},
                          { 6, 9, 5, 0, 1, 7,-1,-1,-1, 2, 8, 4},
                          { 3, 1, 2,-1,-1,-1, 7, 4, 0, 5, 0, 9},
                          { 7, 4, 8,-1,-1,-1, 0, 6, 9, 3, 0, 2},
                          { 0, 6, 0,-1,-1,-1, 3, 1, 0, 7, 0, 8}};
    int question_1[12][12],i,j;
    for(i=0;i<12;i++)
    {
        for(j=0;j<12;j++){question_1[i][j]=question[i][j];}
    }
    /*旋轉*/
    int a=rand()%4;
    switch(a)
    {
        case 0: for(i=0;i<12;i++)//不轉動
                {
                    for(j=0;j<12;j++){question[j][i]=question_1[i][j];}
                }
                break;
        case 1: for(i=0;i<12;i++)//上下左右顛倒
                {
                    for(j=0;j<12;j++){question[11-j][11-i]=question_1[i][j];}
                }
                break;
        case 2: for(i=0;i<12;i++)//上下顛倒
                {
                    for(j=0;j<12;j++){question[11-i][j]=question_1[i][j];}
                }
                break;
        case 3: for(i=0;i<12;i++)//左右顛倒
                {
                    for(j=0;j<12;j++){question[i][11-j]=question_1[i][j];}
                }
                break;
    }
    /*數字對調*/
    int change;
    int b=rand()%8+1;
    int c=rand()%8+1;
    for(i=0;i<12;i++)
    {
        for(j=0;j<12;j++)
        {
            if(question[i][j]==b){question[i][j]=10;}
        }
    }
    for(i=0;i<12;i++)
    {
        for(j=0;j<12;j++)
        {
            if(question[i][j]==c){question[i][j]=b;}
        }
    }
    for(i=0;i<12;i++)
    {
        for(j=0;j<12;j++)
        {
            if(question[i][j]==10){question[i][j]=c;}
        }
    }
    /*print出題目*/
    for(i=0;i<12;i++)
    {
        for(j=0;j<12;j++)
        {
            if(question[i][j]==-1){cout<<question[i][j]<<" ";}
            if(question[i][j]!=-1){cout<<" "<<question[i][j]<<" ";}
        }
        cout<<endl;
    }
}
void Sudoku::ReadIn()
{
	for(int i=0;i<144;i++){cin>>sudoku[i];}
}
bool Sudoku::Check()
{
	int i,j;
	int count_space;
	/*檢查數字是否在-1~9*/
	for(i=0;i<144;i++)
    {
		if(sudoku[i]>9||sudoku[i]<-1){return false;}
	}
	/*檢查橫排*/
	for(i=0;i<12;i++)
    {
		bool num[11]={false};
		for(j=0+12*i;j<12+12*i;j++)
		{
			if(sudoku[j]!=0&&sudoku[j]!=-1&&num[sudoku[j]+1]==1){return false;}
			else{num[sudoku[j]+1]=true;}
		}
	}
	/*檢查直排*/
	for(i=0;i<12;i++)
    {
		bool num[11]={false};
		for(j=i;j<=i+132;j=j+12)
        {
			if(sudoku[j]!=0&&sudoku[j]!=-1&&num[sudoku[j]+1]==1){return false;}
			else{num[sudoku[j]+1]=true;}
		}
	}
	/*檢查九宮格*/
	for(i=0;i<144;i)
    {
		count_space=0;//計算黑區塊
		bool num[11]={false};
		for(j=i;j<i+27;j)
        {
			if(sudoku[j]==-1){count_space++;}
			else if(sudoku[j]!=0&&num[sudoku[j]+1]==1){return false;}
			else{num[sudoku[j]+1]=true;}
			/*同一個九宮格*/
			if(j%3==2){j=j+10;}
			else{j++;}
		}
		if(count_space!=9&&count_space!=0){return false;}
		/*下一個九宮格*/
		if((i/3+1)%4==0){i=i+27;}
		else{i=i+3;}
	}
    return true;
}
void Sudoku::Run(int n)
{
	int i;
    if(catergory>1){return;}
	else if(n>=144)
    {
		catergory++;
		for(i=0;i<144;i++){ans[i]=sudoku[i];}
	}
	else if(sudoku[n]!=0){Run(n+1);}//不為空格
	else
    {
		for(i=1;i<=9;i++)
        {
			sudoku[n]=i;
			if(Check()==0){sudoku[n]=0;}//答案錯誤
			else
            {
				Run(n+1);
				sudoku[n]=0;
			}
		}
	}
}
void Sudoku::Solve()
{
	int i;
	int count_zero=0;
	int count_space=0;
	catergory=0;
	for(int j=0;j<144;j++)//檢查黑區塊
    {
		if(sudoku[j]==-1){count_space++;}
	}
	/*檢查題目*/
	if(Check()==0){cout<<"0"<<endl;}
	else if(count_space!=36){cout<<"0"<<endl;}//黑區塊不完整
	else
    {
		Run(0);
		for(i=0;i<144;i++){sudoku[i]=ans[i];}
		for(i=0;i<144;i++)//檢查是否有零
        {
			if(sudoku[i]==0){count_zero=1;}
		}
		if(count_zero==0)
        {
            if(catergory==1)//一組解
            {
 				cout << "1" <<endl;
                int change_line=0;
                for(i=0;i<144;i++)//print出答案
                {
                    if(sudoku[i]==-1){cout<<sudoku[i]<<" ";}
                    if(sudoku[i]!=-1){cout<<" "<<sudoku[i]<<" ";}
                    change_line++;
                    if(change_line==12)//換行
                    {
                        cout<<endl;
                        change_line=0;
                    }
                }
            }
			else{cout<<"2"<<endl;}//多組解
		}
		else if(count_zero==1){cout<<"0"<<endl;}//無解
	}
}
