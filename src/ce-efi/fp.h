#pragma once

#include "bs.h"
#include "rs.h"

#define EFI_FILE_PROTOCOL_REVISION        0x00010000
#define EFI_FILE_PROTOCOL_REVISION2       0x00020000
#define EFI_FILE_PROTOCOL_LATEST_REVISION EFI_FILE_PROTOCOL_REVISION2

#define EFI_FILE_MODE_READ   0x0000000000000001
#define EFI_FILE_MODE_WRITE  0x0000000000000002
#define EFI_FILE_MODE_CREATE 0x8000000000000000

#define EFI_FILE_READ_ONLY  0x0000000000000001
#define EFI_FILE_HIDDEN     0x0000000000000002
#define EFI_FILE_SYSTEM     0x0000000000000004
#define EFI_FILE_RESERVED   0x0000000000000008
#define EFI_FILE_DIRECTORY  0x0000000000000010
#define EFI_FILE_ARCHIVE    0x0000000000000020
#define EFI_FILE_VALID_ATTR 0x0000000000000037

typedef struct
{
    efi_event event;
    efi_status status;
    ce_usize buffer_size;
    void *buffer;
} efi_file_io_token;

#define EFI_FILE_INFO_GUID                                                             \
    {                                                                                  \
        0x09576e92, 0x6d3f, 0x11d2, { 0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b } \
    }

typedef struct
{
    ce_u64 size;
    ce_u64 file_size;
    ce_u64 physical_size;
    efi_time create_time;
    efi_time last_access_time;
    efi_time modification_time;
    ce_u64 attribute;
    ce_u16 file_name[];
} efi_file_info;

#define EFI_FILE_SYSTEM_INFO_GUID                                                      \
    {                                                                                  \
        0x09576e93, 0x6d3f, 0x11d2, { 0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b } \
    }

typedef struct
{
    ce_u64 size;
    bool read_only;
    ce_u64 volume_size;
    ce_u64 free_space;
    ce_u32 block_size;
    ce_u16 *volume_label[];
} efi_file_system_info;

typedef struct efi_file_protocol
{
    ce_u64 revision;
    efi_api efi_status (*open)(struct efi_file_protocol *self, struct efi_file_protocol **new_handle, const ce_u16 *filename, ce_u64 open_mode, ce_u64 attributes);
    efi_api efi_status (*close)(struct efi_file_protocol *self);
    efi_api efi_status (*delete)(struct efi_file_protocol *self);
    efi_api efi_status (*read)(struct efi_file_protocol *self, ce_usize *len, void *buf);
    efi_api efi_status (*write)(struct efi_file_protocol *self, ce_usize *len, const void *buf);
    efi_api efi_status (*get_position)(struct efi_file_protocol *self, ce_u64 *position);
    efi_api efi_status (*set_position)(struct efi_file_protocol *self, ce_u64 position);
    efi_api efi_status (*get_info)(struct efi_file_protocol *self, const efi_guid *info_type, ce_usize *buf_size, void *buf);
    efi_api efi_status (*set_info)(struct efi_file_protocol *self, const efi_guid *info_type, ce_usize buf_size, void *buf);
    efi_api efi_status (*flush)(struct efi_file_protocol *self);
    efi_api efi_status (*open_ex)(struct efi_file_protocol *self, struct efi_file_protocol *new_handle, ce_u16 *filename, ce_u64 open_mode, ce_u64 attributes, efi_file_io_token *token);
    efi_api efi_status (*read_ex)(struct efi_file_protocol *self, efi_file_io_token *token);
    efi_api efi_status (*write_ex)(struct efi_file_protocol *self, efi_file_io_token *token);
    efi_api efi_status (*flush_ex)(struct efi_file_protocol *self, efi_file_io_token *token);
} efi_file_protocol;
