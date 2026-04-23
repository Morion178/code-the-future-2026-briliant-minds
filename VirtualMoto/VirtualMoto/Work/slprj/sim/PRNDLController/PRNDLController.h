#ifndef PRNDLController_h_
#define PRNDLController_h_
#ifndef PRNDLController_COMMON_INCLUDES_
#define PRNDLController_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "slsv_diagnostic_codegen_c_api.h"
#include "sl_AsyncioQueue/AsyncioQueueCAPI.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "math.h"
#include "sfrtif/sfc_sdi.h"
#endif
#include "PRNDLController_types.h"
#include "rtw_modelmap_simtarget.h"
#include "rt_nonfinite.h"
#include <string.h>
#include <stddef.h>
typedef struct { real_T bpvfrxxenp ; } fotnkdml2q ; typedef struct { int8_T
eob4a4cufc ; boolean_T arzbauqvr1 ; } apq0itlzhx ; typedef struct {
fotnkdml2q ljukzwcq0g1 ; } kkxbltx1cp ; typedef struct { real_T jfic0kod3c ;
real_T cuvupd35at ; uint32_T mm1nentbay ; uint32_T p0okmflqxc ; int8_T
jzuqcidcqp ; int8_T jz3yqpyzsk ; uint8_T ldwjb4dssl ; uint8_T msbebgy5zi ;
uint8_T j1mvd0fbmo ; apq0itlzhx ljukzwcq0g1 ; } pxshinjyri ; struct
ibsopqppuy_ { real_T P_0 ; real_T P_1 [ 2 ] ; real_T P_2 [ 2 ] ; real_T P_3 ;
real_T P_4 ; real_T P_5 ; real_T P_6 ; } ; struct ku2evzhqltp_ { real_T P_4 [
2 ] ; real_T P_5 [ 7 ] ; real_T P_6 [ 56 ] ; real_T P_7 ; real_T P_8 ; real_T
P_9 ; real_T P_10 [ 2 ] ; real_T P_11 [ 7 ] ; real_T P_12 [ 56 ] ; real_T
P_13 ; real_T P_14 ; real_T P_15 ; real_T P_16 [ 7 ] ; real_T P_17 [ 4 ] ;
real_T P_18 ; real_T P_19 [ 7 ] ; real_T P_20 [ 4 ] ; real_T P_21 ; real_T
P_22 ; real_T P_23 ; real_T P_24 ; uint32_T P_25 [ 3 ] ; uint32_T P_26 [ 3 ]
; uint32_T P_27 [ 3 ] ; uint32_T P_28 [ 3 ] ; ibsopqppuy ljukzwcq0g1 ; } ;
struct p3hhjb2ky5 { struct SimStruct_tag * _mdlRefSfcnS ; struct {
rtwCAPI_ModelMappingInfo mmi ; rtwCAPI_ModelMapLoggingInstanceInfo
mmiLogInstanceInfo ; sysRanDType * systemRan [ 6 ] ; int_T systemTid [ 6 ] ;
} DataMapInfo ; struct { int_T mdlref_GlobalTID [ 2 ] ; } Timing ; } ;
typedef struct { kkxbltx1cp rtb ; pxshinjyri rtdw ; ejdirckwac rtm ; }
co0xztiide0 ; extern real_T rtP__CtrlTcuDnLdBpt2f2Drivetrain_sldd_ [ 4 ] ;
extern real_T rtP__CtrlTcuUpLdBpt2f2Drivetrain_sldd_ [ 4 ] ; extern real_T
rtP__TireFrntWhlRadius2f2MotoWheel_sldd_ ; extern real_T
rtP__TireRearWhlRadius2f2MotoWheel_sldd_ ; extern void adgpgs52hf ( SimStruct
* _mdlRefSfcnS , int_T mdlref_TID0 , int_T mdlref_TID1 , ejdirckwac * const
fdopgmryi2 , kkxbltx1cp * localB , pxshinjyri * localDW , void * sysRanPtr ,
int contextTid , rtwCAPI_ModelMappingInfo * rt_ParentMMI , const char_T *
rt_ChildPath , int_T rt_ChildMMIIdx , int_T rt_CSTATEIdx ) ; extern void
mr_PRNDLController_MdlInfoRegFcn ( SimStruct * mdlRefSfcnS , char_T *
modelName , int_T * retVal ) ; extern mxArray * mr_PRNDLController_GetDWork ( const co0xztiide0 * mdlrefDW ) ; extern void mr_PRNDLController_SetDWork ( co0xztiide0 * mdlrefDW , const mxArray * ssDW ) ; extern void mr_PRNDLController_RegisterSimStateChecksum ( SimStruct * S ) ; extern mxArray * mr_PRNDLController_GetSimStateDisallowedBlocks ( ) ; extern const rtwCAPI_ModelMappingStaticInfo * PRNDLController_GetCAPIStaticMap ( void ) ; extern void a0wthexki1 ( fotnkdml2q * localB , ibsopqppuy * localP ) ; extern void ljukzwcq0g ( real_T oa5p3m3qsc , real_T df4l0rp0tc , fotnkdml2q * localB , apq0itlzhx * localDW , ibsopqppuy * localP ) ; extern void pyx05adf24 ( real_T * jnp1raxxu4 , kkxbltx1cp * localB , pxshinjyri * localDW ) ; extern void bd4kosf0po ( real_T * jnp1raxxu4 , pxshinjyri * localDW ) ; extern void PRNDLController ( const real_T * dugx2nyefg , const real_T hh0gyc1nkz [ 2 ] , const real_T ass25qmj2n [ 2 ] , const real_T * bg0ejuvboy , const real_T * f1l10b3cai , const boolean_T np4i5bxs5u [ 2 ] , real_T * jnp1raxxu4 , kkxbltx1cp * localB , pxshinjyri * localDW ) ; extern void iaqi3xc5te ( ejdirckwac * const fdopgmryi2 ) ;
#endif
