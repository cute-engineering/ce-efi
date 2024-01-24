#pragma once

#include "base.h"

#define EFI_SIMPLE_NETWORK_PROTOCOL_GUID                                               \
    {                                                                                  \
        0xa19832b9, 0xac25, 0x11d3, { 0x9a, 0x2d, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d } \
    }

#define EFI_SIMPLE_NETWORK_PROTOCOL_REVISION 0x00010000

#define EFI_MAX_MCAST_FILTER_CNT 16
typedef struct
{
    ce_u32 state;
    ce_u32 hw_address_size;
    ce_u32 media_header_size;
    ce_u32 max_packet_size;
    ce_u32 nv_ram_size;
    ce_u32 nv_ram_access_size;
    ce_u32 receive_filter_mask;
    ce_u32 receive_filter_setting;
    ce_u32 max_m_cast_filter_count;
    ce_u32 m_cast_filter_count;
    efi_mac_addr m_cast_filter[EFI_MAX_MCAST_FILTER_CNT];
    efi_mac_addr current_address;
    efi_mac_addr broadcast_address;
    efi_mac_addr permanent_address;
    ce_u8 if_type;
    bool mac_address_changeable;
    bool multiple_tx_supported;
    bool media_present_supported;
    bool media_present;
} efi_simple_network_mode;

typedef enum
{
    EFI_SIMPLE_NETWORK_STOPPED,
    EFI_SIMPLE_NETWORK_STARTED,
    EFI_SIMPLE_NETWORK_INITIALIZED,
    EFI_SIMPLE_NETWORK_MAX_STATE
} efi_simple_network_state;

#define EFI_SIMPLE_NETWORK_RECEIVE_UNICAST               0x01
#define EFI_SIMPLE_NETWORK_RECEIVE_MULTICAST             0x02
#define EFI_SIMPLE_NETWORK_RECEIVE_BROADCAST             0x04
#define EFI_SIMPLE_NETWORK_RECEIVE_PROMISCUOUS           0x08
#define EFI_SIMPLE_NETWORK_RECEIVE_PROMISCUOUS_MULTICAST 0x10

typedef struct
{
    ce_u64 rx_total_frames;
    ce_u64 rx_good_frames;
    ce_u64 rx_undersize_frames;
    ce_u64 rx_oversize_frames;
    ce_u64 rx_dropped_frames;
    ce_u64 rx_unicast_frames;
    ce_u64 rx_broadcast_frames;
    ce_u64 rx_multicast_frames;
    ce_u64 rx_crc_error_frames;
    ce_u64 rx_total_bytes;
    ce_u64 tx_total_frames;
    ce_u64 tx_good_frames;
    ce_u64 tx_undersize_frames;
    ce_u64 tx_oversize_frames;
    ce_u64 tx_dropped_frames;
    ce_u64 tx_unicast_frames;
    ce_u64 tx_broadcast_frames;
    ce_u64 tx_multicast_frames;
    ce_u64 tx_crc_error_frames;
    ce_u64 tx_total_bytes;
    ce_u64 collisions;
    ce_u64 unsupported_protocol;
    ce_u64 rx_duplicated_frames;
    ce_u64 rx_decrypt_error_frames;
    ce_u64 tx_error_frames;
    ce_u64 tx_retry_frames;
} efi_network_statistics;

#define EFI_SIMPLE_NETWORK_RECEIVE_INTERRUPT  0x01
#define EFI_SIMPLE_NETWORK_TRANSMIT_INTERRUPT 0x02
#define EFI_SIMPLE_NETWORK_COMMAND_INTERRUPT  0x04
#define EFI_SIMPLE_NETWORK_SOFTWARE_INTERRUPT 0x08

typedef struct efi_simple_network_protocol
{
    ce_u64 revision;

    efi_api efi_status (*start)(struct efi_simple_network_protocol *self);
    efi_api efi_status (*stop)(struct efi_simple_network_protocol *self);
    efi_api efi_status (*initialize)(struct efi_simple_network_protocol *self, ce_usize extra_rx_buf_size, ce_usize extra_tx_buf_size);
    efi_api efi_status (*reset)(struct efi_simple_network_protocol *self, bool extended_verification);
    efi_api efi_status (*shutdown)(struct efi_simple_network_protocol *self);
    efi_api efi_status (*receive_filters)(struct efi_simple_network_protocol *self, ce_u32 enable, ce_u32 disable, bool reset_mcast_filter, ce_usize mcast_filter_count, efi_mac_addr *mcast_filter);
    efi_api efi_status (*station_address)(struct efi_simple_network_protocol *self, bool reset, efi_mac_addr *new_addr);
    efi_api efi_status (*statistics)(struct efi_simple_network_protocol *self, bool reset, ce_usize *stats_size, efi_network_statistics *stats_table);
    efi_api efi_status (*m_cast_ip_to_mac)(struct efi_simple_network_protocol *self, bool ipv6, efi_ip_addr *ip, efi_mac_addr *mac);
    efi_api efi_status (*nv_data)(struct efi_simple_network_protocol *self, bool read_write, ce_usize offset, ce_usize buf_size, void *buf);
    efi_api efi_status (*get_status)(struct efi_simple_network_protocol *self, ce_u32 *interrupt_status, void **tx_buf);
    efi_api efi_status (*transmit)(struct efi_simple_network_protocol *self, ce_usize header_size, ce_usize buf_size, void *buf, efi_mac_addr *src, efi_mac_addr *dest, ce_u16 *protocol);
    efi_api efi_status (*receive)(struct efi_simple_network_protocol *self, ce_usize *header_size, ce_usize *buf_size, void *buf, efi_mac_addr *src, efi_mac_addr *dest, ce_u16 *protocol);

    efi_event wait_for_packet;
    efi_simple_network_mode *mode;
} efi_simple_network_protocol;
