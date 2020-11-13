#include <iostream>
#include <string>

class RBTree {
private:
    struct Node {
        int value;
        Node* parent;
        Node* left; //left child
        Node* right; // right child
        std::string color;
        Node (int n) {
            value = n;
            parent = nullptr;
            left = nullptr;
            right = nullptr;
            color = "red";
        }
    };

    Node* root;
    int nodes_number; // number of nodes in tree

    Node* add_node (int n) {
        Node* x = new Node(n);
        return x;
    }

/**********************************************
 * finding previous by value and next by value element
 * @param x -- element itself
 * @return -- next or previous by value element, respectively
 */

    Node* successor (Node* x) {
        if (x->right != nullptr)
            return tree_minimum(x->right);
        Node* y = x->parent;
        while (y != nullptr && x == y->right) {
            x = y;
            y = x->parent;
        }
        return y;
    }

    Node* predecessor (Node* x) {

        if (x->left != nullptr)
            return tree_maximum(x->left);
        Node* y = x->parent;
        while (y != nullptr && x == y->left) {
            x = y;
            y = x->parent;
        }
        return y;
    }
/**********************************************
 * rotating subtrees
 * @param x -- root of subtree before rotation
 */
    void left_rotate (Node* x)  {
        Node* y = x->right;

        x->right = y->left;
        if (!y->left) {
            y->left->parent = x;
            y->left->parent = x;
        }

        y->parent = x->parent;
        if (x->parent == nullptr) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else x->parent->right = y;

        y->left = x;
        x->parent = y;
    }

    void right_rotate (Node* x)  {
        Node* y = x->left;

        x->left = y->right;
        if (!y->right) {
            y->right->parent = x;
        }

        y->parent = x->parent;
        if (x->parent == nullptr) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else x->parent->right = y;

        y->right = x;
        x->parent = y;
    }
/**********************************************
 * methods to insert element in tree: default and special for red-black tree, with fix of insertion
 * @param z -- element to be inserted
 */
    void tree_insert (Node* z) {
        Node* y = nullptr;
        Node* x = root;

        while (x != nullptr) {
            y = x;
            if (z->value < x->value)
                x = x->left;
            else x = x->right;
        }

        z->parent = y;
        if (y == nullptr)
            root = z;
        else if (z->value < y->value)
            y->left = z;
        else y->right = z;
    }

