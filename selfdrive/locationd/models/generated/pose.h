#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_2497164291072602752);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_1094719228690614749);
void pose_H_mod_fun(double *state, double *out_2127076694835493224);
void pose_f_fun(double *state, double dt, double *out_5227450394252956779);
void pose_F_fun(double *state, double dt, double *out_3158793123073568088);
void pose_h_4(double *state, double *unused, double *out_6888673195313457642);
void pose_H_4(double *state, double *unused, double *out_5327486595936963248);
void pose_h_10(double *state, double *unused, double *out_5671532680385375413);
void pose_H_10(double *state, double *unused, double *out_6244754580400464959);
void pose_h_13(double *state, double *unused, double *out_2016775626742602393);
void pose_H_13(double *state, double *unused, double *out_2283144612379737681);
void pose_h_14(double *state, double *unused, double *out_2832180890579824390);
void pose_H_14(double *state, double *unused, double *out_1364245739597478719);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}