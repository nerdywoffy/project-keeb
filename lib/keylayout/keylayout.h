#ifndef KEYLAYOUT
#define KEYLAYOUT

// KeyLayoutState Key Layout State
enum KeyLayoutState { Off = 0, On };

// KeyLayoutType Key Layout Type
// None is Ignored, Single is Singular Input, and Chord is Combination on a single press
// It has different behavior
enum KeyLayoutType { None = 0, Single, Chord, Macro };

// KeyLayout struct for saving key type and what keys are responsible to it
struct KeyLayout {
    KeyLayoutType type;
    int keys[4];
    void (*func)();
};

KeyLayout _None();
KeyLayout _Single(int keys);
KeyLayout _Chord(int key_one, int key_two, int key_three, int key_four);
KeyLayout _Macro(void (*func)());


#endif