#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <string.h>
#include <ctime>
#include <cstdlib>
#include<vector>

#define INT_MAX 2147483647
#define INT_MIN (-INT_MAX - 1)
#define BLACK 1
#define WHITE -1
const int SIZE = 11;
const int SON_NUM = 10;
bool choice_flag = false;
float weight[SIZE][SIZE] = { 0 };
const float my_value_gap = 2.5;
const float my_value = 2;
const float your_value_gap = 2;
const float your_value = 1.7;
int board[SIZE][SIZE] = { 0 };

using namespace std;

//输入输出重定向
//freopen("in.txt","r",stdin);
//freopen("out.txt","r",stdout);

class Solution {
private:
	class PointNode {
	public:
		int first = 0;
		int second = 0;
		PointNode* next = nullptr;
	};
	int extend_board[SIZE + 2][SIZE + 2] = { 0 };
	bool has_find[SIZE + 2][SIZE + 2] = { false };
	PointNode* our_neibor[SIZE * SIZE];
	PointNode* enemy_neibor[SIZE * SIZE];

	void findNeibor_1(int x, int y, int ours, PointNode* sentry) {
		has_find[x][y] = true;
		PointNode* now = sentry;
		if (x - 1 >= 0) {
			if (!has_find[x - 1][y]) {
				if (!extend_board[x - 1][y]) {
					has_find[x - 1][y] = true;
					PointNode* p = new PointNode;
					p->first = x - 1;
					p->second = y;
					now->next = p;
					now = p;
				}
				else if (extend_board[x - 1][y] == ours) {
					PointNode* another = new PointNode;
					findNeibor_1(x - 1, y, ours, another);
					now->next = another->next;
					while (now->next)
						now = now->next;
					delete another;
					another = nullptr;
				}
			}
			if (y + 1 < SIZE + 2) {
				if (!has_find[x - 1][y + 1]) {
					if (!extend_board[x - 1][y + 1]) {
						has_find[x - 1][y + 1] = true;
						PointNode* p = new PointNode;
						p->first = x - 1;
						p->second = y + 1;
						now->next = p;
						now = p;
					}
					else if (extend_board[x - 1][y + 1] == ours) {
						PointNode* another = new PointNode;
						findNeibor_1(x - 1, y + 1, ours, another);
						now->next = another->next;
						while (now->next)
							now = now->next;
						delete another;
						another = nullptr;
					}
				}
			}
		}
		if (y + 1 < SIZE + 2) {
			if (!has_find[x][y + 1]) {
				if (!extend_board[x][y + 1]) {
					has_find[x][y + 1] = true;
					PointNode* p = new PointNode;
					p->first = x;
					p->second = y + 1;
					now->next = p;
					now = p;
				}
				else if (extend_board[x][y + 1] == ours) {
					PointNode* another = new PointNode;
					findNeibor_1(x, y + 1, ours, another);
					now->next = another->next;
					while (now->next)
						now = now->next;
					delete another;
					another = nullptr;
				}
			}
		}
		if (x + 1 < SIZE + 2) {
			if (!has_find[x + 1][y]) {
				if (!extend_board[x + 1][y]) {
					has_find[x + 1][y] = true;
					PointNode* p = new PointNode;
					p->first = x + 1;
					p->second = y;
					now->next = p;
					now = p;
				}
				else if (extend_board[x + 1][y] == ours) {
					PointNode* another = new PointNode;
					findNeibor_1(x + 1, y, ours, another);
					now->next = another->next;
					while (now->next)
						now = now->next;
					delete another;
					another = nullptr;
				}
			}
			if (y - 1 >= 0) {
				if (!has_find[x + 1][y - 1]) {
					if (!extend_board[x + 1][y - 1]) {
						has_find[x + 1][y - 1] = true;
						PointNode* p = new PointNode;
						p->first = x + 1;
						p->second = y - 1;
						now->next = p;
						now = p;
					}
					else if (extend_board[x + 1][y - 1] == ours) {
						PointNode* another = new PointNode;
						findNeibor_1(x + 1, y - 1, ours, another);
						now->next = another->next;
						while (now->next)
							now = now->next;
						delete another;
						another = nullptr;
					}
				}
			}
		}
		if (y - 1 >= 0) {
			if (!has_find[x][y - 1]) {
				if (!extend_board[x][y - 1]) {
					has_find[x][y - 1] = true;
					PointNode* p = new PointNode;
					p->first = x;
					p->second = y - 1;
					now->next = p;
					now = p;
				}
				else if (extend_board[x][y - 1] == ours) {
					PointNode* another = new PointNode;
					findNeibor_1(x, y - 1, ours, another);
					now->next = another->next;
					while (now->next)
						now = now->next;
					delete another;
				}
			}
		}
		PointNode* first = sentry, * second = sentry->next;
		while (second) {
			if (second->first == x && second->second == y) {
				first->next = second->next;
				delete second;
				second = nullptr;
				second = first->next;
			}
			else if (second->first == 0 && second->second == 0) {
				first->next = second->next;
				delete second;
				second = nullptr;
				second = first->next;
			}
			else if (second->first == 0 && second->second == SIZE + 1) {
				first->next = second->next;
				delete second;
				second = nullptr;
				second = first->next;
			}
			else if (second->first == SIZE + 1 && second->second == 0) {
				first->next = second->next;
				delete second;
				second = nullptr;
				second = first->next;
			}
			else if (second->first == SIZE + 1 && second->second == SIZE + 1) {
				first->next = second->next;
				delete second;
				second = nullptr;
				second = first->next;
			}
			else {
				first = second;
				second = second->next;
			}
		}
	}

	void findNeibor(int x, int y, int ours, PointNode* sentry) {
		if (!extend_board[x][y] || (x == 1 || x == SIZE || y == 1 || y == SIZE)) {
			memset(has_find, 0, sizeof(has_find));
			findNeibor_1(x, y, ours, sentry);
		}
		else {
			findNeibor_2(x, y, ours, sentry);
		}
	}

	void findNeibor_2(int x, int y, int ours, PointNode* sentry) {
		if (extend_board[x][y - 1] == ours) {
			PointNode* p, * q;
			if (ours == 1) {
				p = our_neibor[(x - 1) * SIZE + y - 2];
				q = our_neibor[(x - 1) * SIZE + y - 1];
			}
			else {
				p = enemy_neibor[(x - 1) * SIZE + y - 2];
				q = enemy_neibor[(x - 1) * SIZE + y - 1];
			}
			while (p) {
				q->next = new PointNode;
				q->next->first = p->first;
				q->next->second = p->second;
				q = q->next;
				p = p->next;
			}
			return;
		}
		if (extend_board[x - 1][y] == ours) {
			PointNode* p, * q;
			if (ours == 1) {
				p = our_neibor[(x - 2) * SIZE + y - 1];
				q = our_neibor[(x - 1) * SIZE + y - 1];
			}
			else {
				p = enemy_neibor[(x - 2) * SIZE + y - 1];
				q = enemy_neibor[(x - 1) * SIZE + y - 1];
			}
			while (p) {
				q->next = new PointNode;
				q->next->first = p->first;
				q->next->second = p->second;
				q = q->next;
				p = p->next;
			}
			return;
		}
		if (extend_board[x - 1][y + 1] == ours) {
			PointNode* p, * q;
			if (ours == 1) {
				p = our_neibor[(x - 2) * SIZE + y];
				q = our_neibor[(x - 1) * SIZE + y - 1];
			}
			else {
				p = enemy_neibor[(x - 2) * SIZE + y];
				q = enemy_neibor[(x - 1) * SIZE + y - 1];
			}
			while (p) {
				q->next = new PointNode;
				q->next->first = p->first;
				q->next->second = p->second;
				q = q->next;
				p = p->next;
			}
			return;
		}
		memset(has_find, 0, sizeof(has_find));
		findNeibor_1(x, y, ours, sentry);
	}

