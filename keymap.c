#include QMK_KEYBOARD_H
#if __has_include("keymap.h")
#    include "keymap.h"
#endif

#define KC_COPY LCTL(KC_C)
#define KC_CUT LCTL(KC_X)
#define KC_PSTE LCTL(KC_V)
#define KC_UNDO LCTL(KC_Z)
#define KC_REDO RCS(KC_Z) 
#define KC_SAVE LCTL(KC_S) 

#define DOT_EXLM LT(0,KC_DOT)
#define COMM_MINS LT(0,KC_COMM)
#define SLSH_UNDS LT(0,KC_SLSH)
#define SCLN_QUOT LT(0,KC_SCLN)
#define QUOT_SCLN LT(0,KC_QUOT)
#define P_QUOT LT(0,KC_P)
#define O_P LT(0,KC_O)
#define G_EQL LT(0,KC_G)
#define V_BSLS LT(0,KC_V)
#define B_BSLS LT(0,KC_B)
#define DOT_SLSH LT(1,KC_DOT)
#define LTFN_CTLBSPC LT(_FUN, KC_BSPC)

// layer aliases
#define _COLEMAKDH 0
#define _QWERTY 1
#define _WORKMAN 2
#define _MEDIA 3
#define _NAV 4
#define _MOUSE 5
#define _SYM 8
#define _NUM 7
#define _FUN 6
#define _GAME 9
#define _GAMENUM 10
#define _PLOVER 11


#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD

// autocorrect generation commands:
// cd qmk_firmware/keyboards/cheapino/keymaps/nathanieldyer14/
// qmk generate-autocorrect-data autocorrect_dict.txt

char laydef = 'C'; // variable current default layer; 'C' for _COLEMAKDH, 'Q' for _QWERTY, 'G' for _GAME, 'W' for _WORKMAN

layer_state_t default_layer_state_set_user(layer_state_t state) {
    switch(biton32(state)){
        case _COLEMAKDH:
        laydef = 'C';
        rgblight_sethsv (0, 0, 50); // White
        break;
        case _QWERTY:
        laydef = 'Q';
        rgblight_sethsv (80, 255, 100); // Orange
        break;
        case _GAME:
        laydef = 'G';
        rgblight_sethsv (0, 255, 100); // Green
        break;
        case _PLOVER:
        laydef = 'P';
        rgblight_sethsv (85, 255, 100); // Red
        break;
        case _WORKMAN:
        laydef = 'W';
        rgblight_sethsv (240, 255, 100); // Mint
        break;
    };
    return state;
};

// NOTE: Hue is flipped across 43-169 (Yellow-Blue) axis (see https://docs.qmk.fm/features/rgblight#color-selection)
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _GAMENUM:
        rgblight_sethsv (169, 255, 100); // Blue
        break;
    case _FUN:
        rgblight_sethsv (85, 255, 100); // Red
        break;
    case _NUM:
        rgblight_sethsv (169, 255, 100); // Blue
        break;
    case _SYM:
        rgblight_sethsv (0, 255, 100); // Green
        break;
    case _MOUSE:
        rgblight_sethsv (43, 255, 100); // Yellow
        break;
    case _NAV:
        rgblight_sethsv (201, 255, 100); // Cyan
        break;
    case _MEDIA:
        rgblight_sethsv (127, 255, 100); // Magenta
        break;
    default: //  for any other layers, or the default layer
        if(laydef == 'G') {
          rgblight_sethsv (0, 255, 100); // Green
        } else if(laydef == 'Q') {
          rgblight_sethsv (80, 255, 100); // Orange
        } else if(laydef == 'W') {
          rgblight_sethsv (240 , 255, 100); // Mint
        } else if(laydef == 'P') {
          rgblight_sethsv (85, 255, 100); // Red
        } else {
          rgblight_sethsv (0, 0, 50); // White for Default
        }
        break;
    }
  return state;
}

