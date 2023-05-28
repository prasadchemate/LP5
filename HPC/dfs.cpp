#include<bits/stdc++.h>
#include<omp.h>
using namespace std;


//printing the graph
void printGraph(vector<vector<int>> graph)
{
	cout<<"\n\nPrinting Undirected Graph:\n";
	for(int i=0; i<graph.size(); i++)
	{
		cout<<i<<" -> ";
		for(int j=0; j<graph[i].size(); j++)
		{
			cout<<graph[i][j]<<" ";
		}
		cout<<"\n";
	}
}
		
void sequential_DFS(vector<vector<int>> graph,int * visited,int v)
{	
	/*
	visited[v] = 1;
	cout<<" "<<v;
	for(int i=0; i<graph[v].size(); i++)
	{
		if(visited[graph[v][i]] == 0)
		{
			sequential_DFS(graph, visited, graph[v][i]);
		}
	}
	*/
	
	stack<int> S;
	S.push(v);
	visited[v] = 1;
	
	while(!S.empty())
	{
		v = S.top();
		S.pop();
		cout<<" "<<v;
		for(int i=0; i<graph[v].size(); i++)
		{
				if(visited[graph[v][i]] == 0)
				{
					visited[graph[v][i]] = 1;
					S.push(graph[v][i]);
				}
		}
	}
}

void parallel_DFS(vector<vector<int>> graph,int * visited,int v)
{	
	/*
	visited[v] = 1;
	cout<<" "<<v;
	#pragma omp parallel for
	for(int i=0; i<graph[v].size(); i++)
	{
		if(visited[graph[v][i]] == 0)
		{
			parallel_DFS(graph, visited, graph[v][i]);
		}
	}
	*/
	
	stack<int> S;
	S.push(v);
	visited[v] = 1;
	
	while(!S.empty())
	{
		v = S.top();
		#pragma omp critical
		S.pop();
		cout<<" "<<v;
		#pragma omp parallel for
		for(int i=0; i<graph[v].size(); i++)
		{
				if(visited[graph[v][i]] == 0)
				{
					#pragma omp critical
					{
						visited[graph[v][i]] = 1;
						S.push(graph[v][i]);
					}
				}
		}
	}

}

int main()
{
	int vertices, edges;
	cout<<"\nEnter the number of vertices : ";
	cin>>vertices;
	cout<<"\nEnter the number of edges    : ";
	cin>>edges;
	
	//create a graph with given vertices
	vector<vector<int>> graph(vertices);
			
	//reading the graph
	for(int i=0; i<edges; i++)
	{
		int u,v;
		cout<<"\nEnter the edge in the format (u, v) : ";
		cin>>u>>v;
		//insert the edge in the graph
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	
	//printing the graph
	printGraph(graph);
	
	int * visited = new int[vertices];
	//initialize visited array to zero
	for(int i=0; i<vertices; i++)
	{
		visited[i] = 0;
	}
	
	cout<<"\n\n Sequential DFS:\n";
	double s_start, s_end;
	s_start = omp_get_wtime();
	sequential_DFS(graph, visited, 0);
	s_end = omp_get_wtime();
	
	//initialize visited array to zero
	for(int i=0; i<vertices; i++)
	{
		visited[i] = 0;
	}
	
	cout<<"\n\n Parallel DFS:\n";
	double p_start, p_end;
	p_start = omp_get_wtime();
	//#pragma omp parallel
	{
		//#pragma omp single
		{
			parallel_DFS(graph, visited, 0);
		}
	}
	p_end = omp_get_wtime();
	
	double s_time = (s_end - s_start);
	double p_time = (p_end - p_start);
	cout<<"\n\nSequential Time = "<<s_time<<" seconds";
	cout<<"\nParallel Time   = "<<p_time<<" seconds";
	return 0;
}
