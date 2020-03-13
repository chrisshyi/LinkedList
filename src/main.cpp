#include "linked_list.h"
#include <iostream>
#include <vector>
#include <algorithm>
using std::vector;
using std::cout;
using std::endl;
using std::sort;

int main() {
    LinkedList<int> ll;
    ll.insert_back(90);
    ll.insert_back(6);
    ll.insert_back(2);
    ll.insert_back(3);
    ll.insert_back(1);
    ll.insert_back(10);
    ll.insert_back(14);
    ll.insert_back(11);
    cout << ll.to_string() << endl;
    ll.partition(9);
    cout << ll.to_string() << endl;



    auto reversed = ll.reverse();
    cout << reversed.to_string() << endl;

    LinkedList<int> ll1;
    // ll1.insert_back(7);
    // ll1.insert_back(1);
    ll1.insert_back(9);

    LinkedList<int> ll2;
    ll2.insert_back(9);
    //ll2.insert_back(4);

    auto ll3 = sum(ll1, ll2);
    auto ll4 = sum_forward(ll1, ll2);
    cout << ll3.to_string() << endl;
    cout << ll4.to_string() << endl;

    auto ll5 = LinkedList<char>();    
    ll5.insert_back('c');
    ll5.insert_back('b');
    ll5.insert_back('b');
    ll5.insert_back('c');
    
    cout << ll5.is_palindrome() << endl;
    return 0;
}