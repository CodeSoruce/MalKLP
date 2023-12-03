#include "graph.h"

VI operator+(VI &v1, VI &v2)
{
	VI res(v1.size() + v2.size());
	int sz = set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), res.begin()) - res.begin();
	res.resize(sz);
	return res;
};

VI operator-(VI &v1, VI &v2)
{
	VI res(v1.size());
	int sz = set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), res.begin()) - res.begin();
	res.resize(sz);
	return res;
};

VI operator*(VI &v1, VI &v2)
{
	VI res(v1.size());
	int sz = set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), res.begin()) - res.begin();
	res.resize(sz);
	return res;
};

void Graph::dataInput(string graphname)
{
	ifstream infile;
	infile.open(graphname);
	infile >> n >> m >> T;

	Node.reserve(n);
	U.reserve(n);

	for (I i = 0; i < n; i++)
	{
		U.push_back(i);

		Node1 n1;
		n1.Sup = 0;
		n1.exist = 1;

		VI emp = {};
		for (auto j = 0; j < T; j++)
			n1.T_adj.push_back(emp);

		for (auto j = 0; j < T; j++)
			n1.T_adjedge.push_back(emp);

		for (auto j = 0; j < T; j++)
			n1.T_Deg.push_back(0);

		for (auto j = 0; j < T; j++)
			n1.T_exist.push_back(0);

		Node.push_back(n1);
	}

	I u, v, t;
	I pu = -1, pv = -1;
	for (I j = 0; j < m; j++)
	{
		infile >> u >> v >> t;

		Edge1 e;
		e.u = u;
		e.v = v;
		e.t = t;
		e.exist = 1;
		Edge.push_back(e);

		Node[u].T_adj[t].push_back(v);
		Node[u].T_adjedge[t].push_back(j);
		Node[u].T_Deg[t]++;
		Node[u].T_exist[t] = 1;

		Node[v].T_adj[t].push_back(u);
		Node[v].T_adjedge[t].push_back(j);
		Node[v].T_Deg[t]++;
		Node[v].T_exist[t] = 1;

		if (u != pu || v != pv)
		{
			Node[u].adj.push_back(v);
			Node[v].adj.push_back(u);
		}
		pu = u;
		pv = v;
	}

	infile.close();
}

void Graph::GP_Core()
{
	for (I t = 0; t < T; t++)
	{
		for (auto u : U)
		{
			if (Node[u].T_Deg[t] > 0)
				Node[u].Sup++;
			else
				Node[u].T_exist[t] = 0;
		}
	}

	for (I t = 0; t < T; t++)
	{
		for (auto u : U)
		{
			if ((Node[u].T_Deg[t] > 0 && Node[u].T_Deg[t] < threshold - K) || (Node[u].Sup > 0 && Node[u].Sup < L))
				sub_GP_Core(u, t);
		}
	}

	for (auto u : U)
	{
		if (Node[u].Sup == 0)
			Node[u].exist = 0;
	}

	I new_m = 0;

	for (I t = 0; t < T; t++)
	{
		int _m = 0;
		for (auto u : U)
		{
			if (Node[u].T_exist[t] == 0)
			{
				del_tn++;
				Node[u].T_adj[t].clear();
				Node[u].T_adjedge[t].clear();
				continue;
			}
			I p = 0;

			for (I i = 0; i < Node[u].T_adj[t].size(); i++)
			{
				vI v = Node[u].T_adj[t][i];
				if (Node[v].T_exist[t])
					Node[u].T_adj[t][p++] = v;
			}
			Node[u].T_adj[t].resize(p);
			_m += p;
		}
		new_m += _m;
		assert(_m % 2 == 0);
	}
	new_m = new_m/2;
	del_te = m - new_m;

	VI del_U = {};
	del_U.reserve(n);
	for (auto u : U)
	{
		if (Node[u].exist == 0)
		{
			del_U.push_back(u);
			del_n++;
			Node[u].adj.clear();
			continue;
		}

		I p = 0;
		for (I i = 0; i < Node[u].adj.size(); i++)
		{
			vI v = Node[u].adj[i];
			if (Node[v].exist)
				Node[u].adj[p++] = v;
		}
		Node[u].adj.resize(p);
	}
	
	U = U - del_U;
}

void Graph::sub_GP_Core(uI u, I t)
{
	Node[u].T_Deg[t] = 0;
	Node[u].T_exist[t] = 0;

	for (auto v : Node[u].T_adj[t])
	{
		if (Node[v].T_Deg[t] > 0)
		{
			Node[v].T_Deg[t]--;
			if (Node[v].T_Deg[t] < threshold - K)
				sub_GP_Core(v, t);
		}
	}

	if (Node[u].Sup > 0)
	{
		Node[u].Sup--;
		if (Node[u].Sup < L)
		{
			Node[u].Sup = 0;
			Node[u].exist = 0;
			for (I t = 0; t < T; t++)
			{
				if (Node[u].T_Deg[t] > 0)
					sub_GP_Core(u, t);
			}
		}
	}
}

