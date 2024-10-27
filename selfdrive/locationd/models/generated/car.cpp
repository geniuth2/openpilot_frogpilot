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
 *                       Code generated with SymPy 1.12                       *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_8094104599776805306) {
   out_8094104599776805306[0] = delta_x[0] + nom_x[0];
   out_8094104599776805306[1] = delta_x[1] + nom_x[1];
   out_8094104599776805306[2] = delta_x[2] + nom_x[2];
   out_8094104599776805306[3] = delta_x[3] + nom_x[3];
   out_8094104599776805306[4] = delta_x[4] + nom_x[4];
   out_8094104599776805306[5] = delta_x[5] + nom_x[5];
   out_8094104599776805306[6] = delta_x[6] + nom_x[6];
   out_8094104599776805306[7] = delta_x[7] + nom_x[7];
   out_8094104599776805306[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_5549016765179909407) {
   out_5549016765179909407[0] = -nom_x[0] + true_x[0];
   out_5549016765179909407[1] = -nom_x[1] + true_x[1];
   out_5549016765179909407[2] = -nom_x[2] + true_x[2];
   out_5549016765179909407[3] = -nom_x[3] + true_x[3];
   out_5549016765179909407[4] = -nom_x[4] + true_x[4];
   out_5549016765179909407[5] = -nom_x[5] + true_x[5];
   out_5549016765179909407[6] = -nom_x[6] + true_x[6];
   out_5549016765179909407[7] = -nom_x[7] + true_x[7];
   out_5549016765179909407[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_3853780626797894556) {
   out_3853780626797894556[0] = 1.0;
   out_3853780626797894556[1] = 0;
   out_3853780626797894556[2] = 0;
   out_3853780626797894556[3] = 0;
   out_3853780626797894556[4] = 0;
   out_3853780626797894556[5] = 0;
   out_3853780626797894556[6] = 0;
   out_3853780626797894556[7] = 0;
   out_3853780626797894556[8] = 0;
   out_3853780626797894556[9] = 0;
   out_3853780626797894556[10] = 1.0;
   out_3853780626797894556[11] = 0;
   out_3853780626797894556[12] = 0;
   out_3853780626797894556[13] = 0;
   out_3853780626797894556[14] = 0;
   out_3853780626797894556[15] = 0;
   out_3853780626797894556[16] = 0;
   out_3853780626797894556[17] = 0;
   out_3853780626797894556[18] = 0;
   out_3853780626797894556[19] = 0;
   out_3853780626797894556[20] = 1.0;
   out_3853780626797894556[21] = 0;
   out_3853780626797894556[22] = 0;
   out_3853780626797894556[23] = 0;
   out_3853780626797894556[24] = 0;
   out_3853780626797894556[25] = 0;
   out_3853780626797894556[26] = 0;
   out_3853780626797894556[27] = 0;
   out_3853780626797894556[28] = 0;
   out_3853780626797894556[29] = 0;
   out_3853780626797894556[30] = 1.0;
   out_3853780626797894556[31] = 0;
   out_3853780626797894556[32] = 0;
   out_3853780626797894556[33] = 0;
   out_3853780626797894556[34] = 0;
   out_3853780626797894556[35] = 0;
   out_3853780626797894556[36] = 0;
   out_3853780626797894556[37] = 0;
   out_3853780626797894556[38] = 0;
   out_3853780626797894556[39] = 0;
   out_3853780626797894556[40] = 1.0;
   out_3853780626797894556[41] = 0;
   out_3853780626797894556[42] = 0;
   out_3853780626797894556[43] = 0;
   out_3853780626797894556[44] = 0;
   out_3853780626797894556[45] = 0;
   out_3853780626797894556[46] = 0;
   out_3853780626797894556[47] = 0;
   out_3853780626797894556[48] = 0;
   out_3853780626797894556[49] = 0;
   out_3853780626797894556[50] = 1.0;
   out_3853780626797894556[51] = 0;
   out_3853780626797894556[52] = 0;
   out_3853780626797894556[53] = 0;
   out_3853780626797894556[54] = 0;
   out_3853780626797894556[55] = 0;
   out_3853780626797894556[56] = 0;
   out_3853780626797894556[57] = 0;
   out_3853780626797894556[58] = 0;
   out_3853780626797894556[59] = 0;
   out_3853780626797894556[60] = 1.0;
   out_3853780626797894556[61] = 0;
   out_3853780626797894556[62] = 0;
   out_3853780626797894556[63] = 0;
   out_3853780626797894556[64] = 0;
   out_3853780626797894556[65] = 0;
   out_3853780626797894556[66] = 0;
   out_3853780626797894556[67] = 0;
   out_3853780626797894556[68] = 0;
   out_3853780626797894556[69] = 0;
   out_3853780626797894556[70] = 1.0;
   out_3853780626797894556[71] = 0;
   out_3853780626797894556[72] = 0;
   out_3853780626797894556[73] = 0;
   out_3853780626797894556[74] = 0;
   out_3853780626797894556[75] = 0;
   out_3853780626797894556[76] = 0;
   out_3853780626797894556[77] = 0;
   out_3853780626797894556[78] = 0;
   out_3853780626797894556[79] = 0;
   out_3853780626797894556[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_8101463906996855955) {
   out_8101463906996855955[0] = state[0];
   out_8101463906996855955[1] = state[1];
   out_8101463906996855955[2] = state[2];
   out_8101463906996855955[3] = state[3];
   out_8101463906996855955[4] = state[4];
   out_8101463906996855955[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8000000000000007*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_8101463906996855955[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_8101463906996855955[7] = state[7];
   out_8101463906996855955[8] = state[8];
}
void F_fun(double *state, double dt, double *out_7694702356080664485) {
   out_7694702356080664485[0] = 1;
   out_7694702356080664485[1] = 0;
   out_7694702356080664485[2] = 0;
   out_7694702356080664485[3] = 0;
   out_7694702356080664485[4] = 0;
   out_7694702356080664485[5] = 0;
   out_7694702356080664485[6] = 0;
   out_7694702356080664485[7] = 0;
   out_7694702356080664485[8] = 0;
   out_7694702356080664485[9] = 0;
   out_7694702356080664485[10] = 1;
   out_7694702356080664485[11] = 0;
   out_7694702356080664485[12] = 0;
   out_7694702356080664485[13] = 0;
   out_7694702356080664485[14] = 0;
   out_7694702356080664485[15] = 0;
   out_7694702356080664485[16] = 0;
   out_7694702356080664485[17] = 0;
   out_7694702356080664485[18] = 0;
   out_7694702356080664485[19] = 0;
   out_7694702356080664485[20] = 1;
   out_7694702356080664485[21] = 0;
   out_7694702356080664485[22] = 0;
   out_7694702356080664485[23] = 0;
   out_7694702356080664485[24] = 0;
   out_7694702356080664485[25] = 0;
   out_7694702356080664485[26] = 0;
   out_7694702356080664485[27] = 0;
   out_7694702356080664485[28] = 0;
   out_7694702356080664485[29] = 0;
   out_7694702356080664485[30] = 1;
   out_7694702356080664485[31] = 0;
   out_7694702356080664485[32] = 0;
   out_7694702356080664485[33] = 0;
   out_7694702356080664485[34] = 0;
   out_7694702356080664485[35] = 0;
   out_7694702356080664485[36] = 0;
   out_7694702356080664485[37] = 0;
   out_7694702356080664485[38] = 0;
   out_7694702356080664485[39] = 0;
   out_7694702356080664485[40] = 1;
   out_7694702356080664485[41] = 0;
   out_7694702356080664485[42] = 0;
   out_7694702356080664485[43] = 0;
   out_7694702356080664485[44] = 0;
   out_7694702356080664485[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_7694702356080664485[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_7694702356080664485[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_7694702356080664485[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_7694702356080664485[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_7694702356080664485[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_7694702356080664485[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_7694702356080664485[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_7694702356080664485[53] = -9.8000000000000007*dt;
   out_7694702356080664485[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_7694702356080664485[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_7694702356080664485[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_7694702356080664485[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_7694702356080664485[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_7694702356080664485[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_7694702356080664485[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_7694702356080664485[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_7694702356080664485[62] = 0;
   out_7694702356080664485[63] = 0;
   out_7694702356080664485[64] = 0;
   out_7694702356080664485[65] = 0;
   out_7694702356080664485[66] = 0;
   out_7694702356080664485[67] = 0;
   out_7694702356080664485[68] = 0;
   out_7694702356080664485[69] = 0;
   out_7694702356080664485[70] = 1;
   out_7694702356080664485[71] = 0;
   out_7694702356080664485[72] = 0;
   out_7694702356080664485[73] = 0;
   out_7694702356080664485[74] = 0;
   out_7694702356080664485[75] = 0;
   out_7694702356080664485[76] = 0;
   out_7694702356080664485[77] = 0;
   out_7694702356080664485[78] = 0;
   out_7694702356080664485[79] = 0;
   out_7694702356080664485[80] = 1;
}
void h_25(double *state, double *unused, double *out_1351128205251177603) {
   out_1351128205251177603[0] = state[6];
}
void H_25(double *state, double *unused, double *out_4620114418909754511) {
   out_4620114418909754511[0] = 0;
   out_4620114418909754511[1] = 0;
   out_4620114418909754511[2] = 0;
   out_4620114418909754511[3] = 0;
   out_4620114418909754511[4] = 0;
   out_4620114418909754511[5] = 0;
   out_4620114418909754511[6] = 1;
   out_4620114418909754511[7] = 0;
   out_4620114418909754511[8] = 0;
}
void h_24(double *state, double *unused, double *out_3252677413596348784) {
   out_3252677413596348784[0] = state[4];
   out_3252677413596348784[1] = state[5];
}
void H_24(double *state, double *unused, double *out_4607950767159440714) {
   out_4607950767159440714[0] = 0;
   out_4607950767159440714[1] = 0;
   out_4607950767159440714[2] = 0;
   out_4607950767159440714[3] = 0;
   out_4607950767159440714[4] = 1;
   out_4607950767159440714[5] = 0;
   out_4607950767159440714[6] = 0;
   out_4607950767159440714[7] = 0;
   out_4607950767159440714[8] = 0;
   out_4607950767159440714[9] = 0;
   out_4607950767159440714[10] = 0;
   out_4607950767159440714[11] = 0;
   out_4607950767159440714[12] = 0;
   out_4607950767159440714[13] = 0;
   out_4607950767159440714[14] = 1;
   out_4607950767159440714[15] = 0;
   out_4607950767159440714[16] = 0;
   out_4607950767159440714[17] = 0;
}
void h_30(double *state, double *unused, double *out_8121963431601528539) {
   out_8121963431601528539[0] = state[4];
}
void H_30(double *state, double *unused, double *out_9147810749037362709) {
   out_9147810749037362709[0] = 0;
   out_9147810749037362709[1] = 0;
   out_9147810749037362709[2] = 0;
   out_9147810749037362709[3] = 0;
   out_9147810749037362709[4] = 1;
   out_9147810749037362709[5] = 0;
   out_9147810749037362709[6] = 0;
   out_9147810749037362709[7] = 0;
   out_9147810749037362709[8] = 0;
}
void h_26(double *state, double *unused, double *out_2780096195715497976) {
   out_2780096195715497976[0] = state[7];
}
void H_26(double *state, double *unused, double *out_8361617737783810735) {
   out_8361617737783810735[0] = 0;
   out_8361617737783810735[1] = 0;
   out_8361617737783810735[2] = 0;
   out_8361617737783810735[3] = 0;
   out_8361617737783810735[4] = 0;
   out_8361617737783810735[5] = 0;
   out_8361617737783810735[6] = 0;
   out_8361617737783810735[7] = 1;
   out_8361617737783810735[8] = 0;
}
void h_27(double *state, double *unused, double *out_3650545062409668042) {
   out_3650545062409668042[0] = state[3];
}
void H_27(double *state, double *unused, double *out_7124170012871763996) {
   out_7124170012871763996[0] = 0;
   out_7124170012871763996[1] = 0;
   out_7124170012871763996[2] = 0;
   out_7124170012871763996[3] = 1;
   out_7124170012871763996[4] = 0;
   out_7124170012871763996[5] = 0;
   out_7124170012871763996[6] = 0;
   out_7124170012871763996[7] = 0;
   out_7124170012871763996[8] = 0;
}
void h_29(double *state, double *unused, double *out_7287994590663690392) {
   out_7287994590663690392[0] = state[1];
}
void H_29(double *state, double *unused, double *out_8637579404722970525) {
   out_8637579404722970525[0] = 0;
   out_8637579404722970525[1] = 1;
   out_8637579404722970525[2] = 0;
   out_8637579404722970525[3] = 0;
   out_8637579404722970525[4] = 0;
   out_8637579404722970525[5] = 0;
   out_8637579404722970525[6] = 0;
   out_8637579404722970525[7] = 0;
   out_8637579404722970525[8] = 0;
}
void h_28(double *state, double *unused, double *out_613759010965335357) {
   out_613759010965335357[0] = state[0];
}
void H_28(double *state, double *unused, double *out_6673949133157644274) {
   out_6673949133157644274[0] = 1;
   out_6673949133157644274[1] = 0;
   out_6673949133157644274[2] = 0;
   out_6673949133157644274[3] = 0;
   out_6673949133157644274[4] = 0;
   out_6673949133157644274[5] = 0;
   out_6673949133157644274[6] = 0;
   out_6673949133157644274[7] = 0;
   out_6673949133157644274[8] = 0;
}
void h_31(double *state, double *unused, double *out_99503187377705564) {
   out_99503187377705564[0] = state[8];
}
void H_31(double *state, double *unused, double *out_8987825840017162211) {
   out_8987825840017162211[0] = 0;
   out_8987825840017162211[1] = 0;
   out_8987825840017162211[2] = 0;
   out_8987825840017162211[3] = 0;
   out_8987825840017162211[4] = 0;
   out_8987825840017162211[5] = 0;
   out_8987825840017162211[6] = 0;
   out_8987825840017162211[7] = 0;
   out_8987825840017162211[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_8094104599776805306) {
  err_fun(nom_x, delta_x, out_8094104599776805306);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_5549016765179909407) {
  inv_err_fun(nom_x, true_x, out_5549016765179909407);
}
void car_H_mod_fun(double *state, double *out_3853780626797894556) {
  H_mod_fun(state, out_3853780626797894556);
}
void car_f_fun(double *state, double dt, double *out_8101463906996855955) {
  f_fun(state,  dt, out_8101463906996855955);
}
void car_F_fun(double *state, double dt, double *out_7694702356080664485) {
  F_fun(state,  dt, out_7694702356080664485);
}
void car_h_25(double *state, double *unused, double *out_1351128205251177603) {
  h_25(state, unused, out_1351128205251177603);
}
void car_H_25(double *state, double *unused, double *out_4620114418909754511) {
  H_25(state, unused, out_4620114418909754511);
}
void car_h_24(double *state, double *unused, double *out_3252677413596348784) {
  h_24(state, unused, out_3252677413596348784);
}
void car_H_24(double *state, double *unused, double *out_4607950767159440714) {
  H_24(state, unused, out_4607950767159440714);
}
void car_h_30(double *state, double *unused, double *out_8121963431601528539) {
  h_30(state, unused, out_8121963431601528539);
}
void car_H_30(double *state, double *unused, double *out_9147810749037362709) {
  H_30(state, unused, out_9147810749037362709);
}
void car_h_26(double *state, double *unused, double *out_2780096195715497976) {
  h_26(state, unused, out_2780096195715497976);
}
void car_H_26(double *state, double *unused, double *out_8361617737783810735) {
  H_26(state, unused, out_8361617737783810735);
}
void car_h_27(double *state, double *unused, double *out_3650545062409668042) {
  h_27(state, unused, out_3650545062409668042);
}
void car_H_27(double *state, double *unused, double *out_7124170012871763996) {
  H_27(state, unused, out_7124170012871763996);
}
void car_h_29(double *state, double *unused, double *out_7287994590663690392) {
  h_29(state, unused, out_7287994590663690392);
}
void car_H_29(double *state, double *unused, double *out_8637579404722970525) {
  H_29(state, unused, out_8637579404722970525);
}
void car_h_28(double *state, double *unused, double *out_613759010965335357) {
  h_28(state, unused, out_613759010965335357);
}
void car_H_28(double *state, double *unused, double *out_6673949133157644274) {
  H_28(state, unused, out_6673949133157644274);
}
void car_h_31(double *state, double *unused, double *out_99503187377705564) {
  h_31(state, unused, out_99503187377705564);
}
void car_H_31(double *state, double *unused, double *out_8987825840017162211) {
  H_31(state, unused, out_8987825840017162211);
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
