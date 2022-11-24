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
    
    ConcatStringTree* s1 = new ConcatStringTree("a");
    ConcatStringTree* s2 = new ConcatStringTree("b");
    ConcatStringTree* s3 = new ConcatStringTree(s1->concat(*s2));
    cout << s3->getParTreeSize("l") << endl;
    cout << s3->getParTreeStringPreOrder("l") << endl;
    return 0;
}