	void countDoubleDis(int ans[][SIZE + 2], int ours, int color, int upper) {	//1为红，-1为蓝，upper相对轴
		for (int i = 1; i <= SIZE; ++i)
			for (int j = 1; j <= SIZE; ++j)
				ans[i][j] = INT_MAX;
		for (int i = 1; i <= SIZE; ++i)
			ans[0][i] = ans[i][0] = ans[SIZE + 1][i] = ans[i][SIZE + 1] = INT_MAX;
		bool flag;
		if (color == 1 && upper == 0) {
			for (int j = 1; j <= SIZE; ++j) {
				extend_board[j][0] = extend_board[j][SIZE + 1] = -ours;
				extend_board[SIZE + 1][j] = ours;
				ans[0][j] = extend_board[0][j] = 0;
				if (extend_board[1][j] == 0)
					ans[1][j] = 1;
			}
			for (int i = 2; i <= SIZE; ++i)
				for (int j = 1; j <= SIZE; ++j) {
					PointNode* p;
					if (ours == 1) {
						p = our_neibor[(i - 1) * SIZE + j - 1]->next;
						while (p) {
							PointNode* q = p;
							p = p->next;
							delete q;
						}
						our_neibor[(i - 1) * SIZE + j - 1]->next = nullptr;
						if (!extend_board[i][j] || extend_board[i][j] == 1)
							findNeibor(i, j, 1, our_neibor[(i - 1) * SIZE + j - 1]);
					}
					else {
						p = enemy_neibor[(i - 1) * SIZE + j - 1]->next;
						while (p) {
							PointNode* q = p;
							p = p->next;
							delete q;
						}
						enemy_neibor[(i - 1) * SIZE + j - 1]->next = nullptr;
						if (!extend_board[i][j] || extend_board[i][j] == -1)
							findNeibor(i, j, -1, enemy_neibor[(i - 1) * SIZE + j - 1]);
					}
				}
			while (true) {
				flag = false;
				for (int i = 2; i <= SIZE; ++i)
					for (int j = 1; j <= SIZE; ++j) {
						if (!extend_board[i][j]) {
							int min1 = INT_MAX, min2 = INT_MAX;
							PointNode* now;
							if (ours == 1)
								now = our_neibor[(i - 1) * SIZE + j - 1]->next;
							else
								now = enemy_neibor[(i - 1) * SIZE + j - 1]->next;
							while (now) {
								int x = now->first, y = now->second;
								if (ans[x][y] <= min1) {
									min2 = min1;
									min1 = ans[x][y];
								}
								else if (ans[x][y] <= min2)
									min2 = ans[x][y];
								now = now->next;
							}
							if (min2 != INT_MAX && min2 + 1 != ans[i][j]) {
								ans[i][j] = min2 + 1;
								flag = true;
							}
						}
					}
				if (!flag)
					break;
			}
		}
		else if (color == 1 && upper == 1) {
			for (int j = 1; j <= SIZE; ++j) {
				extend_board[j][0] = extend_board[j][SIZE + 1] = -ours;
				extend_board[0][j] = ours;
				ans[SIZE + 1][j] = extend_board[SIZE + 1][j] = 0;
				if (extend_board[SIZE][j] == 0)
					ans[SIZE][j] = 1;
			}
			for (int i = 1; i < SIZE; ++i)
				for (int j = 1; j <= SIZE; ++j) {
					PointNode* p;
					if (ours == 1) {
						p = our_neibor[(i - 1) * SIZE + j - 1]->next;
						while (p) {
							PointNode* q = p;
							p = p->next;
							delete q;
						}
						our_neibor[(i - 1) * SIZE + j - 1]->next = nullptr;
						if (!extend_board[i][j] || extend_board[i][j] == 1)
							findNeibor(i, j, 1, our_neibor[(i - 1) * SIZE + j - 1]);
					}
					else {
						p = enemy_neibor[(i - 1) * SIZE + j - 1]->next;
						while (p) {
							PointNode* q = p;
							p = p->next;
							delete q;
						}
						enemy_neibor[(i - 1) * SIZE + j - 1]->next = nullptr;
						if (!extend_board[i][j] || extend_board[i][j] == -1)
							findNeibor(i, j, -1, enemy_neibor[(i - 1) * SIZE + j - 1]);
					}
				}
			while (true) {
				flag = false;
				for (int i = SIZE - 1; i >= 1; --i)
					for (int j = SIZE; j >= 1; --j) {
						if (!extend_board[i][j]) {
							int min1 = INT_MAX, min2 = INT_MAX;
							PointNode* now;
							if (ours == 1)
								now = our_neibor[(i - 1) * SIZE + j - 1]->next;
							else
								now = enemy_neibor[(i - 1) * SIZE + j - 1]->next;
							while (now) {
								int x = now->first, y = now->second;
								if (ans[x][y] <= min1) {
									min2 = min1;
									min1 = ans[x][y];
								}
								else if (ans[x][y] <= min2)
									min2 = ans[x][y];
								now = now->next;
							}
							if (min2 != INT_MAX && min2 + 1 != ans[i][j]) {
								ans[i][j] = min2 + 1;
								flag = true;
							}
						}
					}
				if (!flag)
					break;
			}
		}
		else if (color == -1 && upper == 0) {
			for (int j = 1; j <= SIZE; ++j) {
				extend_board[0][j] = extend_board[SIZE + 1][j] = -ours;
				extend_board[j][SIZE + 1] = ours;
				ans[j][0] = extend_board[j][0] = 0;
				if (extend_board[j][1] == 0)
					ans[j][1] = 1;
			}
			for (int i = 1; i <= SIZE; ++i)
				for (int j = 2; j <= SIZE; ++j) {
					PointNode* p;
					if (ours == 1) {
						p = our_neibor[(i - 1) * SIZE + j - 1]->next;
						while (p) {
							PointNode* q = p;
							p = p->next;
							delete q;
						}
						our_neibor[(i - 1) * SIZE + j - 1]->next = nullptr;
						if (!extend_board[i][j] || extend_board[i][j] == 1)
							findNeibor(i, j, 1, our_neibor[(i - 1) * SIZE + j - 1]);
					}
					else {
						p = enemy_neibor[(i - 1) * SIZE + j - 1]->next;
						while (p) {
							PointNode* q = p;
							p = p->next;
							delete q;
						}
						enemy_neibor[(i - 1) * SIZE + j - 1]->next = nullptr;
						if (!extend_board[i][j] || extend_board[i][j] == -1)
							findNeibor(i, j, -1, enemy_neibor[(i - 1) * SIZE + j - 1]);
					}
				}
			while (true) {
				flag = false;
				for (int j = 2; j <= SIZE; ++j)
					for (int i = 1; i <= SIZE; ++i) {
						if (!extend_board[i][j]) {
							int min1 = INT_MAX, min2 = INT_MAX;
							PointNode* now;
							if (ours == 1)
								now = our_neibor[(i - 1) * SIZE + j - 1]->next;
							else
								now = enemy_neibor[(i - 1) * SIZE + j - 1]->next;
							while (now) {
								int x = now->first, y = now->second;
								if (ans[x][y] <= min1) {
									min2 = min1;
									min1 = ans[x][y];
								}
								else if (ans[x][y] <= min2)
									min2 = ans[x][y];
								now = now->next;
							}
							if (min2 != INT_MAX && min2 + 1 != ans[i][j]) {
								ans[i][j] = min2 + 1;
								flag = true;
							}
						}
					}
				if (!flag)
					break;
			}
		}
		else {
			for (int j = 1; j <= SIZE; ++j) {
				extend_board[0][j] = extend_board[SIZE + 1][j] = -ours;
				extend_board[j][0] = ours;
				ans[j][SIZE + 1] = extend_board[j][SIZE + 1] = 0;
				if (extend_board[j][SIZE] == 0)
					ans[j][SIZE] = 1;
			}
			for (int i = 1; i <= SIZE; ++i)
				for (int j = 1; j < SIZE; ++j) {
					PointNode* p;
					if (ours == 1) {
						p = our_neibor[(i - 1) * SIZE + j - 1]->next;
						while (p) {
							PointNode* q = p;
							p = p->next;
							delete q;
						}
						our_neibor[(i - 1) * SIZE + j - 1]->next = nullptr;
						if (!extend_board[i][j] || extend_board[i][j] == 1)
							findNeibor(i, j, 1, our_neibor[(i - 1) * SIZE + j - 1]);
					}
					else {
						p = enemy_neibor[(i - 1) * SIZE + j - 1]->next;
						while (p) {
							PointNode* q = p;
							p = p->next;
							delete q;
						}
						enemy_neibor[(i - 1) * SIZE + j - 1]->next = nullptr;
						if (!extend_board[i][j] || extend_board[i][j] == -1)
							findNeibor(i, j, -1, enemy_neibor[(i - 1) * SIZE + j - 1]);
					}
				}
			while (true) {
				flag = false;
				for (int j = SIZE - 1; j >= 1; --j)
					for (int i = SIZE; i >= 1; --i) {
						if (!extend_board[i][j]) {
							int min1 = INT_MAX, min2 = INT_MAX;
							PointNode* now;
							if (ours == 1)
								now = our_neibor[(i - 1) * SIZE + j - 1]->next;
							else
								now = enemy_neibor[(i - 1) * SIZE + j - 1]->next;
							while (now) {
								int x = now->first, y = now->second;
								if (ans[x][y] <= min1) {
									min2 = min1;
									min1 = ans[x][y];
								}
								else if (ans[x][y] <= min2)
									min2 = ans[x][y];
								now = now->next;
							}
							if (min2 != INT_MAX && min2 + 1 != ans[i][j]) {
								ans[i][j] = min2 + 1;
								flag = true;
							}
						}
					}
				if (!flag)
					break;
			}
		}
	}

public:

