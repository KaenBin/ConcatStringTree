#include "ConcatStringTree.h"

// Initialize curID
static int curID = 1;

// Helper functions
    // ConcatStringTree
string ConcatStringTree::Node::preOrderString() const {
    string output = ";(LL=";
    output += to_string(leftLength);
    output += ",L=";
    output += to_string(length);
    output += ",";
    if (!data.empty()) {
        output += "\"";
        output += data;
        output += "\"";
    }

        
    else
        output += "<NULL>";
    output += ")";

    if (left)    
        output += left->preOrderString();
    if (right)
        output += right->preOrderString();

    return output;
}

string ConcatStringTree::Node::preOrder() const {
    string output = "";
    if (!data.empty())
        return data;

    if (left)
        output += left->preOrder();
    
    if (right)
        output += right->preOrder();
    
    return output;
}

ConcatStringTree* ConcatStringTree::subStr(int from, int to) const {
    if (from < 0 || to >= size)
        throw out_of_range("Index of string is invalid!");
    if (from >= to)
        throw logic_error("Invalid range!");
    
    ConcatStringTree* newTree = new ConcatStringTree("");
    if (!data.empty())
    {
        newTree->data = data.substr(from, to);
        newTree->size = newTree->data.length();
        return newTree;
    }
    
    if (from >= leftLength) {
        newTree->right = right->subStr(from - leftLength, to - leftLength);
        newTree->size = newTree->right->size;
    }
    else if (to < leftLength) {
        newTree->left = left->subStr(from, to);
        newTree->leftLength = newTree->size = newTree->left->size;
    }
    else {
        newTree->left = left->subStr(from, leftLength - 1);
        newTree->right = right->subStr(0, to - leftLength);
        newTree->leftLength = newTree->left->size;
        newTree->size = newTree->left->size + newTree->right->size;
    }

    return newTree;
}

ConcatStringTree* ConcatStringTree::helpReverse() const {
    ConcatStringTree* newTree = new ConcatStringTree("");
    if (!data.empty())
    {
        for (int i = size - 1; i >= 0; i--)
            newTree->data += data[i];
        newTree->size = data.length();
        return newTree;
    }
    
    newTree->leftLength = size - leftLength;
    newTree->left = right->helpReverse();
    newTree->right = left->helpReverse();

    if (newTree->left) {
        newTree->leftLength = newTree->left->size;
        newTree->size = newTree->left->size;
    }
    if (newTree->right)
        newTree->size += newTree->right->size;
    

    return newTree;
}

    // ParentsTree
string ConcatStringTree::ParentsTree::preOrderString() const {
    if (!this)
        return "";

    string output = ";(id=";
    output += to_string(id);
    output += ")";

    output += pLeft->preOrderString();
    output += pRight->preOrderString();

    return output;
}

ConcatStringTree::ParentsTree* ConcatStringTree::ParentsTree::maxID(ParentsTree* root) {
    ParentsTree* current = root;
 
    while (current->pRight)
        current = current->pRight;
 
    return current;
}

int ConcatStringTree::ParentsTree::valueBalance(ParentsTree* root) {
    if (!root)
        return 0;
    return getHeight(root->pLeft) - getHeight(root->pRight);
}
// Node
ConcatStringTree::Node::Node(string s, Node* pLeft = nullptr, Node* pRight = nullptr) : data(s), left(pLeft), right(pRight) {
    leftLength = 0;
    length = data.length();
}

int ConcatStringTree::Node::indexOf(char c) const {
    int pos = -1;
    if (!left && !right)
        pos = data.find(c);

    if (pos != -1) {
        if (pos != string::npos)
            return pos;
        else
            return -1;
    }

    pos = left->indexOf(c);
    if (pos != -1) {
        if (pos != string::npos)
            return pos;
        else
            return -1;
    }

    pos = right->indexOf(c);
    if (pos != -1) {
        if (pos != string::npos)
            return leftLength + pos;
        else
            return -1;
    }
    
    return -1;
}

