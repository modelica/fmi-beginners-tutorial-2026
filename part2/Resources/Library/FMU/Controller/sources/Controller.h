/*
 * Controller.h
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

#ifndef RTW_HEADER_Controller_h_
#define RTW_HEADER_Controller_h_
#ifndef Controller_COMMON_INCLUDES_
#define Controller_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* Controller_COMMON_INCLUDES_ */

#include "Controller_types.h"
#include <string.h>

/* Macros for accessing real-time model data structure */
#ifndef rtmGetContStateDisabled
#define rtmGetContStateDisabled(rtm)   ((rtm)->contStateDisabled)
#endif

#ifndef rtmSetContStateDisabled
#define rtmSetContStateDisabled(rtm, val) ((rtm)->contStateDisabled = (val))
#endif

#ifndef rtmGetContStates
#define rtmGetContStates(rtm)          ((rtm)->contStates)
#endif

#ifndef rtmSetContStates
#define rtmSetContStates(rtm, val)     ((rtm)->contStates = (val))
#endif

#ifndef rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag
#define rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm) ((rtm)->CTOutputIncnstWithState)
#endif

#ifndef rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag
#define rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm, val) ((rtm)->CTOutputIncnstWithState = (val))
#endif

#ifndef rtmGetDerivCacheNeedsReset
#define rtmGetDerivCacheNeedsReset(rtm) ((rtm)->derivCacheNeedsReset)
#endif

#ifndef rtmSetDerivCacheNeedsReset
#define rtmSetDerivCacheNeedsReset(rtm, val) ((rtm)->derivCacheNeedsReset = (val))
#endif

#ifndef rtmGetIntgData
#define rtmGetIntgData(rtm)            ((rtm)->intgData)
#endif

#ifndef rtmSetIntgData
#define rtmSetIntgData(rtm, val)       ((rtm)->intgData = (val))
#endif

#ifndef rtmGetOdeF
#define rtmGetOdeF(rtm)                ((rtm)->odeF)
#endif

#ifndef rtmSetOdeF
#define rtmSetOdeF(rtm, val)           ((rtm)->odeF = (val))
#endif

#ifndef rtmGetOdeY
#define rtmGetOdeY(rtm)                ((rtm)->odeY)
#endif

#ifndef rtmSetOdeY
#define rtmSetOdeY(rtm, val)           ((rtm)->odeY = (val))
#endif

#ifndef rtmGetPeriodicContStateIndices
#define rtmGetPeriodicContStateIndices(rtm) ((rtm)->periodicContStateIndices)
#endif

#ifndef rtmSetPeriodicContStateIndices
#define rtmSetPeriodicContStateIndices(rtm, val) ((rtm)->periodicContStateIndices = (val))
#endif

#ifndef rtmGetPeriodicContStateRanges
#define rtmGetPeriodicContStateRanges(rtm) ((rtm)->periodicContStateRanges)
#endif

#ifndef rtmSetPeriodicContStateRanges
#define rtmSetPeriodicContStateRanges(rtm, val) ((rtm)->periodicContStateRanges = (val))
#endif

#ifndef rtmGetZCCacheNeedsReset
#define rtmGetZCCacheNeedsReset(rtm)   ((rtm)->zCCacheNeedsReset)
#endif

#ifndef rtmSetZCCacheNeedsReset
#define rtmSetZCCacheNeedsReset(rtm, val) ((rtm)->zCCacheNeedsReset = (val))
#endif

#ifndef rtmGetdX
#define rtmGetdX(rtm)                  ((rtm)->derivs)
#endif

#ifndef rtmSetdX
#define rtmSetdX(rtm, val)             ((rtm)->derivs = (val))
#endif

#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

/* Block signals (default storage) */
typedef struct {
  real_T FilterCoefficient;            /* '<S36>/Filter Coefficient' */
  real_T IntegralGain;                 /* '<S30>/Integral Gain' */
} B_Controller_T;

/* Continuous states (default storage) */
typedef struct {
  real_T Integrator_CSTATE;            /* '<S33>/Integrator' */
  real_T Filter_CSTATE;                /* '<S28>/Filter' */
} X_Controller_T;

/* State derivatives (default storage) */
typedef struct {
  real_T Integrator_CSTATE;            /* '<S33>/Integrator' */
  real_T Filter_CSTATE;                /* '<S28>/Filter' */
} XDot_Controller_T;

/* State disabled  */
typedef struct {
  boolean_T Integrator_CSTATE;         /* '<S33>/Integrator' */
  boolean_T Filter_CSTATE;             /* '<S28>/Filter' */
} XDis_Controller_T;

#ifndef ODE3_INTG
#define ODE3_INTG

/* ODE3 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[3];                        /* derivatives */
} ODE3_IntgData;

#endif

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T w_desired;                    /* '<Root>/w_desired' */
  real_T w;                            /* '<Root>/w' */
} ExtU_Controller_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T v;                            /* '<Root>/v' */
} ExtY_Controller_T;

