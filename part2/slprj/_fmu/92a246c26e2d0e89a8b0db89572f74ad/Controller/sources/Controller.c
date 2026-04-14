/*
 * Controller.c
 *
 * Third Party Support License -- for use only to support products
 * interfaced to MathWorks software under terms specified in your
 * company's restricted use license agreement.
 *
 * Code generation for model "Controller".
 *
 * Model version              : 16.10
 * Simulink Coder version : 9.9 (R2023a) 19-Nov-2022
 * C source code generated on : Mon Oct  9 07:21:40 2023
 *
 * Target selection: grtfmi.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Emulation hardware selection:
 *    Differs from embedded hardware (MATLAB Host)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Controller.h"
#include "rtwtypes.h"
#include "Controller_private.h"
#include <string.h>

/* Block signals (default storage) */
B_Controller_T Controller_B;

/* Continuous states */
X_Controller_T Controller_X;

/* External inputs (root inport signals with default storage) */
ExtU_Controller_T Controller_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_Controller_T Controller_Y;

/* Real-time model */
static RT_MODEL_Controller_T Controller_M_;
RT_MODEL_Controller_T *const Controller_M = &Controller_M_;

/*
 * This function updates continuous states using the ODE3 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  /* Solver Matrices */
  static const real_T rt_ODE3_A[3] = {
    1.0/2.0, 3.0/4.0, 1.0
  };

  static const real_T rt_ODE3_B[3][3] = {
    { 1.0/2.0, 0.0, 0.0 },

    { 0.0, 3.0/4.0, 0.0 },

    { 2.0/9.0, 1.0/3.0, 4.0/9.0 }
  };

  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE3_IntgData *id = (ODE3_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T hB[3];
  int_T i;
  int_T nXc = 2;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  Controller_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  Controller_step();
  Controller_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  Controller_step();
  Controller_derivatives();

  /* tnew = t + hA(3);
     ynew = y + f*hB(:,3); */
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE3_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, tnew);
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model step function */
void Controller_step(void)
{
  real_T rtb_Subtract;
  if (rtmIsMajorTimeStep(Controller_M)) {
    /* set solver stop time */
    if (!(Controller_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&Controller_M->solverInfo,
                            ((Controller_M->Timing.clockTickH0 + 1) *
        Controller_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&Controller_M->solverInfo,
                            ((Controller_M->Timing.clockTick0 + 1) *
        Controller_M->Timing.stepSize0 + Controller_M->Timing.clockTickH0 *
        Controller_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(Controller_M)) {
    Controller_M->Timing.t[0] = rtsiGetT(&Controller_M->solverInfo);
  }

  /* Sum: '<Root>/Subtract' incorporates:
   *  Inport: '<Root>/w'
   *  Inport: '<Root>/w_desired'
   */
  rtb_Subtract = Controller_U.w_desired - Controller_U.w;

  /* Gain: '<S36>/Filter Coefficient' incorporates:
   *  Gain: '<S27>/Derivative Gain'
   *  Integrator: '<S28>/Filter'
   *  Sum: '<S28>/SumD'
   */
  Controller_B.FilterCoefficient = (Controller_P.PIDController_D * rtb_Subtract
    - Controller_X.Filter_CSTATE) * Controller_P.PIDController_N;

  /* Outport: '<Root>/v' incorporates:
   *  Gain: '<S38>/Proportional Gain'
   *  Integrator: '<S33>/Integrator'
   *  Sum: '<S42>/Sum'
   */
  Controller_Y.v = (Controller_P.PIDController_P * rtb_Subtract +
                    Controller_X.Integrator_CSTATE) +
    Controller_B.FilterCoefficient;

  /* Gain: '<S30>/Integral Gain' */
  Controller_B.IntegralGain = Controller_P.PIDController_I * rtb_Subtract;
  if (rtmIsMajorTimeStep(Controller_M)) {
    rt_ertODEUpdateContinuousStates(&Controller_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++Controller_M->Timing.clockTick0)) {
      ++Controller_M->Timing.clockTickH0;
    }

    Controller_M->Timing.t[0] = rtsiGetSolverStopTime(&Controller_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.001s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.001, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       * Timer of this task consists of two 32 bit unsigned integers.
       * The two integers represent the low bits Timing.clockTick1 and the high bits
       * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
       */
      Controller_M->Timing.clockTick1++;
      if (!Controller_M->Timing.clockTick1) {
        Controller_M->Timing.clockTickH1++;
      }
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void Controller_derivatives(void)
{
  XDot_Controller_T *_rtXdot;
  _rtXdot = ((XDot_Controller_T *) Controller_M->derivs);

  /* Derivatives for Integrator: '<S33>/Integrator' */
  _rtXdot->Integrator_CSTATE = Controller_B.IntegralGain;

  /* Derivatives for Integrator: '<S28>/Filter' */
  _rtXdot->Filter_CSTATE = Controller_B.FilterCoefficient;
}

/* Model initialize function */
void Controller_initialize(void)
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)Controller_M, 0,
                sizeof(RT_MODEL_Controller_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&Controller_M->solverInfo,
                          &Controller_M->Timing.simTimeStep);
    rtsiSetTPtr(&Controller_M->solverInfo, &rtmGetTPtr(Controller_M));
    rtsiSetStepSizePtr(&Controller_M->solverInfo,
                       &Controller_M->Timing.stepSize0);
    rtsiSetdXPtr(&Controller_M->solverInfo, &Controller_M->derivs);
    rtsiSetContStatesPtr(&Controller_M->solverInfo, (real_T **)
                         &Controller_M->contStates);
    rtsiSetNumContStatesPtr(&Controller_M->solverInfo,
      &Controller_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&Controller_M->solverInfo,
      &Controller_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&Controller_M->solverInfo,
      &Controller_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&Controller_M->solverInfo,
      &Controller_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&Controller_M->solverInfo, (&rtmGetErrorStatus
      (Controller_M)));
    rtsiSetRTModelPtr(&Controller_M->solverInfo, Controller_M);
  }

  rtsiSetSimTimeStep(&Controller_M->solverInfo, MAJOR_TIME_STEP);
  Controller_M->intgData.y = Controller_M->odeY;
  Controller_M->intgData.f[0] = Controller_M->odeF[0];
  Controller_M->intgData.f[1] = Controller_M->odeF[1];
  Controller_M->intgData.f[2] = Controller_M->odeF[2];
  Controller_M->contStates = ((X_Controller_T *) &Controller_X);
  rtsiSetSolverData(&Controller_M->solverInfo, (void *)&Controller_M->intgData);
  rtsiSetIsMinorTimeStepWithModeChange(&Controller_M->solverInfo, false);
  rtsiSetSolverName(&Controller_M->solverInfo,"ode3");
  rtmSetTPtr(Controller_M, &Controller_M->Timing.tArray[0]);
  Controller_M->Timing.stepSize0 = 0.001;

  /* block I/O */
  (void) memset(((void *) &Controller_B), 0,
                sizeof(B_Controller_T));

  /* states (continuous) */
  {
    (void) memset((void *)&Controller_X, 0,
                  sizeof(X_Controller_T));
  }

  /* external inputs */
  (void)memset(&Controller_U, 0, sizeof(ExtU_Controller_T));

  /* external outputs */
  Controller_Y.v = 0.0;

  /* InitializeConditions for Integrator: '<S33>/Integrator' */
  Controller_X.Integrator_CSTATE = Controller_P.PIDController_InitialConditio_c;

  /* InitializeConditions for Integrator: '<S28>/Filter' */
  Controller_X.Filter_CSTATE = Controller_P.PIDController_InitialConditionF;
}

/* Model terminate function */
void Controller_terminate(void)
{
  /* (no terminate code required) */
}
