#include "ConcatStringTree.h"
#include "ConcatStringTree.cpp"

int main() {
    // ConcatStringTree s1("Hello");
    // ConcatStringTree s2(",_t");
    // ConcatStringTree s3 = s1.concat(s2);
    // try {
    //     cout << "char at index 10: " << s1.get(10) << endl;
    // }   
    // catch (const out_of_range & ofr) {
    //     cout << "Exception out_of_range: " << ofr.what() << endl;
    // }
    // cout << s1.indexOf('b') << endl;
    // cout << s3.toStringPreOrder() << "\n";
    // cout << s3.toString() << "\n";
    // cout << s3.subString(5,6).toString() << '\n';
    // cout << s3.reverse().toString() << '\n';
    
    // ConcatStringTree* s1 = new ConcatStringTree("a");
    // ConcatStringTree* s2 = new ConcatStringTree("b");
    // ConcatStringTree* s3 = new ConcatStringTree(s1->concat(*s2));
    // ConcatStringTree* s4 = new ConcatStringTree(s1->concat(*s2));
    // ConcatStringTree* s5 = new ConcatStringTree(s1->concat(*s2));
    // cout << s3->getParTreeSize("l") << endl;
    // cout << s3->getParTreeStringPreOrder("l") << endl;

    HashConfig hashConfig(
        2,
        0.5,
        0.5,
        0.75,
        2,
        4
    );
    LitStringHash * litStringHash = new LitStringHash(hashConfig);  
    ReducedConcatStringTree * s1 = new ReducedConcatStringTree("a", litStringHash);
    ReducedConcatStringTree * s2 = new ReducedConcatStringTree("bb", litStringHash);

    cout << s1->toString() << endl;
    cout << s2->toString() << endl;
    ReducedConcatStringTree * s3 = new ReducedConcatStringTree("bb", litStringHash);

    cout << litStringHash->getLastInsertedIndex() << endl;
    cout << litStringHash->toString() << endl;

    delete s3;
    delete s1;
    delete s2;
    delete litStringHash;
    // return 0;
}