#pragma once

#include "dpp.h"

#define EFI_BOOT_SERVICES_SIGNATURE 0x56524553544f4f42
#define EFI_BOOT_SERVICES_REVISION  EFI_SPECIFICATION_VERSION

typedef ce_usize efi_tpl;

#define TPL_APPLICATION 4
#define TPL_CALLBACK    8
#define TPL_NOTIFY      16
#define TPL_HIGH_LEVEL  31

typedef enum
{
    EFI_ALLOCATE_ANY_PAGES,
    EFI_ALLOCATE_MAX_ADDRESS,
    EFI_ALLOCATE_ADDRESS,
    EFI_MAX_ALLOCATE_TYPE
} efi_allocate_type;

typedef struct
{
    ce_u32 type;
    ce_u32 padding;
    efi_physical_addr physical_start;
    efi_virtual_addr virtual_start;
    ce_u64 number_of_pages;
    ce_u64 attribute;
} efi_memory_descriptor;

#define EFI_MEMORY_UC            0x0000000000000001
#define EFI_MEMORY_WC            0x0000000000000002
#define EFI_MEMORY_WT            0x0000000000000004
#define EFI_MEMORY_WB            0x0000000000000008
#define EFI_MEMORY_UCE           0x0000000000000010
#define EFI_MEMORY_WP            0x0000000000001000
#define EFI_MEMORY_RP            0x0000000000002000
#define EFI_MEMORY_XP            0x0000000000004000
#define EFI_MEMORY_NV            0x0000000000008000
#define EFI_MEMORY_MORE_RELIABLE 0x0000000000010000
#define EFI_MEMORY_RO            0x0000000000020000
#define EFI_MEMORY_RUNTIME       0x8000000000000000

#define EFI_MEMORY_DESCRIPTOR_VERSION 1

typedef enum
{
    EFI_INTERFACE_NATIVE
} efi_interface_type;

typedef enum
{
    EFI_LOCATE_SEARCH_ALL_HANDLES,
    EFI_LOCATE_SEARCH_BY_REGISTER_NOTIFY,
    EFI_LOCATE_SEARCH_BY_PROTOCOL
} efi_locate_search_type;

#define EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL  0x00000001
#define EFI_OPEN_PROTOCOL_GET_PROTOCOL        0x00000002
#define EFI_OPEN_PROTOCOL_TEST_PROTOCOL       0x00000004
#define EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER 0x00000008
#define EFI_OPEN_PROTOCOL_BY_DRIVER           0x00000010
#define EFI_OPEN_PROTOCOL_EXCLUSIVE           0x00000020

typedef struct
{
    efi_handle agent_handle;
    efi_handle controller_handle;
    ce_u32 attributes;
    ce_u32 open_count;
} efi_open_protocol_information_entry;

#define EFI_HII_PACKAGE_LIST_PROTOCOL_GUID                                             \
    {                                                                                  \
        0x6a1ee763, 0xd47a, 0x43b4, { 0xaa, 0xbe, 0xef, 0x1d, 0xe2, 0xab, 0x56, 0xfc } \
    }

typedef struct efi_hii_package_list_header efi_hii_package_list_header;
typedef efi_hii_package_list_header *efi_hii_package_list_protocol;

struct efi_system_table;
typedef efi_api efi_status (*efi_image_entry_point)(efi_handle img, struct efi_system_table *sys);

