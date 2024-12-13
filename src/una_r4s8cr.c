/*
 * una_r4s8cr.c
 *
 *  Created on: 06 dec. 2024
 *      Author: Ludo
 */

#include "una_r4s8cr.h"

#include "error.h"
#include "r4s8cr.h"
#include "r4s8cr_registers.h"
#include "swreg.h"
#include "types.h"
#include "una.h"

#ifndef UNA_R4S8CR_DISABLE

/*** UNA R4S8CR local global variables ***/

static uint32_t R4S8CR_REGISTERS[R4S8CR_REGISTER_ADDRESS_LAST] = {
    ((UNA_BIT_ERROR << 14) | (UNA_BIT_ERROR << 12) | (UNA_BIT_ERROR << 10) | (UNA_BIT_ERROR << 8) |
     (UNA_BIT_ERROR << 6)  | (UNA_BIT_ERROR << 4)  | (UNA_BIT_ERROR << 2)  | (UNA_BIT_ERROR << 0)),
    0x00000000
};

/*** UNA R4S8CR functions ***/

/*******************************************************************/
UNA_R4S8CR_status_t UNA_R4S8CR_init(void) {
    // Local variables.
    UNA_R4S8CR_status_t status = UNA_R4S8CR_SUCCESS;
    R4S8CR_status_t r4s8cr_status = R4S8CR_SUCCESS;
    // Init relay box driver.
    r4s8cr_status = R4S8CR_init();
    R4S8CR_exit_error(UNA_R4S8CR_ERROR_BASE_R4S8CR);
errors:
    return status;
}

/*******************************************************************/
UNA_R4S8CR_status_t UNA_R4S8CR_de_init(void) {
    // Local variables.
   UNA_R4S8CR_status_t status = UNA_R4S8CR_SUCCESS;
   R4S8CR_status_t r4s8cr_status = R4S8CR_SUCCESS;
   // Init relay box driver.
   r4s8cr_status = R4S8CR_de_init();
   R4S8CR_exit_error(UNA_R4S8CR_ERROR_BASE_R4S8CR);
errors:
    return status;
}

/*******************************************************************/
UNA_R4S8CR_status_t UNA_R4S8CR_write_register(UNA_access_parameters_t* write_parameters, uint32_t reg_value, uint32_t reg_mask, UNA_access_status_t* write_status) {
    // Local variables.
    UNA_R4S8CR_status_t status = UNA_R4S8CR_SUCCESS;
    R4S8CR_status_t r4s8cr_status = R4S8CR_SUCCESS;
    uint8_t relay_box_id = 0;
    uint8_t relay_index = 0;
    uint8_t idx = 0;
    // Check parameters.
    if ((write_parameters == NULL) || (write_status == NULL)) {
        status = UNA_R4S8CR_ERROR_NULL_PARAMETER;
        goto errors;
    }
    // Reset access status.
    (write_status->all) = 0;
    (write_status->type) = UNA_ACCESS_TYPE_WRITE;
    // Check node address.
    if (((write_parameters->node_addr) < UNA_NODE_ADDRESS_R4S8CR_START) || ((write_parameters->node_addr) > UNA_NODE_ADDRESS_R4S8CR_END)) {
        (*write_status).reply_timeout = 1;
        goto errors;
    }
    // Check register address.
    if ((write_parameters->reg_addr) != R4S8CR_REGISTER_ADDRESS_CONTROL) {
        (write_status->error_received) = 1;
        goto errors;
    }
    // Update RAM register value.
    SWREG_modify_register(&(R4S8CR_REGISTERS[write_parameters->reg_addr]), reg_value, reg_mask);
    // Convert node address to ID.
    relay_box_id = ((write_parameters->node_addr) - UNA_NODE_ADDRESS_R4S8CR_START + 1) & 0x0F;
    // Relay loop.
    for (idx=R4S8CR_RELAY_INDEX_MIN ; idx<=R4S8CR_RELAY_INDEX_MAX ; idx++) {
        // Compute relay id.
        relay_index = (uint8_t) (((relay_box_id - 1) << 3) + idx + 1);
        // Check bit mask.
        if ((reg_mask & (0b1 << idx)) != 0) {
            // Set relay state
            r4s8cr_status = R4S8CR_write(relay_box_id, relay_index, (uint8_t) (reg_value & (0b1 << idx)));
            R4S8CR_exit_error(UNA_R4S8CR_ERROR_BASE_R4S8CR);
        }
    }
errors:
    return status;
}

