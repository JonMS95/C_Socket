#include <stdio.h>
#include <stdlib.h>
#include <string.h>     // memset, strlen
#include "socket_use.h" // IF_ANET, SOCK_STREAM, ...

#include "../Dependency_files/Header_files/GetOptions_api.h"

#define ARGV_PORT_IDX           1
#define ARGV_MAX_CONN_NUM_IDX   2
#define MIN_CONN_NUM            1
#define MAX_CONN_NUM            3
#define MIN_PORT_VALUE          49152
#define MAX_PORT_VALUE          65535

#define MAX_ERROR_MSG_LEN   100

#define ERR_ARG_PARSING_FAILED  -1

#define P_OPT_INDEX 0
#define C_OPT_INDEX 1
#define T_OPT_INDEX 2

#define P_OPT_DETAIL "Port"
#define C_OPT_DETAIL "Maximum number of connections"
#define T_OPT_DETAIL "Just a boolean test option"

option_description opt_desc[] =
{
    {
        .opt_char   = 'p'           ,
        .detail     = P_OPT_DETAIL  ,
        .has_value  = true  ,
        .min_value  = MIN_PORT_VALUE,
        .max_value  = MAX_PORT_VALUE,
    },
    {
        .opt_char   = 'c',
        .detail     = C_OPT_DETAIL,
        .has_value  = true,
        .min_value  = MIN_CONN_NUM,
        .max_value  = MAX_CONN_NUM
    },
    {
        .opt_char   = 't'           ,
        .detail     = T_OPT_DETAIL  ,
        .has_value  = false ,
    }
};

/*
@brief Main function. Program's entry point.
*/
int main(int argc, char** argv)
{
    int opt_desc_size = sizeof(opt_desc) / sizeof(opt_desc[0]);
    char options_short[opt_desc_size * 2 + 1];
    // PreParseOptions(opt_desc, opt_desc_size, options_short);

    // int parse_arguments = ParseArguments(argc, argv, opt_desc, opt_desc_size, options_short);
    int parse_arguments = GetOptions(argc, argv, opt_desc, opt_desc_size, options_short);
    if(parse_arguments < 0)
    {
        printf("Arguments parsing failed!\r\n");
        return ERR_ARG_PARSING_FAILED;
    }
    
    int server_port = opt_desc[P_OPT_INDEX].assigned_value;
    int max_conn_num = opt_desc[C_OPT_INDEX].assigned_value;
    bool test_bool_option = opt_desc[T_OPT_INDEX].assigned_value;

    int socket_desc = CreateSocketDescriptor(AF_INET, SOCK_STREAM, IPPROTO_IP);

    int socket_options = SocketOptions(socket_desc, 1, 1, 1, 5, 5);

    struct sockaddr_in server = PrepareForBinding(AF_INET, INADDR_ANY, server_port);

    int bind_socket = BindSocket(socket_desc, server);

    int listen = SocketListen(socket_desc, max_conn_num);

    int new_socket = SocketAccept(socket_desc);

    int read = SocketRead(new_socket);

    int close = CloseSocket(new_socket);

    return 0;
}
