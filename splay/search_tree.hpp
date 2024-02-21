#ifndef SEARCH_TREE_HPP
#define SEARCH_TREE_HPP

#include <iostream>
#include <string>
#include <algorithm>
#include <cassert>

template<typename T>
struct Node {
    T data;
    Node<T> *left;
    Node<T> *right;
    Node<T> *parent;

    Node<T>(T data_, Node<T> *parent_=nullptr, Node<T> *left_=nullptr, Node<T> *right_=nullptr) 
        : data(data_), parent(parent_), left(left_), right(right_) {}

    template <typename T_iter>
    Node<T>(T_iter entries) {
        auto it = entries.begin();
        this->data = *it;
        parent = nullptr;
        left = nullptr;
        right = nullptr;
        for (it++; it != entries.end(); it++)
            add_entry(*it);
    }

    ~Node<T>() {
        delete left;
        delete right;
    }

    // returns pointer to inserted Node
    Node<T> *add_entry(T data) {
        auto parent = this;
        auto child = &parent;
        while (*child) {
            parent = *child;
            if (data <= parent->data) 
                child = &parent->left;
            else 
                child = &parent->right;
        }
        *child = new Node<T>(data, parent);
        return *child;
    }

    // removes by value, returns parent or nullptr if not found, WITH DELETE
    Node<T> *remove_entry(T data_) {
        auto node = find_entry(data_);
        if (!node) 
            return nullptr;
        auto p = node->parent;
        delete node->remove();
        return p;
    }

    // removes this node, WITHOUT DELETE - returns what should be deleted
    Node<T> *remove() {
        if (!(left || right)) {
            auto p = parent;
            auto ptr = p->get_child_ptr(this);
            *ptr = nullptr;
            return this;
        }
        if (!(left && right)) {
            auto p = parent;
            auto ptr = p->get_child_ptr(this);
            auto child = (left) ? (left) : (right);
            *ptr = child;
            left = nullptr; // so no deletion in destructor
            right = nullptr;
            child->parent = p;
            return this;
        }
        // both are not nullptr
        auto next = right;
        while (next->left != nullptr)
            next = next->left;
        std::swap(next->data, data); // TODO if data is big not efficient?
        return next->remove();
    }

    void raw_dump(int depth=0) {
        std::cout << data << ' ' << this << ' ' << parent << ' '
                  << left << ' ' << right << ' ' << '\n';
        if (right) {
            std::cout << std::string(depth, '\t') << "right: ";
            right->raw_dump(depth+1);
        }
        if (left) {
            std::cout << std::string(depth, '\t') << "left: ";
            left->raw_dump(depth+1);
        }
    }

    void dump(int depth=0) {
        if (right)
            right->dump(depth+1);
        else 
            std::cout << std::string(depth+1, '\t') << "nullptr" << std::endl;
        std::cout << std::string(depth, '\t') << data << std::endl;
        if (left) 
            left->dump(depth+1);
        else 
            std::cout << std::string(depth+1, '\t') << "nullptr" << std::endl;
    }

    void print_sorted(char delim=' ') {
        if (left)
            left->print_sorted();
        std::cout << data << delim;
        if (right)
            right->print_sorted();
    }

    Node<T> *find_entry(T data) {
        auto node = this;
        while (node && node->data != data) {
            if (data <= node->data) 
                node = node->left;
            else 
                node = node->right;
        }
        return node;
    }

    bool check_entry(T data) {
        return !!find_entry(data);
    }

    // returns pointer to new root (upper node)
    Node<T> *rotate_right() {
        if (!left) {
            assert(left!=nullptr);
            return this;
        }
        auto left_ = left;
        auto p = parent;
        auto temp = left_->right;
        if (p)
            *(p->get_child_ptr(this)) = left_;
        left_->parent = p;
        left = temp;
        if (temp)
            temp->parent = this;
        parent = left_;
        left_->right = this;
        return left_;
    }

    // returns pointer to new root (upper node)
    Node<T> *rotate_left() {
        if (!right) {
            assert(right!=nullptr);
            return this;
        }
        auto right_ = right;
        auto p = parent;
        auto temp = right_->left;
        if (p)
            *(p->get_child_ptr(this)) = right_;
        right_->parent = p;
        right = temp;
        if (temp)
            temp->parent = this;
        parent = right_;
        right_->left = this;
        return right_;
    }

    // returns pointer to struct variable holding specified pointer
    Node<T> **get_child_ptr(Node<T> *ptr) {
        if (left == ptr)
            return &left;
        if (right == ptr)
            return &right;
        return nullptr;
    }

    void validate_parentness() {
        if (left) {
            assert(left->parent == this);
            left->validate_parentness();
        }
        if (right) {
            assert(right->parent == this);
            right->validate_parentness();
        }
    }
};

#endif // SEARCH_TREE_HPP