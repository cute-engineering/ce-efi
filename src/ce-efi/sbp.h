#pragma once

#include "base.h"

typedef struct efi_service_binding_protocol
{
    efi_api efi_status (*create_child)(struct efi_service_binding_protocol *self, efi_handle *child_handle);
    efi_api efi_status (*destroy_child)(struct efi_service_binding_protocol *self, efi_handle child_handle);
} efi_service_binding_protocol;
