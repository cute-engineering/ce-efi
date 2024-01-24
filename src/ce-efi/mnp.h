#pragma once

#include "rs.h"
#include "snp.h"

#define EFI_MANAGED_NETWORK_PROTOCOL_GUID                                              \
    {                                                                                  \
        0x7ab33a91, 0xace5, 0x4326, { 0xb5, 0x72, 0xe7, 0xee, 0x33, 0xd3, 0x9f, 0x16 } \
    }

typedef struct
{
    efi_time timestamp;
    efi_event recycle_event;
    ce_u32 packet_length;
    ce_u32 header_length;
    ce_u32 address_length;
    ce_u32 data_length;
    bool broadcast_flag;
    bool multicast_flag;
    bool promiscuous_flag;
    ce_u16 protocol_type;
    void *destination_address;
    void *source_address;
    void *media_header;
    void *packet_data;
} efi_managed_network_receive_data;

typedef struct
{
    ce_u32 fragment_length;
    void *fragment_buffer;
} efi_managed_network_fragment_data;

typedef struct
{
    efi_mac_addr *destination_address;
    efi_mac_addr *source_address;
    ce_u16 protocol_type;
    ce_u32 data_length;
    ce_u16 header_length;
    ce_u16 fragment_count;
    efi_managed_network_fragment_data fragment_table[1];
} efi_managed_network_transmit_data;

typedef struct
{
    ce_u32 received_queue_timeout_value;
    ce_u32 transmit_queue_timeout_value;
    ce_u16 protocol_type_filter;
    bool enable_unicast_receive;
    bool enable_multicast_receive;
    bool enable_broadcast_receive;
    bool enable_promiscuous_receive;
    bool flush_queues_on_reset;
    bool enable_receive_timestamps;
    bool disable_background_polling;
} efi_managed_network_config_data;

typedef struct
{
    efi_event event;
    efi_status status;
    union
    {
        efi_managed_network_receive_data *rx_data;
        efi_managed_network_transmit_data *tx_data;
    } packet;
} efi_managed_network_sync_completion_token;

typedef struct efi_managed_network_protocol
{
    efi_api efi_status (*get_mode_data)(struct efi_managed_network_protocol *self, efi_managed_network_config_data *mnp_config_data, efi_simple_network_mode *snp_mode_data);
    efi_api efi_status (*configure)(struct efi_managed_network_protocol *self, efi_managed_network_config_data *mnp_config_data);
    efi_api efi_status (*mcast_ip_to_mac)(struct efi_managed_network_protocol *self, bool ipv6_flag, efi_ip_addr *ip_addr, efi_mac_addr *mac_addr);
    efi_api efi_status (*groups)(struct efi_managed_network_protocol *self, bool join_flag, efi_mac_addr *mac_addr);
    efi_api efi_status (*transmit)(struct efi_managed_network_protocol *self, efi_managed_network_sync_completion_token *token);
    efi_api efi_status (*receive)(struct efi_managed_network_protocol *self, efi_managed_network_sync_completion_token *token);
    efi_api efi_status (*cancel)(struct efi_managed_network_protocol *self, efi_managed_network_sync_completion_token *token);
    efi_api efi_status (*poll)(struct efi_managed_network_protocol *self);
} efi_managed_network_protocol;
