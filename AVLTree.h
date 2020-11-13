
#ifndef PROJECT_TREES_AVLTREE_H
#define PROJECT_TREES_AVLTREE_H

#endif //PROJECT_TREES_AVLTREE_H

# include <iostream>


class AVLTree {
private:
    int key = 2e9;
    unsigned int height = 0;
    int size = 1;
    int is_root = 1;
    AVLTree* left = nullptr;
    AVLTree* right = nullptr;

    void fix_height() { // пересчет высоты дерева
        unsigned int hl = left->get_height();
        unsigned int hr = right->get_height();
        height = (hl>hr ? hl : hr) + 1 - is_root;
    }

    AVLTree* rotateright() { // правый поворот вокруг node
        AVLTree* new_node = left;
        left = new_node->right;
        new_node->right = this;
        fix_height();
        new_node->fix_height();

        return new_node;
    }

    AVLTree* rotateleft() { // левый поворот вокруг node
        AVLTree* new_node = right;
        right = new_node->left;
        new_node->left = this;
        fix_height();
        new_node->fix_height();

        return new_node;
    }

    AVLTree* balance() { // балансировка узла node
        fix_height();

        if (b_factor() == 2) {
            if (right->b_factor() < 0)
                right = right->rotateright();

            return rotateleft();
        }

        if (b_factor() == -2) {
            if (left->b_factor() > 0)
                left = left->rotateleft();

            return rotateright();
        }

        return this; // балансировка не нужна
    }

    AVLTree* removemin() { // удаление узла с минимальным ключом из дерева node
        if (left == nullptr)
            return right;

        left = left->removemin();

        return balance();
    }


public:
    AVLTree() {
        int key;
        unsigned int height;
        int size;
        int is_root;
        AVLTree* left;
        AVLTree* right;
    }
/*
    ~AVLTree() {
        delete left;
        delete right;
    }
*/
    unsigned int get_height() { // возвращает высоту дерева
        return this ? height : 0;
    }

    int b_factor() { // возвращает разность высот правой и левой ветвей дерева
        return right->get_height() - left->get_height();
    }

    AVLTree* insert(int k) { // вставка ключа k в дерево с корнем node
        if (!this) {
            AVLTree* new_node = new AVLTree;
            new_node->key = k;
            new_node->is_root = 0;
            new_node->height = 1;
            return new_node;
        }

        ++size;

        if (k < key)
            left = left->insert(k);
        else
            right = right->insert(k);

        if (!is_root) {
            return balance();
        } else {
            fix_height();
            return this;
        }
    }

    AVLTree* find_min() { // поиск узла с минимальным ключом в дереве node
        if (left)
            return left->find_min();
        else if (is_root) { // если дерево пустое
            std::cout << "err find_min in empty tree";
            exit(0);
        } else {
            return this;
        }
    }

    AVLTree* erase(int k) { // удаление ключа k из дерева node
        if (!this)
            return nullptr;

        --size;

        if (k < key)
            left = left->erase(k);
        else if (k > key) {
            right = right->erase(k);
        } else { //  k == p->key
            if (!right) {
                AVLTree* l = left;
                delete this;

                return l;
            }

            AVLTree* min = right->find_min();
            min->right = right->removemin();
            min->left = left;
            delete this;

            return min->balance();
        }

        if (!is_root) {
            return balance();
        } else {
            fix_height();
            return this;
        }
    }

    AVLTree* find (int k) { // возвращает адрес ключа по значению k
        if (this == nullptr)
            return nullptr;

        if (k < key)
            return left->find(k);
        else if (k > key)
            return right->find(k);
        else
            return this;
    }

    int get_key(AVLTree* node) { // возвращает значение ключа по адресу
        return node->key;
    }

    int get_size() { // возвращает количество элементов в дереве
        return size - is_root;
    }

    bool empty() { // проверяет дерево на пустоту
        return left || right ? 0 : 1;
    }
};