	int Valuation(int x, int y, bool flag) {
		extend_board[x + 1][y + 1] = (flag ? 1 : -1);
		int our_color = extend_board[2][3], enemy_color = -extend_board[2][3];
		int our_low[SIZE + 2][SIZE + 2], our_upper[SIZE + 2][SIZE + 2], enemy_low[SIZE + 2][SIZE + 2], enemy_upper[SIZE + 2][SIZE + 2];
		countDoubleDis(our_low, 1, our_color, 0);
		countDoubleDis(our_upper, 1, our_color, 1);
		countDoubleDis(enemy_low, -1, enemy_color, 0);
		countDoubleDis(enemy_upper, -1, enemy_color, 1);
		for (int i = 1; i <= SIZE; ++i)
			for (int j = 1; j <= SIZE; ++j) {
				if (our_low[i][j] != INT_MAX && our_upper[i][j] != INT_MAX)
					our_low[i][j] += our_upper[i][j];
				else
					our_low[i][j] = INT_MAX;
				if (enemy_low[i][j] != INT_MAX && enemy_upper[i][j] != INT_MAX)
					enemy_low[i][j] += enemy_upper[i][j];
				else
					enemy_low[i][j] = INT_MAX;
			}
		int our_p = INT_MAX, our_a = 1, enemy_p = INT_MAX, enemy_a = 1;
		for (int i = 1; i <= SIZE; ++i)
			for (int j = 1; j <= SIZE; ++j) {
				if (our_low[i][j] < our_p) {
					our_p = our_low[i][j];
					our_a = 1;
				}
				else if (our_low[i][j] == our_p)
					our_a++;
				if (enemy_low[i][j] < enemy_p) {
					enemy_p = enemy_low[i][j];
					enemy_a = 1;
				}
				else if (enemy_low[i][j] == enemy_p)
					enemy_a++;
			}
		extend_board[x + 1][y + 1] = 0;
		if (enemy_p == INT_MAX) {
			return INT_MAX;
		}
		return 100 * (enemy_p - our_p) - (enemy_a - our_a);
	}

	void judge_win() {
		int our_color = extend_board[2][3], enemy_color = -extend_board[2][3];
		int our_low[SIZE + 2][SIZE + 2], our_upper[SIZE + 2][SIZE + 2], enemy_low[SIZE + 2][SIZE + 2], enemy_upper[SIZE + 2][SIZE + 2];
		countDoubleDis(our_low, 1, our_color, 0);
		countDoubleDis(our_upper, 1, our_color, 1);
		countDoubleDis(enemy_low, -1, enemy_color, 0);
		countDoubleDis(enemy_upper, -1, enemy_color, 1);
		for (int i = 1; i <= SIZE; ++i)
			for (int j = 1; j <= SIZE; ++j) {
				if (our_low[i][j] != INT_MAX && our_upper[i][j] != INT_MAX)
					our_low[i][j] += our_upper[i][j];
				else
					our_low[i][j] = INT_MAX;
				if (enemy_low[i][j] != INT_MAX && enemy_upper[i][j] != INT_MAX)
					enemy_low[i][j] += enemy_upper[i][j];
				else
					enemy_low[i][j] = INT_MAX;
			}
		int our_p = INT_MAX, our_a = 1, enemy_p = INT_MAX, enemy_a = 1;
		for (int i = 1; i <= SIZE; ++i)
			for (int j = 1; j <= SIZE; ++j) {
				if (our_low[i][j] < our_p) {
					our_p = our_low[i][j];
					our_a = 1;
				}
				else if (our_low[i][j] == our_p)
					our_a++;
				if (enemy_low[i][j] < enemy_p) {
					enemy_p = enemy_low[i][j];
					enemy_a = 1;
				}
				else if (enemy_low[i][j] == enemy_p)
					enemy_a++;
			}
		if (enemy_p == INT_MAX) {
			choice_flag = true;
		}
	}

	void Set(int board[][SIZE]) {
		for (int i = 0; i < SIZE; ++i)
			for (int j = 0; j < SIZE; ++j)
				extend_board[i + 1][j + 1] = board[i][j];
	}