// Helper for implementing tap vs. long-press keys. Given a tap-hold
// key event, replaces the hold function with `long_press_keycode`.
static bool process_tap_or_long_press_key(
    keyrecord_t* record, uint16_t long_press_keycode) {
  if (record->tap.count == 0) {  // Key is being held.
    if (record->event.pressed) {
      tap_code16(long_press_keycode);
    }
    return false;  // Skip default handling.
  }
  return true;  // Continue default handling.
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LSFT_T(KC_T):
        case LSFT_T(KC_F):
        case RSFT_T(KC_N):
        case RSFT_T(KC_J):
            return TAPPING_TERM - 50;
        case LGUI_T(KC_A):
        case LGUI_T(KC_O):
        case LGUI_T(KC_I):
        case LGUI_T(KC_SCLN):
            return TAPPING_TERM + 200;
        default:
            return TAPPING_TERM;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
  switch (keycode) {
    case DOT_EXLM:  // Period on tap, Exlamation point on long press.
      return process_tap_or_long_press_key(record, S(KC_1));
    case COMM_MINS:  // Comma on tap, Minus on long press.
      return process_tap_or_long_press_key(record, KC_MINS);
    case SLSH_UNDS:  // Slash on tap, Underscore on long press.
      return process_tap_or_long_press_key(record, S(KC_MINS));
    case SCLN_QUOT:  // Semicolon on tap, Quote on long press.
      return process_tap_or_long_press_key(record, KC_QUOT);
    case QUOT_SCLN:  // Quote on tap, Semicolon on long press.
      return process_tap_or_long_press_key(record, KC_SCLN);
    case P_QUOT:  // P on tap, Quote on long press.
      return process_tap_or_long_press_key(record, KC_QUOT);
    case O_P:  // O on tap, P on long press.
      return process_tap_or_long_press_key(record, KC_P);
    case G_EQL:  // G on tap, Equal on long press.
      return process_tap_or_long_press_key(record, KC_EQL);
    case V_BSLS:  // V on tap, Backslash on long press.
      return process_tap_or_long_press_key(record, KC_BSLS);
    case B_BSLS:  // B on tap, Backslash on long press.
      return process_tap_or_long_press_key(record, KC_BSLS);
    case DOT_SLSH:  // Period on tap, Slash on long press.
      return process_tap_or_long_press_key(record, KC_SLSH);
    case LTFN_CTLBSPC: //Lctrl+Bspc when tapped, LT(_FN) when held
      if(record->event.pressed && record->tap.count) { 
        tap_code16(C(KC_BSPC));
        return false; //override default key behaviour
      }
      return true;
  }

  return true;
}

