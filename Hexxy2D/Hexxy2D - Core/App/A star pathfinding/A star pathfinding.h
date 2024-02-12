#pragma once

namespace AStar
{
	struct Node
	{
		int G_value, H_value;

		int F_value() { return G_value + H_value; }
		Node* left;
		Node* right;
	};
}