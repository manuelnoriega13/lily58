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

enum layer_number {

    _QWERTY = 0,

    _LOWER,

    _RAISE,

    _ADJUST

};

#define RAISE MO(_RAISE)

#define LOWER MO(_LOWER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* QWERTY

     * ,-----------------------------------------.                    ,-----------------------------------------.

     * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  \~   |

     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|

     * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  -   |

     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|

     * |LCTRL |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |

     * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|

     * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|

     * `-----------------------------------------/       /     \      \\-----------------------------------------'

     *                   |LOWER | LGUI | Alt  | /Space  /       \Enter \  |BackSP| RGUI |RAISE |

     *                   |      |      |      |/       /         \      \ |      |      |      |

     *                   `-------------------''-------'           '------''--------------------'

     */

    [_QWERTY] = LAYOUT(

        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_GRV,

        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_MINS,

        KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,

        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_LBRC, KC_RBRC, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,

        LOWER, KC_LGUI, KC_LALT, KC_SPC, KC_ENT, KC_BSPC, KC_RGUI, RAISE

        ),

    /* LOWER

     * ,-----------------------------------------.                    ,-----------------------------------------.

     * |      |      |      |      |      |      |                    |      |      |      |      |      |      |

     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|

     * |      |   !  |   @  |   #  |   $  |   %  |                    |   ^  |   &  |   *  |   (  |   )  |      |

     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|

     * |      |   1  |   2  |   3  |   4  |   5  |-------.    ,-------|   6  |   7  |   8  |   9  |   0  |      |

     * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|

     * |      |      |      |      |      |      |-------|    |-------|   |  |   `  |   +  |   {  |   }  |      |

     * `-----------------------------------------/       /     \      \\-----------------------------------------'

     *                   |LOWER | LGUI | Alt  | /Space  /       \Enter \  |BackSP| RGUI |RAISE |

     *                   |      |      |      |/       /         \      \ |      |      |      |

     *                   `-------------------''-------'           '------''--------------------'

     */

    [_LOWER] = LAYOUT(

        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,

        _______, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,

        _______, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, _______,

        _______, _______, _______, _______, _______, _______, _______, _______, KC_PIPE, KC_GRAVE, KC_PLUS, KC_LCBR, KC_RCBR, _______,

        _______, _______, _______, _______, _______, _______, _______, _______

        ),

    /* RAISE

     * ,-----------------------------------------.                    ,-----------------------------------------.

     * |      |      |      |      |      |      |                    |      |      |      |      |      |      |

     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|

     * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |  F8  |  F9  | F10  | F11  | F12  |

     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|

     * |      |      |      |      |      |      |-------.    ,-------|      | Left | Down |  Up  |Right |      |

     * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|

     * |      |      |      |      |      |      |-------|    |-------|   +  |   =  |   [  |   ]  |   \  |      |

     * `-----------------------------------------/       /     \      \\-----------------------------------------'

     *                   |LOWER | LGUI | Alt  | /Space  /       \Enter \  |BackSP| RGUI |RAISE |

     *                   |      |      |      |/       /         \      \ |      |      |      |

     *                   `-------------------''-------'           '------''--------------------'

     */

    [_RAISE] = LAYOUT(

        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,

        KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,

        _______, _______, _______, _______, _______, _______, XXXXXXX, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, XXXXXXX,

        _______, _______, _______, _______, _______, _______, _______, _______, KC_PLUS, KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS, _______,

        _______, _______, _______, _______, _______, _______, _______, _______

        ),

    /* ADJUST

     * ,-----------------------------------------.                    ,-----------------------------------------.

     * |      |      |      |      |      |      |                    |      |      |      |      |      |      |

     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|

     * |      |      |      |      |      |      |                    |      |      |      |      |      |      |

     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|

     * |      |      |      |      |      |      |-------.    ,-------|      |      |      |      |      |      |

     * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|

     * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |

     * `-----------------------------------------/       /     \      \\-----------------------------------------'

     *                   |LOWER | LGUI | Alt  | /Space  /       \Enter \  |BackSP| RGUI |RAISE |

     *                   |      |      |      |/       /         \      \ |      |      |      |

     *                   `----------------------------'           '------''--------------------'

     */

    [_ADJUST] = LAYOUT(

        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,

        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,

        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,

        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,

        _______, _______, _______, _______, _______, _______, _______, _______)

};

#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _RAISE, _LOWER, _ADJUST);

    return state;
}

enum modifier_glyph_index { GLYPH_A, GLYPH_C, GLYPH_D, GLYPH_F, GLYPH_H, GLYPH_I, GLYPH_L, GLYPH_M, GLYPH_P, GLYPH_R, GLYPH_S, GLYPH_T };

