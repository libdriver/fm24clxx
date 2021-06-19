<div align=center>
<img src="/doc/image/logo.png"/>
</div>

## LibDriver FM24CLXX

[English](/README.md) | [ 简体中文](/README_CH.md)

FM24CLXX是赛普拉斯公司推出的IIC总线的铁电存储芯片。不像EEPROM，铁电存储芯片支持总线速度写入数据，无需等待，铁电拥有比EEPROM更低的写入功耗，铁电支持10^14读写次数，数据保存时间足有151年。

LibDriver FM24CLXX是LibDriver推出的FM24CLXX的全功能驱动，该驱动提供写入和读取功能。

### 目录

  - [说明](#说明)
  - [安装](#安装)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [文档](#文档)
  - [贡献](#贡献)
  - [版权](#版权)
  - [联系我们](#联系我们)

### 说明

/src目录包含了LibDriver FM24CLXX的源文件。

/interface目录包含了LibDriver FM24CLXX与平台无关的IIC总线模板。

/test目录包含了LibDriver FM24CLXX驱动测试程序，该程序可以简单的测试芯片必要功能。

/example目录包含了LibDriver FM24CLXX编程范例。

/doc目录包含了LibDriver FM24CLXX离线文档。

/datasheet目录包含了FM24CLXX数据手册。

/project目录包含了常用Linux与单片机开发板的工程样例。所有工程均采用shell脚本作为调试方法，详细内容可参考每个工程里面的README.md。

### 安装

参考/interface目录下与平台无关的IIC总线模板，完成指定平台的IIC总线驱动。

将/src目录，/interface目录和/example目录加入工程。

### 使用

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

### 文档

在线文档: https://www.libdriver.com/docs/fm24clxx/index.html

离线文档: /doc/html/index.html

### 贡献

请联系lishifenging@outlook.com

### 版权

版权(C) LibDriver 2015-2021 版权所有

MIT 许可证（MIT）

特此免费授予任何获得本软件副本和相关文档文件（下称“软件”）的人不受限制地处置该软件的权利，包括不受限制地使用、复制、修改、合并、发布、分发、转授许可和/或出售该软件副本，以及再授权被配发了本软件的人如上的权利，须在下列条件下：

上述版权声明和本许可声明应包含在该软件的所有副本或实质成分中。

本软件是“如此”提供的，没有任何形式的明示或暗示的保证，包括但不限于对适销性、特定用途的适用性和不侵权的保证。在任何情况下，作者或版权持有人都不对任何索赔、损害或其他责任负责，无论这些追责来自合同、侵权或其它行为中，还是产生于、源于或有关于本软件以及本软件的使用或其它处置。

### 联系我们

请联系lishifenging@outlook.com