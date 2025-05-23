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
 * @file      driver_fm24clxx.c
 * @brief     driver fm24clxx source file
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

#include "driver_fm24clxx.h"

/**
 * @brief chip information definition
 */
#define CHIP_NAME                 "Cypress FM24CLXX"        /**< chip name */
#define MANUFACTURER_NAME         "Cypress"                 /**< manufacturer name */
#define SUPPLY_VOLTAGE_MIN        2.7f                      /**< chip min supply voltage */
#define SUPPLY_VOLTAGE_MAX        3.65f                     /**< chip max supply voltage */
#define MAX_CURRENT               0.1f                      /**< chip max current */
#define TEMPERATURE_MIN           -40.0f                    /**< chip min operating temperature */
#define TEMPERATURE_MAX           85.0f                     /**< chip max operating temperature */
#define DRIVER_VERSION            1000                      /**< driver version */

/**
 * @brief     initialize the chip
 * @param[in] *handle pointer to an fm24clxx handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 * @note      none
 */
uint8_t fm24clxx_init(fm24clxx_handle_t *handle)
{
    if (handle == NULL)                                                         /* check handle */
    {
        return 2;                                                               /* return error */
    }
    if (handle->debug_print == NULL)                                            /* check debug_print */
    {
        return 3;                                                               /* return error */
    }
    if (handle->iic_init == NULL)                                               /* check iic_init */
    {
        handle->debug_print("fm24clxx: iic_init is null.\n");                   /* iic_init is null */
       
        return 3;                                                               /* return error */
    }
    if (handle->iic_deinit == NULL)                                             /* check iic_deinit */
    {
        handle->debug_print("fm24clxx: iic_deinit is null.\n");                 /* iic_deinit is null */
       
        return 3;                                                               /* return error */
    }
    if (handle->iic_read == NULL)                                               /* check iic_read */
    {
        handle->debug_print("fm24clxx: iic_read is null.\n");                   /* iic_read is null */
       
        return 3;                                                               /* return error */
    }
    if (handle->iic_write == NULL)                                              /* check iic_write */
    {
        handle->debug_print("fm24clxx: iic_write is null.\n");                  /* iic_write is null */
       
        return 3;                                                               /* return error */
    }
    if (handle->iic_read_address16 == NULL)                                     /* check iic_read_address16 */
    {
        handle->debug_print("fm24clxx: iic_read_address16 is null.\n");         /* iic_read_address16 is null */
       
        return 3;                                                               /* return error */
    }
    if (handle->iic_write_address16 == NULL)                                    /* check iic_write_address16 */
    {
        handle->debug_print("fm24clxx: iic_write_address16 is null.\n");        /* iic_write_address16 is null */
       
        return 3;                                                               /* return error */
    }
    if (handle->delay_ms == NULL)                                               /* check delay_ms */
    {
        handle->debug_print("fm24clxx: delay_ms is null.\n");                   /* delay_ms is null */
       
        return 3;                                                               /* return error */
    }

    if (handle->iic_init() != 0)                                                /* iic init */
    {
        handle->debug_print("fm24clxx: iic init failed.\n");                    /* iic init failed */
       
        return 1;                                                               /* return error */
    }
    handle->inited = 1;                                                         /* flag finish initialization */

    return 0;                                                                   /* success return 0 */
}

/**
 * @brief     close the chip
 * @param[in] *handle pointer to an fm24clxx handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t fm24clxx_deinit(fm24clxx_handle_t *handle)
{
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    
    if (handle->iic_deinit() != 0)                                    /* iic deinit */
    {
        handle->debug_print("fm24clxx: iic deinit failed.\n");        /* iic deinit failed */
        
        return 1;                                                     /* return error */
    }   
    handle->inited = 0;                                               /* flag close */
    
    return 0;                                                         /* success return 0 */
}

/**
 * @brief     set the chip type
 * @param[in] *handle pointer to an fm24clxx handle structure
 * @param[in] type chip type
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 * @note      none
 */
uint8_t fm24clxx_set_type(fm24clxx_handle_t *handle, fm24clxx_t type)
{
    if (handle == NULL)                 /* check handle */
    {
        return 2;                       /* return error */
    }

    handle->id = (uint16_t)type;        /* set id */
    
    return 0;                           /* success return 0 */
}

