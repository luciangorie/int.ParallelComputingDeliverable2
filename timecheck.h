#ifndef __TIMECHECK__
#define __TIMECHECK__

#include <iostream>
#include <sys/time.h>

class Timer {
private:
    struct timeval start, end;
    bool running;

public:
    Timer() : running(false) {}

    void startTimer() {
        gettimeofday(&start, nullptr);
        running = true;
    }

    void stopTimer() {
        if (running) {
            gettimeofday(&end, nullptr);
            running = false;
        } else {
            std::cerr << "Il timer non è in esecuzione" << std::endl;
        }
    }

    long getElapsedTimeMicroseconds() const {
        if (running) {
            std::cerr << "Timer ancora in esecuzione" << std::endl;
            return 0;
        }
        long seconds = end.tv_sec - start.tv_sec;
        long microseconds = end.tv_usec - start.tv_usec;
        return seconds * 1000000 + microseconds;
    }

    // Calcolare il tempo trascorso in millisecondi
    double getElapsedTimeMilliseconds() const {
        return getElapsedTimeMicroseconds() / 1000.0;
    }

    // Calcolare il tempo trascorso in secondi
    double getElapsedTimeSeconds() const {
        return getElapsedTimeMicroseconds() / 1000000.0;
    }
};



#endif
