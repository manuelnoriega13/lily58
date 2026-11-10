#include QMK_KEYBOARD_H
#include "dynamic_keymap.h"
#include "send_string.h"
#include "vial.h"

// Vial reset routines renamed only in their own translation unit (rules.mk).
void vial_stock_keymap_reset(void);
void vial_stock_macro_reset(void);

static const vial_tap_dance_entry_t PROGMEM dances[] = {
    {KC_NO, KC_LSFT, MC_0, KC_NO, 200},
    {KC_NO, MO(1), TG(1), KC_NO, 250},
    {KC_NO, MO(2), TG(2), KC_NO, 250},
    {KC_NO, KC_NO, KC_NO, KC_NO, 100},
};

static const vial_key_override_entry_t PROGMEM overrides[] = {
    {KC_BSPC, KC_DELETE, 32783, 2, 0, 0, 135},
    {KC_GRAVE, KC_F12, 15, 4, 0, 0, 135},
    {KC_1, KC_F1, 65535, 1, 0, 0, 135},
    {KC_2, KC_F2, 65535, 0, 0, 1, 7},
    {KC_3, KC_F3, 65535, 0, 0, 1, 7},
    {KC_4, KC_F4, 65535, 0, 0, 1, 7},
    {KC_5, KC_F5, 65535, 0, 0, 1, 7},
    {KC_6, KC_F6, 65535, 0, 0, 1, 7},
    {KC_7, KC_F7, 65535, 0, 0, 1, 7},
    {KC_8, KC_F8, 65535, 0, 0, 1, 7},
    {KC_9, KC_F9, 65535, 0, 0, 1, 7},
    {KC_0, KC_F10, 65535, 0, 0, 1, 7},
    {KC_Q, KC_F11, 65535, 0, 0, 0, 7},
    {KC_P, KC_F12, 65535, 0, 0, 1, 7},
    {KC_NO, KC_NO, 65535, 0, 0, 0, 7},
    {KC_NO, KC_NO, 65535, 0, 0, 0, 7},
};

void dynamic_keymap_reset(void) {
    vial_stock_keymap_reset();
    for (uint8_t i = 0; i < ARRAY_SIZE(dances); ++i) {
        vial_tap_dance_entry_t entry;
        memcpy_P(&entry, &dances[i], sizeof(entry));
        dynamic_keymap_set_tap_dance(i, &entry);
    }
    for (uint8_t i = 0; i < ARRAY_SIZE(overrides); ++i) {
        vial_key_override_entry_t entry;
        memcpy_P(&entry, &overrides[i], sizeof(entry));
        dynamic_keymap_set_key_override(i, &entry);
    }
    vial_init(); // Actualiza también la caché RAM cuando se restaura desde Vial.
}

#define MACRO_DOWN(kc) SS_QMK_PREFIX, SS_DOWN_CODE, kc
#define MACRO_UP(kc)   SS_QMK_PREFIX, SS_UP_CODE, kc
#define SCREENSHOT(kc) MACRO_DOWN(KC_LGUI), MACRO_DOWN(KC_LSFT), MACRO_DOWN(kc), MACRO_UP(KC_LGUI), MACRO_UP(KC_LSFT), MACRO_UP(kc)
static const uint8_t PROGMEM macros[] = {
    MACRO_DOWN(KC_CAPS), SS_QMK_PREFIX, SS_DELAY_CODE, 101, 1, MACRO_UP(KC_CAPS), 0,
    SCREENSHOT(KC_3), 0,
    SCREENSHOT(KC_4), 0,
};

void dynamic_keymap_macro_reset(void) {
    vial_stock_macro_reset();
    uint8_t data[sizeof(macros)];
    memcpy_P(data, macros, sizeof(data));
    dynamic_keymap_macro_set_buffer(0, sizeof(data), data);
}
