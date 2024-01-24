#pragma once

#include "dpp.h"

#define EFI_DRIVER_BINDING_PROTOCOL_GUID                                               \
    {                                                                                  \
        0x18a031ab, 0xb443, 0x4d1a, { 0xa5, 0xc0, 0x0c, 0x09, 0x26, 0x1e, 0x9f, 0x71 } \
    }

typedef struct efi_driver_binding_protocol
{
    efi_api efi_status (*supported)(struct efi_driver_binding_protocol *, efi_handle controller_handle, efi_device_path_protocol *remaining_path);
    efi_api efi_status (*start)(struct efi_driver_binding_protocol *self, efi_handle controller_handle, efi_device_path_protocol *remaining_path);
    efi_api efi_status (*stop)(struct efi_driver_binding_protocol *self, efi_handle controller_handle, ce_usize num_children, efi_handle *child_handle_buf);
    ce_u32 version;
    efi_handle image_handle;
    efi_handle driver_binding_handle;
} efi_driver_binding_protocol;
