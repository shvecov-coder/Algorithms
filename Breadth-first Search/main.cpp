#include <queue>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

bool find_route(int start, int finish, int count_node, int* used, int** graph, queue<int> nodes, int * route);
void print_graph(int** graph, int size);
int** read_graph_from_file(ifstream& file, int& count);

int main()
{
	queue<int> nodes;
	int* used = NULL;
	int* route = NULL;
	vector<int> route_map;
	int** graph = NULL;
	int count_node = 0;
	ifstream graph_file("graph.txt");

	if (!graph_file.is_open())
	{
		cout << "Open file is error..." << endl;
		return -1;
	}

	graph = read_graph_from_file(graph_file, count_node);
	print_graph(graph, count_node);
	used = new int[count_node];
	route = new int[count_node];

	for (int i = 0; i < count_node; i++)
	{
		used[i] = 0;
		route[i] = -1;
	}

	if (find_route(5, 3, count_node, used, graph, nodes, route))
	{
		cout << "Route is success..." << endl;
		int cur = 3;
		route_map.push_back(cur + 1);
		while (route[cur] != -1)
		{
			cur = route[cur];
			route_map.push_back(cur + 1);
		}
		reverse(route_map.begin(), route_map.end());
		cout << "Route: ";
		for (int i = 0; i < route_map.size(); i++)
		{
			cout << route_map[i] << " ";
		}
	}
	else
	{
		cout << "Route is not found..." << endl;
	}

	cout << endl << "Used mass: ";

	for (int i = 0; i < count_node; i++)
	{
		cout << used[i] << " ";
	}
	cout << endl;

	// free memory
	for (int i = 0; i < count_node; i++)
	{
		delete[] graph[i];
	}
	delete[] used;
	delete[] route;

	graph_file.close();
}

int ** read_graph_from_file(ifstream & file, int & count)
{
	file >> count;
	cout << "Size: " << count << endl;
	int ** graph = new int* [count];
	for (int i = 0; i < count; i++)
	{
		graph[i] = new int[count];
	}

	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < count; j++)
		{
			file >> graph[i][j];
		}
	}

	return graph;
}

void print_graph(int** graph, int size)
{
	cout << "Graph:" << endl;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cout << graph[i][j] << " ";
		}
		cout << endl;
	}
}

bool find_route(int start, int finish, int count_node, int * used, int ** graph, queue<int> nodes, int * route)
{
	nodes.push(start);
	while (!nodes.empty())
	{
		int current_node = nodes.front();
		nodes.pop();

		for (int i = 0; i < count_node; i++)
		{
			if (graph[current_node][i] == 1 && used[i] == 0)
			{
				route[i] = current_node;
				if (i == finish)
				{
					return true;
				}

				nodes.push(i);
				used[i] = 1;
			}
		}

		used[current_node] = 2;
	}

	return false;
}
