#pragma once

#include "os_detection.h"

typedef enum { PROFILE_DEFAULT, PROFILE_MAC, PROFILE_NON_MAC } keyboard_profile_t;
typedef enum { AUTO, FORCE_MAC, FORCE_NON_MAC, FORCE_DEFAULT } profile_mode_t;

static inline keyboard_profile_t select_profile(profile_mode_t mode, os_variant_t os) {
    switch (mode) {
        case FORCE_MAC:     return PROFILE_MAC;
        case FORCE_NON_MAC: return PROFILE_NON_MAC;
        case FORCE_DEFAULT: return PROFILE_DEFAULT;
        case AUTO:
            switch (os) {
                case OS_MACOS:
                case OS_IOS:     return PROFILE_MAC;
                case OS_WINDOWS:
                case OS_LINUX:   return PROFILE_NON_MAC;
                default:         return PROFILE_DEFAULT;
            }
    }
    return PROFILE_DEFAULT;
}

keyboard_profile_t active_profile(void);
