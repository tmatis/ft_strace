#pragma once

#include <stdint.h>

/**
 * @brief Structure containing the registers of a x86_64 process
 * 
 */
typedef struct
{
    uint64_t r15;
    uint64_t r14;
    uint64_t r13;
    uint64_t r12;
    uint64_t rbp;
    uint64_t rbx;
    uint64_t r11;
    uint64_t r10;
    uint64_t r9;
    uint64_t r8;
    uint64_t rax;
    uint64_t rcx;
    uint64_t rdx;
    uint64_t rsi;
    uint64_t rdi;
    uint64_t orig_rax;
    uint64_t rip;
    uint64_t cs;
    uint64_t eflags;
    uint64_t rsp;
    uint64_t ss;
    uint64_t fs_base;
    uint64_t gs_base;
    uint64_t ds;
    uint64_t es;
    uint64_t fs;
    uint64_t gs;
} user_regs_x86_64_t;

/**
 * @brief Structure containing the registers of a x86 process
 * 
 */
typedef struct
{
    uint32_t ebx;
    uint32_t ecx;
    uint32_t edx;
    uint32_t esi;
    uint32_t edi;
    uint32_t ebp;
    uint32_t eax;
    uint16_t ds;
    uint16_t __ds;
    uint16_t es;
    uint16_t __es;
    uint16_t fs;
    uint16_t __fs;
    uint16_t gs;
    uint16_t __gs;
    uint32_t orig_eax;
    uint32_t eip;
    uint16_t cs;
    uint16_t __cs;
    uint32_t eflags;
    uint32_t esp;
    uint16_t ss;
    uint16_t __ss;
} user_regs_x86_t;


/**
 * @brief Union containing the registers of a x86 or x86_64 process
 * 
 */
typedef union
{
    user_regs_x86_t x86;
    user_regs_x86_64_t x86_64;
} user_regs_t;