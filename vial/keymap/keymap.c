/* Copyright 2020 Naoki Katahira

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

 * along with this program.  If not, see <http\://www\.gnu.org/licenses/>.

 */

#include QMK_KEYBOARD_H

#include <stdio.h>
#include "profiles.h"

enum layer_number {

    _QWERTY = 0,

    _LOWER,

    _RAISE,

    _ADJUST

};

// Orden de matriz de Vial (10 x 6); los dos huecos físicos son KC_NO.
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = {
        {KC_GRAVE, KC_1, KC_2, KC_3, KC_4, KC_5},
        {KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T},
        {TD(0), KC_A, KC_S, KC_D, KC_F, KC_G},
        {KC_LCTL, KC_Z, KC_X, KC_C, KC_V, KC_B},
        {KC_NO, KC_LALT, KC_ESCAPE, TD(1), KC_LGUI, KC_LBRC},
        {KC_BSPC, KC_0, KC_9, KC_8, KC_7, KC_6},
        {KC_BSLS, KC_P, KC_O, KC_I, KC_U, KC_Y},
        {KC_QUOTE, KC_SCLN, KC_L, KC_K, KC_J, KC_H},
        {KC_ENTER, KC_SLASH, KC_DOT, KC_COMMA, KC_M, KC_N},
        {KC_NO, LCTL(KC_UP), KC_ESCAPE, TD(2), KC_SPACE, KC_RBRC},
    },
    [_LOWER] = {
        {KC_TRNS, KC_INSERT, KC_HOME, KC_PGUP, MC_1, MC_2},
        {KC_TRNS, KC_DELETE, KC_END, KC_PGDN, KC_NO, KC_NO},
        {KC_TRNS, KC_NO, KC_UP, KC_NO, KC_NO, KC_NO},
        {KC_TRNS, KC_LEFT, KC_DOWN, KC_RIGHT, KC_NO, KC_NO},
        {KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO},
        {KC_TRNS, KC_EQUAL, KC_MINUS, KC_PMNS, KC_KP_ASTERISK, KC_KP_SLASH},
        {KC_NO, KC_MINUS, KC_PPLS, KC_9, KC_8, KC_7},
        {KC_NO, KC_NO, KC_KP_DOT, KC_6, KC_5, KC_4},
        {KC_TRNS, KC_NO, KC_KP_EQUAL, KC_3, KC_2, KC_1},
        {KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_KP_0},
    },
    [_RAISE] = {
        {KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6},
        {KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO},
        {KC_TRNS, KC_NO, KC_UP, KC_NO, KC_NO, KC_NO},
        {KC_TRNS, KC_LEFT, KC_DOWN, KC_RIGHT, KC_NO, KC_NO},
        {KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO},
        {KC_TRNS, KC_F11, KC_F10, KC_F9, KC_F8, KC_F7},
        {KC_PGUP, KC_F12, KC_NO, KC_MNXT, KC_MPLY, KC_MPRV},
        {KC_PGDN, KC_NO, KC_NO, KC_VOLU, KC_VOLD, KC_MUTE},
        {KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO},
        {KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO},
    },
    [_ADJUST] = {
        {KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO},
        {KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO},
        {KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO},
        {KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO},
        {KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO},
        {KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO},
        {KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO},
        {KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO},
        {KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO},
        {KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO},
    },
};

#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _RAISE, _LOWER, _ADJUST);

    return state;
}

// Fuente proporcional 3–5 x 7: CONTROL y DEFAULT caben en los 32 px de ancho.
typedef struct {
    char letter;
    uint8_t width;
    uint8_t columns[5]; // El bit menos significativo es el píxel superior.
} status_glyph_t;

