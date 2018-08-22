#ifndef _SortedVector_H_
#define _SortedVector_H_

#include <vector>
#include <list>
#include "utils/Misc.h"

namespace SortedVector {


typedef unsigned int KeyType;

template<class Element>
using Iterator = typename std::vector<Element*>::iterator;

struct Bucket {
    KeyType key;
    unsigned int boundary;

    Bucket(KeyType key, unsigned int boundary) {
        this->key = key;
        this->boundary = boundary;
    }
};

typedef std::list<Bucket> BucketList;

typedef BucketList::iterator BucketListIterator;

struct Locator {
    unsigned int pos;
    BucketListIterator bucket_iterator;
};



template<class Element, ClassField<Element, Locator> locator_field>
class SortedVector {
// - Constant time insertion element with lowest key already in the container.
// - Linear time deletion arbitrary element (not implemented not used).
// - Constant time deletion element with lowest key.
// - Constant time key increment (1 unit).
// - Linear time arbitrary key modification (not implemented nor used).
// - Linear time ordered traversal through iterators.

private:
    std::vector<Element*> v;
    BucketList bucket_list;

    bool is_bucket_size_one(const Bucket& bucket) const;
public:
    SortedVector() {}

    SortedVector(unsigned int m);

    void insert_element(Element* element);

    Element* pop_and_push(Element* element);

    void increment_key(Element* element);

    KeyType get_key(Element* element) const;

    unsigned int size() const;

    Iterator<Element> begin() const;

    Iterator<Element> end() const;

    Iterator<Element> begin();

    Iterator<Element> end();
};


}

#include "SortedVector.ipp"

#endif //_SortedVector_H_