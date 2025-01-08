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

/**
* @file mxm_sleep_manager.h
* @date January 2019
* @brief Maxim Sleep Quality Assessment Manager public API header file
*/

/**
* @defgroup sleepQAManager Maxim Sleep Quality Assessment Manager Module
* @brief    Includes Maxim Sleep Quality Assessment Manager API related
*           definitions.
*
* This module is in charge of handling Maxim Sleep Quality Assessment Manager API
* related tasks and definitions.
*/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _SLEEP_MANAGER_H_
#define _SLEEP_MANAGER_H_

#include <stdint.h>
#include <stdbool.h>

/* Macros for library import/export */
#if defined(WELLNESS_SUITE_BUILD)
#define SLEEP_MANAGER_API
#define SLEEP_MANAGER_CALL
#else
#ifdef _WIN32
#ifdef SLEEP_MANAGER_EXPORTS
#define SLEEP_MANAGER_API __declspec(dllexport)
#elif defined SLEEP_MANAGER_IMPORTS
#define SLEEP_MANAGER_API __declspec(dllimport)
#else
#define SLEEP_MANAGER_API
#endif
#define SLEEP_MANAGER_CALL __cdecl
#else    /* Android */
#define SLEEP_MANAGER_API __attribute__((__visibility__("default")))
#define SLEEP_MANAGER_CALL
#endif
#endif

