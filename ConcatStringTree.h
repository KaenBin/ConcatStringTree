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
            int id = -1, height, parSize;
            ParentsTree* pLeft,* pRight;

            ParentsTree(int curID = 0, ParentsTree* left = nullptr, ParentsTree* right = nullptr, int h = 0) : id(curID), pLeft(left), pRight(right), height(h), parSize(1) {}
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
            
            if (data.empty())
                return;
            
            pParent = nullptr;
            id = curID;
            pParent = pParent->insert(pParent, id);
            pParent->parSize = 1;
            curID++;
        }
        ~Node();

        string preOrderString() const;
        string preOrder() const;
        int indexOf(char c) const;
        Node* subStr(int, int) const;
        Node* helpReverse() const;
    };
    Node* root;

    ConcatStringTree() : root(nullptr) {}
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

    public:
    HashConfig() : p(-1), c1(-1), c2(-1), lambda(-1), alpha(-1), initSize(-1) {}
    HashConfig(int P, double C1, double C2, double Lambda, int Alpha, int InitSize) : p(P), c1(C1), c2(C2), lambda(Lambda), alpha(Alpha), initSize(InitSize) {}
};

class LitStringHash {
    HashConfig hash_config;
    int numsEle;
    int m;

    int lastIndex; //getLastInsertedIndex...
public:
    class LitString {
        public:
        int nodeCount;
        ConcatStringTree::Node* data;
        
        LitString() : nodeCount(0), data(nullptr) {}
        ~LitString() {}
    };
    LitString* hashTable;

    LitStringHash(const HashConfig & hashConfig);
    int getLastInsertedIndex() const;
    string toString() const;

    int hash(const string);
    int quadProb(const string, const int);
    void rehash();
    ConcatStringTree::Node* insert(ConcatStringTree::Node*);
};

class ReducedConcatStringTree : public ConcatStringTree {
public:
    ReducedConcatStringTree(const char * s, LitStringHash * litStringHash);
    LitStringHash * litStringHash;
};

#endif // __CONCAT_STRING_TREE_H__