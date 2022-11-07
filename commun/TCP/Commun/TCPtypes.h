#pragma once

typedef enum TCPStatus_t {
    
    TCP_ERROR_OPEN_SOCK = -1,
    TCP_ERROR_WRITE = -2,
    TCP_ERROR_READ = -3,
    TCP_ERROR_CLOSE = -4,
    TCP_ERROR_CONNECT = -5,
    TCP_ERROR_ACCEPT = -6,

    TCP_OK = 0,
}TCPStatus_t;