#include "search_tree.hpp"

#include <vector>
#include <iostream>

void test() {
    Node<int> *root = new Node<int>(std::vector<int>({60,50,40,30,20,10, 51, 52, 57, 52, 41,42,43, 70, 80, 90}));
    root->dump();
    // root->raw_dump();
    // root = root->rotate_right();
    // // root->left->rotate_right();
    // std::cout << "rotated\n";
    // // root->raw_dump();
    // root->dump();
    // root = root->rotate_left();
    // std::cout << "left rot\n";
    // root->dump();
    root->print_sorted();
    std::cout << std::endl;
    root->remove_entry(50);
    root->dump();
    std::cout << root->check_entry(72) << root->check_entry(4);
    std::cout << "validatiing...\n";
    root->validate_parentness();
    std::cout << "validation of parentness is ok if no errors\n";
    delete root;
}

int main() {
    test();
}
