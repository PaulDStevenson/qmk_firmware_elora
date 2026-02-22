#include "swapper.h"

void update_swapper(bool *active, uint16_t cmdish, uint16_t tabish,
                    uint16_t trigger, uint16_t rev_trigger,
                    uint16_t keycode, keyrecord_t *record) {
    if (keycode == trigger) {
        if (record->event.pressed) {
            if (!*active) {
                *active = true;
                register_code(cmdish);
            }
            register_code(tabish);
        } else {
            unregister_code(tabish);
        }
    } else if (keycode == rev_trigger) {
        if (record->event.pressed) {
            if (!*active) {
                *active = true;
                register_code(cmdish);
            }
            register_code(KC_LSFT);
            register_code(tabish);
        } else {
            unregister_code(tabish);
            unregister_code(KC_LSFT);
        }
    } else if (*active && record->event.pressed) {
        *active = false;
        unregister_code(cmdish);
    }
}
