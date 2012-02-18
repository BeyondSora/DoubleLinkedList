#include <iostream>
#include <string>
#include "dllist.hpp"

using namespace std;

int main()
{
    string i = "abc";

    node<string> *aa = new node<string>();
    aa->item = "hello";
    dllist<string> *dd = new dllist<string>(i);
    dllist<string> *d2 = new dllist<string>(aa);
    dllist<string> *d3 = new dllist<string>(dd);
    dd->append(d2);
    dd->append(aa);
    dd->append(2,dd);
    dd->prepend(3,dd);
    dd->print();
    d2->print();
    d3->print();
    cout << dd->getSize() << endl;
    cout << d2->getSize() << endl;
    cout << d3->getSize() << endl;

    dllist<string> *d4 = new dllist<string>();
    d4->append(dd);
    d4->pop_top();
    d4->pop_top();
    d4->pop_back();
    d4->pop(1);
    d4->print();
    cout << d4->getSize() << endl;
    cout << d4->find(3)->item << endl;
    cout << d4->find(6)->item << endl;
    std::string abc;


    delete dd;
    delete d2;
    delete d3;
    delete aa;
    delete d4;
    return 0;
}
