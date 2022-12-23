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
 * @file      driver_fm24clxx_read_test.c
 * @brief     driver fm24clxx read test source file
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
 
#include "driver_fm24clxx_read_test.h"
#include <stdlib.h>

static fm24clxx_handle_t gs_handle;        /**< fm24clxx handle */

/**
 * @brief     read test
 * @param[in] type is the chip type
 * @param[in] address is the chip address pin
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t fm24clxx_read_test(fm24clxx_t type, fm24clxx_address_t address)
{
    uint8_t res, i, j;
    uint8_t buf[12];
    uint8_t buf_check[12];
    uint16_t inc;
    fm24clxx_info_t info;
    
    /* link interface function */
    DRIVER_FM24CLXX_LINK_INIT(&gs_handle, fm24clxx_handle_t);
    DRIVER_FM24CLXX_LINK_IIC_INIT(&gs_handle, fm24clxx_interface_iic_init);
    DRIVER_FM24CLXX_LINK_IIC_DEINIT(&gs_handle, fm24clxx_interface_iic_deinit);
    DRIVER_FM24CLXX_LINK_IIC_READ(&gs_handle, fm24clxx_interface_iic_read);
    DRIVER_FM24CLXX_LINK_IIC_WRITE(&gs_handle, fm24clxx_interface_iic_write);
    DRIVER_FM24CLXX_LINK_IIC_READ_ADDRESS16(&gs_handle, fm24clxx_interface_iic_read_address16);
    DRIVER_FM24CLXX_LINK_IIC_WRITE_ADDRESS16(&gs_handle, fm24clxx_interface_iic_write_address16);
    DRIVER_FM24CLXX_LINK_DELAY_MS(&gs_handle, fm24clxx_interface_delay_ms);
    DRIVER_FM24CLXX_LINK_DEBUG_PRINT(&gs_handle, fm24clxx_interface_debug_print);
    
    /* get information */
    res = fm24clxx_info(&info);
    if (res != 0)
    {
        fm24clxx_interface_debug_print("fm24clxx: get info failed.\n");
       
        return 1;
    }
    else
    {
        /* print chip information */
        fm24clxx_interface_debug_print("fm24clxx: chip is %s.\n", info.chip_name);
        fm24clxx_interface_debug_print("fm24clxx: manufacturer is %s.\n", info.manufacturer_name);
        fm24clxx_interface_debug_print("fm24clxx: interface is %s.\n", info.interface);
        fm24clxx_interface_debug_print("fm24clxx: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        fm24clxx_interface_debug_print("fm24clxx: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        fm24clxx_interface_debug_print("fm24clxx: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        fm24clxx_interface_debug_print("fm24clxx: max current is %0.2fmA.\n", info.max_current_ma);
        fm24clxx_interface_debug_print("fm24clxx: max temperature is %0.1fC.\n", info.temperature_max);
        fm24clxx_interface_debug_print("fm24clxx: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
    /* set chip type */
    res = fm24clxx_set_type(&gs_handle, type);
    if (res != 0)
    {
        fm24clxx_interface_debug_print("fm24clxx: set type failed.\n");
       
        return 1;
    }
    
    /* set iic addr pin */
    res = fm24clxx_set_addr_pin(&gs_handle, address);
    if (res != 0)
    {
        fm24clxx_interface_debug_print("fm24clxx: set address pin failed.\n");
       
        return 1;
    }
    
    /* fm24clxx init */
    res = fm24clxx_init(&gs_handle);
    if (res != 0)
    {
        fm24clxx_interface_debug_print("fm24clxx: init failed.\n");
       
        return 1;
    }
    
    /* start read test */
    fm24clxx_interface_debug_print("fm24clxx: start read test.\n");
    inc = ((uint16_t)type + 1) / 8;
    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 12; j++)
        {
            buf[j] = (uint8_t)(rand() % 256);
        }
    
        /* write data */
        res = fm24clxx_write(&gs_handle, i*inc, (uint8_t *)buf, 12);
        if (res != 0)
        {
            fm24clxx_interface_debug_print("fm24clxx: write failed.\n");
            (void)fm24clxx_deinit(&gs_handle);
            
            return 1;
        }

        /* read data */
        res = fm24clxx_read(&gs_handle, i*inc, (uint8_t *)buf_check, 12);
        if (res != 0)
        {
            fm24clxx_interface_debug_print("fm24clxx: read failed.\n");
            (void)fm24clxx_deinit(&gs_handle);
            
            return 1;
        }
        for (j = 0; j < 12; j++)
        {
            /* check data */
            if (buf[j] != buf_check[j])
            {
                fm24clxx_interface_debug_print("fm24clxx: check error.\n");
                (void)fm24clxx_deinit(&gs_handle);
                
                return 1;
            }
        }
        fm24clxx_interface_debug_print("fm24clxx: 0x%04X read write test passed.\n", i*inc);
    }

    /* finish read test */
    fm24clxx_interface_debug_print("fm24clxx: finish read test.\n");
    (void)fm24clxx_deinit(&gs_handle);
    
    return 0;
}
