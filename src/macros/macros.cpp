#include <Arduino.h>
#include <BleKeyboard.h>

void summon_tasque_manager(BleKeyboard* bleKeyboard) {
    // Send CTRL+ALT+DELETE
    bleKeyboard->press(KEY_LEFT_CTRL);
    bleKeyboard->press(KEY_LEFT_ALT);
    bleKeyboard->press(KEY_DELETE);
    bleKeyboard->releaseAll();
    delay(500);

    for(int i = 0; i < 3; i++) {
        bleKeyboard->press(KEY_DOWN_ARROW);
        bleKeyboard->release(KEY_DOWN_ARROW);
        delay(100);
    }
    delay(500);

    bleKeyboard->press(KEY_RETURN);
    bleKeyboard->releaseAll();
}