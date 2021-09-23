#include <Arduino.h>
#include "../lib/blekeyboardmouse/BleKeyboardMouse.h"
#include "layout.h"
#include "constants.h"
#include "../lib/keyboard_matrix_processor/keyboard_matrix_processor.h"
#include "../lib/keylayout/keylayout.h"
#include "../lib/encoder/encoder.h"

KBMatrixProcessor kbmInstance;
BleKeyboardMouse bleKeyboardMouse;
Encoder encoder;
Encoder secondaryEncoder;

void onChordKeyPressed(int index, KeyLayout whatKey, KeyLayoutState whatState) {
  // For chord key, let's pretend we're pressing fast enough and release at the same time
  if(whatState == KeyLayoutState::On) {
    for(int i = 0; i < 4; i++) {
      if(whatKey.keys[i] == 0x0) {
        continue;
      }

      bleKeyboardMouse.press(whatKey.keys[i]);    
    }
    
    delay(100);
    bleKeyboardMouse.releaseAll();
  }
}

void onSingleKeyPressed(int index, KeyLayout whatKey, KeyLayoutState whatState) {
  Serial.printf("Sending key %d\n",whatKey.keys[0]);
  if(whatState == KeyLayoutState::Off) {
    bleKeyboardMouse.release(whatKey.keys[0]);
  } else {
    bleKeyboardMouse.press(whatKey.keys[0]);
  }
}

void onMacroKeyPressed(int index, KeyLayout whatKey, KeyLayoutState whatState) {
   if(whatState == KeyLayoutState::On) {
     if(whatKey.func != NULL) {
       whatKey.func(&bleKeyboardMouse);
     }
   }
}


void onKeyPressed(int index, KeyLayout whatKey, KeyLayoutState whatState) {
  Serial.printf("Got key at index %d with type %d = State %d\n", index, whatKey.type, whatState);

  if(!bleKeyboardMouse.isConnected()) {
    Serial.printf("No bluetooth device connected. exiting.\n");
    return;
  }

  switch (whatKey.type) {
    case KeyLayoutType::None:
      return;
    case KeyLayoutType::Single:
      onSingleKeyPressed(index, whatKey, whatState);
      return;
    case KeyLayoutType::Chord:
      onChordKeyPressed(index, whatKey, whatState);
      return;
    case KeyLayoutType::Macro:
      onMacroKeyPressed(index, whatKey, whatState);
      return;
  }
}

void executeEncoder(RotaryEncoderAction action, const uint8_t* key) {
  switch(action) {
    case RotaryEncoderAction::KeyPress:
      if(key != NULL) {
        bleKeyboardMouse.press(*key);
        bleKeyboardMouse.release(*key);
      }
      break;
    case RotaryEncoderAction::ScrollUp:
      bleKeyboardMouse.mouseMove(0,0,1);
      break;
    case RotaryEncoderAction::ScrollDown:
      bleKeyboardMouse.mouseMove(0,0,-1);
      break;
  }
}

void executeEncoder(RotaryEncoderAction action, uint8_t key) {
  const uint8_t _key = key;
  executeEncoder(action, &_key);
}

void onEncoderRotated(EncoderMovement encMovement) {
  switch (encMovement) {
    case EncoderMovement::Left:
      executeEncoder(ENCODER_ACTION_A, ENCODER_KEY_A);
      break;
    case EncoderMovement::Right:
      executeEncoder(ENCODER_ACTION_B, ENCODER_KEY_B);
      break;
  }
}

void onSecondaryEncoderRotated(EncoderMovement encMovement) {
  switch (encMovement) {
    case EncoderMovement::Left:
      executeEncoder(SECONDARY_ENCODER_ACTION_A, SECONDARY_ENCODER_KEY_A);
      break;
    case EncoderMovement::Right:
      executeEncoder(SECONDARY_ENCODER_ACTION_B, SECONDARY_ENCODER_KEY_B);
      break;
  }
}


void setup() {
  Serial.begin(115200);

  // Start Bluetooth
  bleKeyboardMouse.begin();
  bleKeyboardMouse.setName("Project Keeb");

  
  kbmInstance = KBMatrixProcessor(NUMBER_OF_COLUMNS, NUMBER_OF_ROWS, COLUMN_PINS, ROW_PINS);
  kbmInstance.setKeyboardLayout(keys);

  // Protip: you can set the "hz" by calculating the debounce time against hz do you want
  // 1000 / hz = debounce time
  kbmInstance.setDebounce(8);

  // Set Callback
  kbmInstance.setOnPress(&onKeyPressed);

  // kbmInstance.debugKeyboardLayout();
  kbmInstance.start();

  // Setup encoder, if there's any
  if(ENCODER_ENABLED) {
    encoder = Encoder(ENCODER_PIN_A, ENCODER_PIN_B);
    encoder.setDebounce(8);
    encoder.setOffset(4);
    encoder.setCallback(&onEncoderRotated);
  }

  // Setup secondary encoder, if there's any
  if(SECONDARY_ENCODER_ENABLED) {
    secondaryEncoder = Encoder(SECONDARY_ENCODER_PIN_A, SECONDARY_ENCODER_PIN_B);
    secondaryEncoder.setDebounce(8);
    secondaryEncoder.setOffset(4);
    secondaryEncoder.setCallback(&onSecondaryEncoderRotated);
  }
}

void loop() {
  kbmInstance.poll();

  if(ENCODER_ENABLED) {  
    encoder.poll();
  }

  if(SECONDARY_ENCODER_ENABLED) {  
    secondaryEncoder.poll();
  }
} 