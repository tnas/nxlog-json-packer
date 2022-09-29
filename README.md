# JSON Packer
A JSON reader for writing data to a compressed stream on a disk.

The original description is detailed on the project's [Wiki](https://github.com/tnas/json-packer/wiki).

## Table of contents
* [Dependencies](#dependencies)
* [Usage](#usage)
* [References](#references)

## Dependencies
- [cJSON - Ultralightweight JSON parser in ANSI C](https://github.com/DaveGamble/cJSON)
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
