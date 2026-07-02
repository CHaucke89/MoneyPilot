#include "car.h"

namespace {
#define DIM 9
#define EDIM 9
#define MEDIM 9
typedef void (*Hfun)(double *, double *, double *);

double mass;

void set_mass(double x){ mass = x;}

double rotational_inertia;

void set_rotational_inertia(double x){ rotational_inertia = x;}

double center_to_front;

void set_center_to_front(double x){ center_to_front = x;}

double center_to_rear;

void set_center_to_rear(double x){ center_to_rear = x;}

double stiffness_front;

void set_stiffness_front(double x){ stiffness_front = x;}

double stiffness_rear;

void set_stiffness_rear(double x){ stiffness_rear = x;}
const static double MAHA_THRESH_25 = 3.8414588206941227;
const static double MAHA_THRESH_24 = 5.991464547107981;
const static double MAHA_THRESH_30 = 3.8414588206941227;
const static double MAHA_THRESH_26 = 3.8414588206941227;
const static double MAHA_THRESH_27 = 3.8414588206941227;
const static double MAHA_THRESH_29 = 3.8414588206941227;
const static double MAHA_THRESH_28 = 3.8414588206941227;
const static double MAHA_THRESH_31 = 3.8414588206941227;

/******************************************************************************
 *                      Code generated with SymPy 1.14.0                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_5817993247136894603) {
   out_5817993247136894603[0] = delta_x[0] + nom_x[0];
   out_5817993247136894603[1] = delta_x[1] + nom_x[1];
   out_5817993247136894603[2] = delta_x[2] + nom_x[2];
   out_5817993247136894603[3] = delta_x[3] + nom_x[3];
   out_5817993247136894603[4] = delta_x[4] + nom_x[4];
   out_5817993247136894603[5] = delta_x[5] + nom_x[5];
   out_5817993247136894603[6] = delta_x[6] + nom_x[6];
   out_5817993247136894603[7] = delta_x[7] + nom_x[7];
   out_5817993247136894603[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_4344067570915274795) {
   out_4344067570915274795[0] = -nom_x[0] + true_x[0];
   out_4344067570915274795[1] = -nom_x[1] + true_x[1];
   out_4344067570915274795[2] = -nom_x[2] + true_x[2];
   out_4344067570915274795[3] = -nom_x[3] + true_x[3];
   out_4344067570915274795[4] = -nom_x[4] + true_x[4];
   out_4344067570915274795[5] = -nom_x[5] + true_x[5];
   out_4344067570915274795[6] = -nom_x[6] + true_x[6];
   out_4344067570915274795[7] = -nom_x[7] + true_x[7];
   out_4344067570915274795[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_6934400592379471799) {
   out_6934400592379471799[0] = 1.0;
   out_6934400592379471799[1] = 0.0;
   out_6934400592379471799[2] = 0.0;
   out_6934400592379471799[3] = 0.0;
   out_6934400592379471799[4] = 0.0;
   out_6934400592379471799[5] = 0.0;
   out_6934400592379471799[6] = 0.0;
   out_6934400592379471799[7] = 0.0;
   out_6934400592379471799[8] = 0.0;
   out_6934400592379471799[9] = 0.0;
   out_6934400592379471799[10] = 1.0;
   out_6934400592379471799[11] = 0.0;
   out_6934400592379471799[12] = 0.0;
   out_6934400592379471799[13] = 0.0;
   out_6934400592379471799[14] = 0.0;
   out_6934400592379471799[15] = 0.0;
   out_6934400592379471799[16] = 0.0;
   out_6934400592379471799[17] = 0.0;
   out_6934400592379471799[18] = 0.0;
   out_6934400592379471799[19] = 0.0;
   out_6934400592379471799[20] = 1.0;
   out_6934400592379471799[21] = 0.0;
   out_6934400592379471799[22] = 0.0;
   out_6934400592379471799[23] = 0.0;
   out_6934400592379471799[24] = 0.0;
   out_6934400592379471799[25] = 0.0;
   out_6934400592379471799[26] = 0.0;
   out_6934400592379471799[27] = 0.0;
   out_6934400592379471799[28] = 0.0;
   out_6934400592379471799[29] = 0.0;
   out_6934400592379471799[30] = 1.0;
   out_6934400592379471799[31] = 0.0;
   out_6934400592379471799[32] = 0.0;
   out_6934400592379471799[33] = 0.0;
   out_6934400592379471799[34] = 0.0;
   out_6934400592379471799[35] = 0.0;
   out_6934400592379471799[36] = 0.0;
   out_6934400592379471799[37] = 0.0;
   out_6934400592379471799[38] = 0.0;
   out_6934400592379471799[39] = 0.0;
   out_6934400592379471799[40] = 1.0;
   out_6934400592379471799[41] = 0.0;
   out_6934400592379471799[42] = 0.0;
   out_6934400592379471799[43] = 0.0;
   out_6934400592379471799[44] = 0.0;
   out_6934400592379471799[45] = 0.0;
   out_6934400592379471799[46] = 0.0;
   out_6934400592379471799[47] = 0.0;
   out_6934400592379471799[48] = 0.0;
   out_6934400592379471799[49] = 0.0;
   out_6934400592379471799[50] = 1.0;
   out_6934400592379471799[51] = 0.0;
   out_6934400592379471799[52] = 0.0;
   out_6934400592379471799[53] = 0.0;
   out_6934400592379471799[54] = 0.0;
   out_6934400592379471799[55] = 0.0;
   out_6934400592379471799[56] = 0.0;
   out_6934400592379471799[57] = 0.0;
   out_6934400592379471799[58] = 0.0;
   out_6934400592379471799[59] = 0.0;
   out_6934400592379471799[60] = 1.0;
   out_6934400592379471799[61] = 0.0;
   out_6934400592379471799[62] = 0.0;
   out_6934400592379471799[63] = 0.0;
   out_6934400592379471799[64] = 0.0;
   out_6934400592379471799[65] = 0.0;
   out_6934400592379471799[66] = 0.0;
   out_6934400592379471799[67] = 0.0;
   out_6934400592379471799[68] = 0.0;
   out_6934400592379471799[69] = 0.0;
   out_6934400592379471799[70] = 1.0;
   out_6934400592379471799[71] = 0.0;
   out_6934400592379471799[72] = 0.0;
   out_6934400592379471799[73] = 0.0;
   out_6934400592379471799[74] = 0.0;
   out_6934400592379471799[75] = 0.0;
   out_6934400592379471799[76] = 0.0;
   out_6934400592379471799[77] = 0.0;
   out_6934400592379471799[78] = 0.0;
   out_6934400592379471799[79] = 0.0;
   out_6934400592379471799[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_6508793848623948395) {
   out_6508793848623948395[0] = state[0];
   out_6508793848623948395[1] = state[1];
   out_6508793848623948395[2] = state[2];
   out_6508793848623948395[3] = state[3];
   out_6508793848623948395[4] = state[4];
   out_6508793848623948395[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_6508793848623948395[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_6508793848623948395[7] = state[7];
   out_6508793848623948395[8] = state[8];
}
void F_fun(double *state, double dt, double *out_5131722384156741838) {
   out_5131722384156741838[0] = 1;
   out_5131722384156741838[1] = 0;
   out_5131722384156741838[2] = 0;
   out_5131722384156741838[3] = 0;
   out_5131722384156741838[4] = 0;
   out_5131722384156741838[5] = 0;
   out_5131722384156741838[6] = 0;
   out_5131722384156741838[7] = 0;
   out_5131722384156741838[8] = 0;
   out_5131722384156741838[9] = 0;
   out_5131722384156741838[10] = 1;
   out_5131722384156741838[11] = 0;
   out_5131722384156741838[12] = 0;
   out_5131722384156741838[13] = 0;
   out_5131722384156741838[14] = 0;
   out_5131722384156741838[15] = 0;
   out_5131722384156741838[16] = 0;
   out_5131722384156741838[17] = 0;
   out_5131722384156741838[18] = 0;
   out_5131722384156741838[19] = 0;
   out_5131722384156741838[20] = 1;
   out_5131722384156741838[21] = 0;
   out_5131722384156741838[22] = 0;
   out_5131722384156741838[23] = 0;
   out_5131722384156741838[24] = 0;
   out_5131722384156741838[25] = 0;
   out_5131722384156741838[26] = 0;
   out_5131722384156741838[27] = 0;
   out_5131722384156741838[28] = 0;
   out_5131722384156741838[29] = 0;
   out_5131722384156741838[30] = 1;
   out_5131722384156741838[31] = 0;
   out_5131722384156741838[32] = 0;
   out_5131722384156741838[33] = 0;
   out_5131722384156741838[34] = 0;
   out_5131722384156741838[35] = 0;
   out_5131722384156741838[36] = 0;
   out_5131722384156741838[37] = 0;
   out_5131722384156741838[38] = 0;
   out_5131722384156741838[39] = 0;
   out_5131722384156741838[40] = 1;
   out_5131722384156741838[41] = 0;
   out_5131722384156741838[42] = 0;
   out_5131722384156741838[43] = 0;
   out_5131722384156741838[44] = 0;
   out_5131722384156741838[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_5131722384156741838[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_5131722384156741838[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_5131722384156741838[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_5131722384156741838[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_5131722384156741838[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_5131722384156741838[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_5131722384156741838[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_5131722384156741838[53] = -9.8100000000000005*dt;
   out_5131722384156741838[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_5131722384156741838[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_5131722384156741838[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_5131722384156741838[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_5131722384156741838[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_5131722384156741838[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_5131722384156741838[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_5131722384156741838[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_5131722384156741838[62] = 0;
   out_5131722384156741838[63] = 0;
   out_5131722384156741838[64] = 0;
   out_5131722384156741838[65] = 0;
   out_5131722384156741838[66] = 0;
   out_5131722384156741838[67] = 0;
   out_5131722384156741838[68] = 0;
   out_5131722384156741838[69] = 0;
   out_5131722384156741838[70] = 1;
   out_5131722384156741838[71] = 0;
   out_5131722384156741838[72] = 0;
   out_5131722384156741838[73] = 0;
   out_5131722384156741838[74] = 0;
   out_5131722384156741838[75] = 0;
   out_5131722384156741838[76] = 0;
   out_5131722384156741838[77] = 0;
   out_5131722384156741838[78] = 0;
   out_5131722384156741838[79] = 0;
   out_5131722384156741838[80] = 1;
}
void h_25(double *state, double *unused, double *out_3280124934580640397) {
   out_3280124934580640397[0] = state[6];
}
void H_25(double *state, double *unused, double *out_3411419942389980122) {
   out_3411419942389980122[0] = 0;
   out_3411419942389980122[1] = 0;
   out_3411419942389980122[2] = 0;
   out_3411419942389980122[3] = 0;
   out_3411419942389980122[4] = 0;
   out_3411419942389980122[5] = 0;
   out_3411419942389980122[6] = 1;
   out_3411419942389980122[7] = 0;
   out_3411419942389980122[8] = 0;
}
void h_24(double *state, double *unused, double *out_5847931756337679085) {
   out_5847931756337679085[0] = state[4];
   out_5847931756337679085[1] = state[5];
}
void H_24(double *state, double *unused, double *out_146505656412343014) {
   out_146505656412343014[0] = 0;
   out_146505656412343014[1] = 0;
   out_146505656412343014[2] = 0;
   out_146505656412343014[3] = 0;
   out_146505656412343014[4] = 1;
   out_146505656412343014[5] = 0;
   out_146505656412343014[6] = 0;
   out_146505656412343014[7] = 0;
   out_146505656412343014[8] = 0;
   out_146505656412343014[9] = 0;
   out_146505656412343014[10] = 0;
   out_146505656412343014[11] = 0;
   out_146505656412343014[12] = 0;
   out_146505656412343014[13] = 0;
   out_146505656412343014[14] = 1;
   out_146505656412343014[15] = 0;
   out_146505656412343014[16] = 0;
   out_146505656412343014[17] = 0;
}
void h_30(double *state, double *unused, double *out_7220280955406446863) {
   out_7220280955406446863[0] = state[4];
}
void H_30(double *state, double *unused, double *out_3505270399101636633) {
   out_3505270399101636633[0] = 0;
   out_3505270399101636633[1] = 0;
   out_3505270399101636633[2] = 0;
   out_3505270399101636633[3] = 0;
   out_3505270399101636633[4] = 1;
   out_3505270399101636633[5] = 0;
   out_3505270399101636633[6] = 0;
   out_3505270399101636633[7] = 0;
   out_3505270399101636633[8] = 0;
}
void h_26(double *state, double *unused, double *out_2218607687745601218) {
   out_2218607687745601218[0] = state[7];
}
void H_26(double *state, double *unused, double *out_7152923261264036346) {
   out_7152923261264036346[0] = 0;
   out_7152923261264036346[1] = 0;
   out_7152923261264036346[2] = 0;
   out_7152923261264036346[3] = 0;
   out_7152923261264036346[4] = 0;
   out_7152923261264036346[5] = 0;
   out_7152923261264036346[6] = 0;
   out_7152923261264036346[7] = 1;
   out_7152923261264036346[8] = 0;
}
void h_27(double *state, double *unused, double *out_6146075726688434777) {
   out_6146075726688434777[0] = state[3];
}
void H_27(double *state, double *unused, double *out_5715522201333645103) {
   out_5715522201333645103[0] = 0;
   out_5715522201333645103[1] = 0;
   out_5715522201333645103[2] = 0;
   out_5715522201333645103[3] = 1;
   out_5715522201333645103[4] = 0;
   out_5715522201333645103[5] = 0;
   out_5715522201333645103[6] = 0;
   out_5715522201333645103[7] = 0;
   out_5715522201333645103[8] = 0;
}
void h_29(double *state, double *unused, double *out_821239437992597717) {
   out_821239437992597717[0] = state[1];
}
void H_29(double *state, double *unused, double *out_3030527545218828008) {
   out_3030527545218828008[0] = 0;
   out_3030527545218828008[1] = 1;
   out_3030527545218828008[2] = 0;
   out_3030527545218828008[3] = 0;
   out_3030527545218828008[4] = 0;
   out_3030527545218828008[5] = 0;
   out_3030527545218828008[6] = 0;
   out_3030527545218828008[7] = 0;
   out_3030527545218828008[8] = 0;
}
void h_28(double *state, double *unused, double *out_7313819527764576514) {
   out_7313819527764576514[0] = state[0];
}
void H_28(double *state, double *unused, double *out_1066897273653501757) {
   out_1066897273653501757[0] = 1;
   out_1066897273653501757[1] = 0;
   out_1066897273653501757[2] = 0;
   out_1066897273653501757[3] = 0;
   out_1066897273653501757[4] = 0;
   out_1066897273653501757[5] = 0;
   out_1066897273653501757[6] = 0;
   out_1066897273653501757[7] = 0;
   out_1066897273653501757[8] = 0;
}
void h_31(double *state, double *unused, double *out_3437311602931769542) {
   out_3437311602931769542[0] = state[8];
}
void H_31(double *state, double *unused, double *out_3380773980513019694) {
   out_3380773980513019694[0] = 0;
   out_3380773980513019694[1] = 0;
   out_3380773980513019694[2] = 0;
   out_3380773980513019694[3] = 0;
   out_3380773980513019694[4] = 0;
   out_3380773980513019694[5] = 0;
   out_3380773980513019694[6] = 0;
   out_3380773980513019694[7] = 0;
   out_3380773980513019694[8] = 1;
}
#include <eigen3/Eigen/Dense>
#include <iostream>

typedef Eigen::Matrix<double, DIM, DIM, Eigen::RowMajor> DDM;
typedef Eigen::Matrix<double, EDIM, EDIM, Eigen::RowMajor> EEM;
typedef Eigen::Matrix<double, DIM, EDIM, Eigen::RowMajor> DEM;

void predict(double *in_x, double *in_P, double *in_Q, double dt) {
  typedef Eigen::Matrix<double, MEDIM, MEDIM, Eigen::RowMajor> RRM;

  double nx[DIM] = {0};
  double in_F[EDIM*EDIM] = {0};

  // functions from sympy
  f_fun(in_x, dt, nx);
  F_fun(in_x, dt, in_F);


  EEM F(in_F);
  EEM P(in_P);
  EEM Q(in_Q);

  RRM F_main = F.topLeftCorner(MEDIM, MEDIM);
  P.topLeftCorner(MEDIM, MEDIM) = (F_main * P.topLeftCorner(MEDIM, MEDIM)) * F_main.transpose();
  P.topRightCorner(MEDIM, EDIM - MEDIM) = F_main * P.topRightCorner(MEDIM, EDIM - MEDIM);
  P.bottomLeftCorner(EDIM - MEDIM, MEDIM) = P.bottomLeftCorner(EDIM - MEDIM, MEDIM) * F_main.transpose();

  P = P + dt*Q;

  // copy out state
  memcpy(in_x, nx, DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
}

// note: extra_args dim only correct when null space projecting
// otherwise 1
template <int ZDIM, int EADIM, bool MAHA_TEST>
void update(double *in_x, double *in_P, Hfun h_fun, Hfun H_fun, Hfun Hea_fun, double *in_z, double *in_R, double *in_ea, double MAHA_THRESHOLD) {
  typedef Eigen::Matrix<double, ZDIM, ZDIM, Eigen::RowMajor> ZZM;
  typedef Eigen::Matrix<double, ZDIM, DIM, Eigen::RowMajor> ZDM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, EDIM, Eigen::RowMajor> XEM;
  //typedef Eigen::Matrix<double, EDIM, ZDIM, Eigen::RowMajor> EZM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, 1> X1M;
  typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> XXM;

  double in_hx[ZDIM] = {0};
  double in_H[ZDIM * DIM] = {0};
  double in_H_mod[EDIM * DIM] = {0};
  double delta_x[EDIM] = {0};
  double x_new[DIM] = {0};


  // state x, P
  Eigen::Matrix<double, ZDIM, 1> z(in_z);
  EEM P(in_P);
  ZZM pre_R(in_R);

  // functions from sympy
  h_fun(in_x, in_ea, in_hx);
  H_fun(in_x, in_ea, in_H);
  ZDM pre_H(in_H);

  // get y (y = z - hx)
  Eigen::Matrix<double, ZDIM, 1> pre_y(in_hx); pre_y = z - pre_y;
  X1M y; XXM H; XXM R;
  if (Hea_fun){
    typedef Eigen::Matrix<double, ZDIM, EADIM, Eigen::RowMajor> ZAM;
    double in_Hea[ZDIM * EADIM] = {0};
    Hea_fun(in_x, in_ea, in_Hea);
    ZAM Hea(in_Hea);
    XXM A = Hea.transpose().fullPivLu().kernel();


    y = A.transpose() * pre_y;
    H = A.transpose() * pre_H;
    R = A.transpose() * pre_R * A;
  } else {
    y = pre_y;
    H = pre_H;
    R = pre_R;
  }
  // get modified H
  H_mod_fun(in_x, in_H_mod);
  DEM H_mod(in_H_mod);
  XEM H_err = H * H_mod;

  // Do mahalobis distance test
  if (MAHA_TEST){
    XXM a = (H_err * P * H_err.transpose() + R).inverse();
    double maha_dist = y.transpose() * a * y;
    if (maha_dist > MAHA_THRESHOLD){
      R = 1.0e16 * R;
    }
  }

  // Outlier resilient weighting
  double weight = 1;//(1.5)/(1 + y.squaredNorm()/R.sum());

  // kalman gains and I_KH
  XXM S = ((H_err * P) * H_err.transpose()) + R/weight;
  XEM KT = S.fullPivLu().solve(H_err * P.transpose());
  //EZM K = KT.transpose(); TODO: WHY DOES THIS NOT COMPILE?
  //EZM K = S.fullPivLu().solve(H_err * P.transpose()).transpose();
  //std::cout << "Here is the matrix rot:\n" << K << std::endl;
  EEM I_KH = Eigen::Matrix<double, EDIM, EDIM>::Identity() - (KT.transpose() * H_err);

  // update state by injecting dx
  Eigen::Matrix<double, EDIM, 1> dx(delta_x);
  dx  = (KT.transpose() * y);
  memcpy(delta_x, dx.data(), EDIM * sizeof(double));
  err_fun(in_x, delta_x, x_new);
  Eigen::Matrix<double, DIM, 1> x(x_new);

  // update cov
  P = ((I_KH * P) * I_KH.transpose()) + ((KT.transpose() * R) * KT);

  // copy out state
  memcpy(in_x, x.data(), DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
  memcpy(in_z, y.data(), y.rows() * sizeof(double));
}




}
extern "C" {

void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_25, H_25, NULL, in_z, in_R, in_ea, MAHA_THRESH_25);
}
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<2, 3, 0>(in_x, in_P, h_24, H_24, NULL, in_z, in_R, in_ea, MAHA_THRESH_24);
}
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_30, H_30, NULL, in_z, in_R, in_ea, MAHA_THRESH_30);
}
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_26, H_26, NULL, in_z, in_R, in_ea, MAHA_THRESH_26);
}
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_27, H_27, NULL, in_z, in_R, in_ea, MAHA_THRESH_27);
}
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_29, H_29, NULL, in_z, in_R, in_ea, MAHA_THRESH_29);
}
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_28, H_28, NULL, in_z, in_R, in_ea, MAHA_THRESH_28);
}
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_31, H_31, NULL, in_z, in_R, in_ea, MAHA_THRESH_31);
}
void car_err_fun(double *nom_x, double *delta_x, double *out_5817993247136894603) {
  err_fun(nom_x, delta_x, out_5817993247136894603);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_4344067570915274795) {
  inv_err_fun(nom_x, true_x, out_4344067570915274795);
}
void car_H_mod_fun(double *state, double *out_6934400592379471799) {
  H_mod_fun(state, out_6934400592379471799);
}
void car_f_fun(double *state, double dt, double *out_6508793848623948395) {
  f_fun(state,  dt, out_6508793848623948395);
}
void car_F_fun(double *state, double dt, double *out_5131722384156741838) {
  F_fun(state,  dt, out_5131722384156741838);
}
void car_h_25(double *state, double *unused, double *out_3280124934580640397) {
  h_25(state, unused, out_3280124934580640397);
}
void car_H_25(double *state, double *unused, double *out_3411419942389980122) {
  H_25(state, unused, out_3411419942389980122);
}
void car_h_24(double *state, double *unused, double *out_5847931756337679085) {
  h_24(state, unused, out_5847931756337679085);
}
void car_H_24(double *state, double *unused, double *out_146505656412343014) {
  H_24(state, unused, out_146505656412343014);
}
void car_h_30(double *state, double *unused, double *out_7220280955406446863) {
  h_30(state, unused, out_7220280955406446863);
}
void car_H_30(double *state, double *unused, double *out_3505270399101636633) {
  H_30(state, unused, out_3505270399101636633);
}
void car_h_26(double *state, double *unused, double *out_2218607687745601218) {
  h_26(state, unused, out_2218607687745601218);
}
void car_H_26(double *state, double *unused, double *out_7152923261264036346) {
  H_26(state, unused, out_7152923261264036346);
}
void car_h_27(double *state, double *unused, double *out_6146075726688434777) {
  h_27(state, unused, out_6146075726688434777);
}
void car_H_27(double *state, double *unused, double *out_5715522201333645103) {
  H_27(state, unused, out_5715522201333645103);
}
void car_h_29(double *state, double *unused, double *out_821239437992597717) {
  h_29(state, unused, out_821239437992597717);
}
void car_H_29(double *state, double *unused, double *out_3030527545218828008) {
  H_29(state, unused, out_3030527545218828008);
}
void car_h_28(double *state, double *unused, double *out_7313819527764576514) {
  h_28(state, unused, out_7313819527764576514);
}
void car_H_28(double *state, double *unused, double *out_1066897273653501757) {
  H_28(state, unused, out_1066897273653501757);
}
void car_h_31(double *state, double *unused, double *out_3437311602931769542) {
  h_31(state, unused, out_3437311602931769542);
}
void car_H_31(double *state, double *unused, double *out_3380773980513019694) {
  H_31(state, unused, out_3380773980513019694);
}
void car_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
void car_set_mass(double x) {
  set_mass(x);
}
void car_set_rotational_inertia(double x) {
  set_rotational_inertia(x);
}
void car_set_center_to_front(double x) {
  set_center_to_front(x);
}
void car_set_center_to_rear(double x) {
  set_center_to_rear(x);
}
void car_set_stiffness_front(double x) {
  set_stiffness_front(x);
}
void car_set_stiffness_rear(double x) {
  set_stiffness_rear(x);
}
}

const EKF car = {
  .name = "car",
  .kinds = { 25, 24, 30, 26, 27, 29, 28, 31 },
  .feature_kinds = {  },
  .f_fun = car_f_fun,
  .F_fun = car_F_fun,
  .err_fun = car_err_fun,
  .inv_err_fun = car_inv_err_fun,
  .H_mod_fun = car_H_mod_fun,
  .predict = car_predict,
  .hs = {
    { 25, car_h_25 },
    { 24, car_h_24 },
    { 30, car_h_30 },
    { 26, car_h_26 },
    { 27, car_h_27 },
    { 29, car_h_29 },
    { 28, car_h_28 },
    { 31, car_h_31 },
  },
  .Hs = {
    { 25, car_H_25 },
    { 24, car_H_24 },
    { 30, car_H_30 },
    { 26, car_H_26 },
    { 27, car_H_27 },
    { 29, car_H_29 },
    { 28, car_H_28 },
    { 31, car_H_31 },
  },
  .updates = {
    { 25, car_update_25 },
    { 24, car_update_24 },
    { 30, car_update_30 },
    { 26, car_update_26 },
    { 27, car_update_27 },
    { 29, car_update_29 },
    { 28, car_update_28 },
    { 31, car_update_31 },
  },
  .Hes = {
  },
  .sets = {
    { "mass", car_set_mass },
    { "rotational_inertia", car_set_rotational_inertia },
    { "center_to_front", car_set_center_to_front },
    { "center_to_rear", car_set_center_to_rear },
    { "stiffness_front", car_set_stiffness_front },
    { "stiffness_rear", car_set_stiffness_rear },
  },
  .extra_routines = {
  },
};

ekf_lib_init(car)
