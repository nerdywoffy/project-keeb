#include "encoder.h"
#include <Arduino.h>

Encoder::Encoder(int pinA, int pinB) {
    this->pinA = pinA;
    this->pinB = pinB;

    ESP32Encoder::useInternalWeakPullResistors=UP;
	this->enc.attachFullQuad(this->pinA, this->pinB);
	this->enc.setCount(0);
}

void Encoder::setDebounce(int debounce) {
    this->debounce = debounce;
}

void Encoder::setOffset(int offset) {
    this->offset = offset;
}

void Encoder::setCallback(void(*callback)(EncoderMovement)) {
    this->callback = callback;
}

void Encoder::sendCallback(EncoderMovement encMovement) {
    if(this->callback == NULL) {
        return;
    }

    this->callback(encMovement);
}

void Encoder::poll() {
    if((millis() + this->debounce) < this->lastSeenMillis) {
        return;
    }
    this->lastSeenMillis = millis();

    int currentEncoderState = (int32_t)this->enc.getCount();
    if((currentEncoderState > (this->lastSeenValue+this->offset)) ||
        (currentEncoderState < (this->lastSeenValue-this->offset))) {

            if(currentEncoderState > this->lastSeenValue) {
                this->sendCallback(EncoderMovement::Right);
            } else if (currentEncoderState < this->lastSeenValue) {
                this->sendCallback(EncoderMovement::Left);
            }

            this->lastSeenValue = currentEncoderState;
    }
}