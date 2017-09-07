#include<iostream>
#include<cstdlib>
#include<fstream>

#define MAX 20
#define INFINITY 9999

using namespace std;

class bell_ford
{
private:
	int n;
	int graph[MAX][MAX];
	int start;
	int distance[MAX];
	int predecessor[MAX];
public:
	void read_graph();
	void initialize();
	void update();
	void check();
	void algorithm();
};

void bell_ford::read_graph()
{
	cout << "Enter the no.of nodes in the graph:: ";
	n = 12;
	cout << n << endl;
	cout << "Starting the adjacency matrix for the graph :: \n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			graph[i][j] = INFINITY;
		}
	}
	ifstream inFile;
	inFile.open("input.txt");
	if (inFile.fail()) {
		cout << "Failed to open the file" << endl;
		exit(1);
	}
	int _start, _end, _weight;
	while (!inFile.eof()) {
		inFile >> _start >> _end >> _weight;
		if (graph[_start][_end] <= _weight) {
			// do nothing
		}
		else {
			cout << _start << '\t' << _end << '\t' << _weight << endl;
			graph[_start][_end] = graph[_end][_start] = _weight;
		}
	}
	cout << "Enter the start vertex::";
	start = 0;
	cout << start << endl;
}

void bell_ford::initialize()
{
	for (int i = 0; i < n; i++)
	{
		distance[i] = INFINITY;
		predecessor[i] = 0;
	}
	distance[start] = 0;
}

void bell_ford::update()
{
	for (int i = 0; i < n; i++)
	{
		for (int u = 0; u < n; u++)
		{
			for (int v = 0; v < n; v++)
			{
				if (graph[u][v] != 0)
				{
					if (distance[v]>distance[u] + graph[u][v])
					{
						distance[v] = distance[u] + graph[u][v];
						predecessor[v] = u;
					}
				}
			}
		}
	}
}

void bell_ford::check()
{
	for (int u = 0; u < n; u++)
	{
		for (int v = 0; v < n; v++)
		{
			if (graph[u][v] != 0)
			{
				if (distance[v]>distance[u] + graph[u][v])
				{
					cout << "does not exist’s ";
					return;
				}
			}
		}
	}

	cout << "\n\nThere is no negative weight cycle and\n";
	cout << "****** The final paths and the distacnes are ******\n\n";
	for (int i = 0; i < n; i++)
	{
		cout << "path for node " << i << " is ::\n";
		int arr[MAX], k = 1;
		int j = i;
		while (predecessor[j] != 0)
		{
			arr[k] = predecessor[j];
			k++;
			j = predecessor[j];
		}
		for (--k; k>0; k--)
			cout << arr[k] << "->";
		cout << i << endl;
		cout << "distance is " << distance[i] << endl << endl << endl;
	}
}

void bell_ford::algorithm()
{
	read_graph();
	initialize();
	update();
	check();
}

int main()
{
	bell_ford obj;
	obj.algorithm();
	return 0;
}