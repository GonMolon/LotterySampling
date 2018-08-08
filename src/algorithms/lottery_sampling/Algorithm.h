#ifndef _LOTTERYSAMPLING_H_
#define _LOTTERYSAMPLING_H_

#include "algorithms/GenericAlgorithm.h"
#include "utils/InputParser.h"
#include "DataStructures.h"
#include <random>

namespace LotterySampling {


template <class T>
class Algorithm : public GenericAlgorithm<Element, T> {

private:

    TicketOrder<Element<T>> level_1;
    TicketOrder<Element<T>> level_2;

    typename Element<T>::FrequencyOrder frequency_order;

    unsigned int m;
    bool aging;
    bool multilevel;

    Ticket MAX_TICKET;
    std::mt19937_64 random_state;
    std::uniform_int_distribution<Ticket> dist;

    bool insert_element(Element<T>& element) override;

    void update_element(Element<T>& element) override;

    Ticket generate_ticket();

    unsigned int estimate_frequency(Ticket min_ticket) const;

    void insert_level_1(Element<T>& element);

    void insert_level_2(Element<T>& element);

public:
    Algorithm(const InputParser& parameters);

    void frequent_query(float f, std::ostream& stream) override;

    void k_top_query(int k, std::ostream& stream) override;

    void print_state() override;
};


}

#include "Algorithm.ipp"

#endif //_LOTTERYSAMPLING_H_
