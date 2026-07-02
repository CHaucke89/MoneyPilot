#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_err_fun(double *nom_x, double *delta_x, double *out_5817993247136894603);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_4344067570915274795);
void car_H_mod_fun(double *state, double *out_6934400592379471799);
void car_f_fun(double *state, double dt, double *out_6508793848623948395);
void car_F_fun(double *state, double dt, double *out_5131722384156741838);
void car_h_25(double *state, double *unused, double *out_3280124934580640397);
void car_H_25(double *state, double *unused, double *out_3411419942389980122);
void car_h_24(double *state, double *unused, double *out_5847931756337679085);
void car_H_24(double *state, double *unused, double *out_146505656412343014);
void car_h_30(double *state, double *unused, double *out_7220280955406446863);
void car_H_30(double *state, double *unused, double *out_3505270399101636633);
void car_h_26(double *state, double *unused, double *out_2218607687745601218);
void car_H_26(double *state, double *unused, double *out_7152923261264036346);
void car_h_27(double *state, double *unused, double *out_6146075726688434777);
void car_H_27(double *state, double *unused, double *out_5715522201333645103);
void car_h_29(double *state, double *unused, double *out_821239437992597717);
void car_H_29(double *state, double *unused, double *out_3030527545218828008);
void car_h_28(double *state, double *unused, double *out_7313819527764576514);
void car_H_28(double *state, double *unused, double *out_1066897273653501757);
void car_h_31(double *state, double *unused, double *out_3437311602931769542);
void car_H_31(double *state, double *unused, double *out_3380773980513019694);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}