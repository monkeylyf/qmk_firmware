#include "planck.h"
#include "action_layer.h"
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _NUMBER 1
#define _SYMBOL 2
#define _FUNC 3
#define _MOUSECURSOR 4

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  NUMBER,
  SYMBOL,
  FUNC
};

enum macro_keycodes {
  KC_LSFT_MINS,
  KC_LSFT_EQL,
};

// Fillers to make layering more clear.
#define _______ KC_TRNS
#define XXXXXXX KC_NO
// Custom Macros.
#define SFT_TAB       SFT_T(KC_TAB)               // Tap for tab, hold for shift.
#define GUI_MINS      GUI_T(KC_MINS)              // Tap for minus(-), hold for GUI.
// Requires KC_TRNS/_______ for the trigger key in the destination layer.
#define LT_MC(kc)     LT(_MOUSECURSOR, kc)        // L-ayer T-ap M-ouse C-ursor.
#define LT_D_MC       LT_MC(KC_D)                 // Tap for d, hold for mouse cursor layer.
#define LT_NB(kc)     LT(_NUMBER, kc)             // L-ayer T-ap N-umB-er.
#define ENT_NB        LT_NB(KC_ENT)               // Tap for enter, hold for Number layer.
#define LT_SB(kc)     LT(_SYMBOL, kc)             // L-ayer T-ap S-ymB-ol.
#define ESC_SB        LT_SB(KC_ESC)               // Tap for ESC, hold for Symbol layer.

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  \   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Func |   A  |   S  | MC/D |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |Sf/Tab|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Ctrl | Alt  |  GUI | Bksp |SB/ESC|NB/Ent|Space |   -  |   =  |      |      |
 * `-----------------------------------------------------------------------------------'
 *
 */
[_QWERTY] = {
  {KC_GRV,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,   KC_Y,   KC_U,   KC_I,    KC_O,   KC_P,    KC_BSLS},
  {FUNC,    KC_A,    KC_S,    LT_D_MC, KC_F,    KC_G,   KC_H,   KC_J,   KC_K,    KC_L,   KC_SCLN, KC_QUOT},
  {SFT_TAB, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT, KC_SLSH, KC_RSFT},
  {_______, KC_LCTL, KC_LALT, KC_LGUI, KC_BSPC, ESC_SB, ENT_NB, KC_SPC, KC_MINS, KC_EQL, _______, _______}
},

/* SYMBOL
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |   (  |   )  |
 * |------+------+------+------+------+------+------+------+------+------|------+------+
 * |      |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |      |   [  |   ]  |
 * |------+------+------+------+------+-------------+------+------+------|------+------+
 * |      |      |      |      |      |      |      |      |      |      |   {  |   }  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 *
 */
[_SYMBOL] = {
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_LPRN, KC_RPRN},
  {_______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, _______, KC_LBRC, KC_RBRC},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_LCBR, KC_RCBR},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
},

/* NUMBER
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_NUMBER] = {
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
},

/* FUNC
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  | F10  | F11  | F12  |
 * |-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      | Left | Down |  Up  | Right|      |      |
 * `-----------------------------------------------------------------------------------'
 * |      |      |      |      |      |      | Play | Prev | Next | BL+  |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      | Mute | Vol- | Vol+ | BL-  |      |Reset |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 */
[_FUNC] = {
  {KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,  KC_F12 },
  {_______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, _______, _______},
  {_______, _______, _______, _______, _______, _______, KC_MPLY, KC_MPRV, KC_MNXT, KC_PAUS,  _______, _______},
  {_______, _______, _______, _______, _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, KC_SLCK,  _______, RESET  }
},

/* Mouse Layer
 * ,-----------------------------------------------------------------------------------.
 * |      |      | BTN4 |      | BTN3 |      |      |WHL_Up|  Up  |WHL_Dn|      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      | BTN2 |      | BTN1 |      |WHL_L | Left | Down |Right |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      | BTN5 |      |WHL_R |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |ACCL2 |ACCL0 |      |ACCL1 |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */

[_MOUSECURSOR] = {
  {_______, _______, KC_BTN4, _______, KC_BTN3, _______, _______, KC_WH_U, KC_MS_U, KC_WH_D, _______, _______},
  {_______, _______, KC_BTN2, _______, KC_BTN1, _______, KC_WH_L, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______},
  {_______, _______, _______, _______, KC_BTN5, _______, KC_WH_R, _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, KC_ACL2, KC_ACL0, _______, KC_ACL1, _______, _______, _______, _______}
}

};

// Audio setup.
#ifdef AUDIO_ENABLE
float tone_startup[][2] = {
    ED_NOTE(_E7 ),
    E__NOTE(_CS7),
    E__NOTE(_E6 ),
    E__NOTE(_A6 ),
    M__NOTE(_CS7, 20)
};

float tone_qwerty[][2]    = SONG(QWERTY_SOUND);
float tone_plover_gb[][2] = SONG(PLOVER_GOODBYE_SOUND);
float tone_goodbye[][2]   = SONG(GOODBYE_SOUND);
float music_scale[][2]    = SONG(MUSIC_SCALE_SOUND);
#endif

void matrix_init_user(void) {
  #ifdef AUDIO_ENABLE
    startup_user();
  #endif
}

#ifdef AUDIO_ENABLE
void startup_user() {
  _delay_ms(20);  // gets rid of tick.
  //PLAY_NOTE_ARRAY(tone_startup, false, 0);
  PLAY_NOTE_ARRAY(music_scale, false, 0);
}

void shutdown_user() {
  PLAY_NOTE_ARRAY(tone_goodbye, false, 0);
  _delay_ms(150);
  stop_all_notes();
}

void music_on_user(void) {
  music_scale_user();
}

void music_scale_user(void) {
  PLAY_NOTE_ARRAY(music_scale, false, 0);
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_NOTE_ARRAY(tone_qwerty, false, 0);
        #endif
        default_layer_set(1UL << _QWERTY);
      }
      return false;
      break;
    case NUMBER:
      if (record->event.pressed) {
        layer_on(_NUMBER);
      } else {
        layer_off(_NUMBER);
      }
      return false;
    case SYMBOL:
      if (record->event.pressed) {
        layer_on(_SYMBOL);
      } else {
        layer_off(_SYMBOL);
      }
      return false;
    case FUNC:
      if (record->event.pressed) {
        layer_on(_FUNC);
      } else {
        layer_off(_FUNC);
      }
      return false;
  }
  return true;
}

// Macro events.
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  switch (id) {
    case KC_LSFT_EQL:
      return MACRODOWN(D(LSFT), T(EQL), END);
      break;
    case KC_LSFT_MINS:
      return MACRODOWN(D(LSFT), T(MINS), END);
      break;
  }
  return MACRO_NONE;
}
