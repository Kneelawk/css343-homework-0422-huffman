//
// Created by cyan on 4/22/25.
//

#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H
#include <iostream>
#include <cstdint>
#include <map>
#include <queue>

#include "printer.h"

template<typename T>
class HuffmanNode {
public:
    uint32_t code = 0;
    size_t len = 0;
    size_t frequency = 0;
    size_t tiebreaker = 0;

    HuffmanNode() = default;

    HuffmanNode(const size_t frequency, const size_t tiebreaker)
        : frequency(frequency),
          tiebreaker(tiebreaker) {
    }

    HuffmanNode(const uint32_t code, const size_t len, const size_t frequency)
        : code(code),
          len(len),
          frequency(frequency) {
    }

    virtual ~HuffmanNode() = default;

    HuffmanNode(const HuffmanNode &other)
        : code(other.code),
          len(other.len),
          frequency(other.frequency) {
    }

    HuffmanNode(HuffmanNode &&other) noexcept
        : code(other.code),
          len(other.len),
          frequency(other.frequency) {
    }

    HuffmanNode &operator=(const HuffmanNode &other) {
        if (this == &other)
            return *this;
        code = other.code;
        len = other.len;
        frequency = other.frequency;
        return *this;
    }

    HuffmanNode &operator=(HuffmanNode &&other) noexcept {
        if (this == &other)
            return *this;
        code = other.code;
        len = other.len;
        frequency = other.frequency;
        return *this;
    }

    virtual HuffmanNode *cloned() = 0;

    virtual bool isParent() = 0;

    virtual void assign(uint32_t prefix, size_t prefix_len) = 0;

    virtual void print(size_t indent) = 0;
};

template<typename T>
class HuffmanParent final : public HuffmanNode<T> {
public:
    HuffmanNode<T> *left = nullptr;
    HuffmanNode<T> *right = nullptr;

    HuffmanParent() = default;

    HuffmanParent(const size_t frequency, const size_t tiebreaker, HuffmanNode<T> *left, HuffmanNode<T> *right)
        : HuffmanNode<T>(frequency, tiebreaker),
          left(left),
          right(right) {
    }

    HuffmanParent(uint32_t code, size_t len, size_t frequency, HuffmanNode<T> *left, HuffmanNode<T> *right)
        : HuffmanNode<T>(code, len, frequency),
          left(left),
          right(right) {
    }

    ~HuffmanParent() override {
        // theoretically these should never be nullptr, but weird things can happen, best to protect against it
        if (left != nullptr) {
            delete left;
        }
        if (right != nullptr) {
            delete right;
        }
    }

    HuffmanParent(const HuffmanParent &other)
        : HuffmanNode<T>(other),
          left(other.left->cloned()),
          right(other.right->cloned()) {
    }

    HuffmanParent(HuffmanParent &&other) noexcept
        : HuffmanNode<T>(std::move(other)),
          left(other.left),
          right(other.right) {
    }

    HuffmanParent &operator=(const HuffmanParent &other) {
        if (this == &other)
            return *this;
        HuffmanNode<T>::operator =(other);
        left = other.left->cloned();
        right = other.right->cloned();
        return *this;
    }

    HuffmanParent &operator=(HuffmanParent &&other) noexcept {
        if (this == &other)
            return *this;
        HuffmanNode<T>::operator =(std::move(other));
        left = other.left;
        right = other.right;
        return *this;
    }

    HuffmanNode<T> *cloned() override {
        HuffmanNode<T> *newLeft = nullptr;
        HuffmanNode<T> *newRight = nullptr;
        if (this->left != nullptr) {
            newLeft = this->left->cloned();
        }
        if (this->right != nullptr) {
            newRight = this->right->cloned();
        }
        return new HuffmanParent(this->code, this->len, this->frequency, newLeft, newRight);
    }

    bool isParent() override {
        return true;
    }

    void assign(uint32_t prefix, size_t prefix_len) override {
        this->code = prefix;
        this->len = prefix_len;

        if (left != nullptr) {
            // 0
            left->assign(prefix << 1, prefix_len + 1);
        }
        if (right != nullptr) {
            // 1
            right->assign((prefix << 1) | 1, prefix_len + 1);
        }
    }

    void print(const size_t indent) override {
        const std::string indentStr(indent, ' ');
        std::cout << indentStr << "Parent : " << printCode(this->code, this->len) << " (" << this->frequency << ") {" <<
                std::endl;
        if (left != nullptr) {
            std::cout << indentStr << "left:" << std::endl;
            left->print(indent + 2);
        }
        if (right != nullptr) {
            std::cout << indentStr << "right:" << std::endl;
            right->print(indent + 2);
        }
        std::cout << indentStr << '}' << std::endl;
    }
};

template<typename T>
class HuffmanLeaf final : public HuffmanNode<T> {
public:
    T data;

