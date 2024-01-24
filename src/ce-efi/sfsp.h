#pragma once

#include "fp.h"

#define EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID                                            \
    {                                                                                   \
        0x0964e5b22, 0x6459, 0x11d2, { 0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b } \
    }

#define EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_REVISION 0x00010000

typedef struct efi_simple_file_system_protocol
{
    ce_u64 revision;
    efi_api efi_status (*open_volume)(struct efi_simple_file_system_protocol *self, efi_file_protocol **root);
} efi_simple_file_system_protocol;
