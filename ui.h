//
// Created by wojtasiq on 25.04.2019.
//

#ifndef SO2_P_2_UI_H
#define SO2_P_2_UI_H

#define PBAR "##################################################"
#define LENGTH 50
#define THREAD_COUNT 10


#include <cmath>
#include <iostream>
#include <map>
#include <ncurses.h>
#include <thread>
#include <vector>

#include "philosopher.h"
#include "dining_table.h"
#include "fork.h"

class ui {
private:
    int row;
    int col;
    int x;
    int y;
    const int max_len = 46;
    std::mutex m;
    std::map<int, const char *> states = {
        std::pair<int, const char *>(-1, "waiting for dining_table"),
        std::pair<int, const char *>(0, "thinking"),
        std::pair<int, const char *>(1, "eating"),
        std::pair<int, const char *>(2, "waiting for forks")};

public:
    ui();
    ~ui();

    void print_initial_state();
    void update_state(int id, const char *state, int progress);
    void update_particular(philosopher *p);
void update();
};


#endif //SO2_P_2_UI_H
