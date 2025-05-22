/* Copyright 2023 splitkb.com <support@splitkb.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* TODO
[X] Modify basic base layers
[X] Modify basic NUM
[X] Modify basic NAV
[X] Sticky shift
[X] Sticky mods
[X] Fix conditional layers
[ ] Modify basic MERGE
[ ] Modify basic MEDIA
[X] Create simple Swapper
[X] Add browser tab to NUM
[X] Create cancel key - try KC_CANCEL - seems to work.
[X] base layer toggle - on thumb key because using tapdance to base layer toggle goes to wrong layer.
[X] Add Delete and RET combos
[ ] mod morph function keys
*/
#include QMK_KEYBOARD_H

enum layers {
    _BASE = 0,
    _M_BASE,
    _G_BASE,
    _NUM,
    _M_NUM,
    _NAV,
    _M_NAV,
    _MERGE,
    _M_MERGE,
    _MEDIA,
    _M_MEDIA,
};

// Aliases for readability in keymap
#define BASE    DF(_BASE)
#define M_BASE  DF(_M_BASE)
#define G_BASE  DF(_G_BASE)

#define NUM      MO(_NUM)
#define NAV      MO(_NAV)
#define MERGE    MO(_MERGE)
#define MEDIA    MO(_MEDIA)

#define W_CUT LCTL(KC_X)
#define W_COPY LCTL(KC_C)
#define W_PASTE LCTL(KC_V)
#define W_UNDO LCTL(KC_Z)
#define W_REDO LCTL(LSFT(KC_Z))

#define M_CUT LGUI(KC_X) 
#define M_COPY LGUI(KC_C)
#define M_PASTE LGUI(KC_V)
#define M_UNDO LGUI(KC_Z)
#define M_REDO LSG(KC_Z)

#define NTAB LCTL(KC_TAB)
#define PTAB LCTL(LSFT(KC_TAB))
#define W_RELOAD KC_F5
#define M_RELOAD LGUI(KC_R)

#define W_SWAPPER LALT(KC_TAB)
#define M_SWAPPER LGUI(KC_TAB)

#define CTL_ESC  MT(MOD_LCTL, KC_ESC)
#define CTL_QUOT MT(MOD_RCTL, KC_QUOTE)
#define CTL_MINS MT(MOD_RCTL, KC_MINUS)
#define ALT_ENT  MT(MOD_LALT, KC_ENT)
// #define NUM_BKSP LT(_NUM, KC_BSPC) - longer require leave for example

// Note: LAlt/Enter (ALT_ENT) is not the same thing as the keyboard shortcut Alt+Enter.
// The notation `mod/tap` denotes a key that activates the modifier `mod` when held down, and
// produces the key `tap` when tapped (i.e. pressed and released).

// Conditional Layers
layer_state_t layer_state_set_user(layer_state_t state) {
  state = update_tri_layer_state(state, _NUM, _M_BASE, _M_NUM);
  state = update_tri_layer_state(state, _NAV, _M_BASE, _M_NAV);
  return state;
}

// Tap Dance
//enum {
    //MINUS_MBASE,
   // MINUS_GBASE,
   // MINUS_WBASE,
//};

// Tap Dance definitions
//tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    //[MINUS_MBASE] = ACTION_TAP_DANCE_LAYER_MOVE(KC_MINUS, 2),
    //[MINUS_GBASE] = ACTION_TAP_DANCE_DOUBLE(KC_MINUS, TO(_G_BASE)),
    //[MINUS_WBASE] = ACTION_TAP_DANCE_DOUBLE(KC_MINUS, TO(_BASE)),
//};
// Combos
enum combos {
  JK_BKSPACE,
  KL_DEL,
  RF_RET,
  ED_BKSPACE
};