    HuffmanLeaf() = default;

    HuffmanLeaf(const size_t frequency, const size_t tiebreaker, const T &data)
        : HuffmanNode<T>(frequency, tiebreaker),
          data(data) {
    }

    HuffmanLeaf(uint32_t code, size_t len, size_t frequency, const T &data)
        : HuffmanNode<T>(code, len, frequency),
          data(data) {
    }

    HuffmanLeaf(const HuffmanLeaf &other)
        : HuffmanNode<T>(other),
          data(other.data) {
    }

    HuffmanLeaf(HuffmanLeaf &&other) noexcept
        : HuffmanNode<T>(std::move(other)),
          data(std::move(other.data)) {
    }

    HuffmanLeaf &operator=(const HuffmanLeaf &other) {
        if (this == &other)
            return *this;
        HuffmanNode<T>::operator =(other);
        data = other.data;
        return *this;
    }

    HuffmanLeaf &operator=(HuffmanLeaf &&other) noexcept {
        if (this == &other)
            return *this;
        HuffmanNode<T>::operator =(std::move(other));
        data = std::move(other.data);
        return *this;
    }

    HuffmanNode<T> *cloned() override {
        return new HuffmanLeaf(this->code, this->len, this->frequency, this->data);
    }

    bool isParent() override {
        return false;
    }

    void assign(uint32_t prefix, size_t prefix_len) override {
        this->code = prefix;
        this->len = prefix_len;
    }

    void print(const size_t indent) override {
        std::cout << std::string(indent, ' ') << "Leaf : '" << data << "' " << this->frequency << " (" <<
                printCode(this->code, this->len) << ");" << std::endl;
    }
};

template<typename T>
class HuffmanNodeComparator {
public:
    bool operator()(const HuffmanNode<T> *a, const HuffmanNode<T> *b) {
        if (a->frequency != b->frequency) return a->frequency > b->frequency;
        return a->tiebreaker > b->tiebreaker;
    }
};

template<typename T>
class HuffmanTree {
    HuffmanNode<T> *root = nullptr;

public:
    explicit HuffmanTree(const std::map<T, size_t> &frequencies) {
        if (frequencies.empty()) {
            return;
        }

        std::priority_queue<HuffmanNode<T> *, std::vector<HuffmanNode<T> *>, HuffmanNodeComparator<T> > q;
        size_t tiebreaker = 0;
        for (const auto &pair: frequencies) {
            q.push(new HuffmanLeaf<T>(pair.second, tiebreaker++, pair.first));
        }
        while (q.size() > 1) {
            HuffmanNode<T> *left = q.top();
            q.pop();
            HuffmanNode<T> *right = q.top();
            q.pop();
            q.push(new HuffmanParent<T>(left->frequency + right->frequency, tiebreaker++, left, right));
        }
        root = q.top();
        q.pop();

        root->assign(0, 0);
    }

    ~HuffmanTree() {
        if (root != nullptr) {
            delete root;
        }
    }

    void collect(std::vector<HuffmanLeaf<T> > &leafCollector) const {
        if (root == nullptr) {
            return;
        }

        std::queue<HuffmanNode<T> *> q;
        q.push(root);

        while (!q.empty()) {
            HuffmanNode<T> *node = q.front();
            q.pop();
            if (node->isParent()) {
                HuffmanParent<T> *parent = dynamic_cast<HuffmanParent<T> *>(node);
                q.push(parent->left);
                q.push(parent->right);
            } else {
                HuffmanLeaf<T> *leaf = dynamic_cast<HuffmanLeaf<T> *>(node);
                leafCollector.push_back(*leaf);
            }
        }
    }

    void collectMap(std::map<T, HuffmanLeaf<T> > &leafMap) const {
        if (root == nullptr) {
            return;
        }

        std::queue<HuffmanNode<T> *> q;
        q.push(root);

        while (!q.empty()) {
            HuffmanNode<T> *node = q.front();
            q.pop();
            if (node->isParent()) {
                HuffmanParent<T> *parent = dynamic_cast<HuffmanParent<T> *>(node);
                q.push(parent->left);
                q.push(parent->right);
            } else {
                HuffmanLeaf<T> *leaf = dynamic_cast<HuffmanLeaf<T> *>(node);
                leafMap[leaf->data] = *leaf;
            }
        }
    }

    HuffmanLeaf<T> get(uint32_t code) const {
        HuffmanNode<T> *node = root;
        while (node->isParent()) {
            HuffmanParent<T> *parent = dynamic_cast<HuffmanParent<T> *>(node);
            if (code & 1) {
                node = parent->right;
            } else {
                node = parent->left;
            }
            code >>= 1;
        }
        return *dynamic_cast<HuffmanLeaf<T> *>(node);
    }
};

#endif //HUFFMAN_TREE_H
