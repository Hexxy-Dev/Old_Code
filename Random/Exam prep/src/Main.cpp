#include <iostream>
#include <vector>
#include <queue>
#include <functional>

struct Node {
	int val;
	std::vector<Node*> connections;
	void ConnectBD(Node* other)
	{
		this->connections.push_back(other);
		other->connections.push_back(this);
	}
	void ConnectTo(Node* other) {
		this->connections.push_back(other);
	}
};

Node* CreateGraph()
{
	Node* nodes = new Node[9];
	for (size_t i = 0; i < 9; i++)
		nodes[i].val = i + 1;

	nodes[1 - 1].ConnectTo(&nodes[2 - 1]);
	nodes[1 - 1].ConnectTo(&nodes[3 - 1]);
	nodes[1 - 1].ConnectTo(&nodes[4 - 1]);

	nodes[2 - 1].ConnectTo(&nodes[5 - 1]);
	//nodes[2 - 1].ConnectBD(&nodes[6 - 1]);

	nodes[3 - 1].ConnectTo(&nodes[6 - 1]);
	nodes[3 - 1].ConnectTo(&nodes[7 - 1]);

	nodes[4 - 1].ConnectTo(&nodes[7 - 1]);

	nodes[5 - 1].ConnectTo(&nodes[3 - 1]);
	nodes[5 - 1].ConnectTo(&nodes[8 - 1]);

	nodes[6 - 1].ConnectTo(&nodes[8 - 1]);
	nodes[6 - 1].ConnectTo(&nodes[9 - 1]);

	return nodes;
}

bool IsNotVisited(std::vector<Node*> visited, Node* N)
{
	for (Node* node : visited)
		if (node == N)
			return false;
	return true;
}

void BFS(Node* root)
{
	std::vector<Node*> visited{ root };
	std::queue<Node*> q;
	q.push(root);

	while (!q.empty()) {
		Node* tmp = q.front();
		q.pop();
		std::cout << tmp->val;
		putchar(' ');
		for(Node* con : tmp->connections)
			if (IsNotVisited(visited, con)) {
				visited.push_back(con);
				q.push(con);
			}
	}
}

void DFS(Node* root)
{
	std::vector<Node*> visited{ root };

	std::function<void(Node*)> dfs = [&](Node* N) {
		std::cout << N->val;
		putchar(' ');
		for(Node* con : N->connections)
			if (IsNotVisited(visited, con)) {
				visited.push_back(con);
				dfs(con);
			}
	};
	dfs(root);
}

void GraphAlgorithms()
{
	Node* root = CreateGraph();

	puts("BFS:");
	BFS(root);
	putchar('\n');

	puts("DFS:");
	DFS(root);
	putchar('\n');

	delete[] root;
}

int main()
{
	GraphAlgorithms();


}