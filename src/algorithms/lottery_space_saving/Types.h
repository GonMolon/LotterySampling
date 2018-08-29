#ifndef _LotterySpaceSaving_Types_H_
#define _LotterySpaceSaving_Types_H_

#include "data_structures/SortedList.h"
#include "data_structures/SortedVector.h"
#include "utils/Misc.h"

namespace LotterySpaceSaving {


template<class Element>
//using FrequencyOrder = SortedList::SortedList<Element, &Element::frequency_order_locator>;
using FrequencyOrder = SortedVector::SortedVector<Element, &Element::frequency_order_locator>;

template<class Element>
//using FrequencyOrderLocator = SortedList::Locator<Element>;
using FrequencyOrderLocator = SortedVector::Locator;

template<class T>
struct Element {

    T id;
    Ticket ticket;
    unsigned int over_estimation;

    FrequencyOrderLocator<Element<T>> frequency_order_locator;

    Element(const T& id) {
        this->id = id;
    }
};


}

#endif //_LotterySpaceSaving_Types_H_