typedef struct
{
    efi_table_header hdr;
    efi_api efi_tpl (*raise_tpl)(efi_tpl new_tpl);
    efi_api void (*restore_tpl)(efi_tpl old_tpl);
    efi_api efi_status (*allocate_pages)(efi_allocate_type type, efi_memory_type memory_type, ce_usize pages, efi_physical_addr *memory);
    efi_api efi_status (*free_pages)(efi_physical_addr memory, ce_usize pages);
    efi_api efi_status (*get_memory_map)(ce_usize *memory_map_size, efi_memory_descriptor *memory_map, ce_usize *map_key, ce_usize *desc_size, ce_u32 *desc_version);
    efi_api efi_status (*allocate_pool)(efi_memory_type pool_type, ce_usize size, void **buf);
    efi_api efi_status (*free_pool)(void *buf);
    efi_api efi_status (*create_event)(ce_u32 type, efi_tpl notify_tpl, efi_event_notify notify_fn, void *notify_ctx, efi_event *event);
    efi_api efi_status (*set_timer)(efi_event event, efi_timer_delay type, ce_u64 trigger_time);
    efi_api efi_status (*wait_for_event)(ce_usize num_events, efi_event *event, ce_usize *index);
    efi_api efi_status (*signal_event)(efi_event event);
    efi_api efi_status (*close_event)(efi_event event);
    efi_api efi_status (*check_event)(efi_event event);
    efi_api efi_status (*install_protocol_interface)(efi_handle *handle, const efi_guid *protocol, efi_interface_type intf_type, void *intf);
    efi_api efi_status (*reinstall_protocol_interface)(efi_handle hadle, const efi_guid *protocol, void *old_intf, void *new_intf);
    efi_api efi_status (*uninstall_protocol_interface)(efi_handle handle, const efi_guid *protocol, void *intf);
    efi_api efi_status (*handle_protocol)(efi_handle handle, const efi_guid *protocol, void **intf);
    void *reserved;
    efi_api efi_status (*register_protocol_notify)(const efi_guid *protocol, efi_event event, void **registration);
    efi_api efi_status (*locate_handle)(efi_locate_search_type search_type, const efi_guid *protocol, void *search_key, ce_usize *buf_size, efi_handle *buf);
    efi_api efi_status (*locate_device_path)(const efi_guid *protocol, efi_device_path_protocol **path, efi_handle *device);
    efi_api efi_status (*install_configuration_table)(const efi_guid *guid, void *table);
    efi_api efi_status (*load_image)(bool boot_policy, efi_handle parent_image_handle, efi_device_path_protocol *path, void *src, ce_usize src_size, efi_handle *image_handle);
    efi_api efi_status (*start_image)(efi_handle image_handle, ce_usize *exit_data_size, ce_u16 **exit_data);
    efi_api efi_status (*exit)(efi_handle image_handle, efi_status exit_status, ce_usize exit_data_size, ce_u16 *exit_data);
    efi_api efi_status (*unload_image)(efi_handle image_handle);
    efi_api efi_status (*exit_boot_services)(efi_handle image_handle, ce_usize map_key);
    efi_api efi_status (*get_next_monotonic_count)(ce_u64 *count);
    efi_api efi_status (*stall)(ce_usize microseconds);
    efi_api efi_status (*set_watchdog_timer)(ce_usize timeout, ce_u64 watchdog_code, ce_usize data_size, ce_u16 *watchdog_data);
    efi_api efi_status (*connect_controller)(efi_handle controller_handle, efi_handle *driver_image_handle, efi_device_path_protocol *remaining_path, bool recursive);
    efi_api efi_status (*disconnect_controller)(efi_handle controller_handle, efi_handle driver_image_handle, efi_handle child_handle);
    efi_api efi_status (*open_protocol)(efi_handle handle, const efi_guid *protocol, void **intf, efi_handle agent_handle, efi_handle controller_handle, ce_u32 attributes);
    efi_api efi_status (*close_protocol)(efi_handle handle, const efi_guid *protocol, efi_handle agent_handle, efi_handle controller_handle);
    efi_api efi_status (*open_protocol_information)(efi_handle handle, const efi_guid *protocol, efi_open_protocol_information_entry **entry_buf, ce_usize *entry_count);
    efi_api efi_status (*protocols_per_handle)(efi_handle handle, efi_guid ***protocol_buf, ce_usize *protocol_buf_count);
    efi_api efi_status (*locate_handle_buffer)(efi_locate_search_type search_type, const efi_guid *protocol, void *search_key, ce_usize *num_handles, efi_handle **buf);
    efi_api efi_status (*locate_protocol)(const efi_guid *protocol, void *registration, void **intf);
    efi_api efi_status (*install_multiple_protocol_interfaces)(efi_handle *handle, ...);
    efi_api efi_status (*uninstall_multiple_protocol_interfaces)(efi_handle handle, ...);
    efi_api efi_status (*calculate_crc32)(void *data, ce_usize len, ce_u32 *crc32);
    efi_api void (*copy_mem)(void *dest, const void *src, ce_usize len);
    efi_api void (*set_mem)(void *buf, ce_usize len, ce_u8 val);
    efi_api efi_status (*create_event_ex)(ce_u32 type, efi_tpl notify_tpl, efi_event_notify notify_fn, const void *notify_ctx, const efi_guid *event_group, efi_event *event);
} efi_boot_services;
