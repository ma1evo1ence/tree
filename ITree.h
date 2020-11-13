
#ifndef PROJECT_TREES_ITREE_H
#define PROJECT_TREES_ITREE_H

#endif //PROJECT_TREES_ITREE_H

class ITree{
    virtual ITree* insert(int num) = 0;
    virtual ITree* erase(int num) = 0;
    virtual ITree* find(int num) = 0;

    ~ITree() = default;;
};
