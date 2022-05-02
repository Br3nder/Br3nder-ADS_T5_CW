#include "aads.h"
#include <fstream>
#include <iostream>
#include <limits>
#include <string>

namespace br = ::br3nder;

std::string read(std::ifstream &f){
    std::string s = "",tmp_s;
    if(f.good()){
        while(!f.eof()){
            std::getline(f, tmp_s);
            s += tmp_s + '\n';
        }
    }
    return s;
}


void fill_vertexes_list(br::List<char>& v, std::string &s){
    for(int i = 0; i < s.length(); i++){
        char symbol = s[i];
        if((i % 6 == 0 || i % 6 == 2) && !v.find(symbol))
            v.push_back(symbol);
    }
}

bool bfs(int **capacity_matrix, int n, int to, int* visited, br::List<int>& buffer, int* parents) {
    if (buffer.size() == 0)
        return false;
    int from = buffer[0];
    buffer.remove_front();
    visited[from] = true;
    if (from == to) {
        return true;
    }
    for (int i = 0; i < n; ++i) {
        if (capacity_matrix[from][i] == 0)
            continue;
        if (visited[i] == true || buffer.find(i))
            continue;
        parents[i] = from;
        buffer.push_back(i);
    }
    return bfs(capacity_matrix, n, to, visited, buffer, parents);
}

void print_path(int from, int to, int* parents, br::List<char>& v) {
    if (to == from) {
        std::cout << v[to];
        return;
    }
    int prefrom = parents[to];
    print_path(from, prefrom, parents, v);
    std::cout << " -> " << v[to];
}

int** get_capacity_matrix(std::string &s, br::List<char> &v){
    int** capacity_matrix = new int*[v.size()];
    for(int i = 0; i < s.length(); i++)
        capacity_matrix[i] = new int[v.size()];

    for(int i = 0; i < v.size(); i++)
        for (int j = 0; j < v.size(); j++)
            capacity_matrix[i][j] = 0;

    char v1, v2;
    int c;
    for(int i = 0; i < s.length(); i++){
        if(i % 6 == 0)
            v1 = s[i];
        else if(i % 6 == 2)
            v2 = s[i];
        else if(i % 6 == 4)
            c = s[i] - '0'; //char to int
        else if(s[i] == '\n'){
            capacity_matrix[v.get_index(v1)][v.get_index(v2)] = c;
        }
    }
    return capacity_matrix;
};

int min(int a, int b){
    return (a < b) ? a : b;
}

int carp_fish(int** matrix, char s, char t, br::List<char> v){
    int* path = new int[v.size()];
    int to;
    int from = v.get_index(s);
    for(int j = 0; j < v.size(); j++) {
        path[j] = -1;
    }
    int* visited = new int[v.size()];
    int max_flow = 0;
    br::List<int> buffer;
    buffer.push_back(v.get_index(s));
    while(bfs(matrix, v.size(), v.get_index(t), visited, buffer, path)){
        to = v.get_index(t);
        int c_min = INT_MAX;
        while(to != from){
            c_min = min(c_min, matrix[path[to]][to]);
            to = path[to];
        }
        to = v.get_index(t);
        while(to != from){
            matrix[path[to]][to] = matrix[path[to]][to] - c_min;
            matrix[to][path[to]] += c_min;
            to = path[to];
        }
        max_flow += c_min;
        buffer = br::List<int>();
        buffer.push_back(v.get_index(s));
        for(int j = 0; j < v.size(); j++)
            path[j] = -1;
        visited = new int[v.size()];
    }
    return max_flow;
}
