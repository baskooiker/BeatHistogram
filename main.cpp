/* 
 * File:   main.cpp
 * Author: Bas
 *
 * Created on 25 februari 2014, 16:43
 */

#include <cstdlib>
#include <vector>
#include <time.h>
#include <algorithm>
#include <fstream>
#include "BeatHistogram.h"

using namespace std;

/*
 * 
 */
float addXXXXOOXO(float val, BeatHistogram* bh) {
    for (int i = 0; i < 5; i++) {
        float noise = (rand() / (float) RAND_MAX) * 10. - 5.;
        if (i < 3)
            val += 125. + noise;
        else if (i == 3)
            val += 375. + noise;
        else
            val += 250. + noise;

        bh->push(val);
    }
    return val;
}

float addXOOXOOXO(float val, BeatHistogram* bh) {
    for (int i = 0; i < 3; i++) {
        float noise = (rand() / (float) RAND_MAX) * 10. - 5.;
        if (i < 2)
            val += 375. + noise;
        else
            val += 250. + noise;
        bh->push(val);
    }
    return val;
}

int main(int argc, char** argv) {

    srand(time(0));

    BeatHistogram* bh = new BeatHistogram();

    float val = .0;
    vector<float> data;
    for (int i = 0; i < 20; i++) {
        val = addXOOXOOXO(val, bh);
    }

    float beat = bh->interval();

    printf("interval = %f\n", beat);

    return 0;
}

