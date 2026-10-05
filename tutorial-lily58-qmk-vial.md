# Mini tutorial: Customize and build your Lily58 with Vial

This guide matches your Lily58 `rev1`, Vial firmware, 128×32 SSD1306 OLED, and four layers (`_QWERTY`, `_LOWER`, `_RAISE`, `_ADJUST`).

## 1. Find the files

Open the root folder of your Vial/QMK repository: it contains `Makefile` and `keyboards/`. For your `lily58/rev1:vial` build target, the keymap files are here:

```text
keyboards/lily58/rev1/keymaps/vial/
```

| File | What it controls | When to edit it |
|---|---|---|
| `keymap.c` | Key assignments for each layer and behavior written in C. In your setup, it also contains the OLED orientation and drawing code. | To change the layer display, add custom logic, or change the default keymap. |
| `config.h` | Compile-time options and limits: dynamic layers, EEPROM space for macros, Combo/Tap Dance/Key Override slots, Vial UID and unlock combo, split settings, and tapping timings. | To change firmware limits or parameters. |
| `rules.mk` | Enables or disables firmware features: Vial/VIA, OLED, Tap Dance, Combos, Key Overrides, and optimizations. | To include a feature or reduce firmware size. |

QMK combines the keyboard-level and keymap-level configuration. To customize only your keymap, edit the files under `keymaps/vial`; avoid changing the general files under `keyboards/lily58/rev1` unless you want the change to affect other keymaps too.

## 2. Choose between Vial and editing code

**You usually do not need to rebuild** to change layer key assignments in Vial, assign macros to keys, or configure the Tap Dance/Combo slots already included in the firmware. Vial saves those changes to the keyboard's dynamic memory.

**You do need to edit and rebuild** when you change the OLED code, add custom C behavior, enable a feature that was excluded, or increase limits such as the number of Tap Dance or Combo entries.

One detail about macros: `DYNAMIC_KEYMAP_MACRO_EEPROM_SIZE 256` reserves **256 bytes** of EEPROM for macro data; it does not mean 256 macros. Vial provides 16 macro slots by default. The number of slots and the available storage are separate limits, and EEPROM is shared with other dynamic features.

Your configuration has `VIAL_COMBO_ENTRIES 8`, but your `rules.mk` has `COMBO_ENABLE = no`. Combos are therefore disabled in the firmware even though slots are defined. To use Combos in Vial, set `COMBO_ENABLE = yes`, rebuild, and check that the firmware still fits in the microcontroller's memory.

## 3. Change the keymap or OLED

Edit `keyboards/lily58/rev1/keymaps/vial/keymap.c`. In your file:

- `enum layer_number` declares the layers.
- `keymaps[][MATRIX_ROWS][MATRIX_COLS]` contains the key assignments for each layer.
- `oled_init_user()` sets the display orientation.
- `render_mod_status()` draws the modifier status on the left half.
- `draw_layer_box()` and `render_layer_status()` draw the boxes and highlight the active layer on the right half.

If you use the keymap file I provided, place it in that folder as `keymap.c`, replacing the previous file. Changes written in C will not appear on the keyboard until you build and flash the new firmware.

## 4. Build the `.hex` file

From the root of the Vial/QMK repository, run:

```sh
make lily58/rev1:vial
```

This builds the `rev1` revision with the `vial` keymap. **It only builds the firmware; it does not flash the keyboard.**

After a successful build, QMK generates the firmware, usually named `lily58_rev1_vial.hex`. To locate it from the repository root, run:

```sh
find . -name 'lily58_rev1_vial.hex' -print
```

Use the generated `.hex` file to flash the microcontroller with your usual method. If the build fails, do not use an older `.hex` as if it contained your latest changes.

## 5. Keep the available space in mind

Your last reported firmware size was **27,526 of 28,672 bytes**, leaving **1,146 bytes** of flash. This measures the compiled firmware size; EEPROM used for dynamic layers and macros is a separate limit. Enabling features or increasing their slot counts may use more space and cause the build to fail.

## References

- [QMK structure and keymap files](https://docs.qmk.fm/getting_started_introduction)
- [QMK configuration: `config.h` and `rules.mk`](https://docs.qmk.fm/config_options)
- [QMK `make` commands](https://docs.qmk.fm/getting_started_make_guide.html)
- [Building Vial firmware and managing memory/features](https://get.vial.today/docs/firmware-size.html)
- [Macros in Vial](https://get.vial.today/manual/macros.html)
