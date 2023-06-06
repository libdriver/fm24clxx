### 1. Chip

#### 1.1 Chip Info

Chip Name: STM32F407ZGT6.

Extern Oscillator: 8MHz.

UART Pin: TX/RX PA9/PA10.

IIC Pin: SCL/SDA PB8/PB9.

### 2. Development and Debugging

#### 2.1 Integrated Development Environment

LibDriver provides both Keil and IAR integrated development environment projects.

MDK is the Keil ARM project and your Keil version must be 5 or higher.Keil ARM project needs STMicroelectronics STM32F4 Series Device Family Pack and you can download from https://www.keil.com/dd2/stmicroelectronics/stm32f407zgtx.

EW is the IAR ARM project and your IAR version must be 9 or higher.

#### 2.2 Serial Port Parameter

Baud Rate: 115200.

Data Bits : 8.

Stop Bits: 1.

Parity: None.

Flow Control: None.

#### 2.3 Serial Port Assistant

We use '\n' to wrap lines.If your serial port assistant displays exceptions (e.g. the displayed content does not divide lines), please modify the configuration of your serial port assistant or replace one that supports '\n' parsing.

### 3. FM24CLXX

#### 3.1 Command Instruction

1. Show fm24clxx chip and driver information.

   ```shell
   fm24clxx (-i | --information)
   ```

2. Show fm24clxx help.

   ```shell
   fm24clxx (-h | --help)
   ```

3. Show fm24clxx pin connections of the current board.

   ```shell
   fm24clxx (-p | --port)
   ```

4. Run fm24clxx read test.

   ```shell
   fm24clxx (-t read | --test=read) [--type=<4 | 16 | 64>] [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>]
   ```

5. Run fm24clxx read function, address is the read register address and it is hexadecimal.

   ```shell
   fm24clxx (-e read | --example=read) [--type=<4 | 16 | 64>] [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>] [--reg=<address>]
   ```

6. Run fm24clxx write function, address is the write register address and it is hexadecimal, data is the set data and it is hexadecimal.

   ```shell
   fm24clxx (-e write | --example=write) [--type=<4 | 16 | 64>] [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>] [--reg=<address>] [--data=<hex>]
   ```

#### 3.2 Command Example

```shell
fm24clxx -i

fm24clxx: chip is Cypress FM24CLXX.
fm24clxx: manufacturer is Cypress.
fm24clxx: interface is IIC.
fm24clxx: driver version is 1.0.
fm24clxx: min supply voltage is 2.7V.
fm24clxx: max supply voltage is 3.7V.
fm24clxx: max current is 0.10mA.
fm24clxx: max temperature is 85.0C.
fm24clxx: min temperature is -40.0C.
```

```shell
fm24clxx -p

fm24clxx: SCL connected to GPIOB PIN8.
fm24clxx: SDA connected to GPIOB PIN9.
```

```shell
fm24clxx -t read --type=16 --addr=0

fm24clxx: chip is Cypress FM24CLXX.
fm24clxx: manufacturer is Cypress.
fm24clxx: interface is IIC.
fm24clxx: driver version is 1.0.
fm24clxx: min supply voltage is 2.7V.
fm24clxx: max supply voltage is 3.7V.
fm24clxx: max current is 0.10mA.
fm24clxx: max temperature is 85.0C.
fm24clxx: min temperature is -40.0C.
fm24clxx: start read test.
fm24clxx: 0x0000 read write test passed.
fm24clxx: 0x0100 read write test passed.
fm24clxx: 0x0200 read write test passed.
fm24clxx: 0x0300 read write test passed.
fm24clxx: 0x0400 read write test passed.
fm24clxx: 0x0500 read write test passed.
fm24clxx: 0x0600 read write test passed.
fm24clxx: 0x0700 read write test passed.
fm24clxx: finish read test.
```

```shell
fm24clxx -e read --type=16 --addr=0 --reg=1

fm24clxx: read 0x0001 is 0x11.
```

```shell
fm24clxx -e write --type=16 --addr=0 --reg=1 --data=11

fm24clxx: write 0x0001 is 0x11.
```

```shell
fm24clxx -h

Usage:
  fm24clxx (-i | --information)
  fm24clxx (-h | --help)
  fm24clxx (-p | --port)
  fm24clxx (-t read | --test=read) [--type=<4 | 16 | 64>] [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>]
  fm24clxx (-e read | --example=read) [--type=<4 | 16 | 64>] [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>]
           [--reg=<address>]
  fm24clxx (-e write | --example=write) [--type=<4 | 16 | 64>] [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>]
           [--reg=<address>] [--data=<hex>]

Options:
     --addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>
                                  Set the chip address pin.([default: 0])
     --data=<hex>                 Set the write data and it is hexadecimal.([default: random])
  -e <read | write>, --example=<read | write>
                                  Run the driver example.
  -h, --help                      Show the help.
  -i, --information               Show the chip information.
  -p, --port                      Display the pin connections of the current board.
      --reg=<address>             Set the register address and it is hexadecimal.([default: 0])
  -t <read>, --test=<read>        Run the driver test.
      --type=<4 | 16 | 64>        Set the chip type.([default: 16])
```

