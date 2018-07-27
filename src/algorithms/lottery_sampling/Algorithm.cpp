#include "Algorithm.h"

using namespace LotterySampling;

Algorithm::Algorithm(const InputParser& parameters) {
    m = (unsigned  int) stoul(parameters.get_parameter("-m"));
    aging = parameters.has_parameter("-aging");
}

void Algorithm::frequent_query(float f, std::ostream& stream) {

}

void Algorithm::k_top_query(int k, std::ostream& stream) {

}

ElementLocator Algorithm::insert_element(std::string& element_id) {
    ElementLocator locator;
    Ticket ticket;
    if(size() < m) {
        locator.element_iterator = level_1.emplace(element_id, ticket, 1);
        locator.level = 1;
    } else {
        if(ticket > level_1.begin()->ticket) {
            locator.element_iterator = level_1.emplace(element_id, ticket, 1);
            locator.level = 1;
            // continue
        } else if(ticket > level_2.begin()->ticket) {
            locator.level = 2;
            // continue
        } else {
            locator.level = -1;
            // continue
        }
    }
    return locator;
}

void Algorithm::update_element(ElementLocator& locator) {

}

void Algorithm::print_state() {
}
