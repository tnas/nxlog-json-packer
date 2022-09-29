# JSON Packer
A JSON reader for writing data to a compressed stream on a disk.

The original description is detailed on the project's [Wiki](https://github.com/tnas/json-packer/wiki).

## Table of contents
* [Brief](#brief)
* [Dependencies](#dependencies)
* [Usage](#usage)
    * [Compiling](#compiling)
    * [Testing](#testing)
    * [Running](#running)
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

the cJSON library has been added to the project in the folder `cjson`

- [Apache Portable Runtime - 1.7.0](https://apr.apache.org/)

Even though Apache Portable Runtime Utility 1.6.1 has not been
used in this implementation, the CMake build automation software
expects such a dependency.

## Usage
The program expects a standard JSON file with no  complex or nested elements.
There is no error handling if this condition is not met, i. e.,
`Segmentation fault` errors can be triggered when the program doesn't run under
such conditions.

### Compiling
To compile the program, run the command

```Shell
cmake --build .
```

### Testing
After compiling the program, the test suite can be invoke through the command

```Shell
make test
```

### Running
The program can run in two modes.

The first one is by do not passing any command argument as follow

```Shell
./json-packer
```

In this mode, it will parse all files in the `./json-input` folder. The folders `txt-output`
and `tlv-output` will be used to store the program's outcomes.
The suffixes `_txt` and `_tlv` are appended to the names of the created files, respectively.


In the second mode, the program expects a specific JSON file to be passed as parameter.
The directory from which the program was run is used to store the program's outcomes.
Two files are created: `output.txt` and `output.tlv`.

The command line parameter `-f` must be used to inform the file as follow

```Shell
./json-packer -f input01.json
```

**Remark:** The program only recognizes the `-f` command argument. If any other
arguments are passed to the program, they will be disregarded.

## References
- [X.690](https://en.wikipedia.org/wiki/X.690)
- [ASN.1 encoding rules](https://www.itu.int/rec/T-REC-X.690-202102-I/en)
- [Abstract Syntax Notation One](https://www.openscdp.org/scripts/tutorial/emv/TLV.html)
- [libapr - Programming Tutorial](http://dev.ariel-networks.com/apr/apr-tutorial/html/apr-tutorial.html#toc19)
- [CMake Tutorial](https://cmake.org/cmake/help/latest/guide/tutorial/index.html)