    void rbtree_insert (Node* x) {
        Node* y;

        tree_insert(x);
        x->color = "red";

        while ((x != root) && (x->parent->color == "red")) {

            if (x->parent == x->parent->parent->left) {
                if (x->parent->parent->right != nullptr) {
                    y = x->parent->parent->right;
                    if (y->color == "red") {
                        x->parent->color = "black";
                        y->color = "black";
                        x->parent->parent->color = "red";
                        x = x->parent->parent;
                    } else if (y->color == "black") {
                        if (x == x->parent->right) {
                            x = x->parent;
                            left_rotate(x);
                        }
                        x->parent->color = "black";
                        x->parent->parent->color = "red";
                        right_rotate(x->parent->parent);
                    }
                }
                else {
                    x->color = "black";
                    break;
                }
            }

            else if (x->parent == x->parent->parent->right) {
                if (x->parent->parent->left != nullptr) {
                    y = x->parent->parent->left;
                    if (y->color == "red") {
                        x->parent->color = "black";
                        y->color = "black";
                        x->parent->parent->color = "red";
                        x = x->parent->parent;
                    } else if (y->color == "black") {
                        if (x == x->parent->left) {
                            x = x->parent;
                            right_rotate(x);
                        }
                        x->parent->color = "black";
                        x->parent->parent->color = "red";
                        left_rotate(x->parent->parent);
                    }
                }
                else {
                    x->color = "black";
                    break;
                }
            }
        }
        root->color = "black";
    }
/**********************************************
 * fixing tree after deletion of an element
 * @param x -- child of the deleted element or nullptr if deleted element had no children
 */
    void rbtree_delete_fixup (Node* x) {
        Node* w;

        while (x != root && x->color == "black") {
            // case x is left child
            if (x == x->parent->left) {
                w = x->parent->right;

                if (w->color == "red") {
                    w->color = "black";
                    left_rotate(x->parent);
                    w = x->parent->right;
                }

                if ((w->left->color == "black") && (w->right->color == "black")) {
                    w->color = "red";
                    x = x->parent;
                } else {
                    if (w->right->color == "black") {
                        w->left->color = "black";
                        w->color = "red";
                        right_rotate(w);
                        w = x->parent->right;
                    }

                    w->color = x->parent->color;
                    x->parent->color = "black";
                    w->right->color = "black";
                    left_rotate(x->parent);
                    x = root;
                }
            }
                //case x is right child, symmetrical
            else if (x == x->parent->right) {
                w = x->parent->left;

                if (w->color == "red") {
                    w->color = "black";
                    right_rotate(x->parent);
                    w = x->parent->left;
                }

                if ((w->left->color == "black") && (w->right->color == "black")) {
                    w->color = "red";
                    x = x->parent;
                } else {
                    if (w->left->color == "black") {
                        w->right->color = "black";
                        w->color = "red";
                        right_rotate(w);
                        w = x->parent->right;
                    }

                    w->color = x->parent->color;
                    x->parent->color = "black";
                    w->left->color = "black";
                    right_rotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = "black";
    }
/**********************************************
 * deleting an element of tree
 * @param z -- element to be deleted
 * @return
 */
    Node* rbtree_delete (Node* z) {
        Node* y;
        Node* x;
        if ((z->left == nullptr) or (z->right == nullptr))
            y = z;
        else y = successor(z);

        if (y->left != nullptr)
            x = y->left;
        else x = y->right;

        if (x != nullptr)
            x->parent = y->parent;
        if (y->parent == nullptr)
            root = x;
        else if (y == y->parent->left)
            x = y->parent->left;
        else x = y->parent->right;

        if (y != z)
            z->value = y->value;

        if (y->color == "black")
            rbtree_delete_fixup(x);
        return y;
    }
/**********************************************
 * delete all nodes of tree
 * @param x -- root of tree
 */
    void clear (Node* x) {
        if (x != nullptr) {
            if (x->right != nullptr) clear(x->right);
            if (x->left != nullptr) clear(x->left);
            clear(x);
        }
    }

public:
    RBTree() {
        root = nullptr;
        nodes_number = 0;
    }

    int get_size () {
        return nodes_number;
    }

    bool is_empty () {
        return (root == nullptr);
    }

    int root_value () {
        return root->value;
    }

    Node* tree_minimum (Node* x) {
        while (x->left != nullptr)
            x = x->left;
        return x;
    }

    Node* tree_maximum (Node* x) {
        while (x->right != nullptr)
            x = x->right;
        return x;
    }

    Node* search (Node* x, int n) {
        if ((x == nullptr) or (n == x->value)) {
            return x;
        }

        if (n < x->value) {
            return search(x->left, n);
        }
        else return search(x->right, n);
    }

    Node* find (int n) { // search in all tree
        if (n < root->value) {
            return search(root->left, n);
        }
        else return search(root->right, n);
    }

    void inorder_tree_walk(Node* x) {
        if (x != nullptr) {
            inorder_tree_walk(x->left);
            std::cout << x->value << std::endl;
            inorder_tree_walk(x->right);
        }
    }

    void insert (Node* x) {
        rbtree_insert(x);
    }

    void insert (int n) {
        rbtree_insert(add_node(n));
        nodes_number++;
    }

    void delete_elem (Node* x) {
        rbtree_delete(x);
    }

    void delete_elem (int n) {
        Node* x = search(root, n);
        if (x != nullptr) {
            rbtree_delete(x);
            nodes_number--;
        }
        else std::cout << "There is no such element in tree." << std::endl;
    }


    ~RBTree() {
        clear(root);
    }
};
