#pragma once

#include "base.h"

#define EFI_BLOCK_IO_PROTOCOL_GUID                                                     \
    {                                                                                  \
        0x964e5b21, 0x6459, 0x11d2, { 0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b } \
    }

#define EFI_BLOCK_IO_PROTOCOL_REVISION2 0x00020001
#define EFI_BLOCK_IO_PROTOCOL_REVISION3 0x00020031

typedef struct efi_block_io_media efi_block_io_media;
typedef struct efi_block_io_protocol efi_block_io_protocol;

struct efi_block_io_protocol
{
    ce_u64 revision;
    efi_block_io_media *media;
    efi_api efi_status (*reset)(efi_block_io_protocol *self, bool ExtendedVerification);
    efi_api efi_status (*read_blocks)(efi_block_io_protocol *self, ce_u32 MediaId, ce_u64 LBA, ce_u64 BufferSize, void *Buffer);
    efi_api efi_status (*write_blocks)(efi_block_io_protocol *self, ce_u32 MediaId, ce_u64 LBA, ce_u64 BufferSize, const void *Buffer);
    efi_api efi_status (*flush_blocks)(efi_block_io_protocol *self);
};

struct efi_block_io_media
{
    // present in rev1
    ce_u32 media_id;
    bool removable_media;
    bool media_present;
    bool logical_partition;
    bool read_only;
    bool write_caching;
    ce_u32 block_size;
    ce_u32 io_align;
    ce_u64 last_block;

    // present in rev2
    ce_u64 lowest_aligned_lba;
    ce_u32 logical_blocks_per_physical_block;

    // present in rev3
    ce_u32 optimal_transfer_length_granularity;
};
