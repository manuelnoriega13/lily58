// Keep the EEPROM signature of the preceding local build across recompiles.
// Re-evaluate this value when changing any on-device data layout.
#include "version.h"
#undef BUILD_ID
#define BUILD_ID 0xA2F2EFUL
