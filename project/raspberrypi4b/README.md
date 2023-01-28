### 1. Board

#### 1.1 Board Info

Board Name: Raspberry Pi 4B.

IIC Pin: SCL/SDA GPIO3/GPIO2.

### 2. Install

#### 2.1 Dependencies

Install the necessary dependencies.

```shell
sudo apt-get install libgpiod-dev pkg-config cmake -y
```

#### 2.2 Makefile

Build the project.

```shell
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

#### 2.3 CMake

Build the project.

```shell
mkdir build && cd build 
cmake .. 
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

Test the project and this is optional.

```shell
make test
```

Find the compiled library in CMake. 

```cmake
find_package(fm24clxx REQUIRED)
```

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
./fm24clxx -i

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
./fm24clxx -p

fm24clxx: SCL connected to GPIO3(BCM).
fm24clxx: SDA connected to GPIO2(BCM).
```

```shell
./fm24clxx -t read --type=16 --addr=0

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
./fm24clxx -e read --type=16 --addr=0 --reg=1

fm24clxx: read 0x0001 is 0x11.
```

```shell
./fm24clxx -e write --type=16 --addr=0 --reg=1 --data=11

fm24clxx: write 0x0001 is 0x11.
```

```shell
./fm24clxx -h

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

