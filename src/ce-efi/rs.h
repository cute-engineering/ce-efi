#pragma once

#include "bs.h"

#define EFI_RUNTIME_SERVICES_SIGNATURE 0x56524553544e5552
#define EFI_RUNTIME_SERVICES_REVISION  EFI_SPECIFICATION_VERSION

#define EFI_VARIABLE_NON_VOLATILE                          0x00000001
#define EFI_VARIABLE_BOOTSERVICE_ACCESS                    0x00000002
#define EFI_VARIABLE_RUNTIME_ACCESS                        0x00000004
#define EFI_VARIABLE_HARDWARE_ERROR_RECORD                 0x00000008
#define EFI_VARIABLE_AUTHENTICATED_WRITE_ACCESS            0x00000010
#define EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS 0x00000020
#define EFI_VARIABLE_APPEND_WRITE                          0x00000040

#define EFI_HARDWARE_ERROR_VARIABLE                                                    \
    {                                                                                  \
        0x414e6bdd, 0xe47b, 0x47cc, { 0xb2, 0x44, 0xbb, 0x61, 0x02, 0x0c, 0xf5, 0x16 } \
    }

typedef struct
{
    ce_u16 year;
    ce_u8 month;
    ce_u8 day;
    ce_u8 hour;
    ce_u8 minute;
    ce_u8 second;
    ce_u8 pad1;
    ce_u32 nanosecond;
    ce_i16 time_zone;
    ce_u8 daylight;
    ce_u8 pad2;
} efi_time;

#define EFI_TIME_ADJUST_DAYLIGHT 0x01
#define EFI_TIME_IN_DAYLIGHT     0x02

#define EFI_UNSPECIFIED_TIMEZONE 0x07FF

typedef struct
{
    ce_u32 resolution;
    ce_u32 accuracy;
    bool sets_to_zero;
} efi_time_capabilities;

#define EFI_OPTIONAL_PTR 0x00000001

typedef enum
{
    EFI_RESET_COLD,
    EFI_RESET_WARM,
    EFI_RESET_SHUTDOWN,
    EFI_RESET_PLATFORM_SPECIFIC
} efi_reset_type;

typedef struct
{
    ce_u64 length;
    union
    {
        efi_physical_addr data_block;
        efi_physical_addr continuation_pointer;
    };
} efi_capsule_block_descriptor;

typedef struct
{
    efi_guid capsule_guid;
    ce_u32 header_size;
    ce_u32 flags;
    ce_u32 capsule_image_size;
} efi_capsule_header;

#define EFI_CAPSULE_FLAGS_PERSIST_ACROSS_RESET  0x00010000
#define EFI_CAPSULE_FLAGS_POPULATE_SYSTEM_TABLE 0x00020000
#define EFI_CAPSULE_FLAGS_INITIATE_RESET        0x00040000

#define EFI_OS_INDICATIONS_BOOT_TO_FW_UI                   0x0000000000000001
#define EFI_OS_INDICATIONS_TIMESTAMP_REVOCATION            0x0000000000000002
#define EFI_OS_INDICATIONS_FILE_CAPSULE_DELIVERY_SUPPORTED 0x0000000000000004
#define EFI_OS_INDICATIONS_FMP_CAPSULE_SUPPORTED           0x0000000000000008
#define EFI_OS_INDICATIONS_CAPSULE_RESULT_VAR_SUPPORTED    0x0000000000000010
#define EFI_OS_INDICATIONS_START_OS_RECOVERY               0x0000000000000020
#define EFI_OS_INDICATIONS_START_PLATFORM_RECOVERY         0x0000000000000040

#define EFI_CAPSULE_REPORT_GUID                                                        \
    {                                                                                  \
        0x39b68c46, 0xf7fb, 0x441b, { 0xb6, 0xec, 0x16, 0xb0, 0xf6, 0x98, 0x21, 0xf3 } \
    }

typedef struct
{
    ce_u32 variable_total_size;
    ce_u32 reserved;
    efi_guid capsule_guid;
    efi_time capsule_processed;
    efi_status capsule_status;
} efi_capsule_result_variable_header;

typedef struct
{
    efi_table_header hdr;

    efi_api efi_status (*get_time)(efi_time *time, efi_time_capabilities *capabilities);
    efi_api efi_status (*set_time)(efi_time *time);
    efi_api efi_status (*get_wakeup_time)(bool *enabled, bool *pending, efi_time *time);
    efi_api efi_status (*set_wakeup_time)(bool enable, efi_time *time);
    efi_api efi_status (*set_virtual_address_map)(ce_usize memory_map_size, ce_usize desc_size, ce_u32 desc_version, efi_memory_descriptor *virtual_map);
    efi_api efi_status (*convert_pointer)(ce_usize debug_disposition, void **addr);
    efi_api efi_status (*get_variable)(ce_u16 *var_name, efi_guid *vendor_guid, ce_u32 *attributes, ce_usize *data_size, void *data);
    efi_api efi_status (*get_next_variable_name)(ce_usize *var_name_size, ce_u16 *var_name, efi_guid *vendor_guid);
    efi_api efi_status (*set_variable)(ce_u16 *var_name, efi_guid *vendor_guid, ce_u32 attributes, ce_usize data_size, const void *data);
    efi_api efi_status (*get_next_high_monotonic_count)(ce_u32 *high_count);
    efi_api efi_status (*reset_system)(efi_reset_type reset_type, efi_status reset_status, ce_usize data_size, void *reset_data);
    efi_api efi_status (*update_capsule)(efi_capsule_header **capsule_header_array, ce_usize capsule_count, efi_physical_addr scatter_gather_list);
    efi_api efi_status (*query_capsule_capabilities)(efi_capsule_header **capsule_header_array, ce_usize capsule_count, ce_u64 *max_capsule_size, efi_reset_type *reset_type);
    efi_api efi_status (*query_variable_info)(ce_u32 attributes, ce_u64 *max_var_storage_size, ce_u64 *remaining_var_storage_size, ce_u64 *max_var_size);
} efi_runtime_services;
