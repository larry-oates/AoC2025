#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

int main (){
	std::ifstream input("input");
	vector<pair<unsigned long int, unsigned long int>> ranges;
	int freshIngredients{0};
	
	unsigned long int minRange{};
	unsigned long int maxRange{};
	char rangeSeperator;
	for(string line; getline(input, line);){
		if (line == "") break;
		istringstream linestream (line);
		linestream >> minRange >> rangeSeperator >> maxRange;
		cout << minRange << '-' << maxRange << endl;
		ranges.push_back(make_pair(minRange, maxRange));
	}
 
	cout << "ranges done" << endl;
	for(string line; getline(input, line);){
		unsigned long int ingredientID{stoul(line)};
		cout << ingredientID << endl;
		for (auto range: ranges){
			if (ingredientID >= range.first && ingredientID <= range.second) {
				freshIngredients++;
				break;
			}
		}
	}
	cout << "Fresh ingredient count:" << freshIngredients << endl;
	return 0;
}
