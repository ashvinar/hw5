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

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here

bool scheduleHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    vector<size_t>& workerShifts,
    size_t day,
    size_t workerPos);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    
    sched.resize(avail.size());
    for(size_t i = 0; i < avail.size(); i++) {
        sched[i].resize(dailyNeed, INVALID_ID);
    }
    
    vector<size_t> workerShifts(avail[0].size(), 0);
    return scheduleHelper(avail, dailyNeed, maxShifts, sched, workerShifts, 0, 0);
}

bool scheduleHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    vector<size_t>& workerShifts,
    size_t day,
    size_t workerPos)
{
    if(day == avail.size()) {
        return true;
    }
    
    if(workerPos == dailyNeed) {
        return scheduleHelper(avail, dailyNeed, maxShifts, sched, workerShifts, day + 1, 0);
    }
    
    for(size_t worker = 0; worker < avail[day].size(); worker++) {
        if(avail[day][worker] && workerShifts[worker] < maxShifts) {
            bool alreadyScheduled = false;
            for(size_t i = 0; i < workerPos; i++) {
                if(sched[day][i] == worker) {
                    alreadyScheduled = true;
                    break;
                }
            }
            
            if(!alreadyScheduled) {
                sched[day][workerPos] = worker;
                workerShifts[worker]++;
                
                if(scheduleHelper(avail, dailyNeed, maxShifts, sched, workerShifts, day, workerPos + 1)) {
                    return true;
                }
                
                sched[day][workerPos] = INVALID_ID;
                workerShifts[worker]--;
            }
        }
    }
    
    return false;
}

