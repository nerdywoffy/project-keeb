#include <Arduino.h>
#include "../../lib/ESP32-BLE-KeyboardMouse/BleKeyboardMouse.h"

void summon_tasque_manager(BleKeyboardMouse* bleKeyboardMouse) {
    // Send CTRL+ALT+DELETE
    bleKeyboardMouse->press(KEY_LEFT_CTRL);
    bleKeyboardMouse->press(KEY_LEFT_ALT);
    bleKeyboardMouse->press(KEY_DELETE);
    bleKeyboardMouse->releaseAll();
    delay(500);

    for(int i = 0; i < 3; i++) {
        bleKeyboardMouse->press(KEY_DOWN_ARROW);
        bleKeyboardMouse->release(KEY_DOWN_ARROW);
        delay(100);
    }
    delay(500);

    bleKeyboardMouse->press(KEY_RETURN);
    bleKeyboardMouse->releaseAll();
}