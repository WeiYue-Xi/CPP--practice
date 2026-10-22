//
// Created by 24242 on 2026/10/21.
//

#ifndef OBJECTANDCLASS_TRACKER_H
#define OBJECTANDCLASS_TRACKER_H


class Tracker
{
private:
    static int liveCount;
public:
    Tracker()
    {
        liveCount++;
    }
    ~Tracker()
    {
        liveCount--;
    }
    static int getLiveCount();
};


#endif //OBJECTANDCLASS_TRACKER_H