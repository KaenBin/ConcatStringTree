#include "ConcatStringTree.h"

// Initialize curID
// static int curID = 1;

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

ConcatStringTree::Node* ConcatStringTree::Node::subStr(int from, int to) const {
    if (from < 0 || to >= length)
        throw out_of_range("Index of string is invalid!");
    if (from >= to)
        throw logic_error("Invalid range!");
    
    Node* newTree = new Node("");
    if (!data.empty())
    {
        newTree->data = data.substr(from, to);
        newTree->length = newTree->data.length();
        return newTree;
    }
    
    if (from >= leftLength) {
        newTree->right = right->subStr(from - leftLength, to - leftLength);
        newTree->length = newTree->right->length;
    }
    else if (to < leftLength) {
        newTree->left = left->subStr(from, to);
        newTree->leftLength = newTree->length = newTree->left->length;
    }
    else {
        newTree->left = left->subStr(from, leftLength - 1);
        newTree->right = right->subStr(0, to - leftLength);
        newTree->leftLength = newTree->left->length;
        newTree->length = newTree->left->length + newTree->right->length;
    }

    return newTree;
}

ConcatStringTree::Node* ConcatStringTree::Node::helpReverse() const {
    Node* newTree = new Node("");
    if (!data.empty())
    {
        for (int i = length - 1; i >= 0; i--)
            newTree->data += data[i];
        newTree->length = data.length();
        return newTree;
    }
    
    newTree->leftLength = length - leftLength;
    newTree->left = right->helpReverse();
    newTree->right = left->helpReverse();

    if (newTree->left) {
        newTree->leftLength = newTree->left->length;
        newTree->length = newTree->left->length;
    }
    if (newTree->right)
        newTree->length += newTree->right->length;
    

    return newTree;
}

    // ParentsTree
string ConcatStringTree::Node::ParentsTree::preOrderString() const {
    if (!this)
        return "";

    string output = ";(id=";
    output += to_string(id);
    output += ")";

    output += pLeft->preOrderString();
    output += pRight->preOrderString();

    return output;
}

ConcatStringTree::Node::ParentsTree* ConcatStringTree::Node::ParentsTree::maxID(ParentsTree* root) {
    ParentsTree* current = root;
 
    while (current->pRight)
        current = current->pRight;
 
    return current;
}

int ConcatStringTree::Node::ParentsTree::valueBalance(ParentsTree* root) {
    if (!root)
        return 0;
    return getHeight(root->pLeft) - getHeight(root->pRight);
}
// Node

ConcatStringTree::Node::~Node() {
    if (!this)
        return;

    if (data != "")
        pParent = pParent->delParsTree(pParent, id);
    if (left) {
        left->pParent = left->pParent->delParsTree(left->pParent, id);
        if (!left->pParent)
            delete left;
    }
    if (right) {
        right->pParent = right->pParent->delParsTree(right->pParent, id);
        if (!right->pParent)
            delete right;
    }
}

