// Copyright 2020 imchipwood
#include QMK_KEYBOARD_H
#include "anim.c"
typedef struct {
    int len;
    char (*data)[512];
} Image;



void next_layer(void);
Image get_layer_img(uint8_t);
bool get_keycode_img(uint16_t);
void render_img(Image);


//
// Keycodes
//
enum keycodes {
    ENC_LEFT = SAFE_RANGE,
    ENC_RIGHT,
    KC_FOX,
    LYR_NXT,
    CS_SUMMARY,
    CMTCPY,
};

//
// Layers
//
enum layers {
    DEFAULT,
    CODE,
    BLENDER,
    END,
};

//
// Keymaps
//
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    
    /*--------------------------------------\
    (   FOX    )        [                  ]|
    |---------------------------------------|
    |    7    |    8    |    9    |    =    |
    |---------|---------|---------|---------|
    |    4    |    5    |    6    |    +    |
    |---------|---------|---------|---------|
    |    1    |    2    |    3    |    -    |
    |---------|---------|---------|---------|
    |    0    |    0    |    .    |  Enter  |
    \--------------------------------------*/
    [DEFAULT] = LAYOUT(
        KC_FOX,
        KC_P7,       KC_P8,     KC_P9,      LYR_NXT,
        KC_P4,       KC_P5,     KC_P6,      KC_KP_PLUS,
        KC_P1,       KC_P2,     KC_P3,      KC_KP_MINUS,
        KC_P0,       KC_P0,     KC_PDOT,    KC_KP_ENTER
    ),

    /*--------------------------------------\
    (   FOX    )        [                  ]|
    |---------------------------------------|
    |    7    |    8    |    9    |    =    |
    |---------|---------|---------|---------|
    |    4    |    5    |    6    |    +    |
    |---------|---------|---------|---------|
    |    1    |    2    |    3    |    -    |
    |---------|---------|---------|---------|
    |    0    |    0    |    .    |  Enter  |
    \--------------------------------------*/
    [CODE] = LAYOUT(
        KC_FOX,
        LCTL(LGUI(KC_LEFT)),   LCTL(LGUI(KC_RIGHT)),      KC_NO,       LYR_NXT,
        LSFT(KC_SPACE),         KC_NO,      KC_NO,       LCTL(KC_K),
        LCTL(KC_SLASH),      CMTCPY,      CS_SUMMARY,    KC_F12,
        KC_NO,        KC_NO,      KC_NO,       LCTL(LSFT(KC_S))
    ),

    [BLENDER] = LAYOUT(
        KC_FOX,
        KC_B,        KC_B,      KC_B,       LYR_NXT,
        KC_B,        KC_B,      KC_B,       KC_B,
        KC_B,        KC_B,      KC_B,       KC_B,
        KC_B,        KC_B,      KC_B,       KC_B
    )
};

//
// Process keycodes and any extra stuff
//
bool kc_img_active = false;
uint16_t kc_img_timer = 0;

uint16_t last_keycode = 0;
#define KEYCODE_IMAGE_TIMEOUT 2000

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record -> event.pressed) {
        kc_img_active = true;
        last_keycode = keycode;
        kc_img_timer = timer_read();
    }

    switch (keycode) {
        case KC_FOX:
            if ( record -> event.pressed ) {
                send_string("fox");
            }
            return false;
        case LYR_NXT:
            if (record -> event.pressed) {
                next_layer();
            }
            return false;
        case CS_SUMMARY:
            if (record -> event.pressed) {
                SEND_STRING("/// <summary>"SS_TAP(X_ENTER));
                SEND_STRING("/// "SS_TAP(X_ENTER));
                SEND_STRING("/// </summary>"SS_TAP(X_UP));
            }
            return false;
        case CMTCPY:
            if (record -> event.pressed) {
                register_code(KC_LCTL);
                tap_code(KC_C);
                tap_code(KC_SLASH);
                unregister_code(KC_LCTL);
                tap_code(KC_RIGHT);
                tap_code(KC_ENTER);
                register_code(KC_LCTL);
                tap_code(KC_V);
                unregister_code(KC_LCTL);
            }
            return false;
        default:
            return true;
    }

};

//
// LYR_NXT keycode functionality
//
uint8_t current_layer = DEFAULT;
void next_layer() {
    uint8_t next = current_layer + 1;

    if (next >= END) {
        next = DEFAULT;
    }

    layer_on(next);
    layer_off(current_layer);
    current_layer = next;
};

