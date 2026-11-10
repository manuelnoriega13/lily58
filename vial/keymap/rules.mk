# Compatibilidad con VIA y Vial
VIA_ENABLE = yes
VIAL_ENABLE = yes

# Funciones que quieres conservar
OLED_ENABLE = yes
TAP_DANCE_ENABLE = yes
EXTRAKEY_ENABLE = yes
KEY_OVERRIDE_ENABLE = yes
VIAL_KEY_OVERRIDE_ENABLE = yes

# Funciones que no usas: desactivarlas puede ahorrar memoria
MOUSEKEY_ENABLE = no
WPM_ENABLE = no
COMBO_ENABLE = no
SPACE_CADET_ENABLE = no
REPEAT_KEY_ENABLE = no
LAYER_LOCK_ENABLE = no
CAPS_WORD_ENABLE = no
GRAVE_ESC_ENABLE = no
MAGIC_ENABLE = no
BOOTMAGIC_ENABLE = no
COMMAND_ENABLE = no
CONSOLE_ENABLE = no
QMK_SETTINGS = no

# El teclado no tiene iluminación RGB
RGBLIGHT_ENABLE = no
RGB_MATRIX_ENABLE = no

# Optimización del enlazado
LTO_ENABLE = yes

OS_DETECTION_ENABLE = yes
SRC += profiles.c vial_defaults.c

# Extend the two actual reset entry points without changing the Vial checkout.
$(INTERMEDIATE_OUTPUT)/quantum/dynamic_keymap.o: FILE_SPECIFIC_CFLAGS += -Ddynamic_keymap_reset=vial_stock_keymap_reset -Ddynamic_keymap_macro_reset=vial_stock_macro_reset
$(INTERMEDIATE_OUTPUT)/quantum/via.o: FILE_SPECIFIC_CFLAGS += -include $(KEYMAP_PATH)/eeprom_version.h

# Resolve the symlink from vial-qmk back to this Git repository.
LILY58_ARCHIVE_DIR := $(realpath $(dir $(lastword $(MAKEFILE_LIST))))/../firmware
.PHONY: archive_lily58
all: archive_lily58
archive_lily58: check-size
	@mkdir -p "$(LILY58_ARCHIVE_DIR)"
	@dest="$(LILY58_ARCHIVE_DIR)/$(TARGET)-$$(date '+%Y-%m-%d_%H-%M-%S').hex"; \
	cp "$(BUILD_DIR)/$(TARGET).hex" "$$dest" && printf 'Firmware archivado en %s\n' "$$dest"
