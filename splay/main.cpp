#include "search_tree.hpp"

#include <vector>
#include <iostream>

int main() {
    // Node<int> root(std::vector<int>({1,5,2,24,6,72,124,3}));
    Node<int> *root = new Node<int>(std::vector<int>({60,50,40,30,20,10, 51, 52, 57, 52, 41,42,43, 70, 80, 90}));
    root->dump();
    // root->raw_dump();
    root = root->rotate_right();
    // root->left->rotate_right();
    std::cout << "rotated\n";
    // root->raw_dump();
    root->dump();
    root = root->rotate_left();
    std::cout << "left rot\n";
    root->dump();
    root->print_sorted();
    std::cout << root->check_entry(72) << root->check_entry(4);
}
