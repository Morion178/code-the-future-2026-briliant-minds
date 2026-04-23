#ifndef OpenLoopController_h_
#define OpenLoopController_h_
#ifndef OpenLoopController_COMMON_INCLUDES_
#define OpenLoopController_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "slsv_diagnostic_codegen_c_api.h"
#include "sl_AsyncioQueue/AsyncioQueueCAPI.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "math.h"
#endif
#include "OpenLoopController_types.h"
#include "rtw_modelmap_simtarget.h"
#include "rt_nonfinite.h"
#include <string.h>
#include <stddef.h>
typedef struct { boolean_T jfk2awovhw ; } ptlsrjusnd ; struct nzwosi2zd3d_ {
boolean_T P_0 ; } ; struct b3lqzryvib { struct SimStruct_tag * _mdlRefSfcnS ;
struct { rtwCAPI_ModelMappingInfo mmi ; rtwCAPI_ModelMapLoggingInstanceInfo
mmiLogInstanceInfo ; sysRanDType * systemRan [ 2 ] ; int_T systemTid [ 2 ] ;
} DataMapInfo ; struct { int_T mdlref_GlobalTID [ 2 ] ; } Timing ; } ;
typedef struct { ptlsrjusnd rtb ; mb0ycltnvs rtm ; } kx0gjmohhwa ; extern
void cuzhnyqkk1 ( SimStruct * _mdlRefSfcnS , int_T mdlref_TID0 , int_T
mdlref_TID1 , mb0ycltnvs * const ahbaxoyrw2 , ptlsrjusnd * localB , void *
sysRanPtr , int contextTid , rtwCAPI_ModelMappingInfo * rt_ParentMMI , const
char_T * rt_ChildPath , int_T rt_ChildMMIIdx , int_T rt_CSTATEIdx ) ; extern
void mr_OpenLoopController_MdlInfoRegFcn ( SimStruct * mdlRefSfcnS , char_T *
modelName , int_T * retVal ) ; extern mxArray *
mr_OpenLoopController_GetDWork ( const kx0gjmohhwa * mdlrefDW ) ; extern void
mr_OpenLoopController_SetDWork ( kx0gjmohhwa * mdlrefDW , const mxArray *
ssDW ) ; extern void mr_OpenLoopController_RegisterSimStateChecksum ( SimStruct
* S ) ; extern mxArray * mr_OpenLoopController_GetSimStateDisallowedBlocks ( )
; extern const rtwCAPI_ModelMappingStaticInfo *
OpenLoopController_GetCAPIStaticMap ( void ) ; extern void eo1ddfxdk5 ( boolean_T lqsafojnoo [ 2 ] , ptlsrjusnd * localB ) ; extern void c0vpoyawl0 ( ptlsrjusnd * localB ) ; extern void OpenLoopController ( const real_T penz1mlrsr [ 2 ] , real_T foxrqbg00l [ 2 ] ) ; extern void OpenLoopControllerTID1 ( boolean_T lqsafojnoo [ 2 ] , ptlsrjusnd * localB ) ; extern void mhz4h2tzla ( mb0ycltnvs * const ahbaxoyrw2 ) ;
#endif
