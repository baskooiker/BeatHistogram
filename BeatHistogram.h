/* 
 * File:   BeatHistogram.h
 * Author: Bas
 *
 * Created on 25 februari 2014, 17:04
 */

#ifndef BEATHISTOGRAM_H
#define	BEATHISTOGRAM_H

#include <deque>

using namespace std;

class BeatHistogram {
public:
    BeatHistogram();
    BeatHistogram(const BeatHistogram& orig);
    virtual ~BeatHistogram();

    // methods
    float interval();
    void push(float time);
    void clear();
    
private:
    // data
    deque<float> buffer;
    
    // parameters
    int buffersize;
    float maxInterval;
    float histogramD;
    int minBuffer;
    int smoothRange;
    
};

#endif	/* BEATHISTOGRAM_H */