const uint16_t PROGMEM jk_combo[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM kl_combo[] = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM rf_combo[] = {KC_R, KC_F, COMBO_END};
const uint16_t PROGMEM ed_combo[] = {KC_E, KC_D, COMBO_END};

combo_t key_combos[] = {
  [JK_BKSPACE] = COMBO(jk_combo, KC_BSPC),
  [KL_DEL] = COMBO(kl_combo, KC_DEL),
  [RF_RET] = COMBO(rf_combo, KC_ENT),
  [ED_BKSPACE] = COMBO(ed_combo, KC_BSPC),
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: BASE (Windows)
 *
 * ,-------------------------------------------.      ,------.  ,------.      ,-------------------------------------------.
 * |  Esc   |   1  |   2  |   3  |   4  |   5  |      |LShift|  |RShift|      |   6  |   7  |   8  |   9  |   0  |  Esc   |
 * |--------+------+------+------+------+------|      |------|  |------|      |------+------+------+------+------+--------|
 * |  Tab   |   Q  |   W  |   E  |   R  |   T  |      |LCtrl |  | RCtrl|      |   Y  |   U  |   I  |   O  |   P  |  Bksp  |
 * |--------+------+------+------+------+------|      |------|  |------|      |------+------+------+------+------+--------|
 * |Ctrl/Esc|   A  |   S  |   D  |   F  |   G  |      | LAlt |  | RAlt |      |   H  |   J  |   K  |   L  | ;  : |Ctrl/' "|
 * |--------+------+------+------+------+------+------+------|  |------|------+------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  | [ {  |CapsLk|  |F-keys|  ] } |   N  |   M  | ,  < | . >  | /  ? | RShift |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |MEDIA| LGUI  | LAlt/| Space| NUM  |  | NUM  | Shift| AltGr| RGUI | Menu |
 *                        |      |      | Enter|      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 *
 * ,----------------------------.      ,------.                 ,----------------------------.      ,------.
 * | Prev | Next | Pause | Stop |      | Mute |                 | Prev | Next | Pause | Stop |      | Mute |
 * `----------------------------'      `------'                 `----------------------------'      '------'
 */
    [_BASE] = LAYOUT_myr(
      KC_ESC  , KC_1 ,  KC_2   ,  KC_3  ,   KC_4 ,   KC_5 ,         XXXXXXX,     XXXXXXX,          KC_6 ,  KC_7 ,  KC_8 ,   KC_9 ,  KC_0 , KC_MINUS,
      KC_TAB  , KC_Q ,  KC_W   ,  KC_E  ,   KC_R ,   KC_T ,         XXXXXXX,     XXXXXXX,          KC_Y ,  KC_U ,  KC_I ,   KC_O ,  KC_P , KC_EQL,
      KC_LSFT , KC_A ,  KC_S   ,  KC_D  ,   KC_F ,   KC_G ,         XXXXXXX,     XXXXXXX,          KC_H ,  KC_J ,  KC_K ,   KC_L ,KC_SCLN, KC_QUOTE,
      KC_LCTL , KC_Z ,  KC_X   ,  KC_C  ,   KC_V ,   KC_B , KC_LBRC, XXXXXXX,     XXXXXXX  , TO(_M_BASE), KC_N ,  KC_M ,KC_COMM, KC_DOT ,KC_SLSH, KC_CANCEL,
                                KC_LALT , KC_LGUI,   NUM, KC_SPC ,XXXXXXX,     XXXXXXX   , OSM(MOD_LSFT) ,NAV, XXXXXXX, XXXXXXX,

      KC_MPRV, KC_MNXT, KC_MPLY, KC_MSTP,    KC_MUTE,                            KC_MPRV, KC_MNXT, KC_MPLY, KC_MSTP,    KC_MUTE
    ),
/*
 * Base Layer: Mac
 */
    [_M_BASE] = LAYOUT_myr(
      _______, _______, _______, _______, _______, _______,          _______, _______,          _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______,          _______, _______,          _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______,          _______, _______,          _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, TO(_G_BASE), _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,

      _______, _______, _______, _______,          _______,                   _______, _______, _______, _______,          _______
    ),

/*
 * Base Layer: Gaming
 */
    [_G_BASE] = LAYOUT_myr(
      _______, _______, _______, _______, _______, _______,          _______, _______,          _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______,          _______, _______,          _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______,          _______, _______,          _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, TO(_BASE), _______, _______, _______, _______, _______, _______,
                                 _______, KC_LCTL, KC_LSFT, _______, _______, _______, XXXXXXX, KC_ENT, _______, _______,

      _______, _______, _______, _______,          _______,                   _______, _______, _______, _______,          _______
    ),

/*
 * NAV Layer: Navigation & Symbols
 *
 * ,-------------------------------------------.      ,------.  ,------.      ,-------------------------------------------.
 * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |------|  |------|      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      | PgUp | Home |   ↑  | End  | VolUp| Delete |
 * |--------+------+------+------+------+------|      |------|  |------|      |------+------+------+------+------+--------|
 * |        |  GUI |  Alt | Ctrl | Shift|      |      |      |  |      |      | PgDn |  ←   |   ↓  |   →  | VolDn| Insert |
 * |--------+------+------+------+------+------+------+------|  |------|------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |ScLck |  |      |      | Pause|M Prev|M Play|M Next|VolMut| PrtSc  |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 *
 * ,----------------------------.      ,------.                 ,----------------------------.      ,------.
 * | Prev | Next | Pause | Stop |      | Mute |                 | Prev | Next | Pause | Stop |      | Mute |
 * `----------------------------'      `------'                 `----------------------------'      '------'
 */
    [_NAV] = LAYOUT_myr(
      KC_ESC , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,          _______, _______,          KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10, KC_F11,
      _______, KC_TILD, KC_LT  , KC_LBRC, KC_RBRC, KC_GT  ,          _______, _______,          KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_PSCR, KC_F12,
      _______, KC_GRV , KC_UNDS, KC_LPRN, KC_RPRN, KC_AMPR,          _______, _______,          KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_ENT,  KC_INS,
      _______, KC_BSLS, KC_AT  , KC_LCBR, KC_RCBR, KC_PIPE, _______, KC_SCRL, _______, _______,KC_PAUSE, KC_BSPC, KC_DEL,  KC_TAB,  XXXXXXX, XXXXXXX,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,

      _______, _______, _______, _______,          _______,                   _______, _______, _______, _______,          _______
    ),

/*
 * NAV Layer: Mac
 */
    [_M_NAV] = LAYOUT_myr(
      _______, _______, _______, _______, _______, _______,          _______, _______,          _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______,          _______, _______,          _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______,          _______, _______,          _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,

      _______, _______, _______, _______,          _______,                   _______, _______, _______, _______,          _______
    ),



/*
 * NUM Layer: Numbers, Calum mods and a few symbols
 *
 * ,-------------------------------------------.      ,------.  ,------.      ,-------------------------------------------.
 * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |------|  |------|      |------+------+------+------+------+--------|
 * |    `   |  1   |  2   |  3   |  4   |  5   |      |      |  |      |      |   6  |  7   |  8   |  9   |  0   |   =    |
 * |--------+------+------+------+------+------|      |------|  |------|      |------+------+------+------+------+--------|
 * |    ~   |  !   |  @   |  #   |  $   |  %   |      |      |  |      |      |   ^  |  &   |  *   |  (   |  )   |   +    |
 * |--------+------+------+------+------+------+------+------|  |------|------+------+------+------+------+------+--------|
 * |    |   |   \  |  :   |  ;   |  -   |  [   |  {   |      |  |      |   }  |   ]  |  _   |  ,   |  .   |  /   |   ?    |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 *
 * ,-----------------------------.      ,------.                ,---------------------------.      ,------.
 * |        |      |      |      |      |      |                |      |      |      |      |      |      |
 * `-----------------------------'      `------'                `---------------------------'      '------'
 */
    [_NUM] = LAYOUT_myr(
     KC_ESC  , XXXXXXX, XXXXXXX, PTAB, NTAB, W_RELOAD,                                    _______, _______,          KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10, KC_F11,
     XXXXXXX , KC_HASH, KC_AT  ,KC_MINS , W_SWAPPER , KC_EQL ,                            _______, _______,          KC_PERC, KC_7   , KC_8  ,  KC_9 , KC_ASTR , XXXXXXX ,
     XXXXXXX , OSM(MOD_LGUI), OSM(MOD_LALT), OSM(MOD_LCTL), OSM(MOD_LSFT), KC_PLUS,       _______, _______,          KC_DOT , KC_0   , KC_1  , KC_2  , KC_3, XXXXXXX,
     XXXXXXX , W_UNDO,    W_CUT, W_COPY , W_PASTE, W_REDO , KC_LCBR,                      _______, _______,          KC_RCBR, XXXXXXX, KC_4   , KC_5  ,  KC_6 , KC_SLSH, XXXXXXX,
                                                      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,

      _______, _______, _______, _______,          _______,                   _______, _______, _______, _______,          _______
    ),

/*
 * NAV Layer: Mac
 */
    [_M_NUM] = LAYOUT_myr(
      _______, _______, _______, _______, _______, M_RELOAD,                              _______, _______,          _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, M_SWAPPER, _______,                             _______, _______,          _______, _______, _______, _______, _______, _______,
      _______, OSM(MOD_LCTL), _______, OSM(MOD_LGUI), OSM(MOD_LSFT), _______,             _______, _______,          _______, _______, _______, _______, _______, _______,
      _______, M_UNDO, M_CUT, M_COPY, M_PASTE, M_REDO, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                                      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,

      _______, _______, _______, _______,          _______,                   _______, _______, _______, _______,          _______
    ),


/*
 * MERGE Layer: MERGE keys
 *
 * ,-------------------------------------------.      ,------.  ,------.      ,-------------------------------------------.
 * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |------|  |------|      |------+------+------+------+------+--------|
 * |        |  F9  | F10  | F11  | F12  |      |      |      |  |      |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |------|  |------|      |------+------+------+------+------+--------|
 * |        |  F5  |  F6  |  F7  |  F8  |      |      |      |  |      |      |      | Shift| Ctrl |  Alt |  GUI |        |
 * |--------+------+------+------+------+------+------+------|  |------|------+------+------+------+------+------+--------|
 * |        |  F1  |  F2  |  F3  |  F4  |      |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 *
 * ,-----------------------------.      ,------.                ,---------------------------.      ,------.
 * |        |      |      |      |      |      |                |      |      |      |      |      |      |
 * `-----------------------------'      `------'                `---------------------------'      '------'
 */
    [_MERGE] = LAYOUT_myr(
      _______, _______, _______, _______, _______, _______,          _______, _______,          _______, _______, _______, _______, _______, _______,
      _______,  KC_F9 ,  KC_F10,  KC_F11,  KC_F12, _______,          _______, _______,          _______, _______, _______, _______, _______, _______,
      _______,  KC_F5 ,  KC_F6 ,  KC_F7 ,  KC_F8 , _______,          _______, _______,          _______, KC_RSFT, KC_RCTL, KC_LALT, KC_RGUI, _______,
      _______,  KC_F1 ,  KC_F2 ,  KC_F3 ,  KC_F4 , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,

      _______, _______, _______, _______,          _______,                   _______, _______, _______, _______,          _______
    ),

/*
 * Merge Layer: Mac
 */
    [_M_MERGE] = LAYOUT_myr(
      _______, _______, _______, _______, _______, _______,          _______, _______,          _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______,          _______, _______,          _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______,          _______, _______,          _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,

      _______, _______, _______, _______,          _______,                   _______, _______, _______, _______,          _______
    ),


/*
 * MEDIA Layer: Default layer settings, RGB
 *
 * ,-------------------------------------------.      ,------.  ,------.      ,-------------------------------------------.
 * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |------|  |------|      |------+------+------+------+------+--------|
 * |        |      |      |BASE|      |      |      |      |  |      |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |------|  |------|      |------+------+------+------+------+--------|
 * |        |      |      |M_BASE|      |      |      |      |  |      |      | TOG  | SAI  | HUI  | VAI  | MOD  |        |
 * |--------+------+------+------+------+------+------+------|  |------|------+------+------+------+------+------+--------|
 * |        |      |      |Colmak|      |      |      |      |  |      |      |      | SAD  | HUD  | VAD  | RMOD |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 *
 * ,-----------------------------.      ,------.                ,---------------------------.      ,------.
 * |        |      |      |      |      |      |                |      |      |      |      |      |      |
 * `-----------------------------'      `------'                `---------------------------'      '------'
 */
    [_MEDIA] = LAYOUT_myr(
      _______, _______, _______, _______, _______, _______,         _______, _______,          _______, _______, _______, _______,  _______, _______,
      _______, _______, _______, BASE , _______, _______,         _______, _______,          _______, _______, _______, _______,  _______, _______,
      _______, _______, _______, M_BASE , _______, _______,         _______, _______,          RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI,  RGB_MOD, _______,
      _______, _______, _______, G_BASE, _______, _______,_______, _______, _______, _______, _______, RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD, _______,
                                 _______, _______, _______,_______, _______, _______, _______, _______, _______, _______,

      _______, _______, _______, _______,          _______,                   _______, _______, _______, _______,          _______

    ),

/*
 * Media Layer: Mac
 */
    [_M_MEDIA] = LAYOUT_myr(
      _______, _______, _______, _______, _______, _______,          _______, _______,          _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______,          _______, _______,          _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______,          _______, _______,          _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,

      _______, _______, _______, _______,          _______,                   _______, _______, _______, _______,          _______
    ),


};

/* The default OLED and rotary encoder code can be found at the bottom of qmk_firmware/keyboards/splitkb/elora/rev1/rev1.c
 * These default settings can be overriden by your own settings in your keymap.c
 * DO NOT edit the rev1.c file; instead override the weakly defined default functions by your own.
 */

/* DELETE THIS LINE TO UNCOMMENT (1/2)
#ifdef OLED_ENABLE
bool oled_task_user(void) {
  // Your code goes here
}
#endif

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
  // Your code goes here
}
#endif
DELETE THIS LINE TO UNCOMMENT (2/2) */