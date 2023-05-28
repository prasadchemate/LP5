#include<bits/stdc++.h>
#include<omp.h>
using namespace std;

void printGraph(vector<vector<int>>& graph)
{
	cout<<"\n\nGraph\n";
	for(int i=0; i<graph.size(); i++)
	{
		cout<<i<<" -> ";
		for(int j=0; j<graph[i].size(); j++)
		{
			cout<<graph[i][j]<<" ";
		}
		cout<<endl;
	}
}

void S_BFS(vector<vector<int>>& graph,int * visited,int v)
{
	queue<int> Q;
	Q.push(v);
	visited[v] = 1;
	
	while(!Q.empty())
	{
		v = Q.front();
		Q.pop();
		cout<<" "<<v;
		for(int i=0; i<graph[v].size(); i++)
		{
			int adj = graph[v][i];
			if(visited[adj] == 0)
			{
				visited[adj] = 1;
				Q.push(adj);
			}
		}
	}
}

void P_BFS(vector<vector<int>>& graph,int * visited,int v)
{
	queue<int> Q;
	Q.push(v);
	visited[v] = 1;
	
	while(!Q.empty())
	{
		v = Q.front();
		#pragma omp critical
		Q.pop();
		cout<<" "<<v;
		#pragma omp parallel for
		for(int i=0; i<graph[v].size(); i++)
		{
			int adj = graph[v][i];
			if(visited[adj] == 0)		//if adj is not visited
			{
				#pragma omp critical
				{
					visited[adj] = 1;
					Q.push(adj);
				}
			}
		}
	}
}

int main()
{
	int v,e;
	cout<<"\nEnter the number of vertices and edges (v, e) : ";
	cin>>v>>e;
	
	//create the graph using v
	vector<vector<int>> graph(v);
	
	cout<<"\nEnter the edges in the format (u, v)\n";
	for(int i=0; i<e; i++)
	{
		int u,v;
		cin>>u>>v;
		//add edge in graph
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	
	printGraph(graph);
	
	int * visited = new int[v];
	for(int i=0; i<v; i++)
	{
		visited[i] = 0;
	}
	
	double start,end,stime,ptime;
	
	start = omp_get_wtime();
	cout<<"\n\nSequential BFS\n";
	S_BFS(graph, visited, 0);
	end = omp_get_wtime();
	stime = (end - start);
	
	for(int i=0; i<v; i++)
	{
		visited[i] = 0;
	}
	
	start = omp_get_wtime();
	cout<<"\n\nParallel BFS\n";
	P_BFS(graph, visited, 0);
	end = omp_get_wtime();
	ptime = (end - start);
	
	cout<<"\n\nSequential Time = "<<stime<<" sec";
	cout<<"\nParallel Time   = "<<ptime<<" sec";
	
	return 0;
}
