#include <Arduino.h>
#include <BleKeyboard.h>
#include "layout.h"
#include "../lib/keyboard_matrix_processor/keyboard_matrix_processor.h"
#include "../lib/keylayout/keylayout.h"

KBMatrixProcessor kbmInstance;
BleKeyboard bleKeyboard;

void onChordKeyPressed(int index, KeyLayout whatKey, KeyLayoutState whatState) {
  // For chord key, let's pretend we're pressing fast enough and release at the same time
  if(whatState == KeyLayoutState::On) {
    for(int i = 0; i < 4; i++) {
      if(whatKey.keys[i] == 0x0) {
        continue;
      }

      bleKeyboard.press(whatKey.keys[i]);    
    }
    
    delay(100);
    bleKeyboard.releaseAll();
  }
}

void onSingleKeyPressed(int index, KeyLayout whatKey, KeyLayoutState whatState) {
  Serial.printf("Sending key %d\n",whatKey.keys[0]);
  if(whatState == KeyLayoutState::Off) {
    bleKeyboard.release(whatKey.keys[0]);
  } else {
    bleKeyboard.press(whatKey.keys[0]);
  }
}

void onMacroKeyPressed(int index, KeyLayout whatKey, KeyLayoutState whatState) {
   if(whatState == KeyLayoutState::On) {
     if(whatKey.func != NULL) {
       whatKey.func(&bleKeyboard);
     }
   }
}


void onKeyPressed(int index, KeyLayout whatKey, KeyLayoutState whatState) {
  Serial.printf("Got key at index %d with type %d = State %d\n", index, whatKey.type, whatState);

  if(!bleKeyboard.isConnected()) {
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

void setup() {
  Serial.begin(115200);

  // Start Bluetooth
  bleKeyboard.begin();
  bleKeyboard.setName("Project Keeb");

  kbmInstance = KBMatrixProcessor(NUMBER_OF_COLUMNS, NUMBER_OF_ROWS, COLUMN_PINS, ROW_PINS);
  kbmInstance.setKeyboardLayout(keys);

  // Protip: you can set the "hz" by calculating the debounce time against hz do you want
  // 1000 / hz = debounce time
  kbmInstance.setDebounce(8);

  // Set Callback
  kbmInstance.setOnPress(&onKeyPressed);

  // kbmInstance.debugKeyboardLayout();
  kbmInstance.start();
}


void loop() {
  kbmInstance.poll();
}