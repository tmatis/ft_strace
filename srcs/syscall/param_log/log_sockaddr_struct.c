#define _GNU_SOURCE

#include "param_log.h"
#include <ft_printf.h>
#include <ft_strace_utils.h>
#include <macros.h>
#include <sys/uio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/**
 * @brief Log a sockaddr struct
 * 
 * @param value the ptr to sockaddr
 * @param context the context of the syscall
 * @return int the number of bytes written
 */
int log_SOCKADDR_STRUCT(uint64_t value, syscall_log_param_t *context)
{
    if (value == 0)
        return ft_dprintf(STDERR_FILENO, "NULL");
    if (context->after_syscall)
    {
        int64_t ret = (int64_t)registers_get_return(context->regs, context->type);
        if (ret < 0)
            return ft_dprintf(STDERR_FILENO, "%p", (void *)value);
    }
    struct sockaddr sockaddr;
    struct iovec local = {
        .iov_base = &sockaddr,
        .iov_len = sizeof(sockaddr),
    };
    struct iovec remote = {
        .iov_base = (void *)value,
        .iov_len = sizeof(sockaddr),
    };
    if (process_vm_readv(context->pid, &local, 1, &remote, 1, 0) < 0)
    {
        log_error("log_SOCKADDR_STRUCT", "process_vm_readv failed", true);
        return 0;
    }
    if (sockaddr.sa_family == AF_INET)
    {
        struct sockaddr_in *sockaddr_in = (struct sockaddr_in *)&sockaddr;
        return ft_dprintf(STDERR_FILENO, "{sa_family=AF_INET, sin_port=htons(%d), sin_addr=inet_addr(\"%s\")}",
                          ntohs(sockaddr_in->sin_port), inet_ntoa(sockaddr_in->sin_addr));
    }
    else if (sockaddr.sa_family == AF_INET6)
    {
        struct sockaddr_in6 *sockaddr_in6 = (struct sockaddr_in6 *)&sockaddr;
        char addr_str[INET6_ADDRSTRLEN];
        inet_ntop(AF_INET6, &sockaddr_in6->sin6_addr, addr_str, INET6_ADDRSTRLEN);
        return ft_dprintf(STDERR_FILENO, "{sa_family=AF_INET6, sin6_port=htons(%d), sin6_addr=inet_addr(\"%s\")}",
                          ntohs(sockaddr_in6->sin6_port), addr_str);
    }
    else
        return ft_dprintf(STDERR_FILENO, "{sa_family=%d}", sockaddr.sa_family);
}