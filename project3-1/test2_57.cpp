#include <iostream>
#include <fstream>
#include <math.h>
#include "Search_tree.h"
using namespace std;

template<typename Type>
int show(Search_tree<Type>& tree, bool b = true) {
    int t = 0;
    int score = 2;
    if (b) {
        for (typename Search_tree<Type>::Iterator itr = tree.begin(); itr != tree.end(); ++itr) {
            //if (tree.size()<100)
            cout << *itr << " ";
            t++;
        }
        if (tree.size() == 0) {
            cout << "Tree is empty.";
        }
    }
    else {
        for (typename Search_tree<Type>::Iterator itr = tree.rbegin(); itr != tree.rend(); --itr) {
            std::cout << *itr << " ";
            t++;
        }
        if (tree.size() == 0)
            cout << "Tree is empty.";
    }

    cout << endl;
    if (t == tree.size())
    {
        if (b)
            cout << "Passed, showing tree (increasing):(" << score << " sccores)" << endl;
        else
            cout << "Passed, showing tree (decreasing):(" << score << " sccores)" << endl;
    }
    else {
        score = 0;
        cout << "Failed, showing tree (increasing):(" << score << " sccore)" << endl;
    }
    return score;
}

template<typename Type>
int chk_height(Search_tree<Type>& tree) {
    int score = 8;
    int h = tree.height();
    int t = int(1.44 * log2(tree.size()));

    if (h > t) {
        score = 0;
        cout << "Failed, Height comp(" << h << ">" << t << "):(" << score << " sccores)" << endl;
        return score;
    }
    else
        cout << "Passed, Height comp(" << h << "):(" << score << " sccores)" << endl;
    return score;
}

template<typename Type>
int filling_tree(Search_tree<Type>& tree, int n, int p) {
    int score = 3;
    int t, i;
    for (i = 1; i <= n; ++i) {
        t = (p * i) % n;
        //cout<<t<<" ";
        Type d = Type(t) + 0.1;
        tree.insert(d);
        typename Search_tree<Type>::Iterator itr = tree.find(d);
        if (*itr != d) {
            score = 0;
            cout << "Failed, filling_tree (" << n << ") items: (" << score << " sccore)" << endl;
            return score;
        }
    }
    if (i == n + 1)
        cout << "Passed, filling_tree(" << n << ") items:(" << score << " sccores)" << endl;
    return score;
}

template<typename Type>
int erase_item(Search_tree<Type>& tree, Type item) {
    int score = 1;
    int t1 = 0;
    for (typename Search_tree<Type>::Iterator itr = tree.begin(); itr != tree.end(); ++itr) {
        if (*itr == item)
            t1++;
    }

    tree.erase(item);
    int t2 = 0;
    for (typename Search_tree<Type>::Iterator itr = tree.begin(); itr != tree.end(); ++itr) {
        if (*itr == item)
            t2++;
    }

    if (t1 > 0 && t1 == t2 + 1) {
        cout << "Passed, eraseing (" << item << "):(" << score << " sccore)" << endl;
    }
    else if (t1 > 0) {
        score = 0;
        cout << "Failed, erasing(" << item << ") items:(" << score << " sccore)" << endl;
    }
    return score;
}

template<typename Type>
int insert_item(Search_tree<Type>& tree, Type item) {
    int score = 1;
    int t1 = 0;
    for (typename Search_tree<Type>::Iterator itr = tree.begin(); itr != tree.end(); ++itr) {
        if (*itr == item)
            t1++;
    }

    tree.insert(item); 

    int t2 = 0;
    for (typename Search_tree<Type>::Iterator itr = tree.begin(); itr != tree.end(); ++itr) {
        if (*itr == item)
            t2++;
    }

    if (t2 > 0 && t1 + 1 == t2) {
        cout << "Passed, inserting (" << item << "):(" << score << " sccore)" << endl;
    }
    else if (t2 > 0) {
        score = 0;
        cout << "Failed, inserting(item: " << item << ") mismatch number of items (" << score << " sccore)" << endl;
    }
    return score;
}

template<typename Type>
int remove_a_bunch(Search_tree<Type>& tree, int item) {
    int j = 0;
    int score = 3;
    int s = tree.size();
    Type* a = new Type[tree.size()];

    for (typename Search_tree<Type>::Iterator itr = tree.begin(); itr != tree.end(); ++itr) {
        if (*itr < item) {
            a[j] = *itr;
            j++;
        }
    }
    for (int i = 0; i < j; i++) {
        tree.erase(a[i]);
    }

    int new_s = tree.size();
    if (new_s + j != s) {
        score = 0;
        cout << "Failes, removing a bunch (items less than " << item << "). Tree size mismatch:(" << score << " sccore)" << endl;
        return score;
    }

    for (typename Search_tree<Type>::Iterator itr = tree.begin(); itr != tree.end(); ++itr)
        if (*itr < item) {
            score = 0;
            cout << "Failes, removing a bunch (items less than " << item << "). Some items are exist:(" << score << " sccore)" << endl;
            return score;
        }

    delete[] a;
    cout << "Passed, removing a bunch (items less than " << item << "):(" << score << " sccores)" << endl;
    return score;
}

int main(int argc, char** argv) {
    Search_tree<double> tree;
    int score = 0;

    int n = 500, t, p;
    cout << "n=" << n << endl;

    score += filling_tree(tree, n, 671);

    score += chk_height(tree);

    cout << "Front:   " << tree.front() << std::endl;
    cout << "Back:    " << tree.back() << std::endl;

    score += show(tree, true);
    score += show(tree, false);

    score += insert_item(tree, 100.1);
    score += erase_item(tree, 2.1);

    show(tree, true);

    score += remove_a_bunch(tree, 10.0);
    score += chk_height(tree);

    cout << "clearing tree..." << endl;
    tree.clear();

    show(tree, false);

    score += filling_tree(tree, n, 1);
    //tree.levelorder_newline(); cout<<endl;

    score += chk_height(tree);

    cout << "Front:   " << tree.front() << std::endl;
    cout << "Back:    " << tree.back() << std::endl;

    score += show(tree, true);
    score += show(tree, false);

    score += insert_item(tree, 100.1);
    score += erase_item(tree, 2.1);
    score += erase_item(tree, 2.0);

    show(tree, true);

    score += remove_a_bunch(tree, 100.0);
    show(tree, true);
    score += chk_height(tree);

    cout << "clearing tree..." << endl;
    tree.clear();


    std::cout << "Total score: " << score << " out of 57." << std::endl;
    cout << argv[1] << endl;
    ofstream f(argv[1],ios::app);
    f<<score<<endl;
    f.close();

    return 0;
}
