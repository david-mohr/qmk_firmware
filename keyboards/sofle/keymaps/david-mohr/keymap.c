#include QMK_KEYBOARD_H

#define HOME_A LGUI_T(KC_A)
#define HOME_R LALT_T(KC_R)
#define HOME_S LCTL_T(KC_S)
#define HOME_T LSFT_T(KC_T)

#define HOME_N RSFT_T(KC_N)
#define HOME_E RCTL_T(KC_E)
#define HOME_I LALT_T(KC_I)
#define HOME_O RGUI_T(KC_O)

#define DMM_Z LCTL_T(KC_Z)
#define DMM_X LSFT_T(KC_X)

#define __HELD__ _______

enum sofle_layers {
    _COLEMAKDH,
    _NUM_NAV,
    _SYM,
};

enum custom_keycodes {
    UPDIR = SAFE_RANGE,
    KC_ALTNUM,
};

// I've removed the top row completely, the two outer buttons on each side of the bottom row and the outer columns of the main rows
// Essentially left with 3x15 + 3 on each hand
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_COLEMAKDH] = LAYOUT(
  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                                 XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
  XXXXXXX,   KC_Q,     KC_W,     KC_F,     KC_P,     KC_B,                                    KC_J,     KC_L,     KC_U,     KC_Y,    KC_SCLN,  XXXXXXX,
  XXXXXXX,  HOME_A,   HOME_R,   HOME_S,   HOME_T,    KC_G,                                    KC_M,    HOME_N,   HOME_E,   HOME_I,   HOME_O,   XXXXXXX,
  XXXXXXX,  DMM_Z,    DMM_X,     KC_C,     KC_D,     KC_V,   KC_MUTE,               KC_BTN3,  KC_K,     KC_H,    KC_COMM,  KC_DOT,   KC_SLSH,  XXXXXXX,
  XXXXXXX,XXXXXXX,       KC_BSPC,LT(_NUM_NAV, KC_SPC),MT(MOD_LALT, KC_TAB),          KC_ESC,  LT(_SYM, KC_ENT),  KC_QUOT,            XXXXXXX,  XXXXXXX
),

[_NUM_NAV] = LAYOUT(
  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
  XXXXXXX,  XXXXXXX,   KC_7,     KC_8,     KC_9,    XXXXXXX,                       XXXXXXX,  XXXXXXX,  KC_PGUP,  XXXXXXX,  XXXXXXX,  XXXXXXX,
  XXXXXXX,   KC_0,    KC_1,     KC_2,     KC_3,     XXXXXXX,                       KC_LEFT,  KC_DOWN,   KC_UP,   KC_RGHT,  XXXXXXX,  XXXXXXX,
  XXXXXXX,  KC_DOT,   KC_4,     KC_5,     KC_6,    KC_ENTER, _______,     _______, XXXXXXX,  XXXXXXX,  KC_PGDN,  XXXXXXX,  XXXXXXX,  XXXXXXX,
  XXXXXXX,  XXXXXXX,                    _______, __HELD__, __HELD__,     _______, _______, _______,             XXXXXXX,  XXXXXXX
),
[_SYM] = LAYOUT(
  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
  XXXXXXX,  KC_TILD,   KC_LT,    KC_GT,   KC_UNDS,  UPDIR,                          KC_AMPR,  KC_GRV,  KC_LBRC,  KC_RBRC,  KC_PERC,  XXXXXXX,
  XXXXXXX,  KC_EXLM,  KC_MINS,  KC_PLUS,  KC_EQL,   KC_HASH,                        KC_PIPE,  KC_COLN,  KC_LPRN,  KC_RPRN,   KC_AT,   XXXXXXX,
  XXXXXXX,  KC_CIRC,  KC_SLSH,  KC_ASTR,  KC_BSLS,  XXXXXXX,  _______,   _______,   XXXXXXX,  KC_DLR,   KC_LCBR,  KC_RCBR,  KC_QUES,  XXXXXXX,
  XXXXXXX, XXXXXXX,                         _______, _______, _______,    _______, __HELD__, _______,                       XXXXXXX,  XXXXXXX
),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_caps_word(keycode, record)) { return false; }
    switch (keycode) {
      case UPDIR:  // Types ../ to go up a directory on the shell.
        if (record->event.pressed) {
          SEND_STRING("../");
        }
        return false;
      case MT(MOD_LALT, KC_TAB):
		if (record->tap.count && record->event.pressed) {
          tap_code16(KC_TAB);
		  return false;
		} else if (record->event.pressed) {
          // register_mods(mod_config(MOD_LALT));
          layer_on(_NUM_NAV);
        } else {
          // unregister_mods(mod_config(MOD_LALT));
          layer_off(_NUM_NAV);
		}
		return true;
      case KC_COPY:
        if (record->event.pressed) {
          register_mods(mod_config(MOD_LCTL));
          register_code(KC_C);
        } else {
          unregister_mods(mod_config(MOD_LCTL));
          unregister_code(KC_C);
        }
        return false;
      case KC_PASTE:
        if (record->event.pressed) {
          register_mods(mod_config(MOD_LCTL));
          register_code(KC_V);
        } else {
          unregister_mods(mod_config(MOD_LCTL));
          unregister_code(KC_V);
        }
        return false;
      case KC_CUT:
        if (record->event.pressed) {
          register_mods(mod_config(MOD_LCTL));
          register_code(KC_X);
        } else {
          unregister_mods(mod_config(MOD_LCTL));
          unregister_code(KC_X);
        }
        return false;
      case KC_ALTNUM:
        if (record->event.pressed) {
          register_mods(mod_config(MOD_LALT));
          layer_on(_NUM_NAV);
        } else {
          unregister_mods(mod_config(MOD_LALT));
          layer_off(_NUM_NAV);
        }
		if (record->tap.count && record->event.pressed) {
			tap_code16(C(KC_C)); // Intercept tap function to send Ctrl-C
		} else if (record->event.pressed) {
			tap_code16(C(KC_V)); // Intercept hold function to send Ctrl-V
		}
        break;
    }
    return true;
}

#ifdef ENCODER_ENABLE

static int8_t l_ticks = 0;
bool encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) {
    if (clockwise) { ++l_ticks; } else { --l_ticks; }  // Count up or down.
    if (abs(l_ticks) >= 5) {                           // Take action!
      tap_code(clockwise ? KC_VOLD : KC_VOLU);
      l_ticks = 0;                                     // Reset counter.
    }
  } else if (index == 1) {
    if (clockwise) {
      tap_code(KC_MS_WH_DOWN);
    } else {
      tap_code(KC_MS_WH_UP);
    }
  }
  return true;
}

#endif
