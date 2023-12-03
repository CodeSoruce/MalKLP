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
typedef vector<vector<vector<int>>> VVVI;
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
	
	VI adj;
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

	double processingtime = 0;

	I n, m, T, num_e = -1;

	I K, L, threshold;

	I del_tn = 0, del_n = 0, del_te = 0, del_e = 0; 

	VI unit = {0};

	VI U;
	vector<Node1> Node;
	vector<Edge1> Edge;

	VVI TDeg_inAns;

	VVI Hop_adj;

	VVI Cand;
	VVI Cand_t;
	VVI Xand;
	VI Ans;
	vector<bool> inAns;

	VVI OUT;
	I OUT_num = 0;

	void dataInput(string graphname);
	
	void OPT();

	I sub_OPT(I p);

	void DVB_Pruning(I p);
	
	static bool compare(const I &a, const I &b);
	static bool compare1(const I &a, const I &b);
};

#endif // !GRAPH
