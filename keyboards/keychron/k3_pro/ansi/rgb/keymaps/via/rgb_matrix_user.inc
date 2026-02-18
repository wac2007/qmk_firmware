// Copyright 2025 Wallace Coelho
// SPDX-License-Identifier: GPL-2.0-or-later

// Custom RGB Matrix effect: static finger-column colouring.
// Cycle to it with UG_NEXT just like any built-in animation.

RGB_MATRIX_EFFECT(FINGER_COLUMNS)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

// clang-format off

enum finger {
    F_LP, // Left Pinky
    F_LR, // Left Ring
    F_LM, // Left Middle
    F_LI, // Left Index
    F_TH, // Thumb
    F_RI, // Right Index
    F_RM, // Right Middle
    F_RR, // Right Ring
    F_RP  // Right Pinky
};

/* Map every LED index (0-83) to the finger that types it.
 *
 * Row 0 (func) : Esc  BrD  BrU  MCt  LPd  VlD | VlU  Prv  Ply  Nxt  Mut  VDn  VUp  Snp  Del  UG
 * Row 1 (num)  :  `    1    2    3    4    5   |  6    7    8    9    0    -    =   BS       PgU
 * Row 2 (top)  : Tab   Q    W    E    R    T   |  Y    U    I    O    P    [    ]    \       PgD
 * Row 3 (home) : Cap   A    S    D    F    G   |  H    J    K    L    ;    '        Ent      Hom
 * Row 4 (bot)  : LSft       Z    X    C    V    B   N    M    ,    .    /       RSft  Up   End
 * Row 5 (mod)  : LCt  LOp  LCm                Spc                RCm   Fn  RCt   <-   v    ->
 */
static const uint8_t PROGMEM finger_map[84] = {
    /* Row 0 - 16 LEDs */  F_LP, F_LP, F_LR, F_LM, F_LI, F_LI, F_RI, F_RI, F_RM, F_RR, F_RP, F_RP, F_RP, F_RP, F_RP, F_RP,
    /* Row 1 - 15 LEDs */  F_LP, F_LP, F_LR, F_LM, F_LI, F_LI, F_RI, F_RI, F_RM, F_RR, F_RP, F_RP, F_RP, F_RP, F_RP,
    /* Row 2 - 15 LEDs */  F_LP, F_LP, F_LR, F_LM, F_LI, F_LI, F_RI, F_RI, F_RM, F_RR, F_RP, F_RP, F_RP, F_RP, F_RP,
    /* Row 3 - 14 LEDs */  F_LP, F_LP, F_LR, F_LM, F_LI, F_LI, F_RI, F_RI, F_RM, F_RR, F_RP, F_RP, F_RP, F_RP,
    /* Row 4 - 14 LEDs */  F_LP, F_LP, F_LR, F_LM, F_LI, F_LI, F_RI, F_RI, F_RM, F_RR, F_RP, F_RP, F_RP, F_RP,
    /* Row 5 - 10 LEDs */  F_LP, F_LP, F_TH, F_TH, F_TH, F_RP, F_RP, F_RP, F_RP, F_RP
};

/* Base RGB colour per finger (at full brightness).
 * Symmetric: pink - yellow - green - blue | white | red - green - yellow - pink */
static const uint8_t PROGMEM finger_colors[][3] = {
    [F_LP] = {180,  40, 120},  /* Pink         */
    [F_LR] = {180, 180,  10},  /* Yellow       */
    [F_LM] = { 10, 180,  10},  /* Green        */
    [F_LI] = { 40,  70, 180},  /* Blue         */
    [F_TH] = {160, 160, 160},  /* White        */
    [F_RI] = {180,  40,  40},  /* Red          */
    [F_RM] = { 10, 180,  10},  /* Green        */
    [F_RR] = {180, 180,  10},  /* Yellow       */
    [F_RP] = {180,  40, 120},  /* Pink         */
};

// clang-format on

static bool FINGER_COLUMNS(effect_params_t *params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    uint8_t val = rgb_matrix_config.hsv.v; // respect global brightness

    for (uint8_t i = led_min; i < led_max; i++) {
        uint8_t f = pgm_read_byte(&finger_map[i]);
        uint8_t r = pgm_read_byte(&finger_colors[f][0]);
        uint8_t g = pgm_read_byte(&finger_colors[f][1]);
        uint8_t b = pgm_read_byte(&finger_colors[f][2]);

        // Scale by global brightness
        r = (uint16_t)r * val / 255;
        g = (uint16_t)g * val / 255;
        b = (uint16_t)b * val / 255;

        rgb_matrix_set_color(i, r, g, b);
    }

    return rgb_matrix_check_finished_leds(led_max);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
