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
#include <getopt.h>
#include <math.h>
#include <stdlib.h>

/**
 * @brief     fm24clxx full function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *            - 0 success
 *            - 1 run failed
 *            - 5 param is invalid
 * @note      none
 */
uint8_t fm24clxx(uint8_t argc, char **argv)
{
    int c;
    int longindex = 0;
    const char short_options[] = "hipe:t:";
    const struct option long_options[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"information", no_argument, NULL, 'i'},
        {"port", no_argument, NULL, 'p'},
        {"example", required_argument, NULL, 'e'},
        {"test", required_argument, NULL, 't'},
        {"addr", required_argument, NULL, 1},
        {"data", required_argument, NULL, 2},
        {"reg", required_argument, NULL, 3},
        {"type", required_argument, NULL, 4},
        {NULL, 0, NULL, 0},
    };
    char type[33] = "unknown";
    uint16_t addr = 0x0000;
    uint8_t data = rand() % 0xFF;
    fm24clxx_address_t addr_pin = FM24CLXX_ADDRESS_A000;
    fm24clxx_t chip_type = FM24CL16B;

    /* if no params */
    if (argc == 1)
    {
        /* goto the help */
        goto help;
    }

    /* init 0 */
    optind = 0;

    /* parse */
    do
    {
        /* parse the args */
        c = getopt_long(argc, argv, short_options, long_options, &longindex);

        /* judge the result */
        switch (c)
        {
            /* help */
            case 'h' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "h");

                break;
            }

            /* information */
            case 'i' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "i");

                break;
            }

            /* port */
            case 'p' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "p");

                break;
            }

            /* example */
            case 'e' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "e_%s", optarg);

                break;
            }

            /* test */
            case 't' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "t_%s", optarg);

                break;
            }

            /* addr pin */
            case 1 :
            {
                /* set the addr pin */
                if (strcmp("0", optarg) == 0)
                {
                    addr_pin = FM24CLXX_ADDRESS_A000;
                }
                else if (strcmp("1", optarg) == 0)
                {
                    addr_pin = FM24CLXX_ADDRESS_A001;
                }
                else if (strcmp("2", optarg) == 0)
                {
                    addr_pin = FM24CLXX_ADDRESS_A010;
                }
                else if (strcmp("3", optarg) == 0)
                {
                    addr_pin = FM24CLXX_ADDRESS_A011;
                }
                else if (strcmp("4", optarg) == 0)
                {
                    addr_pin = FM24CLXX_ADDRESS_A100;
                }
                else if (strcmp("5", optarg) == 0)
                {
                    addr_pin = FM24CLXX_ADDRESS_A101;
                }
                else if (strcmp("6", optarg) == 0)
                {
                    addr_pin = FM24CLXX_ADDRESS_A110;
                }
                else if (strcmp("7", optarg) == 0)
                {
                    addr_pin = FM24CLXX_ADDRESS_A111;
                }
                else
                {
                    return 5;
                }

                break;
            }

            /* data */
            case 2 :
            {
                char *p;
                uint16_t l;
                uint16_t i;
                uint64_t hex_data;

                /* set the data */
                l = strlen(optarg);

                /* check the header */
                if (l >= 2)
                {
                    if (strncmp(optarg, "0x", 2) == 0)
                    {
                        p = optarg + 2;
                        l -= 2;
                    }
                    else if (strncmp(optarg, "0X", 2) == 0)
                    {
                        p = optarg + 2;
                        l -= 2;
                    }
                    else
                    {
                        p = optarg;
                    }
                }
                else
                {
                    p = optarg;
                }
                
                /* init 0 */
                hex_data = 0;

                /* loop */
                for (i = 0; i < l; i++)
                {
                    if ((p[i] <= '9') && (p[i] >= '0'))
                    {
                        hex_data += (p[i] - '0') * (uint32_t)pow(16, l - i - 1);
                    }
                    else if ((p[i] <= 'F') && (p[i] >= 'A'))
                    {
                        hex_data += ((p[i] - 'A') + 10) * (uint32_t)pow(16, l - i - 1);
                    }
                    else if ((p[i] <= 'f') && (p[i] >= 'a'))
                    {
                        hex_data += ((p[i] - 'a') + 10) * (uint32_t)pow(16, l - i - 1);
                    }
                    else
                    {
                        return 5;
                    }
                }
                
                /* set the data */
                data = hex_data % 0xFF;

                break;
            }
            
            /* addr */
            case 3 :
            {
                char *p;
                uint16_t l;
                uint16_t i;
                uint64_t hex_data;

                /* set the data */
                l = strlen(optarg);

                /* check the header */
                if (l >= 2)
                {
                    if (strncmp(optarg, "0x", 2) == 0)
                    {
                        p = optarg + 2;
                        l -= 2;
                    }
                    else if (strncmp(optarg, "0X", 2) == 0)
                    {
                        p = optarg + 2;
                        l -= 2;
                    }
                    else
                    {
                        p = optarg;
                    }
                }
                else
                {
                    p = optarg;
                }
                
                /* init 0 */
                hex_data = 0;

                /* loop */
                for (i = 0; i < l; i++)
                {
                    if ((p[i] <= '9') && (p[i] >= '0'))
                    {
                        hex_data += (p[i] - '0') * (uint32_t)pow(16, l - i - 1);
                    }
                    else if ((p[i] <= 'F') && (p[i] >= 'A'))
                    {
                        hex_data += ((p[i] - 'A') + 10) * (uint32_t)pow(16, l - i - 1);
                    }
                    else if ((p[i] <= 'f') && (p[i] >= 'a'))
                    {
                        hex_data += ((p[i] - 'a') + 10) * (uint32_t)pow(16, l - i - 1);
                    }
                    else
                    {
                        return 5;
                    }
                }
                
                /* set the addr */
                addr = hex_data % 0xFFFF;

                break;
            }

            /* type */
            case 4 :
            {
                if (strcmp("4", optarg) == 0)
                {
                    chip_type = FM24CL04B;
                }
                else if (strcmp("16", optarg) == 0)
                {
                    chip_type = FM24CL16B;
                }
                else if (strcmp("64", optarg) == 0)
                {
                    chip_type = FM24CL64B;
                }
                else
                {
                    return 5;
                }

                break;
            }

            /* the end */
            case -1 :
            {
                break;
            }

            /* others */
            default :
            {
                return 5;
            }
        }
    } while (c != -1);

    /* run the function */
    if (strcmp("t_read", type) == 0)
    {
        /* run read test */
        if (fm24clxx_read_test(chip_type, addr_pin) != 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if (strcmp("e_read", type) == 0)
    {
        uint8_t res;

        /* basic init */
        res = fm24clxx_basic_init(chip_type, addr_pin);
        if (res != 0)
        {
            return 1;
        }

        /* read data */
        res = fm24clxx_basic_read(addr, (uint8_t *)&data, 1);
        if (res != 0)
        {
            (void)fm24clxx_basic_deinit();

            return 1;
        }

        /* output */
        fm24clxx_interface_debug_print("fm24clxx: read 0x%04x is 0x%02X.\n", addr, data);

        /* deinit */
        (void)fm24clxx_basic_deinit();

        return 0;
    }
    else if (strcmp("e_write", type) == 0)
    {
        uint8_t res;

        /* basic init */
        res = fm24clxx_basic_init(chip_type, addr_pin);
        if (res != 0)
        {
            return 1;
        }

        /* write data */
        res = fm24clxx_basic_write(addr, (uint8_t *)&data, 1);
        if (res != 0)
        {
            (void)fm24clxx_basic_deinit();

            return 1;
        }

        /* output */
        fm24clxx_interface_debug_print("fm24clxx: write 0x%04x is 0x%02X.\n", addr, data);

        /* deinit */
        (void)fm24clxx_basic_deinit();

        return 0;
    }
    else if (strcmp("h", type) == 0)
    {
        help:
        fm24clxx_interface_debug_print("Usage:\n");
        fm24clxx_interface_debug_print("  fm24clxx (-i | --information)\n");
        fm24clxx_interface_debug_print("  fm24clxx (-h | --help)\n");
        fm24clxx_interface_debug_print("  fm24clxx (-p | --port)\n");
        fm24clxx_interface_debug_print("  fm24clxx (-t read | --test=read) [--type=<4 | 16 | 64>] [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>]\n");
        fm24clxx_interface_debug_print("  fm24clxx (-e read | --example=read) [--type=<4 | 16 | 64>] [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>]\n");
        fm24clxx_interface_debug_print("           [--reg=<address>]\n");
        fm24clxx_interface_debug_print("  fm24clxx (-e write | --example=write) [--type=<4 | 16 | 64>] [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>]\n");
        fm24clxx_interface_debug_print("           [--reg=<address>] [--data=<hex>]\n");
        fm24clxx_interface_debug_print("\n");
        fm24clxx_interface_debug_print("Options:\n");
        fm24clxx_interface_debug_print("      --addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>\n");
        fm24clxx_interface_debug_print("                                  Set the chip address pin.([default: 0])\n");
        fm24clxx_interface_debug_print("      --data=<hex>                Set the write data and it is hexadecimal.([default: random])\n");
        fm24clxx_interface_debug_print("  -e <read | write>, --example=<read | write>\n");
        fm24clxx_interface_debug_print("                                  Run the driver example.\n");
        fm24clxx_interface_debug_print("  -h, --help                      Show the help.\n");
        fm24clxx_interface_debug_print("  -i, --information               Show the chip information.\n");
        fm24clxx_interface_debug_print("  -p, --port                      Display the pin connections of the current board.\n");
        fm24clxx_interface_debug_print("      --reg=<address>             Set the register address and it is hexadecimal.([default: 0])\n");
        fm24clxx_interface_debug_print("  -t <read>, --test=<read>        Run the driver test.\n");
        fm24clxx_interface_debug_print("      --type=<4 | 16 | 64>        Set the chip type.([default: 16])\n");

        return 0;
    }
    else if (strcmp("i", type) == 0)
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
    else if (strcmp("p", type) == 0)
    {
        /* print pin connection */
        fm24clxx_interface_debug_print("fm24clxx: SCL connected to GPIO3(BCM).\n");
        fm24clxx_interface_debug_print("fm24clxx: SDA connected to GPIO2(BCM).\n");
        
        return 0;
    }
    else
    {
        return 5;
    }
}

/**
 * @brief     main function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *             - 0 success
 * @note      none
 */
int main(uint8_t argc, char **argv)
{
    uint8_t res;

    res = fm24clxx(argc, argv);
    if (res == 0)
    {
        /* run success */
    }
    else if (res == 1)
    {
        fm24clxx_interface_debug_print("fm24clxx: run failed.\n");
    }
    else if (res == 5)
    {
        fm24clxx_interface_debug_print("fm24clxx: param is invalid.\n");
    }
    else
    {
        fm24clxx_interface_debug_print("fm24clxx: unknown status code.\n");
    }

    return 0;
}