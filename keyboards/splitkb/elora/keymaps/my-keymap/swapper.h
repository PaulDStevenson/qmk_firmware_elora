#pragma once
#include QMK_KEYBOARD_H

// Implements a "smart" modifier+key swapper with reverse support.
// The modifier (cmdish) is held for as long as the trigger or reverse trigger
// key is being repeatedly pressed. It is released as soon as any other key
// is pressed. The reverse trigger sends Shift+tabish to cycle backwards.
//
// Example usage (Alt-Tab window switcher):
//   update_swapper(&active, KC_LALT, KC_TAB, SW_WIN, SW_WIN_REV, keycode, record);
void update_swapper(
    bool    *active,
    uint16_t cmdish,
    uint16_t tabish,
    uint16_t trigger,
    uint16_t rev_trigger,
    uint16_t keycode,
    keyrecord_t *record
);
