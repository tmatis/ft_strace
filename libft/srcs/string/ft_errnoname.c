#include <errno.h>

#define ERRNO_NAME(errnoname) [errnoname] = #errnoname

static const char *error_names[] = {
	ERRNO_NAME(0),
	ERRNO_NAME(EPERM),
	ERRNO_NAME(ENOENT),
	ERRNO_NAME(ESRCH),
	ERRNO_NAME(EINTR),
	ERRNO_NAME(EIO),
	ERRNO_NAME(ENXIO),
	ERRNO_NAME(E2BIG),
	ERRNO_NAME(ENOEXEC),
	ERRNO_NAME(EBADF),
	ERRNO_NAME(ECHILD),
	ERRNO_NAME(EAGAIN),
	ERRNO_NAME(ENOMEM),
	ERRNO_NAME(EACCES),
	ERRNO_NAME(EFAULT),
	ERRNO_NAME(ENOTBLK),
	ERRNO_NAME(EBUSY),
	ERRNO_NAME(EEXIST),
	ERRNO_NAME(EXDEV),
	ERRNO_NAME(ENODEV),
	ERRNO_NAME(ENOTDIR),
	ERRNO_NAME(EISDIR),
	ERRNO_NAME(EINVAL),
	ERRNO_NAME(ENFILE),
	ERRNO_NAME(EMFILE),
	ERRNO_NAME(ENOTTY),
	ERRNO_NAME(ETXTBSY),
	ERRNO_NAME(EFBIG),
	ERRNO_NAME(ENOSPC),
	ERRNO_NAME(ESPIPE),
	ERRNO_NAME(EROFS),
	ERRNO_NAME(EMLINK),
	ERRNO_NAME(EPIPE),
	ERRNO_NAME(EDOM),
	ERRNO_NAME(ERANGE),
	ERRNO_NAME(EDEADLK),
	ERRNO_NAME(ENAMETOOLONG),
	ERRNO_NAME(ENOLCK),
	ERRNO_NAME(ENOTEMPTY),
	ERRNO_NAME(ELOOP),
	ERRNO_NAME(ENOMSG),
	ERRNO_NAME(EIDRM),
	ERRNO_NAME(ECHRNG),
	ERRNO_NAME(EL2NSYNC),
	ERRNO_NAME(EL3HLT),
	ERRNO_NAME(EL3RST),
	ERRNO_NAME(ELNRNG),
	ERRNO_NAME(EUNATCH),
	ERRNO_NAME(ENOCSI),
	ERRNO_NAME(EL2HLT),
	ERRNO_NAME(EBADE),
	ERRNO_NAME(EBADR),
	ERRNO_NAME(EXFULL),
	ERRNO_NAME(ENOANO),
	ERRNO_NAME(EBADRQC),
	ERRNO_NAME(EBADSLT),
	ERRNO_NAME(EBFONT),
	ERRNO_NAME(ENOSTR),
	ERRNO_NAME(ENODATA),
	ERRNO_NAME(ETIME),
	ERRNO_NAME(ENOSR),
	ERRNO_NAME(ENONET),
	ERRNO_NAME(ENOPKG),
	ERRNO_NAME(EREMOTE),
	ERRNO_NAME(ENOLINK),
	ERRNO_NAME(EADV),
	ERRNO_NAME(ESRMNT),
	ERRNO_NAME(ECOMM),
	ERRNO_NAME(EPROTO),
	ERRNO_NAME(EMULTIHOP),
	ERRNO_NAME(EDOTDOT),
	ERRNO_NAME(EBADMSG),
	ERRNO_NAME(EOVERFLOW),
	ERRNO_NAME(ENOTUNIQ),
	ERRNO_NAME(EBADFD),
	ERRNO_NAME(EREMCHG),
	ERRNO_NAME(ELIBACC),
	ERRNO_NAME(ELIBBAD),
	ERRNO_NAME(ELIBSCN),
	ERRNO_NAME(ELIBMAX),
	ERRNO_NAME(ELIBEXEC),
	ERRNO_NAME(EILSEQ),
	ERRNO_NAME(ENOSYS),
	ERRNO_NAME(ERESTART),
	ERRNO_NAME(ESTRPIPE),
	ERRNO_NAME(EUSERS),
	ERRNO_NAME(ENOTSOCK),
	ERRNO_NAME(EDESTADDRREQ),
	ERRNO_NAME(EMSGSIZE),
	ERRNO_NAME(EPROTOTYPE),
	ERRNO_NAME(ENOPROTOOPT),
	ERRNO_NAME(EPROTONOSUPPORT),
	ERRNO_NAME(ESOCKTNOSUPPORT),
	ERRNO_NAME(EOPNOTSUPP),
	ERRNO_NAME(EPFNOSUPPORT),
	ERRNO_NAME(EAFNOSUPPORT),
	ERRNO_NAME(EADDRINUSE),
	ERRNO_NAME(EADDRNOTAVAIL),
	ERRNO_NAME(ENETDOWN),
	ERRNO_NAME(ENETUNREACH),
	ERRNO_NAME(ENETRESET),
	ERRNO_NAME(ECONNABORTED),
	ERRNO_NAME(ECONNRESET),
	ERRNO_NAME(ENOBUFS),
	ERRNO_NAME(EISCONN),
	ERRNO_NAME(ENOTCONN),
	ERRNO_NAME(ESHUTDOWN),
	ERRNO_NAME(ETOOMANYREFS),
	ERRNO_NAME(ETIMEDOUT),
	ERRNO_NAME(ECONNREFUSED),
	ERRNO_NAME(EHOSTDOWN),
	ERRNO_NAME(EHOSTUNREACH),
	ERRNO_NAME(EALREADY),
	ERRNO_NAME(EINPROGRESS),
	ERRNO_NAME(ESTALE),
	ERRNO_NAME(EUCLEAN),
	ERRNO_NAME(ENOTNAM),
	ERRNO_NAME(ENAVAIL),
	ERRNO_NAME(EISNAM),
	ERRNO_NAME(EREMOTEIO),
	ERRNO_NAME(EDQUOT),
	ERRNO_NAME(ENOMEDIUM),
	ERRNO_NAME(EMEDIUMTYPE),
	ERRNO_NAME(ECANCELED),
	ERRNO_NAME(ENOKEY),
	ERRNO_NAME(EKEYEXPIRED),
	ERRNO_NAME(EKEYREVOKED),
	ERRNO_NAME(EKEYREJECTED),
	ERRNO_NAME(EOWNERDEAD),
	ERRNO_NAME(ENOTRECOVERABLE),
	ERRNO_NAME(ERFKILL),
	ERRNO_NAME(EHWPOISON),
};

/**
 * @brief get the name of an error number
 *
 * @param errnum the error number
 * @return const char* the name of the error number
 */
const char *ft_errnoname(int errnum)
{
	if (errnum < 0 || (unsigned)(errnum) >= sizeof(error_names) / sizeof(error_names[0]))
		return "UNKNOWN";

	return error_names[errnum];
}