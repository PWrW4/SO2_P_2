//
// Created by wojtasiq on 25.04.2019.
//

#include "ui.h"


std::vector<philosopher *> philosophers;
bool end = false;
int main(int argc, char **argv) {

    dining_table table;
    ui u;

    for (auto i = 0; i < THREAD_COUNT-1; i++) {
        philosopher *p = new philosopher(i + 1, table, std::ref(table.forks[i]),
                                         std::ref(table.forks[i + 1]));
        philosophers.push_back(p);
    }
    philosophers.push_back(new philosopher(THREAD_COUNT, table, table.forks[THREAD_COUNT-1], table.forks[0]));
    std::this_thread::sleep_for(std::chrono::seconds(1));
    table.ready = true;
    std::thread t1(&ui::update, &u);

    t1.join();
    for (auto p : philosophers) {
        p->t.join();
    }
    endwin();
    return 0;
}

ui::ui() {
    initscr();
    noecho();
    raw();
    nodelay(stdscr, TRUE);
    start_color();
    use_default_colors();
    curs_set(0);
    init_pair(1, COLOR_MAGENTA, -1);
    init_pair(2, COLOR_GREEN, -1);
    init_pair(3, COLOR_RED, -1);
    getmaxyx(stdscr, col, row);
    x = row / 2 - max_len;
    y = col / 2;
}

ui::~ui() { endwin(); }

void exit() { end = true; }

void ui::update_particular(philosopher *p) {
    int id = p->id;
    int state = p->state;
    std::lock_guard<std::mutex> guard(m);
    move(y + id - 10, 0);
    clrtoeol();
    move(y + id - 10, x);
    if (state == 2) {
        attron(COLOR_PAIR(3));
        printw("Philosopher %d is %s", id, states[state]);
    } else {
        int progress = p->progress;
        int lpad = (int)std::round(progress / 100.0f * LENGTH);
        int rpad = LENGTH - lpad;
        attron(COLOR_PAIR(state + 1));
        if (p->state==0){
            printw("Philosopher %d is %s            %3d%% [%.*s%*s]", id, states[state],
                   progress, lpad, PBAR, rpad, "");
        } else{
            printw("Philosopher %d is %s              %3d%% [%.*s%*s]", id, states[state],
                   progress, lpad, PBAR, rpad, "");
        }

        if (p->state==0){
            attron(COLOR_PAIR(2));
            move(y + p->left_fork.id - 8 + 10 , 0);
            clrtoeol();
            move(y + p->left_fork.id - 8 + 10 , x);
            printw("Widelec nr  %d jest wolny", p->left_fork.id+1);

            move(y + p->right_fork.id - 8 + 10 , 0);
            clrtoeol();
            move(y + p->right_fork.id - 8 + 10 , x);
            printw("Widelec nr  %d jest wolny", p->right_fork.id+1);
        } else {
            attron(COLOR_PAIR(3));
            move(y + p->left_fork.id - 8 + 10 , 0);
            clrtoeol();
            move(y + p->left_fork.id - 8 + 10 , x);
            printw("Widelec nr  %d jest zajety", p->left_fork.id+1);

            move(y + p->right_fork.id - 8 + 10 , 0);
            clrtoeol();
            move(y + p->right_fork.id - 8 + 10 , x);
            printw("Widelec nr  %d jest zajety", p->right_fork.id+1);
        }



    }



    refresh();
}

void ui::update() {
    while (true) {
        int c = getch();
        if (c == 113) {
            // Wyjście z programu
            for (auto phil : philosophers) {
                phil->exit = true;
            }
            return;
        }
        std::vector<std::thread> v;
        for (auto p : philosophers) {
            v.emplace_back(std::thread(&ui::update_particular, this, p));
        }

        for (auto &p : v) {
            p.join();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

