//
// Created by 24242 on 2026/10/21.
//

#ifndef OBJECTANDCLASS_SCORE_H
#define OBJECTANDCLASS_SCORE_H


class Score
{
private:
    int value;
public:
    Score(int n = 0)
        :value(n)
    {

    }
    Score(const Score& other)
        :value(other.value)
    {

    }
    Score& operator=(const Score& other);
    void setValue(int n)
    {
        value = n;
    }
    int getValue() const
    {
        return value;
    }
};


#endif //OBJECTANDCLASS_SCORE_H