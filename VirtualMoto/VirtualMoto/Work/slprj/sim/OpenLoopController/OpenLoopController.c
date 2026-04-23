#include "OpenLoopController.h"
#include "rtwtypes.h"
#include "OpenLoopController_private.h"
#include "OpenLoopController_capi.h"
static RegMdlInfo rtMdlInfo_OpenLoopController [ 39 ] = { { "kx0gjmohhwa" ,
MDL_INFO_NAME_MDLREF_DWORK , 0 , - 1 , ( void * ) "OpenLoopController" } , {
"braj5cvob2" , MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT , 0 , - 1 , ( void * )
"OpenLoopController" } , { "brslu33keb" , MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT ,
0 , - 1 , ( void * ) "OpenLoopController" } , { "mhf02ofeum" ,
MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT , 0 , - 1 , ( void * ) "OpenLoopController"
} , { "at11mwx3qe" , MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT , 0 , - 1 , ( void * )
"OpenLoopController" } , { "g3qkuub4oq" , MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT ,
0 , - 1 , ( void * ) "OpenLoopController" } , { "m4hyylt00z" ,
MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT , 0 , - 1 , ( void * ) "OpenLoopController"
} , { "bmg5nymc3n" , MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT , 0 , - 1 , ( void * )
"OpenLoopController" } , { "goav1sxtgg" , MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT ,
0 , - 1 , ( void * ) "OpenLoopController" } , { "erx3s0rskq" ,
MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT , 0 , - 1 , ( void * ) "OpenLoopController"
} , { "p0tdcr0fan" , MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT , 0 , - 1 , ( void * )
"OpenLoopController" } , { "nb4iuj5nig" , MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT ,
0 , - 1 , ( void * ) "OpenLoopController" } , { "mymyewjcgc" ,
MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT , 0 , - 1 , ( void * ) "OpenLoopController"
} , { "ptlsrjusnd" , MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT , 0 , - 1 , ( void * )
"OpenLoopController" } , { "fqwf3jmgr5" , MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT ,
0 , - 1 , ( void * ) "OpenLoopController" } , { "mhz4h2tzla" ,
MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT , 0 , - 1 , ( void * ) "OpenLoopController"
} , { "eo1ddfxdk5" , MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT , 0 , - 1 , ( void * )
"OpenLoopController" } , { "cuzhnyqkk1" , MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT ,
0 , - 1 , ( void * ) "OpenLoopController" } , { "c0vpoyawl0" ,
MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT , 0 , - 1 , ( void * ) "OpenLoopController"
} , { "bwy2avu4fg" , MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT , 0 , - 1 , ( void * )
"OpenLoopController" } , { "OpenLoopController" ,
MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT , 0 , 0 , ( NULL ) } , { "k2ui2ptcqu" ,
MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT , 0 , - 1 , ( void * ) "OpenLoopController"
} , { "nzwosi2zd3d" , MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT , 0 , - 1 , ( void * )
"OpenLoopController" } , { "b3lqzryvib" , MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT ,
0 , - 1 , ( void * ) "OpenLoopController" } , { "mb0ycltnvs" ,
MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT , 0 , - 1 , ( void * ) "OpenLoopController"
} , { "mr_OpenLoopController_GetSimStateDisallowedBlocks" ,
MDL_INFO_ID_MODEL_FCN_NAME , 0 , - 1 , ( void * ) "OpenLoopController" } , {
"mr_OpenLoopController_extractBitFieldFromCellArrayWithOffset" ,
MDL_INFO_ID_MODEL_FCN_NAME , 0 , - 1 , ( void * ) "OpenLoopController" } , {
"mr_OpenLoopController_cacheBitFieldToCellArrayWithOffset" ,
MDL_INFO_ID_MODEL_FCN_NAME , 0 , - 1 , ( void * ) "OpenLoopController" } , {
"mr_OpenLoopController_restoreDataFromMxArrayWithOffset" ,
MDL_INFO_ID_MODEL_FCN_NAME , 0 , - 1 , ( void * ) "OpenLoopController" } , {
"mr_OpenLoopController_cacheDataToMxArrayWithOffset" ,
MDL_INFO_ID_MODEL_FCN_NAME , 0 , - 1 , ( void * ) "OpenLoopController" } , {
"mr_OpenLoopController_extractBitFieldFromMxArray" ,
MDL_INFO_ID_MODEL_FCN_NAME , 0 , - 1 , ( void * ) "OpenLoopController" } , {
"mr_OpenLoopController_cacheBitFieldToMxArray" , MDL_INFO_ID_MODEL_FCN_NAME ,
0 , - 1 , ( void * ) "OpenLoopController" } , {
"mr_OpenLoopController_restoreDataFromMxArray" , MDL_INFO_ID_MODEL_FCN_NAME ,
0 , - 1 , ( void * ) "OpenLoopController" } , {
"mr_OpenLoopController_cacheDataAsMxArray" , MDL_INFO_ID_MODEL_FCN_NAME , 0 ,
- 1 , ( void * ) "OpenLoopController" } , {
"mr_OpenLoopController_RegisterSimStateChecksum" , MDL_INFO_ID_MODEL_FCN_NAME
, 0 , - 1 , ( void * ) "OpenLoopController" } , {
"mr_OpenLoopController_SetDWork" , MDL_INFO_ID_MODEL_FCN_NAME , 0 , - 1 , ( void
* ) "OpenLoopController" } , { "mr_OpenLoopController_GetDWork" ,
MDL_INFO_ID_MODEL_FCN_NAME , 0 , - 1 , ( void * ) "OpenLoopController" } , {
"OpenLoopController.h" , MDL_INFO_MODEL_FILENAME , 0 , - 1 , ( NULL ) } , {
"OpenLoopController.c" , MDL_INFO_MODEL_FILENAME , 0 , - 1 , ( void * )
"OpenLoopController" } } ; nzwosi2zd3d nzwosi2zd3 = { false } ; void
eo1ddfxdk5 ( boolean_T lqsafojnoo [ 2 ] , ptlsrjusnd * localB ) { lqsafojnoo
[ 0 ] = localB -> jfk2awovhw ; lqsafojnoo [ 1 ] = localB -> jfk2awovhw ; }
void c0vpoyawl0 ( ptlsrjusnd * localB ) { localB -> jfk2awovhw = nzwosi2zd3 .
P_0 ; } void OpenLoopController ( const real_T penz1mlrsr [ 2 ] , real_T
foxrqbg00l [ 2 ] ) { foxrqbg00l [ 0 ] = penz1mlrsr [ 0 ] ; foxrqbg00l [ 1 ] =
penz1mlrsr [ 1 ] ; } void OpenLoopControllerTID1 ( boolean_T lqsafojnoo [ 2 ]
, ptlsrjusnd * localB ) { localB -> jfk2awovhw = nzwosi2zd3 . P_0 ;
lqsafojnoo [ 0 ] = localB -> jfk2awovhw ; lqsafojnoo [ 1 ] = localB ->
jfk2awovhw ; } void mhz4h2tzla ( mb0ycltnvs * const ahbaxoyrw2 ) { if ( !
slIsRapidAcceleratorSimulating ( ) ) { slmrRunPluginEvent ( ahbaxoyrw2 ->
_mdlRefSfcnS , "OpenLoopController" ,
"SIMSTATUS_TERMINATING_MODELREF_ACCEL_EVENT" ) ; } } void cuzhnyqkk1 ( SimStruct
* _mdlRefSfcnS , int_T mdlref_TID0 , int_T mdlref_TID1 , mb0ycltnvs * const
ahbaxoyrw2 , ptlsrjusnd * localB , void * sysRanPtr , int contextTid ,
rtwCAPI_ModelMappingInfo * rt_ParentMMI , const char_T * rt_ChildPath , int_T
rt_ChildMMIIdx , int_T rt_CSTATEIdx ) { ( void ) memset ( ( void * )
ahbaxoyrw2 , 0 , sizeof ( mb0ycltnvs ) ) ; ahbaxoyrw2 -> Timing .
mdlref_GlobalTID [ 0 ] = mdlref_TID0 ; ahbaxoyrw2 -> Timing .
mdlref_GlobalTID [ 1 ] = mdlref_TID1 ; ahbaxoyrw2 -> _mdlRefSfcnS = ( _mdlRefSfcnS ) ; if ( ! slIsRapidAcceleratorSimulating ( ) ) { slmrRunPluginEvent ( ahbaxoyrw2 -> _mdlRefSfcnS , "OpenLoopController" , "START_OF_SIM_MODEL_MODELREF_ACCEL_EVENT" ) ; } ( void ) memset ( ( ( void * ) localB ) , 0 , sizeof ( ptlsrjusnd ) ) ; OpenLoopController_InitializeDataMapInfo ( ahbaxoyrw2 , sysRanPtr , contextTid ) ; if ( ( rt_ParentMMI != ( NULL ) ) && ( rt_ChildPath != ( NULL ) ) ) { rtwCAPI_SetChildMMI ( * rt_ParentMMI , rt_ChildMMIIdx , & ( ahbaxoyrw2 -> DataMapInfo . mmi ) ) ; rtwCAPI_SetPath ( ahbaxoyrw2 -> DataMapInfo . mmi , rt_ChildPath ) ; rtwCAPI_MMISetContStateStartIndex ( ahbaxoyrw2 -> DataMapInfo . mmi , rt_CSTATEIdx ) ; } } void mr_OpenLoopController_MdlInfoRegFcn ( SimStruct * mdlRefSfcnS , char_T * modelName , int_T * retVal ) { * retVal = 0 ; { boolean_T regSubmodelsMdlinfo = false ; ssGetRegSubmodelsMdlinfo ( mdlRefSfcnS , & regSubmodelsMdlinfo ) ; if ( regSubmodelsMdlinfo ) { } } * retVal = 0 ; ssRegModelRefMdlInfo ( mdlRefSfcnS , modelName , rtMdlInfo_OpenLoopController , 39 ) ; * retVal = 1 ; } static void mr_OpenLoopController_cacheDataAsMxArray ( mxArray * destArray , mwIndex i , int j , const void * srcData , size_t numBytes ) ; static void mr_OpenLoopController_cacheDataAsMxArray ( mxArray * destArray , mwIndex i , int j , const void * srcData , size_t numBytes ) { mxArray * newArray = mxCreateUninitNumericMatrix ( ( size_t ) 1 , numBytes , mxUINT8_CLASS , mxREAL ) ; memcpy ( ( uint8_T * ) mxGetData ( newArray ) , ( const uint8_T * ) srcData , numBytes ) ; mxSetFieldByNumber ( destArray , i , j , newArray ) ; } static void mr_OpenLoopController_restoreDataFromMxArray ( void * destData , const mxArray * srcArray , mwIndex i , int j , size_t numBytes ) ; static void mr_OpenLoopController_restoreDataFromMxArray ( void * destData , const mxArray * srcArray , mwIndex i , int j , size_t numBytes ) { memcpy ( ( uint8_T * ) destData , ( const uint8_T * ) mxGetData ( mxGetFieldByNumber ( srcArray , i , j ) ) , numBytes ) ; } static void mr_OpenLoopController_cacheBitFieldToMxArray ( mxArray * destArray , mwIndex i , int j , uint_T bitVal ) ; static void mr_OpenLoopController_cacheBitFieldToMxArray ( mxArray * destArray , mwIndex i , int j , uint_T bitVal ) { mxSetFieldByNumber ( destArray , i , j , mxCreateDoubleScalar ( ( real_T ) bitVal ) ) ; } static uint_T mr_OpenLoopController_extractBitFieldFromMxArray ( const mxArray * srcArray , mwIndex i , int j , uint_T numBits ) ; static uint_T mr_OpenLoopController_extractBitFieldFromMxArray ( const mxArray * srcArray , mwIndex i , int j , uint_T numBits ) { const uint_T varVal = ( uint_T ) mxGetScalar ( mxGetFieldByNumber ( srcArray , i , j ) ) ; return varVal & ( ( 1u << numBits ) - 1u ) ; } static void mr_OpenLoopController_cacheDataToMxArrayWithOffset ( mxArray * destArray , mwIndex i , int j , mwIndex offset , const void * srcData , size_t numBytes ) ; static void mr_OpenLoopController_cacheDataToMxArrayWithOffset ( mxArray * destArray , mwIndex i , int j , mwIndex offset , const void * srcData , size_t numBytes ) { uint8_T * varData = ( uint8_T * ) mxGetData ( mxGetFieldByNumber ( destArray , i , j ) ) ; memcpy ( ( uint8_T * ) & varData [ offset * numBytes ] , ( const uint8_T * ) srcData , numBytes ) ; } static void mr_OpenLoopController_restoreDataFromMxArrayWithOffset ( void * destData , const mxArray * srcArray , mwIndex i , int j , mwIndex offset , size_t numBytes ) ; static void mr_OpenLoopController_restoreDataFromMxArrayWithOffset ( void * destData , const mxArray * srcArray , mwIndex i , int j , mwIndex offset , size_t numBytes ) { const uint8_T * varData = ( const uint8_T * ) mxGetData ( mxGetFieldByNumber ( srcArray , i , j ) ) ; memcpy ( ( uint8_T * ) destData , ( const uint8_T * ) & varData [ offset * numBytes ] , numBytes ) ; } static void mr_OpenLoopController_cacheBitFieldToCellArrayWithOffset ( mxArray * destArray , mwIndex i , int j , mwIndex offset , uint_T fieldVal ) ; static void mr_OpenLoopController_cacheBitFieldToCellArrayWithOffset ( mxArray * destArray , mwIndex i , int j , mwIndex offset , uint_T fieldVal ) { mxSetCell ( mxGetFieldByNumber ( destArray , i , j ) , offset , mxCreateDoubleScalar ( ( real_T ) fieldVal ) ) ; } static uint_T mr_OpenLoopController_extractBitFieldFromCellArrayWithOffset ( const mxArray * srcArray , mwIndex i , int j , mwIndex offset , uint_T numBits ) ; static uint_T mr_OpenLoopController_extractBitFieldFromCellArrayWithOffset ( const mxArray * srcArray , mwIndex i , int j , mwIndex offset , uint_T numBits ) { const uint_T fieldVal = ( uint_T ) mxGetScalar ( mxGetCell ( mxGetFieldByNumber ( srcArray , i , j ) , offset ) ) ; return fieldVal & ( ( 1u << numBits ) - 1u ) ; } mxArray * mr_OpenLoopController_GetDWork ( const kx0gjmohhwa * mdlrefDW ) { static const char_T * ssDWFieldNames [ 3 ] = { "rtb" , "NULL->rtdw" , "NULL->rtzce" , } ; mxArray * ssDW = mxCreateStructMatrix ( 1 , 1 , 3 , ssDWFieldNames ) ; mr_OpenLoopController_cacheDataAsMxArray ( ssDW , 0 , 0 , ( const void * ) & ( mdlrefDW -> rtb ) , sizeof ( mdlrefDW -> rtb ) ) ; ( void ) mdlrefDW ; return ssDW ; } void mr_OpenLoopController_SetDWork ( kx0gjmohhwa * mdlrefDW , const mxArray * ssDW ) { ( void ) ssDW ; ( void ) mdlrefDW ; mr_OpenLoopController_restoreDataFromMxArray ( ( void * ) & ( mdlrefDW -> rtb ) , ssDW , 0 , 0 , sizeof ( mdlrefDW -> rtb ) ) ; } void mr_OpenLoopController_RegisterSimStateChecksum ( SimStruct * S ) { const uint32_T chksum [ 4 ] = { 1815852212U , 2877551904U , 4099247995U , 1005163055U , } ; slmrModelRefRegisterSimStateChecksum ( S , "OpenLoopController" , & chksum [ 0 ] ) ; } mxArray * mr_OpenLoopController_GetSimStateDisallowedBlocks ( ) { return ( NULL ) ; }
#if defined(_MSC_VER)
#pragma warning(disable: 4505) //unreferenced local function has been removed
#endif
