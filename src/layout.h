#include <Arduino.h>
#include "../lib/usbhid_keys/usbhid_keys.h"
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
    _Chord(KEY_LEFT_CTRL, KEY_LEFT_SHIFT,0xB1, 0x00),_None(),_None(),_None(),_None(),  
    _None()       ,_None(),_None(),_None(),_None(),  
    _None()       ,_None(),_None(),_None(),_None(),  
    _None()       ,_None(),_None(),_None(),_None(),
};  

#endif