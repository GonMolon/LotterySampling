#ifndef _Frequent_Algorithm_H_
#define _Frequent_Algorithm_H_

#include "algorithms/GenericAlgorithm.h"
#include "algorithms/frequent/Types.h"
#include "utils/InputParser.h"


namespace Frequent {


template<class T>
class Algorithm : public GenericAlgorithm<Element, T, FrequencyOrderIterator<Element<T>>> {

private:

    FrequencyOrder<Element<T>> frequency_order;
    unsigned int m;
    unsigned int offset;

    bool insert_element(Element<T>& element) override;

    void update_element(Element<T>& element) override;

public:

    Algorithm(const InputParser& parameters);

    FrequencyOrderIterator<Element<T>> frequency_order_begin() override;

    FrequencyOrderIterator<Element<T>> frequency_order_end() override;

    float get_threshold() const override;

    void print_state() override;
};


}

#include "algorithms/frequent/Algorithm.ipp"

#endif //_Frequent_Algorithm_H_