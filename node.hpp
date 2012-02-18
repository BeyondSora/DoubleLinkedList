#include <cstddef>

using namespace std;

template <class T>
class node {
    public:
        T item;
        node<T> *prev;
        node<T> *next;

        node();
        node(const T item);
        node(const node<T> *that);  // copy constructor
        ~node();
};

template <class T>
node<T>::node()
    : prev(NULL), next(NULL) {}

template <class T>
node<T>::node(const T item)
    : prev(NULL), next(NULL), item(item) {}

template <class T>
node<T>::node(const node *that)     // create a duplicate
    : prev(NULL), next(NULL), item(that->item) {}

template <class T>
node<T>::~node() {}
