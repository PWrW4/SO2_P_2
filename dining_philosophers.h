//
// Created by wojtasiq on 25.04.2019.
//

#ifndef SO2_P_2_DINING_PHILOSOPHERS_H
#define SO2_P_2_DINING_PHILOSOPHERS_H

#include <atomic>
#include "fork.h"

class dining_philosophers {
public:
    std::array<fork, 10> forks;
    dining_philosophers();
    std::atomic<bool> ready{false};
};

dining_philosophers::dining_philosophers() {}

#endif //SO2_P_2_DINING_PHILOSOPHERS_H
