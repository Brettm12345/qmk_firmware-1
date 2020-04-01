#include QMK_KEYBOARD_H
#pragma once

enum layers { BASE, HHKB, PROG, MOUSE };

// Tap for tab hold for MOUSE
#define HYPR_TAB HYPR_T(KC_TAB)

// Tap for leader holder for HHKB
#define LEADER_HHKB LT(HHKB, KC_LEAD)

// Tap for space hold for PROG
#define SPACE_PROG LT(PROG, KC_SPC)

// Tap for ESC hold for CTRL
#define CTL_ESC CTL_T(KC_ESC)

// Tab for ; hold for Meh
#define MEH_SCLN MEH_T(KC_SCLN)

enum {
    TD_LBRC = 0,
    TD_RBRC,
};

#define KT_LBRC TD(TD_LBRC)
#define KT_RBRC TD(TD_RBRC)

#define LEADER_TIMEOUT 800

void tmux_prefix(void);

enum combos {
    // left hand combinations.
    LBRACE_RBRACE,
    COLON_COMMA,
    COLON_QUOTE,
    COMMA_DOT,
    DOT_P,
    Q_J,
    J_K,

    // right hand combinations.
    L_R,
    R_C,
    C_G,
    V_W,
    W_M,

    // both hands combinations.
    DOT_C,
    J_W,
    P_G,
    U_H
};

enum userspace_custom_keycodes {
    PLACEHOLDER = SAFE_RANGE,  // Can always be here
    FAT_ARROW,                 // =>
    SKINNY_ARROW,              // ->
    REVERSE_ARROW,             // <-
    CONCAT,                    // <>
    MAP,                       // <$>
    MAP_FLIPPED_ALT,           // <&>
    MAP_FLIPPED,               // <#>
    FLAP,                      // <@>
    PIPE,                      // |>
    PIPE_ALT,                  // >>>
    PIPE_FLIPPED_ALT,          // <<<
    ALT,                       // <|>
    APPLY,                     // <*>
    SEQUENCE_AP_LEFT,          // <*
    SEQUENCE_AP_RIGHT,         // *>
    AND,                       // &&
    OR,                        // ||
    BIND,                      // >>=
    BIND_FLIPPED,              // =<<
    VOID_LEFT,                 // <$
    VOID_RIGHT,                // $>
    DOUBLE_COLON,              // ::
    REF,                       // '&
    COMPOSE_KLEISLI,           // >=>
    COMPOSE_KLEISLI_FLIPPED,   // <=<
    TMUX,
    FLASH  // Handle keyboard flashing
};

bool process_record_keymap(uint16_t keycode, keyrecord_t *record);