// 3x5 uppercase glyphs, packed as five 3-bit rows.
static const uint16_t modifier_font[] PROGMEM = {
    (2 << 12) | (5 << 9) | (7 << 6) | (5 << 3) | 5, // A
    (3 << 12) | (4 << 9) | (4 << 6) | (4 << 3) | 3, // C
    (6 << 12) | (5 << 9) | (5 << 6) | (5 << 3) | 6, // D
    (7 << 12) | (4 << 9) | (6 << 6) | (4 << 3) | 4, // F
    (5 << 12) | (5 << 9) | (7 << 6) | (5 << 3) | 5, // H
    (7 << 12) | (2 << 9) | (2 << 6) | (2 << 3) | 7, // I
    (4 << 12) | (4 << 9) | (4 << 6) | (4 << 3) | 7, // L
    (5 << 12) | (7 << 9) | (7 << 6) | (5 << 3) | 5, // M
    (6 << 12) | (5 << 9) | (6 << 6) | (4 << 3) | 4, // P
    (6 << 12) | (5 << 9) | (6 << 6) | (5 << 3) | 5, // R
    (3 << 12) | (4 << 9) | (2 << 6) | (1 << 3) | 6, // S
    (7 << 12) | (2 << 9) | (2 << 6) | (2 << 3) | 2  // T
};

static const uint8_t label_shift[] PROGMEM = {GLYPH_S, GLYPH_H, GLYPH_I, GLYPH_F, GLYPH_T};
static const uint8_t label_ctrl[] PROGMEM  = {GLYPH_C, GLYPH_T, GLYPH_R, GLYPH_L};
static const uint8_t label_alt[] PROGMEM   = {GLYPH_A, GLYPH_L, GLYPH_T};
static const uint8_t label_cmd[] PROGMEM   = {GLYPH_C, GLYPH_M, GLYPH_D};
static const uint8_t label_caps[] PROGMEM  = {GLYPH_C, GLYPH_A, GLYPH_P, GLYPH_S};

static void draw_modifier_indicator(uint8_t y, const uint8_t *label, uint8_t length, bool active) {
    const uint8_t x             = 0;
    const uint8_t width         = 32;
    const uint8_t height        = 22;
    const uint8_t scale         = 2;
    const uint8_t char_width    = 3;
    const uint8_t text_width    = length * char_width * scale;
    const uint8_t content_width = width - 2;
    const uint8_t text_x        = x + 1 + (content_width - text_width) / 2;
    const uint8_t text_y        = y + (height - 5 * scale) / 2;

    // Active modifiers get a filled box; inactive ones keep an outline.
    for (uint8_t py = 0; py < height; py++) {
        for (uint8_t px = 0; px < width; px++) {
            bool border = px == 0 || px == width - 1 || py == 0 || py == height - 1;
            if (active || border) {
                oled_write_pixel(x + px, y + py, true);
            }
        }
    }

    // Draw the label at 2x scale, inverting it inside an active box.
    for (uint8_t index = 0; index < length; index++) {
        uint8_t  glyph_index = pgm_read_byte(&label[index]);
        uint16_t glyph       = pgm_read_word(&modifier_font[glyph_index]);
        for (uint8_t row = 0; row < 5; row++) {
            uint8_t pixels = (glyph >> ((4 - row) * 3)) & 0b111;
            for (uint8_t col = 0; col < char_width; col++) {
                if (pixels & (1 << (2 - col))) {
                    for (uint8_t sy = 0; sy < scale; sy++) {
                        for (uint8_t sx = 0; sx < scale; sx++) {
                            oled_write_pixel(text_x + index * char_width * scale + col * scale + sx, text_y + row * scale + sy, !active);
                        }
                    }
                }
            }
        }
    }
}

static void render_mod_status(void) {
    uint8_t mods   = get_mods();
    led_t   leds   = host_keyboard_led_state();
    uint8_t status = 0;

    if (mods & MOD_MASK_SHIFT) status |= 1 << 0;
    if (mods & MOD_MASK_CTRL) status |= 1 << 1;
    if (mods & MOD_MASK_ALT) status |= 1 << 2;
    if (mods & MOD_MASK_GUI) status |= 1 << 3;
    if (leds.caps_lock) status |= 1 << 4;

    static uint8_t previous_status = 0xFF;
    if (status == previous_status) {
        return;
    }
    previous_status = status;

    oled_clear();
    draw_modifier_indicator(3, label_shift, sizeof(label_shift), status & (1 << 0));
    draw_modifier_indicator(28, label_ctrl, sizeof(label_ctrl), status & (1 << 1));
    draw_modifier_indicator(53, label_alt, sizeof(label_alt), status & (1 << 2));
    draw_modifier_indicator(78, label_cmd, sizeof(label_cmd), status & (1 << 3));
    draw_modifier_indicator(103, label_caps, sizeof(label_caps), status & (1 << 4));
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
