// ----------------------------------------------------------------------------
// BSD 3-Clause License

// Copyright (c) 2016, qbrobotics
// Copyright (c) 2017, Centro "E.Piaggio"
// All rights reserved.

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:

// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.

// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.

// * Neither the name of the copyright holder nor the names of its
//   contributors may be used to endorse or promote products derived from
//   this software without specific prior written permission.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// POSSIBILITY OF SUCH DAMAGE.
// ----------------------------------------------------------------------------

/**
* \file         globals.h
*
* \brief        Global definitions and macros are set in this file.
* \date         October 01, 2017
* \author       _Centro "E.Piaggio"_
* \copyright    (C) 2012-2016 qbrobotics. All rights reserved.
* \copyright    (C) 2017 Centro "E.Piaggio". All rights reserved.
*/

#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED

//=================================================================     includes
#include <device.h>
#include "stdlib.h"
#include "math.h"
#include "commands.h"

//==============================================================================
//                                                                        DEVICE
//==============================================================================

#define VERSION         "CUFF MOD v6.1.5"

#define NUM_OF_MOTORS           2
#define NUM_OF_SENSORS          3
#define NUM_OF_ANALOG_INPUTS    3
#define NUM_OF_PARAMS           25

//==============================================================================
//                                                                       CONTROL
//==============================================================================

#define PWM_MAX_VALUE   100         // PWM is from 0 to 100, this value is used
                                    // to limit this value
#define PWM_DEAD        0           // deadband value, is directly added to the
                                    // value of PWM always limited to 100

// WARNING POS_INTEGRAL_SAT_LIMIT need to be lower than 2^17 or you have to modify
// the code in the motor control function
#define POS_INTEGRAL_SAT_LIMIT   100000  // Anti wind-up
#define CURR_INTEGRAL_SAT_LIMIT  100000  // Anti wind-up
//#define CALIB_CURRENT            1000    // Max current for calibration (mA)
#define DEFAULT_CURRENT_LIMIT    1500    // Current limit when using CURR_AND_POS_CONTROL
    

//==============================================================================
//                                                               SYNCHRONIZATION
//==============================================================================

// Main frequency 1000 Hz

#define CALIBRATION_DIV         100     // 10 Hz

#define DIV_INIT_VALUE          1

//==============================================================================
//                                                                           DMA
//==============================================================================
    
#define DMA_BYTES_PER_BURST 2
#define DMA_REQUEST_PER_BURST 1
#define DMA_SRC_BASE (CYDEV_PERIPH_BASE)
#define DMA_DST_BASE (CYDEV_SRAM_BASE)
    
//==============================================================================
//                                                                     INTERRUPT
//==============================================================================
#define    WAIT_START   0
#define    WAIT_ID      1
#define    WAIT_LENGTH  2
#define    RECEIVE      3
#define    UNLOAD       4
    
//==============================================================================
//                                                                         OTHER
//==============================================================================

#define FALSE           0
#define TRUE            1

#define DEFAULT_EEPROM_DISPLACEMENT 10   // in pages
    
#define MAX_WATCHDOG_TIMER 250          // num * 2 [cs]

    
//==============================================================================
//     funzione polinomiale quarto grado al posto della logaritmica
//==============================================================================
    
#define P1             53100
#define P2             (-90980)
#define P3             57310
#define P4             (-11980) 
#define P5              4552
#define P6              (-3)
    
//==============================================================================
//     funzione polinomiale quinto grado al posto della logaritmica
//==============================================================================
    
#define P1_QUINTO              0.00000004717
#define P2_QUINTO              -0.0008275
#define P3_QUINTO              0.5337
#define P4_QUINTO              -114.3
#define P5_QUINTO              44460
#define P6_QUINTO              -35270

//==============================================================================
//    funzione polinomiale quarto grado normalizzata al posto della logaritmica
//==============================================================================
    
//#define P1_QUARTO              31760
//#define P2_QUARTO              -42240
//#define P3_QUARTO              20160
//#define P4_QUARTO              1085
//#define P5_QUARTO              27.63
    
//==============================================================================
//    funzione polinomiale quinto grado normalizzata al posto della logaritmica
//==============================================================================
    
//#define P1_QUINTO              47170
//#define P2_QUINTO              -82750
//#define P3_QUINTO              53370
//#define P4_QUINTO              -11430
//#define P5_QUINTO              4446
//#define P6_QUINTO              -3.527
//==============================================================================
//     funzione polinomiale terzo grado al posto dell'esponenziale
//==============================================================================
    
#define P1_TERZO              22.15
#define P2_TERZO              -47.13
#define P3_TERZO              34.49
#define P4_TERZO              -8.53

//==============================================================================
//                                                        structures definitions
//==============================================================================

//=========================================================     motor references

struct st_ref {

    int32 pos[NUM_OF_MOTORS];       // motor reference position
    uint8 onoff;                    // enable flags

};

//=============================================================     measurements

struct st_meas {

