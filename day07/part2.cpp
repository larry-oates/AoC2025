#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

int main(){
	fstream input("input");
	string line{};
	int pos{0};
	vector<long long unsigned int> tachyons;

	// Find inital position
	getline(input, line);
	for (char c: line){
		if (c == 'S') tachyons.push_back(1);
		else tachyons.push_back(0);
		pos++;
	}

	// remove the extra line
	getline(input, line);
	for (; getline(input, line);){
		pos = 0;
		for(char c: line){
			if (c == '^' && tachyons[pos] >= 1){
				long long unsigned int tachCount = tachyons.at(pos);
				tachyons.at(pos) = 0;
				tachyons.at(pos + 1) += tachCount;
				tachyons.at(pos - 1) += tachCount;
			}
			pos++;
		}
		// remove the extra line
		getline(input, line);
	}
	
	long long unsigned int totalTimelines{0};
	for (long long unsigned int tachCount: tachyons){
		totalTimelines += tachCount;
	}

	cout << "Total timelines:" << totalTimelines << endl;
	return 0;
}
