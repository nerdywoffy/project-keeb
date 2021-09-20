#include "../keylayout/keylayout.h"

class KBMatrixProcessor {
    public:
        KBMatrixProcessor() = default;
        KBMatrixProcessor(int numCol, int numRow, int *pinCol, int *pinRow);
        void setKeyboardLayout(KeyLayout *keyLayout);
        void setDebounce(int ms);
        void setOnPress(void(*onPress)(int, KeyLayout, KeyLayoutState));
        void start();

        void poll();

        void debugKeyboardLayout();
    private:
        int calculateArrayPosition(int currentNumCol, int currentNumRow);
        
        int numCol = 0;
        int numRow = 0;
        int *pinCol = {};
        int *pinRow = {};
        KeyLayout *keyLayout = {};
        int debounce = 0;
        int *state = {};
        int lastSeenMs = 0;
        void(*onPress)(int, KeyLayout, KeyLayoutState);
};
