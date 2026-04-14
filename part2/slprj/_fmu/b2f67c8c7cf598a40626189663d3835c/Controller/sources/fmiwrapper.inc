#include "simstruc_types.h"

#include "Controller.h"
#include "Controller_private.h"

typedef struct {
	BuiltInDTypeId dtypeID;
	size_t size;
	void* address;
} ModelVariable;

#ifndef NO_FMI_FUNCTION_PREFIX
#define FMI2_FUNCTION_PREFIX Controller_
#endif

#define MODEL_GUID       "{3224d720-7b21-417a-b138-5d5099f4b70d}"
#define MODEL            Controller
#define MODEL_INITIALIZE Controller_initialize
#define MODEL_STEP       Controller_step
#define MODEL_TERMINATE  Controller_terminate
#define RT_MDL_TYPE      RT_MODEL_Controller_T
#define STEP_SIZE        0.001
#define NUM_TASKS        1
#define NUM_SAMPLE_TIMES 2
#define FIRST_TASK_ID    1

/* since R2019a the block parameters are defined as extern */
#ifndef rtmGetDefaultParam
#define rtmGetDefaultParam(S) (&Controller_P)
#endif

/* Definitions for non-reusable models */
#define RT_MDL_INSTANCE     Controller_M
#define rtmGetU(S)          (&Controller_U)
#define rtmGetY(S)          (&Controller_Y)
#define rtmGetBlockIO(S)    (&Controller_B)

/* Parameters */
#define RT_MDL_P_T  P_Controller_T
#define RT_MDL_P    Controller_P

static void initializeModelVariables(RT_MDL_TYPE* S, ModelVariable modelVariables[]) {

    modelVariables[0].dtypeID = 0;
    modelVariables[0].size    = 0;
    modelVariables[0].address = &(rtmGetU(S)->w_desired);

    modelVariables[1].dtypeID = 0;
    modelVariables[1].size    = 0;
    modelVariables[1].address = &(rtmGetU(S)->w);

    modelVariables[2].dtypeID = 0;
    modelVariables[2].size    = 0;
    modelVariables[2].address = &(rtmGetY(S)->v);
}

#define N_MODEL_VARIABLES 3
