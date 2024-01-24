#pragma once

#include <ce-base.h>

// Attribute to emit an error if a function is called.
#if __has_attribute(unavailable)
#    define EFI_FUNCTION_UNAVAILABLE(msg) __attribute__((unavailable(msg))) /* Clang */
#else
#    define EFI_FUNCTION_UNAVAILABLE(msg)
#endif

// EFI functions and callbacks use the Microsoft Windows x86_64 ABI.
//
// This ABI is special for x86_64 (and possibly other architectures). Set the appropriate
// attribute per architecture, or allow the header to be used for types only with no function
// calls allowed.
#if defined(__x86_64__)
#    define efi_api __attribute__((ms_abi))
#elif defined(__i386__)
#    define efi_api __attribute__((regparm(0)))
#elif defined(__aarch64__) || defined(__riscv)
// ARM64 doesn't need the ABI tag, likewise RISC-V.
#    define efi_api
#else
#    define efi_api EFI_FUNCTION_UNAVAILABLE("EFI API functions undefined for this architecture.")
#endif

#define EFI_ERROR_MASK ((uintptr_t)INTPTR_MAX + 1)
#define EFI_ERR(x)     (EFI_ERROR_MASK | (x))
#define EFI_ERROR(x)   (((intptr_t)(x)) < 0)

#define EFI_SUCCESS              0u
#define EFI_LOAD_ERROR           EFI_ERR(1)
#define EFI_INVALID_PARAMETER    EFI_ERR(2)
#define EFI_UNSUPPORTED          EFI_ERR(3)
#define EFI_BAD_BUFFER_SIZE      EFI_ERR(4)
#define EFI_BUFFER_TOO_SMALL     EFI_ERR(5)
#define EFI_NOT_READY            EFI_ERR(6)
#define EFI_DEVICE_ERROR         EFI_ERR(7)
#define EFI_WRITE_PROTECTED      EFI_ERR(8)
#define EFI_OUT_OF_RESOURCES     EFI_ERR(9)
#define EFI_VOLUME_CORRUPTED     EFI_ERR(10)
#define EFI_VOLUME_FULL          EFI_ERR(11)
#define EFI_NO_MEDIA             EFI_ERR(12)
#define EFI_MEDIA_CHANGED        EFI_ERR(13)
#define EFI_NOT_FOUND            EFI_ERR(14)
#define EFI_ACCESS_DENIED        EFI_ERR(15)
#define EFI_NO_RESPONSE          EFI_ERR(16)
#define EFI_NO_MAPPING           EFI_ERR(17)
#define EFI_TIMEOUT              EFI_ERR(18)
#define EFI_NOT_STARTED          EFI_ERR(19)
#define EFI_ALREADY_STARTED      EFI_ERR(20)
#define EFI_ABORTED              EFI_ERR(21)
#define EFI_ICMP_ERROR           EFI_ERR(22)
#define EFI_TFTP_ERROR           EFI_ERR(23)
#define EFI_PROTOCOL_ERROR       EFI_ERR(24)
#define EFI_INCOMPATIBLE_VERSION EFI_ERR(25)
#define EFI_SECURITY_VIOLATION   EFI_ERR(26)
#define EFI_CRC_ERROR            EFI_ERR(27)
#define EFI_END_OF_MEDIA         EFI_ERR(28)
#define EFI_END_OF_FILE          EFI_ERR(31)
#define EFI_INVALID_LANGUAGE     EFI_ERR(32)
#define EFI_COMPROMISED_DATA     EFI_ERR(33)
#define EFI_IP_ADDRESS_CONFLICT  EFI_ERR(34)
#define EFI_HTTP_ERROR           EFI_ERR(35)
#define EFI_CONNECTION_FIN       EFI_ERR(104)
#define EFI_CONNECTION_RESET     EFI_ERR(105)
#define EFI_CONNECTION_REFUSED   EFI_ERR(106)

// TODO: figure out where to put these. They're just mentioned in passing in the
// spec as some of many industry standard GUIDs but not part of the spec itself.
#define ACPI_TABLE_GUID                                                                \
    {                                                                                  \
        0xeb9d2d30, 0x2d88, 0x11d3, { 0x9a, 0x16, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d } \
    }
#define ACPI_20_TABLE_GUID                                                             \
    {                                                                                  \
        0x8868e871, 0xe4f1, 0x11d3, { 0xbc, 0x22, 0x00, 0x80, 0xc7, 0x3c, 0x88, 0x81 } \
    }
#define SMBIOS_TABLE_GUID                                                              \
    {                                                                                  \
        0xeb9d2d31, 0x2d88, 0x11d3, { 0x9a, 0x16, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d } \
    }
