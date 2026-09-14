#ifndef TIMESLOT_H
#define TIMESLOT_H

#include <iostream>
#include <string>
using namespace std;

class TimeSlot{
    private:
        string day;
        int startTime;
        int endTime;
        string location;

    public:
        TimeSlot();

        TimeSlot(const string& day,int startTime,int endTime,const string& location);

        string getDay()const;
        int getStartTime()const;
        int getEndTime()const;
        string getLocation()const;

        bool operator==(const TimeSlot& other) const;
        friend ostream& operator<<(ostream& os,const TimeSlot& slot);

};

#endif