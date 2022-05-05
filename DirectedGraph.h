#pragma once
#include<list>
#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<map>
#include<sstream> 
#include<algorithm> 
#include<set> 

/**
* @brief
* structure that help to search cycles in graph
*/

struct Graph
{
    /**
    * @brief
    * map of the connections of the node
    */

    std::map<int, std::list<int>> neighbors;

    /**
    * @brief
    * set of cycles
    */

    std::set<std::string> cycles;

    /**
    * @param v incoming arrows of nodes
    * @param w outgoing arrows of nodes
    * @brief
    * function that add connection of nodes
    */

    void addEdge(int v, int w);

    /**
    * @brief
    * function that searching for cycles in given graph
    */

    void depthSearch();

    /**
    * @param V size of graph
    * @param goTo to which node need to go
    * @param path path that were covered
    * @brief
    * function that is one of the stage of the recursion which search in node's neightbors
    */

    void depthSearchHelper(int V, int goTo, std::vector<int>& path);
};

/**
* @param FILE_NAME file name
* @param strings cycles found
* @brief
* function that print found cycles to a file
*/

void print_vector(const std::string& FILE_NAME, const std::set<std::string>& strings);

/**
* @param inputFile input file
* @param outputFile output file
* @brief
* function that execute program, check the correct syntax of the content of the input file. Verification.
*/

int execute(std::string inputFile, std::string outputFile);
