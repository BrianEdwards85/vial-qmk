/* Copyright 2025 @ Keychron (https://www.keychron.com)
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
#include "keychron_common.h"

enum custom_keycodes {
    M_LN_ = NEW_SAFE_RANGE,
};

enum layers {
    BASE,
    FN,
    CAD,
};
// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_tenkey_27(
        KC_MUTE, KC_CALC,  KC_DEL,  KC_TAB,  KC_BSPC,
        MC_1,    KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS,
        MC_2,    KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
        MC_3,    KC_P4,   KC_P5,   KC_P6,
        MC_4,    KC_P1,   KC_P2,   KC_P3,
        TT(FN),  KC_P0,            KC_PDOT, KC_PENT ),

    [FN] = LAYOUT_tenkey_27(
        _______, BT_HST1,     BT_HST2,     BT_HST3,     P2P4G,
        _______, _______,     _______,     _______,     _______,
        _______, LCTL(KC_P7), LCTL(KC_P7), LCTL(KC_P9), _______,
        _______, LCTL(KC_P4), KC_MPLY,     LCTL(KC_P6),
        _______, LCTL(KC_P1), LCTL(KC_P2), LCTL(KC_P3),
        _______, _______,                  _______,     _______),

    [CAD] = LAYOUT_tenkey_27(
        _______, M_LN_,   _______, _______, _______,
        _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,
        _______, _______, _______, _______, 
        _______, _______, _______, _______, 
        _______, _______,          _______, _______),
};

// clang-format on
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [FN]   = {ENCODER_CCW_CW(UG_VALD, UG_VALU)},
    [CAD] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
};
#endif // ENCODER_MAP_ENABLE

bool send_macro(char *string, keyrecord_t *record) {
    if (record->event.pressed) {
        SEND_STRING(string);
        return false;
    } else {
        return true;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case M_LN_:
            return send_macro("li\n", record);
        default:
            if (!process_record_keychron_common(keycode, record)) { return false; }
            return true;
    }
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    for (uint8_t i = led_min; i < led_max; i++) {
        switch(get_highest_layer(layer_state|default_layer_state)) {
            case 3:
                rgb_matrix_set_color(i, RGB_YELLOW);
                break;
            case 2:
                rgb_matrix_set_color(i, RGB_GREEN);
                break;
            case 1:
                rgb_matrix_set_color(i, RGB_RED);
                break;
            default:
                rgb_matrix_set_color(i, RGB_BLUE);

                break;
        }
    }
    return false;
}