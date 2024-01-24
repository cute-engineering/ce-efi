#pragma once

#include "base.h"

#define EFI_SHELL_PARAMETERS_PROTOCOL_GUID                                             \
    {                                                                                  \
        0x752f3136, 0x4e16, 0x4fdc, { 0xa2, 0x2a, 0xe5, 0xf4, 0x68, 0x12, 0xf4, 0xca } \
    }

typedef struct
{
    ce_u16 **argv;
    ce_usize argc;
    efi_handle std_in;
    efi_handle std_out;
    efi_handle std_err;
} efi_shell_parameters_protocol;