//
// Encoder task switcher
//
bool task_switch_active = false;
uint16_t task_switch_timer = 0;
#define TASK_SWITCH_TIMEOUT 1000

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (!task_switch_active) {
        task_switch_active = true;
        register_code(KC_LALT);
    }

    task_switch_timer = timer_read();

    if (clockwise) {
        tap_code(KC_TAB);
    } else {
        tap_code16(LSFT(KC_TAB));
    }

    // Keycode image update
    kc_img_active = true;
    last_keycode = clockwise ? ENC_RIGHT : ENC_LEFT;
    kc_img_timer = timer_read();

    return true;
};


//
// Animation parameters
//
#define ANIM_FRAME_LENGTH 167 // frame length in ms. 167 is 6FPS. Well a tiny tiny tiny tiny tiny bit slower than 6FPS. TINY
uint16_t anim_timer = 0;
uint8_t anim_current_frame = 1;
uint8_t anim_total_frame = 0;


//
// Layer images 
//
Image get_layer_img(uint8_t layer) {
    Image img;

    switch (layer) {
        case DEFAULT:
            img.len = len_numpad;
            img.data = img_numpad;
            break;
        case CODE:
            img.len = len_unity;
            img.data = img_unity;
            img.len = len_irochat;
            img.data = img_irochat;
            break;
        case BLENDER:
            img.len = len_blender;
            img.data = img_blender;
            break;
        default:
            img.len = len_clear;
            img.data = img_clear;
            break;
    }

    return img;
};

//
// Keycode images
// TODO: To be replaced with actual images like get_layer_img.fugggggg
//
bool get_keycode_img(uint16_t keycode) {
    oled_set_cursor(5,3);
    switch(keycode) {
        case KC_P1 ... KC_P0: // this was for debug and doesnt work. when i press 9 it prints 0. cool
            oled_write_char( (char)((keycode - 88) + 48), false);
            return true;
        case ENC_LEFT:
            oled_write(PSTR(" < TASK   "), false);
            return true;
        case ENC_RIGHT:
            oled_write(PSTR("   TASK > "), false);
            return true;
        case KC_FOX:
            oled_write(PSTR("FOXXXXXXXX"), false);
            return true;              
        case CS_SUMMARY:
            oled_write(PSTR("///SUMMARY"), false);
            return true;        
        case CMTCPY:
            oled_write(PSTR("CMNT->COPY"), false);
            return true;
        case LCTL(LGUI(KC_LEFT)):
            oled_write(PSTR(" < DKTP   "), false);
            return true;
        case LCTL(LGUI(KC_RIGHT)):
            oled_write(PSTR("   DKTP > "), false);
            return true;
        default:
            return false;
    }
};

void render_img(Image img) {
    // Update animation parameters
    anim_total_frame = img.len;
    if (anim_current_frame > anim_total_frame || anim_total_frame == 1) {
        anim_current_frame = 1;
    }

    oled_set_cursor(0,0);
    oled_write_raw_P( img.data[anim_current_frame - 1], sizeof(img.data[anim_current_frame - 1]) );
};

//
// OLED render cycle!!!!!!!!!!!!!
//
#define OLED_TIMEOUT 60000
#define OLED_BRIGHTNESS 255

bool oled_task_user(void) {
    // Keycode image renders if a keycode was pressed recently.
    bool did_render = false;
    if (kc_img_active) {
        did_render = get_keycode_img(last_keycode);
    } 
    
    // Layer image renders if no keycode image renders.
    if (!did_render) {
        render_img( get_layer_img(current_layer) );
    }

    // Flipbook animation handling
    if (anim_timer == 0) {
        anim_timer = timer_read();
    }

    if (timer_elapsed(anim_timer) > ANIM_FRAME_LENGTH) {
        anim_current_frame = anim_current_frame + 1 > anim_total_frame ? 1 : anim_current_frame + 1;
        anim_timer = timer_read();
    }

    return false;
};

//
// Timers!!!!!!!!!!!!!
//
void matrix_scan_user(void) {

    // Encoder task switcher
    if (task_switch_active) {
        if (timer_elapsed(task_switch_timer) > TASK_SWITCH_TIMEOUT) {
            unregister_code(KC_LALT);
            task_switch_active = false;
        }
    }

    if (kc_img_active) {
        if (timer_elapsed(kc_img_timer) > KEYCODE_IMAGE_TIMEOUT) {
            kc_img_active = false;
        }
    }
    
};


