/*******************************************************************************
* Copyright (C) Maxim Integrated Products, Inc., All rights Reserved.
*
* This software is protected by copyright laws of the United States and
* of foreign countries. This material may also be protected by patent laws
* and technology transfer regulations of the United States and of foreign
* countries. This software is furnished under a license agreement and/or a
* nondisclosure agreement and may only be used or reproduced in accordance
* with the terms of those agreements. Dissemination of this information to
* any party or parties not specified in the license agreement and/or
* nondisclosure agreement is expressly prohibited.
*
* The above copyright notice and this permission notice shall be included
* in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
* OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL MAXIM INTEGRATED BE LIABLE FOR ANY CLAIM, DAMAGES
* OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
* ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
* OTHER DEALINGS IN THE SOFTWARE.
*
* Except as contained in this notice, the name of Maxim Integrated
* Products, Inc. shall not be used except as stated in the Maxim Integrated
* Products, Inc. Branding Policy.
*
* The mere transfer of this software does not imply any licenses
* of trade secrets, proprietary technology, copyrights, patents,
* trademarks, maskwork rights, or any other form of intellectual
* property whatsoever. Maxim Integrated Products, Inc. retains all
* ownership rights.
*******************************************************************************
*/

#ifndef DRIVERS_ALGOWRAPPER_ALGOWRAPPER_H_
#define DRIVERS_ALGOWRAPPER_ALGOWRAPPER_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Macros for library import/export */
#if defined(WIN32) || defined(_WIN32)
#define COMPILER_INLINED
#ifdef MXM_ALGOSUITE_EXPORTS
#define MXM_ALGOSUITE_API __declspec(dllexport)
#elif defined MXM_RRM_IMPORTS
#define MXM_ALGOSUITE_API __declspec(dllimport)
#else
#define MXM_ALGOSUITE_API
#endif
#define MXM_ALGOSUITE_CALL __cdecl
#else    /* Android */
#define MXM_ALGOSUITE_API __attribute__((__visibility__("default")))
#define MXM_ALGOSUITE_CALL
#define COMPILER_INLINED __attribute__(( always_inline))
#endif

#include <stdbool.h>
#include <stdint.h>

#include "mxm_hrv_public_limited.h"
#include "mxm_sleep_manager.h"

typedef struct {

    uint32_t inp_sample_count;
    uint32_t grn_count;
    uint32_t grn2Cnt;
    uint32_t irCnt;
    uint32_t redCnt;
    int32_t accelx;
    int32_t accely;
    int32_t accelz;
    uint32_t whrm_suite_curr_opmode;
    uint32_t hearth_rate_estim;
    uint32_t hr_confidence;
    uint32_t rr_interbeat_interval;
    uint32_t rr_confidence;
    uint32_t activity_class;
    uint32_t r_spo2;
    uint32_t spo2_confidence;
    uint32_t spo2_estim;
    uint32_t spo2_calc_percentage;
    uint32_t spo2_low_sign_quality_flag;
    uint32_t spo2_motion_flag;
    uint32_t spo2_low_pi_flag;
    uint32_t spo2_unreliable_r_flag;
    uint32_t spo2_unreliable_orient_flag;
    uint32_t spo2_state;
    uint32_t skin_contact_state;
    uint32_t walk_steps;
    uint32_t run_steps;
    uint32_t kcal;
    uint32_t cadence;
    uint32_t timestampUpper32bit;
    uint32_t timestampLower32bit;

} mxm_algosuite_input_data;


typedef MxmHrvRet                                 mxm_algosuite_hrv_retcode;
typedef mxm_sleep_manager_return                  mxm_algosuite_sleep_retcode;

typedef struct {
    char version_string[20]; /**< version in vXX.XX.XX format */
    unsigned short int version;  /**< The first number in vXX.XX.XX format */
    unsigned short int sub_version;  /**< The second number in vXX.XX.XX format */
    unsigned short int sub_sub_version;  /**< The third number in vXX.XX.XX format */
} mxm_algosuite_version_str;

 typedef struct{
     mxm_algosuite_hrv_retcode hrv_status;
     mxm_algosuite_sleep_retcode sleep_status;
}mxm_algosuite_return_code;


 typedef struct {
    MxmHrvOutData 						       hrv_out_sample;
    mxm_sleep_manager_output_dataframe         sleep_out_Sample;
 } mxm_algosuite_output_data;


#define MXM_ALGOSUITE_ENABLE_HRV    ( 1 << 0)
#define MXM_ALGOSUITE_ENABLE_SLEEP  ( 1 << 2)

typedef struct {
    unsigned char                           enabledAlgorithms;
    MxmHrvConfig                            hrvConfig;
    mxm_sleep_manager_config                sleepConfig;
} mxm_algosuite_init_data;

MXM_ALGOSUITE_API void mxm_algosuite_manager_init( const mxm_algosuite_init_data *const init_str,
                                                   mxm_algosuite_return_code *const status);

MXM_ALGOSUITE_API void mxm_algosuite_manager_run( const mxm_algosuite_input_data *const data_in_str,
                                                  mxm_algosuite_output_data *const data_out_str,
                                                  mxm_algosuite_return_code *const status);

MXM_ALGOSUITE_API void mxm_algosuite_manager_end( const unsigned char tobeDisabledAlgorithms,
                                                  mxm_algosuite_return_code *const status);

MXM_ALGOSUITE_API void mxm_algosuite_manager_get_versions(mxm_algosuite_version_str *const version_str);


MXM_ALGOSUITE_API void mxm_algosuite_manager_calculate_SQI( float deep_time_in_sec,
                                                            float rem_time_in_sec,
                                                            float in_sleep_wake_time_in_sec,
                                                            int number_of_wake_in_sleep,
                                                            float *output_sleep_quality_index,
                                                            mxm_algosuite_return_code *const status );

MXM_ALGOSUITE_API void mxm_algosuite_manager_getauthinitials( const uint8_t *const auth_inits,
                                                              uint8_t *out_auth_initials);

MXM_ALGOSUITE_API int mxm_algosuite_manager_authenticate( const uint8_t *const auth_str1,
                                                           const uint8_t *const auth_str2);

#ifdef __cplusplus
}
#endif


#endif /* DRIVERS_ALGOWRAPPER_ALGOWRAPPER_H_ */
