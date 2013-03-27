#include <iostream>
#include <CMATH>
#include <ITERATOR>
#include <algorithm>
using namespace std;

const int N = 6;

int A[N+1] = {0};

bool vis[N+1] = {false};

bool isp[N*2+1] = {true};

void createPrimeList() {
	
	fill(isp+1, isp+2*N+1, true);

	

	int m = (int)floor(sqrt(2*N)+0.5);
	int s = 0;
	for (int p=2; p<=m; p++) {
		for (int i=2; i<=N; i++) {
			s = i*p;
			if (s<=2*N && isp[s]) {
				isp[s] = false;
			}			
		}
	}
	
}

void primeCircle(int cur) {

	vis[1] = true;
	A[1] = 1;

	for (int i=2; i<=N; i++) {
		if (!vis[i] && isp[i + A[cur-1]]) {
			A[cur] = i;
			vis[i] = true;

			if (cur == N && isp[A[cur]+1]) {
				copy(A+1, A+N+1, ostream_iterator<int>(cout, " "));
				cout<<endl;
				//ע�⣺��û��ȫ������visʱ���������return;�������ʹ����ȫ�����飬
				//�������ֽ������
				//(1)������"return;"(��ã�����Ҫ�úÿ��ǽ�������)
				//(2)���ڡ�return;��ǰ����vis[i] = false;������ʾ
				//vis[i] = false; return;
				//(3)���������"vis[i] = true;"�����ݹ�ǰһ������ϡ�����primeCircle(cur+1)ǰ�����ϡ�vis[i] = true;��
				//return;
			}

			primeCircle(cur+1);
			vis[i] = false;
		}
	}
}


int main(void) {

	createPrimeList();
	primeCircle(2);

	return 0;
}