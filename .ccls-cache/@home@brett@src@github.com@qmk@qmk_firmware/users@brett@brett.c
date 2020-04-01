#include "brett.h"

/* qk_tap_dance_action_t tap_dance_actions[] = {[TD_LBRC] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_LT), [TD_RBRC] = ACTION_TAP_DANCE_DOUBLE(KC_RBRC, KC_GT)}; */

void tmux_prefix(void) { tap_code16(C(KC_P)); }

char *get_key(uint16_t keycode) {
    switch (keycode) {
        case FAT_ARROW:
            return "=>";
        case SKINNY_ARROW:
            return "->";
        case REVERSE_ARROW:
            return "<-";
        case CONCAT:
            return "<>";
        case MAP:
            return "<$>";
        case MAP_FLIPPED:
            return "<#>";
        case MAP_FLIPPED_ALT:
            return "<&>";
        case FLAP:
            return "<@>";
        case PIPE:
            return "|>";
        case ALT:
            return "<|>";
        case APPLY:
            return "<*>";
        case SEQUENCE_AP_LEFT:
            return "<*";
        case SEQUENCE_AP_RIGHT:
            return "*>";
        case AND:
            return "&&";
        case OR:
            return "||";
        case BIND:
            return ">>=";
        case BIND_FLIPPED:
            return "=<<";
        case DOUBLE_COLON:
            return "::";
        case VOID_LEFT:
            return "<$";
        case VOID_RIGHT:
            return "$>";
        case PIPE_ALT:
            return ">>>";
        case PIPE_FLIPPED_ALT:
            return "<<<";
        case REF:
            return "'&";
        case COMPOSE_KLEISLI:
            return ">=>";
        case COMPOSE_KLEISLI_FLIPPED:
            return "<=<";
        default:
            return "";
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    bool pressed = record->event.pressed;
    switch (keycode) {
        case FAT_ARROW ... COMPOSE_KLEISLI_FLIPPED:
            if (pressed) {
                send_string(get_key(keycode));
            }
            return false;
        case TMUX:
            if (!pressed) {
                tmux_prefix();
            }
            return false;
        case FLASH:
            if (!pressed) {
                SEND_STRING("make -j8 --output-sync " QMK_KEYBOARD ":" QMK_KEYMAP ":flash" SS_TAP(X_ENTER));
                reset_keyboard();
            }
            return false;
        default:
            return true;
    }
}

const uint16_t PROGMEM colon_comma_combo[]   = {KC_SCLN, KC_COMM, COMBO_END};
const uint16_t PROGMEM colon_quote_combo[]   = {KC_SCLN, KC_QUOT, COMBO_END};
const uint16_t PROGMEM lbrace_rbrace_combo[] = {KC_LBRC, KC_RBRC, COMBO_END};
const uint16_t PROGMEM comma_dot_combo[]     = {KC_COMM, KC_DOT, COMBO_END};
const uint16_t PROGMEM dot_p_combo[]         = {KC_DOT, KC_P, COMBO_END};
const uint16_t PROGMEM q_j_combo[]           = {KC_Q, KC_J, COMBO_END};
const uint16_t PROGMEM j_k_combo[]           = {KC_J, KC_K, COMBO_END};

// right hand combinations.
const uint16_t PROGMEM l_r_combo[] = {KC_L, KC_R, COMBO_END};
const uint16_t PROGMEM r_c_combo[] = {KC_R, KC_C, COMBO_END};
const uint16_t PROGMEM c_g_combo[] = {KC_C, KC_G, COMBO_END};
const uint16_t PROGMEM v_w_combo[] = {KC_V, KC_W, COMBO_END};
const uint16_t PROGMEM w_m_combo[] = {KC_W, KC_M, COMBO_END};

// both hand combinations.
const uint16_t PROGMEM dot_c_combo[] = {KC_DOT, KC_C, COMBO_END};
const uint16_t PROGMEM j_w_combo[]   = {KC_J, KC_W, COMBO_END};
const uint16_t PROGMEM u_h_combo[]   = {KC_U, KC_H, COMBO_END};
const uint16_t PROGMEM p_g_combo[]   = {KC_P, KC_G, COMBO_END};
const uint16_t PROGMEM k_m_combo[]   = {KC_K, KC_M, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    // left hand combinations.
    [LBRACE_RBRACE] = COMBO(lbrace_rbrace_combo, KC_LEAD),
    [COLON_COMMA]   = COMBO(colon_comma_combo, KC_TAB),
    [COLON_QUOTE]   = COMBO(colon_quote_combo, KC_LEAD),
    [COMMA_DOT]     = COMBO(comma_dot_combo, KC_QUES),
    [DOT_P]         = COMBO(dot_p_combo, KC_UNDS),
    [Q_J]           = COMBO(q_j_combo, KC_LEAD),
    [J_K]           = COMBO(j_k_combo, KC_ESC),

    // right hand combinations.
    [L_R] = COMBO(l_r_combo, KC_BSPC),
    [R_C] = COMBO(r_c_combo, KC_SLSH),
    [C_G] = COMBO(c_g_combo, KC_MINS),
    [V_W] = COMBO(v_w_combo, KC_APP),
    [W_M] = COMBO(w_m_combo, KC_DELT),

    // both hand combinations.
    [DOT_C] = COMBO(dot_c_combo, KC_PGUP),
    [J_W]   = COMBO(j_w_combo, KC_PGDN),
    [U_H]   = COMBO(u_h_combo, KC_ENT),
    [P_G]   = COMBO(p_g_combo, KC_HOME)};

LEADER_EXTERNS();

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
    LEADER_DICTIONARY() {
        leading = false;
        leader_end();
        SEQ_ONE_KEY(KC_R) {
            SEND_STRING("make -j8 --output-sync " QMK_KEYBOARD ":" QMK_KEYMAP ":flash" SS_TAP(X_ENTER));
            reset_keyboard();
        }
        SEQ_ONE_KEY(KC_T) { tmux_prefix(); }
        SEQ_TWO_KEYS(KC_S, KC_C) { SEND_STRING("sudo systemctl"); }
        SEQ_TWO_KEYS(KC_N, KC_B) { SEND_STRING("nix-build"); }
        SEQ_TWO_KEYS(KC_N, KC_S) { SEND_STRING("nix-shell"); }
        SEQ_TWO_KEYS(KC_G, KC_A) { SEND_STRING("git add ."); }
        SEQ_TWO_KEYS(KC_G, KC_D) { SEND_STRING("git diff"); }
        SEQ_THREE_KEYS(KC_G, KC_D, KC_S) { SEND_STRING("git diff --staged"); }
        SEQ_TWO_KEYS(KC_G, KC_L) { SEND_STRING("git log"); }
        SEQ_THREE_KEYS(KC_G, KC_L, KC_O) { SEND_STRING("git log --oneline"); }
        SEQ_TWO_KEYS(KC_G, KC_F) { SEND_STRING("git fetch"); }
        SEQ_TWO_KEYS(KC_G, KC_O) { SEND_STRING("git checkout"); }
        SEQ_TWO_KEYS(KC_G, KC_P) { SEND_STRING("git pull"); }
        SEQ_TWO_KEYS(KC_G, KC_S) { SEND_STRING("git status"); }
        SEQ_THREE_KEYS(KC_G, KC_C, KC_A) { SEND_STRING("git commit --amend"); }
    }
}
