#include "action_util.h"

static const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Keymap 0: Default Layer
     *
     * ,--------------------------------------------------.           ,--------------------------------------------------.
     * | ESC    |   1  |   2  |   3  |   4  |   5  |   6  |           |   7  |   8  |   9  |   0  |   -  |   =  |  BkSp  |
     * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
     * | Tab    |   Q  |   W  |   E  |   R  |   T  |  \   |           |  [   |   Y  |   U  |   I  |   O  |   P  | Enter  |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * | Fn3    |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |   '    |
     * |--------+------+------+------+------+------|  ~   |           |  ]   |------+------+------+------+------+--------|
     * | Fn4    |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  | Fn5    |
     * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
     *   |      |      |      |      |      |                                       |  Lft |  Dn  |  Up  | Rght | RAlt |
     *   `----------------------------------'                                       `----------------------------------'
     *                                        ,-------------.       ,-------------.
     *                                        | Del  | ~Fn1 |       | Fn0  | LGui |
     *                                 ,------|------|------|       |------+------+------.
     *                                 |      |      | Home |       | PgUp |      |      |
     *                                 | Space| LAlt |------|       |------| Enter| Space|
     *                                 |      |      | End  |       | PgDn |      |      |
     *                                 `--------------------'       `--------------------'
     *
     * FN3: LCtrl or ESC
     * FN4: LShft or (
     * FN5: RShft or )
     */

    KEYMAP(  // layout: layer 0: default
        // left hand
        ESC, 1,   2,   3,   4,   5,   6,
        TAB, Q,   W,   E,   R,   T,   BSLS,
        FN3, A,   S,   D,   F,   G,
        FN4, Z,   X,   C,   V,   B,   GRV,
        NO, NO,  NO,  NO,  NO,
                                      DEL, FN1,
                                          HOME,
                                 SPC,LALT, END,
        // right hand
                7,   8,   9,   0,MINS, EQL,BSPC,
             LBRC,   Y,   U,   I,   O,   P, ENT,
                     H,   J,   K,   L,SCLN,QUOT,
             RBRC,   N,   M,COMM, DOT,SLSH, FN5,
                       LEFT,DOWN,  UP,RGHT,RALT,
         FN0,LGUI,
        PGUP,
        PGDN, ENT, SPC
    ),

    /* Keymap 1: Function keys + Teensy (FN7)
     *
     * ,--------------------------------------------------.           ,--------------------------------------------------.
     * |        |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |           |  F7  |  F8  |  F9  | F10  | F11  | F12  |        |
     * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
     * |        |      |      | PgUp |      |      |      |           |      |      |      |      |      |      |        |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * |        |      |      | PgDn |      |      |------|           |------| Lft  |  Dn  |  Up  | Rght |      |        |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
     * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
     *   |      |      |      |      |      |                                       |      |      |      |      | FN2  |
     *   `----------------------------------'                                       `----------------------------------'
     *                                        ,-------------.       ,-------------.
     *                                        |      |      |       |      |      |
     *                                 ,------|------|------|       |------+------+------.
     *                                 |      |      |      |       |      |      |      |
     *                                 |      |      |------|       |------|      |      |
     *                                 |      |      |      |       |      |      |      |
     *                                 `--------------------'       `--------------------'
     *
     * FN2: Teensy
     */

    KEYMAP(  // layout: layer 1: F-keys instead of numbers
        // left hand
        TRNS,F1,  F2,  F3,  F4,  F5,  F6,
        TRNS,TRNS,TRNS,PGUP,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,PGDN,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,
                                      TRNS,TRNS,
                                           TRNS,
                                 TRNS,TRNS,TRNS,
        // right hand
             F7,  F8,  F9,  F10, F11, F12, TRNS,
             TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
                  LEFT,  UP,DOWN,RGHT,TRNS,TRNS,
             TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
                       TRNS,TRNS,TRNS,TRNS, FN2,
        TRNS,TRNS,
        TRNS,
        TRNS,TRNS,TRNS
    ),
};

/* id for user defined functions */
enum function_id {
    TEENSY_KEY,
    LSHIFT_LPAREN,
    RSHIFT_RPAREN,
};

/*
 * Fn action definition
 */
static const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_DEFAULT_LAYER_SET(0),               // FN0 - switch to Layer0
    [1] = ACTION_LAYER_MOMENTARY(1),                 // FN1 - push Layer1
    [2] = ACTION_FUNCTION(TEENSY_KEY),               // FN2 - Teensy key
    [3] = ACTION_MODS_TAP_KEY(MOD_LCTL, KC_ESC),     // FN3 - LCtrl acts as Esc on tap
    [4] = ACTION_FUNCTION_TAP(LSHIFT_LPAREN),        // FN4 - LShft acts as ( on tap
    [5] = ACTION_FUNCTION_TAP(RSHIFT_RPAREN),        // FN5 - RShft acts as ) on tap
};

/*
 * User defined action function
 */
void action_function(keyrecord_t *event, uint8_t id, uint8_t opt)
{
    print("action_function called\n");
    print("id  = "); phex(id); print("\n");
    print("opt = "); phex(opt); print("\n");

    keyevent_t evt = event->event;
    tap_t tap = event->tap;

    switch (id) {
        case TEENSY_KEY:
            clear_keyboard();
            print("\n\nJump to bootloader... ");
            _delay_ms(250);
            bootloader_jump(); // should not return
            print("not supported.\n");
            break;
        case LSHIFT_LPAREN:
            if (evt.pressed) {
                if (tap.count == 0 || tap.interrupted) {
                    add_mods(MOD_BIT(KC_LSHIFT));
                } else {
                    add_mods(MOD_BIT(KC_LSHIFT));
                    add_key(KC_9);
                    send_keyboard_report();
                    del_mods(MOD_BIT(KC_LSHIFT));
                    del_key(KC_9);
                    send_keyboard_report();
                }
            } else {
                if (tap.count == 0 || tap.interrupted) {
                    del_mods(MOD_BIT(KC_LSHIFT));
                }
            }
            break;
        case RSHIFT_RPAREN:
            if (evt.pressed) {
                if (tap.count == 0 || tap.interrupted) {
                    add_mods(MOD_BIT(KC_RSHIFT));
                } else {
                    add_mods(MOD_BIT(KC_RSHIFT));
                    add_key(KC_0);
                    send_keyboard_report();
                    del_mods(MOD_BIT(KC_RSHIFT));
                    del_key(KC_0);
                    send_keyboard_report();
                }
            } else {
                if (tap.count == 0 || tap.interrupted) {
                    del_mods(MOD_BIT(KC_RSHIFT));
                }
            }
            break;
    }
}
