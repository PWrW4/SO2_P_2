//
// Created by wojtasiq on 25.04.2019.
//

#ifndef SO2_P_2_PHILOSOPHER_H
#define SO2_P_2_PHILOSOPHER_H

#include <atomic>
#include <chrono>
#include <mutex>
#include <random>
#include <thread>
#include <vector>

#include "fork.h"
#include "dining_philosophers.h"

class philosopher {
public:
    int id;
    dining_philosophers &table;
    fork &left_fork;
    fork &right_fork;
    std::thread t;
    std::mt19937 rng{std::random_device{}()};
    int state = -1;
    int progress = 0;
    std::mutex m;
    bool exit = false;
    philosopher(int _id, dining_philosophers &table_ref, fork &l, fork &r)
            : id(_id), table(table_ref), left_fork(l), right_fork(r),
              t(&philosopher::live, this) {}
    void live();
    void eat();
    void think();
};

void philosopher::live() {
    while (!table.ready) {
        std::this_thread::yield();
    }
    while (!exit) {
        think();
        state = 2;
        // wait_for_forks();
        eat();
        // release_forks();
    }
    return;
}

void philosopher::think() {
    // std::unique_lock<std::mutex> guard(m, std::defer_lock);
    // guard.lock();
    state = 0;
    // guard.unlock();
    int part = std::uniform_int_distribution<int>(15, 25)(rng);
    for (auto i = 1; i <= part; i++) {
        if (exit) {
            return;
        }
        double p = (double)i / (double)part;
        // guard.lock();
        progress = std::round(p * 100.0);
        // guard.unlock();
        // std::thread t(&ui::update_state, &u, id, "thinking", progress);
        // u.update_state(id, "thinking", progress);
        // t.join();

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

void philosopher::eat() {
    std::lock(left_fork.mtx, right_fork.mtx);
    std::lock_guard<std::mutex> left_lock(left_fork.mtx, std::adopt_lock);
    std::lock_guard<std::mutex> right_lock(right_fork.mtx, std::adopt_lock);
    state = 1;
    int part = std::uniform_int_distribution<int>(15, 25)(rng);
    for (auto i = 1; i <= part; i++) {
        if (exit) {
            return;
        }
        double p = (double)i / (double)part;
        progress = std::round(p * 100.0);
        // std::thread t(&ui::update_state, &u, id, "thinking", progress);
        // u.update_state(id, "thinking", progress);
        // t.join();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

#endif //SO2_P_2_PHILOSOPHER_H
