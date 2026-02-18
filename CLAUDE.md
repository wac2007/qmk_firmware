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

## Keymap Layers

Standard 4-layer structure: `MAC_BASE`, `MAC_FN`, `WIN_BASE`, `WIN_FN`
- RGB keycodes: `UG_xxxx` (not the deprecated `RGB_xxx`)
- Bluetooth host switching: `BT_HST1`, `BT_HST2`, `BT_HST3`
- Battery level check: `BAT_LVL`

## Gotchas

- `*.bin` files are gitignored — don't commit compiled firmware
- VIA JSON files in `via_json/` directories are tracked; root-level `via*.json` are gitignored
- The shift register is driven via SPI (`DRIVE_SHRIFT_REGISTER_WITH_SPI` — the typo is intentional/upstream)
- Branch `wls_2025q1` is the working branch; `master` tracks upstream Keychron
- This repo has massive diffs from master due to Keychron fork divergence — don't be alarmed by large file counts
