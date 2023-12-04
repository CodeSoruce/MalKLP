#include "graph.h"
#include <ctime>

int main(int argc, char *argv[])
{
	string algo, graphname, graphfile;
	I K, L, threshold;
	graphname=argv[1];
	K=atoi(argv[2]);
	L=atoi(argv[3]);
	threshold=atoi(argv[4]);

	cout << algo << "  " << graphname << "  K=" << K << "  L=" << L << "  Theta=" << threshold << endl;

	graphfile="../../sample_dataset/" + graphname + ".txt";

	Graph g;

	g.K = K;
	g.L = L;
	g.threshold = threshold;

	g.dataInput(graphfile);
	cout << "Input Done" << endl;


	auto start_GP_Core = chrono::steady_clock::now();
	g.GP_Core();
	auto end_GP_Core = chrono::steady_clock::now();
	double Time_GP_Core = chrono::duration_cast<chrono::microseconds>(end_GP_Core - start_GP_Core).count();
	cout << "Graph Reduction Done" << endl;


	string s = "-";
	auto start = chrono::steady_clock::now();
	try{
		g.OPT();
	}
	catch (string s1){
		s = s1;
	}
	auto end = chrono::steady_clock::now();
	double RuningTime = chrono::duration_cast<chrono::microseconds>(end - start).count();
	
	cout << algo << endl;
	cout << graphname << endl;
	cout << "K = " << K << endl;
	cout << "L = " << L << endl;
	cout << "Theta = " << threshold << endl << endl;

	cout << "precent_del_edge = " << float(g.del_te)/float(g.m) << endl << endl;

	cout << "AllTime : " << RuningTime/1000000 + Time_GP_Core/1000000 << endl << endl;

	cout << "ALL Done" << endl;

	return 0;
}
