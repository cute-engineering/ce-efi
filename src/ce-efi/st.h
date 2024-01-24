#pragma once

#include "bs.h"
#include "rs.h"
#include "stip.h"
#include "stop.h"

#define EFI_SYSTEM_TABLE_SIGNATURE     0x5453595320494249
#define EFI_2_60_SYSTEM_TABLE_REVISION ((2 << 16) | (60))
#define EFI_2_50_SYSTEM_TABLE_REVISION ((2 << 16) | (50))
#define EFI_2_40_SYSTEM_TABLE_REVISION ((2 << 16) | (40))
#define EFI_2_31_SYSTEM_TABLE_REVISION ((2 << 16) | (31))
#define EFI_2_30_SYSTEM_TABLE_REVISION ((2 << 16) | (30))
#define EFI_2_20_SYSTEM_TABLE_REVISION ((2 << 16) | (20))
#define EFI_2_10_SYSTEM_TABLE_REVISION ((2 << 16) | (10))
#define EFI_2_00_SYSTEM_TABLE_REVISION ((2 << 16) | (00))
#define EFI_1_10_SYSTEM_TABLE_REVISION ((1 << 16) | (10))
#define EFI_1_02_SYSTEM_TABLE_REVISION ((1 << 16) | (02))
#define EFI_SPECIFICATION_VERSION      EFI_SYSTEM_TABLE_REVISION
#define EFI_SYSTEM_TABLE_REVISION      EFI_2_60_SYSTEM_TABLE_REVISION

typedef struct
{
    efi_guid VendorGuid;
    const void *VendorTable;
} efi_configuration_table;

typedef struct efi_system_table
{
    efi_table_header hdr;
    ce_u16 *firmware_vendor;
    ce_u32 firmware_revision;
    efi_handle console_in_handle;
    efi_simple_text_input_protocol *con_in;
    efi_handle console_out_handle;
    efi_simple_text_output_protocol *con_out;
    efi_handle standard_error_handle;
    efi_simple_text_output_protocol *std_err;
    efi_runtime_services *runtime_services;
    efi_boot_services *boot_services;
    ce_usize number_of_table_entries;
    const efi_configuration_table *configuration_table;
} efi_system_table;
