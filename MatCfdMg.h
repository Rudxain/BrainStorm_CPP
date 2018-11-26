//
// MATLAB Compiler: 6.5 (R2017b)
// Date: Mon Nov 26 10:40:54 2018
// Arguments: "-B""macro_default""-W""cpplib:MatCfdMg""-T""link:lib""CfdMg"
//

#ifndef __MatCfdMg_h
#define __MatCfdMg_h 1

#if defined(__cplusplus) && !defined(mclmcrrt_h) && defined(__linux__)
#  pragma implementation "mclmcrrt.h"
#endif
#include "mclmcrrt.h"
#include "mclcppclass.h"
#ifdef __cplusplus
extern "C" {
#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_MatCfdMg_C_API 
#define LIB_MatCfdMg_C_API /* No special import/export declaration */
#endif

/* GENERAL LIBRARY FUNCTIONS -- START */

extern LIB_MatCfdMg_C_API 
bool MW_CALL_CONV MatCfdMgInitializeWithHandlers(
       mclOutputHandlerFcn error_handler, 
       mclOutputHandlerFcn print_handler);

extern LIB_MatCfdMg_C_API 
bool MW_CALL_CONV MatCfdMgInitialize(void);

extern LIB_MatCfdMg_C_API 
void MW_CALL_CONV MatCfdMgTerminate(void);

extern LIB_MatCfdMg_C_API 
void MW_CALL_CONV MatCfdMgPrintStackTrace(void);

/* GENERAL LIBRARY FUNCTIONS -- END */

/* C INTERFACE -- MLX WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- START */

extern LIB_MatCfdMg_C_API 
bool MW_CALL_CONV mlxCfdMg(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

/* C INTERFACE -- MLX WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- END */

#ifdef __cplusplus
}
#endif


/* C++ INTERFACE -- WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- START */

#ifdef __cplusplus

/* On Windows, use __declspec to control the exported API */
#if defined(_MSC_VER) || defined(__MINGW64__)

#ifdef EXPORTING_MatCfdMg
#define PUBLIC_MatCfdMg_CPP_API __declspec(dllexport)
#else
#define PUBLIC_MatCfdMg_CPP_API __declspec(dllimport)
#endif

#define LIB_MatCfdMg_CPP_API PUBLIC_MatCfdMg_CPP_API

#else

#if !defined(LIB_MatCfdMg_CPP_API)
#if defined(LIB_MatCfdMg_C_API)
#define LIB_MatCfdMg_CPP_API LIB_MatCfdMg_C_API
#else
#define LIB_MatCfdMg_CPP_API /* empty! */ 
#endif
#endif

#endif

extern LIB_MatCfdMg_CPP_API void MW_CALL_CONV CfdMg(int nargout, mwArray& z, const mwArray& x);

/* C++ INTERFACE -- WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- END */
#endif

#endif