static const status_glyph_t status_font[] PROGMEM = {
    {' ', 2, {0}}, {'A', 4, {0x7e,0x09,0x09,0x7e}},
    {'C', 4, {0x3e,0x41,0x41,0x22}}, {'D', 4, {0x7f,0x41,0x41,0x3e}},
    {'E', 3, {0x7f,0x49,0x41}}, {'F', 3, {0x7f,0x09,0x01}},
    {'H', 4, {0x7f,0x08,0x08,0x7f}}, {'I', 3, {0x41,0x7f,0x41}},
    {'K', 4, {0x7f,0x08,0x14,0x63}}, {'L', 3, {0x7f,0x40,0x40}},
    {'M', 5, {0x7f,0x02,0x0c,0x02,0x7f}}, {'N', 4, {0x7f,0x04,0x18,0x7f}},
    {'O', 4, {0x3e,0x41,0x41,0x3e}}, {'P', 4, {0x7f,0x09,0x09,0x06}},
    {'R', 4, {0x7f,0x09,0x19,0x66}}, {'S', 4, {0x46,0x49,0x49,0x31}},
    {'T', 3, {0x01,0x7f,0x01}}, {'U', 4, {0x3f,0x40,0x40,0x3f}},
    {'W', 5, {0x3f,0x40,0x38,0x40,0x3f}}, {'Y', 5, {0x03,0x04,0x78,0x04,0x03}},
};

static const status_glyph_t *status_glyph(char letter) {
    for (uint8_t i = 0; i < ARRAY_SIZE(status_font); ++i) {
        if (pgm_read_byte(&status_font[i].letter) == letter) return &status_font[i];
    }
    return &status_font[0];
}

static void write_status_line(uint8_t y, const char *label, bool active) {
    uint8_t width = 0;
    for (const char *p = label; pgm_read_byte(p); ++p) {
        width += pgm_read_byte(&status_glyph(pgm_read_byte(p))->width) + 1;
    }
    uint8_t x = (33 - width) / 2; // width incluye el espacio final.
    for (uint8_t col = 0; col < 32; ++col) {
        for (uint8_t row = 0; row < 11; ++row) oled_write_pixel(col, y + row, active);
    }
    for (const char *p = label; pgm_read_byte(p); ++p) {
        const status_glyph_t *glyph = status_glyph(pgm_read_byte(p));
        for (uint8_t col = 0; col < pgm_read_byte(&glyph->width); ++col, ++x) {
            uint8_t bits = pgm_read_byte(&glyph->columns[col]);
            for (uint8_t row = 0; row < 7; ++row) {
                if (bits & (1 << row)) oled_write_pixel(x, y + row + 2, !active);
            }
        }
        ++x;
    }
}

static void render_mod_status(void) {
    static uint8_t previous_mods = 0xff;
    static uint8_t previous_profile = 0xff;
    static bool previous_caps;
    keyboard_profile_t profile = active_profile();
    uint8_t mods = get_mods() | get_weak_mods();
    bool caps = host_keyboard_led_state().caps_lock;
    bool first = previous_profile == 0xff;
    uint8_t changed = first ? 0xff : mods ^ previous_mods;
    if (profile != previous_profile) {
        const char *label = profile == PROFILE_MAC ? PSTR("MAC") :
                            profile == PROFILE_NON_MAC ? PSTR("NO MAC") : PSTR("DEFAULT");
        write_status_line(2, label, false);
    }
    if (changed & MOD_MASK_SHIFT) write_status_line(28, PSTR("SHIFT"), mods & MOD_MASK_SHIFT);
    if (changed & MOD_MASK_CTRL)  write_status_line(49, PSTR("CONTROL"), mods & MOD_MASK_CTRL);
    if (changed & MOD_MASK_ALT)   write_status_line(70, PSTR("ALT"), mods & MOD_MASK_ALT);
    if ((changed & MOD_MASK_GUI) || profile != previous_profile) {
        write_status_line(91, profile == PROFILE_NON_MAC ? PSTR("WKEY") : PSTR("CMD"), mods & MOD_MASK_GUI);
    }
    if (first || previous_caps != caps) write_status_line(112, PSTR("CAPS"), caps);
    previous_mods = mods;
    previous_caps = caps;
    previous_profile = profile;
}

