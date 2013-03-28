#include <IOSTREAM>
using namespace std;
/*
A[1-n]��ʾn������A[i] --> p[i-1] X p[i]
p[0-n]��ʾ����ľ�����
m[i][j]��ʾ����ֵ
s[i][j]��¼���Ž�
*/

const int N = 6;
int m[N+1][N+1] = {0};
int s[N+1][N+1] = {0};
void MatrixChain(int *p, int n, int m[N+1][N+1], int s[N+1][N+1]) {

	//Ԥ����߽�
	for (int i=1; i<=n; i++) {
		m[i][i] = 0;
	}

	for (int l=2; l<=n; l++) {
		for (i=1; i<=n-l+1; i++) {

			int j = i+l-1;

			//�����������á���ʼ����Сֵ��
			m[i][j] = m[i][i] + m[i+1][j] + p[i-1]*p[i]*p[j];
			s[i][j] = i;

			for (int k=i+1; k<j; k++) {

				int q = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];

				if (q < m[i][j]) {
					m[i][j] = q;
					s[i][j] = k;
				}
				
			}
		}
	}
}

void print_optimal_parens(int s[N+1][N+1], int i, int j) {
	if (i == j) {
		cout<<"A"<<i;
	} else {
		cout<<"(";
		print_optimal_parens(s, i, s[i][j]);
		print_optimal_parens(s, s[i][j]+1, j);
		cout<<")";
	}

}

int main(void) {

	int p[] = {30, 35, 15, 5, 10, 20, 25};
	
	MatrixChain(p, N, m, s);
	print_optimal_parens(s, 1, 6);
	cout<<endl;

	return 0;
}