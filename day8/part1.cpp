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
	constexpr int numOfConnections {1000};
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
	for (size_t connectionIdx{0}; connectionIdx < numOfConnections; connectionIdx++){
		const auto& conn = connections.at(connectionIdx);
		
		int sourceCircuit = junctionBoxs.at(conn.boxId1).circuit;
		int targetCircuit = junctionBoxs.at(conn.boxId2).circuit;

		if (sourceCircuit != targetCircuit) {
		    for (size_t box{0}; box < junctionBoxs.size(); box++){
			if (junctionBoxs.at(box).circuit == targetCircuit)
			    junctionBoxs.at(box).circuit = sourceCircuit;   
		    }
		}
	    }

	unordered_map<int, int> circuitFreq;
	for(auto b: junctionBoxs){
		circuitFreq[b.circuit]++;
	}

	long int freq1{};
	long int freq2{};
	long int freq3{};
	for(auto b: circuitFreq){
		if (b.second > freq1){
			freq3 = freq2;
			freq2 = freq1;
			freq1 = b.second;
		}
		else if(b.second > freq2){
			freq3 = freq2;
			freq2 = b.second;
		}
		else if(b.second > freq3)
			freq3 = b.second;
	}
	
	cout << freq1 << '*' << freq2 << '*' << freq3 << '=' << freq1*freq2*freq3 << endl;

	return 0;
}
