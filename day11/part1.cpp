#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <map>

using namespace std;

struct Server
{
	string name;
	vector<Server *> outputs;
	// Cache paths found if accessed again
	long long pathsToZero{-1};
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

long long count_paths_to_out(Server *server)
{
	long long pathCount{0ll};

	// If already searched, return cached value
	if (server->pathsToZero != -1)
		return server->pathsToZero;

	for (auto output : server->outputs)
	{
		if (output->name == "out")
			pathCount++;
		else
			pathCount += count_paths_to_out(output);
	}
	server->pathsToZero = pathCount;
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

	Server *start_server = find_or_create_server(servers, "you");
	cout << "Total paths to out:" << count_paths_to_out(start_server) << endl;

	return 0;
}