// ConcatStringTree
ConcatStringTree::ConcatStringTree(char const* s) {
    root = new Node(s);

    pParent = nullptr;
    root->id = curID;
    pParent = pParent->insert(pParent, root->id);
    pParent->parSize = 1;
    curID++;
}

int ConcatStringTree::length() const {
    if (!root)
        return -1;

    return root->length;
}

char ConcatStringTree::get(int index) const {
    if (!root)
        return 'E';
    
    if (index < 0 || index >= root->length)   throw out_of_range("Index of string is invalid!");

    Node* temp = this->root;
    while (temp->right && index > temp->leftLength) {
        temp = temp->right;
        index -= temp->leftLength;
    }

    while (temp->left)
        temp = temp->left;

    return temp->data[index];
}

int ConcatStringTree::indexOf(char c) const {
    return root->indexOf(c);
}

string ConcatStringTree::toStringPreOrder() const {
    string output = "ConcatStringTree[(LL=";
    output += to_string(root->leftLength);
    output += ",L=";
    output += to_string(root->length);
    output += ",";
    if (!root->data.empty()) {
        output += "\"";
        output += root->data;
        output += "\"";
    }
        
    else
        output += "<NULL>";
    output += ")";

    if (root->left)
        output += root->left->preOrderString();
    if (root->right)
        output += root->right->preOrderString();
    output += "]";

    return output;
}

string ConcatStringTree::toString() const {
    string output = "ConcatStringTree[\"";
    output += root->preOrder();
    output += "\"]";
    return output;
}

ConcatStringTree ConcatStringTree::concat(const ConcatStringTree & otherS) const {
    ConcatStringTree newTree("");
    newTree.root->leftLength = this->root->length;
    newTree.root->length = this->root->length + otherS.root->length;
    newTree.root->left = this->root;
    newTree.root->right = otherS.root;

    newTree.root->id = curID;
    this->pParent = this->pParent->insert(this->pParent, curID);
    otherS.pParent = otherS.pParent->insert(otherS.pParent, curID);
    this->pParent->parSize++;
    otherS.pParent->parSize++;
    curID++;
    return newTree;
}

ConcatStringTree ConcatStringTree::subString(int from, int to) const {
    if (from < 0 || to >= size)
        throw out_of_range("Index of string is invalid!");
    if (from >= to)
        throw logic_error("Invalid range!");
    
    ConcatStringTree* newTree = subStr(from, to);

    return *newTree;
}

ConcatStringTree ConcatStringTree::reverse() const {
    ConcatStringTree* newTree = helpReverse();
    return *newTree;
}

int ConcatStringTree::getParTreeSize(const string & query) {
    int length = query.length();
    ConcatStringTree* root = this;

    for (int i = 0; i < length; i++)
    {
        if (!root)
            throw runtime_error("Invalid query: reaching NULL");
        
        switch (query[i])
        {
        case 'l':
            root = root->left;
            break;
        case 'r':
            root = root->right;
            break;

        default:
            throw runtime_error("Invalid character of query");
            break;
        }
    }
    
    return root->pParent->size();
}

string ConcatStringTree::getParTreeStringPreOrder(const string & query) const {
    int length = query.length();
    ParentsTree* root = pParent;

    for (int i = 0; i < length; i++)
    {
        if (!root)
            throw runtime_error("Invalid query: reaching NULL");
        
        switch (query[i])
        {
        case 'l':
            root = root->pLeft;
            break;
        case 'r':
            root = root->pRight;
            break;

        default:
            throw runtime_error("Invalid character of query");
            break;
        }
    }

    return root->toStringPreOrder();
}

ConcatStringTree::~ConcatStringTree() {
    // if (!pParent)
    //     return;
    

}

// ParentsTree
int ConcatStringTree::ParentsTree::getHeight(ParentsTree* root) {
    if (!root)
        return 0;

    return root->height;
}

