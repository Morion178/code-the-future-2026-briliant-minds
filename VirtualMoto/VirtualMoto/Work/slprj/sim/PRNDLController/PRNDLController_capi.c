#include <stddef.h>
#include "rtw_capi.h"
#ifdef HOST_CAPI_BUILD
#include "PRNDLController_capi_host.h"
#define sizeof(...) ((size_t)(0xFFFF))
#undef rt_offsetof
#define rt_offsetof(s,el) ((uint16_T)(0xFFFF))
#define TARGET_CONST
#define TARGET_STRING(s) (s)
#ifndef SS_UINT64
#define SS_UINT64 17
#endif
#ifndef SS_INT64
#define SS_INT64 18
#endif
#else
#include "builtin_typeid_types.h"
#include "PRNDLController.h"
#include "PRNDLController_capi.h"
#include "PRNDLController_private.h"
#ifdef LIGHT_WEIGHT_CAPI
#define TARGET_CONST
#define TARGET_STRING(s)               ((NULL))
#else
#define TARGET_CONST                   const
#define TARGET_STRING(s)               (s)
#endif
#endif
static rtwCAPI_Signals rtBlockSignals [ ] = { { 0 , 0 , ( NULL ) , ( NULL ) ,
0 , 0 , 0 , 0 , 0 } } ; static rtwCAPI_States rtBlockStates [ ] = { { 0 , - 1
, ( NULL ) , ( NULL ) , ( NULL ) , 0 , 0 , 0 , 0 , 0 , 0 , - 1 , 0 } } ;
static int_T rt_LoggedStateIdxList [ ] = { - 1 } ; static TARGET_CONST
rtwCAPI_DataTypeMap rtDataTypeMap [ ] = { { "" , "" , 0 , 0 , 0 , 0 , 0 , 0 ,
0 } } ;
#ifdef HOST_CAPI_BUILD
#undef sizeof
#endif
static TARGET_CONST rtwCAPI_ElementMap rtElementMap [ ] = { { ( NULL ) , 0 ,
0 , 0 , 0 } , } ; static rtwCAPI_DimensionMap rtDimensionMap [ ] = { {
rtwCAPI_SCALAR , 0 , 0 , 0 } } ; static uint_T rtDimensionArray [ ] = { 0 } ;
static rtwCAPI_FixPtMap rtFixPtMap [ ] = { { ( NULL ) , ( NULL ) ,
rtwCAPI_FIX_RESERVED , 0 , 0 , ( boolean_T ) 0 } , } ; static
rtwCAPI_SampleTimeMap rtSampleTimeMap [ ] = { { ( NULL ) , ( NULL ) , 0 , 0 }
} ; static int_T rtContextSystems [ 6 ] ; static rtwCAPI_LoggingMetaInfo
loggingMetaInfo [ ] = { { 0 , 0 , "" , 0 } } ; static
rtwCAPI_ModelMapLoggingStaticInfo mmiStaticInfoLogging = { 6 ,
rtContextSystems , loggingMetaInfo , 0 , ( NULL ) , { 0 , ( NULL ) , ( NULL )
} , 0 , ( NULL ) } ; static rtwCAPI_ModelMappingStaticInfo mmiStatic = { {
rtBlockSignals , 0 , ( NULL ) , 0 , ( NULL ) , 0 } , { ( NULL ) , 0 , ( NULL
) , 0 } , { rtBlockStates , 0 } , { rtDataTypeMap , rtDimensionMap ,
rtFixPtMap , rtElementMap , rtSampleTimeMap , rtDimensionArray } , "float" ,
{ 1236222985U , 2459392871U , 1881739306U , 1994243649U } , &
mmiStaticInfoLogging , 0 , ( boolean_T ) 0 , rt_LoggedStateIdxList } ; const
rtwCAPI_ModelMappingStaticInfo * PRNDLController_GetCAPIStaticMap ( void ) {
return & mmiStatic ; }
#ifndef HOST_CAPI_BUILD
static void PRNDLController_InitializeSystemRan ( ejdirckwac * const
fdopgmryi2 , sysRanDType * systemRan [ ] , pxshinjyri * localDW , int_T
systemTid [ ] , void * rootSysRanPtr , int rootTid ) { UNUSED_PARAMETER ( fdopgmryi2 ) ; UNUSED_PARAMETER ( localDW ) ; systemRan [ 0 ] = ( sysRanDType * ) rootSysRanPtr ; systemRan [ 1 ] = ( sysRanDType * ) & localDW -> ljukzwcq0g1 . eob4a4cufc ; systemRan [ 2 ] = ( sysRanDType * ) & localDW -> jzuqcidcqp ; systemRan [ 3 ] = ( sysRanDType * ) & localDW -> jz3yqpyzsk ; systemRan [ 4 ] = ( NULL ) ; systemRan [ 5 ] = ( NULL ) ; systemTid [ 3 ] = fdopgmryi2 -> Timing . mdlref_GlobalTID [ 0 ] ; systemTid [ 2 ] = fdopgmryi2 -> Timing . mdlref_GlobalTID [ 0 ] ; systemTid [ 1 ] = fdopgmryi2 -> Timing . mdlref_GlobalTID [ 0 ] ; systemTid [ 4 ] = fdopgmryi2 -> Timing . mdlref_GlobalTID [ 0 ] ; systemTid [ 5 ] = fdopgmryi2 -> Timing . mdlref_GlobalTID [ 0 ] ; systemTid [ 0 ] = rootTid ; rtContextSystems [ 0 ] = 0 ; rtContextSystems [ 1 ] = 1 ; rtContextSystems [ 2 ] = 2 ; rtContextSystems [ 3 ] = 3 ; rtContextSystems [ 4 ] = 0 ; rtContextSystems [ 5 ] = 0 ; }
#endif
#ifndef HOST_CAPI_BUILD
void PRNDLController_InitializeDataMapInfo ( ejdirckwac * const fdopgmryi2 ,
pxshinjyri * localDW , void * sysRanPtr , int contextTid ) {
rtwCAPI_SetVersion ( fdopgmryi2 -> DataMapInfo . mmi , 1 ) ;
rtwCAPI_SetStaticMap ( fdopgmryi2 -> DataMapInfo . mmi , & mmiStatic ) ;
rtwCAPI_SetLoggingStaticMap ( fdopgmryi2 -> DataMapInfo . mmi , &
mmiStaticInfoLogging ) ; rtwCAPI_SetPath ( fdopgmryi2 -> DataMapInfo . mmi ,
( NULL ) ) ; rtwCAPI_SetFullPath ( fdopgmryi2 -> DataMapInfo . mmi , ( NULL )
) ; rtwCAPI_SetInstanceLoggingInfo ( fdopgmryi2 -> DataMapInfo . mmi , &
fdopgmryi2 -> DataMapInfo . mmiLogInstanceInfo ) ; rtwCAPI_SetChildMMIArray ( fdopgmryi2 -> DataMapInfo . mmi , ( NULL ) ) ; rtwCAPI_SetChildMMIArrayLen ( fdopgmryi2 -> DataMapInfo . mmi , 0 ) ; PRNDLController_InitializeSystemRan ( fdopgmryi2 , fdopgmryi2 -> DataMapInfo . systemRan , localDW , fdopgmryi2 -> DataMapInfo . systemTid , sysRanPtr , contextTid ) ; rtwCAPI_SetSystemRan ( fdopgmryi2 -> DataMapInfo . mmi , fdopgmryi2 -> DataMapInfo . systemRan ) ; rtwCAPI_SetSystemTid ( fdopgmryi2 -> DataMapInfo . mmi , fdopgmryi2 -> DataMapInfo . systemTid ) ; rtwCAPI_SetGlobalTIDMap ( fdopgmryi2 -> DataMapInfo . mmi , & fdopgmryi2 -> Timing . mdlref_GlobalTID [ 0 ] ) ; }
#else
#ifdef __cplusplus
extern "C" {
#endif
void PRNDLController_host_InitializeDataMapInfo ( PRNDLController_host_DataMapInfo_T * dataMap , const char * path ) { rtwCAPI_SetVersion ( dataMap -> mmi , 1 ) ; rtwCAPI_SetStaticMap ( dataMap -> mmi , & mmiStatic ) ; rtwCAPI_SetDataAddressMap ( dataMap -> mmi , ( NULL ) ) ; rtwCAPI_SetVarDimsAddressMap ( dataMap -> mmi , ( NULL ) ) ; rtwCAPI_SetPath ( dataMap -> mmi , path ) ; rtwCAPI_SetFullPath ( dataMap -> mmi , ( NULL ) ) ; rtwCAPI_SetChildMMIArray ( dataMap -> mmi , ( NULL ) ) ; rtwCAPI_SetChildMMIArrayLen ( dataMap -> mmi , 0 ) ; }
#ifdef __cplusplus
}
#endif
#endif
