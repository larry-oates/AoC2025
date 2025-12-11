#include <fstream>
#include <iostream>
#include <set>
using namespace std;

int main(){
	fstream input("input");
	string line{};
	int splitTotal{0};
	int pos{0};
	set<int> tachyons{};

	// Find inital position
	getline(input, line);
	while (line[pos] != 'S') pos++;
	tachyons.insert(pos);
	cout << tachyons.contains(pos) << endl;

	// remove the extra line
	getline(input, line);
	for (; getline(input, line);){
		pos = 0;
		for(char c: line){
			if (c == '^' && tachyons.contains(pos)){
				tachyons.erase(pos);
				tachyons.insert(pos + 1);
				tachyons.insert(pos - 1);
				splitTotal++;
			}
			pos++;
		}
		// remove the extra line
		getline(input, line);
	}

	cout << "Total Splits:" << splitTotal << endl;
	return 0;
}
