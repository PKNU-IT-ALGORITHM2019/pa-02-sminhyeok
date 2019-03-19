#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <time.h>
using namespace std;
int *visitX, * visitY, *index, *tour,N;;	//�湮�� x,y ��ǥ , �湮 ��ġ�� ��Ÿ�� index, ���� ũ��
bool *use;
float TSP(int k, float min);

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
		}// ���� �Է� �Ϸ�
		index[0] = 0;	// TSP �ݺ��� ���� �� ���� + ������ ��ġ�� ���� �ּұ��� ã�°� �������
		use[0] = true;

		cout << TSP(1,987654321.0) << "\n[";
		for (int j = 0; j < N; j++) {
			cout << tour[j] << " ";
		}
		cout << "]\n";

		end = clock();
		cout << "����ð� : " << (double)(end - begin) /1000<< "\n";
	}
}


float TSP(int k, float min) {
	if (k == N) {
		float sum = 0;
		for (int i = 0; i < N - 1; i++) {
			sum += sqrtf(powf(visitX[index[i]] - visitX[index[i + 1]], 2) + powf(visitY[index[i]] - visitY[index[i + 1]], 2));
			// ���� ������������ �ִܰŸ� ����
		}
		sum += sqrtf(powf(visitX[index[0]] - visitX[index[N - 1]], 2) + powf(visitY[index[0]] - visitY[index[N - 1]], 2));
		if (sum < min) {
			for (int i = 0; i < N; i++)
				tour[i] = index[i];
		}
		return sum;
	}
	else {
		float answer = min;
		for (int i = 1; i < N; i++) {
			if (!use[i]) {
				use[i] = true;
				index[k] = i;
				float temp = TSP(k + 1, answer);
				if (temp < answer) answer = temp;
				use[i] = false;
			}
		}
		return answer;
	}
}