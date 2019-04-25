//
// Created by wojtasiq on 25.04.2019.
//

#ifndef SO2_P_2_FORK_H
#define SO2_P_2_FORK_H
#include <mutex>
#include "ui.h"

class fork {
public:
    int id;
    std::mutex mtx;
};


#endif //SO2_P_2_FORK_H
