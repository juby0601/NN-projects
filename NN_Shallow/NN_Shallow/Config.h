#pragma once

const unsigned int SAMPLE_SIZE = 246;
const unsigned int TOTAL_WINDOW_SIZE = 147;
const unsigned int WINDOW_SIZE = 50;
const unsigned int NUMBER_OF_LAYERS = 4;
const unsigned int FIRST_HIDDEN_LAYER_NEURONS = 10;
const unsigned int SECOND_HIDDEN_LAYER_NEURONS = 3;
const unsigned int OUTPUT_NEURONS = 1;
const double WEIGHT_SCALE = 1;
const double WEIGHT_MIN = -WEIGHT_SCALE;
const double WEIGHT_MAX = WEIGHT_SCALE;
const double LERANING_RATE = 0.1;
const double ERROR_THRESHOLD = 0.01;
const double BIAS = 0.01;
const double ALPHA = 0.8;
const int EPOCHS = 5000;