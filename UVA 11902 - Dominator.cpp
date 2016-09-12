#include <iostream>
#include <string>

using namespace std;

void dfs_visit(int n, int **matriz, char *cor, int vertice, int **pai){
	cor[vertice] = 'c';
	for(int i = 0; i < n; i++){
		if(matriz[vertice][i] == 1){
			if(cor[i] == 'b'){
				pai[i][0] = 1;
				pai[i][1] = vertice;
				dfs_visit(n, matriz, cor, i, pai);
			}
			else 
				if(i != vertice)
					pai[i][0] = 0;
		}
	}
}

int main(){
	int t, n;
	cin >> t;
	for(int x = 0; x < t; x++){
		cin >> n;
		int **matriz = new int*[n];
		int **pai = new int*[n];
		char *cor = new char[n];
		char **dominator = new char*[n];
		for(int i = 0;i < n; ++i){
	        matriz[i] = new int[n];
	        pai[i] = new int[2];
	        dominator[i] = new char[n];
	        cor[i] = 'b';
	    }
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				pai[i][j] = 0;
				dominator[i][j] = 'N';
				matriz[i][j] = 0;
			}
		}
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				cin >> matriz[i][j];
			}
		}
		dfs_visit(n, matriz, cor, 0, pai);
		for(int i = 0; i < n; i++){
			if(pai[i][0] == 1){
				dominator[pai[i][1]][i] = 'Y';
			}
			if(cor[i] == 'c'){
				dominator[0][i] = 'Y';
				dominator[i][i] = 'Y';
			}
		}
		cout << "Case " << x+1 << ":" << endl;
		for(int i = 0; i < n; i++){
			cout << "+";
			for(int i = 0; i < ((2*n) - 1); i++){
				cout << "-";
			}
			cout << "+" << endl;
			for(int j = 0; j < n; j++){
				cout << "|" << dominator[i][j];
			}
			cout << "|" << endl; 
		}
		cout << "+";
		for(int i = 0; i < ((2*n) - 1); i++){
			cout << "-";
		}
		cout << "+" << endl;
	}
}