static void draw_layer_box(uint8_t x, uint8_t y, uint8_t number, bool active) {
    static const uint8_t digits[4][7] = {
        {0b01110, 0b10001, 0b10011, 0b10101, 0b11001, 0b10001, 0b01110}, // 0
        {0b00100, 0b01100, 0b00100, 0b00100, 0b00100, 0b00100, 0b01110}, // 1
        {0b01110, 0b10001, 0b00001, 0b00010, 0b00100, 0b01000, 0b11111}, // 2
        {0b11110, 0b00001, 0b00001, 0b01110, 0b00001, 0b00001, 0b11110}  // 3
    };
    const uint8_t box_size = 30;
    const uint8_t scale    = 4;

    // OLED_ROTATION_270 changes the drawing area to 32x128.
    // The active layer is filled; inactive layers show only the outline.
    for (uint8_t py = 0; py < box_size; py++) {
        for (uint8_t px = 0; px < box_size; px++) {
            bool border = (px == 0 || px == box_size - 1 || py == 0 || py == box_size - 1);
            if (active || border) {
                oled_write_pixel(x + px, y + py, true);
            }
        }
    }

    // Enlarge the 5x7 digit to 20x28 pixels and center it in the box.
    for (uint8_t row = 0; row < 7; row++) {
        for (uint8_t col = 0; col < 5; col++) {
            if (digits[number][row] & (1 << (4 - col))) {
                for (uint8_t sy = 0; sy < scale; sy++) {
                    for (uint8_t sx = 0; sx < scale; sx++) {
                        oled_write_pixel(x + 5 + col * scale + sx, y + 1 + row * scale + sy, !active);
                    }
                }
            }
        }
    }
}

static void render_layer_status(void) {
    uint8_t        layer          = get_highest_layer(layer_state);
    static uint8_t previous_layer = 0xFF;

    // Redraw only when the active layer changes.
    if (layer == previous_layer) {
        return;
    }
    previous_layer = layer;

    oled_clear();
    draw_layer_box(1, 1, 0, layer == _QWERTY);
    draw_layer_box(1, 33, 1, layer == _LOWER);
    draw_layer_box(1, 65, 2, layer == _RAISE);
    draw_layer_box(1, 97, 3, layer == _ADJUST);
}

char keylog_str[24] = {};

char keylogs_str[21] = {};

int keylogs_str_idx = 0;

char wpm[4];

char layer_misc[7];

const char code_to_name[60] = {

    ' ', ' ', ' ',  ' ', 'a', 'b', 'c', 'd', 'e', 'f',

    'g', 'h', 'i',  'j', 'k', 'l', 'm', 'n', 'o', 'p',

    'q', 'r', 's',  't', 'u', 'v', 'w', 'x', 'y', 'z',

    '1', '2', '3',  '4', '5', '6', '7', '8', '9', '0',

    'R', 'E', 'B',  'T', '_', '-', '=', '[', ']', '\\',

    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
    char name = ' ';

    if (keycode < 60) {
        name = code_to_name[keycode];
    }

    // update keylog

    snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",

             record->event.key.row, record->event.key.col,

             keycode, name);

    // update keylogs

    if (keylogs_str_idx == sizeof(keylogs_str) - 1) {
        keylogs_str_idx = 0;

        for (int i = 0; i < sizeof(keylogs_str) - 1; i++) {
            keylogs_str[i] = ' ';
        }
    }

    keylogs_str[keylogs_str_idx] = name;

    keylogs_str_idx++;
}

const char *read_keylog(void) {
    return keylog_str;
}

const char *read_keylogs(void) {
    return keylogs_str;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        render_mod_status(); // mitad izquierda

    } else {
        render_layer_status(); // mitad derecha
    }

    return false;
}

#endif // OLED_ENABLE