int ConcatStringTree::Node::indexOf(char c) const {
    int pos = -1;
    if (!left && !right)
        if (!data.empty())
            return data.find(c);
        else
            return -1;

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
ConcatStringTree::ConcatStringTree(const char* s) {
    root = new Node(s);
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
    root->pParent = root->pParent->insert(root->pParent, curID);
    otherS.root->pParent = otherS.root->pParent->insert(otherS.root->pParent, curID);
    root->pParent->parSize++;
    otherS.root->pParent->parSize++;
    curID++;
    return newTree;
}

ConcatStringTree ConcatStringTree::subString(int from, int to) const {
    if (from < 0 || to >= root->length)
        throw out_of_range("Index of string is invalid!");
    if (from >= to)
        throw logic_error("Invalid range!");
    
    ConcatStringTree* newTree = new ConcatStringTree("");
    newTree->root = root->subStr(from, to);

    return *newTree;
}

ConcatStringTree ConcatStringTree::reverse() const {
    ConcatStringTree* newTree = new ConcatStringTree("");
    newTree->root = root->helpReverse();
    return *newTree;
}

int ConcatStringTree::getParTreeSize(const string & query) const{
    int length = query.length();
    Node* temp = root;

    for (int i = 0; i < length; i++)
    {
        if (!temp)
            throw runtime_error("Invalid query: reaching NULL");
        
        switch (query[i])
        {
        case 'l':
            temp = temp->left;
            break;
        case 'r':
            temp = temp->right;
            break;

        default:
            throw runtime_error("Invalid character of query");
            break;
        }
    }
    
    return temp->pParent->size();
}

string ConcatStringTree::getParTreeStringPreOrder(const string & query) const {
    int length = query.length();
    Node* temp = root;

    for (int i = 0; i < length; i++)
    {
        if (!root)
            throw runtime_error("Invalid query: reaching NULL");
        
        switch (query[i])
        {
        case 'l':
            temp = temp->left;
            break;
        case 'r':
            temp = temp->right;
            break;

        default:
            throw runtime_error("Invalid character of query");
            break;
        }
    }

    return temp->pParent->toStringPreOrder();
}

ConcatStringTree::~ConcatStringTree() {
    if (!this)
        return;

    if (root)
        if (!root->pParent)
            delete root;
}

// ParentsTree
int ConcatStringTree::Node::ParentsTree::getHeight(ParentsTree* root) {
    if (!root)
        return 0;

    return root->height;
}

ConcatStringTree::Node::ParentsTree* ConcatStringTree::Node::ParentsTree::rightRotate(ParentsTree* root) {
    ParentsTree* left = root->pLeft;
    root->pLeft = left->pRight;
    left->pRight = root;

    root->height = 1 + max(getHeight(root->pLeft), getHeight(root->pRight));
    left->height = 1 + max(getHeight(left->pLeft), getHeight(left->pRight));

    return left;
}

ConcatStringTree::Node::ParentsTree* ConcatStringTree::Node::ParentsTree::leftRotate(ParentsTree* root) {
    ParentsTree* right = root->pRight;
    root->pRight = right->pLeft;
    right->pLeft = root;

    root->height = 1 + max(getHeight(root->pLeft), getHeight(root->pRight));
    right->height = 1 + max(getHeight(right->pLeft), getHeight(right->pRight));

    return right;
}

ConcatStringTree::Node::ParentsTree* ConcatStringTree::Node::ParentsTree::insert(ParentsTree* root, int curID) {
    if (!root)
        return new ParentsTree(curID, nullptr, nullptr, 1);

    if (curID > root->id)
        root->pRight = insert(root->pRight, curID);
    else if (curID < root->id)
        root->pRight = insert(root->pLeft, curID);
    else
        return root;

    root->height = 1 + max(getHeight(root->pLeft), getHeight(root->pRight));
    root->parSize++;

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

ConcatStringTree::Node::ParentsTree* ConcatStringTree::Node::ParentsTree::delParsTree(ParentsTree* root, int curID) {
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
    root->parSize--;

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

string ConcatStringTree::Node::ParentsTree::toStringPreOrder() const {
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

// LitStringHash
LitStringHash::LitStringHash(const HashConfig & hashConfig) {
    hash_config = hashConfig;
    numsEle = 0;
    m = hashConfig.initSize;
    hashTable = new LitString[m];
}

int LitStringHash::getLastInsertedIndex() const {
    // this function is stupid alr?
    return lastIndex;
}

string LitStringHash::toString() const {
    string output = "LitStringHash[";

    if (m >= 1) {
        output += "(";
        if (hashTable[0].data) {
            output += "litS=\"";
            output += hashTable[0].data->data;
            output += "\"";
        }
        output += ")";
    }

    for (int i = 1; i < m; i++)
    {
        output += ";(";
        if (hashTable[i].data) {
            output += "litS=\"";
            output += hashTable[i].data->data;
            output += "\"";
        }
        output += ")";
    }
    
    output += "]";
    return output;
}

int LitStringHash::hash(const string s) {
    int n = s.length();
    int hash_value = 0;
    for (int i = 0; i < n; i++) {
        int pow = 1;
        for (int j = 0; j < i; j++)
            pow *= hash_config.p;
        hash_value += int(s[i]) * pow;
    }
    
    return hash_value % m;
}

int LitStringHash::quadProb(const string s, const int i) {
    return int((hash(s) + hash_config.c1 * i + hash_config.c2 * i * i)) % m;
}

void LitStringHash::rehash() {
    int newSize = hash_config.alpha * numsEle;
    LitString* newHashTable = new LitString[newSize];

    for (int i = 0; i < m; i++)
        if (hashTable[i].data) {
            newHashTable[i].data = hashTable[i].data;
            newHashTable[i].nodeCount = hashTable[i].nodeCount;
        }
        
    delete hashTable;
    m = newSize;
    hashTable = newHashTable;
}

ConcatStringTree::Node* LitStringHash::insert(ConcatStringTree::Node* node) {
    int pos = hash(node->data);
    for (int i = 0; i < m; i++)
    {
        int check = (i + pos) % m;
        if (!hashTable[check].data)
        {
            numsEle++;
            if (numsEle / double(m) > hash_config.lambda)
                rehash();
            hashTable[check].data = node;
            hashTable[check].nodeCount++;
            lastIndex = check;
            return hashTable[check].data;
        }
        if (hashTable[check].data->data == node->data) {
            delete node;
            lastIndex = check;
            return hashTable[check].data;
        }
    }
    
    return nullptr;
}

// ReducedConcatStringTree
ReducedConcatStringTree::ReducedConcatStringTree(const char * s, LitStringHash * litStringHash) {
    Node* newNode = new Node (s);
    root = litStringHash->insert(newNode);

    if (!root)
        throw runtime_error("No possible slot");

    this->litStringHash = litStringHash;
}