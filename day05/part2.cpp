#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

int main (){
	std::ifstream input("input");
	vector<pair<unsigned long int, unsigned long int>> ranges;
	unsigned long int freshID{0};
	
	unsigned long int minRange{};
	unsigned long int maxRange{};
	char rangeSeperator;
	for(string line; getline(input, line);){
		if (line == "") break;
		istringstream linestream (line);
		linestream >> minRange >> rangeSeperator >> maxRange;
		ranges.push_back(make_pair(minRange, maxRange));
	}

	for (unsigned int currRange{0}; currRange < ranges.size()-1; currRange++) {
		for (unsigned int compRange{currRange+1}; compRange < ranges.size(); compRange++){
			if (ranges[compRange].first == 0 && ranges[compRange].second == 0) continue;
			// compared range is totally within
			if (ranges[currRange].first <= ranges[compRange].first && ranges[currRange].second >= ranges[compRange].second) {
				ranges[compRange].first = 0;
				ranges[compRange].second = 0;
			}
			// compared range totally engulfs
			else if (ranges[currRange].first >= ranges[compRange].first && ranges[currRange].second <= ranges[compRange].second) {
				ranges[currRange].first = 0;
				ranges[currRange].second = 0;
				goto rangeDeleted;
			}
			else if (ranges[currRange].second >= ranges[compRange].first && ranges[currRange].second <= ranges[compRange].second) {
				ranges[currRange].second = ranges[compRange].first - 1;
			}
			else if (ranges[currRange].first <= ranges[compRange].second && ranges[currRange].first >= ranges[compRange].first) {
				ranges[currRange].first = ranges[compRange].second + 1;
			}
		}
		rangeDeleted:
		cout << ranges[currRange].first << '-' << ranges[currRange].second << endl;
		// Skip deleted ranges
		if (ranges[currRange].first == 0 && ranges[currRange].second == 0) continue;
		freshID += (ranges[currRange].second - ranges[currRange].first) + 1; 
	}
	cout << ranges.back().first << '-' << ranges.back().second << endl;
	if (ranges.back().first != 0 && ranges.back().second != 0) 
		freshID += ranges.back().second - ranges.back().first + 1;
	cout << "Fresh id count:" << freshID << endl;
	return 0;
}