    int32 pos[NUM_OF_SENSORS];      // sensor position
    int16 curr[NUM_OF_MOTORS];      // motor currents
    int8 rot[NUM_OF_SENSORS];       // sensor rotations
    int16 vel[NUM_OF_SENSORS];      // sensor velocity
    int16 acc[NUM_OF_SENSORS];      // sensor acceleration

};

//==============================================================     data packet

struct st_data {

    uint8   buffer[128];                    // CMD/DATA/CHECKSUM
    int16   length;                         // length
    int16   ind;                            // index
    uint8   ready;                          // Flag

};

//============================================     settings stored on the memory

struct st_mem {

    uint8   flag;                       // Device has been configured               1
    uint8   id;                         // device ID                                1

    int32   k_p;                        // Proportional constant                    4
    int32   k_i;                        // Derivative constant                      4
    int32   k_d;                        // Integrative constant                     4

    int32   k_p_c;                      // Proportional constant current            4
    int32   k_i_c;                      // Derivative constant current              4
    int32   k_d_c;                      // Integrative constant current             4       26

    int32   k_p_dl;                     // Proportional double loop constant        4
    int32   k_i_dl;                     // Derivative double loop constant          4
    int32   k_d_dl;                     // Integrative double loop constant         4

    int32   k_p_c_dl;                   // Prop. double loop current constant       4
    int32   k_i_c_dl;                   // Derivative double loop current constant  4
    int32   k_d_c_dl;                   // Integrative double loop current constant 4       24

    int16   current_limit;              // Limit for absorbed current               2

    uint8   activ;                      // Activation upon startup                  1
    uint8   input_mode;                 // Input mode                               1       
    uint8   control_mode;               // Control mode                             1

    uint8   res[NUM_OF_SENSORS];        // Angle resolution                         1 (3)
    int32   m_off[NUM_OF_SENSORS];      // Measurement offset                       4 (12)
    float   m_mult[NUM_OF_SENSORS];     // Measurement multiplier                   4 (12)  32
    uint8   pos_lim_flag;               // Position limit active/inactive           1
    int32   pos_lim_inf[NUM_OF_MOTORS]; // Inferior position limit for motors       4 (8)
    int32   pos_lim_sup[NUM_OF_MOTORS]; // Superior position limit for motors       4 (8)

    uint16  max_stiffness;              // Max stiffness value obtained
                                        // during calibration                       2       19
    uint8   baud_rate;                  // Baud Rate Setted                         1
    uint8   watchdog_period;            // Watchdog period setted, 255 = disable    1
    int32   max_step_neg;               // Maximum velocity for negative inputs     4       
    int32   max_step_pos;               // Maximum velocity for positive inputs     4

    /*=========================CUFF RELATIVE PARAMETERS=============================*/
    uint8   cuff_activation_flag_force;       //                                          1
    float   curr_prop_gain;             //                                          4
    int16   curr_sat;                   //                                          2
    int16   curr_dead_zone;             //                                          2

    uint8   cuff_activation_flag_proprio;       //                                          1
    int32   max_slide;
    int32   max_force;
    int32   max_SH_pos;
    uint8   hand_ID;
    
    uint8   cuff_activation_flag_force_proprio;
    
    uint16 power_tension;               //                                          2
    
    int32   SH_rest_pos;
    
    uint8 right_left;
    
                                                                                    //TO UPDATE
};


/*
//=================================================     calibration status

enum calibration_status {

    STOP        = 0,
    START       = 1,
    CONTINUE_1  = 2,
    CONTINUE_2  = 3,
    PAUSE_1     = 4,
    PAUSE_2     = 5

};*/

//====================================      external global variables declaration


extern struct st_ref    g_ref, g_refNew, g_refOld;  // motor variables
extern struct st_meas   g_meas, g_measOld;          // measurements
extern struct st_data   g_rx;                       // income data
extern struct st_mem    g_mem, c_mem;               // memory


extern uint32 timer_value;
extern uint32 timer_value0;

// Device Data

extern int32   dev_tension;                         // Power supply tension
extern uint8   dev_pwm_limit;

extern uint8 calibration_flag;

// Bit Flag

extern CYBIT reset_last_value_flag;
extern CYBIT tension_valid;                         // tension validation bit
extern CYBIT cuff_flag_force;                             // cuff activation flag
extern CYBIT cuff_flag_proprio;                             // cuff activation flag
extern CYBIT cuff_flag_force_proprio;                             // cuff activation flag
extern CYBIT interrupt_flag;                        // interrupt flag enabler
extern CYBIT watchdog_flag;                         // watchdog flag enabler


extern CYBIT pret_done;                             //Pretensioning done

extern CYBIT pretensioning_flag;
// DMA Buffer

extern int16 ADC_buf[3];

// Sign of pwm_input to calculate current with sign

extern int8 pwm_sign[2];

// Zero position after pretensioning

extern int32 pret_offset_pos[2];

// -----------------------------------------------------------------------------

#endif

//[] END OF FILE