void Graph::OPT()
{
	TDeg_inAns.resize(n);
	for (I i = 0; i < n; i++)
		TDeg_inAns[i].resize(T, 0);

	Hop_adj.resize(n);

	Cand.resize(U.size()+2);
	Xand.resize(U.size()+2);
	Cand_t.resize(U.size()+2);

	Ans.resize(U.size());

	inAns.resize(n, false);

	Cand[0] = U;

	for (auto u : U)
	{
		Ans[0] = u;
		inAns[u] = true;

		Cand[1].clear();
		Cand[1].push_back(u);
		for (auto v : Node[u].adj)
		{
			if (v < u)
				continue;
			Cand[1].push_back(v);
			for (auto w : Node[v].adj)
			{
				if (w < u)
					continue;
				Cand[1].push_back(w);
			}
		}
		sort(Cand[1].begin(), Cand[1].end());
		I p = 0;
		I pv = -1;
		for (I i = 0; i < Cand[1].size(); i++)
		{
			uI v = Cand[1][i];
			if (pv != v)
			{
				Cand[1][p++] = v;
				pv = v;
			}
		}
		Cand[1].resize(p);

		Cand_t[1].clear();
		for (I t = 0; t < T; t++)
		{
			if (Node[u].T_exist[t])
				Cand_t[1].push_back(t);
		}

		unit[0] = u;
		Cand[1] = Cand[1] - unit;
		Hop_adj[u] = Cand[1];

		for (auto t : Cand_t[1])
		{
			for (auto v : Node[u].T_adj[t])
			{
				TDeg_inAns[v][t]++;
			}
		}
		

		sub_OPT(1);

		for (auto t : Cand_t[1])
		{
			for (auto v : Node[u].T_adj[t])
			{
				TDeg_inAns[v][t]--;
			}
		}
		inAns[u] = false;
	}
}

I Graph::sub_OPT(I p)
{
	I flag = 0;
	for (auto u : Cand[p])
	{
		Ans[p] = u;
		inAns[u] = true;

		DVB_Pruning(p);


		if (p + 1 + Cand[p+1].size() >= threshold && Cand_t[p+1].size() >= L)
		{
			I in_flag = sub_OPT(p+1);

			flag = 1;
			if (p + 1 >= threshold)
			{
				VI tem(Ans.begin(), Ans.begin() + p + 1);
				sort(tem.begin(), tem.end());
				CheckMal(tem);
			}
		}

		for (auto t : Cand_t[p])
		{
			if (TDeg_inAns[u][t] < p + 1 - K)
				continue;

			for (auto v : Node[u].T_adj[t])
			{
				TDeg_inAns[v][t]--;
			}
		}

		inAns[u] = false;
	}

	return flag;
}

void Graph::DVB_Pruning(I p)
{
	Cand[p+1].clear();
	Xand[p+1].clear();
	Cand_t[p+1].clear();

	uI u = Ans[p];
	
	for (auto t : Cand_t[p])
	{
		if (TDeg_inAns[u][t] < p + 1 - K)
			continue;

		for (auto v : Node[u].T_adj[t])
		{
			TDeg_inAns[v][t]++;
		}

		I flag = 0;
		for (I i = 0; i < p; i++)
		{
			vI v = Ans[i];
			if (TDeg_inAns[v][t] < p + 1 - K)
			{
				flag = 1;
				break;
			}
		}

		if (flag)
			continue;

		Cand_t[p+1].push_back(t);
	}

	if (Cand_t[p+1].size() < L)
		return;

	for (auto v : Cand[p])
	{
		if (v <= u)
			continue;

		I time_count = 0;
		for (auto t : Cand_t[p+1])
		{
			if (TDeg_inAns[v][t] >= p + 1 - K)
				time_count++;
		}
		if (time_count >= L)
			Cand[p+1].push_back(v);
	}

	for (auto v : Cand[1])
	{
		if (v >= u)
			break;

		if (inAns[v])
			continue;

		I time_count = 0;
		for (auto t : Cand_t[p+1])
		{
			if (TDeg_inAns[v][t] >= p + 1 - K)
				time_count++;
		}
		if (time_count >= L)
			Xand[p+1].push_back(v);
	}
}

void Graph::CheckMal(VI &U)
{
	VI em = {-1};
	for (I i = 0; i < OUT.size(); i++)
	{
		VI Ut = OUT[i];

		if (Ut.size() >= U.size())
		{
			if ((U - Ut).size() == 0)
			{
				return;
			}
		}
		else
		{
			if ((Ut - U).size() == 0)
			{
				OUT[i] = em;
				OUT_num--;
			}
		}
	}
	OUT.push_back(U);
	OUT_num++;
}