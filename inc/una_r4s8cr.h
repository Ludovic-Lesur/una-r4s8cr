/*
 * una_r4s8cr.h
 *
 *  Created on: 06 dec. 2024
 *      Author: Ludo
 */

#ifndef __UNA_R4S8CR_H__
#define __UNA_R4S8CR_H__

#ifndef UNA_R4S8CR_DISABLE_FLAGS_FILE
#include "una_r4s8cr_flags.h"
#endif
#include "r4s8cr.h"
#include "strings.h"
#include "types.h"
#include "una.h"

/*** UNA R4S8CR structures ***/

/*!******************************************************************
 * \enum UNA_R4S8CR_status_t
 * \brief UNA R4S8CR driver error codes.
 *******************************************************************/
typedef enum {
    // Driver errors.
    UNA_R4S8CR_SUCCESS = 0,
    UNA_R4S8CR_ERROR_NULL_PARAMETER,
    // Low level drivers errors.
    UNA_R4S8CR_ERROR_BASE_R4S8CR = 0x0100,
    UNA_R4S8CR_ERROR_BASE_STRING = (UNA_R4S8CR_ERROR_BASE_R4S8CR + R4S8CR_ERROR_BASE_LAST),
    // Last base value.
    UNA_R4S8CR_ERROR_BASE_LAST = (UNA_R4S8CR_ERROR_BASE_STRING + STRING_ERROR_BASE_LAST)
} UNA_R4S8CR_status_t;

#ifndef UNA_R4S8CR_DISABLE

/*** UNA R4S8CR functions ***/

/*!******************************************************************
 * \fn UNA_R4S8CR_status_t UNA_R4S8CR_init(void)
 * \brief Init UNA interface.
 * \param[in]   none
 * \param[out]  none
 * \retval      Function execution status.
 *******************************************************************/
UNA_R4S8CR_status_t UNA_R4S8CR_init(void);

/*!******************************************************************
 * \fn UNA_R4S8CR_status_t UNA_R4S8CR_de_init(void)
 * \brief Release UNA interface.
 * \param[in]   none
 * \param[out]  none
 * \retval      Function execution status.
 *******************************************************************/
UNA_R4S8CR_status_t UNA_R4S8CR_de_init(void);

/*!******************************************************************
 * \fn UNA_R4S8CR_status_t UNA_R4S8CR_send_command(UNA_command_parameters_t* command_parameters)
 * \brief Send a command over UNA R4S8CR interface.
 * \param[in]   command_parameters: Pointer to the command parameters.
 * \param[out]  none
 * \retval      Function execution status.
 *******************************************************************/
UNA_R4S8CR_status_t UNA_R4S8CR_send_command(UNA_command_parameters_t* command_parameters);

/*!******************************************************************
 * \fn UNA_R4S8CR_status_t UNA_R4S8CR_write_register(UNA_access_parameters_t* write_parameters, uint32_t reg_value, uint32_t reg_mask, UNA_access_status_t* write_status)
 * \brief Write node register through UNA interface.
 * \param[in]   write_parameters: Pointer to the write operation parameters.
 * \param[in]   reg_value: Register value to write.
 * \param[in]   reg_mask: Writing operation mask.
 * \param[out]  write_status: Pointer to the writing operation status.
 * \retval      Function execution status.
 *******************************************************************/
UNA_R4S8CR_status_t UNA_R4S8CR_write_register(UNA_access_parameters_t* write_parameters, uint32_t reg_value, uint32_t reg_mask, UNA_access_status_t* write_status);

/*!******************************************************************
 * \fn UNA_R4S8CR_status_t UNA_R4S8CR_read_register(UNA_access_parameters_t* read_parameters, uint32_t* reg_value, UNA_access_status_t* read_status)
 * \brief Read node register through UNA interface.
 * \param[in]   read_parameters: Pointer to the read operation parameters.
 * \param[out]  reg_value: Pointer to the read register value.
 * \param[out]  read_status: Pointer to the read operation status.
 * \retval      Function execution status.
 *******************************************************************/
UNA_R4S8CR_status_t UNA_R4S8CR_read_register(UNA_access_parameters_t* read_parameters, uint32_t* reg_value, UNA_access_status_t* read_status);

/*!******************************************************************
 * \fn UNA_R4S8CR_status_t UNA_R4S8CR_scan(UNA_node_t* nodes_list, uint8_t nodes_list_size, uint8_t* nodes_count)
 * \brief Scan all R4S8CR nodes connected to the bus.
 * \param[in]   nodes_list_size: Maximum size of the node list.
 * \param[out]  nodes_list: Pointer to the list where to store the nodes.
 * \param[out]  nodes_count: Pointer to the number of nodes detected.
 * \retval      Function execution status.
 *******************************************************************/
UNA_R4S8CR_status_t UNA_R4S8CR_scan(UNA_node_t* nodes_list, uint8_t nodes_list_size, uint8_t* nodes_count);

/*******************************************************************/
#define UNA_R4S8CR_exit_error(base) { ERROR_check_exit(una_r4s8cr_status, UNA_R4S8CR_SUCCESS, base) }

/*******************************************************************/
#define UNA_R4S8CR_stack_error(base) { ERROR_check_stack(una_r4s8cr_status, UNA_R4S8CR_SUCCESS, base) }

/*******************************************************************/
#define UNA_R4S8CR_stack_exit_error(base, code) { ERROR_check_stack_exit(una_r4s8cr_status, UNA_R4S8CR_SUCCESS, base, code) }

#endif /* UNA_R4S8CR_DISABLE */

#endif /* __UNA_R4S8CR_H__ */
