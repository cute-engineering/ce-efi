#pragma once

#include "dpp.h"
#include "st.h"

#define EFI_LOADED_IMAGE_PROTOCOL_GUID                                                 \
    {                                                                                  \
        0x5b1b31a1, 0x9562, 0x11d2, { 0x8e, 0x3f, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b } \
    }

#define EFI_LOADED_IMAGE_PROTOCOL_REVISION 0x1000

typedef struct
{
    ce_u32 revision;
    efi_handle parent_handle;
    efi_system_table *system_table;
    efi_handle device_handle;
    efi_device_path_protocol *file_path;
    void *reserved;
    ce_u32 load_options_size;
    void *load_options;
    void *image_base;
    ce_u64 image_size;
    efi_memory_type image_code_type;
    efi_memory_type image_data_type;
    efi_api efi_status (*unload)(efi_handle img);
} efi_loaded_image_protocol;
