#pragma once

#include "dpp.h"

#define EFI_DEVICE_PATH_TO_TEXT_PROTOCOL_GUID                                          \
    {                                                                                  \
        0x8b843e20, 0x8132, 0x4852, { 0x90, 0xcc, 0x55, 0x1a, 0x4e, 0x4a, 0x7f, 0x1c } \
    }

typedef struct efi_device_path_to_text_protocol
{
    efi_api ce_u16 *(*convert_device_node_to_text)(const efi_device_path_protocol *dev_node, bool display_only, bool allow_shortcuts);
    efi_api ce_u16 *(*convert_device_path_to_text)(const efi_device_path_protocol *dev_path, bool display_only, bool allow_shortcuts);
} efi_device_path_to_text_protocol;
