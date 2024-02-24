#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

size_t iterations = 0;

struct item {
	size_t weight;
	size_t price;

	bool operator<(const item& other) { return weight < other.weight; }
};

uint32_t FindMaxProfit(size_t MaxWeight, size_t NumberOfItems, const item* items, size_t Weight = 0, size_t start = 0)
{
	iterations++;

	size_t max = 0;

	for (size_t i = start; i < NumberOfItems; i++) {
		size_t weight = Weight;
		weight += items[i].weight;
		if (weight > MaxWeight)
			break;
		size_t val = items[i].price + FindMaxProfit(MaxWeight, NumberOfItems, items, weight, i + 1);
		if (max < val)
			max = val;
	}

	return max;
}

int main()
{
	auto start = std::chrono::high_resolution_clock::now();

	size_t NumberOfItems = 24, MaxWeight = 6404180; //13549094
	item items[] = {{382745,  825594},{799601, 1677009},{909247, 1676628},{729069, 1523970},{467902,  943972},{44328,   97426},{34610,   69666},{698150, 1296457},{823460, 1679693},{903959, 1902996},{853665, 1844992},{551830, 1049289},{610856, 1252836},{670702, 1319836},{488960,  953277},{951111, 2067538},{323046,  675367},{446298,  853655},{931161, 1826027},{31385,   65731},{496951,  901489},{264724,  577243},{224916,  466257},{169684,  369261}};

	//bool changed = 1;
	//while (changed) {
	//	changed = 0;
	//	for (size_t i = 0; i < NumberOfItems - 1; i++) {
	//		iterations++;
	//		if (items[i].weight > items[i + 1].weight) {
	//			item tmp = items[i];
	//			items[i] = items[i + 1];
	//			items[i + 1] = tmp;
	//			changed = 1;
	//		}
	//	}
	//}

	std::sort(std::begin(items), std::end(items));

	printf("%d ", FindMaxProfit(MaxWeight, NumberOfItems, items));
	printf("%d ", iterations);

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> time = end - start;
	std::cout << time.count();
}
