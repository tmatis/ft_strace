#include <registers.h>

/**
 * @brief Get registers type from size
 * 
 * @param size the registers size
 * @return register_type_t the registers type
 */
register_type_t registers_get_type(size_t size)
{
    if (size == sizeof(struct user_regs_struct))
        return X86_64;
    return X86_32;
}