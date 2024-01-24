#pragma once

#include "base.h"

#define EFI_SIMPLE_TEXT_INPUT_PROTOCOL_GUID                                            \
    {                                                                                  \
        0x387477c1, 0x69c7, 0x11d2, { 0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b } \
    }

typedef struct
{
    ce_u16 scan_code;
    ce_u16 unicode_char;
} efi_input_key;

typedef struct efi_simple_text_input_protocol
{
    efi_api efi_status (*reset)(struct efi_simple_text_input_protocol *self, bool extendend_verification);
    efi_api efi_status (*read_key_stroke)(struct efi_simple_text_input_protocol *self, efi_input_key *key);
    efi_event wait_for_key;
} efi_simple_text_input_protocol;