	Solution() {
		for (int i = 0; i < SIZE * SIZE; ++i) {
			our_neibor[i] = new PointNode;
			enemy_neibor[i] = new PointNode;
		}
	}

	~Solution() {
		for (int i = 0; i < SIZE * SIZE; ++i) {
			PointNode* p = our_neibor[i];
			while (p) {
				PointNode* q = p;
				p = p->next;
				delete q;
			}
			p = enemy_neibor[i];
			while (p) {
				PointNode* q = p;
				p = p->next;
				delete q;
			}
		}
	}
};

void sort(int value[][3]) {
	int bound = SIZE * SIZE - 1;
	bool flag = true;
	while (flag) {
		flag = false;
		for (int i = 0; i < bound; ++i) {
			if (value[i][0] < value[i + 1][0]) {
				int tempv = value[i][0];
				int tempx = value[i][1];
				int tempy = value[i][2];
				value[i][0] = value[i + 1][0];
				value[i][1] = value[i + 1][1];
				value[i][2] = value[i + 1][2];
				value[i + 1][0] = tempv;
				value[i + 1][1] = tempx;
				value[i + 1][2] = tempy;
				flag = true;
			}
		}
	}
	return;
}

class Gametree {
private:
	class Node {//博弈树节点
	public:
		Solution solution;
		int value_pernode[SIZE * SIZE][3];
		int value;
		Node* children[SON_NUM] = {};
		int x, y;
		int board[SIZE][SIZE]{};

		Node() {
			for (int i = 0; i < SIZE * SIZE; i++) {
				value_pernode[i][0] = INT_MIN;
				value_pernode[i][1] = -1;
				value_pernode[i][2] = -1;
			}
			value = INT_MIN;
			x = y = 0;
			memset(board, 0, sizeof(board));
		}
		Node(Node* node, int a, int b, int val) {
			for (int i = 0; i < SIZE * SIZE; i++) {
				value_pernode[i][0] = INT_MIN;
				value_pernode[i][1] = -1;
				value_pernode[i][2] = -1;
			}
			value = val;
			x = a;
			y = b;
			memcpy(board, node->board, sizeof(board));
			board[x][y] = 1;
		}

		void extend_down() {

			solution.Set(board);
			for (int i = 0; i < SIZE; i++)
				for (int j = 0; j < SIZE; j++) {
					if (board[i][j] == 0) {
						value_pernode[i * SIZE + j][0] = solution.Valuation(i, j, true);
						value_pernode[i * SIZE + j][1] = i;
						value_pernode[i * SIZE + j][2] = j;
					}

				}
			sort(value_pernode);

			for (int i = 0; i < SON_NUM; i++) {
				children[i] = new Node(this, value_pernode[i][1], value_pernode[i][2], value_pernode[i][0]);
			}

		}
		/// <summary>
		/// /////////////////////////////////////////////////////INT_MAX制胜
		/// </summary>
		void return_up() {

			board[x][y] = 1;
			solution.Set(board);
			for (int i = 0; i < SIZE; i++)
				for (int j = 0; j < SIZE; j++) {
					if (board[i][j] == 0) {
						value_pernode[i * SIZE + j][0] = solution.Valuation(i, j, false);
						value_pernode[i * SIZE + j][1] = i;
						value_pernode[i * SIZE + j][2] = j;
					}

				}
			board[x][y] = 0;//棋盘复原
			sort(value_pernode);
			int i = SIZE * SIZE - 1;
			while (value_pernode[i][1] == -1 && i > 0) {
				i--;
			}
			value = value_pernode[i][0];//更改权值
		}

	};

	Node* node_root = new Node();

public:
	Gametree(int(&board)[SIZE][SIZE], int x, int y) {
		memcpy(node_root->board, board, sizeof(board));
		node_root->x = x;
		node_root->y = y;
	}
	pair<int, int> game() {
		node_root->extend_down();
		for (int i = 0; i < SON_NUM; i++) {
			node_root->children[i]->return_up();
		}
		int max_value = INT_MIN;
		pair<int, int> ans(-1, -1);
		for (int i = 0; i < SON_NUM; i++) {
			if (node_root->children[i]->value > max_value) {
				max_value = node_root->children[i]->value;
				ans.first = node_root->children[i]->x;
				ans.second = node_root->children[i]->y;
			}

		}
		return ans;

	}

	void test() {
		for (int i = 0; i < SON_NUM; i++) {
			cout << "(" << node_root->children[i]->x << "," << node_root->children[i]->y << ") :" << node_root->children[i]->value << endl;
		}
	}
};

bool islegal(int x, int y) {//判断是否可落子
	if (x >= 0 && x < SIZE && y >= 0 && y < SIZE) {
		if (board[x][y] == 0)
			return true;
	}
	else
		return false;

}
bool inBoard(int x, int y) {
	return x >= 0 && y >= 0 && x < SIZE&& y < SIZE;
}
void change_value(int x, int y, bool mine) {
	if (mine) {
		/*if (islegal(x, y + 1))
			weight[x][y + 1] += my_value;
		if (islegal(x - 1, y + 1))
			weight[x - 1][y + 1] += my_value;
		if (islegal(x - 1, y))
			weight[x - 1][y] += my_value;
		if (islegal(x, y + 1))
			weight[x][y + 1] += my_value;
		if (islegal(x +1, y- 1))
			weight[x + 1][y - 1] += my_value;
		if (islegal(x + 1, y ))
			weight[x + 1][y ] += my_value;*/


		if (islegal(x + 1, y + 1))
			weight[x + 1][y + 1] += my_value_gap;
		if (islegal(x - 1, y + 2))
			weight[x - 1][y + 2] += my_value_gap;
		if (islegal(x - 2, y + 1))
			weight[x - 2][y + 1] += my_value_gap;
		if (islegal(x - 1, y - 1))
			weight[x - 1][y - 1] += my_value_gap;
		if (islegal(x + 1, y - 2))
			weight[x + 1][y - 2] += my_value_gap;
		if (islegal(x + 2, y - 1))
			weight[x + 2][y - 1] += my_value_gap;
	}
	else {
		/*if (islegal(x, y + 1))
			weight[x][y + 1] += your_value;
		if (islegal(x - 1, y + 1))
			weight[x - 1][y + 1] += your_value;
		if (islegal(x - 1, y))
			weight[x - 1][y] += your_value;
		if (islegal(x, y + 1))
			weight[x][y + 1] += your_value;
		if (islegal(x + 1, y - 1))
			weight[x + 1][y - 1] += your_value;
		if (islegal(x + 1, y))
			weight[x + 1][y] += your_value;*/


		if (islegal(x + 1, y + 1))
			weight[x + 1][y + 1] += your_value_gap;
		if (islegal(x - 1, y + 2))
			weight[x - 1][y + 2] += your_value_gap;
		if (islegal(x - 2, y + 1))
			weight[x - 2][y + 1] += your_value_gap;
		if (islegal(x - 1, y - 1))
			weight[x - 1][y - 1] += your_value_gap;
		if (islegal(x + 1, y - 2))
			weight[x + 1][y - 2] += your_value_gap;
		if (islegal(x + 2, y - 1))
			weight[x + 2][y - 1] += your_value_gap;
	}

}


