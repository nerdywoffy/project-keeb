#include <ESP32Encoder.h>

#ifndef ENCODERLIB
#define ENCODERLIB
    enum EncoderMovement {Left = 0, Right};
#endif

class Encoder {
    public:
        Encoder() = default;
        Encoder(int pinA, int pinB);

        void setDebounce(int debounce);
        void setOffset(int offset);
        void setCallback(void(*callback)(EncoderMovement));

        void poll();
    private:
        ESP32Encoder enc = {};
        int pinA = 0;
        int pinB = 0;
        int debounce = 0;
        int offset = 0;

        int lastSeenValue = 0;
        int lastSeenMillis = 0;
        void(*callback)(EncoderMovement) = NULL;
        void sendCallback(EncoderMovement encMovement);
};
