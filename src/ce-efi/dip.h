#pragma once

#include "bs.h"
#include "rs.h"

#define EFI_DISK_IO_PROTOCOL_GUID                                                      \
    {                                                                                  \
        0xCE345171, 0xBA0B, 0x11d2, { 0x8e, 0x4F, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b } \
    }

#define EFI_DISK_IO_PROTOCOL_REVISION 0x00010000

typedef struct efi_disk_io_protocol efi_disk_io_protocol;

struct efi_disk_io_protocol
{
    ce_u64 revision;
    efi_api efi_status (*read_disk)(efi_disk_io_protocol *self, ce_u32 media_id, ce_u64 offset, ce_u64 buffer_size, void *buffer);
    efi_api efi_status (*write_disk)(efi_disk_io_protocol *self, ce_u32 media_id, ce_u64 offset, ce_u64 buffer_size, const void *buffer);
};
