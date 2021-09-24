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
const bool ENCODER_ENABLED = false;

// ENCODER_PIN_A Encoder Pin A
int ENCODER_PIN_A = 22;
// ENCODER_PIN_B Encoder Pin B
int ENCODER_PIN_B = 21;

// ENCODER_ACTION_A Encoder Action A 
const RotaryEncoderAction ENCODER_ACTION_A = KeyPress;
// ENCODER_ACTION_A Encoder Action B
const RotaryEncoderAction ENCODER_ACTION_B = KeyPress;

// ENCODER_KEY_A Encoder Key A (Only if action is KeyPress)
const uint8_t *ENCODER_KEY_A = KEY_MEDIA_VOLUME_DOWN;
// ENCODER_KEY_A Encoder Key B (Only if action is KeyPress)
const uint8_t *ENCODER_KEY_B = KEY_MEDIA_VOLUME_UP;

// SECONDARY_ENCODER_ENABLED Enable Encoder Support
const bool SECONDARY_ENCODER_ENABLED = false;

// SECONDARY_ENCODER_PIN_A Encoder Pin A
int SECONDARY_ENCODER_PIN_A = 22;
// SECONDARY_ENCODER_PIN_B Encoder Pin B
int SECONDARY_ENCODER_PIN_B = 21;

// SECONDARY_ENCODER_ACTION_A Encoder Action A 
const RotaryEncoderAction SECONDARY_ENCODER_ACTION_A = KeyPress;
// SECONDARY_ENCODER_ACTION_A Encoder Action B
const RotaryEncoderAction SECONDARY_ENCODER_ACTION_B = KeyPress;

// SECONDARY_ENCODER_KEY_A Encoder Key A (Only if action is KeyPress)
const uint8_t *SECONDARY_ENCODER_KEY_A = KEY_MEDIA_VOLUME_DOWN;
// SECONDARY_ENCODER_KEY_A Encoder Key B (Only if action is KeyPress)
const uint8_t *SECONDARY_ENCODER_KEY_B = KEY_MEDIA_VOLUME_UP;


// TERNARY_ENCODER_ENABLED Enable Encoder Support
const bool TERNARY_ENCODER_ENABLED = false;

// TERNARY_ENCODER_PIN_A Encoder Pin A
int TERNARY_ENCODER_PIN_A = 22;
// TERNARY_ENCODER_PIN_B Encoder Pin B
int TERNARY_ENCODER_PIN_B = 21;

// TERNARY_ENCODER_ACTION_A Encoder Action A 
const RotaryEncoderAction TERNARY_ENCODER_ACTION_A = KeyPress;
// TERNARY_ENCODER_ACTION_A Encoder Action B
const RotaryEncoderAction TERNARY_ENCODER_ACTION_B = KeyPress;

// TERNARY_ENCODER_KEY_A Encoder Key A (Only if action is KeyPress)
const uint8_t *TERNARY_ENCODER_KEY_A = KEY_MEDIA_VOLUME_DOWN;
// SECONDARY_ENCODER_KEY_A Encoder Key B (Only if action is KeyPress)
const uint8_t *TERNARY_ENCODER_KEY_B = KEY_MEDIA_VOLUME_UP;

#endif