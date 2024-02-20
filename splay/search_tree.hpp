#include <iostream>
#include <string>
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

    ~Node() {
        delete left;
        delete right;
    }

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

    bool check_entry(T data) {
        auto node = this;
        while (node && node->data != data) {
            if (data <= node->data) 
                node = node->left;
            else 
                node = node->right;
        }
        return !!node;
    }

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
        parent = left_;
        left_->right = this;
        return left_;
    }

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
        parent = right_;
        right_->left = this;
        return right_;
    }

    Node<T> **get_child_ptr(Node<T> *ptr) {
        if (left == ptr)
            return &left;
        if (right == ptr)
            return &right;
        return nullptr;
    }
};