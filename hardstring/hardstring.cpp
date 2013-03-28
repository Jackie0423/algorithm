#include <IOSTREAM>
#include <IOMANIP>
using namespace std;

//输出字典序第N个数
const int N = 7;
//字符个数
const int L = 3;
//辅助数组
int s[N+1] = {0};

bool hardString(int cur) {
	if (cur == N) {
	
		for (int i=0; i<cur; i++) {
			printf("%c",'A'+s[i]);
		}
		cout<<endl;

		return true;
	}

	for (int i=0; i<L; i++) {
		s[cur] = i;
		bool ok = true;
		//j表示后缀比较长度
		for (int j=1; 2*j<=2*cur+1; j++) {
			bool equal = true;
			for (int k=0; k<j; k++) {
				if (s[cur-k] != s[cur-k-j]) {
					equal = false;
					break;
				}
			}
			if (equal) {
				ok = false;
				break;
			}
		}

		if (ok) {
			if(hardString(cur+1)) {
				return true;
			}
		}
	}

	return false;
}

int main(void) {

	hardString(0);

	return 0;
}