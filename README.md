# C_Server_Socket 🔌
### A server socket written in C language
The aim of this project is to build and learn about internet sockets, so it has been created for both educational and practical purposes.


## Table of contents 🗂️
* [**Introduction**](#introduction)
* [**Features**](#features)
* [**Prerequisites**](#prerequisites)
* [**Installation instructions**](#installation-instructions)
* [**Usage**](#usage)
* [**To do**](#to-do)


## Introduction <a id="introduction"></a> 📑
This library was started as a way for me to have a more practical approach to how TCP sockets work. I felt a bit scared in the beginning since I was overwhelmed by the many concepts I had to get a deeper understanding of.
However, as I found out the vast amount of practical applications it may have in real life, I started regarding it as a way more amusing and enriching activity for my professional career.

Building this project has involved a deep understanding of:
* C/C++ programming
* Bash scripting
* TCP/IP protocol stack
* Dependency management
* Parallel-running processes
* Tests
* Linux OS operation

and the list goes on and on.
Despite existing some aspects that need to be improved, it's a project I feel quite proud of. More of those (such as UDP support) will be coming soon.
By now, it has been designed for it to be run on Linux distros (such as Ubuntu). The resulting library is a *.so* file alongside a C language header (*.h*) file.


## Features <a id="features"></a> 🌟
The resulting library comes with many options that can be applied to it, such as setting timeouts, or adding a custom interaction function,
it's to say, an arbitrary function to describe how the socket should interact once the client has connected to it.

When it comes to security, TLS can be set, as well as the paths to the private key and server certificate, which should be created by the user itself
(these files are not provided with the current project for privacy concerns).

In order to get some knowledge about how to use the library alongside its options, go to [Usage](#usage).


## Prerequisites <a id="prerequisites"></a> 🧱
By now, the application has only been tested in POSIX-compliant Linux distros. In these, many of the dependencies dependencies below may already come installed in the SO.
In the following list, the minimum versions required (if any) by the library are listed.

| Dependency                   | Minimum version |
| :--------------------------- | :-------------: |
| [gcc][gcc-link]              | 11.4            |
| [Bash][bash-link]            | 4.4             |
| [Make][make-link]            | 4.1             |
| [Git][git-link]              | 2.34.1          |
| [Xmlstarlet][xmlstarlet-link]| 1.6.1           |
| [OpenSSL][openssl-link]      | 3.0.2           |

[gcc-link]:        https://gcc.gnu.org/
[bash-link]:       https://www.gnu.org/software/bash/
[make-link]:       https://www.gnu.org/software/make/
[git-link]:        https://git-scm.com/
[xmlstarlet-link]: https://xmlstar.sourceforge.net/
[openssl-link]:    https://www.openssl.org/

Except for Make, Bash and OpenSSL, the latest version of each of the remaining dependencies will be installed automatically if they have not been found beforehand. 

On top of the ones listed above, there are some *JMS* dependencies (libraries that were also made by myself) that are required for both the library and the test executable to be built,
(although these are managed by the library itself, so no need to download them manually):
* [C_Common_shell_files](https://github.com/JonMS95/C_Common_shell_files)
* [C_Severity_Log](https://github.com/JonMS95/C_Severity_Log)
* [C_Arg_Parse](https://github.com/JonMS95/C_Arg_Parse)
* [C_Client_Socket](https://github.com/JonMS95/C_Client_Socket)


## Installation instructions <a id="installation-instructions"></a> 📓
### Download and compile
In order to download the repo, just clone it from GitHub to your choice path by using the [link](https://github.com/JonMS95/C_Server_Socket) to the project.

```bash
cd /path/to/repos
git clone https://github.com/JonMS95/C_Server_Socket
```

Then navigate to the directory in which the repo has been downloaded, and set execution permissions to every file just in case they have not been sent beforehand.

```bash
cd /path/to/repos/C_Server_Socket

find . -type f -exec chmod u+x {} +
```

For the library to be built (i.e., clean, download dependencies and compile), just type the following on your command:

```bash
make
```

The result of the line above will be a new API directory (which will match the used version). Within it, a *.h* and a *.so* file will be found.
- **/path/to/repos/C_Server_Socket/API**
  - **vM_m**
    - **Dynamic_libraries**
      - **_libServerSocket.so.M.m_**
    - **Header_files**
      - **_ServerSocket_api.h_**

Where **_M_** and **_m_** stand for the major and minor version numbers.
**_ServerSocket_api.h_** could also be found in **_/path/to/repos/C_Server_Socket/Source_files/ServerSocket_api.h_** although it may differ depending on the version.

### Compile and run test
For the test executable file to be compiled and executed, use:

```bash
make test
```

Again, the one below is the path to the generated executable file:
- **/path/to/repos/C_Server_Socket/Tests**
  - **Executable_files**
      - **_main_**
  - Source_files
  - Dependency_files


## Usage <a id="usage"></a> 🖱️
The following is the main server socket function prototype as found in the **_header API file_** (_/path/to/repos/C_Server_Socket/API/vM_m/Header_files/ServerSocket_api.h_) or in the [repo file](https://github.com/JonMS95/C_Server_Socket/blob/main/Source_files/ServerSocket_api.h).

```c
C_SERVER_SOCKET_API int ServerSocketRun(int             server_port                                     ,
                                        int             max_conn_num                                    ,
                                        bool            concurrent                                      ,
                                        bool            non_blocking                                    ,
                                        bool            reuse_address                                   ,
                                        bool            reuse_port                                      ,
                                        unsigned long   rx_timeout_s                                    ,
                                        unsigned long   rx_timeout_us                                   ,
                                        unsigned long   tx_timeout_s                                    ,
                                        unsigned long   tx_timeout_us                                   ,
                                        bool            secure                                          ,
                                        const char*     cert_path                                       ,
                                        const char*     pkey_path                                       ,
                                        int             (*CustomSocketStateInteract)(int client_socket) );
```

The amount of input parameters can be a bit astonishing, but please keep in mind it has been designed this way to
provide maximum optionality so each developer can customize its usage as much as possible. Here is a list of the meaning of each input parameter:
* **server_port**: specifies the port the server is meant to listen to
* **max_conn_num**: maximum number of connections /clients
* **concurrent**: specifies whether or not could those connections be parallel
* **non_blocking**: tells whether or not is the socket non-blocking (not recommended)
* **reuse_address**: reuse address, does not hold the address after the socket is closed (strongly recommended)
* **reuse_port**: reuse port, does not hold the port after the socket is closed (strongly recommended)
* **rx_timeout_s**: receive timeout in seconds.
* **rx_timeout_us**: receive timeout in microseconds.
* **tx_timeout_s**: send timeout in seconds.
* **tx_timeout_us**: send timeout in microseconds.
* **secure**: enable secure communication (TLS).
* **cert_path**: path to the server certificate.
* **key_path**: path to the server private key.
* **CustomSocketStateInteract**: custom function to interact with the client once a connection has been established.

In exchange, the function returns:
* **0** if everything went OK, or exit sending **failure signal** if SIGINT signal handler could not be properly set

For reference, a proper API usage example has been provided on the [test source file](https://github.com/JonMS95/C_Server_Socket/blob/main/Tests/Source_files/main.c).
As this one uses [**C_Arg_Parse library**](https://github.com/JonMS95/C_Arg_Parse), input parameters can be provided by using command-line interface.
An example of CLI usage is provided in the [**Shell_files/test.sh**](https://github.com/JonMS95/C_Server_Socket/blob/main/Shell_files/test.sh) file.


## To do <a id="to-do"></a> ☑️
- [ ] Add UDP support
- [ ] Use threads instead of parallel processes (more handleable)
- [ ] Add a contributing guide file.
- [ ] Add a license file.
