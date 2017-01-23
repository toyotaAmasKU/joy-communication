/*  Author : Supakit Kriangkhajorn ,2016
    Follow me : skconan
    Ref: https://www.mathworks.com/help/simulink/sfg/example-of-a-basic-c-mex-s-function.html   */

#define S_FUNCTION_NAME joy_read_c /* Defines and Includes */
#define S_FUNCTION_LEVEL 2
#include "simstruc.h"
#include<stdio.h>

static void mdlInitializeSizes(SimStruct *S)
{
    ssSetNumSFcnParams(S, 0);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        return; /* Parameter mismatch reported by the Simulink engine*/
    }

    if (!ssSetNumInputPorts(S, 0)) return;
    
    if (!ssSetNumOutputPorts(S,2)) return;
    ssSetOutputPortWidth(S, 0, DYNAMICALLY_SIZED);
    ssSetOutputPortWidth(S, 1, DYNAMICALLY_SIZED);

    ssSetNumSampleTimes(S, 1);

    /* Take care when specifying exception free code - see sfuntmpl.doc */
    ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE);
}

static void mdlInitializeSampleTimes(SimStruct *S)
{
    ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
    ssSetOffsetTime(S, 0, 0.0);
}

static void mdlOutputs(SimStruct *S, int_T tid)
{
    int velocity, leftright;
    real_T *y = ssGetOutputPortRealSignal(S,0);
    int_T width = ssGetOutputPortWidth(S,0);
    FILE *fptr;

    fptr = fopen("joy_forward.txt","r"); 
    fseek(fptr, -sizeof(char)*3, SEEK_END);
    fscanf(fptr,"%d",&velocity);
    fclose(fptr);
    *y = velocity;

    real_T *y1 = ssGetOutputPortRealSignal(S,1);
    int_T width1 = ssGetOutputPortWidth(S,1);
    
    fptr = fopen("joy_leftright.txt","r"); 
    fseek(fptr, -sizeof(char)*4, SEEK_END);
    fscanf(fptr,"%d",&leftright);
    fclose(fptr);
    *y1 = leftright;
    
}


static void mdlTerminate(SimStruct *S){}
#ifdef MATLAB_MEX_FILE /* Is this file being compiled as a MEX-file? */
#include "simulink.c" /* MEX-file interface mechanism */
#else
#include "cg_sfun.h" /* Code generation registration function */
#endif