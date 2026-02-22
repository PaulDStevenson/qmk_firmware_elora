#pragma once
#include QMK_KEYBOARD_H

// Implements a "smart" modifier+key swapper.
// The modifier (cmdish) is held for as long as the trigger key is being
// repeatedly pressed. It is released as soon as any other key is pressed.
//
// Example usage (Alt-Tab window switcher):
//   update_swapper(&sw_win_active, KC_LALT, KC_TAB, SW_WIN, keycode, record);
void update_swapper(
    bool    *active,
    uint16_t cmdish,
    uint16_t tabish,
    uint16_t trigger,
    uint16_t keycode,
    keyrecord_t *record
);
