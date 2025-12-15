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

	vector<pair<Coords, Coords>> edges{};
	for(size_t i{0}; i < redTiles.size() - 1; i++){
		edges.push_back(pair(redTiles[i], redTiles[i+1]));
	}
	edges.push_back(pair(redTiles[0], redTiles[redTiles.size()-1]));

	long long int largestArea{0};
	
	for(size_t idx1{0}; idx1 < redTiles.size()-1; idx1++){
		for(size_t idx2{idx1 + 1}; idx2 < redTiles.size(); idx2++){
			long long x1{max(redTiles.at(idx1).first , redTiles.at(idx2).first)};
			long long x2{min(redTiles.at(idx1).first , redTiles.at(idx2).first)};
			long long y1{max(redTiles.at(idx1).second , redTiles.at(idx2).second)};
			long long y2{min(redTiles.at(idx1).second , redTiles.at(idx2).second)};
			long long dx {x1-x2+1}; 
			long long dy {y1-y2+1}; 
			long long area {dx*dy};
			// To check if the rectangle is inside the green area, check no edge is inside our rectangle
			// Won't work with any input but SHOULD do with the one we have... hohoho!
			for(auto edge: edges){
				// if Xs the same - vertical edge
				if (edge.first.first == edge.second.first){
					long long ey1{max(edge.first.second, edge.second.second)};
					long long ey2{min(edge.first.second, edge.second.second)};
					long long ex{edge.first.first};
					if (x1 > ex && x2 < ex && ey2 < y1 && ey1 > y2)
						goto outside;
				}
				else{ // horizontal edge
					long long ex1{max(edge.first.first, edge.second.first)};
					long long ex2{min(edge.first.first, edge.second.first)};
					long long ey{edge.first.second};
					if (y1 > ey && y2 < ey && ex2 < x1 && ex1 > x2)
						goto outside;
				}
			}

			if (area > largestArea){
				largestArea = area;
			}
			outside:;
		}
	}

	cout << "Largest Area:" << largestArea << endl;

	return 0;
}
