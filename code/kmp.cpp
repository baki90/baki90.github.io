#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

#define MAX 1000000
int pi[MAX];

void InitNext(string p)
{
	int i, j = 0, M = p.length();
	pi[0] = -1;
	for (i = 0, j = -1; i <= M; i++, j++) {
		pi[i] = j;
		while ((j >= 0) && (p[i] != p[j]))
			j = pi[j];
	}

}

vector<int> positions;

void KMP(string p, string t)
{
	int cnt = 0;
	int i, j, pos = 0, M = p.length(), N = t.length();
	InitNext(p);
	for (i = 0, j = 0; j < M && i < N; i++, j++) {
		while ((j >= 0) && (t[i] != p[j])) j = pi[j];
		if (j == M - 1) { //비교가 모두 이루어져 같은 상태가 됨
			j = pi[j] - 1; //(포문 끝나고 증가 방지)
			pos = i - (M - 1);  //중첩 시작 위치
			positions.push_back(pos); //맞은 부분 인덱스 삽입
			--i;//다음 턴에 i가 증가하므로, 현재부터 비교 시작
		}
	}
}



int main() {
	std::cin.tie(NULL);
	std::ios_base::sync_with_stdio(false);
	
	string file_name; //찾고자 하는 파일 이름
	string find; //찾고자 하는 단어
	string buffer; //파일 읽어옴
	string content;

	printf("quit: q\nplease write your file name: ");
	cin >> file_name;

	ifstream input(file_name); //읽기파일 열기

	if (!input.is_open()) {
		cout << "파일이 없습니다.\n";
	}
	else {
		while (!input.eof()) { //파일 끝인지 체크        
			getline(input, buffer); //엔터키까지 읽어들임
			buffer.append("\n"); //엔터키 추가하고
			content.append(buffer); //content에 담아놓음
		}
		input.close(); //파일닫기

		while (true) {
			cout << "찾고 싶은 단어를 입력해 주세요.\n";
			cin >> find;
			if (find.compare("q") == 0) break;
			KMP(find, content);
			if (!positions.empty()) {
				for (auto i : positions) {
					cout << i << " ";
				}
				cout << "에서 " << find << "찾았습니다.\n";
			}
			else cout << "찾고자 하는 단어가 없습니다.\n";
			positions.clear();
		}
	}

	
	
}
