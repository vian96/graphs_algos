#ifndef SPLAY_TREE_HPP
#define SPLAY_TREE_HPP

#include "search_tree.hpp"

template<typename T>
struct SplayTree {
    Node<T> *root;

    SplayTree<T>(T data_) 
        : root(new Node<T>(data_)) {}

    SplayTree<T>(Node<T> *root_) {
        root = root_;
    }

    template <typename T_iter>
    SplayTree<T>(T_iter entries)
        : root(new Node<T>(entries)) {}

    ~SplayTree<T>() {
        delete root;
    }

    void splay(Node<T> *x) {
        while (x->parent) { // if is not parent yet
            auto p = x->parent;
            if (!p->parent) { // zig step
                if (x == p->left)
                    p->rotate_right();
                else
                    p->rotate_left();
                root = x;
                return;
            }

            auto g = p->parent;
            if (x == p->left && p == g->left) { // zig-zig step
                g->rotate_right();
                p->rotate_right();
            } else if (x == p->right && p == g->right) { // zig-zig
                g->rotate_left();
                p->rotate_left();
            } else if (x == p->right) { // zig-zag step
                p->rotate_left();
                g->rotate_right();
            } else if (x == p->left) { // zig-zag
                p->rotate_right();
                g->rotate_left();
            }
        }
        root = x;
    }

    void add_entry(T data) {
        splay(root->add_entry(data));
    }

    void remove_entry(T data) {
        auto x = root->remove_entry(data);
        if (x) 
            splay(x);
    }
};

#endif // SPLAY_TREE_HPP
