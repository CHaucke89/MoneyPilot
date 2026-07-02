#include "pose.h"

namespace {
#define DIM 18
#define EDIM 18
#define MEDIM 18
typedef void (*Hfun)(double *, double *, double *);
const static double MAHA_THRESH_4 = 7.814727903251177;
const static double MAHA_THRESH_10 = 7.814727903251177;
const static double MAHA_THRESH_13 = 7.814727903251177;
const static double MAHA_THRESH_14 = 7.814727903251177;

/******************************************************************************
 *                      Code generated with SymPy 1.14.0                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_2497164291072602752) {
   out_2497164291072602752[0] = delta_x[0] + nom_x[0];
   out_2497164291072602752[1] = delta_x[1] + nom_x[1];
   out_2497164291072602752[2] = delta_x[2] + nom_x[2];
   out_2497164291072602752[3] = delta_x[3] + nom_x[3];
   out_2497164291072602752[4] = delta_x[4] + nom_x[4];
   out_2497164291072602752[5] = delta_x[5] + nom_x[5];
   out_2497164291072602752[6] = delta_x[6] + nom_x[6];
   out_2497164291072602752[7] = delta_x[7] + nom_x[7];
   out_2497164291072602752[8] = delta_x[8] + nom_x[8];
   out_2497164291072602752[9] = delta_x[9] + nom_x[9];
   out_2497164291072602752[10] = delta_x[10] + nom_x[10];
   out_2497164291072602752[11] = delta_x[11] + nom_x[11];
   out_2497164291072602752[12] = delta_x[12] + nom_x[12];
   out_2497164291072602752[13] = delta_x[13] + nom_x[13];
   out_2497164291072602752[14] = delta_x[14] + nom_x[14];
   out_2497164291072602752[15] = delta_x[15] + nom_x[15];
   out_2497164291072602752[16] = delta_x[16] + nom_x[16];
   out_2497164291072602752[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_1094719228690614749) {
   out_1094719228690614749[0] = -nom_x[0] + true_x[0];
   out_1094719228690614749[1] = -nom_x[1] + true_x[1];
   out_1094719228690614749[2] = -nom_x[2] + true_x[2];
   out_1094719228690614749[3] = -nom_x[3] + true_x[3];
   out_1094719228690614749[4] = -nom_x[4] + true_x[4];
   out_1094719228690614749[5] = -nom_x[5] + true_x[5];
   out_1094719228690614749[6] = -nom_x[6] + true_x[6];
   out_1094719228690614749[7] = -nom_x[7] + true_x[7];
   out_1094719228690614749[8] = -nom_x[8] + true_x[8];
   out_1094719228690614749[9] = -nom_x[9] + true_x[9];
   out_1094719228690614749[10] = -nom_x[10] + true_x[10];
   out_1094719228690614749[11] = -nom_x[11] + true_x[11];
   out_1094719228690614749[12] = -nom_x[12] + true_x[12];
   out_1094719228690614749[13] = -nom_x[13] + true_x[13];
   out_1094719228690614749[14] = -nom_x[14] + true_x[14];
   out_1094719228690614749[15] = -nom_x[15] + true_x[15];
   out_1094719228690614749[16] = -nom_x[16] + true_x[16];
   out_1094719228690614749[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_2127076694835493224) {
   out_2127076694835493224[0] = 1.0;
   out_2127076694835493224[1] = 0.0;
   out_2127076694835493224[2] = 0.0;
   out_2127076694835493224[3] = 0.0;
   out_2127076694835493224[4] = 0.0;
   out_2127076694835493224[5] = 0.0;
   out_2127076694835493224[6] = 0.0;
   out_2127076694835493224[7] = 0.0;
   out_2127076694835493224[8] = 0.0;
   out_2127076694835493224[9] = 0.0;
   out_2127076694835493224[10] = 0.0;
   out_2127076694835493224[11] = 0.0;
   out_2127076694835493224[12] = 0.0;
   out_2127076694835493224[13] = 0.0;
   out_2127076694835493224[14] = 0.0;
   out_2127076694835493224[15] = 0.0;
   out_2127076694835493224[16] = 0.0;
   out_2127076694835493224[17] = 0.0;
   out_2127076694835493224[18] = 0.0;
   out_2127076694835493224[19] = 1.0;
   out_2127076694835493224[20] = 0.0;
   out_2127076694835493224[21] = 0.0;
   out_2127076694835493224[22] = 0.0;
   out_2127076694835493224[23] = 0.0;
   out_2127076694835493224[24] = 0.0;
   out_2127076694835493224[25] = 0.0;
   out_2127076694835493224[26] = 0.0;
   out_2127076694835493224[27] = 0.0;
   out_2127076694835493224[28] = 0.0;
   out_2127076694835493224[29] = 0.0;
   out_2127076694835493224[30] = 0.0;
   out_2127076694835493224[31] = 0.0;
   out_2127076694835493224[32] = 0.0;
   out_2127076694835493224[33] = 0.0;
   out_2127076694835493224[34] = 0.0;
   out_2127076694835493224[35] = 0.0;
   out_2127076694835493224[36] = 0.0;
   out_2127076694835493224[37] = 0.0;
   out_2127076694835493224[38] = 1.0;
   out_2127076694835493224[39] = 0.0;
   out_2127076694835493224[40] = 0.0;
   out_2127076694835493224[41] = 0.0;
   out_2127076694835493224[42] = 0.0;
   out_2127076694835493224[43] = 0.0;
   out_2127076694835493224[44] = 0.0;
   out_2127076694835493224[45] = 0.0;
   out_2127076694835493224[46] = 0.0;
   out_2127076694835493224[47] = 0.0;
   out_2127076694835493224[48] = 0.0;
   out_2127076694835493224[49] = 0.0;
   out_2127076694835493224[50] = 0.0;
   out_2127076694835493224[51] = 0.0;
   out_2127076694835493224[52] = 0.0;
   out_2127076694835493224[53] = 0.0;
   out_2127076694835493224[54] = 0.0;
   out_2127076694835493224[55] = 0.0;
   out_2127076694835493224[56] = 0.0;
   out_2127076694835493224[57] = 1.0;
   out_2127076694835493224[58] = 0.0;
   out_2127076694835493224[59] = 0.0;
   out_2127076694835493224[60] = 0.0;
   out_2127076694835493224[61] = 0.0;
   out_2127076694835493224[62] = 0.0;
   out_2127076694835493224[63] = 0.0;
   out_2127076694835493224[64] = 0.0;
   out_2127076694835493224[65] = 0.0;
   out_2127076694835493224[66] = 0.0;
   out_2127076694835493224[67] = 0.0;
   out_2127076694835493224[68] = 0.0;
   out_2127076694835493224[69] = 0.0;
   out_2127076694835493224[70] = 0.0;
   out_2127076694835493224[71] = 0.0;
   out_2127076694835493224[72] = 0.0;
   out_2127076694835493224[73] = 0.0;
   out_2127076694835493224[74] = 0.0;
   out_2127076694835493224[75] = 0.0;
   out_2127076694835493224[76] = 1.0;
   out_2127076694835493224[77] = 0.0;
   out_2127076694835493224[78] = 0.0;
   out_2127076694835493224[79] = 0.0;
   out_2127076694835493224[80] = 0.0;
   out_2127076694835493224[81] = 0.0;
   out_2127076694835493224[82] = 0.0;
   out_2127076694835493224[83] = 0.0;
   out_2127076694835493224[84] = 0.0;
   out_2127076694835493224[85] = 0.0;
   out_2127076694835493224[86] = 0.0;
   out_2127076694835493224[87] = 0.0;
   out_2127076694835493224[88] = 0.0;
   out_2127076694835493224[89] = 0.0;
   out_2127076694835493224[90] = 0.0;
   out_2127076694835493224[91] = 0.0;
   out_2127076694835493224[92] = 0.0;
   out_2127076694835493224[93] = 0.0;
   out_2127076694835493224[94] = 0.0;
   out_2127076694835493224[95] = 1.0;
   out_2127076694835493224[96] = 0.0;
   out_2127076694835493224[97] = 0.0;
   out_2127076694835493224[98] = 0.0;
   out_2127076694835493224[99] = 0.0;
   out_2127076694835493224[100] = 0.0;
   out_2127076694835493224[101] = 0.0;
   out_2127076694835493224[102] = 0.0;
   out_2127076694835493224[103] = 0.0;
   out_2127076694835493224[104] = 0.0;
   out_2127076694835493224[105] = 0.0;
   out_2127076694835493224[106] = 0.0;
   out_2127076694835493224[107] = 0.0;
   out_2127076694835493224[108] = 0.0;
   out_2127076694835493224[109] = 0.0;
   out_2127076694835493224[110] = 0.0;
   out_2127076694835493224[111] = 0.0;
   out_2127076694835493224[112] = 0.0;
   out_2127076694835493224[113] = 0.0;
   out_2127076694835493224[114] = 1.0;
   out_2127076694835493224[115] = 0.0;
   out_2127076694835493224[116] = 0.0;
   out_2127076694835493224[117] = 0.0;
   out_2127076694835493224[118] = 0.0;
   out_2127076694835493224[119] = 0.0;
   out_2127076694835493224[120] = 0.0;
   out_2127076694835493224[121] = 0.0;
   out_2127076694835493224[122] = 0.0;
   out_2127076694835493224[123] = 0.0;
   out_2127076694835493224[124] = 0.0;
   out_2127076694835493224[125] = 0.0;
   out_2127076694835493224[126] = 0.0;
   out_2127076694835493224[127] = 0.0;
   out_2127076694835493224[128] = 0.0;
   out_2127076694835493224[129] = 0.0;
   out_2127076694835493224[130] = 0.0;
   out_2127076694835493224[131] = 0.0;
   out_2127076694835493224[132] = 0.0;
   out_2127076694835493224[133] = 1.0;
   out_2127076694835493224[134] = 0.0;
   out_2127076694835493224[135] = 0.0;
   out_2127076694835493224[136] = 0.0;
   out_2127076694835493224[137] = 0.0;
   out_2127076694835493224[138] = 0.0;
   out_2127076694835493224[139] = 0.0;
   out_2127076694835493224[140] = 0.0;
   out_2127076694835493224[141] = 0.0;
   out_2127076694835493224[142] = 0.0;
   out_2127076694835493224[143] = 0.0;
   out_2127076694835493224[144] = 0.0;
   out_2127076694835493224[145] = 0.0;
   out_2127076694835493224[146] = 0.0;
   out_2127076694835493224[147] = 0.0;
   out_2127076694835493224[148] = 0.0;
   out_2127076694835493224[149] = 0.0;
   out_2127076694835493224[150] = 0.0;
   out_2127076694835493224[151] = 0.0;
   out_2127076694835493224[152] = 1.0;
   out_2127076694835493224[153] = 0.0;
   out_2127076694835493224[154] = 0.0;
   out_2127076694835493224[155] = 0.0;
   out_2127076694835493224[156] = 0.0;
   out_2127076694835493224[157] = 0.0;
   out_2127076694835493224[158] = 0.0;
   out_2127076694835493224[159] = 0.0;
   out_2127076694835493224[160] = 0.0;
   out_2127076694835493224[161] = 0.0;
   out_2127076694835493224[162] = 0.0;
   out_2127076694835493224[163] = 0.0;
   out_2127076694835493224[164] = 0.0;
   out_2127076694835493224[165] = 0.0;
   out_2127076694835493224[166] = 0.0;
   out_2127076694835493224[167] = 0.0;
   out_2127076694835493224[168] = 0.0;
   out_2127076694835493224[169] = 0.0;
   out_2127076694835493224[170] = 0.0;
   out_2127076694835493224[171] = 1.0;
   out_2127076694835493224[172] = 0.0;
   out_2127076694835493224[173] = 0.0;
   out_2127076694835493224[174] = 0.0;
   out_2127076694835493224[175] = 0.0;
   out_2127076694835493224[176] = 0.0;
   out_2127076694835493224[177] = 0.0;
   out_2127076694835493224[178] = 0.0;
   out_2127076694835493224[179] = 0.0;
   out_2127076694835493224[180] = 0.0;
   out_2127076694835493224[181] = 0.0;
   out_2127076694835493224[182] = 0.0;
   out_2127076694835493224[183] = 0.0;
   out_2127076694835493224[184] = 0.0;
   out_2127076694835493224[185] = 0.0;
   out_2127076694835493224[186] = 0.0;
   out_2127076694835493224[187] = 0.0;
   out_2127076694835493224[188] = 0.0;
   out_2127076694835493224[189] = 0.0;
   out_2127076694835493224[190] = 1.0;
   out_2127076694835493224[191] = 0.0;
   out_2127076694835493224[192] = 0.0;
   out_2127076694835493224[193] = 0.0;
   out_2127076694835493224[194] = 0.0;
   out_2127076694835493224[195] = 0.0;
   out_2127076694835493224[196] = 0.0;
   out_2127076694835493224[197] = 0.0;
   out_2127076694835493224[198] = 0.0;
   out_2127076694835493224[199] = 0.0;
   out_2127076694835493224[200] = 0.0;
   out_2127076694835493224[201] = 0.0;
   out_2127076694835493224[202] = 0.0;
   out_2127076694835493224[203] = 0.0;
   out_2127076694835493224[204] = 0.0;
   out_2127076694835493224[205] = 0.0;
   out_2127076694835493224[206] = 0.0;
   out_2127076694835493224[207] = 0.0;
   out_2127076694835493224[208] = 0.0;
   out_2127076694835493224[209] = 1.0;
   out_2127076694835493224[210] = 0.0;
   out_2127076694835493224[211] = 0.0;
   out_2127076694835493224[212] = 0.0;
   out_2127076694835493224[213] = 0.0;
   out_2127076694835493224[214] = 0.0;
   out_2127076694835493224[215] = 0.0;
   out_2127076694835493224[216] = 0.0;
   out_2127076694835493224[217] = 0.0;
   out_2127076694835493224[218] = 0.0;
   out_2127076694835493224[219] = 0.0;
   out_2127076694835493224[220] = 0.0;
   out_2127076694835493224[221] = 0.0;
   out_2127076694835493224[222] = 0.0;
   out_2127076694835493224[223] = 0.0;
   out_2127076694835493224[224] = 0.0;
   out_2127076694835493224[225] = 0.0;
   out_2127076694835493224[226] = 0.0;
   out_2127076694835493224[227] = 0.0;
   out_2127076694835493224[228] = 1.0;
   out_2127076694835493224[229] = 0.0;
   out_2127076694835493224[230] = 0.0;
   out_2127076694835493224[231] = 0.0;
   out_2127076694835493224[232] = 0.0;
   out_2127076694835493224[233] = 0.0;
   out_2127076694835493224[234] = 0.0;
   out_2127076694835493224[235] = 0.0;
   out_2127076694835493224[236] = 0.0;
   out_2127076694835493224[237] = 0.0;
   out_2127076694835493224[238] = 0.0;
   out_2127076694835493224[239] = 0.0;
   out_2127076694835493224[240] = 0.0;
   out_2127076694835493224[241] = 0.0;
   out_2127076694835493224[242] = 0.0;
   out_2127076694835493224[243] = 0.0;
   out_2127076694835493224[244] = 0.0;
   out_2127076694835493224[245] = 0.0;
   out_2127076694835493224[246] = 0.0;
   out_2127076694835493224[247] = 1.0;
   out_2127076694835493224[248] = 0.0;
   out_2127076694835493224[249] = 0.0;
   out_2127076694835493224[250] = 0.0;
   out_2127076694835493224[251] = 0.0;
   out_2127076694835493224[252] = 0.0;
   out_2127076694835493224[253] = 0.0;
   out_2127076694835493224[254] = 0.0;
   out_2127076694835493224[255] = 0.0;
   out_2127076694835493224[256] = 0.0;
   out_2127076694835493224[257] = 0.0;
   out_2127076694835493224[258] = 0.0;
   out_2127076694835493224[259] = 0.0;
   out_2127076694835493224[260] = 0.0;
   out_2127076694835493224[261] = 0.0;
   out_2127076694835493224[262] = 0.0;
   out_2127076694835493224[263] = 0.0;
   out_2127076694835493224[264] = 0.0;
   out_2127076694835493224[265] = 0.0;
   out_2127076694835493224[266] = 1.0;
   out_2127076694835493224[267] = 0.0;
   out_2127076694835493224[268] = 0.0;
   out_2127076694835493224[269] = 0.0;
   out_2127076694835493224[270] = 0.0;
   out_2127076694835493224[271] = 0.0;
   out_2127076694835493224[272] = 0.0;
   out_2127076694835493224[273] = 0.0;
   out_2127076694835493224[274] = 0.0;
   out_2127076694835493224[275] = 0.0;
   out_2127076694835493224[276] = 0.0;
   out_2127076694835493224[277] = 0.0;
   out_2127076694835493224[278] = 0.0;
   out_2127076694835493224[279] = 0.0;
   out_2127076694835493224[280] = 0.0;
   out_2127076694835493224[281] = 0.0;
   out_2127076694835493224[282] = 0.0;
   out_2127076694835493224[283] = 0.0;
   out_2127076694835493224[284] = 0.0;
   out_2127076694835493224[285] = 1.0;
   out_2127076694835493224[286] = 0.0;
   out_2127076694835493224[287] = 0.0;
   out_2127076694835493224[288] = 0.0;
   out_2127076694835493224[289] = 0.0;
   out_2127076694835493224[290] = 0.0;
   out_2127076694835493224[291] = 0.0;
   out_2127076694835493224[292] = 0.0;
   out_2127076694835493224[293] = 0.0;
   out_2127076694835493224[294] = 0.0;
   out_2127076694835493224[295] = 0.0;
   out_2127076694835493224[296] = 0.0;
   out_2127076694835493224[297] = 0.0;
   out_2127076694835493224[298] = 0.0;
   out_2127076694835493224[299] = 0.0;
   out_2127076694835493224[300] = 0.0;
   out_2127076694835493224[301] = 0.0;
   out_2127076694835493224[302] = 0.0;
   out_2127076694835493224[303] = 0.0;
   out_2127076694835493224[304] = 1.0;
   out_2127076694835493224[305] = 0.0;
   out_2127076694835493224[306] = 0.0;
   out_2127076694835493224[307] = 0.0;
   out_2127076694835493224[308] = 0.0;
   out_2127076694835493224[309] = 0.0;
   out_2127076694835493224[310] = 0.0;
   out_2127076694835493224[311] = 0.0;
   out_2127076694835493224[312] = 0.0;
   out_2127076694835493224[313] = 0.0;
   out_2127076694835493224[314] = 0.0;
   out_2127076694835493224[315] = 0.0;
   out_2127076694835493224[316] = 0.0;
   out_2127076694835493224[317] = 0.0;
   out_2127076694835493224[318] = 0.0;
   out_2127076694835493224[319] = 0.0;
   out_2127076694835493224[320] = 0.0;
   out_2127076694835493224[321] = 0.0;
   out_2127076694835493224[322] = 0.0;
   out_2127076694835493224[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_5227450394252956779) {
   out_5227450394252956779[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_5227450394252956779[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_5227450394252956779[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_5227450394252956779[3] = dt*state[12] + state[3];
   out_5227450394252956779[4] = dt*state[13] + state[4];
   out_5227450394252956779[5] = dt*state[14] + state[5];
   out_5227450394252956779[6] = state[6];
   out_5227450394252956779[7] = state[7];
   out_5227450394252956779[8] = state[8];
   out_5227450394252956779[9] = state[9];
   out_5227450394252956779[10] = state[10];
   out_5227450394252956779[11] = state[11];
   out_5227450394252956779[12] = state[12];
   out_5227450394252956779[13] = state[13];
   out_5227450394252956779[14] = state[14];
   out_5227450394252956779[15] = state[15];
   out_5227450394252956779[16] = state[16];
   out_5227450394252956779[17] = state[17];
}
void F_fun(double *state, double dt, double *out_3158793123073568088) {
   out_3158793123073568088[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3158793123073568088[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3158793123073568088[2] = 0;
   out_3158793123073568088[3] = 0;
   out_3158793123073568088[4] = 0;
   out_3158793123073568088[5] = 0;
   out_3158793123073568088[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3158793123073568088[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3158793123073568088[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3158793123073568088[9] = 0;
   out_3158793123073568088[10] = 0;
   out_3158793123073568088[11] = 0;
   out_3158793123073568088[12] = 0;
   out_3158793123073568088[13] = 0;
   out_3158793123073568088[14] = 0;
   out_3158793123073568088[15] = 0;
   out_3158793123073568088[16] = 0;
   out_3158793123073568088[17] = 0;
   out_3158793123073568088[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3158793123073568088[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3158793123073568088[20] = 0;
   out_3158793123073568088[21] = 0;
   out_3158793123073568088[22] = 0;
   out_3158793123073568088[23] = 0;
   out_3158793123073568088[24] = 0;
   out_3158793123073568088[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3158793123073568088[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3158793123073568088[27] = 0;
   out_3158793123073568088[28] = 0;
   out_3158793123073568088[29] = 0;
   out_3158793123073568088[30] = 0;
   out_3158793123073568088[31] = 0;
   out_3158793123073568088[32] = 0;
   out_3158793123073568088[33] = 0;
   out_3158793123073568088[34] = 0;
   out_3158793123073568088[35] = 0;
   out_3158793123073568088[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3158793123073568088[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3158793123073568088[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3158793123073568088[39] = 0;
   out_3158793123073568088[40] = 0;
   out_3158793123073568088[41] = 0;
   out_3158793123073568088[42] = 0;
   out_3158793123073568088[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3158793123073568088[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3158793123073568088[45] = 0;
   out_3158793123073568088[46] = 0;
   out_3158793123073568088[47] = 0;
   out_3158793123073568088[48] = 0;
   out_3158793123073568088[49] = 0;
   out_3158793123073568088[50] = 0;
   out_3158793123073568088[51] = 0;
   out_3158793123073568088[52] = 0;
   out_3158793123073568088[53] = 0;
   out_3158793123073568088[54] = 0;
   out_3158793123073568088[55] = 0;
   out_3158793123073568088[56] = 0;
   out_3158793123073568088[57] = 1;
   out_3158793123073568088[58] = 0;
   out_3158793123073568088[59] = 0;
   out_3158793123073568088[60] = 0;
   out_3158793123073568088[61] = 0;
   out_3158793123073568088[62] = 0;
   out_3158793123073568088[63] = 0;
   out_3158793123073568088[64] = 0;
   out_3158793123073568088[65] = 0;
   out_3158793123073568088[66] = dt;
   out_3158793123073568088[67] = 0;
   out_3158793123073568088[68] = 0;
   out_3158793123073568088[69] = 0;
   out_3158793123073568088[70] = 0;
   out_3158793123073568088[71] = 0;
   out_3158793123073568088[72] = 0;
   out_3158793123073568088[73] = 0;
   out_3158793123073568088[74] = 0;
   out_3158793123073568088[75] = 0;
   out_3158793123073568088[76] = 1;
   out_3158793123073568088[77] = 0;
   out_3158793123073568088[78] = 0;
   out_3158793123073568088[79] = 0;
   out_3158793123073568088[80] = 0;
   out_3158793123073568088[81] = 0;
   out_3158793123073568088[82] = 0;
   out_3158793123073568088[83] = 0;
   out_3158793123073568088[84] = 0;
   out_3158793123073568088[85] = dt;
   out_3158793123073568088[86] = 0;
   out_3158793123073568088[87] = 0;
   out_3158793123073568088[88] = 0;
   out_3158793123073568088[89] = 0;
   out_3158793123073568088[90] = 0;
   out_3158793123073568088[91] = 0;
   out_3158793123073568088[92] = 0;
   out_3158793123073568088[93] = 0;
   out_3158793123073568088[94] = 0;
   out_3158793123073568088[95] = 1;
   out_3158793123073568088[96] = 0;
   out_3158793123073568088[97] = 0;
   out_3158793123073568088[98] = 0;
   out_3158793123073568088[99] = 0;
   out_3158793123073568088[100] = 0;
   out_3158793123073568088[101] = 0;
   out_3158793123073568088[102] = 0;
   out_3158793123073568088[103] = 0;
   out_3158793123073568088[104] = dt;
   out_3158793123073568088[105] = 0;
   out_3158793123073568088[106] = 0;
   out_3158793123073568088[107] = 0;
   out_3158793123073568088[108] = 0;
   out_3158793123073568088[109] = 0;
   out_3158793123073568088[110] = 0;
   out_3158793123073568088[111] = 0;
   out_3158793123073568088[112] = 0;
   out_3158793123073568088[113] = 0;
   out_3158793123073568088[114] = 1;
   out_3158793123073568088[115] = 0;
   out_3158793123073568088[116] = 0;
   out_3158793123073568088[117] = 0;
   out_3158793123073568088[118] = 0;
   out_3158793123073568088[119] = 0;
   out_3158793123073568088[120] = 0;
   out_3158793123073568088[121] = 0;
   out_3158793123073568088[122] = 0;
   out_3158793123073568088[123] = 0;
   out_3158793123073568088[124] = 0;
   out_3158793123073568088[125] = 0;
   out_3158793123073568088[126] = 0;
   out_3158793123073568088[127] = 0;
   out_3158793123073568088[128] = 0;
   out_3158793123073568088[129] = 0;
   out_3158793123073568088[130] = 0;
   out_3158793123073568088[131] = 0;
   out_3158793123073568088[132] = 0;
   out_3158793123073568088[133] = 1;
   out_3158793123073568088[134] = 0;
   out_3158793123073568088[135] = 0;
   out_3158793123073568088[136] = 0;
   out_3158793123073568088[137] = 0;
   out_3158793123073568088[138] = 0;
   out_3158793123073568088[139] = 0;
   out_3158793123073568088[140] = 0;
   out_3158793123073568088[141] = 0;
   out_3158793123073568088[142] = 0;
   out_3158793123073568088[143] = 0;
   out_3158793123073568088[144] = 0;
   out_3158793123073568088[145] = 0;
   out_3158793123073568088[146] = 0;
   out_3158793123073568088[147] = 0;
   out_3158793123073568088[148] = 0;
   out_3158793123073568088[149] = 0;
   out_3158793123073568088[150] = 0;
   out_3158793123073568088[151] = 0;
   out_3158793123073568088[152] = 1;
   out_3158793123073568088[153] = 0;
   out_3158793123073568088[154] = 0;
   out_3158793123073568088[155] = 0;
   out_3158793123073568088[156] = 0;
   out_3158793123073568088[157] = 0;
   out_3158793123073568088[158] = 0;
   out_3158793123073568088[159] = 0;
   out_3158793123073568088[160] = 0;
   out_3158793123073568088[161] = 0;
   out_3158793123073568088[162] = 0;
   out_3158793123073568088[163] = 0;
   out_3158793123073568088[164] = 0;
   out_3158793123073568088[165] = 0;
   out_3158793123073568088[166] = 0;
   out_3158793123073568088[167] = 0;
   out_3158793123073568088[168] = 0;
   out_3158793123073568088[169] = 0;
   out_3158793123073568088[170] = 0;
   out_3158793123073568088[171] = 1;
   out_3158793123073568088[172] = 0;
   out_3158793123073568088[173] = 0;
   out_3158793123073568088[174] = 0;
   out_3158793123073568088[175] = 0;
   out_3158793123073568088[176] = 0;
   out_3158793123073568088[177] = 0;
   out_3158793123073568088[178] = 0;
   out_3158793123073568088[179] = 0;
   out_3158793123073568088[180] = 0;
   out_3158793123073568088[181] = 0;
   out_3158793123073568088[182] = 0;
   out_3158793123073568088[183] = 0;
   out_3158793123073568088[184] = 0;
   out_3158793123073568088[185] = 0;
   out_3158793123073568088[186] = 0;
   out_3158793123073568088[187] = 0;
   out_3158793123073568088[188] = 0;
   out_3158793123073568088[189] = 0;
   out_3158793123073568088[190] = 1;
   out_3158793123073568088[191] = 0;
   out_3158793123073568088[192] = 0;
   out_3158793123073568088[193] = 0;
   out_3158793123073568088[194] = 0;
   out_3158793123073568088[195] = 0;
   out_3158793123073568088[196] = 0;
   out_3158793123073568088[197] = 0;
   out_3158793123073568088[198] = 0;
   out_3158793123073568088[199] = 0;
   out_3158793123073568088[200] = 0;
   out_3158793123073568088[201] = 0;
   out_3158793123073568088[202] = 0;
   out_3158793123073568088[203] = 0;
   out_3158793123073568088[204] = 0;
   out_3158793123073568088[205] = 0;
   out_3158793123073568088[206] = 0;
   out_3158793123073568088[207] = 0;
   out_3158793123073568088[208] = 0;
   out_3158793123073568088[209] = 1;
   out_3158793123073568088[210] = 0;
   out_3158793123073568088[211] = 0;
   out_3158793123073568088[212] = 0;
   out_3158793123073568088[213] = 0;
   out_3158793123073568088[214] = 0;
   out_3158793123073568088[215] = 0;
   out_3158793123073568088[216] = 0;
   out_3158793123073568088[217] = 0;
   out_3158793123073568088[218] = 0;
   out_3158793123073568088[219] = 0;
   out_3158793123073568088[220] = 0;
   out_3158793123073568088[221] = 0;
   out_3158793123073568088[222] = 0;
   out_3158793123073568088[223] = 0;
   out_3158793123073568088[224] = 0;
   out_3158793123073568088[225] = 0;
   out_3158793123073568088[226] = 0;
   out_3158793123073568088[227] = 0;
   out_3158793123073568088[228] = 1;
   out_3158793123073568088[229] = 0;
   out_3158793123073568088[230] = 0;
   out_3158793123073568088[231] = 0;
   out_3158793123073568088[232] = 0;
   out_3158793123073568088[233] = 0;
   out_3158793123073568088[234] = 0;
   out_3158793123073568088[235] = 0;
   out_3158793123073568088[236] = 0;
   out_3158793123073568088[237] = 0;
   out_3158793123073568088[238] = 0;
   out_3158793123073568088[239] = 0;
   out_3158793123073568088[240] = 0;
   out_3158793123073568088[241] = 0;
   out_3158793123073568088[242] = 0;
   out_3158793123073568088[243] = 0;
   out_3158793123073568088[244] = 0;
   out_3158793123073568088[245] = 0;
   out_3158793123073568088[246] = 0;
   out_3158793123073568088[247] = 1;
   out_3158793123073568088[248] = 0;
   out_3158793123073568088[249] = 0;
   out_3158793123073568088[250] = 0;
   out_3158793123073568088[251] = 0;
   out_3158793123073568088[252] = 0;
   out_3158793123073568088[253] = 0;
   out_3158793123073568088[254] = 0;
   out_3158793123073568088[255] = 0;
   out_3158793123073568088[256] = 0;
   out_3158793123073568088[257] = 0;
   out_3158793123073568088[258] = 0;
   out_3158793123073568088[259] = 0;
   out_3158793123073568088[260] = 0;
   out_3158793123073568088[261] = 0;
   out_3158793123073568088[262] = 0;
   out_3158793123073568088[263] = 0;
   out_3158793123073568088[264] = 0;
   out_3158793123073568088[265] = 0;
   out_3158793123073568088[266] = 1;
   out_3158793123073568088[267] = 0;
   out_3158793123073568088[268] = 0;
   out_3158793123073568088[269] = 0;
   out_3158793123073568088[270] = 0;
   out_3158793123073568088[271] = 0;
   out_3158793123073568088[272] = 0;
   out_3158793123073568088[273] = 0;
   out_3158793123073568088[274] = 0;
   out_3158793123073568088[275] = 0;
   out_3158793123073568088[276] = 0;
   out_3158793123073568088[277] = 0;
   out_3158793123073568088[278] = 0;
   out_3158793123073568088[279] = 0;
   out_3158793123073568088[280] = 0;
   out_3158793123073568088[281] = 0;
   out_3158793123073568088[282] = 0;
   out_3158793123073568088[283] = 0;
   out_3158793123073568088[284] = 0;
   out_3158793123073568088[285] = 1;
   out_3158793123073568088[286] = 0;
   out_3158793123073568088[287] = 0;
   out_3158793123073568088[288] = 0;
   out_3158793123073568088[289] = 0;
   out_3158793123073568088[290] = 0;
   out_3158793123073568088[291] = 0;
   out_3158793123073568088[292] = 0;
   out_3158793123073568088[293] = 0;
   out_3158793123073568088[294] = 0;
   out_3158793123073568088[295] = 0;
   out_3158793123073568088[296] = 0;
   out_3158793123073568088[297] = 0;
   out_3158793123073568088[298] = 0;
   out_3158793123073568088[299] = 0;
   out_3158793123073568088[300] = 0;
   out_3158793123073568088[301] = 0;
   out_3158793123073568088[302] = 0;
   out_3158793123073568088[303] = 0;
   out_3158793123073568088[304] = 1;
   out_3158793123073568088[305] = 0;
   out_3158793123073568088[306] = 0;
   out_3158793123073568088[307] = 0;
   out_3158793123073568088[308] = 0;
   out_3158793123073568088[309] = 0;
   out_3158793123073568088[310] = 0;
   out_3158793123073568088[311] = 0;
   out_3158793123073568088[312] = 0;
   out_3158793123073568088[313] = 0;
   out_3158793123073568088[314] = 0;
   out_3158793123073568088[315] = 0;
   out_3158793123073568088[316] = 0;
   out_3158793123073568088[317] = 0;
   out_3158793123073568088[318] = 0;
   out_3158793123073568088[319] = 0;
   out_3158793123073568088[320] = 0;
   out_3158793123073568088[321] = 0;
   out_3158793123073568088[322] = 0;
   out_3158793123073568088[323] = 1;
}
void h_4(double *state, double *unused, double *out_6888673195313457642) {
   out_6888673195313457642[0] = state[6] + state[9];
   out_6888673195313457642[1] = state[7] + state[10];
   out_6888673195313457642[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_5327486595936963248) {
   out_5327486595936963248[0] = 0;
   out_5327486595936963248[1] = 0;
   out_5327486595936963248[2] = 0;
   out_5327486595936963248[3] = 0;
   out_5327486595936963248[4] = 0;
   out_5327486595936963248[5] = 0;
   out_5327486595936963248[6] = 1;
   out_5327486595936963248[7] = 0;
   out_5327486595936963248[8] = 0;
   out_5327486595936963248[9] = 1;
   out_5327486595936963248[10] = 0;
   out_5327486595936963248[11] = 0;
   out_5327486595936963248[12] = 0;
   out_5327486595936963248[13] = 0;
   out_5327486595936963248[14] = 0;
   out_5327486595936963248[15] = 0;
   out_5327486595936963248[16] = 0;
   out_5327486595936963248[17] = 0;
   out_5327486595936963248[18] = 0;
   out_5327486595936963248[19] = 0;
   out_5327486595936963248[20] = 0;
   out_5327486595936963248[21] = 0;
   out_5327486595936963248[22] = 0;
   out_5327486595936963248[23] = 0;
   out_5327486595936963248[24] = 0;
   out_5327486595936963248[25] = 1;
   out_5327486595936963248[26] = 0;
   out_5327486595936963248[27] = 0;
   out_5327486595936963248[28] = 1;
   out_5327486595936963248[29] = 0;
   out_5327486595936963248[30] = 0;
   out_5327486595936963248[31] = 0;
   out_5327486595936963248[32] = 0;
   out_5327486595936963248[33] = 0;
   out_5327486595936963248[34] = 0;
   out_5327486595936963248[35] = 0;
   out_5327486595936963248[36] = 0;
   out_5327486595936963248[37] = 0;
   out_5327486595936963248[38] = 0;
   out_5327486595936963248[39] = 0;
   out_5327486595936963248[40] = 0;
   out_5327486595936963248[41] = 0;
   out_5327486595936963248[42] = 0;
   out_5327486595936963248[43] = 0;
   out_5327486595936963248[44] = 1;
   out_5327486595936963248[45] = 0;
   out_5327486595936963248[46] = 0;
   out_5327486595936963248[47] = 1;
   out_5327486595936963248[48] = 0;
   out_5327486595936963248[49] = 0;
   out_5327486595936963248[50] = 0;
   out_5327486595936963248[51] = 0;
   out_5327486595936963248[52] = 0;
   out_5327486595936963248[53] = 0;
}
void h_10(double *state, double *unused, double *out_5671532680385375413) {
   out_5671532680385375413[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_5671532680385375413[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_5671532680385375413[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_6244754580400464959) {
   out_6244754580400464959[0] = 0;
   out_6244754580400464959[1] = 9.8100000000000005*cos(state[1]);
   out_6244754580400464959[2] = 0;
   out_6244754580400464959[3] = 0;
   out_6244754580400464959[4] = -state[8];
   out_6244754580400464959[5] = state[7];
   out_6244754580400464959[6] = 0;
   out_6244754580400464959[7] = state[5];
   out_6244754580400464959[8] = -state[4];
   out_6244754580400464959[9] = 0;
   out_6244754580400464959[10] = 0;
   out_6244754580400464959[11] = 0;
   out_6244754580400464959[12] = 1;
   out_6244754580400464959[13] = 0;
   out_6244754580400464959[14] = 0;
   out_6244754580400464959[15] = 1;
   out_6244754580400464959[16] = 0;
   out_6244754580400464959[17] = 0;
   out_6244754580400464959[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_6244754580400464959[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_6244754580400464959[20] = 0;
   out_6244754580400464959[21] = state[8];
   out_6244754580400464959[22] = 0;
   out_6244754580400464959[23] = -state[6];
   out_6244754580400464959[24] = -state[5];
   out_6244754580400464959[25] = 0;
   out_6244754580400464959[26] = state[3];
   out_6244754580400464959[27] = 0;
   out_6244754580400464959[28] = 0;
   out_6244754580400464959[29] = 0;
   out_6244754580400464959[30] = 0;
   out_6244754580400464959[31] = 1;
   out_6244754580400464959[32] = 0;
   out_6244754580400464959[33] = 0;
   out_6244754580400464959[34] = 1;
   out_6244754580400464959[35] = 0;
   out_6244754580400464959[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_6244754580400464959[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_6244754580400464959[38] = 0;
   out_6244754580400464959[39] = -state[7];
   out_6244754580400464959[40] = state[6];
   out_6244754580400464959[41] = 0;
   out_6244754580400464959[42] = state[4];
   out_6244754580400464959[43] = -state[3];
   out_6244754580400464959[44] = 0;
   out_6244754580400464959[45] = 0;
   out_6244754580400464959[46] = 0;
   out_6244754580400464959[47] = 0;
   out_6244754580400464959[48] = 0;
   out_6244754580400464959[49] = 0;
   out_6244754580400464959[50] = 1;
   out_6244754580400464959[51] = 0;
   out_6244754580400464959[52] = 0;
   out_6244754580400464959[53] = 1;
}
void h_13(double *state, double *unused, double *out_2016775626742602393) {
   out_2016775626742602393[0] = state[3];
   out_2016775626742602393[1] = state[4];
   out_2016775626742602393[2] = state[5];
}
void H_13(double *state, double *unused, double *out_2283144612379737681) {
   out_2283144612379737681[0] = 0;
   out_2283144612379737681[1] = 0;
   out_2283144612379737681[2] = 0;
   out_2283144612379737681[3] = 1;
   out_2283144612379737681[4] = 0;
   out_2283144612379737681[5] = 0;
   out_2283144612379737681[6] = 0;
   out_2283144612379737681[7] = 0;
   out_2283144612379737681[8] = 0;
   out_2283144612379737681[9] = 0;
   out_2283144612379737681[10] = 0;
   out_2283144612379737681[11] = 0;
   out_2283144612379737681[12] = 0;
   out_2283144612379737681[13] = 0;
   out_2283144612379737681[14] = 0;
   out_2283144612379737681[15] = 0;
   out_2283144612379737681[16] = 0;
   out_2283144612379737681[17] = 0;
   out_2283144612379737681[18] = 0;
   out_2283144612379737681[19] = 0;
   out_2283144612379737681[20] = 0;
   out_2283144612379737681[21] = 0;
   out_2283144612379737681[22] = 1;
   out_2283144612379737681[23] = 0;
   out_2283144612379737681[24] = 0;
   out_2283144612379737681[25] = 0;
   out_2283144612379737681[26] = 0;
   out_2283144612379737681[27] = 0;
   out_2283144612379737681[28] = 0;
   out_2283144612379737681[29] = 0;
   out_2283144612379737681[30] = 0;
   out_2283144612379737681[31] = 0;
   out_2283144612379737681[32] = 0;
   out_2283144612379737681[33] = 0;
   out_2283144612379737681[34] = 0;
   out_2283144612379737681[35] = 0;
   out_2283144612379737681[36] = 0;
   out_2283144612379737681[37] = 0;
   out_2283144612379737681[38] = 0;
   out_2283144612379737681[39] = 0;
   out_2283144612379737681[40] = 0;
   out_2283144612379737681[41] = 1;
   out_2283144612379737681[42] = 0;
   out_2283144612379737681[43] = 0;
   out_2283144612379737681[44] = 0;
   out_2283144612379737681[45] = 0;
   out_2283144612379737681[46] = 0;
   out_2283144612379737681[47] = 0;
   out_2283144612379737681[48] = 0;
   out_2283144612379737681[49] = 0;
   out_2283144612379737681[50] = 0;
   out_2283144612379737681[51] = 0;
   out_2283144612379737681[52] = 0;
   out_2283144612379737681[53] = 0;
}
void h_14(double *state, double *unused, double *out_2832180890579824390) {
   out_2832180890579824390[0] = state[6];
   out_2832180890579824390[1] = state[7];
   out_2832180890579824390[2] = state[8];
}
void H_14(double *state, double *unused, double *out_1364245739597478719) {
   out_1364245739597478719[0] = 0;
   out_1364245739597478719[1] = 0;
   out_1364245739597478719[2] = 0;
   out_1364245739597478719[3] = 0;
   out_1364245739597478719[4] = 0;
   out_1364245739597478719[5] = 0;
   out_1364245739597478719[6] = 1;
   out_1364245739597478719[7] = 0;
   out_1364245739597478719[8] = 0;
   out_1364245739597478719[9] = 0;
   out_1364245739597478719[10] = 0;
   out_1364245739597478719[11] = 0;
   out_1364245739597478719[12] = 0;
   out_1364245739597478719[13] = 0;
   out_1364245739597478719[14] = 0;
   out_1364245739597478719[15] = 0;
   out_1364245739597478719[16] = 0;
   out_1364245739597478719[17] = 0;
   out_1364245739597478719[18] = 0;
   out_1364245739597478719[19] = 0;
   out_1364245739597478719[20] = 0;
   out_1364245739597478719[21] = 0;
   out_1364245739597478719[22] = 0;
   out_1364245739597478719[23] = 0;
   out_1364245739597478719[24] = 0;
   out_1364245739597478719[25] = 1;
   out_1364245739597478719[26] = 0;
   out_1364245739597478719[27] = 0;
   out_1364245739597478719[28] = 0;
   out_1364245739597478719[29] = 0;
   out_1364245739597478719[30] = 0;
   out_1364245739597478719[31] = 0;
   out_1364245739597478719[32] = 0;
   out_1364245739597478719[33] = 0;
   out_1364245739597478719[34] = 0;
   out_1364245739597478719[35] = 0;
   out_1364245739597478719[36] = 0;
   out_1364245739597478719[37] = 0;
   out_1364245739597478719[38] = 0;
   out_1364245739597478719[39] = 0;
   out_1364245739597478719[40] = 0;
   out_1364245739597478719[41] = 0;
   out_1364245739597478719[42] = 0;
   out_1364245739597478719[43] = 0;
   out_1364245739597478719[44] = 1;
   out_1364245739597478719[45] = 0;
   out_1364245739597478719[46] = 0;
   out_1364245739597478719[47] = 0;
   out_1364245739597478719[48] = 0;
   out_1364245739597478719[49] = 0;
   out_1364245739597478719[50] = 0;
   out_1364245739597478719[51] = 0;
   out_1364245739597478719[52] = 0;
   out_1364245739597478719[53] = 0;
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

void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_4, H_4, NULL, in_z, in_R, in_ea, MAHA_THRESH_4);
}
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_10, H_10, NULL, in_z, in_R, in_ea, MAHA_THRESH_10);
}
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_13, H_13, NULL, in_z, in_R, in_ea, MAHA_THRESH_13);
}
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_14, H_14, NULL, in_z, in_R, in_ea, MAHA_THRESH_14);
}
void pose_err_fun(double *nom_x, double *delta_x, double *out_2497164291072602752) {
  err_fun(nom_x, delta_x, out_2497164291072602752);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_1094719228690614749) {
  inv_err_fun(nom_x, true_x, out_1094719228690614749);
}
void pose_H_mod_fun(double *state, double *out_2127076694835493224) {
  H_mod_fun(state, out_2127076694835493224);
}
void pose_f_fun(double *state, double dt, double *out_5227450394252956779) {
  f_fun(state,  dt, out_5227450394252956779);
}
void pose_F_fun(double *state, double dt, double *out_3158793123073568088) {
  F_fun(state,  dt, out_3158793123073568088);
}
void pose_h_4(double *state, double *unused, double *out_6888673195313457642) {
  h_4(state, unused, out_6888673195313457642);
}
void pose_H_4(double *state, double *unused, double *out_5327486595936963248) {
  H_4(state, unused, out_5327486595936963248);
}
void pose_h_10(double *state, double *unused, double *out_5671532680385375413) {
  h_10(state, unused, out_5671532680385375413);
}
void pose_H_10(double *state, double *unused, double *out_6244754580400464959) {
  H_10(state, unused, out_6244754580400464959);
}
void pose_h_13(double *state, double *unused, double *out_2016775626742602393) {
  h_13(state, unused, out_2016775626742602393);
}
void pose_H_13(double *state, double *unused, double *out_2283144612379737681) {
  H_13(state, unused, out_2283144612379737681);
}
void pose_h_14(double *state, double *unused, double *out_2832180890579824390) {
  h_14(state, unused, out_2832180890579824390);
}
void pose_H_14(double *state, double *unused, double *out_1364245739597478719) {
  H_14(state, unused, out_1364245739597478719);
}
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
}

const EKF pose = {
  .name = "pose",
  .kinds = { 4, 10, 13, 14 },
  .feature_kinds = {  },
  .f_fun = pose_f_fun,
  .F_fun = pose_F_fun,
  .err_fun = pose_err_fun,
  .inv_err_fun = pose_inv_err_fun,
  .H_mod_fun = pose_H_mod_fun,
  .predict = pose_predict,
  .hs = {
    { 4, pose_h_4 },
    { 10, pose_h_10 },
    { 13, pose_h_13 },
    { 14, pose_h_14 },
  },
  .Hs = {
    { 4, pose_H_4 },
    { 10, pose_H_10 },
    { 13, pose_H_13 },
    { 14, pose_H_14 },
  },
  .updates = {
    { 4, pose_update_4 },
    { 10, pose_update_10 },
    { 13, pose_update_13 },
    { 14, pose_update_14 },
  },
  .Hes = {
  },
  .sets = {
  },
  .extra_routines = {
  },
};

ekf_lib_init(pose)