#define SMBIOS3_TABLE_GUID                                                             \
    {                                                                                  \
        0xf2fd1544, 0x9794, 0x4a2c, { 0x99, 0x2e, 0xe5, 0xbb, 0xcf, 0x20, 0xe3, 0x94 } \
    }

#define EFI_MEMORY_ATTRIBUTES_GUID                                                     \
    {                                                                                  \
        0xdcfa911d, 0x26eb, 0x469f, { 0xa2, 0x20, 0x38, 0xb7, 0xdc, 0x46, 0x12, 0x20 } \
    }

typedef struct
{
    ce_u64 signature;
    ce_u32 revision;
    ce_u32 header_size;
    ce_u32 crc32;
    ce_u32 reserved;
} efi_table_header;

typedef struct efi_guid
{
    ce_u32 data1;
    ce_u16 data2;
    ce_u16 data3;
    ce_u8 data4[8];
} efi_guid;

typedef void *efi_handle;

typedef ce_usize efi_status __attribute__((warn_unused_result));

typedef struct
{
    ce_u8 addr[32];
} efi_mac_addr;

typedef struct
{
    ce_u8 addr[4];
} efi_ipv4_addr;

typedef struct
{
    ce_u8 addr[16];
} efi_ipv6_addr;

typedef union
{
    efi_ipv4_addr v4;
    efi_ipv6_addr v6;
} efi_ip_addr;

typedef struct efi_memory_attributes_table_header
{
    ce_u32 version;
    ce_u32 number_of_entries;
    ce_u32 descriptor_size;
    ce_u32 reserved;
} efi_memory_attributes_table_header;

// This really belongs in boot-services.h, but causes circular dependencies with
// device-path.h.
typedef enum
{
    EFI_RESERVED_MEMORY_TYPE,
    EFI_LOADER_CODE,
    EFI_LOADER_DATA,
    EFI_BOOT_SERVICES_CODE,
    EFI_BOOT_SERVICES_DATA,
    EFI_RUNTIME_SERVICES_CODE,
    EFI_RUNTIME_SERVICES_DATA,
    EFI_CONVENTIONAL_MEMORY,
    EFI_UNUSABLE_MEMORY,
    EFI_ACPI_RECLAIM_MEMORY,
    EFI_ACPI_MEMORY_NVS,
    EFI_MEMORY_MAPPED_IO,
    EFI_MEMORY_MAPPED_IO_PORT_SPACE,
    EFI_PAL_CODE,
    EFI_PERSISTENT_MEMORY,
    EFI_MAX_MEMORY_TYPE
} efi_memory_type;

typedef ce_u64 efi_physical_addr;
typedef ce_u64 efi_virtual_addr;

typedef void *efi_event;

#define EVT_TIMER                         0x80000000
#define EVT_RUNTIME                       0x40000000
#define EVT_NOTIFY_WAIT                   0x00000100
#define EVT_NOTIFY_SIGNAL                 0x00000200
#define EVT_SIGNAL_EXIT_BOOT_SERVICES     0x00000201
#define EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE 0x60000202

#define EFI_EVENT_GROUP_EXIT_BOOT_SERVICES                                             \
    {                                                                                  \
        0x27abf055, 0xb1b8, 0x4c26, { 0x80, 0x48, 0x74, 0x8f, 0x37, 0xba, 0xa2, 0xdf } \
    }
#define EFI_EVENT_GROUP_VIRTUAL_ADDRESS_CHANGE                                         \
    {                                                                                  \
        0x13fa7698, 0xc831, 0x49c7, { 0x87, 0xea, 0x8f, 0x43, 0xfc, 0xc2, 0x51, 0x96 } \
    }
#define EFI_EVENT_GROUP_MEMORY_MAP_CHANGE                                              \
    {                                                                                  \
        0x78bee926, 0x692f, 0x48fd, { 0x9e, 0xdb, 0x01, 0x42, 0x2e, 0xf0, 0xd7, 0xab } \
    }
#define EFI_EVENT_GROUP_READY_TO_BOOT                                                  \
    {                                                                                  \
        0x7ce88fb3, 0x4bd7, 0x4679, { 0x87, 0xa8, 0xa8, 0xd8, 0xde, 0xe5, 0x0d, 0x2b } \
    }

typedef efi_api void (*efi_event_notify)(efi_event event, void *ctx);

typedef enum
{
    EFI_TIMER_CANCEL,
    EFI_TIMER_PERIODIC,
    EFI_TIMER_RELATIVE
} efi_timer_delay;
