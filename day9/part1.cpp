#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

using Coords = pair<long long, long long>;
int main(){
	fstream input("input");
	vector<Coords> redTiles;
	for(string line; getline(input, line);){
		char comma;
		stringstream sline(line);
		Coords coords;
		sline >> coords.first >> comma >> coords.second;
		redTiles.push_back(coords);
	}

	long long int largestArea{0};
	
	for(size_t idx1{0}; idx1 < redTiles.size()-1; idx1++){
		for(size_t idx2{idx1 + 1}; idx2 < redTiles.size(); idx2++){
			long long dx {llabs(redTiles.at(idx1).first - redTiles.at(idx2).first)+1}; 
			long long dy {llabs(redTiles.at(idx1).second - redTiles.at(idx2).second)+1}; 
			long long area {dx*dy};
			if (area > largestArea){
				largestArea = area;
				cout << dx << '*' << dy << '=' << area << endl;
			}
		}
	}

	cout << "Largest Area:" << largestArea << endl;

	return 0;
}