#define MAX_IBI_COUNT   4 // Maximum IBI count belong to 1HZ data package

    /**
    * @public
    * @ingroup sleepQAManager
    * @brief   Sleep Quality Assessment Manager version structure
    */
    typedef struct _mxm_sleep_manager_version_str {
        char versionStrn[20];    /**< version in vXX.XX.XX format */
        unsigned short int version;		    /**< The first number in vXX.XX.XX format */
        unsigned short int subVersion;   	/**< The second number in vXX.XX.XX format */
        unsigned short int subsubVersion;   /**< The third number in vXX.XX.XX format */
    } mxm_sleep_manager_version_str;



    /**
    * @public
    * @ingroup sleepQAManager
    * @brief   Sleep Quality Assessment Manager Sleep/Wake Detection Duration Config parameter
    *
    * This enumaration helps to decide Sleep/Wake detection duration config parameter to
    * determine sleep or wake regarding to last N minutes.
    */
    //TODO:Config selection guide
    typedef enum _mxm_sleep_manager_minimum_detectable_sleep_duration {
        MXM_SLEEP_MANAGER_MINIMUM_SLEEP_20_MIN = 20, /**<Detect sleeps more than 20 min.
                                                     Initial Latency 20 min.*/

        MXM_SLEEP_MANAGER_MINIMUM_SLEEP_30_MIN = 30, /**<Detect sleeps more than 30 min.
                                                     Initial Latency 30 min.*/

        MXM_SLEEP_MANAGER_MINIMUM_SLEEP_40_MIN = 40, /**<<Detect sleeps more than 40 min.
                                                 Initial Latency 40 min. */

        MXM_SLEEP_MANAGER_MINIMUM_SLEEP_50_MIN = 50, /**<Detect sleeps more than 50 min.
                                                 Initial Latency 50 min. */

        MXM_SLEEP_MANAGER_MINIMUM_SLEEP_60_MIN = 60,/**<Detect sleeps more than 60 min.
                                               Initial Latency 60 min.  */
    }mxm_sleep_manager_minimum_detectable_sleep_duration;

    /**
    * @public
    * @ingroup sleepQAManager
    * @brief   Sleep Quality Assessment Manager Subject's Gender option
    *
    * This enumaration helps to define subject's gender
    */
    typedef enum _mxm_sleep_manager_gender {
        MXM_MALE,
        MXM_FEMALE
    } mxm_sleep_manager_gender;

    /**
    * @public
    * @ingroup sleepQAManager
    * @brief   Sleep Quality Assessment Manager user info
    *
    */
    typedef struct _mxm_sleep_user_info {

        uint16_t age;       /**< Age of the user to set (in years)*/
        uint16_t weight;    /**< Weight of the user to set (in kg) */
        mxm_sleep_manager_gender gender;    /**< Gender of the user to set, 0:Male 1:Female */
        float sleep_resting_hr; /**< Resting HR of the user. Needs to be set if is_resting_hr_available is true*/

    } mxm_sleep_user_info;


    /**
    * @public
    * @ingroup sleepQAManager
    * @brief   Sleep Quality Assessment Manager Config strucutre
    */
    typedef struct _mxm_sleep_manager_config
    {

        mxm_sleep_manager_minimum_detectable_sleep_duration mxm_sleep_detection_duration; /**<
                                                                                  Minimum sleep duration allowed*/
        mxm_sleep_user_info user_info; /**< User info including age,gender,weight*/

        bool is_resting_hr_available;/**< Availability of the resting HR of the subject*/

        bool is_confidence_level_available_hr; /**< Availability of the confidence level for the HR measurement*/
        bool is_confidence_level_available_ibi; /**< Availability of the confidence level for the IBI measruement*/
        bool is_activity_available;/**< Availability of the activity identifier*/
    } mxm_sleep_manager_config;

    /**
    * @public
    * @ingroup sleepQAManager
    * @brief   Sleep Quality Assessment Manager Sleep/Wake Indicator
    *
    * This enumaration is a flag indicating whether the sleep-wake decision is updated or not. Moreover
    * the sleep-wake-output status is set to NOT_CALCULATED during the first N minutes (initialization period)
    * defined by @ref _mxm_sleep_manager_detection_duration_config
    */
    typedef enum _mxm_sleep_manager_sleep_wake_output_status {
        MXM_SLEEP_MANAGER_NOT_CALCULATED = 0,  /**< If the Sleep/Wake Decision is not ready */
        MXM_SLEEP_MANAGER_CALCULATED = 1,      /**< If the Sleep/Wake Decision is made */
    } mxm_sleep_manager_sleep_wake_output_status;

    /**
    * @public
    * @ingroup sleepQAManager
    * @brief   Sleep Quality Assessment Manager Sleep Phase Output Status
    *
    * This enumaration indicates the sleep phase output's readiness information
    */
    typedef enum _mxm_sleep_manager_sleep_phase_output_status {
        MXM_SLEEP_MANAGER_PHASE_NOT_CALCULATED = 0, /**< If the Sleep Phase Decision is not ready */
        MXM_SLEEP_MANAGER_PHASE_READY = 1,          /**< If the Sleep Phase Decision is ready */
    } mxm_sleep_manager_sleep_phase_output_status;

    /**
    * @public
    * @ingroup sleepQAManager
    * @brief   Sleep Quality Assessment Manager return types
    */
    typedef enum _mxm_sleep_manager_return {
        MXM_SLEEP_MANAGER_SUCCESS,                  /**< Success return code */
        MXM_SLEEP_MANAGER_INIT_NULL_PTR_ERROR,      /**< NULL pointer error (during initialization) return code */
        MXM_SLEEP_MANAGER_INIT_INVALID_INPUT_ERROR, /**< Invalid Input error return code */
        MXM_SLEEP_MANAGER_ALGO_INIT_ERROR,          /**< Algorithm module initialization error return code */
        MXM_SLEEP_MANAGER_ALGO_END_ERROR,           /**< Algorithm module termination error return code */
        MXM_SLEEP_MANAGER_RUN_NULL_PTR_ERROR,       /**< NULL pointer error (during execution) return code */
        MXM_SLEEP_MANAGER_RUN_ALGO_ERROR,           /**< Algorithm execution error return code */
        MXM_SLEEP_MANAGER_RUN_ALGO_AGE_OR_GENDER_NOT_DEFINED, /**< Age or gender is not defined return code */
    } mxm_sleep_manager_return;

    /**
    * @public
    * @ingroup sleepQAManager
    * @brief   Sleep Quality Assessment Manager Sleep Wake Output
    *
    * This enumaration indicates the subject's sleep status of the user.
    */
    typedef enum _mxm_sleep_manager_sleep_wake_output {
        MXM_SLEEP_MANAGER_WAKE = 0,   /**< While subject is in sleep, short-term decision for wake */
        MXM_SLEEP_MANAGER_UNDECIDED,   /**< If the Sleep Wake output is not ready, decision will be UNDECIDED */
        MXM_SLEEP_MANAGER_SLEEP       /**< While subject is in sleep, short-term decision for sleep */
    } mxm_sleep_manager_sleep_wake_output;

    /**
    * @public
    * @ingroup sleepQAManager
    * @brief   Sleep Quality Assessment Manager Sleep Phase Output while subject is in sleep
    *
    * This enumaration indicates the subject's sleep phase output while the subject is in sleep
    */
    typedef enum _mxm_sleep_manager_sleep_phase_output {
        MXM_SLEEP_MANAGER_SP_UNDEFINED = -1,        /**< If Sleep Phases Output is either not ready or
                                                    can not be calculated*/
        MXM_SLEEP_MANAGER_SP_WAKE = 0,                 /**< Subject is in the awake state*/
        MXM_SLEEP_MANAGER_REM = 2,                  /**< Subject sleeps in in the REM stage */
        MXM_SLEEP_MANAGER_LIGHT = 3,                /**< Subject sleeps in in the LIGHT stage */
        MXM_SLEEP_MANAGER_DEEP = 4                  /**< Subject sleeps in in the DEEP stage */
    } mxm_sleep_manager_sleep_phase_output;

    /**
    * @public
    * @ingroup sleepQAManager
    * @brief   Sleep Quality Assessment Manager Supported Input Activity Types
    *
    * This enumaration defines the supported activities.
    * If there is no apriori information regarding the activity select 'MXM_SLEEP_MANAGER_ACTIVITY_NOT_AVAILABLE'.
    * Algorithm supports only REST and NON-REST activities to process.
    */
    typedef enum _mxm_sleep_manager_activity_type {
        MXM_SLEEP_MANAGER_ACTIVITY_NOT_AVAILABLE,   /**< When activity input is not available */
        MXM_SLEEP_MANAGER_REST_ACTIVITY,            /**< Rest activity*/
        MXM_SLEEP_MANAGER_NON_REST_ACTIVITY,        /**< Any activity having motion*/
    } mxm_sleep_manager_activity_type;


    /**
    * @public
    * @ingroup sleepQAManager
    * @brief   Sleep Quality Assessment Manager Sleep Algorithm Encoded Output
    *
    * This structure keeps encoded output to keep sleep output with minimal memory usage.
    * The user can get a summary of subjects sleep by keeping only the encoded outputs with needs_storage flag is true
    */
    typedef struct _mxm_sleep_manager_sleep_encoded_output {
        mxm_sleep_manager_sleep_phase_output sleep_phase; /**< Sleep phase */
        int duration;  /**< Duration of the given sleep phase*/
        bool needs_storage; /**< The given phase and duration needs to be stored in memory*/
    } mxm_sleep_manager_sleep_encoded_output;

    /**
    * @public
    * @ingroup sleepQAManager
    * @brief   Sleep Quality Assessment Manager HRV Data Input Structure
    *
    * This structure keeps hrv metrics that are required to run Sleep algorithm.
    */
    typedef struct _mxm_sleep_manager_hrv_input_package {
        bool is_hrv_calculated; /**< A flag corresponding to whether or not HRV is calculated */
        float hrv_lf; /**< HRV Metric corresponding to the low frequency power (ms^2) */
        float hrv_hf; /**< HRV Metric corresponding to the high frequency power (ms^2) */
        float hrv_lf_over_hf; /**< HRV Metric corresponding to the ratio of low frequency to high frequency power (%) */
        float hrv_pnn50; /**< HRV Metric corresponding to the proportion of successive RR intervals > 50 ms in relation to total RR intervals (%) */
        float hrv_rmssd; /**< HRV Metric corresponding to the root mean square of successive RR interval differences (ms) */
        float hrv_sdnn; /**< HRV Metric corresponding to standart deviation of NN intervals (ms) */
        float hrv_avnn; /**< HRV Metric corresponding to average of NN intervals (ms) */
    } mxm_sleep_manager_hrv_input_package;


    /**
    * @public
    * @ingroup sleepQAManager
    * @brief   Sleep Quality Assessment Manager Input Data Structure
    */
    //TODO: add comments to new variables

    typedef struct _mxm_sleep_manager_input_data_str {

        float hr;                            /**< Instant HR value of subject (bpm)*/
        float hr_conf_level;                 /**< Confidence Level of instant HR value of subject. Range:0-100.
                                             Higher values correponds to confident measurements.*/
        bool is_hr_updated;                 /**< Update flag of the HR*/

        float interbeat_interval[MAX_IBI_COUNT];            /**< Inter-beat interval (IBI) values of subject (ms) corresponds to 1 second */

        float interbeat_interval_conf_level[MAX_IBI_COUNT]; /**< Confidence Level of instant inter-beat interval (IBI)
                                             values of subject corresponds to 1 second. Range:0-100. Higher values corresponds
                                             confident measurements */

        mxm_sleep_manager_hrv_input_package hrv_input_pkg; /**< HRV Metrics input package */

        bool is_interbeat_interval_updated; /**< Update flag of the IBI*/

        float respiration_rate;             /**< Reserved for future use*/
        bool is_respiration_rate_updated; /**< Reserved for future use*/

        float spo2; /**< Reserved for future use*/
        bool is_spo2_updated;/**< Reserved for future use*/

        mxm_sleep_manager_activity_type activity_type; /**< Activity of subject */

        float mean_accelerometer_magnitude;                 /**< Mean magnitude of the accelerometer data in milli-g units*/
        bool is_accelerometer_updated; /**< Update flag of the accelerometer*/

    } mxm_sleep_manager_input_data_str;


    /**
    * @public
    * @ingroup sleepQAManager
    * @brief   Sleep Quality Assessment Manager Output Data Structure
    */
    typedef struct _mxm_sleep_manager_output_data_str {

        // Sleep/Wake Classification related outputs
        mxm_sleep_manager_sleep_wake_output_status sleep_wake_decision_status; /**< Update flag of the sleep_wake_decision*/
        mxm_sleep_manager_sleep_wake_output sleep_wake_decision; /**< Sleep/Wake Classification output */
        short int sleep_wake_detection_latency; /** in minutes */
        float sleep_wake_output_conf_level;    /**< Sleep/Wake Classification output confidence level*/

        // Sleep Phases Classification related outputs
        mxm_sleep_manager_sleep_phase_output_status sleep_phase_output_status; /**< Sleep Phases Output status */
        mxm_sleep_manager_sleep_phase_output sleep_phase_output; /**< Sleep Phases Classification output */
        float sleep_phase_output_conf_level;    /**< Sleep Phases Classification output confidence level*/

        mxm_sleep_manager_sleep_encoded_output encoded_output; /**< The encoded output of SLeep Algorithm*/

        float hr;                               /**< HR value processed by SleepQA Algorithm */
        float acc_mag;                          /**< Accelerometer Magnitude value processed by SleepQA Algorithm */
        float interbeat_interval;               /**< Inter-beat Interval value processed by SleepQA Algorithm */
        float sleep_resting_hr;                     /**< Resting HR calculated at the end of the nigth. Required as an input for next initialization*/

    } mxm_sleep_manager_output_data_str;

    /**
    * @public
    * @ingroup sleepQAManager
    * @brief   Sleep Quality Assessment Manager Input DataFrame
    */
    typedef struct _mxm_sleep_manager_input_dataframe {
        mxm_sleep_manager_input_data_str * input_data_arr;  /**< Array of observations containing descriptors (HR, IBI, ACC. and etc.)*/

        unsigned int input_data_arr_length;                 /**< Length of the observations*/

        uint64_t date_info;                                 /**< Date Info is the time for the initial
                                                            mxm_sleep_manager_input_data_str unix timestamp*/

    }mxm_sleep_manager_input_dataframe;

    /**
    * @public
    * @ingroup sleepQAManager
    * @brief   Sleep Quality Assessment Manager Output DataFrame
    */
    typedef struct _mxm_sleep_manager_output_dataframe {
        mxm_sleep_manager_output_data_str * output_data_arr; /**< Array of outputs corresponding to the input array of observations*/

        unsigned int output_data_arr_length; /**< Length of the outputs*/

        uint64_t date_info;                                 /**< Date Info is the time for the initial
                                                                    mxm_sleep_manager_input_data_str unix timestamp*/
    }mxm_sleep_manager_output_dataframe;

    /**
    * @public
    * @ingroup sleepQAManager
    *
    * @brief     Initializes the Sleep Quality Assessment Manager according to the configuration given by @p sleep_confg
    *
    * This function should be called once at the beginning of a typical flow.
    *
    * @param     [in] sleep_confg    Sleep Quality Assessment Manager Configuration structure pointer
    *
    * @return    Return code as defined in @ref _mxm_sleep_manager_return
    */
    SLEEP_MANAGER_API mxm_sleep_manager_return SLEEP_MANAGER_CALL mxm_sleep_manager_init(const mxm_sleep_manager_config *const sleep_confg);

    /**
    * @public
    * @ingroup sleepQAManager
    *
    * @brief     Runs the Sleep Quality Assessment Manager to process the batch input.
    *
    * Typical algorithm flow should be as follows <br>
    * - Call ::mxm_sleep_manager_init once for initialization
    * - Call ::mxm_sleep_manager_set_age once after initialization is done
    * - Call ::mxm_sleep_manager_set_gender once after initialization is done
    * - Call ::mxm_sleep_manager_run for every batch/sleep_dataframe
    * - Call ::mxm_sleep_manager_end once for termination
    *
    * @param     [in] input_str_ptr     Pointer to a structure that contains input data to run the Sleep Quality Assessment Manager
    * @param     [out] output_str_ptr   Pointer to a structure that contains output data filled by the Sleep Quality Assessment Manager
    *
    *
    * @return    Return code as defined in @ref _mxm_sleep_manager_return
    */
    SLEEP_MANAGER_API mxm_sleep_manager_return SLEEP_MANAGER_CALL mxm_sleep_manager_run(const mxm_sleep_manager_input_dataframe * const input_str_ptr,
        mxm_sleep_manager_output_dataframe *const output_str_ptr);

    /**
    * @public
    * @ingroup sleepQAManager
    *
    * @brief     Terminates the Sleep Quality Assessment Manager
    *
    * This function should be called once at the end of a typical flow.
    *
    * @return    Return code as defined in @ref _mxm_sleep_manager_return
    */
    SLEEP_MANAGER_API mxm_sleep_manager_return SLEEP_MANAGER_CALL mxm_sleep_manager_end();

    /**
    * @public
    * @ingroup spo2Manager
    *
    * @brief     Version query function
    *
    * @param     [out] version_ptr    Pointer to a structure that contains algorithm version data filled by the Sleep Quality Assessment Manager
    *
    * @return    This is a void function.
    */
    SLEEP_MANAGER_API void SLEEP_MANAGER_CALL ver_mxm_sleep_manager(mxm_sleep_manager_version_str *version_ptr);



    /**
    * @public
    * @ingroup sleepQAManager
    *
    * @brief     Calculates the Sleep Quality Index related to subject's sleep.
    *
    * This function should be called after the detection of subject's wake-up.
    *
    * @param     [in] deep_time_in_sec              The time spent in DEEP state (in seconds) during the subject's sleep period
    * @param     [in] rem_time_in_sec               The time spent in REM state (in seconds) during the subject's sleep period
    * @param     [in] in_sleep_wake_time_in_sec     The time between Bed time and Wake-Up time (in seconds)
    * @param     [in] number_of_wake_in_sleep       Count of wakes during the sleep period.
    * @param     [out] output_sleep_quality_index   Calculated Sleep Quality Index
    *
    * @return    Return code as defined in @ref _mxm_sleep_manager_return
    */
    SLEEP_MANAGER_API mxm_sleep_manager_return SLEEP_MANAGER_CALL mxm_sleep_manager_calculate_SQI(
                                                                        float deep_time_in_sec,
                                                                        float rem_time_in_sec,
                                                                        float in_sleep_wake_time_in_sec,
                                                                        int number_of_wake_in_sleep,
                                                                        float *output_sleep_quality_index);
    /**
    * @public
    * @ingroup sleepQAManager
    *
    * @brief     Calculates the resting heart rate of the current experiment.
    *
    * This function should be called after the detection of subject's wake-up.
    * @param     [out] resting_hr                    Calculated resting heart rate
    * @param     [out] calculation_duration_in_sec   Duration from which resting HR is calculated
    *
    * @return    Return code as defined in @ref _mxm_sleep_manager_return
    */
    SLEEP_MANAGER_API mxm_sleep_manager_return SLEEP_MANAGER_CALL mxm_sleep_manager_calculate_resting_hr(
        float *resting_hr,
        unsigned int *calculation_duration_in_sec);
#endif /* SLEEP_MANAGER_H_ */

#ifdef __cplusplus // If this is a C++ compiler, use C linkage
}
#endif
