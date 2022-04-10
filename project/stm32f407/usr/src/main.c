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
 * @file      main.c
 * @brief     main source file
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
#include "driver_fm24clxx_basic.h"
#include "shell.h"
#include "clock.h"
#include "delay.h"
#include "uart.h"
#include <stdlib.h>

/**
 * @brief global var definition
 */
uint8_t g_buf[256];        /**< uart buffer */
uint16_t g_len;            /**< uart buffer length */

/**
 * @brief     fm24clxx full function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *             - 0 success
 *             - 1 run failed
 *             - 5 param is invalid
 * @note      none
 */
uint8_t fm24clxx(uint8_t argc, char **argv)
{
    if (argc == 1)
    {
        goto help;
    }
    if (argc == 2)
    {
        if (strcmp("-i", argv[1]) == 0)
        {
            fm24clxx_info_t info;
            
            /* print fm24clxx info */
            fm24clxx_info(&info);
            fm24clxx_interface_debug_print("fm24clxx: chip is %s.\n", info.chip_name);
            fm24clxx_interface_debug_print("fm24clxx: manufacturer is %s.\n", info.manufacturer_name);
            fm24clxx_interface_debug_print("fm24clxx: interface is %s.\n", info.interface);
            fm24clxx_interface_debug_print("fm24clxx: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
            fm24clxx_interface_debug_print("fm24clxx: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
            fm24clxx_interface_debug_print("fm24clxx: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
            fm24clxx_interface_debug_print("fm24clxx: max current is %0.2fmA.\n", info.max_current_ma);
            fm24clxx_interface_debug_print("fm24clxx: max temperature is %0.1fC.\n", info.temperature_max);
            fm24clxx_interface_debug_print("fm24clxx: min temperature is %0.1fC.\n", info.temperature_min);
            
            return 0;
        }
        else if (strcmp("-p", argv[1]) == 0)
        {
            /* print pin connection */
            fm24clxx_interface_debug_print("fm24clxx: SCL connected to GPIOB PIN8.\n");
            fm24clxx_interface_debug_print("fm24clxx: SDA connected to GPIOB PIN9.\n");
            
            return 0;
        }
        else if (strcmp("-h", argv[1]) == 0)
        {
            /* show fm24clxx help */
            
            help:
            
            fm24clxx_interface_debug_print("fm24clxx -i\n\tshow fm24clxx chip and driver information.\n");
            fm24clxx_interface_debug_print("fm24clxx -h\n\tshow fm24clxx help.\n");
            fm24clxx_interface_debug_print("fm24clxx -p\n\tshow fm24clxx pin connections of the current board.\n");
            fm24clxx_interface_debug_print("fm24clxx -t read -type (4 | 16 | 64) -a (0 | 1| 2 | 3 | 4 | 5 | 6 | 7)\n\t"
                                           "run fm24clxx read test.\n");
            fm24clxx_interface_debug_print("fm24clxx -c read -type (4 | 16 | 64) -a (0 | 1| 2 | 3 | 4 | 5 | 6 | 7) <registeraddr>\n\t"
                                           "run fm24clxx read function.\n");
            fm24clxx_interface_debug_print("fm24clxx -c write -type (4 | 16 | 64) -a (0 | 1| 2 | 3 | 4 | 5 | 6 | 7) <registeraddr> <data>\n\t"
                                           "run fm24clxx write function.data is hexadecimal.\n");
            
            return 0;
        }
        else
        {
            return 5;
        }
    }
    else if (argc == 7)
    {
        /* run test */
        if (strcmp("-t", argv[1]) == 0)
        {
             /* read test */
            if (strcmp("read", argv[2]) == 0)
            {
                fm24clxx_t type;
                fm24clxx_address_t address;
                
                if (strcmp("type", argv[3]) == 0)
                {
                    return 5;
                }
                if (strcmp("4", argv[4]) == 0)
                {
                    type = FM24CL04B;
                }
                else if (strcmp("16", argv[4]) == 0)
                {
                    type = FM24CL16B;
                }
                else if (strcmp("64", argv[4]) == 0)
                {
                    type = FM24CL64B;
                }
                else
                {
                    fm24clxx_interface_debug_print("fm24clxx: type is invalid.\n");
                    
                    return 5;
                }
                if (strcmp("a", argv[5]) == 0)
                {
                    return 5;
                }
                if ((argv[6][0]<'0') || argv[6][0]>'7')
                {
                    fm24clxx_interface_debug_print("fm24clxx: iic address is invalid.\n");
                    
                    return 5;
                }
                address = (fm24clxx_address_t)atoi(argv[6]);
                
                /* run read test */
                if (fm24clxx_read_test(type, address) != 0)
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    else if (argc == 8)
    {
        /* run function */
        if (strcmp("-c", argv[1]) == 0)
        {
            /* read function */
            if (strcmp("read", argv[2]) == 0)
            {
                uint8_t res;
                uint8_t data;
                uint16_t reg_address;
                fm24clxx_t type;
                fm24clxx_address_t address;
                
                if (strcmp("type", argv[3]) == 0)
                {
                    return 5;
                }
                if (strcmp("4", argv[4]) == 0)
                {
                    type = FM24CL04B;
                }
                else if (strcmp("16", argv[4]) == 0)
                {
                    type = FM24CL16B;
                }
                else if (strcmp("64", argv[4]) == 0)
                {
                    type = FM24CL64B;
                }
                else
                {
                    fm24clxx_interface_debug_print("fm24clxx: type is invalid.\n");
                    
                    return 5;
                }
                if (strcmp("a", argv[5]) == 0)
                {
                    return 5;
                }
                if ((argv[6][0]<'0') || argv[6][0]>'7')
                {
                    fm24clxx_interface_debug_print("fm24clxx: iic address is invalid.\n");
                    
                    return 5;
                }
                address = (fm24clxx_address_t)atoi(argv[6]);
                if (strlen(argv[7]) < 4)
                {
                    fm24clxx_interface_debug_print("fm24clxx: read address length must be 4.\n");
                    
                    return 5;
                }
                reg_address = 0;
                if ((argv[7][0] <= '9') && (argv[7][0] >= '0'))
                {
                    reg_address = (argv[7][0] - '0') * 16 * 16 *16;
                }
                else
                {
                    reg_address = (argv[7][0] - 'A' + 10) * 16 * 16 *16;
                }
                if ((argv[7][1] <= '9') && (argv[7][1] >= '0'))
                {
                    reg_address += (argv[7][1] - '0') * 16 *16;
                }
                else
                {
                    reg_address += (argv[7][1] - 'A' + 10) * 16 * 16;
                }
                if ((argv[7][2] <= '9') && (argv[7][2] >= '0'))
                {
                    reg_address += (argv[7][2] - '0') * 16;
                }
                else
                {
                    reg_address += (argv[7][2] - 'A' + 10) * 16;
                }
                if ((argv[7][3] <= '9') && (argv[7][3] >= '0'))
                {
                    reg_address += (argv[7][3] - '0');
                }
                else
                {
                    reg_address += (argv[7][3] - 'A' + 10);
                }
                res = fm24clxx_basic_init(type, address);
                if (res != 0)
                {
                    return 1;
                }
                res = fm24clxx_basic_read(reg_address, (uint8_t *)&data, 1);
                if (res != 0)
                {
                    (void)fm24clxx_basic_deinit();
                    
                    return 1;
                }
                else
                {
                    fm24clxx_interface_debug_print("fm24clxx: read 0x%04x is 0x%02X.\n", reg_address, data);
                }
                (void)fm24clxx_basic_deinit();
                
                return 0;
            }
            
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    else if (argc == 9)
    {
        /* run function */
        if (strcmp("-c", argv[1]) == 0)
        {
            /* write function */
            if (strcmp("write", argv[2]) == 0)
            {
                uint8_t res;
                uint8_t data;
                uint16_t reg_address;
                fm24clxx_t type;
                fm24clxx_address_t address;
                
                if (strcmp("type", argv[3]) == 0)
                {
                    return 5;
                }
                if (strcmp("4", argv[4]) == 0)
                {
                    type = FM24CL04B;
                }
                else if (strcmp("16", argv[4]) == 0)
                {
                    type = FM24CL16B;
                }
                else if (strcmp("64", argv[4]) == 0)
                {
                    type = FM24CL64B;
                }
                else
                {
                    fm24clxx_interface_debug_print("fm24clxx: type is invalid.\n");
                    
                    return 5;
                }
                if (strcmp("a", argv[5]) == 0)
                {
                    return 5;
                }
                if ((argv[6][0]<'0') || argv[6][0]>'7')
                {
                    fm24clxx_interface_debug_print("fm24clxx: iic address is invalid.\n");
                    
                    return 5;
                }
                address = (fm24clxx_address_t)atoi(argv[6]);
                if (strlen(argv[7]) < 4)
                {
                    fm24clxx_interface_debug_print("fm24clxx: write address length must be 4.\n");
                    
                    return 5;
                }
                reg_address = 0;
                if ((argv[7][0] <= '9') && (argv[7][0] >= '0'))
                {
                    reg_address = (argv[7][0] - '0') * 16 * 16 *16;
                }
                else
                {
                    reg_address = (argv[7][0] - 'A' + 10) * 16 * 16 *16;
                }
                if ((argv[7][1] <= '9') && (argv[7][1] >= '0'))
                {
                    reg_address += (argv[7][1] - '0') * 16 *16;
                }
                else
                {
                    reg_address += (argv[7][1] - 'A' + 10) * 16 * 16;
                }
                if ((argv[7][2] <= '9') && (argv[7][2] >= '0'))
                {
                    reg_address += (argv[7][2] - '0') * 16;
                }
                else
                {
                    reg_address += (argv[7][2] - 'A' + 10) * 16;
                }
                if ((argv[7][3] <= '9') && (argv[7][3] >= '0'))
                {
                    reg_address += (argv[7][3] - '0');
                }
                else
                {
                    reg_address += (argv[7][3] - 'A' + 10);
                }
                data = 0;
                if ((argv[8][0] <= '9') && (argv[8][0] >= '0'))
                {
                    data += (argv[8][0] - '0') * 16;
                }
                else
                {
                    data += (argv[8][0] - 'A' + 10) * 16;
                }
                if ((argv[8][1] <= '9') && (argv[8][1] >= '0'))
                {
                    data += (argv[8][1] - '0');
                }
                else
                {
                    data += (argv[8][1] - 'A' + 10);
                }
                res = fm24clxx_basic_init(type, address);
                if (res != 0)
                {
                    return 1;
                }
                res = fm24clxx_basic_write(reg_address, (uint8_t *)&data, 1);
                if (res != 0)
                {
                    (void)fm24clxx_basic_deinit();
                    
                    return 1;
                }
                else
                {
                    fm24clxx_interface_debug_print("fm24clxx: write 0x%04x is 0x%02X.\n", reg_address, data);
                }
                (void)fm24clxx_basic_deinit();
                
                return 0;
            }
            
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    
    /* param is invalid */
    else
    {
        return 5;
    }
}

/**
 * @brief main function
 * @note  none
 */
int main(void)
{
    uint8_t res;
    
    /* stm32f407 clock init and hal init */
    clock_init();
    
    /* delay init */
    delay_init();
    
    /* uart1 init */
    uart1_init(115200);
    
    /* shell init && register fm24clxx fuction */
    shell_init();
    shell_register("fm24clxx", fm24clxx);
    uart1_print("fm24clxx: welcome to libdriver fm24clxx.\n");
    
    while (1)
    {
        /* read uart */
        g_len = uart1_read(g_buf, 256);
        if (g_len)
        {
            /* run shell */
            res = shell_parse((char *)g_buf, g_len);
            if (res == 0)
            {
                /* run success */
            }
            else if (res == 1)
            {
                uart1_print("fm24clxx: run failed.\n");
            }
            else if (res == 2)
            {
                uart1_print("fm24clxx: unknow command.\n");
            }
            else if (res == 3)
            {
                uart1_print("fm24clxx: length is too long.\n");
            }
            else if (res == 4)
            {
                uart1_print("fm24clxx: pretreat failed.\n");
            }
            else if (res == 5)
            {
                uart1_print("fm24clxx: param is invalid.\n");
            }
            else
            {
                uart1_print("fm24clxx: unknow status code.\n");
            }
            uart1_flush();
        }
        delay_ms(100);
    }
}