/*******************************************************************/
UNA_R4S8CR_status_t UNA_R4S8CR_read_register(UNA_access_parameters_t* read_parameters, uint32_t* reg_value, UNA_access_status_t* read_status) {
    // Local variables.
    UNA_R4S8CR_status_t status = UNA_R4S8CR_SUCCESS;
    R4S8CR_status_t r4s8cr_status = R4S8CR_SUCCESS;
    uint8_t relay_box_id = 0;
    uint8_t state = 0;
    UNA_bit_representation_t rxst[R4S8CR_NUMBER_OF_RELAYS];
    uint8_t idx = 0;
    uint32_t unused_mask = 0;
    // Check parameters.
    if ((read_parameters == NULL) || (read_status == NULL)) {
       status = UNA_R4S8CR_ERROR_NULL_PARAMETER;
       goto errors;
    }
    // Reset relays status.
    for (idx=0 ; idx<R4S8CR_NUMBER_OF_RELAYS ; idx++) {
        rxst[idx] = UNA_BIT_ERROR;
    }
    // Reset access status.
    (read_status->all) = 0;
    (read_status->type) = UNA_ACCESS_TYPE_READ;
    // Check node address.
    if (((read_parameters->node_addr) < UNA_NODE_ADDRESS_R4S8CR_START) || ((read_parameters->node_addr) > UNA_NODE_ADDRESS_R4S8CR_END)) {
       (*read_status).reply_timeout = 1;
       goto errors;
    }
    // Check register address.
    if ((read_parameters->reg_addr) >= R4S8CR_REGISTER_ADDRESS_LAST) {
       (read_status->error_received) = 1;
       goto errors;
    }
    // Update register.
    if ((read_parameters->reg_addr) == R4S8CR_REGISTER_ADDRESS_STATUS) {
        // Convert node address to ID.
        relay_box_id = ((read_parameters->node_addr) - UNA_NODE_ADDRESS_R4S8CR_START + 1) & 0x0F;
        // Read relays state.
        r4s8cr_status = R4S8CR_read(relay_box_id, &state);
        R4S8CR_exit_error(UNA_R4S8CR_ERROR_BASE_R4S8CR);
        // Write register.
        for (idx=R4S8CR_RELAY_INDEX_MIN ; idx<=R4S8CR_RELAY_INDEX_MAX ; idx++) {
            // Convert to UNA bit representation.
            rxst[idx] = (((state >> idx) & 0x01) == 0) ? UNA_BIT_0 : UNA_BIT_1;
            // Write field.
            SWREG_write_field(&(R4S8CR_REGISTERS[R4S8CR_REGISTER_ADDRESS_STATUS]), &unused_mask, ((uint32_t) rxst[idx]), (0b11 << (idx << 1)));
        }
    }
    (*reg_value) = R4S8CR_REGISTERS[read_parameters->reg_addr];
errors:
    return status;
}

/*******************************************************************/
UNA_R4S8CR_status_t UNA_R4S8CR_scan(UNA_node_t* nodes_list, uint8_t nodes_list_size, uint8_t* nodes_count) {
    // Local variables.
    UNA_R4S8CR_status_t status = UNA_R4S8CR_SUCCESS;
    UNA_access_parameters_t read_params;
    UNA_access_status_t read_status;
    UNA_node_address_t node_addr = 0;
    uint8_t node_list_idx = 0;
    uint32_t reg_value = 0;
    // Check parameters.
    if ((nodes_list == NULL) || (nodes_list_size == 0) || (nodes_count == NULL)) {
        status = UNA_R4S8CR_ERROR_NULL_PARAMETER;
        goto errors;
    }
    // Reset count.
    (*nodes_count) = 0;
    // Build read input common parameters.
    read_params.reg_addr = R4S8CR_REGISTER_ADDRESS_STATUS;
    read_params.reply_params.type = UNA_REPLY_TYPE_VALUE;
    read_params.reply_params.timeout_ms = 0;
    // Loop on all addresses.
    for (node_addr=UNA_NODE_ADDRESS_R4S8CR_START ; node_addr<=UNA_NODE_ADDRESS_R4S8CR_END ; node_addr++) {
        // Update read parameters.
        read_params.node_addr = node_addr;
        // Ping address.
        status = UNA_R4S8CR_read_register(&read_params, &reg_value, &read_status);
        if (status != UNA_R4S8CR_SUCCESS) goto errors;
        // Check reply status.
        if (read_status.flags == 0) {
            // Node found.
            (*nodes_count)++;
            // Store address and reset board ID.
            nodes_list[node_list_idx].address = node_addr;
            nodes_list[node_list_idx].board_id = UNA_BOARD_ID_R4S8CR;
        }
        // Check index.
        if ((*nodes_count) >= nodes_list_size) break;
    }
errors:
    return status;
}

#endif /* UNA_R4S8CR_DISABLE */
