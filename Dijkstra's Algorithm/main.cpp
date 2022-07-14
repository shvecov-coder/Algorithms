#include <vector>
#include <limits>
#include <fstream>
#include <iostream>

using namespace std;

void print_graph(int** graph, int size);
void solution(int** graph, int count);
int** read_graph_from_file(ifstream& file, int & count_node);
int find_lowest_cost_node(int* costs, int* used, int count_nodes);

int main()
{
	int count_node = 0;
	int** graph = NULL;
	ifstream file("graph.txt");

	if (!file.is_open())
	{
		cout << "File is not opened..." << endl;
		return -1;
	}

	graph = read_graph_from_file(file, count_node);
	print_graph(graph, count_node);
	solution(graph, count_node);

	// free memory
	for (int i = 0; i < count_node; i++)
	{
		delete[] graph[i];
	}
	file.close();

	return 0;
}

int** read_graph_from_file(ifstream& file, int & count_node)
{
	file >> count_node;
	cout << "Count nodes: " << count_node << endl;

	int** ptr = new int* [count_node];

	for (int i = 0; i < count_node; i++)
	{
		ptr[i] = new int[count_node];
	}

	for (int i = 0; i < count_node; i++)
	{
		for (int j = 0; j < count_node; j++)
		{
			file >> ptr[i][j];
		}
	}

	return ptr;
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

void solution(int** graph, int count)
{
	int current_node = 0;
	int* parent = new int[count];
	int* used = new int[count];
	int* costs = new int[count];

	for (int i = 0; i < count; i++)
	{
		used[i] = 0;
		costs[i] = INT_MAX;
		parent[i] = -1;
	}

	costs[0] = 0;
	parent[0] = 0;

	current_node = find_lowest_cost_node(costs, used, count);
	while (current_node != -1)
	{
		for (int i = 0; i < count; i++)
		{
			if (graph[current_node][i] != -1)
			{
				int new_cost = costs[current_node] + graph[current_node][i];
				if (new_cost < costs[i])
				{
					costs[i] = new_cost;
					parent[i] = current_node;
				}
			}
		}

		used[current_node] = 1;
		current_node = find_lowest_cost_node(costs, used, count);
	}

	cout << "Pay raoute: " << costs[count - 1] << endl;
	cout << "Route: ";

	int crt_nd = count - 1;
	vector<int> route;

	while (crt_nd)
	{
		route.push_back(crt_nd);
		crt_nd = parent[crt_nd];
	}
	route.push_back(crt_nd);
	reverse(route.begin(), route.end());

	for (int i = 0; i < route.size(); i++)
	{
		cout << route[i] << " ";
	}

	delete[] parent;
	delete[] used;
	delete[] costs;
}

int find_lowest_cost_node(int * costs, int * used, int count_nodes)
{
	int min = INT_MAX;
	int min_idx = -1;

	for (int i = 0; i < count_nodes; i++)
	{
		if (costs[i] < min && used[i] == 0)
		{
			min = costs[i];
			min_idx = i;
		}
	}

	return min_idx;
}