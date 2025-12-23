#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <map>

using namespace std;

// Paths to zero that pass through the required named server nodes
struct Paths 
{
	long long neither{-1ll};
	long long fft{0ll};
	long long dac{0ll};
	long long both{0ll};
};

struct Server
{
	string name;
	vector<Server *> outputs;
	// Cache paths found if accessed again
	Paths paths{};
};

// Using a map is safer as it doesn't invalidate pointers on insertion
Server *find_or_create_server(map<string, Server> &servers, const string &name)
{
	// operator[] will create a new Server if 'name' is not a key,
	// and return a reference to the existing or new Server.
	Server &server = servers[name];
	// If it was newly created, its name will be empty.
	if (server.name.empty())
		server.name = name;
	return &server;
}

Paths count_paths(Server *server)
{
	// If already searched, return cached value
	if (server->paths.neither != -1)
	return server->paths;
	
	Paths pathCount{};
	pathCount.neither = 0;
	for (auto output : server->outputs)
	{
		if (output->name == "out"){
			pathCount.neither++;
		}
		else {
			Paths outPaths = count_paths(output);
			pathCount.both += outPaths.both;
			pathCount.fft += outPaths.fft;
			pathCount.dac += outPaths.dac;
			pathCount.neither += outPaths.neither;
		}
	}
	if (server->name == "fft"){
		pathCount.both += pathCount.dac;
		pathCount.dac = 0;
		pathCount.fft += pathCount.neither;
		pathCount.neither = 0;
	}
	else if (server->name == "dac"){
		pathCount.both += pathCount.fft;
		pathCount.fft = 0;
		pathCount.dac += pathCount.neither;
		pathCount.neither = 0;
	}
	server->paths = pathCount;
	return pathCount;
}

int main()
{
	fstream input("input");
	map<string, Server> servers;
	for (string line; getline(input, line);)
	{
		stringstream ss(line);
		string server_name;
		ss >> server_name;
		server_name.pop_back();
		Server *current_server{find_or_create_server(servers, server_name)};

		string output_name;
		// The rest of the line contains the names of the output servers
		while (ss >> output_name)
		{
			// Find or create the output server
			Server *output_server = find_or_create_server(servers, output_name);
			// Add the output server to the current server's outputs
			current_server->outputs.push_back(output_server);
		}
	}

	Server *start_server = find_or_create_server(servers, "svr");
	cout << "Total paths to out:" << count_paths(start_server).both << endl;

	return 0;
}
