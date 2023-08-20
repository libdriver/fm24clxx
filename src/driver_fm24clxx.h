/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      driver_fm24clxx.h
 * @brief     driver fm24clxx header file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2021-06-15
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2021/06/15  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#ifndef DRIVER_FM24CLXX_H
#define DRIVER_FM24CLXX_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup fm24clxx_driver fm24clxx driver function
 * @brief    fm24clxx driver modules
 * @{
 */

/**
 * @addtogroup fm24clxx_base_driver
 * @{
 */

/**
 * @brief fm24clxx type enumeration definition
 */
typedef enum
{
    FM24CL04B = 512,          /**< FM24CL04B type */
    FM24CL16B = 2048,         /**< FM24CL16B type */
    FM24CL64B = 8192,         /**< FM24CL64B type */
} fm24clxx_t;

/**
 * @brief fm24clxx address enumeration definition
 */
typedef enum
{
    FM24CLXX_ADDRESS_A000 = 0,        /**< A2A1A0 000 */
    FM24CLXX_ADDRESS_A001 = 1,        /**< A2A1A0 001 */
    FM24CLXX_ADDRESS_A010 = 2,        /**< A2A1A0 010 */
    FM24CLXX_ADDRESS_A011 = 3,        /**< A2A1A0 011 */
    FM24CLXX_ADDRESS_A100 = 4,        /**< A2A1A0 100 */
    FM24CLXX_ADDRESS_A101 = 5,        /**< A2A1A0 101 */
    FM24CLXX_ADDRESS_A110 = 6,        /**< A2A1A0 110 */
    FM24CLXX_ADDRESS_A111 = 7,        /**< A2A1A0 111 */
} fm24clxx_address_t;

/**
 * @brief fm24clxx handle structure definition
 */
typedef struct fm24clxx_handle_s
{
    uint8_t iic_addr;                                                                              /**< iic device address */
    uint8_t (*iic_init)(void);                                                                     /**< point to an iic_init function address */
    uint8_t (*iic_deinit)(void);                                                                   /**< point to an iic_deinit function address */
    uint8_t (*iic_read)(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);                    /**< point to an iic_read function address */
    uint8_t (*iic_write)(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);                   /**< point to an iic_write function address */
    uint8_t (*iic_read_address16)(uint8_t addr, uint16_t reg, uint8_t *buf, uint16_t len);         /**< point to an iic_read_address16 function address */
    uint8_t (*iic_write_address16)(uint8_t addr, uint16_t reg, uint8_t *buf, uint16_t len);        /**< point to an iic_write_address16 function address */
    void (*delay_ms)(uint32_t ms);                                                                 /**< point to a delay_ms function address */
    void (*debug_print)(const char *const fmt, ...);                                               /**< point to a debug_print function address */
    uint16_t id;                                                                                   /**< chip id */
    uint8_t inited;                                                                                /**< inited flag */
} fm24clxx_handle_t;

/**
 * @brief fm24clxx information structure definition
 */
typedef struct fm24clxx_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[8];                 /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} fm24clxx_info_t;

/**
 * @}
 */

/**
 * @defgroup fm24clxx_link_driver fm24clxx link driver function
 * @brief    fm24clxx link driver modules
 * @ingroup  fm24clxx_driver
 * @{
 */

/**
 * @brief     initialize fm24clxx_handle_t structure
 * @param[in] HANDLE points to an fm24clxx handle structure
 * @param[in] STRUCTURE is fm24clxx_handle_t
 * @note      none
 */
#define DRIVER_FM24CLXX_LINK_INIT(HANDLE, STRUCTURE)           memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link iic_init function
 * @param[in] HANDLE points to an fm24clxx handle structure
 * @param[in] FUC points to an iic_init function address
 * @note      none
 */
#define DRIVER_FM24CLXX_LINK_IIC_INIT(HANDLE, FUC)             (HANDLE)->iic_init = FUC

/**
 * @brief     link iic_deinit function
 * @param[in] HANDLE points to an fm24clxx handle structure
 * @param[in] FUC points to an iic_deinit function address
 * @note      none
 */
#define DRIVER_FM24CLXX_LINK_IIC_DEINIT(HANDLE, FUC)           (HANDLE)->iic_deinit = FUC

/**
 * @brief     link iic_read function
 * @param[in] HANDLE points to an fm24clxx handle structure
 * @param[in] FUC points to an iic_read function address
 * @note      none
 */
