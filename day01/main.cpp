#include <iostream>
#include <fstream>
#include <cassert>

int main() {
	constexpr int startingPos{50};
	constexpr int NumOfPips{100};

	std::ifstream input("input.txt");
	char direction {};
	int distance {};
	int position {startingPos};
	int numOfZeros{0};

	while (input >> direction >> distance) {
		numOfZeros += distance/NumOfPips;		
		distance %= NumOfPips;
		switch (direction) {
			case 'L': {
				if (position == 0) numOfZeros--;
				position -= distance;
				if (position < 0){
					position += NumOfPips;
					numOfZeros++;
				}
				if (position == 0) numOfZeros++;
				break;
			}
			case 'R': {
				position += distance;
				if (position >= NumOfPips) {
					position -= NumOfPips;
					numOfZeros++;
				}
				break;
			}
			default:
				assert("Unknown direction parsed");
		}
	}

	std::cout << "Real password is: " << numOfZeros << std::endl;
	return 0;
}