/* Parameters (default storage) */
struct P_Controller_T_ {
  real_T PIDController_D;              /* Mask Parameter: PIDController_D
                                        * Referenced by: '<S27>/Derivative Gain'
                                        */
  real_T PIDController_I;              /* Mask Parameter: PIDController_I
                                        * Referenced by: '<S30>/Integral Gain'
                                        */
  real_T PIDController_InitialConditionF;
                              /* Mask Parameter: PIDController_InitialConditionF
                               * Referenced by: '<S28>/Filter'
                               */
  real_T PIDController_InitialConditio_c;
                              /* Mask Parameter: PIDController_InitialConditio_c
                               * Referenced by: '<S33>/Integrator'
                               */
  real_T PIDController_N;              /* Mask Parameter: PIDController_N
                                        * Referenced by: '<S36>/Filter Coefficient'
                                        */
  real_T PIDController_P;              /* Mask Parameter: PIDController_P
                                        * Referenced by: '<S38>/Proportional Gain'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_Controller_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X_Controller_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  XDis_Controller_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeY[2];
  real_T odeF[3][2];
  ODE3_IntgData intgData;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numSampTimes;
  } Sizes;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    uint32_T clockTick1;
    uint32_T clockTickH1;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Block parameters (default storage) */
extern P_Controller_T Controller_P;

/* Block signals (default storage) */
extern B_Controller_T Controller_B;

/* Continuous states (default storage) */
extern X_Controller_T Controller_X;

/* External inputs (root inport signals with default storage) */
extern ExtU_Controller_T Controller_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_Controller_T Controller_Y;

/* Model entry point functions */
extern void Controller_initialize(void);
extern void Controller_step(void);
extern void Controller_terminate(void);

/* Real-time Model object */
extern RT_MODEL_Controller_T *const Controller_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Controller'
 * '<S1>'   : 'Controller/PID Controller'
 * '<S2>'   : 'Controller/PID Controller/Anti-windup'
 * '<S3>'   : 'Controller/PID Controller/D Gain'
 * '<S4>'   : 'Controller/PID Controller/Filter'
 * '<S5>'   : 'Controller/PID Controller/Filter ICs'
 * '<S6>'   : 'Controller/PID Controller/I Gain'
 * '<S7>'   : 'Controller/PID Controller/Ideal P Gain'
 * '<S8>'   : 'Controller/PID Controller/Ideal P Gain Fdbk'
 * '<S9>'   : 'Controller/PID Controller/Integrator'
 * '<S10>'  : 'Controller/PID Controller/Integrator ICs'
 * '<S11>'  : 'Controller/PID Controller/N Copy'
 * '<S12>'  : 'Controller/PID Controller/N Gain'
 * '<S13>'  : 'Controller/PID Controller/P Copy'
 * '<S14>'  : 'Controller/PID Controller/Parallel P Gain'
 * '<S15>'  : 'Controller/PID Controller/Reset Signal'
 * '<S16>'  : 'Controller/PID Controller/Saturation'
 * '<S17>'  : 'Controller/PID Controller/Saturation Fdbk'
 * '<S18>'  : 'Controller/PID Controller/Sum'
 * '<S19>'  : 'Controller/PID Controller/Sum Fdbk'
 * '<S20>'  : 'Controller/PID Controller/Tracking Mode'
 * '<S21>'  : 'Controller/PID Controller/Tracking Mode Sum'
 * '<S22>'  : 'Controller/PID Controller/Tsamp - Integral'
 * '<S23>'  : 'Controller/PID Controller/Tsamp - Ngain'
 * '<S24>'  : 'Controller/PID Controller/postSat Signal'
 * '<S25>'  : 'Controller/PID Controller/preSat Signal'
 * '<S26>'  : 'Controller/PID Controller/Anti-windup/Passthrough'
 * '<S27>'  : 'Controller/PID Controller/D Gain/Internal Parameters'
 * '<S28>'  : 'Controller/PID Controller/Filter/Cont. Filter'
 * '<S29>'  : 'Controller/PID Controller/Filter ICs/Internal IC - Filter'
 * '<S30>'  : 'Controller/PID Controller/I Gain/Internal Parameters'
 * '<S31>'  : 'Controller/PID Controller/Ideal P Gain/Passthrough'
 * '<S32>'  : 'Controller/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S33>'  : 'Controller/PID Controller/Integrator/Continuous'
 * '<S34>'  : 'Controller/PID Controller/Integrator ICs/Internal IC'
 * '<S35>'  : 'Controller/PID Controller/N Copy/Disabled'
 * '<S36>'  : 'Controller/PID Controller/N Gain/Internal Parameters'
 * '<S37>'  : 'Controller/PID Controller/P Copy/Disabled'
 * '<S38>'  : 'Controller/PID Controller/Parallel P Gain/Internal Parameters'
 * '<S39>'  : 'Controller/PID Controller/Reset Signal/Disabled'
 * '<S40>'  : 'Controller/PID Controller/Saturation/Passthrough'
 * '<S41>'  : 'Controller/PID Controller/Saturation Fdbk/Disabled'
 * '<S42>'  : 'Controller/PID Controller/Sum/Sum_PID'
 * '<S43>'  : 'Controller/PID Controller/Sum Fdbk/Disabled'
 * '<S44>'  : 'Controller/PID Controller/Tracking Mode/Disabled'
 * '<S45>'  : 'Controller/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S46>'  : 'Controller/PID Controller/Tsamp - Integral/TsSignalSpecification'
 * '<S47>'  : 'Controller/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S48>'  : 'Controller/PID Controller/postSat Signal/Forward_Path'
 * '<S49>'  : 'Controller/PID Controller/preSat Signal/Forward_Path'
 */
#endif                                 /* RTW_HEADER_Controller_h_ */
