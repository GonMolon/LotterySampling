#ifndef _Types_LotterySampling_H_
#define _Types_LotterySampling_H_

#include <set>
#include <vector>

namespace LotterySampling {

    
using namespace std;

typedef uint64_t Ticket;

template<class Element>
class TicketOrder { // Implementation of a min binary heap to represent the order by ticket value of sampled elements

private:
    struct CompareTicket {
        inline bool operator()(const Element* a, const Element* b) const {
            return a->ticket < b->ticket;
        }
    };

    vector<Element*> v;

public:
    TicketOrder() {}

    TicketOrder(unsigned int m);

    typedef int iterator;

    Element* top() const;

    Element* pop();

    void push(Element* element);

    Element* pop_and_push(Element* element);

    void ticket_updated(iterator it);

    void remove_element(iterator it);

    bool empty() const;

    unsigned int size() const;
};


template<class T>
struct Element {

private:
    struct CompareFrequency {
        inline bool operator()(const Element<T>* a, const Element<T>* b) const {
            return *a < *b;
        }
    };

public:
    typedef multiset<Element<T>*, CompareFrequency> FrequencyOrder;

    T id;
    Ticket ticket;
    unsigned int freq;
    unsigned int over_estimation;

    typename TicketOrder<Element<T>>::iterator ticket_iterator;
    int level;

    typename FrequencyOrder::iterator frequency_iterator;

    Element(const T& id) {
        this->id = id;
    }

    bool operator<(const Element<T>& element) const {
        return this->freq < element.freq;
    }
};


}

#include "DataStructures.ipp"

#endif //_Types_LotterySampling_H_
