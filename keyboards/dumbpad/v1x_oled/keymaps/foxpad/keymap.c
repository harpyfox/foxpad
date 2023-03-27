// Copyright 2020 imchipwood
#include QMK_KEYBOARD_H

enum keycodes {
    ALT_TAB = SAFE_RANGE,
    KC_FOX,
};

enum unicode {
    FOX,
    SNEK
};

const uint32_t unicode_map[] PROGMEM = {
    [FOX] = 0x1F98A, // 🦊
    [SNEK]  = 0x1F40D, // 🐍
};

enum layers { // another enum array for LOGO images that show layers?
    DEFAULT,
    CODE,
    BLENDER,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
        /*
            DEFAULT LAYER
    /-----------------------------------------------------`
    |             |    7    |    8    |    9    |  Bkspc  |
    |             |---------|---------|---------|---------|
    |             |    4    |    5    |    6    |   Esc   |
    |             |---------|---------|---------|---------|
    |             |    1    |    2    |    3    |   Tab   |
    |-------------|---------|---------|---------|---------|
    | Play Pause  |  TT(1)  |    0    |    .    |  Enter  |
    \-----------------------------------------------------'
    */
    [DEFAULT] = LAYOUT(
                    KC_FOX,      KC_FOX,    KC_FOX,      KC_FOX,
                    KC_FOX,      KC_FOX,    KC_FOX,      KC_FOX,
                    KC_FOX,      KC_FOX,    KC_FOX,      KC_FOX,
        KC_FOX,     KC_FOX,      KC_FOX,    KC_FOX,      KC_FOX
    ),
    /*
            SUB LAYER
    /-----------------------------------------------------`
    |             |         |         |         |  Reset  |
    |             |---------|---------|---------|---------|
    |             |         |         |         |    +    |
    |             |---------|---------|---------|---------|
    |             |         |         |         |    -    |
    |-------------|---------|---------|---------|---------|
    |    LOCK     |         |         |         |    =    |
    \-----------------------------------------------------'
    */
    [CODE] = LAYOUT(
                    _______,     _______,     _______,      QK_BOOT,
                    _______,     _______,     _______,      KC_KP_PLUS,
                    _______,     _______,     _______,      KC_KP_MINUS,
        QK_LOCK,    _______,     _______,     _______,      KC_EQL
    ),

    [BLENDER] = LAYOUT(
                    _______,     _______,     _______,      _______,
                    _______,     _______,     _______,      _______,
                    _______,     _______,     _______,      _______,
        _______,    _______,     _______,     _______,      _______
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    switch (keycode) {
        case (KC_FOX):
            if ( record -> event.pressed ) {
                send_string("fox");
            }
            return false;
        default:
            return true;
    }

};
