#include "PRNDLController.h"
#include "rtwtypes.h"
#include "PRNDLController_private.h"
#include "mwmathutil.h"
#include "PRNDLController_capi.h"
#include "look1_binlcpw.h"
#include "plook_binc.h"
#include "intrp3d_l_pw.h"
#include "look1_binlcapw.h"
#include <string.h>
#define anf2nyqqlb ((uint8_T)2U)
#define bljendk0zq ((uint8_T)3U)
#define c3tscmpimb ((uint8_T)5U)
#define ddvm0y4hod ((uint8_T)4U)
#define evccign45j ((uint8_T)1U)
#define hgqxqzz5jy ((uint8_T)4U)
#define igvqestgao ((uint8_T)6U)
#define japeuimdgw ((uint8_T)3U)
#define jcwvjyrxps ((uint8_T)0U)
#define k5vrhoaqhz ((uint8_T)1U)
#define oj3rltsxbh ((uint8_T)2U)
static RegMdlInfo rtMdlInfo_PRNDLController [ 64 ] = { { "jo3mm1xere" ,
MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT , 0 , - 1 , ( void * ) "PRNDLController" } ,
{ "ape1szzygr" , MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT , 0 , - 1 , ( void * )
"PRNDLController" } , { "l33aknyfnu" , MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT , 0 ,
- 1 , ( void * ) "PRNDLController" } , { "fp4ohvseqc" ,
MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT , 0 , - 1 , ( void * ) "PRNDLController" } ,
{ "luahu5gsba" , MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT , 0 , - 1 , ( void * )
"PRNDLController" } , { "jvnpd215hq" , MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT , 0 ,
- 1 , ( void * ) "PRNDLController" } , { "minmdjzm2y" ,
MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT , 0 , - 1 , ( void * ) "PRNDLController" } ,
{ "jxq024b10v" , MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT , 0 , - 1 , ( void * )
"PRNDLController" } , { "iojfwkpo2e" , MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT , 0 ,
- 1 , ( void * ) "PRNDLController" } , { "otjirroues" ,
MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT , 0 , - 1 , ( void * ) "PRNDLController" } ,
{ "ibsopqppuy" , MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT , 0 , - 1 , ( void * )
"PRNDLController" } , { "apq0itlzhx" , MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT , 0 ,
- 1 , ( void * ) "PRNDLController" } , { "fotnkdml2q" ,
MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT , 0 , - 1 , ( void * ) "PRNDLController" } ,
{ "co0xztiide0" , MDL_INFO_NAME_MDLREF_DWORK , 0 , - 1 , ( void * )
"PRNDLController" } , { "ki13um5dqr" , MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT , 0 ,
- 1 , ( void * ) "PRNDLController" } , { "ji3ay1hx4z" ,
MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT , 0 , - 1 , ( void * ) "PRNDLController" } ,
{ "gbca2omkbl" , MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT , 0 , - 1 , ( void * )
"PRNDLController" } , { "a4oaezplpa" , MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT , 0 ,
- 1 , ( void * ) "PRNDLController" } , { "iy3ipzwxtk" ,
MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT , 0 , - 1 , ( void * ) "PRNDLController" } ,
{ "eyfxiyli2d" , MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT , 0 , - 1 , ( void * )
"PRNDLController" } , { "kcjasopilv" , MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT , 0 ,
- 1 , ( void * ) "PRNDLController" } , { "ndcl02pi23" ,
MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT , 0 , - 1 , ( void * ) "PRNDLController" } ,
{ "afrnrzpv0j" , MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT , 0 , - 1 , ( void * )
"PRNDLController" } , { "a3lqbyujoh" , MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT , 0 ,
- 1 , ( void * ) "PRNDLController" } , { "me5fy0j3vp" ,
MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT , 0 , - 1 , ( void * ) "PRNDLController" } ,
{ "pxshinjyri" , MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT , 0 , - 1 , ( void * )
"PRNDLController" } , { "kkxbltx1cp" , MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT , 0 ,
- 1 , ( void * ) "PRNDLController" } , { "hijclorvt4" ,
MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT , 0 , - 1 , ( void * ) "PRNDLController" } ,
{ "iaqi3xc5te" , MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT , 0 , - 1 , ( void * )
"PRNDLController" } , { "gfu5so5aoy" , MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT , 0 ,
- 1 , ( void * ) "PRNDLController" } , { "n3ntwvsrxl" ,
MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT , 0 , - 1 , ( void * ) "PRNDLController" } ,
{ "i1jvkksbsa" , MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT , 0 , - 1 , ( void * )
"PRNDLController" } , { "bd4kosf0po" , MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT , 0 ,
- 1 , ( void * ) "PRNDLController" } , { "pyx05adf24" ,
MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT , 0 , - 1 , ( void * ) "PRNDLController" } ,
{ "adgpgs52hf" , MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT , 0 , - 1 , ( void * )
"PRNDLController" } , { "mkvwmlqxwd" , MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT , 0 ,
- 1 , ( void * ) "PRNDLController" } , { "ha5314fjrw" ,
MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT , 0 , - 1 , ( void * ) "PRNDLController" } ,
{ "c11l3fzu4t" , MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT , 0 , - 1 , ( void * )
"PRNDLController" } , { "po2zyegemw" , MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT , 0 ,
- 1 , ( void * ) "PRNDLController" } , { "b5ajx0sjun" ,
MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT , 0 , - 1 , ( void * ) "PRNDLController" } ,
{ "a0wthexki1" , MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT , 0 , - 1 , ( void * )
"PRNDLController" } , { "otvydtem30" , MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT , 0 ,
- 1 , ( void * ) "PRNDLController" } , { "mnzk1u4gk2" ,
MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT , 0 , - 1 , ( void * ) "PRNDLController" } ,
{ "ir0ttputjw" , MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT , 0 , - 1 , ( void * )
"PRNDLController" } , { "ljukzwcq0g" , MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT , 0 ,
0 , ( void * ) "LugCheck" } , { "PRNDLController" ,
MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT , 0 , 0 , ( NULL ) } , { "fxsdmxnzko" ,
MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT , 0 , - 1 , ( void * ) "PRNDLController" } ,
{ "ku2evzhqltp" , MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT , 0 , - 1 , ( void * )
"PRNDLController" } , { "p3hhjb2ky5" , MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT , 0 ,
- 1 , ( void * ) "PRNDLController" } , { "ejdirckwac" ,
MDL_INFO_ID_GLOBAL_RTW_CONSTRUCT , 0 , - 1 , ( void * ) "PRNDLController" } ,
{ "mr_PRNDLController_GetSimStateDisallowedBlocks" ,
MDL_INFO_ID_MODEL_FCN_NAME , 0 , - 1 , ( void * ) "PRNDLController" } , {
"mr_PRNDLController_extractBitFieldFromCellArrayWithOffset" ,
MDL_INFO_ID_MODEL_FCN_NAME , 0 , - 1 , ( void * ) "PRNDLController" } , {
"mr_PRNDLController_cacheBitFieldToCellArrayWithOffset" ,
MDL_INFO_ID_MODEL_FCN_NAME , 0 , - 1 , ( void * ) "PRNDLController" } , {
"mr_PRNDLController_restoreDataFromMxArrayWithOffset" ,
MDL_INFO_ID_MODEL_FCN_NAME , 0 , - 1 , ( void * ) "PRNDLController" } , {
"mr_PRNDLController_cacheDataToMxArrayWithOffset" ,
MDL_INFO_ID_MODEL_FCN_NAME , 0 , - 1 , ( void * ) "PRNDLController" } , {
"mr_PRNDLController_extractBitFieldFromMxArray" , MDL_INFO_ID_MODEL_FCN_NAME
, 0 , - 1 , ( void * ) "PRNDLController" } , {
"mr_PRNDLController_cacheBitFieldToMxArray" , MDL_INFO_ID_MODEL_FCN_NAME , 0
, - 1 , ( void * ) "PRNDLController" } , {
"mr_PRNDLController_restoreDataFromMxArray" , MDL_INFO_ID_MODEL_FCN_NAME , 0
, - 1 , ( void * ) "PRNDLController" } , {
"mr_PRNDLController_cacheDataAsMxArray" , MDL_INFO_ID_MODEL_FCN_NAME , 0 , -
1 , ( void * ) "PRNDLController" } , {
"mr_PRNDLController_RegisterSimStateChecksum" , MDL_INFO_ID_MODEL_FCN_NAME ,
0 , - 1 , ( void * ) "PRNDLController" } , { "mr_PRNDLController_SetDWork" ,
MDL_INFO_ID_MODEL_FCN_NAME , 0 , - 1 , ( void * ) "PRNDLController" } , {
"mr_PRNDLController_GetDWork" , MDL_INFO_ID_MODEL_FCN_NAME , 0 , - 1 , ( void
* ) "PRNDLController" } , { "PRNDLController.h" , MDL_INFO_MODEL_FILENAME , 0
, - 1 , ( NULL ) } , { "PRNDLController.c" , MDL_INFO_MODEL_FILENAME , 0 , -
1 , ( void * ) "PRNDLController" } } ; ku2evzhqltp ku2evzhqlt = { { 1.0 , 2.0
} , { 2.0 , 3.0 , 4.0 , 5.0 , 6.0 , 7.0 , 8.0 } , { 5.0 , 15.0 , 25.0 , 35.0
, 20.0 , 30.0 , 40.0 , 50.0 , 30.0 , 40.0 , 50.0 , 60.0 , 40.0 , 50.0 , 60.0
, 70.0 , 50.0 , 60.0 , 70.0 , 80.0 , 60.0 , 70.0 , 80.0 , 90.0 , 70.0 , 80.0
, 90.0 , 100.0 , 5.0 , 15.0 , 25.0 , 35.0 , 20.0 , 30.0 , 40.0 , 50.0 , 30.0
, 40.0 , 50.0 , 60.0 , 40.0 , 50.0 , 60.0 , 70.0 , 50.0 , 60.0 , 70.0 , 80.0
, 60.0 , 70.0 , 80.0 , 90.0 , 70.0 , 80.0 , 90.0 , 100.0 } , 0.0 , 1200.0 ,
2000.0 , { 1.0 , 2.0 } , { 1.0 , 2.0 , 3.0 , 4.0 , 5.0 , 6.0 , 7.0 } , { 20.0
, 30.0 , 40.0 , 50.0 , 30.0 , 40.0 , 50.0 , 60.0 , 40.0 , 50.0 , 60.0 , 70.0
, 50.0 , 60.0 , 70.0 , 80.0 , 60.0 , 70.0 , 80.0 , 90.0 , 70.0 , 80.0 , 90.0
, 100.0 , 80.0 , 100.0 , 120.0 , 160.0 , 20.0 , 30.0 , 40.0 , 50.0 , 30.0 ,
40.0 , 50.0 , 60.0 , 40.0 , 50.0 , 60.0 , 70.0 , 50.0 , 60.0 , 70.0 , 80.0 ,
60.0 , 70.0 , 80.0 , 90.0 , 70.0 , 80.0 , 90.0 , 100.0 , 80.0 , 100.0 , 120.0
, 160.0 } , 0.1 , 0.1 , 0.0 , { 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 } , {
0.0 , 0.0 , 0.0 , 0.0 } , 0.0 , { 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 } ,
{ 0.0 , 0.0 , 0.0 , 0.0 } , 8.0 , 120.0 , 0.5 , 1.0 , { 3U , 6U , 1U } , { 1U
, 4U , 28U } , { 3U , 6U , 1U } , { 1U , 4U , 28U } , { 0.0 , { 0.0 , 1.0 } ,
{ 0.0 , 200.0 } , 0.75 , 0.25 , 1.0 , 0.0 } } ; void a0wthexki1 ( fotnkdml2q
* localB , ibsopqppuy * localP ) { localB -> bpvfrxxenp = localP -> P_0 ; }
void ljukzwcq0g ( real_T oa5p3m3qsc , real_T df4l0rp0tc , fotnkdml2q * localB
, apq0itlzhx * localDW , ibsopqppuy * localP ) { real_T narbgkhhkc ;
narbgkhhkc = look1_binlcpw ( df4l0rp0tc - oa5p3m3qsc , localP -> P_2 , localP
-> P_1 , 1U ) ; localDW -> arzbauqvr1 = ( ( narbgkhhkc >= localP -> P_3 ) ||
( ( ! ( narbgkhhkc <= localP -> P_4 ) ) && localDW -> arzbauqvr1 ) ) ; if ( localDW -> arzbauqvr1 ) { localB -> bpvfrxxenp = localP -> P_5 ; } else { localB -> bpvfrxxenp = localP -> P_6 ; } localDW -> eob4a4cufc = 4 ; } void pyx05adf24 ( real_T * jnp1raxxu4 , kkxbltx1cp * localB , pxshinjyri * localDW ) { localDW -> mm1nentbay = 0U ; localDW -> p0okmflqxc = 0U ; * jnp1raxxu4 = 0.0 ; localDW -> jfic0kod3c = 0.0 ; localDW -> cuvupd35at = 0.0 ; localDW -> ldwjb4dssl = 0U ; localDW -> msbebgy5zi = jcwvjyrxps ; localDW -> j1mvd0fbmo = jcwvjyrxps ; a0wthexki1 ( & localB -> ljukzwcq0g1 , & ku2evzhqlt . ljukzwcq0g1 ) ; } void bd4kosf0po ( real_T * jnp1raxxu4 , pxshinjyri * localDW ) { localDW -> mm1nentbay = 0U ; localDW -> p0okmflqxc = 0U ; * jnp1raxxu4 = 0.0 ; localDW -> jfic0kod3c = 0.0 ; localDW -> cuvupd35at = 0.0 ; localDW -> ldwjb4dssl = 0U ; localDW -> msbebgy5zi = jcwvjyrxps ; localDW -> j1mvd0fbmo = jcwvjyrxps ; } void PRNDLController ( const real_T * dugx2nyefg , const real_T hh0gyc1nkz [ 2 ] , const real_T ass25qmj2n [ 2 ] , const real_T * bg0ejuvboy , const real_T * f1l10b3cai , const boolean_T np4i5bxs5u [ 2 ] , real_T * jnp1raxxu4 , kkxbltx1cp * localB , pxshinjyri * localDW ) { real_T fractions [ 3 ] ; real_T fractions_p [ 3 ] ; real_T fyhqjoahnx ; real_T h2qokyky50 ; real_T nptu0pfroh ; real_T p2lckh1vgy_p ; uint32_T bpIndices [ 3 ] ; uint32_T bpIndices_p [ 3 ] ; boolean_T of4dexp3nz ; of4dexp3nz = ( np4i5bxs5u [ 0 ] || np4i5bxs5u [ 1 ] ) ; fyhqjoahnx = ( rtP__TireFrntWhlRadius2f2MotoWheel_sldd_ + rtP__TireRearWhlRadius2f2MotoWheel_sldd_ ) / 2.0 * muDoubleScalarAbs ( ass25qmj2n [ 0 ] + ass25qmj2n [ 1 ] ) * 3.5999999999999996 ; h2qokyky50 = 9.5492965855137211 * * bg0ejuvboy ; if ( localDW -> mm1nentbay < MAX_uint32_T ) { localDW -> mm1nentbay ++ ; } if ( localDW -> p0okmflqxc < MAX_uint32_T ) { localDW -> p0okmflqxc ++ ; } if ( localDW -> ldwjb4dssl == 0 ) { localDW -> ldwjb4dssl = 1U ; * jnp1raxxu4 = ku2evzhqlt . P_7 ; if ( ku2evzhqlt . P_7 == 80.0 ) { localDW -> msbebgy5zi = japeuimdgw ; * jnp1raxxu4 = 80.0 ; localDW -> cuvupd35at = 0.0 ; } else if ( ku2evzhqlt . P_7 < 0.0 ) { localDW -> msbebgy5zi = ddvm0y4hod ; * jnp1raxxu4 = - 1.0 ; localDW -> cuvupd35at = 0.0 ; } else if ( ku2evzhqlt . P_7 == 0.0 ) { localDW -> mm1nentbay = 0U ; localDW -> msbebgy5zi = anf2nyqqlb ; * jnp1raxxu4 = 0.0 ; localDW -> cuvupd35at = 0.0 ; } else { localDW -> msbebgy5zi = evccign45j ; } if ( localDW -> cuvupd35at == 1.0 ) { localDW -> j1mvd0fbmo = bljendk0zq ; } else { localDW -> j1mvd0fbmo = oj3rltsxbh ; * jnp1raxxu4 = 0.0 ; } } else { switch ( localDW -> msbebgy5zi ) { case evccign45j : if ( ( ( localDW -> jfic0kod3c != 0.0 ) && ( * dugx2nyefg < 0.01 ) && ( ( * jnp1raxxu4 == 1.0 ) || ( * jnp1raxxu4 == 2.0 ) ) ) || of4dexp3nz || ( * f1l10b3cai == 0.0 ) ) { localDW -> mm1nentbay = 0U ; localDW -> msbebgy5zi = anf2nyqqlb ; * jnp1raxxu4 = 0.0 ; localDW -> cuvupd35at = 0.0 ; } else { ljukzwcq0g ( h2qokyky50 , ku2evzhqlt . P_8 , & localB -> ljukzwcq0g1 , & localDW -> ljukzwcq0g1 , & ku2evzhqlt . ljukzwcq0g1 ) ; localDW -> jfic0kod3c = localB -> ljukzwcq0g1 . bpvfrxxenp ; localDW -> cuvupd35at = 1.0 ; } break ; case anf2nyqqlb : of4dexp3nz = ! of4dexp3nz ; if ( ( * dugx2nyefg >= 0.1 ) && of4dexp3nz && ( h2qokyky50 >= ku2evzhqlt . P_9 ) ) { * jnp1raxxu4 = 1.0 ; localDW -> msbebgy5zi = evccign45j ; } else if ( ( * f1l10b3cai == - 1.0 ) && of4dexp3nz ) { localDW -> msbebgy5zi = ddvm0y4hod ; * jnp1raxxu4 = - 1.0 ; localDW -> cuvupd35at = 0.0 ; } else if ( ( localDW -> mm1nentbay >= ( uint32_T ) muDoubleScalarCeil ( ku2evzhqlt . P_22 * 1000.0 ) ) && ( ( * f1l10b3cai == 80.0 ) && ( ( hh0gyc1nkz [ 0 ] + hh0gyc1nkz [ 1 ] ) * ku2evzhqlt . P_23 > 0.5 ) && ( muDoubleScalarAbs ( fyhqjoahnx ) <= 1.0 ) && ( * dugx2nyefg > 0.0 ) && ( * dugx2nyefg <= 0.05 ) ) ) { localDW -> msbebgy5zi = japeuimdgw ; * jnp1raxxu4 = 80.0 ; localDW -> cuvupd35at = 0.0 ; } else { ljukzwcq0g ( h2qokyky50 , ku2evzhqlt . P_8 , & localB -> ljukzwcq0g1 , & localDW -> ljukzwcq0g1 , & ku2evzhqlt . ljukzwcq0g1 ) ; localDW -> jfic0kod3c = localB -> ljukzwcq0g1 . bpvfrxxenp ; } break ; case japeuimdgw : if ( ( muDoubleScalarAbs ( fyhqjoahnx ) <= 1.0 ) && ( * dugx2nyefg > 0.0 ) ) { localDW -> mm1nentbay = 0U ; localDW -> msbebgy5zi = anf2nyqqlb ; * jnp1raxxu4 = 0.0 ; localDW -> cuvupd35at = 0.0 ; } break ; default : if ( ( * f1l10b3cai == 1.0 ) || of4dexp3nz ) { localDW -> mm1nentbay = 0U ; localDW -> msbebgy5zi = anf2nyqqlb ; * jnp1raxxu4 = 0.0 ; localDW -> cuvupd35at = 0.0 ; } break ; } bpIndices [ 0U ] = plook_binc ( * dugx2nyefg , rtP__CtrlTcuUpLdBpt2f2Drivetrain_sldd_ , 3U , & p2lckh1vgy_p ) ; fractions [ 0U ] = p2lckh1vgy_p ; bpIndices [ 1U ] = plook_binc ( * jnp1raxxu4 , ku2evzhqlt . P_11 , 6U , & p2lckh1vgy_p ) ; fractions [ 1U ] = p2lckh1vgy_p ; bpIndices [ 2U ] = plook_binc ( ku2evzhqlt . P_24 , ku2evzhqlt . P_10 , 1U , & p2lckh1vgy_p ) ; fractions [ 2U ] = p2lckh1vgy_p ; nptu0pfroh = ( intrp3d_l_pw ( bpIndices , fractions , ku2evzhqlt . P_12 , ku2evzhqlt . P_26 ) + look1_binlcapw ( * jnp1raxxu4 , ku2evzhqlt . P_11 , ku2evzhqlt . P_16 , 6U ) ) + look1_binlcapw ( * dugx2nyefg , rtP__CtrlTcuUpLdBpt2f2Drivetrain_sldd_ , ku2evzhqlt . P_17 , 3U ) ; localDW -> jz3yqpyzsk = 4 ; bpIndices_p [ 0U ] = plook_binc ( * dugx2nyefg , rtP__CtrlTcuDnLdBpt2f2Drivetrain_sldd_ , 3U , & p2lckh1vgy_p ) ; fractions_p [ 0U ] = p2lckh1vgy_p ; bpIndices_p [ 1U ] = plook_binc ( * jnp1raxxu4 , ku2evzhqlt . P_5 , 6U , & p2lckh1vgy_p ) ; fractions_p [ 1U ] = p2lckh1vgy_p ; bpIndices_p [ 2U ] = plook_binc ( ku2evzhqlt . P_24 , ku2evzhqlt . P_4 , 1U , & p2lckh1vgy_p ) ; fractions_p [ 2U ] = p2lckh1vgy_p ; p2lckh1vgy_p = ( intrp3d_l_pw ( bpIndices_p , fractions_p , ku2evzhqlt . P_6 , ku2evzhqlt . P_28 ) + look1_binlcapw ( * jnp1raxxu4 , ku2evzhqlt . P_5 , ku2evzhqlt . P_19 , 6U ) ) + look1_binlcapw ( * dugx2nyefg , rtP__CtrlTcuDnLdBpt2f2Drivetrain_sldd_ , ku2evzhqlt . P_20 , 3U ) ; localDW -> jzuqcidcqp = 4 ; switch ( localDW -> j1mvd0fbmo ) { case k5vrhoaqhz : if ( ( ( fyhqjoahnx >= p2lckh1vgy_p ) && ( ! ( localDW -> jfic0kod3c != 0.0 ) ) ) || ( * jnp1raxxu4 < 1.0 ) ) { localDW -> j1mvd0fbmo = bljendk0zq ; } else if ( * jnp1raxxu4 > 1.0 ) { ( * jnp1raxxu4 ) -- ; localDW -> j1mvd0fbmo = bljendk0zq ; } break ; case oj3rltsxbh : if ( localDW -> cuvupd35at == 1.0 ) { localDW -> j1mvd0fbmo = bljendk0zq ; } break ; case bljendk0zq : if ( localDW -> cuvupd35at != 1.0 ) { localDW -> j1mvd0fbmo = oj3rltsxbh ; * jnp1raxxu4 = 0.0 ; } else if ( ( ( fyhqjoahnx < p2lckh1vgy_p ) || ( localDW -> jfic0kod3c != 0.0 ) ) && ( * jnp1raxxu4 > 1.0 ) ) { localDW -> p0okmflqxc = 0U ; localDW -> j1mvd0fbmo = c3tscmpimb ; } else if ( ( fyhqjoahnx > nptu0pfroh ) && ( * jnp1raxxu4 <= ku2evzhqlt . P_21 - 1.0 ) && ( h2qokyky50 >= ku2evzhqlt . P_9 ) ) { localDW -> p0okmflqxc = 0U ; localDW -> j1mvd0fbmo = igvqestgao ; } break ; case hgqxqzz5jy : if ( ( ! ( fyhqjoahnx <= nptu0pfroh ) ) && ( ! ( localDW -> jfic0kod3c != 0.0 ) ) ) { ( * jnp1raxxu4 ) ++ ; } localDW -> j1mvd0fbmo = bljendk0zq ; break ; case c3tscmpimb : if ( ( localDW -> p0okmflqxc >= ( uint32_T ) muDoubleScalarCeil ( ku2evzhqlt . P_13 * 1000.0 ) ) && ( ( fyhqjoahnx < p2lckh1vgy_p ) || ( localDW -> jfic0kod3c != 0.0 ) ) ) { localDW -> j1mvd0fbmo = k5vrhoaqhz ; } else if ( ( fyhqjoahnx >= p2lckh1vgy_p ) && ( ! ( localDW -> jfic0kod3c != 0.0 ) ) ) { localDW -> j1mvd0fbmo = bljendk0zq ; } break ; default : if ( ( localDW -> p0okmflqxc >= ( uint32_T ) muDoubleScalarCeil ( ku2evzhqlt . P_14 * 1000.0 ) ) && ( fyhqjoahnx > nptu0pfroh ) ) { localDW -> j1mvd0fbmo = hgqxqzz5jy ; } else if ( ( fyhqjoahnx <= nptu0pfroh ) || ( localDW -> jfic0kod3c != 0.0 ) ) { localDW -> j1mvd0fbmo = bljendk0zq ; } break ; } } } void iaqi3xc5te ( ejdirckwac * const fdopgmryi2 ) { if ( ! slIsRapidAcceleratorSimulating ( ) ) { slmrRunPluginEvent ( fdopgmryi2 -> _mdlRefSfcnS , "PRNDLController" , "SIMSTATUS_TERMINATING_MODELREF_ACCEL_EVENT" ) ; } } void adgpgs52hf ( SimStruct * _mdlRefSfcnS , int_T mdlref_TID0 , int_T mdlref_TID1 , ejdirckwac * const fdopgmryi2 , kkxbltx1cp * localB , pxshinjyri * localDW , void * sysRanPtr , int contextTid , rtwCAPI_ModelMappingInfo * rt_ParentMMI , const char_T * rt_ChildPath , int_T rt_ChildMMIIdx , int_T rt_CSTATEIdx ) { ( void ) memset ( ( void * ) fdopgmryi2 , 0 , sizeof ( ejdirckwac ) ) ; fdopgmryi2 -> Timing . mdlref_GlobalTID [ 0 ] = mdlref_TID0 ; fdopgmryi2 -> Timing . mdlref_GlobalTID [ 1 ] = mdlref_TID1 ; fdopgmryi2 -> _mdlRefSfcnS = ( _mdlRefSfcnS ) ; if ( ! slIsRapidAcceleratorSimulating ( ) ) { slmrRunPluginEvent ( fdopgmryi2 -> _mdlRefSfcnS , "PRNDLController" , "START_OF_SIM_MODEL_MODELREF_ACCEL_EVENT" ) ; } ( void ) memset ( ( ( void * ) localB ) , 0 , sizeof ( kkxbltx1cp ) ) ; ( void ) memset ( ( void * ) localDW , 0 , sizeof ( pxshinjyri ) ) ; PRNDLController_InitializeDataMapInfo ( fdopgmryi2 , localDW , sysRanPtr , contextTid ) ; if ( ( rt_ParentMMI != ( NULL ) ) && ( rt_ChildPath != ( NULL ) ) ) { rtwCAPI_SetChildMMI ( * rt_ParentMMI , rt_ChildMMIIdx , & ( fdopgmryi2 -> DataMapInfo . mmi ) ) ; rtwCAPI_SetPath ( fdopgmryi2 -> DataMapInfo . mmi , rt_ChildPath ) ; rtwCAPI_MMISetContStateStartIndex ( fdopgmryi2 -> DataMapInfo . mmi , rt_CSTATEIdx ) ; } } void mr_PRNDLController_MdlInfoRegFcn ( SimStruct * mdlRefSfcnS , char_T * modelName , int_T * retVal ) { * retVal = 0 ; { boolean_T regSubmodelsMdlinfo = false ; ssGetRegSubmodelsMdlinfo ( mdlRefSfcnS , & regSubmodelsMdlinfo ) ; if ( regSubmodelsMdlinfo ) { } } * retVal = 0 ; ssRegModelRefMdlInfo ( mdlRefSfcnS , modelName , rtMdlInfo_PRNDLController , 64 ) ; * retVal = 1 ; } static void mr_PRNDLController_cacheDataAsMxArray ( mxArray * destArray , mwIndex i , int j , const void * srcData , size_t numBytes ) ; static void mr_PRNDLController_cacheDataAsMxArray ( mxArray * destArray , mwIndex i , int j , const void * srcData , size_t numBytes ) { mxArray * newArray = mxCreateUninitNumericMatrix ( ( size_t ) 1 , numBytes , mxUINT8_CLASS , mxREAL ) ; memcpy ( ( uint8_T * ) mxGetData ( newArray ) , ( const uint8_T * ) srcData , numBytes ) ; mxSetFieldByNumber ( destArray , i , j , newArray ) ; } static void mr_PRNDLController_restoreDataFromMxArray ( void * destData , const mxArray * srcArray , mwIndex i , int j , size_t numBytes ) ; static void mr_PRNDLController_restoreDataFromMxArray ( void * destData , const mxArray * srcArray , mwIndex i , int j , size_t numBytes ) { memcpy ( ( uint8_T * ) destData , ( const uint8_T * ) mxGetData ( mxGetFieldByNumber ( srcArray , i , j ) ) , numBytes ) ; } static void mr_PRNDLController_cacheBitFieldToMxArray ( mxArray * destArray , mwIndex i , int j , uint_T bitVal ) ; static void mr_PRNDLController_cacheBitFieldToMxArray ( mxArray * destArray , mwIndex i , int j , uint_T bitVal ) { mxSetFieldByNumber ( destArray , i , j , mxCreateDoubleScalar ( ( real_T ) bitVal ) ) ; } static uint_T mr_PRNDLController_extractBitFieldFromMxArray ( const mxArray * srcArray , mwIndex i , int j , uint_T numBits ) ; static uint_T mr_PRNDLController_extractBitFieldFromMxArray ( const mxArray * srcArray , mwIndex i , int j , uint_T numBits ) { const uint_T varVal = ( uint_T ) mxGetScalar ( mxGetFieldByNumber ( srcArray , i , j ) ) ; return varVal & ( ( 1u << numBits ) - 1u ) ; } static void mr_PRNDLController_cacheDataToMxArrayWithOffset ( mxArray * destArray , mwIndex i , int j , mwIndex offset , const void * srcData , size_t numBytes ) ; static void mr_PRNDLController_cacheDataToMxArrayWithOffset ( mxArray * destArray , mwIndex i , int j , mwIndex offset , const void * srcData , size_t numBytes ) { uint8_T * varData = ( uint8_T * ) mxGetData ( mxGetFieldByNumber ( destArray , i , j ) ) ; memcpy ( ( uint8_T * ) & varData [ offset * numBytes ] , ( const uint8_T * ) srcData , numBytes ) ; } static void mr_PRNDLController_restoreDataFromMxArrayWithOffset ( void * destData , const mxArray * srcArray , mwIndex i , int j , mwIndex offset , size_t numBytes ) ; static void mr_PRNDLController_restoreDataFromMxArrayWithOffset ( void * destData , const mxArray * srcArray , mwIndex i , int j , mwIndex offset , size_t numBytes ) { const uint8_T * varData = ( const uint8_T * ) mxGetData ( mxGetFieldByNumber ( srcArray , i , j ) ) ; memcpy ( ( uint8_T * ) destData , ( const uint8_T * ) & varData [ offset * numBytes ] , numBytes ) ; } static void mr_PRNDLController_cacheBitFieldToCellArrayWithOffset ( mxArray * destArray , mwIndex i , int j , mwIndex offset , uint_T fieldVal ) ; static void mr_PRNDLController_cacheBitFieldToCellArrayWithOffset ( mxArray * destArray , mwIndex i , int j , mwIndex offset , uint_T fieldVal ) { mxSetCell ( mxGetFieldByNumber ( destArray , i , j ) , offset , mxCreateDoubleScalar ( ( real_T ) fieldVal ) ) ; } static uint_T mr_PRNDLController_extractBitFieldFromCellArrayWithOffset ( const mxArray * srcArray , mwIndex i , int j , mwIndex offset , uint_T numBits ) ; static uint_T mr_PRNDLController_extractBitFieldFromCellArrayWithOffset ( const mxArray * srcArray , mwIndex i , int j , mwIndex offset , uint_T numBits ) { const uint_T fieldVal = ( uint_T ) mxGetScalar ( mxGetCell ( mxGetFieldByNumber ( srcArray , i , j ) , offset ) ) ; return fieldVal & ( ( 1u << numBits ) - 1u ) ; } mxArray * mr_PRNDLController_GetDWork ( const co0xztiide0 * mdlrefDW ) { static const char_T * ssDWFieldNames [ 3 ] = { "rtb" , "rtdw" , "NULL->rtzce" , } ; mxArray * ssDW = mxCreateStructMatrix ( 1 , 1 , 3 , ssDWFieldNames ) ; mr_PRNDLController_cacheDataAsMxArray ( ssDW , 0 , 0 , ( const void * ) & ( mdlrefDW -> rtb ) , sizeof ( mdlrefDW -> rtb ) ) ; { static const char_T * rtdwDataFieldNames [ 11 ] = { "mdlrefDW->rtdw.jfic0kod3c" , "mdlrefDW->rtdw.cuvupd35at" , "mdlrefDW->rtdw.mm1nentbay" , "mdlrefDW->rtdw.p0okmflqxc" , "mdlrefDW->rtdw.jzuqcidcqp" , "mdlrefDW->rtdw.jz3yqpyzsk" , "mdlrefDW->rtdw.ldwjb4dssl" , "mdlrefDW->rtdw.msbebgy5zi" , "mdlrefDW->rtdw.j1mvd0fbmo" , "mdlrefDW->rtdw.ljukzwcq0g1.eob4a4cufc" , "mdlrefDW->rtdw.ljukzwcq0g1.arzbauqvr1" , } ; mxArray * rtdwData = mxCreateStructMatrix ( 1 , 1 , 11 , rtdwDataFieldNames ) ; mr_PRNDLController_cacheDataAsMxArray ( rtdwData , 0 , 0 , ( const void * ) & ( mdlrefDW -> rtdw . jfic0kod3c ) , sizeof ( mdlrefDW -> rtdw . jfic0kod3c ) ) ; mr_PRNDLController_cacheDataAsMxArray ( rtdwData , 0 , 1 , ( const void * ) & ( mdlrefDW -> rtdw . cuvupd35at ) , sizeof ( mdlrefDW -> rtdw . cuvupd35at ) ) ; mr_PRNDLController_cacheDataAsMxArray ( rtdwData , 0 , 2 , ( const void * ) & ( mdlrefDW -> rtdw . mm1nentbay ) , sizeof ( mdlrefDW -> rtdw . mm1nentbay ) ) ; mr_PRNDLController_cacheDataAsMxArray ( rtdwData , 0 , 3 , ( const void * ) & ( mdlrefDW -> rtdw . p0okmflqxc ) , sizeof ( mdlrefDW -> rtdw . p0okmflqxc ) ) ; mr_PRNDLController_cacheDataAsMxArray ( rtdwData , 0 , 4 , ( const void * ) & ( mdlrefDW -> rtdw . jzuqcidcqp ) , sizeof ( mdlrefDW -> rtdw . jzuqcidcqp ) ) ; mr_PRNDLController_cacheDataAsMxArray ( rtdwData , 0 , 5 , ( const void * ) & ( mdlrefDW -> rtdw . jz3yqpyzsk ) , sizeof ( mdlrefDW -> rtdw . jz3yqpyzsk ) ) ; mr_PRNDLController_cacheDataAsMxArray ( rtdwData , 0 , 6 , ( const void * ) & ( mdlrefDW -> rtdw . ldwjb4dssl ) , sizeof ( mdlrefDW -> rtdw . ldwjb4dssl ) ) ; mr_PRNDLController_cacheDataAsMxArray ( rtdwData , 0 , 7 , ( const void * ) & ( mdlrefDW -> rtdw . msbebgy5zi ) , sizeof ( mdlrefDW -> rtdw . msbebgy5zi ) ) ; mr_PRNDLController_cacheDataAsMxArray ( rtdwData , 0 , 8 , ( const void * ) & ( mdlrefDW -> rtdw . j1mvd0fbmo ) , sizeof ( mdlrefDW -> rtdw . j1mvd0fbmo ) ) ; mr_PRNDLController_cacheDataAsMxArray ( rtdwData , 0 , 9 , ( const void * ) & ( mdlrefDW -> rtdw . ljukzwcq0g1 . eob4a4cufc ) , sizeof ( mdlrefDW -> rtdw . ljukzwcq0g1 . eob4a4cufc ) ) ; mr_PRNDLController_cacheDataAsMxArray ( rtdwData , 0 , 10 , ( const void * ) & ( mdlrefDW -> rtdw . ljukzwcq0g1 . arzbauqvr1 ) , sizeof ( mdlrefDW -> rtdw . ljukzwcq0g1 . arzbauqvr1 ) ) ; mxSetFieldByNumber ( ssDW , 0 , 1 , rtdwData ) ; } ( void ) mdlrefDW ; return ssDW ; } void mr_PRNDLController_SetDWork ( co0xztiide0 * mdlrefDW , const mxArray * ssDW ) { ( void ) ssDW ; ( void ) mdlrefDW ; mr_PRNDLController_restoreDataFromMxArray ( ( void * ) & ( mdlrefDW -> rtb ) , ssDW , 0 , 0 , sizeof ( mdlrefDW -> rtb ) ) ; { const mxArray * rtdwData = mxGetFieldByNumber ( ssDW , 0 , 1 ) ; mr_PRNDLController_restoreDataFromMxArray ( ( void * ) & ( mdlrefDW -> rtdw . jfic0kod3c ) , rtdwData , 0 , 0 , sizeof ( mdlrefDW -> rtdw . jfic0kod3c ) ) ; mr_PRNDLController_restoreDataFromMxArray ( ( void * ) & ( mdlrefDW -> rtdw . cuvupd35at ) , rtdwData , 0 , 1 , sizeof ( mdlrefDW -> rtdw . cuvupd35at ) ) ; mr_PRNDLController_restoreDataFromMxArray ( ( void * ) & ( mdlrefDW -> rtdw . mm1nentbay ) , rtdwData , 0 , 2 , sizeof ( mdlrefDW -> rtdw . mm1nentbay ) ) ; mr_PRNDLController_restoreDataFromMxArray ( ( void * ) & ( mdlrefDW -> rtdw . p0okmflqxc ) , rtdwData , 0 , 3 , sizeof ( mdlrefDW -> rtdw . p0okmflqxc ) ) ; mr_PRNDLController_restoreDataFromMxArray ( ( void * ) & ( mdlrefDW -> rtdw . jzuqcidcqp ) , rtdwData , 0 , 4 , sizeof ( mdlrefDW -> rtdw . jzuqcidcqp ) ) ; mr_PRNDLController_restoreDataFromMxArray ( ( void * ) & ( mdlrefDW -> rtdw . jz3yqpyzsk ) , rtdwData , 0 , 5 , sizeof ( mdlrefDW -> rtdw . jz3yqpyzsk ) ) ; mr_PRNDLController_restoreDataFromMxArray ( ( void * ) & ( mdlrefDW -> rtdw . ldwjb4dssl ) , rtdwData , 0 , 6 , sizeof ( mdlrefDW -> rtdw . ldwjb4dssl ) ) ; mr_PRNDLController_restoreDataFromMxArray ( ( void * ) & ( mdlrefDW -> rtdw . msbebgy5zi ) , rtdwData , 0 , 7 , sizeof ( mdlrefDW -> rtdw . msbebgy5zi ) ) ; mr_PRNDLController_restoreDataFromMxArray ( ( void * ) & ( mdlrefDW -> rtdw . j1mvd0fbmo ) , rtdwData , 0 , 8 , sizeof ( mdlrefDW -> rtdw . j1mvd0fbmo ) ) ; mr_PRNDLController_restoreDataFromMxArray ( ( void * ) & ( mdlrefDW -> rtdw . ljukzwcq0g1 . eob4a4cufc ) , rtdwData , 0 , 9 , sizeof ( mdlrefDW -> rtdw . ljukzwcq0g1 . eob4a4cufc ) ) ; mr_PRNDLController_restoreDataFromMxArray ( ( void * ) & ( mdlrefDW -> rtdw . ljukzwcq0g1 . arzbauqvr1 ) , rtdwData , 0 , 10 , sizeof ( mdlrefDW -> rtdw . ljukzwcq0g1 . arzbauqvr1 ) ) ; } } void mr_PRNDLController_RegisterSimStateChecksum ( SimStruct * S ) { const uint32_T chksum [ 4 ] = { 1600033070U , 1578012278U , 2934961905U , 4229512415U , } ; slmrModelRefRegisterSimStateChecksum ( S , "PRNDLController" , & chksum [ 0 ] ) ; } mxArray * mr_PRNDLController_GetSimStateDisallowedBlocks ( ) { return ( NULL ) ; }
#if defined(_MSC_VER)
#pragma warning(disable: 4505) //unreferenced local function has been removed
#endif
