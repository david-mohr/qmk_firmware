/*
 * Copyright 2022 Kevin Gee <info@controller.works>
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

#define LTH_IN  BSPC_DEL
#define LTH_MID LT(_NUM_NAV, KC_SPC)
#define LTH_OUT MT(MOD_LALT, KC_TAB)
#define RTH_OUT KC_ESC
#define RTH_MID LT(_SYM, KC_ENT)
#define RTH_IN  KC_QUOT

#define __HELD__ _______

enum dave_layers {
    _COLEMAKDH,
    _NUM_NAV,
    _SYM,
};

enum custom_keycodes {
    UPDIR = SAFE_RANGE,
    BSPC_DEL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_COLEMAKDH] = LAYOUT_split_3x5_3(
  //,--------------------------------------------.                    ,--------------------------------------------.
         KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                         KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
       HOME_A,  HOME_R,  HOME_S,  HOME_T,    KC_G,                         KC_M,  HOME_N,  HOME_E,  HOME_I,  HOME_O,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
        DMM_Z,   DMM_X,    KC_C,    KC_D,    KC_V,                         KC_K,    KC_H, KC_COMM,  KC_DOT, KC_SLSH,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                  LTH_IN, LTH_MID, LTH_OUT,    RTH_OUT, RTH_MID, RTH_IN
                             //`--------------------------'  `--------------------------'

  ),

  [_NUM_NAV] = LAYOUT_split_3x5_3(
  //,--------------------------------------------.                    ,--------------------------------------------.
      KC_MINS,    KC_7,    KC_8,    KC_9, XXXXXXX,                      XXXXXXX, XXXXXXX, KC_PGUP, KC_HOME, KC_KB_VOLUME_UP,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
         KC_0,    KC_1,    KC_2,    KC_3,KC_ENTER,                      KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, XXXXXXX,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
       KC_DOT,    KC_4,    KC_5,    KC_6, XXXXXXX,                      XXXXXXX, XXXXXXX, KC_PGDN, KC_END, KC_KB_VOLUME_DOWN,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                 _______,__HELD__,__HELD__,    _______,   MO(3),  KC_GRV
                             //`--------------------------'  `--------------------------'
  ),

  [_SYM] = LAYOUT_split_3x5_3(
  //,--------------------------------------------.                    ,--------------------------------------------.
      KC_TILD,   KC_LT,   KC_GT, KC_UNDS,   UPDIR,                      KC_AMPR, XXXXXXX, KC_LBRC, KC_RBRC, KC_PERC,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      KC_EXLM, KC_MINS, KC_PLUS,  KC_EQL, KC_HASH,                      KC_PIPE, KC_COLN, KC_LPRN, KC_RPRN,   KC_AT,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      KC_CIRC, KC_SLSH, KC_ASTR, KC_BSLS, XXXXXXX,                      XXXXXXX,  KC_DLR, KC_LCBR, KC_RCBR, KC_QUES,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                 _______,   MO(3), _______,    _______,__HELD__, _______
                             //`--------------------------'  `--------------------------'
  ),

  [3] = LAYOUT_split_3x5_3(
  //,--------------------------------------------.                    ,--------------------------------------------.
      QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_WH_U, KC_MS_U, KC_WH_D,   DT_UP,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI,                      XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD,                      XXXXXXX, KC_BTN1, KC_BTN3, KC_BTN2, DT_DOWN,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                 _______, _______, _______,    _______, _______, _______
                             //`--------------------------'  `--------------------------'
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint8_t saved_mods = 0;
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
		}
        // switch to layer 2 with the ALT key held
        else if (record->event.pressed) {
          layer_on(_NUM_NAV);
        } else {
          layer_off(_NUM_NAV);
		}
		return true;
      case BSPC_DEL:
        if (record->event.pressed) {
          saved_mods = get_mods() & MOD_MASK_SHIFT;

          if (saved_mods == MOD_MASK_SHIFT) {  // Both shifts pressed
            register_code(KC_DEL);
          } else if (saved_mods) {   // One shift pressed
            del_mods(saved_mods);  // Remove any Shifts present
            register_code(KC_DEL);
            add_mods(saved_mods);  // Add shifts again
          } else {
            register_code(KC_BSPC);
          }
        } else {
          unregister_code(KC_DEL);
          unregister_code(KC_BSPC);
        }
        return false;
    }
    return true;
}
