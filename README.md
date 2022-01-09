[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md)

<div align=center>
<img src="/doc/image/logo.png"/>
</div>

## LibDriver FM24CLXX

[![API](https://img.shields.io/badge/api-reference-blue)](https://www.libdriver.com/docs/fm24clxx/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

FM24CLXX is a ferroelectric memory chip of IIC bus introduced by Cypress. Unlike EEPROM, ferroelectric storage chip supports bus speed writing data without waiting. Ferroelectric has lower write power than EEPROM. Ferroelectric supports 10^14 read and write times, and the data storage time is 151 years.

LibDriver FM24CLXX is the full function driver of FM24CLXX launched by LibDriver. FM24CLXX provides write and read functions.

### Table of Contents

  - [Instruction](#Instruction)
  - [Install](#Install)
  - [Usage](#Usage)
    - [example basic](#example-basic)
  - [Document](#Document)
  - [Contributing](#Contributing)
  - [License](#License)
  - [Contact Us](#Contact-Us)

### Instruction

/src includes LibDriver FM24CLXX source files.

/interface includes LibDriver FM24CLXX IIC platform independent template。

/test includes LibDriver FM24CLXX driver test code and this code can test the chip necessary function simply。

/example includes LibDriver FM24CLXX sample code.

/doc includes LibDriver FM24CLXX offline document.

/datasheet includes FM24CLXX datasheet。

/project includes the common Linux and MCU development board sample code. All projects use the shell script to debug the driver and the detail instruction can be found in each project's README.md.

### Install

Reference /interface IIC platform independent template and finish your platform IIC driver.

Add /src, /interface and /example to your project.

### Usage

#### example basic

```C
uint8_t res;
uint8_t data;

res = fm24clxx_basic_init(FM24CL16B, FM24CLXX_ADDRESS_A000);
if (res)
{
    return 1;
}

...

res = fm24clxx_basic_read(0x00, (uint8_t *)&data, 1);
if (res)
{
    fm24clxx_basic_deinit();

    return 1;
}
else
{
    fm24clxx_interface_debug_print("fm24clxx: 0x%02X.\n", data);
}

...

res = fm24clxx_basic_write(0x00, (uint8_t *)&data, 1);
if (res)
{
    fm24clxx_basic_deinit();

    return 1;
}
else
{
    fm24clxx_interface_debug_print("fm24clxx: 0x%02X.\n", data);
}

...

fm24clxx_basic_deinit();

return 0;
```

### Document

Online documents: https://www.libdriver.com/docs/fm24clxx/index.html

Offline documents: /doc/html/index.html

### Contributing

Please sent an e-mail to lishifenging@outlook.com

### License

Copyright (c) 2015 - present LibDriver All rights reserved



The MIT License (MIT) 



Permission is hereby granted, free of charge, to any person obtaining a copy

of this software and associated documentation files (the "Software"), to deal

in the Software without restriction, including without limitation the rights

to use, copy, modify, merge, publish, distribute, sublicense, and/or sell

copies of the Software, and to permit persons to whom the Software is

furnished to do so, subject to the following conditions: 



The above copyright notice and this permission notice shall be included in all

copies or substantial portions of the Software. 



THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR

IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,

FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE

AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER

LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,

OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE

SOFTWARE. 

### Contact Us

Please sent an e-mail to lishifenging@outlook.com