/* This file was generated by qmk json2c. You may or may not want to
 * edit it directly.
 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_COLEMAKDH] = LAYOUT_split_3x5_3(
    KC_Q, KC_W, KC_F, KC_P, KC_B, KC_J, KC_L, KC_U, KC_Y, QUOT_SCLN, 
    LGUI_T(KC_A), LALT_T(KC_R), LCTL_T(KC_S), LSFT_T(KC_T), G_EQL, KC_M, RSFT_T(KC_N), LCTL_T(KC_E), LALT_T(KC_I), LGUI_T(KC_O), 
    LSFT_T(KC_Z), KC_X, KC_C, KC_D, V_BSLS, KC_K, KC_H, COMM_MINS, DOT_EXLM, SLSH_UNDS, 
    LT(_MEDIA,KC_ESC), LT(_NAV,KC_SPC), LT(_MOUSE,KC_TAB), LT(_SYM,KC_ENT), LT(_NUM,KC_BSPC), LTFN_CTLBSPC), // Default
    [_WORKMAN] = LAYOUT_split_3x5_3(
    KC_Q, KC_D, KC_R, KC_W, KC_B, KC_J, KC_F, KC_U, KC_P, QUOT_SCLN, 
    LGUI_T(KC_A), LALT_T(KC_S), LCTL_T(KC_H), LSFT_T(KC_T), G_EQL, KC_Y, RSFT_T(KC_N), LCTL_T(KC_E), LALT_T(KC_O), LGUI_T(KC_I), 
    LSFT_T(KC_Z), KC_X, KC_M, KC_C, V_BSLS, KC_K, KC_L, COMM_MINS, DOT_EXLM, SLSH_UNDS, 
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS), // Default
    [_QWERTY] = LAYOUT_split_3x5_3(
    KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, P_QUOT, 
    LGUI_T(KC_A), LALT_T(KC_S), LCTL_T(KC_D), LSFT_T(KC_F), G_EQL, KC_H, RSFT_T(KC_J), LCTL_T(KC_K), LALT_T(KC_L), LGUI_T(KC_SCLN), 
    LSFT_T(KC_Z), KC_X, KC_C, KC_V, B_BSLS, KC_N, KC_M, COMM_MINS, DOT_EXLM, SLSH_UNDS, 
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS), // Qwerty
    [_MEDIA] = LAYOUT_split_3x5_3(
    DF(_PLOVER), NK_ON, NK_OFF, DF(_WORKMAN), DF(_QWERTY), CG_SWAP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
    KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, DF(_COLEMAKDH), CG_NORM, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, 
    AC_TOGG, AC_ON, AC_OFF, KC_TRNS, DF(_GAME), RGB_TOG, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
    KC_TRNS, KC_TRNS, KC_TRNS, KC_MSTP, KC_MPLY, KC_MUTE), // Media
    [_NAV] = LAYOUT_split_3x5_3(
    KC_UNDO, KC_CUT, KC_COPY, KC_PSTE, KC_REDO, KC_REDO, KC_PSTE, KC_COPY, KC_CUT, KC_UNDO, 
    KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_SAVE, KC_CAPS, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, 
    KC_UNDO, KC_CUT, KC_COPY, KC_PSTE, KC_REDO, KC_INS, KC_HOME, KC_PGDN, KC_PGUP, KC_END, 
    KC_TRNS, KC_TRNS, KC_TRNS, KC_ENT, KC_BSPC, KC_DEL), // Nav
    [_MOUSE] = LAYOUT_split_3x5_3(
    KC_UNDO, KC_CUT, KC_COPY, KC_PSTE, KC_REDO, KC_TRNS, MS_BTN4, KC_TRNS, KC_TRNS, MS_BTN5, 
    KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_TRNS, KC_TRNS, MS_LEFT, MS_DOWN, MS_UP, MS_RGHT, 
    KC_TRNS, MS_ACL2, MS_ACL1, MS_ACL0, KC_TRNS, KC_TRNS, MS_WHLL, MS_WHLD, MS_WHLU, MS_WHLR, 
    KC_TRNS, KC_TRNS, KC_TRNS, MS_BTN2, MS_BTN1, MS_BTN3), // Mouse
    [_SYM] = LAYOUT_split_3x5_3(
    S(KC_LBRC), S(KC_7), S(KC_8), S(KC_9), S(KC_RBRC), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
    S(KC_SCLN), S(KC_4), S(KC_5), S(KC_6), S(KC_EQL), KC_TRNS, KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI, 
    S(KC_GRV), S(KC_1), S(KC_2), S(KC_3), S(KC_BSLS), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
    S(KC_9), S(KC_0), S(KC_MINS), KC_TRNS, KC_TRNS, KC_TRNS), // Sym
    [_NUM] = LAYOUT_split_3x5_3(
    KC_LBRC, KC_7, KC_8, KC_9, KC_RBRC, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
    KC_SCLN, KC_4, KC_5, KC_6, KC_EQL, KC_TRNS, KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI, 
    KC_GRV, KC_1, KC_2, KC_3, KC_BSLS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
    KC_DOT, KC_0, KC_MINS, KC_TRNS, KC_TRNS, KC_TRNS), // Num
    [_FUN] = LAYOUT_split_3x5_3(
    KC_F12, KC_F7, KC_F8, KC_F9, KC_PSCR, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
    KC_F11, KC_F4, KC_F5, KC_F6, KC_PAUS, KC_TRNS, KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI, 
    KC_F10, KC_F1, KC_F2, KC_F3, KC_SCRL, KC_TRNS, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, 
    KC_APP, KC_SPC, KC_TAB, KC_TRNS, KC_TRNS, KC_TRNS), // Fun
    [_GAME] = LAYOUT_split_3x5_3(
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, O_P, 
    KC_LSFT, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L,
    KC_LCTL, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, DOT_SLSH, 
    LT(_GAMENUM,KC_ESC), KC_SPC, KC_T, DF(_COLEMAKDH), KC_TRNS, KC_TRNS), // Qwerty Offset for Gaming
    [_GAMENUM] = LAYOUT_split_3x5_3(
    KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, 
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS), // Num Offset for Gaming
    [_PLOVER] = LAYOUT_split_3x5_3(
    KC_T,    KC_T,    KC_W,    KC_E,    KC_R,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,
    KC_G,    KC_A,    KC_S,    KC_D,    KC_F,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    DF(_COLEMAKDH),XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX, XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
    KC_1,    KC_C,    KC_V,    KC_N,    KC_M,    KC_Y),
    // * * T P H   -F -P -L -T -D
    // * S K W R   -R -B -G -S -Z
    //     # A O   E U *
};

#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {

};
#endif // defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)



