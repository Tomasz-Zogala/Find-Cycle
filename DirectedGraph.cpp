#include<list>
#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<map>
#include<sstream> 
#include<algorithm> 
#include<set> 
#include "DirectedGraph.h"

void Graph::addEdge(int v, int w)
{
    neighbors[v].push_back(w);
}

void Graph::depthSearch() {
    int V = neighbors.empty() ? 0 : neighbors.rbegin()->first;
    for (auto& kv : neighbors) {
        std::vector<int> path;
        depthSearchHelper(V, kv.first, path);
    }
}

void Graph::depthSearchHelper(int V, int node, std::vector<int>& path)
{
    path.push_back(node);
    for (const auto& neighbour : neighbors[node]) {
        bool neighborVisited = false;
        for (int i = 0; i < path.size(); ++i) {
            if (neighbour != path[i]) {
                continue;
            }
            neighborVisited = true;

            if (i > 0) {
                continue;
            }

            std::vector<int> cycle;
            for (int j = i; j < path.size(); ++j) {
                cycle.push_back(path[j]);
            }

            int minNodeIndex = 0;
            for (int j = 1; j < cycle.size(); ++j) {
                if (cycle[j] < cycle[minNodeIndex]) {
                    minNodeIndex = j;
                }
            }

            std::vector<int> standardizedCycle;
            for (int j = 0; j < cycle.size(); ++j) {
                standardizedCycle.push_back(cycle[(j + minNodeIndex) % cycle.size()]);
            }

            std::stringstream buffer;
            for (int j = 0; j < standardizedCycle.size(); ++j) {
                buffer << standardizedCycle[j] << " -> ";
            }
            buffer << standardizedCycle[0];
            std::string cycleStr = buffer.str();
            cycles.emplace(cycleStr);
        }
        if (!neighborVisited) {
            depthSearchHelper(V, neighbour, path);
        }
    }
}

void print_vector(const std::string& FILE_NAME, const std::set<std::string>& strings)
{
    std::ofstream file(FILE_NAME);
    if (!file) {
        std::cout << "Can't open output file '" << FILE_NAME << "' " << std::endl;
        exit(1);
    }

    for (const std::string n : strings) {
        file << n << std::endl;
    }
}

int execute(std::string inputFile, std::string outputFile)
{
    Graph g;
    std::ifstream file(inputFile);
    if (!file)
    {
        std::cout << "Can't open input file '" << inputFile << "' " << std::endl;
        return 1;
    }

    std::string word1;
    std::string word2;
    std::string word3;
    while (true) {
        if (!(file >> word1)) {
            // EOF
            break;
        }
        //checking if there is an arrow
        if (!(file >> word2) || (word2 != "->")) {
            std::cout << "Invalid graph syntax - missing arrow and target node";
            return 1;
        }
        if (!(file >> word3)) {
            std::cout << "Invalid graph syntax - missing target node";
            return 1;
        }
        if (word3[word3.size() - 1] == ',') {
            word3.pop_back();
        }
        int start = stoi(word1);
        int end = stoi(word3);
        g.addEdge(start, end);
    }

    g.depthSearch();
    if (g.cycles.empty()) {
        std::cout << "No cycles" << std::endl;
    }
    else {
        for (const auto& cycle : g.cycles) {
            std::cout << cycle << std::endl;
        }
    }


    if (g.cycles.empty()) {
        std::set<std::string> toPrint;
        toPrint.emplace("No cycles");
        print_vector(outputFile, toPrint);
    }
    else {
        print_vector(outputFile, g.cycles);
    }
    return 0;
}
