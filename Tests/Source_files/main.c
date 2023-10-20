#include <stdlib.h>
#include <string.h>     // memset, strlen

#include "ServerSocket_api.h"
#include "GetOptions_api.h"
#include "SeverityLog_api.h"

/********** Private constants **********/
/***************************************/

/************ Port settings ************/

#define PORT_OPT_CHAR       'p'
#define PORT_OPT_LONG       "Port"
#define PORT_OPT_DETAIL     "Range of acceptable port numbers"
#define PORT_MIN_VALUE      49152
#define PORT_MAX_VALUE      65535
#define PORT_DEFAULT_VALUE  50000

/********* Connection settings *********/

#define CLIENTS_OPT_CHAR        'c'
#define CLIENTS_OPT_LONG        "Clients"
#define CLIENTS_OPT_DETAIL      "Maximum number of clients (sequential)"
#define CLIENTS_MIN_VALUE       1
#define CLIENTS_MAX_VALUE       3
#define CLIENTS_DEFAULT_VALUE   1

/***************************************/

/*
@brief Main function. Program's entry point.
*/
int main(int argc, char** argv)
{
    SetSeverityLogMask(SVRTY_LOG_MASK_ALL);

    int server_port;
    int max_clients_num;

    SetOptionDefinitionInt( PORT_OPT_CHAR       ,
                            PORT_OPT_LONG       ,
                            PORT_OPT_DETAIL     ,
                            PORT_MIN_VALUE      ,
                            PORT_MAX_VALUE      ,
                            PORT_DEFAULT_VALUE  ,
                            &server_port        );

    SetOptionDefinitionInt( CLIENTS_OPT_CHAR        ,
                            CLIENTS_OPT_LONG        ,
                            CLIENTS_OPT_DETAIL      ,
                            CLIENTS_MIN_VALUE       ,
                            CLIENTS_MAX_VALUE       ,
                            CLIENTS_DEFAULT_VALUE   ,
                            &max_clients_num        );

    int parse_arguments = ParseOptions(argc, argv);
    if(parse_arguments < 0)
    {
        LOG_ERR("Arguments parsing failed!");
        return parse_arguments;
    }

    LOG_INF("Arguments successfully parsed!");

    ServerSocketRun(server_port, max_clients_num);

    return 0;
}
