### 1. chip

#### 1.1 chip info

chip name : STM32F407ZGT6.

extern oscillator : 8MHz.

uart pin: TX/RX PA9/PA10.

iic pin: SCL/SDA PB8/PB9.

### 2. shell

#### 2.1 shell parameter

baud rate: 115200

data bits : 8

stop bits: 1

parity: none

flow control: none

### 3. fm24clxx

#### 3.1 command Instruction

​          fm24clxx is a basic command which can test all fm24clxx driver function:

​           -i          show fm24clxx chip and driver information.

​           -h         show fm24clxx help.

​           -p         show fm24clxx pin connections of the current board.

​           -t  read -type (4 | 16 | 64) -a (0 | 1| 2 | 3 | 4 | 5 | 6 | 7)         run fm24clxx read test.

​           -c (read -type (4 | 16 | 64)  -a (0 | 1| 2 | 3 | 4 | 5 | 6 | 7)  <registeraddr>| write  -type (4 | 16 | 64) -a (0 | 1| 2 | 3 | 4 | 5 | 6 | 7)  <registeraddr> <data>)

​           -c read -type (4 | 16 | 64) -a (0 | 1| 2 | 3 | 4 | 5 | 6 | 7)  <registeraddr>        run fm24clxx read function.

​           -c write -type (4 | 16 | 64) -a (0 | 1| 2 | 3 | 4 | 5 | 6 | 7)  <registeraddr> <data>        run fm24clxx write function.data is hexadecimal.

#### 3.2 command example

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
fm24clxx -t read -type 16 -a 0

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
fm24clxx -c read -type 16 -a 0 0001

fm24clxx: read 0x0001 is 0x11.
```

```shell
fm24clxx -c write -type 16 -a 0 0001 11 

fm24clxx: write 0x0001 is 0x11.
```

```shell
fm24clxx -h

fm24clxx -i
	show fm24clxx chip and driver information.
fm24clxx -h
	show fm24clxx help.
fm24clxx -p
	show fm24clxx pin connections of the current board.
fm24clxx -t read -type (4 | 16 | 64) -a (0 | 1| 2 | 3 | 4 | 5 | 6 | 7)
	run fm24clxx read test.
fm24clxx -c read -type (4 | 16 | 64) -a (0 | 1| 2 | 3 | 4 | 5 | 6 | 7) <registeraddr>
	run fm24clxx read function.
fm24clxx -c write -type (4 | 16 | 64) -a (0 | 1| 2 | 3 | 4 | 5 | 6 | 7) <registeraddr> <data>
	run fm24clxx write function.data is hexadecimal.
```

