#pragma once
#include <math.h>


const unsigned int SAMPLE_SIZE = 50000;
const unsigned int TOTAL_NUMBER_OF_CLASSES = 10;
const unsigned int TOTAL_NUMBER_OF_IMAGES = 5000;
const unsigned int TOTAL_NUMBER_OF_TEST_IMAGES = 10000;
const unsigned int PIXELS_PER_COLOR_PER_IMAGE = 1024;
const unsigned int TOTAL_VALUES_PER_IMAGE = PIXELS_PER_COLOR_PER_IMAGE * 3 + 1;

const unsigned int TOTAL_WINDOW_SIZE = 50000;
const unsigned int NUMBER_OF_LAYERS = 4;
const unsigned int NUMBER_OF_INPUTS = 1024;
const unsigned int OUTPUT_NEURONS = 10;
const unsigned int LAYER_NEURONS[NUMBER_OF_LAYERS] = { NUMBER_OF_INPUTS, 500, 100, OUTPUT_NEURONS };
const double WEIGHT_SCALE = 4*sqrt(6.0/(double)(OUTPUT_NEURONS+NUMBER_OF_INPUTS));;
const double WEIGHT_MIN = -WEIGHT_SCALE;
const double WEIGHT_MAX = WEIGHT_SCALE;
const double LERANING_RATE = 0.1;
const double BIAS = 0.5;
const double ALPHA = 0.9;
const int EPOCHS = 50000;
const double XOFFSET = 1.5;
const double YOFFSET =  0.8; 
const double XSCALE = 4.5;
const double YSCALE = 2;