#include <iostream>
#include "coursework.h"

int main() {

    namespace br = ::br3nder;

    std::ifstream file(R"(C:\Users\brend\CLionProjects\untitled3\file.txt)");
    br::List<char> v;
    std::string s = read(file);
    fill_vertexes_list(v, s);
    int** matrix = get_capacity_matrix(s, v);
            std::cout << s << "\nList of vertexes: " << v << "\nsize: " << v.size() << "\nmatrix is: \n";
    for(int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v.size(); j++)
            std::cout << matrix[i][j] << " ";
        std::cout << std::endl;
    }

    std::cout << "\nmax flow: " << carp_fish(matrix, 'S', 'T', v);

    return 0;
}
