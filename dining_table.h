//
// Created by wojtasiq on 25.04.2019.
//

#ifndef SO2_P_2_DINING_TABLE_H
#define SO2_P_2_DINING_TABLE_H

#include "philosopher.h"
#include <atomic>
#include "fork.h"
#include <queue>

class dining_table {
public:
    std::array<fork, THREAD_COUNT> forks;
    dining_table();
    std::atomic<bool> ready{false};
};

dining_table::dining_table() {
    for (int i = 0; i < THREAD_COUNT; ++i) {
        forks.at(i).id = i;
    }
}

#endif //SO2_P_2_DINING_TABLE_H
