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

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  NUMBER,
  SYMBOL,
  FUNC
};

enum macro_keycodes {
  KC_CMD_TAB,
  KC_AG_FIND,
  KC_AG_AGAIN,
  KC_AG_UNDO,
  KC_AG_CUT,
  KC_AG_COPY,
  KC_AG_PASTE,
  KC_LSFT_MINS,
  KC_LSFT_EQL,
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO
// Macro definitions.
#define LSFT_MINS   M(KC_LSFT_MINS)     // Underscore sign.
#define LSFT_EQL    M(KC_LSFT_EQL)      // Plus sign.

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  `   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |  \   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | FUNC | Ctrl | Alt  | GUI  | Symb | Bksp |Enter |Space |Number|   [  |   ]  |      |
 * `-----------------------------------------------------------------------------------'
 *
 */
[_QWERTY] = {
  {KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,   KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_GRV },
  {KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,   KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT},
  {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,   KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_BSLS},
  {FUNC,    KC_LCTL, KC_LALT, KC_LGUI, SYMBOL, KC_BSPC, KC_ENT,  KC_SPC,  NUMBER,  KC_LBRC, KC_RBRC, _______}
},

/* SYMBOL
 * ,-----------------------------------------------------------------------------------.
 * |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |   _  |  +   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      | Left | Down |  Up  | Right|      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_SYMBOL] = {
  {KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,  LSFT_MINS, LSFT_EQL},
  {_______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, _______,   _______ },
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,   _______ },
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,   _______ }
},

/* NUMBER
 * ,-----------------------------------------------------------------------------------.
 * |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |   -  |  =   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_NUMBER] = {
  {KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
},

/* FUNC
 * ,-----------------------------------------------------------------------------------.
 * | F12  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
 * |-----------------------------------------------------------------------------------.
 * |      | Play | Prev | Next | BL+  |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      | Mute | Vol- | Vol+ | BL-  |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |Reset |
 * `-----------------------------------------------------------------------------------'
 */
[_FUNC] = {
  {KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11 },
  {_______, KC_MPLY, KC_MPRV, KC_MNXT, KC_PAUS, _______, _______, _______, _______, _______, _______, _______},
  {_______, KC_MUTE, KC_VOLD, KC_VOLU, KC_SLCK, _______, _______, _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RESET  }
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
