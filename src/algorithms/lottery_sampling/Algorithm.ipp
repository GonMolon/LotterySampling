#include "algorithms/lottery_sampling/Algorithm.h"


namespace LotterySampling {


template<class T>
Algorithm<T>::Algorithm(const InputParser& parameters) {
    m = (unsigned int) stoul(parameters.get_parameter("-m"));
    if(parameters.has_parameter("-phi")) {
        phi = stod(parameters.get_parameter("-phi"));
    } else {
        phi = -1;
    }
    ticket_order = TicketOrder<Element<T>>(m);
    this->set_monitored_size(m);
    int seed;
    if(parameters.has_parameter("-seed")) {
        seed = stoi(parameters.get_parameter("-seed"));
    } else {
        seed = -1;
    }
    ticket_generator = TicketUtils(seed);
}

template<class T>
FrequencyOrder<Element<T>>& Algorithm<T>::get_frequency_order() {
    return frequency_order;
}

template<class T>
bool Algorithm<T>::insert_element(Element<T>& element) {
    element.ticket = ticket_generator.generate_token();

    if(this->sample_size() < m) {
        frequency_order.insert_element(&element);
        ticket_order.push(&element);
    } else { // Max number of monitored elements is reached. This new one may replace the one with less hits
        if(phi == -1 && element.ticket < ticket_order.top()->ticket) {
            return false;
        }
        if(phi != -1 && element.ticket < TicketUtils::estimate_ticket(floor(phi * this->N))) {
            return false;
        }
        Element<T>* removed_element = frequency_order.replace_last(&element);
        ticket_order.pop_and_push(removed_element, &element);
        this->remove_element(removed_element->id);

        frequency_order.increase_key(&element);
    }
    return true;
}

template<class T>
void Algorithm<T>::update_element(Element<T>& element) {
    frequency_order.increase_key(&element);
    Token token = ticket_generator.generate_token();
    if(token > element.ticket) {
        element.ticket = token;
        ticket_order.key_updated(&element);
    }
}

template<class T>
double Algorithm<T>::get_frequency_threshold(double f) const {
    if(phi != -1) {
        assert(f == phi);
    }
    return f;
}

template<class T>
unordered_map<string, double> Algorithm<T>::get_custom_stats() const {
    unordered_map<string, double> stats;
    if(phi == -1) {
        stats["threshold"] = TicketUtils::normalize_ticket(ticket_order.top()->ticket);
    } else {
        stats["threshold"] = TicketUtils::normalize_ticket(TicketUtils::estimate_ticket(floor(phi * this->N)));
    }
    return stats;
}


}