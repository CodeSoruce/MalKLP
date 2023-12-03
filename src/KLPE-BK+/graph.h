#ifndef GRAPH
#define GRAPH

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <fstream>
#include <cmath>
#include <queue>
#include <iterator>
#include <bitset>
#include <math.h>
#include <unordered_map>
#include <stack>
#include <random>
#include <chrono>
#define NDEBUG
#include <assert.h>

#define TIMEOVER 43200

using namespace std;

typedef int I;
typedef int uI;
typedef int vI;
typedef int eI;

typedef vector<int> VI;
typedef queue<int> QI;
typedef vector<vector<int>> VVI;
typedef pair<uI, I> PII;
typedef pair<VI, VI> PVIVI;

typedef unordered_map<int, int> UMII;

static VI tdeg_u = {};

VI operator+(VI &v1, VI &v2);
VI operator-(VI &v1, VI &v2);
VI operator*(VI &v1, VI &v2);

typedef struct Node1
{
	VVI T_adj;
	VVI T_adjedge;
	VI T_Deg;
	VI T_exist;
	
	I Sup;
	bool exist;
} Node1;

typedef struct Edge1
{
	uI u;
	vI v;
	I t;
	bool exist;
} Edge1;

class Graph
{
public:
	double throwtime = 0;

	double testtime = 0;

	I n, m, T, num_e = -1;

	I K, L, threshold;
	
	I del_tn = 0, del_n = 0, del_te = 0, del_e = 0; 

	VI unit = {0};

	VI U;
	vector<Node1> Node;
	vector<Edge1> Edge;

	VVI OUT;
	I OUT_num = 0;

	void dataInput(string graphname);

	void GP_Core();

	void sub_GP_Core(uI u, I t);

	void Base(VI &U, VI &C);

	bool CheckFP(VI &U);

	void CheckMal(VI &U);

	static bool compare(const I &a, const I &b);
	static bool compare1(const I &a, const I &b);
};

#endif // !GRAPH
