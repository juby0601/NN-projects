#pragma once
#include <math.h>

const unsigned int SAMPLE_SIZE = 200;
const unsigned int TOTAL_WINDOW_SIZE = 100;
const unsigned int NUMBER_OF_INPUTS = 2;
const unsigned int NUMBER_OF_LAYERS = 4;
const unsigned int FIRST_HIDDEN_LAYER_NEURONS = 10;
const unsigned int SECOND_HIDDEN_LAYER_NEURONS = 5;
const unsigned int OUTPUT_NEURONS = 1;
const double WEIGHT_SCALE = 4*sqrt(6/(OUTPUT_NEURONS+NUMBER_OF_INPUTS));
const double WEIGHT_MIN = -WEIGHT_SCALE;
const double WEIGHT_MAX = WEIGHT_SCALE;
const double LERANING_RATE = 0.05;
const double ERROR_THRESHOLD = 0.01;
const double BIAS = 0.0;
const double ALPHA = 0.9;
const int EPOCHS = 50000;
const double XOFFSET = -0.75;
const double YOFFSET = -0.2; 
const double XSCALE = 2.25;
const double YSCALE = 1;