#include <Arduino.h>
#include "keyboard_matrix_processor.h"

KBMatrixProcessor::KBMatrixProcessor(int numCol, int numRow, int *pinCol, int *pinRow) {
    this->numCol = numCol;
    this->numRow = numRow;
    this->pinCol = pinCol;
    this->pinRow = pinRow;
}

void KBMatrixProcessor::setKeyboardLayout(KeyLayout *keyLayout) {
    this->keyLayout = keyLayout;
}

void KBMatrixProcessor::start() {
    // Check if callback function were empty
    if(this->onPress == NULL) {
        Serial.println("No callback function defined, keyboard may not be executed well.");
    }

    // Create Emptied State
    this->state = new int[numCol*numRow]{};
    for(int i = 0; i < numCol*numRow; i++) {
        this->state[i] = 0;
    }
}

void KBMatrixProcessor::debugKeyboardLayout() {
    int totalLayout = this->numCol * this->numRow;

    for (int i = 0; i < totalLayout; i++) {
        KeyLayout n = this->keyLayout[i];
        Serial.printf("-  Index %d\n", i);
        Serial.printf("|_ Type: %d\n", n.type);

        if(n.type == 1) {
            for (int j = 0; j < 1; j++) {
                Serial.printf("|_ Key Number: %d\n", n.keys[j]);
            }
        }

       if(n.type == 2) {
            for(int j = 0; j < sizeof(n.keys) / sizeof(n.keys[0]); j++) {
                Serial.printf("|_ Chord %d: %d\n", j, n.keys[j]);
            }
        }
    }
}

void KBMatrixProcessor::setDebounce(int ms) {
    this->debounce = ms;
}

void KBMatrixProcessor::setOnPress(void(*onPress)(int, KeyLayout, KeyLayoutState)) {
    this->onPress = onPress;
}

int KBMatrixProcessor::calculateArrayPosition(int currentNumCol, int currentNumRow) {
    return (currentNumRow * this->numRow) + (currentNumCol);
}

void KBMatrixProcessor::poll() {
    if(millis() < this->lastSeenMs + this->debounce) {
        return;
    }
    this->lastSeenMs = millis();

    // Initialize INPUT_PULLUP for Column
    for(int i = 0; i < numRow; i++) {
        pinMode(this->pinRow[i], INPUT_PULLUP);
    }

    // Initialize OUTPUT for Column
    for(int i = 0; i < numCol; i++) {
        pinMode(this->pinCol[i], OUTPUT);
        digitalWrite(this->pinCol[i], LOW);

        // Read Value
        for(int j = 0; j < numRow; j++) {
            int state = !digitalRead(this->pinRow[j]);
            int index = calculateArrayPosition(i, j);

            if(this->state[index] != state) {
                this->state[index] = state;

                if(this->onPress != NULL) {
                    this->onPress(index, this->keyLayout[index], (KeyLayoutState) state);
                }
            }
        }

        // End Pulse
        digitalWrite(this->pinCol[i], HIGH);
        pinMode(this->pinCol[i], INPUT);
    }
}