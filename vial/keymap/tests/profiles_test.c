#include <assert.h>
#include "profiles.h"

int main(void) {
    const os_variant_t systems[] = {OS_UNSURE, OS_MACOS, OS_IOS, OS_WINDOWS, OS_LINUX, (os_variant_t)99};
    const keyboard_profile_t automatic[] = {PROFILE_DEFAULT, PROFILE_MAC, PROFILE_MAC, PROFILE_NON_MAC, PROFILE_NON_MAC, PROFILE_DEFAULT};
    for (unsigned i = 0; i < sizeof(systems) / sizeof(*systems); ++i) {
        assert(select_profile(AUTO, systems[i]) == automatic[i]);
        assert(select_profile(FORCE_DEFAULT, systems[i]) == PROFILE_DEFAULT);
        assert(select_profile(FORCE_MAC, systems[i]) == PROFILE_MAC);
        assert(select_profile(FORCE_NON_MAC, systems[i]) == PROFILE_NON_MAC);
    }
}