/**
 * @brief      get the chip type
 * @param[in]  *handle pointer to an fm24clxx handle structure
 * @param[out] *type pointer to a chip type buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t fm24clxx_get_type(fm24clxx_handle_t *handle, fm24clxx_t *type)
{
    if (handle == NULL)                      /* check handle */
    {
        return 2;                            /* return error */
    }

    *type = (fm24clxx_t)(handle->id);        /* get id */
    
    return 0;                                /* success return 0 */
}

/**
 * @brief     set the chip address pin
 * @param[in] *handle pointer to an fm24clxx handle structure
 * @param[in] addr_pin chip address pin
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 * @note      none
 */
uint8_t fm24clxx_set_addr_pin(fm24clxx_handle_t *handle, fm24clxx_address_t addr_pin)
{
    if (handle == NULL)                       /* check handle */
    {
        return 2;                             /* return error */
    }

    handle->iic_addr = 0xA0;                  /* set iic addr */
    handle->iic_addr |= addr_pin << 1;        /* set iic address */
    
    return 0;                                 /* success return 0 */
}

/**
 * @brief      get the chip address pin
 * @param[in]  *handle pointer to an fm24clxx handle structure
 * @param[out] *addr_pin pointer to a chip address pin
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t fm24clxx_get_addr_pin(fm24clxx_handle_t *handle, fm24clxx_address_t *addr_pin)
{
    if (handle == NULL)                                                         /* check handle */
    {
        return 2;                                                               /* return error */
    }

    *addr_pin = (fm24clxx_address_t)((handle->iic_addr & (~0xA0)) >> 1);        /* get iic address */
    
    return 0;                                                                   /* success return 0 */
}

/**
 * @brief      read bytes from the chip
 * @param[in]  *handle pointer to an fm24clxx handle structure
 * @param[in]  address register address
 * @param[out] *buf pointer to a data buffer
 * @param[in]  len buffer length
 * @return     status code
 *             - 0 success
 *             - 1 read data failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 end address is over the max address
 * @note       none
 */
uint8_t fm24clxx_read(fm24clxx_handle_t *handle, uint16_t address, uint8_t *buf, uint16_t len)
{
    uint8_t page_remain;
    
    if (handle == NULL)                                                                                      /* check handle */
    {
        return 2;                                                                                            /* return error */
    }
    if (handle->inited != 1)                                                                                 /* check handle initialization */
    {
        return 3;                                                                                            /* return error */
    }

    if ((uint16_t)(address + len) > handle->id)                                                              /* check length */
    {
        handle->debug_print("fm24clxx: read out of range.\n");                                               /* read out of range */
       
        return 4;                                                                                            /* return error */
    }
    page_remain = (uint8_t)(8 - address % 8);                                                                /* get page remain */
    if (len <= page_remain)                                                                                  /* page remain */
    {
        page_remain = (uint8_t)len;                                                                          /* set page remain */
    }
    if (handle->id > (uint16_t)FM24CL16B)                                                                    /* choose id to set different address */
    {
        while (1)
        {
            if (handle->iic_read_address16(handle->iic_addr, address, buf, page_remain) != 0)                /* read data */
            {
                handle->debug_print("fm24clxx: read failed.\n");                                             /* read failed */
               
                return 1;                                                                                    /* return error */
            }
            if (page_remain == len)                                                                          /* check break */
            {
                break;                                                                                       /* break loop */
            }
            else
            {
                address += page_remain;                                                                      /* address increase */
                buf += page_remain;                                                                          /* buffer point increase */
                len -= page_remain;                                                                          /* length decrease */
                if (len < 8)                                                                                 /* check length */
                {
                    page_remain = (uint8_t)len;                                                              /* set the reset length */
                }
                else
                {
                    page_remain = 8;                                                                         /* set page */
                }
            }
        }
    }
    else
    {
        while (1)
        {
            if (handle->iic_read((uint8_t)(handle->iic_addr + ((address / 256) << 1)), address % 256, buf,
                page_remain) != 0)                                                                           /* read page */
            {
                handle->debug_print("fm24clxx: read failed.\n");                                             /* read failed */
               
                return 1;                                                                                    /* return error */
            }
            if (page_remain == len)                                                                          /* check break */
            {
                break;                                                                                       /* break loop */
            }
            else
            {
                address += page_remain;                                                                      /* address increase */
                buf += page_remain;                                                                          /* buffer point increase */
                len -= page_remain;                                                                          /* length decrease */
                if (len < 8)                                                                                 /* check length */
                {
                    page_remain = (uint8_t)len;                                                              /* set the reset length */
                }
                else
                {
                    page_remain = 8;                                                                         /* set page */
                }
            }
        }
    }
    
    return 0;                                                                                                /* success return 0 */
}

