#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void live_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_9(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_12(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_35(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_32(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_33(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_H(double *in_vec, double *out_3945335657060037103);
void live_err_fun(double *nom_x, double *delta_x, double *out_8938088280571293435);
void live_inv_err_fun(double *nom_x, double *true_x, double *out_6738903235738351081);
void live_H_mod_fun(double *state, double *out_5209810659151512023);
void live_f_fun(double *state, double dt, double *out_8163943672570367896);
void live_F_fun(double *state, double dt, double *out_897498466737785332);
void live_h_4(double *state, double *unused, double *out_3502569351056287501);
void live_H_4(double *state, double *unused, double *out_8296063605264325527);
void live_h_9(double *state, double *unused, double *out_2847618749778993425);
void live_H_9(double *state, double *unused, double *out_8054873958634734882);
void live_h_10(double *state, double *unused, double *out_1279704386804620564);
void live_H_10(double *state, double *unused, double *out_5924778728138962838);
void live_h_12(double *state, double *unused, double *out_6058064620041131879);
void live_H_12(double *state, double *unused, double *out_3276607197232363732);
void live_h_35(double *state, double *unused, double *out_3596720275326589648);
void live_H_35(double *state, double *unused, double *out_531044164907350023);
void live_h_32(double *state, double *unused, double *out_2720821542282497077);
void live_H_32(double *state, double *unused, double *out_4798236762950977682);
void live_h_13(double *state, double *unused, double *out_4277917187949734404);
void live_H_13(double *state, double *unused, double *out_8186721540452566877);
void live_h_14(double *state, double *unused, double *out_2847618749778993425);
void live_H_14(double *state, double *unused, double *out_8054873958634734882);
void live_h_33(double *state, double *unused, double *out_1458389216353049840);
void live_H_33(double *state, double *unused, double *out_2619512839731507581);
void live_predict(double *in_x, double *in_P, double *in_Q, double dt);
}