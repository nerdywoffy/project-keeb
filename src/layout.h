#include <Arduino.h>
#include "../lib/keylayout/keylayout.h"
#include "constants.h"
#include "macros/macros.h"

#ifndef KEEB_LAYOUT
#define KEEB_LAYOUT

// Declare your Keeb Layout Here
// for input, try to read from documentation at lib/keyboard_layout/keyboard_layout.h

// NUMBER_OF_ROWS Number of Rows that are included on a single project
const int NUMBER_OF_ROWS = 4;
// NUMBER_OF_COLUMNS Number of Columns that are included on a single project
const int NUMBER_OF_COLUMNS = 5;

// ROW_PINS Number of Row Pins that are included on a single project
int ROW_PINS[NUMBER_OF_ROWS] = {13, 12, 14, 27};
// COLUMN_PINS Number of Column Pins that are included on a single project
int COLUMN_PINS[NUMBER_OF_COLUMNS] = {15, 2, 4, 5, 18};

// keys Mapping of keyboard
// make sure to read constants.h to change key type.
KeyLayout keys[NUMBER_OF_ROWS*NUMBER_OF_COLUMNS] = {
    _None(),_None(),_None(),_None(),_None(),
    _None(),_None(),_None(),_None(),_None(),  
    _None(),_None(),_None(),_None(),_None(),  
    _None(),_None(),_None(),_None(),_None(),
};  


// ENCODER_ENABLED Enable Encoder Support
const bool ENCODER_ENABLED = true;

// ENCODER_PIN_A Encoder Pin A
int ENCODER_PIN_A = 23;
// ENCODER_PIN_B Encoder Pin B
int ENCODER_PIN_B = 22;

// ENCODER_KEY_A Encoder Key A
const uint8_t *ENCODER_KEY_A = KEY_MEDIA_VOLUME_DOWN;
// ENCODER_KEY_A Encoder Key B
const uint8_t *ENCODER_KEY_B = KEY_MEDIA_VOLUME_UP;

#endif