/**
 * @brief     write bytes to the chip
 * @param[in] *handle pointer to an fm24clxx handle structure
 * @param[in] address register address
 * @param[in] *buf pointer to a data buffer
 * @param[in] len buffer length
 * @return    status code
 *            - 0 success
 *            - 1 write data failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 end address is over the max address
 * @note      none
 */
uint8_t fm24clxx_write(fm24clxx_handle_t *handle, uint16_t address, uint8_t *buf, uint16_t len)
{
    uint8_t page_remain;
    
    if (handle == NULL)                                                                                       /* check handle */
    {
        return 2;                                                                                             /* return error */
    }
    if (handle->inited != 1)                                                                                  /* check handle initialization */
    {
        return 3;                                                                                             /* return error */
    }

    if ((uint16_t)(address + len) > handle->id)                                                               /* check length */
    {
        handle->debug_print("fm24clxx: write out of range.\n");                                               /* write out of range */
       
        return 1;                                                                                             /* return error */
    }
    page_remain = (uint8_t)(8 - address % 8);                                                                 /* set page remain */
    if (len <= page_remain)                                                                                   /* check length */
    {
        page_remain = (uint8_t)len;                                                                           /* set page remain */
    }
    if (handle->id > (uint16_t)FM24CL16B)                                                                     /* check id */
    {
        while (1)
        {
            if (handle->iic_write_address16(handle->iic_addr, address, buf, page_remain) != 0)                /* write data */
            {
                handle->debug_print("fm24clxx: write failed.\n");                                             /* write failed */
               
                return 1;                                                                                     /* return error */
            }
            if (page_remain == len)                                                                           /* check break */
            {
                break;                                                                                        /* break */
            }
            else
            {
                address += page_remain;                                                                       /* address increase */
                buf += page_remain;                                                                           /* buffer point increase */
                len -= page_remain;                                                                           /* length decrease */
                if (len < 8)                                                                                  /* check length */
                {
                    page_remain = (uint8_t)len;                                                               /* set the reset length */
                }
                else
                {
                    page_remain = 8;                                                                          /* set page */
                }
            }
        }
    }        
    else
    {
        while (1)
        {
            if (handle->iic_write((uint8_t)(handle->iic_addr + ((address / 256) << 1)), address % 256, buf,
                page_remain) != 0)                                                                            /* write page */
            {
                handle->debug_print("fm24clxx: write failed.\n");                                             /* write failed */
               
                return 1;                                                                                     /* return error */
            }
            if (page_remain == len)                                                                           /* check break */
            {
                break;                                                                                        /* break */
            }
            else
            {
                address += page_remain;                                                                       /* address increase */
                buf += page_remain;                                                                           /* buffer point increase */
                len -= page_remain;                                                                           /* length decrease */
                if (len < 8)                                                                                  /* check length */
                {
                    page_remain = (uint8_t)len;                                                               /* set the rest length */
                }
                else
                {
                    page_remain = 8;                                                                          /* set page */
                }
            }
        }
    }
    
    return 0;                                                                                                 /* success return 0 */
}


/**
 * @brief      get chip's information
 * @param[out] *info pointer to an fm24clxx info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t fm24clxx_info(fm24clxx_info_t *info)
{
    if (info == NULL)                                               /* check handle */
    {
        return 2;                                                   /* return error */
    }
    
    memset(info, 0, sizeof(fm24clxx_info_t));                       /* initialize fm24clxx info structure */
    strncpy(info->chip_name, CHIP_NAME, 32);                        /* copy chip name */
    strncpy(info->manufacturer_name, MANUFACTURER_NAME, 32);        /* copy manufacturer name */
    strncpy(info->interface, "IIC", 8);                             /* copy interface name */
    info->supply_voltage_min_v = SUPPLY_VOLTAGE_MIN;                /* set minimal supply voltage */
    info->supply_voltage_max_v = SUPPLY_VOLTAGE_MAX;                /* set maximum supply voltage */
    info->max_current_ma = MAX_CURRENT;                             /* set maximum current */
    info->temperature_max = TEMPERATURE_MAX;                        /* set minimal temperature */
    info->temperature_min = TEMPERATURE_MIN;                        /* set maximum temperature */
    info->driver_version = DRIVER_VERSION;                          /* set driver version */
    
    return 0;                                                       /* success return 0 */
}