#define DRIVER_FM24CLXX_LINK_IIC_READ(HANDLE, FUC)             (HANDLE)->iic_read = FUC

/**
 * @brief     link iic_write function
 * @param[in] HANDLE points to an fm24clxx handle structure
 * @param[in] FUC points to an iic_write function address
 * @note      none
 */
#define DRIVER_FM24CLXX_LINK_IIC_WRITE(HANDLE, FUC)            (HANDLE)->iic_write = FUC

/**
 * @brief     link iic_read_address16 function
 * @param[in] HANDLE points to an fm24clxx handle structure
 * @param[in] FUC points to an iic_read_address16 function address
 * @note      none
 */
#define DRIVER_FM24CLXX_LINK_IIC_READ_ADDRESS16(HANDLE, FUC)   (HANDLE)->iic_read_address16 = FUC

/**
 * @brief     link iic_write_address16 function
 * @param[in] HANDLE points to an fm24clxx handle structure
 * @param[in] FUC points to an iic_write_address16 function address
 * @note      none
 */
#define DRIVER_FM24CLXX_LINK_IIC_WRITE_ADDRESS16(HANDLE, FUC)  (HANDLE)->iic_write_address16 = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE points to an fm24clxx handle structure
 * @param[in] FUC points to a delay_ms function address
 * @note      none
 */
#define DRIVER_FM24CLXX_LINK_DELAY_MS(HANDLE, FUC)             (HANDLE)->delay_ms = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE points to an fm24clxx handle structure
 * @param[in] FUC points to a debug_print function address
 * @note      none
 */
#define DRIVER_FM24CLXX_LINK_DEBUG_PRINT(HANDLE, FUC)          (HANDLE)->debug_print = FUC

/**
 * @}
 */

/**
 * @defgroup fm24clxx_base_driver fm24clxx base driver function
 * @brief    fm24clxx base driver modules
 * @ingroup  fm24clxx_driver
 * @{
 */

/**
 * @brief      get chip's information
 * @param[out] *info points to an fm24clxx info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t fm24clxx_info(fm24clxx_info_t *info);

/**
 * @brief     initialize the chip
 * @param[in] *handle points to an fm24clxx handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 * @note      none
 */
uint8_t fm24clxx_init(fm24clxx_handle_t *handle);

/**
 * @brief     close the chip
 * @param[in] *handle points to an fm24clxx handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t fm24clxx_deinit(fm24clxx_handle_t *handle);

/**
 * @brief     set the chip type
 * @param[in] *handle points to an fm24clxx handle structure
 * @param[in] type is the chip type
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 * @note      none
 */
uint8_t fm24clxx_set_type(fm24clxx_handle_t *handle, fm24clxx_t type);

/**
 * @brief      get the chip type
 * @param[in]  *handle points to an fm24clxx handle structure
 * @param[out] *type points to a chip type buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t fm24clxx_get_type(fm24clxx_handle_t *handle, fm24clxx_t *type);

/**
 * @brief     set the chip address pin
 * @param[in] *handle points to an fm24clxx handle structure
 * @param[in] addr_pin is the chip address pin
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 * @note      none
 */
uint8_t fm24clxx_set_addr_pin(fm24clxx_handle_t *handle, fm24clxx_address_t addr_pin);

/**
 * @brief      get the chip address pin
 * @param[in]  *handle points to an fm24clxx handle structure
 * @param[out] *addr_pin points to a chip address pin
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t fm24clxx_get_addr_pin(fm24clxx_handle_t *handle, fm24clxx_address_t *addr_pin);

/**
 * @brief      read bytes from the chip
 * @param[in]  *handle points to an fm24clxx handle structure
 * @param[in]  address is the register address
 * @param[out] *buf points to a data buffer
 * @param[in]  len is the buffer length
 * @return     status code
 *             - 0 success
 *             - 1 read data failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 end address is over the max address
 * @note       none
 */
uint8_t fm24clxx_read(fm24clxx_handle_t *handle, uint16_t address, uint8_t *buf, uint16_t len);

/**
 * @brief     write bytes to the chip
 * @param[in] *handle points to an fm24clxx handle structure
 * @param[in] address is the register address
 * @param[in] *buf points to a data buffer
 * @param[in] len is the buffer length
 * @return    status code
 *            - 0 success
 *            - 1 write data failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 end address is over the max address
 * @note      none
 */
uint8_t fm24clxx_write(fm24clxx_handle_t *handle, uint16_t address, uint8_t *buf, uint16_t len);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
