#include <Arduino.h>
#include "../lib/ESP32-BLE-KeyboardMouse/BleKeyboardMouse.h"
#include "layout.h"
#include "../lib/keyboard_matrix_processor/keyboard_matrix_processor.h"
#include "../lib/keylayout/keylayout.h"
#include "../lib/encoder/encoder.h"

KBMatrixProcessor kbmInstance;
BleKeyboardMouse bleKeyboardMouse;
Encoder encoder;

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

void onEncoderRotated(EncoderMovement encMovement) {
  switch (encMovement) {
    case EncoderMovement::Left:
      // bleKeyboardMouse.press(ENCODER_KEY_A);
      // bleKeyboardMouse.release(ENCODER_KEY_A);
      bleKeyboardMouse.mouseMove(0,0,1);
      break;
    case EncoderMovement::Right:
      bleKeyboardMouse.mouseMove(0,0,-1);
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
}

void loop() {
  kbmInstance.poll();

  if(ENCODER_ENABLED) {  
    encoder.poll();
  }
} 