int gap(int& x, int& y)
{
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++) {
			if (i < 2)
				weight[i][j] = (15 - j) / 10;
			else
				if (j < 2)
					weight[i][j] = (15 - i) / 10;
				else
					weight[i][j] = (20 - max(i, j)) / 10;
		}
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++) {
			if (board[i][j] == 1) {
				change_value(i, j, true);
			}
			else
				if (board[i][j] == -1) {
					change_value(i, j, false);
				}
		}
	float max_wei = 0;
	int& new_x = x;
	int& new_y = y;
	if (board[1][2] != 1) {



		for (int j = 10; j >= 0; j--)
			for (int i = 10; i >= 0; i--)
			{

				if (board[i][j] == 1) {
					if (inBoard(i - 1, j + 2) && board[i - 1][j + 2] == 1 && ((board[i - 1][j + 1] == -1 && inBoard(i - 1, j + 1)) || (inBoard(i, j + 1) && board[i][j + 1] == -1))) {
						if (board[i - 1][j + 1] == -1 && islegal(i, j + 1)) {
							new_x = i;
							new_y = j + 1;

							return 0;
						}
						else if (board[i][j + 1] == -1 && islegal(i - 1, j + 1)) {
							new_x = i - 1;
							new_y = j + 1;

							return 0;
						}
					}
					if (inBoard(i - 2, j + 1) && board[i - 2][j + 1] == 1 && inBoard(i - 1, j) && inBoard(i - 1, j + 1) && (board[i - 1][j] == -1 || board[i - 1][j + 1] == -1)) {
						if (board[i - 1][j] == -1 && islegal(i - 1, j + 1)) {
							new_x = i - 1;
							new_y = j + 1;

							return 0;
						}
						else if (board[i - 1][j + 1] == -1 && islegal(i - 1, j)) {
							new_x = i - 1;
							new_y = j;

							return 0;
						}
					}
					if (inBoard(i - 1, j - 1) && inBoard(i - 1, j) && inBoard(i, j - 1) && board[i - 1][j - 1] == 1 && (board[i - 1][j] == -1 || board[i][j - 1] == -1)) {
						if (board[i - 1][j] == -1 && islegal(i, j - 1)) {
							new_x = i;
							new_y = j - 1;

							return 0;
						}
						else if (board[i][j - 1] == -1 && islegal(i - 1, j)) {
							new_x = i - 1;
							new_y = j;

							return 0;
						}
					}
					if (inBoard(i + 1, j - 2) && inBoard(i + 1, j - 1) && inBoard(i, j - 1) && board[i + 1][j - 2] == 1 && (board[i + 1][j - 1] == -1 || board[i][j - 1] == -1)) {
						if (board[i + 1][j - 1] == -1 && islegal(i, j - 1)) {
							new_x = i;
							new_y = j - 1;

							return 0;
						}
						else if (board[i][j - 1] == -1 && islegal(i + 1, j - 1)) {
							new_x = i + 1;
							new_y = j - 1;

							return 0;
						}
					}
					if (inBoard(i + 2, j - 1) && inBoard(i + 1, j - 1) && inBoard(i + 1, j) && board[i + 2][j - 1] == 1 && (board[i + 1][j - 1] == -1 || board[i + 1][j] == -1)) {
						if (board[i + 1][j - 1] == -1 && islegal(i + 1, j)) {
							new_x = i + 1;
							new_y = j;

							return 0;
						}
						else if (board[i + 1][j] == -1 && islegal(i + 1, j - 1)) {
							new_x = i + 1;
							new_y = j - 1;

							return 0;
						}
					}
					if (inBoard(i + 1, j + 1) && inBoard(i, j + 1) && inBoard(i + 1, j) && board[i + 1][j + 1] == 1 && (board[i][j + 1] == -1 || board[i + 1][j] == -1)) {
						if (board[i][j + 1] == -1 && islegal(i + 1, j)) {
							new_x = i + 1;
							new_y = j;

							return 0;
						}
						else if (board[i + 1][j] == -1 && islegal(i, j + 1)) {
							new_x = i;
							new_y = j + 1;

							return 0;
						}
					}
				}
			}





		for (int i = 0; i < SIZE; i++)
			for (int j = 0; j < SIZE; j++) {

				if (j == 2 && i != 10 && board[i][j] == 1 && board[i][j - 1] == 0 && board[i + 1][j - 1] == 0 && inBoard(i + 1, j - 1) && board[i + 1][0] == 0 && inBoard(i + 1, 0) && islegal(i + 1, 0)) {
					new_x = i + 1;
					new_y = 0;

					return 0;
				}
			}

		for (int i = 0; i < SIZE; i++)
			for (int j = 0; j < SIZE; j++) {

				if (j == 8 && i != 0 && board[i][j] == 1 && board[i][j + 1] == 0 && board[i - 1][j + 1] == 0 && inBoard(i - 1, j + 1) && board[i - 1][10] == 0 && islegal(i - 1, 10)) {
					new_x = i - 1;
					new_y = 10;

					return 0;
				}
			}
		int dddd = 0;
		for (int i = 0; i < SIZE; i++) {
			if (board[i][0] == 1)
				dddd = 1;
		}
		if (dddd == 0)
			for (int i = 0; i < SIZE; i++)
				for (int j = 0; j < SIZE; j++) {

					if (j == 1 && i != 10 && board[i][j] == 1 && (board[i][j - 1] == 0 || (board[i + 1][j - 1] == 0 && inBoard(i + 1, j - 1)))) {
						if (board[i][j - 1] == 0 && islegal(i, j - 1)) {
							new_x = i;
							new_y = j - 1;

							return 0;
						}
						else if (board[i + 1][j - 1] == 0 && islegal(i + 1, j - 1)) {
							new_x = i + 1;
							new_y = j - 1;

							return 0;
						}
					}
				}
		int ddd = 0;
		for (int i = 0; i < SIZE; i++) {
			if (board[i][10] == 1)
				ddd = 1;
		}
		if (ddd == 0)
			for (int i = 0; i < SIZE; i++)
				for (int j = 0; j < SIZE; j++) {

					if (j == 9 && i != 0 && board[i][j] == 1 && (board[i][j + 1] == 0 || (inBoard(i - 1, j + 1) && board[i - 1][j + 1] == 0))) {
						if (board[i][j + 1] == 0 && islegal(i, j + 1)) {
							new_x = i;
							new_y = j + 1;

							return 0;
						}
						else if (board[i - 1][j + 1] == 0 && islegal(i - 1, j + 1)) {
							new_x = i - 1;
							new_y = j + 1;

							return 0;
						}
					}
				}
		for (int j = 10; j >= 0; j--)
			for (int i = 10; i >= 0; i--)
			{

				if (board[i][j] == 1) {
					if (inBoard(i - 1, j + 1) && inBoard(i, j + 1) && board[i - 1][j + 1] == -1 && board[i][j + 1] == 0) {
						if (islegal(i, j + 1)) {
							new_x = i;
							new_y = j + 1;

							return 0;
						}
					}
					if (inBoard(i, j + 1) && inBoard(i - 1, j + 1) && board[i][j + 1] == -1 && board[i - 1][j + 1] == 0) {
						if (islegal(i - 1, j + 1)) {
							new_x = i - 1;
							new_y = j + 1;

							return 0;
						}
					}
					if (inBoard(i, j + 1) && inBoard(i + 1, j) && board[i][j + 1] == -1 && board[i + 1][j] == 0) {
						if (islegal(i + 1, j)) {
							new_x = i + 1;
							new_y = j;

							return 0;
						}
					}
					if (inBoard(i + 1, j) && inBoard(i, j + 1) && board[i + 1][j] == -1 && board[i][j + 1] == 0) {
						if (islegal(i, j + 1)) {
							new_x = i;
							new_y = j + 1;

							return 0;
						}
					}
				}
			}
		for (int j = 10; j > -1; j--)
			for (int i = 0; i < SIZE; i++)
			{

				if (board[i][j] == 1) {

					if (inBoard(i - 1, j + 2) && inBoard(i - 1, j + 1) && inBoard(i, j + 1) && board[i - 1][j + 2] == 0 && board[i - 1][j + 1] == 0 && board[i][j + 1] == 0 && islegal(i - 1, j + 2)) {
						new_x = i - 1;
						new_y = j + 2;

						return 0;
					}
					if (inBoard(i - 2, j + 1) && inBoard(i - 1, j) && inBoard(i - 1, j + 1) && board[i - 2][j + 1] == 0 && board[i - 1][j] == 0 && board[i - 1][j + 1] == 0 && islegal(i - 2, j + 1)) {
						new_x = i - 2;
						new_y = j + 1;

						return 0;
					}
					if (inBoard(i + 1, j + 1) && inBoard(i, j + 1) && inBoard(i + 1, j) && board[i + 1][j + 1] == 0 && board[i][j + 1] == 0 && board[i + 1][j] == 0 && islegal(i + 1, j + 1)) {
						new_x = i + 1;
						new_y = j + 1;

						return 0;
					}
					if (inBoard(i + 2, j - 1) && inBoard(i + 1, j - 1) && inBoard(i + 1, j) && board[i + 2][j - 1] == 0 && board[i + 1][j - 1] == 0 && board[i + 1][j] == 0 && islegal(i + 2, j - 1)) {
						new_x = i + 2;
						new_y = j - 1;

						return 0;
					}
					if (inBoard(i - 1, j - 1) && inBoard(i - 1, j) && inBoard(i, j - 1) && board[i - 1][j - 1] == 0 && board[i - 1][j] == 0 && board[i][j - 1] == 0 && islegal(i - 1, j - 1)) {
						new_x = i - 1;
						new_y = j - 1;

						return 0;
					}
					if (inBoard(i + 1, j - 2) && inBoard(i + 1, j - 2) && inBoard(i, j - 1) && board[i + 1][j - 2] == 0 && board[i + 1][j - 1] == 0 && board[i][j - 1] == 0 && islegal(i + 1, j - 2)) {
						new_x = i + 1;
						new_y = j - 2;

						return 0;
					}


				}
			}




		for (int i = 10; i >= 0; i--)
			for (int j = 10; j >= 0; j--) {

				if (board[i][j] == 1) {
					if (inBoard(i - 1, j + 2) && inBoard(i - 1, j + 1) && inBoard(i, j + 1) && board[i - 1][j + 2] == 1 && (board[i - 1][j + 1] == 0 || board[i][j + 1] == 0)) {
						if (board[i - 1][j + 1] == 0 && islegal(i - 1, j + 1)) {
							new_x = i - 1;
							new_y = j + 1;

							return 0;
						}
						else if (board[i][j + 1] == 0 && islegal(i, j + 1)) {
							new_x = i;
							new_y = j + 1;

							return 0;
						}
					}
					if (inBoard(i + 1, j + 1) && inBoard(i, j + 1) && inBoard(i + 1, j) && board[i + 1][j + 1] == 1 && (board[i][j + 1] == 0 || board[i + 1][j] == 0)) {
						if (board[i][j + 1] == 0 && islegal(i, j + 1)) {
							new_x = i;
							new_y = j + 1;

							return 0;
						}
						else if (board[i + 1][j] == 0 && islegal(i + 1, j)) {
							new_x = i + 1;
							new_y = j;

							return 0;
						}
					}
					if (inBoard(i - 2, j + 1) && inBoard(i - 1, j) && inBoard(i - 1, j + 1) && board[i - 2][j + 1] == 1 && (board[i - 1][j] == 0 || board[i - 1][j + 1] == 0)) {
						if (board[i - 1][j] == 0 && islegal(i - 1, j)) {
							new_x = i - 1;
							new_y = j;

							return 0;
						}
						else if (board[i - 1][j + 1] == 0 && islegal(i - 1, j + 1)) {
							new_x = i - 1;
							new_y = j + 1;

							return 0;
						}
					}
					if (inBoard(i - 1, j - 1) && inBoard(i - 1, j) && inBoard(i, j - 1) && board[i - 1][j - 1] == 1 && (board[i - 1][j] == 0 || board[i][j - 1] == 0)) {
						if (board[i - 1][j] == 0 && islegal(i - 1, j)) {
							new_x = i - 1;
							new_y = j;

							return 0;
						}
						else if (board[i][j - 1] == 0 && islegal(i, j - 1)) {
							new_x = i;
							new_y = j - 1;

							return 0;
						}
					}
					if (inBoard(i + 1, j - 2) && inBoard(i + 1, j - 1) && inBoard(i, j - 1) && board[i + 1][j - 2] == 1 && (board[i + 1][j - 1] == 0 || board[i][j - 1] == 0)) {
						if (board[i + 1][j - 1] == 0 && islegal(i + 1, j - 1)) {
							new_x = i + 1;
							new_y = j - 1;

							return 0;
						}
						else if (board[i][j - 1] == 0 && islegal(i, j - 1)) {
							new_x = i;
							new_y = j - 1;

							return 0;
						}
					}
					if (inBoard(i + 2, j - 1) && inBoard(i + 1, j - 1) && inBoard(i + 1, j) && board[i + 2][j - 1] == 1 && (board[i + 1][j - 1] == 0 || board[i + 1][j] == 0)) {
						if (board[i + 1][j - 1] == 0 && islegal(i + 1, j - 1)) {
							new_x = i + 1;
							new_y = j - 1;

							return 0;
						}
						else if (board[i + 1][j] == 0 && islegal(i + 1, j)) {
							new_x = i + 1;
							new_y = j;

							return 0;
						}
					}
				}
			}
		for (int i = 0; i < SIZE; i++)
			for (int j = 0; j < SIZE; j++) {
				if (islegal(i, j) && board[i][j] == 0) {
					if (weight[i][j] > max_wei) {
						cout << "scc" << endl;
						max_wei = weight[i][j];
						new_x = i;
						new_y = j;
					}
					else if (weight[i][j] == max_wei) {
						if (board[1][2] == 1 && j < new_y) {
							cout << "cewf" << endl;
							new_x = i;
							new_y = j;
						}
						else if (board[i][j] == -1 && i > new_x == i) {
							new_x = i;
							new_y = j;
						}
					}
				}
			}
	}

	if (board[1][2] == 1) {
		for (int i = 10; i >= 0; i--)
			for (int j = 10; j >= 0; j--) {
				if (board[i][j] == 1) {
					if (inBoard(i - 1, j + 2) && board[i - 1][j + 2] == 1 && ((board[i - 1][j + 1] == -1 && inBoard(i - 1, j + 1)) || (inBoard(i, j + 1) && board[i][j + 1] == -1))) {
						if (board[i - 1][j + 1] == -1 && islegal(i, j + 1)) {
							new_x = i;
							new_y = j + 1;

							return 0;
						}
						else if (board[i][j + 1] == -1 && islegal(i - 1, j + 1)) {
							new_x = i - 1;
							new_y = j + 1;

							return 0;
						}
					}
					if (inBoard(i - 2, j + 1) && board[i - 2][j + 1] == 1 && inBoard(i - 1, j) && inBoard(i - 1, j + 1) && (board[i - 1][j] == -1 || board[i - 1][j + 1] == -1)) {
						if (board[i - 1][j] == -1 && islegal(i - 1, j + 1)) {
							new_x = i - 1;
							new_y = j + 1;

							return 0;
						}
						else if (board[i - 1][j + 1] == -1 && islegal(i - 1, j)) {
							new_x = i - 1;
							new_y = j;

							return 0;
						}
					}
					if (inBoard(i - 1, j - 1) && inBoard(i - 1, j) && inBoard(i, j - 1) && board[i - 1][j - 1] == 1 && (board[i - 1][j] == -1 || board[i][j - 1] == -1)) {
						if (board[i - 1][j] == -1 && islegal(i, j - 1)) {
							new_x = i;
							new_y = j - 1;

							return 0;
						}
						else if (board[i][j - 1] == -1 && islegal(i - 1, j)) {
							new_x = i - 1;
							new_y = j;

							return 0;
						}
					}
					if (inBoard(i + 1, j - 2) && inBoard(i + 1, j - 1) && inBoard(i, j - 1) && board[i + 1][j - 2] == 1 && (board[i + 1][j - 1] == -1 || board[i][j - 1] == -1)) {
						if (board[i + 1][j - 1] == -1 && islegal(i, j - 1)) {
							new_x = i;
							new_y = j - 1;

							return 0;
						}
						else if (board[i][j - 1] == -1 && islegal(i + 1, j - 1)) {
							new_x = i + 1;
							new_y = j - 1;

							return 0;
						}
					}
					if (inBoard(i + 2, j - 1) && inBoard(i + 1, j - 1) && inBoard(i + 1, j) && board[i + 2][j - 1] == 1 && (board[i + 1][j - 1] == -1 || board[i + 1][j] == -1)) {
						if (board[i + 1][j - 1] == -1 && islegal(i + 1, j)) {
							new_x = i + 1;
							new_y = j;

							return 0;
						}
						else if (board[i + 1][j] == -1 && islegal(i + 1, j - 1)) {
							new_x = i + 1;
							new_y = j - 1;

							return 0;
						}
					}
					if (inBoard(i + 1, j + 1) && inBoard(i, j + 1) && inBoard(i + 1, j) && board[i + 1][j + 1] == 1 && (board[i][j + 1] == -1 || board[i + 1][j] == -1)) {
						if (board[i][j + 1] == -1 && islegal(i + 1, j)) {
							new_x = i + 1;
							new_y = j;

							return 0;
						}
						else if (board[i + 1][j] == -1 && islegal(i, j + 1)) {
							new_x = i;
							new_y = j + 1;

							return 0;
						}
					}
				}
			}

		for (int i = 10; i >= 0; i--)
			for (int j = 10; j >= 0; j--) {
				if (j != 10 && i == 2 && board[i][j] == 1 && board[i - 1][j + 1] == 0 && board[i - 1][j] == 0 && inBoard(0, j - 1) && board[0][j - 1] == 0 && islegal(0, j - 1)) {
					new_x = 0;
					new_y = j - 1;

					return 0;
				}
			}

		for (int i = 10; i >= 0; i--)
			for (int j = 10; j >= 0; j--) {
				if (j != 0 && i == 8 && board[i][j] == 1 && board[i + 1][j - 1] == 0 && board[i + 1][j] == 0 && inBoard(i + 2, j - 1) && board[i + 2][j - 1] == 0 && islegal(i + 2, j - 1)) {
					new_x = i + 2;
					new_y = j - 1;

					return 0;
				}
			}
		int dddd = 0;
		for (int j = 0; j < SIZE; j++) {
			if (board[0][j] == 1)
				dddd = 1;
		}
		if (dddd == 0)
			for (int i = 10; i >= 0; i--)
				for (int j = 10; j >= 0; j--) {
					if (j != 10 && i == 1 && board[i][j] == 1 && (board[i - 1][j] == 0 || (inBoard(i - 1, j + 1) && board[i - 1][j + 1] == 0))) {
						if (board[i - 1][j] == 0 && islegal(i - 1, j)) {
							new_x = i - 1;
							new_y = j;

							return 0;
						}
						else if (board[i - 1][j + 1] == 0 && islegal(i - 1, j + 1)) {
							new_x = i - 1;
							new_y = j + 1;

							return 0;
						}
					}
				}
		int ddd = 0;
		for (int j = 0; j < SIZE; j++) {
			if (board[10][j] == 1)
				ddd = 1;
		}
		if (ddd == 0)
			for (int i = 10; i >= 0; i--)
				for (int j = 10; j >= 0; j--) {
					if (j != 0 && i == 9 && board[i][j] == 1 && (board[i + 1][j] == 0 || (inBoard(i + 1, j - 1) && board[i + 1][j - 1] == 0))) {
						if (board[i + 1][j] == 0 && islegal(i + 1, j)) {
							new_x = i + 1;
							new_y = j;

							return 0;
						}
						else if (board[i + 1][j - 1] == 0 && islegal(i + 1, j - 1)) {
							new_x = i + 1;
							new_y = j - 1;

							return 0;
						}
					}
				}

		for (int i = 10; i >= 0; i--)
			for (int j = 10; j >= 0; j--) {
				if (board[i][j] == 1) {
					if (inBoard(i + 1, j) && inBoard(i + 1, j - 1) && board[i + 1][j - 1] == -1 && board[i + 1][j] == 0) {
						if (islegal(i + 1, j)) {
							new_x = i + 1;
							new_y = j;

							return 0;
						}
					}
					if (inBoard(i + 1, j) && inBoard(i, j + 1) && board[i + 1][j] == -1 && board[i][j + 1] == 0) {
						if (islegal(i, j + 1)) {
							new_x = i;
							new_y = j + 1;

							return 0;
						}
					}
					if (inBoard(i + 1, j) && inBoard(i, j + 1) && board[i][j + 1] == -1 && board[i + 1][j] == 0) {
						if (islegal(i + 1, j)) {
							new_x = i + 1;
							new_y = j;

							return 0;
						}
					}
				}
			}
		for (int i = 10; i >= 0; i--)
			for (int j = 10; j >= 0; j--) {
				if (board[i][j] == 1) {
					if (inBoard(i + 1, j + 1) && inBoard(i, j + 1) && inBoard(i + 1, j) && board[i + 1][j + 1] == 0 && board[i][j + 1] == 0 && board[i + 1][j] == 0 && islegal(i + 1, j + 1)) {
						new_x = i + 1;
						new_y = j + 1;

						return 0;
					}
					if (inBoard(i + 2, j - 1) && inBoard(i + 1, j - 1) && inBoard(i + 1, j) && board[i + 2][j - 1] == 0 && board[i + 1][j - 1] == 0 && board[i + 1][j] == 0 && islegal(i + 2, j - 1)) {
						new_x = i + 2;
						new_y = j - 1;

						return 0;
					}
					if (inBoard(i - 1, j + 2) && inBoard(i - 1, j + 1) && inBoard(i, j + 1) && board[i - 1][j + 2] == 0 && board[i - 1][j + 1] == 0 && board[i][j + 1] == 0 && islegal(i - 1, j + 2)) {
						new_x = i - 1;
						new_y = j + 2;

						return 0;
					}
					if (inBoard(i - 2, j + 1) && inBoard(i - 1, j) && inBoard(i - 1, j + 1) && board[i - 2][j + 1] == 0 && board[i - 1][j] == 0 && board[i - 1][j + 1] == 0 && islegal(i - 2, j + 1)) {
						new_x = i - 2;
						new_y = j + 1;

						return 0;
					}
					if (inBoard(i - 1, j - 1) && inBoard(i - 1, j) && inBoard(i, j - 1) && board[i - 1][j - 1] == 0 && board[i - 1][j] == 0 && board[i][j - 1] == 0 && islegal(i - 1, j - 1)) {
						new_x = i - 1;
						new_y = j - 1;

						return 0;
					}
					if (inBoard(i + 1, j - 2) && inBoard(i + 1, j - 2) && inBoard(i, j - 1) && board[i + 1][j - 2] == 0 && board[i + 1][j - 1] == 0 && board[i][j - 1] == 0 && islegal(i + 1, j - 2)) {
						new_x = i + 1;
						new_y = j - 2;

						return 0;
					}


				}
			}



		for (int i = 10; i >= 0; i--)
			for (int j = 10; j >= 0; j--) {
				if (board[i][j] == 1) {
					if (inBoard(i - 1, j + 2) && inBoard(i - 1, j + 1) && inBoard(i, j + 1) && board[i - 1][j + 2] == 1 && (board[i - 1][j + 1] == 0 || board[i][j + 1] == 0)) {
						if (board[i - 1][j + 1] == 0 && islegal(i - 1, j + 1)) {
							new_x = i - 1;
							new_y = j + 1;

							return 0;
						}
						else if (board[i][j + 1] == 0 && islegal(i, j + 1)) {
							new_x = i;
							new_y = j + 1;

							return 0;
						}
					}
					if (inBoard(i + 1, j + 1) && inBoard(i, j + 1) && inBoard(i + 1, j) && board[i + 1][j + 1] == 1 && (board[i][j + 1] == 0 || board[i + 1][j] == 0)) {
						if (board[i][j + 1] == 0 && islegal(i, j + 1)) {
							new_x = i;
							new_y = j + 1;

							return 0;
						}
						else if (board[i + 1][j] == 0 && islegal(i + 1, j)) {
							new_x = i + 1;
							new_y = j;

							return 0;
						}
					}
					if (inBoard(i - 2, j + 1) && inBoard(i - 1, j) && inBoard(i - 1, j + 1) && board[i - 2][j + 1] == 1 && (board[i - 1][j] == 0 || board[i - 1][j + 1] == 0)) {
						if (board[i - 1][j] == 0 && islegal(i - 1, j)) {
							new_x = i - 1;
							new_y = j;

							return 0;
						}
						else if (board[i - 1][j + 1] == 0 && islegal(i - 1, j + 1)) {
							new_x = i - 1;
							new_y = j + 1;

							return 0;
						}
					}
					if (inBoard(i - 1, j - 1) && inBoard(i - 1, j) && inBoard(i, j - 1) && board[i - 1][j - 1] == 1 && (board[i - 1][j] == 0 || board[i][j - 1] == 0)) {
						if (board[i - 1][j] == 0 && islegal(i - 1, j)) {
							new_x = i - 1;
							new_y = j;

							return 0;
						}
						else if (board[i][j - 1] == 0 && islegal(i, j - 1)) {
							new_x = i;
							new_y = j - 1;

							return 0;
						}
					}
					if (inBoard(i + 1, j - 2) && inBoard(i + 1, j - 1) && inBoard(i, j - 1) && board[i + 1][j - 2] == 1 && (board[i + 1][j - 1] == 0 || board[i][j - 1] == 0)) {
						if (board[i + 1][j - 1] == 0 && islegal(i + 1, j - 1)) {
							new_x = i + 1;
							new_y = j - 1;

							return 0;
						}
						else if (board[i][j - 1] == 0 && islegal(i, j - 1)) {
							new_x = i;
							new_y = j - 1;

							return 0;
						}
					}
					if (inBoard(i + 2, j - 1) && inBoard(i + 1, j - 1) && inBoard(i + 1, j) && board[i + 2][j - 1] == 1 && (board[i + 1][j - 1] == 0 || board[i + 1][j] == 0)) {
						if (board[i + 1][j - 1] == 0 && islegal(i + 1, j - 1)) {
							new_x = i + 1;
							new_y = j - 1;

							return 0;
						}
						else if (board[i + 1][j] == 0 && islegal(i + 1, j)) {
							new_x = i + 1;
							new_y = j;

							return 0;
						}
					}
				}
			}
		for (int i = 10; i >= 0; i--)
			for (int j = 10; j >= 0; j--) {
				if (islegal(i, j) && board[i][j] == 0) {
					if (weight[i][j] > max_wei) {
						max_wei = weight[i][j];
						new_x = i;
						new_y = j;
					}
					else if (weight[i][j] == max_wei) {
						if (board[1][2] == 1 && j < new_y) {
							new_x = i;
							new_y = j;
						}
						else if (board[i][j] == -1 && i > new_x == i) {
							new_x = i;
							new_y = j;
						}
					}
				}
			}
	}

	return 0;

}



