#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#endif

#include "schedwork.h"

using namespace std;

static const Worker_T INVALID_ID = (unsigned int)-1;

// Add prototypes for any helper functions here
bool verification(DailySchedule& sched, const AvailabilityMatrix& avail, vector<size_t>& shiftCounts, const size_t dailyNeed, const size_t maxShifts, size_t d_, size_t w_);

// Add your implementation of schedule() and other helper functions here
bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
) {
    if (avail.empty()) return false;
    sched.clear();

    std::vector<size_t> shiftCounts(avail[0].size(), 0);
    sched.resize(avail.size(), std::vector<Worker_T>(dailyNeed));

    return verification(sched, avail, shiftCounts, dailyNeed, maxShifts, 0, 0);
}

bool verification(DailySchedule& sched, const AvailabilityMatrix& avail, std::vector<size_t>& shiftCounts, const size_t dailyNeed, const size_t maxShifts, size_t d_, size_t w_ ) {
    
    //base case
    if (d_ == avail.size()) return true;

    if (w_ == dailyNeed) return verification(sched, avail, shiftCounts, dailyNeed, maxShifts, d_ + 1, 0);

    
    for (int i = 0; i < avail[d_].size(); i++) {

        if (avail[d_][i] && shiftCounts[i] < maxShifts) {

            sched[d_][w_] = i;
            shiftCounts[i]++;

            if (verification(sched, avail, shiftCounts, dailyNeed, maxShifts, d_, w_ + 1)) return true;

            sched[d_][w_] = INVALID_ID;
            shiftCounts[i]--;
            
        }
    }

    return false;
}