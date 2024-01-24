#pragma once

#include "base.h"

typedef struct
{
    ce_u8 default_protocol;
    bool accept_any_protocol;
    bool accept_icmp_errors;
    bool accept_promiscuous;
    efi_ipv6_addr destination_address;
    efi_ipv6_addr station_address;
    ce_u8 traffic_class;
    ce_u8 hop_limit;
    ce_u32 flow_label;
    ce_u32 receive_timeout;
    ce_u32 transmit_timeout;
} efi_ip6_config_data;

typedef struct
{
    efi_ipv6_addr address;
    ce_u8 prefix_length;
} efi_ip6_address_info;

typedef struct
{
    efi_ipv6_addr gateway;
    efi_ipv6_addr destination;
    ce_u8 prefix_length;
} efi_ip6_route_table;

typedef enum
{
    EFI_NEIGHBOR_IN_COMPLETE,
    EFI_NEIGHBOR_REACHABLE,
    EFI_NEIGHBOR_STALE,
    EFI_NEIGHBOR_DELAY,
    EFI_NEIGHBOR_PROBE
} efi_ip6_neighbor_state;

typedef struct
{
    efi_ipv6_addr neighbor;
    efi_mac_addr link_address;
    efi_ip6_neighbor_state state;
} efi_ip6_neighbor_cache;

typedef struct
{
    ce_u8 type;
    ce_u8 code;
} efi_ip6_icmp_type;

typedef struct
{
    bool is_started;
    ce_u32 max_packet_size;
    efi_ip6_config_data config_data;
    bool is_configured;
    ce_u32 address_count;
    efi_ip6_address_info *address_list;
    ce_u32 group_count;
    efi_ipv6_addr *group_table;
    ce_u32 route_count;
    efi_ip6_route_table *route_table;
    ce_u32 neighbor_count;
    efi_ip6_neighbor_cache *neighbor_cache;
    ce_u32 prefix_count;
    efi_ip6_address_info *prefix_table;
    ce_u32 icmp_type_count;
    efi_ip6_icmp_type *icmp_type_list;
} efi_ip6_mode_data;
