#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

struct Region{
	int height{};
	int width{};
	int totalPresents{};
};

int
main()
{
	fstream input("input");
	int regionsThatFit{};
	for (string line; getline(input, line);)
	{
		Region region{};
		stringstream ss(line);
		char _;
		ss >> region.height;
		ss >> _;
		ss >> region.width;
		ss >> _;
		for (int i{}; i < 6; i++){
			int presents{};
			ss >> presents;
			region.totalPresents += presents;
		}

		// Try a greedy algorithm - each pressent gets a 3x3 space;
		if (((region.width / 3) * (region.height / 3)) >= region.totalPresents ){
			regionsThatFit++;
		}
	}
	cout << "Regions that can fit presents:" << regionsThatFit << endl;
	// I can't believe that worked...
	return 0;
}