ConcatStringTree::ParentsTree* ConcatStringTree::ParentsTree::rightRotate(ParentsTree* root) {
    ParentsTree* left = root->pLeft;
    root->pLeft = left->pRight;
    left->pRight = root;

    root->height = 1 + max(getHeight(root->pLeft), getHeight(root->pRight));
    left->height = 1 + max(getHeight(left->pLeft), getHeight(left->pRight));

    return left;
}

ConcatStringTree::ParentsTree* ConcatStringTree::ParentsTree::leftRotate(ParentsTree* root) {
    ParentsTree* right = root->pRight;
    root->pRight = right->pLeft;
    right->pLeft = root;

    root->height = 1 + max(getHeight(root->pLeft), getHeight(root->pRight));
    right->height = 1 + max(getHeight(right->pLeft), getHeight(right->pRight));

    return right;
}

ConcatStringTree::ParentsTree* ConcatStringTree::ParentsTree::insert(ParentsTree* root, int curID) {
    if (!root) {
        return new ParentsTree(curID, nullptr, nullptr, 1);
    }

    if (curID > root->id)
        root->pRight = insert(root->pRight, curID);
    else if (curID < root->id)
        root->pRight = insert(root->pLeft, curID);
    else
        return root;

    root->height = 1 + max(getHeight(root->pLeft), getHeight(root->pRight));

    int valBalance = getHeight(root->pLeft) - getHeight(root->pRight);
    
    if (valBalance > 1 && curID < root->pLeft->id)
        return rightRotate(root);
 
    if (valBalance < -1 && curID > root->pRight->id)
        return leftRotate(root);
 
    if (valBalance > 1 && curID > root->pLeft->id) {
        root->pLeft = leftRotate(root->pLeft);
        return rightRotate(root);
    }

    if (valBalance < -1 && curID < root->pRight->id) {
        root->pRight = rightRotate(root->pRight);
        return leftRotate(root);
    }
    return root;
}

ConcatStringTree::ParentsTree* ConcatStringTree::ParentsTree::delParsTree(ParentsTree* root, int curID) {
    if (!root)
        return root;

    if (curID > root->id)
        root->pRight = delParsTree(root->pRight, curID);
    else if (curID < root->id)
        root->pLeft = delParsTree(root->pRight, curID);
    else {
        if (!root->pLeft || !root->pRight) {
            ParentsTree* temp = root->pLeft;
            if (!root->pRight)
                temp = root->pRight;

            if (!temp) {
                temp = root;
                root = NULL;
                delete temp;
            }
            else {
                *root = *temp;
                delete temp;
            }
        }
        else {
            ParentsTree* temp = maxID(root->pLeft);

            root->id = temp->id;
            root->pRight = delParsTree(root->pRight, temp->id);
        }
    }

    if (!root)
        return root;
 
    root->height = 1 + max(getHeight(root->pLeft), getHeight(root->pRight));

    int valBalance = valueBalance(root);

    if (valBalance > 1 && valueBalance(root->pLeft) >= 0)
        return rightRotate(root);

    if (valBalance < -1 && valueBalance(root->pRight) <= 0)
        return leftRotate(root);

    if (valBalance > 1 && valueBalance(root->pLeft) < 0){
        root->pLeft = leftRotate(root->pLeft);
        return rightRotate(root);
    }

    if (valBalance < -1 && valueBalance(root->pRight) > 0){
        root->pRight = rightRotate(root->pRight);
        return leftRotate(root);
    }
 
    return root;
}

string ConcatStringTree::ParentsTree::toStringPreOrder() const {
    string output = "ParentsTree[";

    if (parSize > 0)
    {
        output += "(id=";
        output += to_string(id);
        output += ")";
        output += pLeft->preOrderString();
        output += pRight->preOrderString();
    }

    output += "]";
    return output;
}