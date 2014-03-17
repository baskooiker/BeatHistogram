/* 
 * File:   BeatHistogram.cpp
 * Author: Bas
 * 
 * Created on 25 februari 2014, 17:04
 */

#include "BeatHistogram.h"
#include <deque>
#include <vector>
#include <fstream>
#include <stdlib.h>

using namespace std;

BeatHistogram::BeatHistogram() {
    buffersize = 10;
    maxInterval = 4000.;
    histogramD = 10.;
    minBuffer = 10;
    smoothRange = 3;
}

BeatHistogram::BeatHistogram(const BeatHistogram& orig) {
}

BeatHistogram::~BeatHistogram() {
}

void BeatHistogram::push(float time) {
    buffer.push_back(time);
    if (buffer.size() > buffersize)
        buffer.pop_front();
}

float BeatHistogram::interval() {
    if (buffer.size() < minBuffer)
        return -1;

    vector<float> intervals;
    for (int i = 0; i < buffer.size(); i++) {
        for (int j = i + 1; j < buffer.size(); j++) {
            float dif = buffer[j] - buffer[i];
            if (dif < maxInterval)
                intervals.push_back(dif);
            else
                break;
        }
    }

    // init histogram
    vector<int> hist;
    for (int i = 0; i < maxInterval / histogramD; i++)
        hist.push_back(0);

    // fill histogram
    for (int i = 0; i < intervals.size(); i++)
        hist[intervals[i] / histogramD]++;

    // sum histogram
    vector<float> sumHist;
    for (int i = 0; i < hist.size(); i++) {
        sumHist.push_back(0.);
        for (int j = -smoothRange; j <= smoothRange; j++)
            if (j + i > 0 && j + 1 < hist.size())
                sumHist[i] += (float)hist[i + j] * (smoothRange - abs(j)) / (float)smoothRange;
    }

    // write to file
    ofstream out;
    out.open("hist.txt");
    ofstream out2;
    out2.open("sumHist.txt");
    for (int i = 0; i < hist.size(); i++){
        out << hist[i] << "\n";
        out2 << sumHist[i] << "\n";
    }
    out.close();
    out2.close();

    // find maximum index
    int index = 0;
    float value = sumHist[0];
    for (int i = 1; i < sumHist.size(); i++) {
        if (sumHist[i] > value) {
            value = sumHist[i];
            index = i;
        }
    }

    return (float) index * histogramD;
}

void BeatHistogram::clear() {
    buffer.clear();
}