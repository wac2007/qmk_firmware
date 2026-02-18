# Keychron QMK Firmware

Personal fork of Keychron's QMK firmware for a **Keychron K3 Pro** (ANSI, RGB).

## Target Keyboard

All code changes target `keychron/k3_pro/ansi/rgb` unless editing a shared file (`quantum/`, `drivers/`, `keyboards/keychron/common/`, `keyboards/keychron/bluetooth/`) — in that case, ensure changes don't break other keyboards.

## Build Commands

```bash
# Build firmware (format: make keychron/<model>/<layout>/<variant>:<keymap>)
make keychron/k3_pro/ansi/rgb:default
make keychron/k3_pro/ansi/rgb:via

# Build + flash
make keychron/k3_pro/ansi/rgb:via:flash
```

## Flash / Reset

To enter bootloader: connect USB, toggle mode switch to "Off", hold Esc (or reset button under spacebar), then toggle switch to "Cable".

## Project Structure

```
keyboards/keychron/
├── bluetooth/          # Bluetooth stack (CKBT51 module)
├── common/             # Shared Keychron utilities (factory test, wireless, keychron_common)
├── k3_pro/             # Keyboard definition
│   ├── config.h        # Hardware pins, BT config, EEPROM settings
│   ├── rules.mk        # Build flags, source files, bluetooth.mk include
│   ├── k3_pro.c/h      # Board-level code
│   ├── matrix.c         # Key matrix scanning (SPI + 74HC595 shift register)
│   ├── ansi/rgb/        # ANSI layout, RGB variant
│   │   ├── keyboard.json  # QMK data-driven config (USB PID, RGB matrix driver/animations)
│   │   └── keymaps/
│   │       ├── default/keymap.c
│   │       └── via/keymap.c   # VIA-compatible keymap (4 layers)
│   └── via_json/        # VIA app JSON definitions
quantum/                 # QMK core (modified: rgb_matrix, led_matrix, action, dynamic_keymap)
drivers/                 # Hardware drivers (LED, backlight, sensors, etc.)
```

## Code Style

- C firmware — uses `.clang-format` (Google-based, 4-space indent, no tabs, column limit 1000)
- Format with: `clang-format -i <file>`
- Keymaps use `// clang-format off` to preserve alignment

## Keymap Layers (8 total)

| Idx | Name     | Type      | Activation                                   |
|-----|----------|-----------|----------------------------------------------|
| 0   | MAC_BASE | Base      | DIP switch                                   |
| 1   | MAC_FN   | Momentary | MO(1) key                                    |
| 2   | WIN_BASE | Base      | DIP switch                                   |
| 3   | WIN_FN   | Momentary | MO(3) key                                    |
| 4   | GAMING   | Toggle    | Combo: tap E+L                               |
| 5   | NUMBERS  | Momentary | Combo: hold Z+X (left bottom row)            |
| 6   | SYMBOLS  | Momentary | Combo: hold D+F (left middle + index)        |
| 7   | NAV      | Momentary | Combo: hold S+D (left ring + middle)         |

- RGB keycodes: `UG_xxxx` (not the deprecated `RGB_xxx`)
- Bluetooth host switching: `BT_HST1`, `BT_HST2`, `BT_HST3`
- Battery level check: `BAT_LVL`

## Combos

Combos are global — they work from any layer. Defined in `keymaps/via/keymap.c`.

| Combo keys | Physical position       | Action       |
|------------|-------------------------|--------------|
| S + D      | Left ring + middle      | MO(NAV)      |
| D + F      | Left middle + index     | MO(SYMBOLS)  |
| Z + X      | Left bottom row         | MO(NUMBERS)  |
| E + L      | Cross-hand              | TG(GAMING)   |

Timing: `COMBO_TERM 50` ms (in `keymaps/via/config.h`).

## Tarmak Status

Currently at **Tarmak stage 1** (E-J-K-N cycle). Remapping happens at OS level. The firmware base layer is still QWERTY, so combo keycodes reference QWERTY positions. When/if Tarmak is implemented at the firmware level, combo keycodes in `keymap.c` will need updating.

## VIA

All 8 layers are remappable via [usevia.com](https://usevia.com). Layer count is set by `DYNAMIC_KEYMAP_LAYER_COUNT=8` in `keymaps/via/rules.mk`. After flashing, do an EEPROM reset (hold Esc while plugging in) so VIA picks up the new layout. Combos are firmware-only and not visible in VIA.

## Gotchas

- `*.bin` files are gitignored — don't commit compiled firmware
- VIA JSON files in `via_json/` directories are tracked; root-level `via*.json` are gitignored
- The shift register is driven via SPI (`DRIVE_SHRIFT_REGISTER_WITH_SPI` — the typo is intentional/upstream)
- Branch `wls_2025q1` is the working branch; `master` tracks upstream Keychron
- This repo has massive diffs from master due to Keychron fork divergence — don't be alarmed by large file counts
