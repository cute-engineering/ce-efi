#pragma once

#include "base.h"

#define EFI_TCG2_PROTOCOL_GUID                                                         \
    {                                                                                  \
        0x607f766c, 0x7455, 0x42be, { 0x93, 0x0b, 0xe4, 0xd7, 0x6d, 0xb2, 0x72, 0x0f } \
    }

/* values for EFI_TCG2_EVENT_LOG_FORMAT */
#define EFI_TCG2_EVENT_LOG_FORMAT_TCG_1_2 0x00000001
#define EFI_TCG2_EVENT_LOG_FORMAT_TCG_2   0x00000002

/* values for EFI_TCG2_EVENT_ALGORITHM_BITMAP */
#define EFI_TCG2_BOOT_HASH_ALG_SHA1    0x00000001
#define EFI_TCG2_BOOT_HASH_ALG_SHA256  0x00000002
#define EFI_TCG2_BOOT_HASH_ALG_SHA384  0x00000004
#define EFI_TCG2_BOOT_HASH_ALG_SHA512  0x00000008
#define EFI_TCG2_BOOT_HASH_ALG_SM3_256 0x00000010

typedef struct
{
    ce_u8 Major;
    ce_u8 Minor;
} efi_tcg2_version;

typedef struct
{
    ce_u8 size;
    efi_tcg2_version StructureVersion;
    efi_tcg2_version ProtocolVersion;
    ce_u32 HashAlgorithmBitmap;
    ce_u32 SupportedEventLogs;
    ce_u8 TPMPresentFlag;
    ce_u16 MaxCommandSize;
    ce_u16 MaxResponseSize;
    ce_u32 ManufacturerID;
    ce_u32 NumberOfPcrBanks;
    ce_u32 ActivePcrBanks;
} efi_tcg2_boot_service_capability; // not packed ("TCG EFI Protocol Specification 6.4")
_Static_assert(sizeof(efi_tcg2_boot_service_capability) == 36,
               "Wrong efi_tcg2_boot_service_capability size");

typedef struct efi_tcg2_event_header
{
    ce_u32 HeaderSize;
    ce_u16 HeaderVersion;
    ce_u32 PCRIndex;
    ce_u32 EventType;
} __attribute__((packed)) efi_tcg2_event_header;

typedef struct efi_tcg2_event
{
    ce_u32 Size;
    efi_tcg2_event_header Header;
    ce_u8 Event[];
} __attribute__((packed)) efi_tcg2_event;

typedef struct efi_tcg2_protocol
{
    efi_api efi_status (*get_capability)(struct efi_tcg2_protocol *, efi_tcg2_boot_service_capability *);
    efi_api efi_status (*get_event_log)(struct efi_tcg2_protocol *, ce_u32 event_log_format, void **event_log_location, void **event_log_last_entry, bool *event_log_truncated);
    efi_api efi_status (*hash_log_extend_event)(struct efi_tcg2_protocol *, ce_u64 flags, void *data_to_hash, ce_u64 data_len, efi_tcg2_event *tcg_event);
    efi_api efi_status (*submit_command)(struct efi_tcg2_protocol *, ce_u32 block_size, ce_u8 *block_data, ce_u32 output_size, ce_u8 *output_data);
    efi_api efi_status (*get_active_pcr_banks)(struct efi_tcg2_protocol *, ce_u32 *active_pcr_banks);
    efi_api efi_status (*set_active_pcr_banks)(struct efi_tcg2_protocol *, ce_u32 active_pcr_banks);
    efi_api efi_status (*get_result_of_set_active_pcr_banks)(struct efi_tcg2_protocol *, ce_u32 *present, ce_u32 *response);
} efi_tcg2_protocol;
