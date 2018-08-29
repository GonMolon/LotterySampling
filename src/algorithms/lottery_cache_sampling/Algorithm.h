#ifndef _LotteryCacheSampling_Algorithm_H_
#define _LotteryCacheSampling_Algorithm_H_

#include <algorithms/GenericAlgorithm.h>
#include <utils/InputParser.h>
#include "Types.h"
#include "utils/Misc.h"


namespace LotteryCacheSampling {


template<class T>
class Algorithm : public GenericAlgorithm<Element, T, FrequencyOrderIterator<Element<T>>> {

private:

    FrequencyOrder<Element<T>> frequency_order;
    CacheOrder<Element<T>> cache_order;

    unsigned int m;
    TicketGenerator ticket_generator;
    Ticket mean_ticket;

    bool insert_element(Element<T>& element) override;

    void update_element(Element<T>& element) override;

public:

    Algorithm(const InputParser& parameters);

    FrequencyOrderIterator<Element<T>> frequency_order_begin() override;

    FrequencyOrderIterator<Element<T>> frequency_order_end() override;

    void print_state() override;
};


}

#include "Algorithm.ipp"

#endif //_LotteryCacheSampling_Algorithm_H_
