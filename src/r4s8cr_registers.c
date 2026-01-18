/*
 * r4s8cr_registers.c
 *
 *  Created on: 06 dec. 2024
 *      Author: Ludo
 */

#include "r4s8cr_registers.h"

#ifndef UNA_R4S8CR_DISABLE_FLAGS_FILE
#include "una_r4s8cr_flags.h"
#endif
#include "types.h"
#include "una.h"

/*** R4S8CR REGISTERS global variables ***/

const UNA_register_t R4S8CR_REGISTER[R4S8CR_REGISTER_ADDRESS_LAST] = {
    /* STATUS_1 */
    {
       UNA_REGISTER_ACCESS_READ_ONLY,
       200,
       UNA_REGISTER_RESET_VALUE_STATIC,
       (uint32_t) ((UNA_BIT_ERROR << 14) | (UNA_BIT_ERROR << 12) | (UNA_BIT_ERROR << 10) | (UNA_BIT_ERROR << 8) |
                   (UNA_BIT_ERROR << 6)  | (UNA_BIT_ERROR << 4)  | (UNA_BIT_ERROR << 2)  | (UNA_BIT_ERROR << 0)),
    },
    /* CONTROL_1 */
    {
       UNA_REGISTER_ACCESS_READ_WRITE,
       5000,
       UNA_REGISTER_RESET_VALUE_STATIC,
       0x00000000
    },
};
