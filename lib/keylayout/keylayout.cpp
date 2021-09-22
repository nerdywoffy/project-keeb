#include "keylayout.h"
#include "../blekeyboardmouse/BleKeyboardMouse.h"

// _None a function that shortcut KeyLayout object creation with KeyLayoutType::None
// used to make layout.h more "humanly-readable"
KeyLayout _None() {
    return KeyLayout{KeyLayoutType::None, {}};
}

// _Single a function that shortcut KeyLayout object creation with KeyLayoutType::Single
// used to make layout.h more "humanly-readable"
KeyLayout _Single(int keys) {
    return  KeyLayout{KeyLayoutType::Single, {keys}};
}

// _Chord a function that shortcut KeyLayout object creation with KeyLayoutType::Chord
// used to make layout.h more "humanly-readable"
KeyLayout _Chord(int key_one, int key_two, int key_three, int key_four) {
    return KeyLayout{KeyLayoutType::Chord, {key_one, key_two, key_three, key_four}};
}

// _Macro a function that shortcut KeyLayout object creation with KeyLayoutType::Macro
// used to make layout.h more "humanly-readable"
KeyLayout _Macro(void (*func)(BleKeyboardMouse*)) {
    // ! This aren't implemented yet.
    return KeyLayout{KeyLayoutType::Macro, {}, func};
}
