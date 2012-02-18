#include "node.hpp"
#include <iostream>

using namespace std;

template <class T>
class dllist {
    private:
        node<T> *first;
        node<T> *last;
        int size;

        void join(node<T> *n1, node<T> *n2);
        void retSubList(node<T> *&subList,
                node<T> *&iterator,
                const dllist<T> *list);

    public:
        dllist();
        dllist(const T item);
        dllist(const node<T> *n);
        dllist(const dllist<T> *that);      // copy constructor
        ~dllist();

        int getSize() { return this->size; }
        node<T>* getFirst() { return this->first; }
        node<T>* getLast() { return this->last; }

        void prepend(const T item);
        void prepend(const node<T> *n);
        void prepend(const dllist<T> *list);
        void prepend(int index, const dllist<T> *list);
        void append(const T item);
        void append(const node<T> *n);
        void append(const dllist<T> *list);
        void append(int index, const dllist<T> *list);

        /* to be implemented */
        node<T>* find(int index);
        //

        void pop_top();
        void pop_back();
        void pop(int index);
        void pop(int index, int num);       // (start, num of nodes to be popped)

        //testing -- ONLY WORKS FOR print-able OBJECTS
        void print()
        {
            if (this->size == 0) { errout(-1); return; }
            node<T> *it = this->first;
            for (; it != NULL; it = it->next) {
                cout << it->item << endl;
            }
        }
};

template <class T>
dllist<T>::dllist()
    : first(NULL), last(NULL), size(0) {}

template <class T>
dllist<T>::dllist(const T item)
    : size(1) { this->first = this->last = new node<T>(item); }

template <class T>
dllist<T>::dllist(const node<T> *n)
    : size(1) { this->first = this->last = new node<T>(n); }

template <class T>
dllist<T>::dllist(const dllist<T> *that)    // create a duplicate
    : size(that->size)
{
    node<T> *iterator = NULL;
    node<T> *it = that->first;
    if (it != NULL) {
        this->first = this->last = iterator = new node<T>(it);
        it = it->next;
    }
    else {
        this->first = this->last = NULL;
    }
    for (; it != NULL; it = it->next) {
        node<T> *temp = new node<T>(it);
        this->join(iterator, temp);
        iterator = temp;
    }
        void errout(const int err);
}
    this->last = iterator;
}

template <class T>
dllist<T>::~dllist()
{
    node<T> *it;
    it = this->first;
    while (it != NULL) {
        node<T> *temp = it;
        it = it->next;
        delete temp;
    }
}

template <class T>
void dllist<T>::errout(const int err)
{
    switch (err) {
        default: break;
        case -1:
             cerr << "OUT OF BOUND ACCESS!" << endl;
             break;
    }
}

template <class T>
void dllist<T>::join(node<T> *n1, node<T> *n2)
{
    n1->next = n2;
    n2->prev = n1;
}

template <class T>
void dllist<T>::retSubList(node<T> *&subList,       // will point to the beginning
               node<T> *&iterator,      // will point to the end
               const dllist<T> *list)
{
    node<T> *it = list->first;
    if (it != NULL) {
        subList = iterator = new node<T>(it);
        it = it->next;
    }
    else {
        subList = iterator = NULL;
    }
    for (; it != NULL; it = it->next) {
        node<T> *temp = new node<T>(it);
        this->join(iterator, temp);
        iterator = temp;
    }

}

template <class T>
void dllist<T>::prepend(const T item)
{
    node<T> *newNode = new node<T>(item);
    if (this->size > 0) {
        this->join(newNode, this->first);
        this->first = newNode;
    }
    else {
        this->first = this->last = newNode;
    }
    this->size += 1;
}

template <class T>
void dllist<T>::prepend(const node<T> *n)
{
    this->prepend(n->item);
}

template <class T>
void dllist<T>::prepend(const dllist<T> *list)
{
    node<T> *subList;
    node<T> *iterator;
    this->retSubList(subList, iterator, list);
    if (this->size > 0) {
        this->join(iterator, this->first);
        this->first = subList;
    }
    else {
        this->first = subList;
        this->last = iterator;
    }
    this->size += list->size;
}

template <class T>
void dllist<T>::prepend(int index, const dllist<T> *list)
{
    if (index >= this->size || size == 0) { errout(-1); return; }
    if (index == 0) { this->prepend(list); return; }
    node<T> *subList;
    node<T> *iterator;
    this->retSubList(subList, iterator, list);
    node<T> *it = this->first;
    while (index > 0) {
        it = it->next;
        index -= 1;
    }
    node<T> *temp = it->prev;
    this->join(iterator, it);
    this->join(temp, subList);
    this->size += list->size;
}

template <class T>
void dllist<T>::append(const T item)
{
    node<T> *newNode = new node<T>(item);
    if (this->size > 0) {
        this->join(this->last, newNode);
        this->last = newNode;
    }
    else {
        this->first = this->last = newNode;
    }
    this->size += 1;
}

template <class T>
void dllist<T>::append(const node<T> *n)
{
    this->append(n->item);
}

template <class T>
void dllist<T>::append(const dllist<T> *list)
{
    node<T> *subList;
    node<T> *iterator;
    this->retSubList(subList, iterator, list);
    if (this->size > 0) {
        this->join(this->last, subList);
        this->last = iterator;
    }
    else {
        this->first = subList;
        this->last = iterator;
    }
    this->size += list->size;
}

template <class T>
void dllist<T>::append(int index, const dllist<T> *list)
{
    if (index >= this->size || this->size == 0) { errout(-1); return; }
    if (index == this->size - 1) { this->append(list); return; }
    node<T> *subList;
    node<T> *iterator;
    this->retSubList(subList, iterator, list);
    node<T> *it = this->first;
    while (index > 0) {
        it = it->next;
        index -= 1;
    }
    node<T> *temp = it->next;
    this->join(it, subList);
    this->join(iterator, temp);
    this->size += list->size;
}

template <class T>
node<T>* dllist<T>::find(int index)
{
    node<T>* it;
    if (index < 0 ||
        index >= this->size ||
        this->size == 0) { errout(-1); return NULL; }
    if (index * 2 > this->size) {
        int i = this->size - index - 1;
        for (it = this->last; it != NULL;
             it = it->prev, --i) {
            if (i == 0) { return it; }
        }
    }
    else {
        int i = 0;
        for (it = this->first; it != NULL;
             it = it->next, ++i) {
            if (i == index) { return it; }
        }
    }
}

template <class T>
void dllist<T>::pop_top()
{
    if (this->size == 0) { errout(-1); return; }
    this->size -= 1;
    node<T> *temp = this->first;
    this->first = this->first->next;
    if (this->size == 0) { this->last = this->first; }
    else { this->first->prev = NULL; }
    delete temp;
}

template <class T>
void dllist<T>::pop_back()
{
    if (this->size == 0) { errout(-1); return; }
    this->size -= 1;
    node<T> *temp = this->last;
    this->last = this->last->prev;
    if (this->size == 0) { this->first = this->last; }
    else { this->last->next = NULL; }
    delete temp;
}

template <class T>
void dllist<T>::pop(int index)
{
    if (index < 0 ||
        index >= this->size ||
        this->size == 0) { errout(-1); return; }
    if (index == 0) { this->pop_top(); return; }
    if (index == this->size - 1) { this->pop_back(); return; }
    this->size -= 1;
    node<T> *n = this->find(index);
    this->join(n->prev, n->next);
    delete n;
}

template <class T>
void dllist<T>::pop(int index, int num)
{