int main() {


	int x, y, n;
	//恢复目前的棋盘信息
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		cin >> x >> y; if (x != -1) board[x][y] = -1;	//对方
		cin >> x >> y; if (x != -1) board[x][y] = 1;	//我方
	}
	cin >> x >> y;  if (x != -1) board[x][y] = -1;	//对方
	else {
		cout << 1 << ' ' << 2 << endl;
		return 0;
	}
	if (n == 1) {
		cout << 7 << ' ' << 3 << endl;
		return 0;
	}
	if (n == 2 && x == 7 && y == 3) {
		cout << 4 << " " << 7 << endl;
		return 0;
	}
	//此时board[][]里存储的就是当前棋盘的所有棋子信息,x和y存的是对方最近一步下的棋

	//int time0 = clock();
	Solution solution;
	solution.Set(board);
	solution.judge_win();
	if (!choice_flag) {
		Gametree gt(board, x, y);

		pair<int, int> ans = gt.game();
		int new_x = ans.first;
		int new_y = ans.second;
		// 向平台输出决策结果
		//gt.test();
		cout << new_x << ' ' << new_y << endl;
		//int time1 = clock();
		//cout << "time:" << (double)(time1 - time0) / 1000 << " second" << endl;
	}
	else {
		int new_x, new_y;
		gap(new_x, new_y);
		cout << new_x << ' ' << new_y << endl;
	}
	return 0;
}
//析构函数没写