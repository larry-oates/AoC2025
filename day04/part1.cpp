#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

static vector<string> lines;

bool isAccessable(size_t x, size_t y){
	constexpr int maxNeighbours{4};
	constexpr char roll{'@'};
	constexpr char space{'.'};

	// Filter non-roll spaces
	if (lines[y][x] == space) return false;

	// Corner cases
	if ((x == 0 && y == 0) || (x == 0 && y == lines.size()-1) || (x == lines[y].size()-1 && y == 0) || (x == lines[y].size()-1 && y == lines.size()-1) ) return true;
	
	int neighbours{0};
	// Edge case - need to find one empty space
	if (x == 0) {
		if (lines[y-1][0] == roll) neighbours++;
		if (lines[y+1][0] == roll) neighbours++;
		if (lines[y-1][1] == roll) neighbours++;
		if (lines[y][1] == roll) neighbours++;
		if (lines[y+1][1] == roll) neighbours++;
	}
	else if (y == 0) {
		if (lines[0][x-1] == roll) neighbours++;
		if (lines[0][x+1] == roll) neighbours++;
		if (lines[1][x-1] == roll) neighbours++;
		if (lines[1][x] == roll) neighbours++;
		if (lines[1][x+1] == roll) neighbours++;
	}
	else if (x == lines[y].size()-1){
		if (lines[y-1][lines[y].size()-1] == roll) neighbours++;
		if (lines[y+1][lines[y].size()-1] == roll) neighbours++;
		if (lines[y-1][lines[y].size()-2] == roll) neighbours++;
		if (lines[y][lines[y].size()-2] == roll) neighbours++;
		if (lines[y+1][lines[y].size()-2] == roll) neighbours++;
	}
	else if (y == lines.size()-1){
		if (lines[lines.size()-1][x-1] == roll) neighbours++;
		if (lines[lines.size()-1][x+1] == roll) neighbours++;
		if (lines[lines.size()-2][x-1] == roll) neighbours++;
		if (lines[lines.size()-2][x] == roll) neighbours++;
		if (lines[lines.size()-2][x+1] == roll) neighbours++;
	}

	// Center case
	else {
		if (lines[y+1][x+1] == roll ) neighbours++;
		if (lines[y+1][x] == roll ) neighbours++;
		if (lines[y+1][x-1] == roll ) neighbours++;
		if (lines[y][x+1] == roll ) neighbours++;
		if (lines[y][x-1] == roll ) neighbours++;
		if (lines[y-1][x-1] == roll ) neighbours++;
		if (lines[y-1][x] == roll ) neighbours++;
		if (lines[y-1][x+1] == roll ) neighbours++;
	} 
	if (neighbours < maxNeighbours){
		return true;
	}
	else return false;
	
}

int main (){
	ifstream input("input");
	int accessableRolls{0};

	for (string line; getline(input, line);){
		lines.push_back(line);
	}

	for (size_t x{0}; x < lines[0].size(); x++){
		for (size_t y{0}; y < lines.size(); y++){
			accessableRolls += (isAccessable(x,y) ? 1 : 0);
		}
	}

	cout << "Accessable rolls:" << accessableRolls << endl;
	return 0;
}

