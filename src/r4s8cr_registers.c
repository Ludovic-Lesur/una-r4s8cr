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

#ifdef UNA_R4S8CR_USE_REGISTER_ACCESS
const UNA_register_access_t R4S8CR_REGISTER_ACCESS[R4S8CR_REGISTER_ADDRESS_LAST] = {
    UNA_REGISTER_ACCESS_READ_ONLY,
    UNA_REGISTER_ACCESS_READ_WRITE,
};
#endif
#ifdef UNA_R4S8CR_USE_REGISTER_ACCESS_TIMEOUT
const uint32_t R4S8CR_REGISTER_ACCESS_TIMEOUT_MS[R4S8CR_REGISTER_ADDRESS_LAST] = {
    200,
    5000
};
#endif
#ifdef UNA_R4S8CR_USE_REGISTER_ERROR_VALUE
const uint32_t R4S8CR_REGISTER_ERROR_VALUE[R4S8CR_REGISTER_ADDRESS_LAST] = {
    ((UNA_BIT_ERROR << 14) | (UNA_BIT_ERROR << 12) | (UNA_BIT_ERROR << 10) | (UNA_BIT_ERROR << 8) |
    (UNA_BIT_ERROR << 6)   | (UNA_BIT_ERROR << 4)  | (UNA_BIT_ERROR << 2)  | (UNA_BIT_ERROR << 0)),
    0x00000000
};
#endif
