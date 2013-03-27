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
				//注意：当没有全局数组vis时，可以添加return;但是如果使用了全局数组，
				//则有三种解决方案
				//(1)、不用"return;"(最好，但需要好好考虑结束条件)
				//(2)、在“return;”前，令vis[i] = false;如下所示
				//vis[i] = false; return;
				//(3)、将上面的"vis[i] = true;"调至递归前一条语句上。即在primeCircle(cur+1)前，加上“vis[i] = true;”
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