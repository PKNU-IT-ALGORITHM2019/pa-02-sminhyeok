#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <time.h>
using namespace std;
int *visitX, *visitY, *index, *tour, N;;	//방문할 x,y 좌표 , 방문 위치를 나타낼 index, 파일 크기
bool *use;
float answer;
void TSP(int k, float sum);

int main() {
	string file[7] = { "input0.txt" ,"input1.txt" ,"input2.txt" ,"input3.txt" ,"input4.txt" ,"input5.txt" ,"input6.txt" };
	for (int i = 0; i < 7; i++) {

		clock_t begin, end;
		begin = clock();

		ifstream fin(file[i]);
		if (!fin) { cout << "File Open Fail\n"; return 0; }

		fin >> N;
		visitX = new int[N];
		visitY = new int[N];
		index = new int[N];
		tour = new int[N];
		use = new bool[N];

		for (int i = 0; i < N; i++) {
			fin >> visitX[i] >> visitY[i];
			use[i] = false;
		}// 파일 입력 완료
		answer = 987654321.0;
		index[0] = 0;	// TSP 반복수 줄일 수 있음 + 임의의 위치가 어디든 최소길이 찾는건 상관없음
		use[0] = true;
		TSP(1, 0);
		
		cout << fixed;
		cout.precision(14);	// 소수점 14자리까지 출력
		cout << "#" << i+1 << "\n" <<  answer << "\n[";
		for (int j = 0; j < N; j++) {
			cout << tour[j] << " ";
		}
		cout << "]\n";

		end = clock();
		cout << "수행시간 : " << (double)(end - begin) / 1000 << "s\n";
	}
}


void TSP(int k, float sum) {
	if (sum > answer) return;
	if (k == N) {
		float temp = sum;
		temp += sqrtf(powf(visitX[index[0]] - visitX[index[N - 1]], 2) + powf(visitY[index[0]] - visitY[index[N - 1]], 2));
		if (temp < answer) {
			answer = temp;
			for (int i = 0; i < N; i++)
				tour[i] = index[i];
		}
		return ;
	}
	else {
		for (int i = 1; i < N; i++) {
			if (!use[i]) {
				float temp = sum;
				use[i] = true;
				index[k] = i;
				temp += sqrtf(powf(visitX[index[k]] - visitX[index[k - 1]], 2) + powf(visitY[index[k]] - visitY[index[k - 1]], 2));
				TSP(k + 1, temp);
				use[i] = false;
			}
		}
		return;
	}
}