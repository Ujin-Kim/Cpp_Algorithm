#include <iostream>
using namespace std;

int n, k;
int level;
int A[201];
int belt[201];

void rotation() {
	//��Ʈȸ��
	int temp = belt[2 * n];
	for (int i = 2 * n - 1; i >= 1; i--) {
		belt[i + 1] = belt[i];
	}
	belt[1] = temp;

	//������ ȸ��
	temp = A[2 * n];
	for (int i = 2 * n - 1; i >= 1; i--) {
		A[i + 1] = A[i];
	}
	A[1] = temp;
}

void remove() {
	if (belt[n] == 1) belt[n] = 0;
}

void robot_move() {
	for (int i = n - 1; i >= 1; i--) {
		if (belt[i] == 1 && belt[i+1] == 0 && A[i+1] >= 1) {
			belt[i + 1] = 1;
			belt[i] = 0;
			A[i + 1] -= 1;
		}
	}
}

void add_robot() {
	if (belt[1] == 0 && A[1] != 0) {
		belt[1] = 1;
		A[1] -= 1;
	}
}

bool check() {
	int cnt = 0;
	for (int i = 1; i <= 2 * n; i++) {
		if (A[i] == 0) cnt++;
	}
	if (cnt >= k) return true;
	else return false;
}

int main() {
	cin >> n >> k;
	for (int i = 1; i <= 2 * n; i++) {
		cin >> A[i];
	}

	while (1) {
		level++;

		//1. ��Ʈ ȸ��
		rotation();

		//1-1. ������ĭ�� �κ������� ����
		remove();

		//2. ���� ���� �ö� �κ����� ȸ���������� 1ĭ �̵�
		robot_move();

		//2-1. ������ĭ�� �κ������� ����
		remove();

		//3. �ø���ĭ�� �κ� �ø�
		add_robot();

		//������ 0��ĭ Ȯ��
		if(check()) break;
	}

	cout << level << "\n";

	return 0;
}