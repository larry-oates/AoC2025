#include <fstream>
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

struct JunctionBox{
	long long int x;
	long long int y;
	long long int z;
	int circuit;
};

struct Connection{
	long long int distance;
	size_t boxId1;
	size_t boxId2;
};

long long int getDistance(JunctionBox box1, JunctionBox box2){
	return (box1.x - box2.x) * (box1.x - box2.x) + (box1.y - box2.y)*(box1.y - box2.y) + (box1.z - box2.z)*(box1.z - box2.z);
}

bool compConnection(Connection a, Connection b){
	return a.distance < b.distance;
}

int main(){
	int numOfBoxs {0};
	fstream input("input");
	vector<JunctionBox> junctionBoxs{};
	vector<Connection> connections{};

	for (string line; getline(input, line); numOfBoxs++){
		JunctionBox jbox;
		stringstream sline(line);
		char c;
		sline >> jbox.x >> c >> jbox.y >> c >> jbox.z;
		jbox.circuit = numOfBoxs;
		junctionBoxs.push_back(jbox);
	}

	for (size_t i{0}; i < junctionBoxs.size() - 1; i++ ){
		for (size_t j{i+1}; j < junctionBoxs.size(); j++){
			connections.push_back(Connection{getDistance(junctionBoxs[i],junctionBoxs[j]),i,j});
		}
	}

	// Sort - shortest connections first
	sort(connections.begin(), connections.end(), compConnection);

	// Connect the circuts
	for (size_t connectionIdx{0}; connectionIdx < connections.size(); connectionIdx++){
		const auto& conn = connections.at(connectionIdx);
		
		int sourceCircuit = junctionBoxs.at(conn.boxId1).circuit;
		int targetCircuit = junctionBoxs.at(conn.boxId2).circuit;

		bool fullyConnected {true};
		if (sourceCircuit != targetCircuit) {
		    for (size_t box{0}; box < junctionBoxs.size(); box++){
			if (junctionBoxs.at(box).circuit == targetCircuit)
			    junctionBoxs.at(box).circuit = sourceCircuit;   
			if (junctionBoxs.at(box).circuit != sourceCircuit)
				fullyConnected = false;
		    }
			if (fullyConnected) {
				cout << junctionBoxs.at(conn.boxId1).x << '*' << junctionBoxs.at(conn.boxId2).x << '=' <<
					junctionBoxs.at(conn.boxId1).x * junctionBoxs.at(conn.boxId2).x << endl;
			}
		}
	    }

	return 0;
}
