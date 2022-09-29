# JSON Packer
A JSON reader for writing data to a compressed stream on a disk.

The original description is detailed on the project's [Wiki](https://github.com/tnas/json-packer/wiki).

## Table of contents
* [Brief](#brief)
* [Dependencies](#dependencies)
* [Usage](#usage)
* [References](#references)

## Brief
A TLV object (or record) has been implemented according to the next schema

![](https://github.com/tnas/json-packer/blob/main/docs/tlv.png)

As described in the original specification, complex and nested types are not covered
by this implementation. A very important feature involves the **JSON boolean type**.
In this program, this type is allocated in 3 bytes: **1 for type (tag), 1 for length and
1 for the boolean value**, i. e., 0xFF (true) and 0x00 (false). For example, the value TRUE
is encoded as

 ![](https://github.com/tnas/json-packer/blob/main/docs/tlv-boolean.png)

 Serial TLV Objects were connected as follow:

 ![](https://github.com/tnas/json-packer/blob/main/docs/serial-tlv.png)

## Dependencies
The program depends on two external libraries:

- [cJSON - Ultralightweight JSON parser in ANSI C](https://github.com/DaveGamble/cJSON)

As explained by the author

> Because the entire library is only one C file and one header file,
> you can just copy cJSON.h and cJSON.c to your projects source and start using it.

the cJSON library has been added to the project into the folder `cjson`

- [Apache Portable Runtime - 1.7.0](https://apr.apache.org/)

## Usage
```Shell
cmake --build .
./json-packer
```

## References
- [X.690](https://en.wikipedia.org/wiki/X.690)
- [ASN.1 encoding rules](https://www.itu.int/rec/T-REC-X.690-202102-I/en)
- [Abstract Syntax Notation One](https://www.openscdp.org/scripts/tutorial/emv/TLV.html)
- [libapr - Programming Tutorial](http://dev.ariel-networks.com/apr/apr-tutorial/html/apr-tutorial.html#toc19)
- [CMake Tutorial](https://cmake.org/cmake/help/latest/guide/tutorial/index.html)
