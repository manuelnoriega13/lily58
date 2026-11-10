#include QMK_KEYBOARD_H
#include "profiles.h"

static profile_mode_t mode = AUTO;
static os_variant_t host = OS_UNSURE;
static keyboard_profile_t active = PROFILE_DEFAULT;

keyboard_profile_t active_profile(void) {
    return active;
}

bool process_detected_host_os_user(os_variant_t os) {
    host = os;
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode < QK_KB_0 || keycode > QK_KB_3) return true;
    if (record->event.pressed) mode = (profile_mode_t)(keycode - QK_KB_0);
    return false;
}

void housekeeping_task_user(void) {
    if (!is_keyboard_master()) return;
    keyboard_profile_t next = select_profile(mode, host);
    if (next == active || get_mods() || get_weak_mods()) return;
    // Key-down and key-up must see the same mapping, including pending holds.
    for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
        if (matrix_get_row(row)) return;
    }
    keymap_config.swap_lctl_lgui = keymap_config.swap_rctl_rgui = next == PROFILE_NON_MAC;
    active = next;
}
