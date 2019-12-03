#include QMK_KEYBOARD_H
#include "keymap_german.h"
#include "version.h"

#define BASE 0 // default layer
#define MISC 1

enum custom_keycodes {
#ifdef ORYX_CONFIGURATOR
  EPRM = EZ_SAFE_RANGE,
#else
  EPRM = SAFE_RANGE,
#endif
  VRSN,
  RGB_SLD
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[BASE] = LAYOUT_ergodox(
      /* Left Half */
      KC_ESC,  KC_1,         KC_2,    KC_3,    KC_4,   KC_5, KC_MEDIA_PLAY_PAUSE,
      KC_TAB,  KC_Q,         KC_W,    KC_E,    KC_R,   KC_T, KC_MEDIA_NEXT_TRACK,
      DE_CIRC, KC_A,         KC_S,    KC_D,    KC_F,   KC_G,
      KC_LSFT, LALT_T(DE_Y), KC_X,    KC_C,    KC_V,   KC_B, KC_MEDIA_PREV_TRACK,
      KC_LCTL, OSL(1),       DF(1),   KC_LALT, KC_RALT,

      /* Thumb cluster */
      KC_LEFT, KC_RIGHT,
      KC_HOME,
      KC_SPC, KC_BSPC, KC_END,

      /* Right Half */
      KC_PSCR,   KC_6, KC_7, KC_8,    KC_9,   KC_0,            KC_BSPC,
      DE_SS,     DE_Z, KC_U, KC_I,    KC_O,   KC_P,            DE_PLUS,
      /*      */ KC_H, KC_J, KC_K,    KC_L,   DE_HASH,         KC_ENT,
      DE_LESS,   KC_N, KC_M, DE_COMM, DE_DOT, RCTL_T(DE_MINS), KC_RSFT,
      KC_RALT, KC_RALT, KC_RALT, DE_GRV, KC_RGUI,

      /* Thumb cluster */
      KC_DOWN, KC_UP,
      KC_PGUP,
      KC_PGDN, KC_TAB, KC_LGUI
   ),
[MISC] = LAYOUT_ergodox(
      /* Left Half */
      KC_NO, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_NO,
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
      KC_NO, KC_NO, KC_DEL, KC_NO, KC_NO, KC_NO,
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
      DF(0), DF(0), DF(0), KC_NO, KC_NO,

      /* Thumb cluster */
      KC_NO, KC_NO,
      KC_NO,
      KC_NO, KC_NO, KC_NO,

      /* Right Half */
      KC_NO, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_NO,
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
      /* */  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,

      /* Thumb cluster */
      KC_NO, KC_NO,
      KC_NO,
      KC_NO, KC_NO, KC_NO
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch (keycode) {
      case EPRM:
        eeconfig_init();
        return false;
      case VRSN:
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        return false;
      #ifdef RGBLIGHT_ENABLE
      case RGB_SLD:
        rgblight_mode(1);
        return false;
      #endif
    }
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
#ifdef RGBLIGHT_COLOR_LAYER_0
  rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#endif
};

// Runs whenever there is a layer state change.
layer_state_t layer_state_set_user(layer_state_t state) {
  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();

  uint8_t layer = get_highest_layer(state);
  switch (layer) {
      case 0:
        #ifdef RGBLIGHT_COLOR_LAYER_0
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
        #else
        #ifdef RGBLIGHT_ENABLE
          rgblight_init();
        #endif
        #endif
        break;
      case 1:
        ergodox_right_led_1_on();
        #ifdef RGBLIGHT_COLOR_LAYER_1
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_1);
        #endif
        break;
      case 2:
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_2
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_2);
        #endif
        break;
      case 3:
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_3
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_3);
        #endif
        break;
      case 4:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_4
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_4);
        #endif
        break;
      case 5:
        ergodox_right_led_1_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_5
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_5);
        #endif
        break;
      case 6:
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_6
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
        #endif
        break;
      case 7:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_7
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_7);
        #endif
        break;
      default:
        break;
    }

  return state;
};
