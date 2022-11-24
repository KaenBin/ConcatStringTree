#ifndef __CONCAT_STRING_TREE_H__
#define __CONCAT_STRING_TREE_H__

#include "main.h"

// Initialize curID
static int curID = 1;

class ConcatStringTree {    
public:    
    class Node {
        public:
        class ParentsTree {
            public:
            int id, height, parSize;
            ParentsTree* pLeft,* pRight;

            ParentsTree(int curID = 0, ParentsTree* left = nullptr, ParentsTree* right = nullptr, int h = 0) : id(curID), pLeft(left), pRight(right), height(h) {}
            int getHeight(ParentsTree*);
            ParentsTree* rightRotate(ParentsTree*);
            ParentsTree* leftRotate(ParentsTree*);
            ParentsTree* insert(ParentsTree*, int);
            ParentsTree* delParsTree(ParentsTree*, int);
            ~ParentsTree() {}

            // Helper functions
            string preOrderString() const;
            ParentsTree* maxID(ParentsTree*);
            int valueBalance(ParentsTree*);

            int size() const { return parSize; }
            string toStringPreOrder() const;
        };
        ParentsTree* pParent;

        int leftLength, length, id;
        string data;
        Node* left,* right;
        Node(string s, Node* pLeft = nullptr, Node* pRight = nullptr) : data(s), left(pLeft), right(pRight) {
            leftLength = 0;
            length = data.length(); 

            pParent = nullptr;
            id = curID;
            pParent = pParent->insert(pParent, id);
            pParent->parSize = 1;
            curID++;
        }
        ~Node() {}

        string preOrderString() const;
        string preOrder() const;
        int indexOf(char c) const;
        Node* subStr(int, int) const;
        Node* helpReverse() const;
    };
    Node* root;

    ConcatStringTree(const char * s);
    int length() const;
    char get(int index) const;
    int indexOf(char c) const;
    string toStringPreOrder() const;
    string toString() const;
    ConcatStringTree concat(const ConcatStringTree & otherS) const;
    ConcatStringTree subString(int from, int to) const;
    ConcatStringTree reverse() const;

    int getParTreeSize(const string & query) const;
    string getParTreeStringPreOrder(const string & query) const;
    
    ~ConcatStringTree();
};

class ReducedConcatStringTree; // forward declaration
class LitStringHash; // forward declaration

class HashConfig {
private:
    int p;
    double c1, c2;
    double lambda;
    double alpha;
    int initSize;

    friend class ReducedConcatStringTree;
    friend class LitStringHash;
};

class LitStringHash {
public:
    LitStringHash(const HashConfig & hashConfig);
    int getLastInsertedIndex() const;
    string toString() const;
};

class ReducedConcatStringTree /* */ {
public:
    ReducedConcatStringTree(const char * s, LitStringHash * litStringHash);
    LitStringHash * litStringHash;
};

#endif // __CONCAT_STRING_TREE_H__