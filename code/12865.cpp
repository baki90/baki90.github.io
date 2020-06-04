#include <iostream>
#include <algorithm>
using namespace std;

int dp[101][100001] = { 0, };
int N, K;
int W, V;

int items[101][2] = { 0, }; //item에 따른 0. 무게, 1. 가치

void print() {
	for (int i = 0; i <= N; i++) {
		for (int j = 0; j <= K; j++)
			cout << dp[i][j] << " ";
		cout << endl;
	}
}


int main() {
	cin >> N >> K;

	for (int i = 1; i <= N; i++) {
		cin >> W >> V;
		items[i][0] = W;
		items[i][1] = V;
	}
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= K; j++) {
			if (items[i][0] <= j) { //무게가 초과하지 않으면 그때의 아이템을 담는 것과, 이전 값을 비교해 본다.
				dp[i][j] = max(dp[i - 1][j], items[i][1] + dp[i - 1][j - items[i][0]]);
			}
			else { //초과해서 이전 값만을 취한다. (전에 넣었던 것 기준)
				dp[i][j] = dp[i - 1][j];
			}
		}
	}
	//print();
	cout << dp[N][K];
}
