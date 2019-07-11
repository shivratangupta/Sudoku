#include<iostream>
#include<vector>
#include<stdlib.h>
#include<math.h>
using namespace std;

int n=9, k, sqn;
vector<vector<int> > arr(n, vector<int> (n, 0));

bool Notingrid(int row, int col, int num){
	for(int i=0; i<sqn; i++){
		for(int j=0; j<sqn; j++){
			if(arr[row+i][col+j] == num)
				return false;
		}
	}

	return true;
}

void fillgrid(int row, int col){
	int num;
	for(int i=0; i<sqn; i++){
		for(int j=0; j<sqn; j++){
			num = rand() % 9 + 1;
			while(!Notingrid(row, col, num))
				num = rand() % 9 + 1;

			arr[row+i][col+j] = num;
		}
	}
}

bool Notinrow(int i, int num){
	for(int j=0; j<n; j++){
		if(arr[i][j] == num)
			return false;
	}

	return true;
}

bool Notincol(int j, int num){
	for(int i=0; i<n; i++){
		if(arr[i][j] == num)
			return false;
	}

	return true;
}

bool checksafe(int i, int j, int num){
	return Notinrow(i, num) && Notincol(j, num) &&
		   Notingrid(i - i % sqn, j - j % sqn, num);
}

bool fillothers(int i, int j){
	if(j >= n && i < n-1){
		i++;
		j = 0;
	}

	if(i >= n && j >= n)
		return true;

	if(i < sqn){
		if(j < sqn)
			j = sqn;
	}

	else if(i < n - sqn){
		if(j == (int)(i / sqn) * sqn)
			j = j + sqn;
	}

	else{
		if(j == n - sqn){
			i++;
			j = 0;

			if(i >= n)
				return true;
		}
	}

	for(int num=1; num<=9; num++){

		if(checksafe(i, j, num)){

			arr[i][j] = num;
			if(fillothers(i, j+1))
				return true;

			arr[i][j] = 0;
		}
	}

	return false;
}

void removedigits(){
	int count;
	count = k;

	while(count != 0){
		int gridno;

		gridno = (rand() % (n * n));

		int i, j;
		i = gridno / n;
		j = gridno % n;

		if(arr[i][j] != 0){
			count--;
			arr[i][j] = 0;
		}
	}
}

void printsudoku(){
	for(int i=0; i<n; i++){
		if(i % 3 == 0)
			cout<<"-------------"<<endl;
		for(int j=0; j<n; j++){
			if(j % 3 == 0)
				cout<<"|";

			cout<<arr[i][j];
		}

		cout<<"|"<<endl;
	}
	cout<<"-------------"<<endl;
}

void solvesudoku(vector<vector<int> > result){
	int count;
	count = k;

	while(count != 0){
		int x, y, num;
		cout<<"Enter position which you want to change"<<endl;
		cout<<"Row:";
		cin>>x;
		cout<<"Col:";
		cin>>y;

		if(arr[x-1][y-1] != 0)
			cout<<"You can't change filled position"<<endl;

		else{
			cout<<"Enter number:";
			cin>>num;

			if(num == result[x-1][y-1]){
				arr[x-1][y-1] = num;
				printsudoku();
				count--;
			} 

			else
				cout<<"You have Entered wrong number in that position"<<endl;
		}
	}

	cout<<"Congratulation you have completed the sudoku"<<endl;
}

int main(){
	sqn = sqrt(n);

	for(int i=0; i<n; i+=sqn)
		fillgrid(i, i);

	fillothers(0, 3);

	int choice;
	bool diff = true;
	while(diff){
		cout<<"1.Easy"<<endl;
		cout<<"2.Medium"<<endl;
		cout<<"3.Hard"<<endl;

		cout<<"Enter the difficulty level:";
		cin>>choice;

		switch(choice){
			case 1:
				k = 43;
				diff = false;
				break;

			case 2:
				k = 51;
				diff = false;
				break;

			case 3:
				k = 56;
				diff = false;
				break;

			default:
				cout<<"You have Entered wrong choice"<<endl; 
		}
	}

	vector<vector<int> > result;
	
	result = arr;

	removedigits();
	
	printsudoku();

	solvesudoku(result);
}