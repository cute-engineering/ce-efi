#pragma once

#include "ip6.h"
#include "mnp.h"
#include "snp.h"

#define EFI_TCP6_SERVICE_BINDING_PROTOCOL_GUID                                         \
    {                                                                                  \
        0xec20eb79, 0x6c1a, 0x4664, { 0x9a, 0x0d, 0xd2, 0xe4, 0xcc, 0x16, 0xd6, 0x64 } \
    }

#define EFI_TCP6_PROTOCOL_GUID                                                         \
    {                                                                                  \
        0x46e44855, 0xbd60, 0x4ab7, { 0xab, 0x0d, 0xa6, 0x79, 0xb9, 0x44, 0x7d, 0x77 } \
    }

typedef struct
{
    efi_ipv6_addr station_address;
    ce_u16 station_port;
    efi_ipv6_addr remote_address;
    ce_u16 remote_port;
    bool active_flag;
} efi_tcp6_access_point;

typedef struct
{
    ce_u32 receive_buffer_size;
    ce_u32 send_buffer_size;
    ce_u32 max_syn_back_log;
    ce_u32 connection_timeout;
    ce_u32 data_retries;
    ce_u32 fin_timeout;
    ce_u32 time_wait_timeout;
    ce_u32 keep_alive_probes;
    ce_u32 keep_alive_time;
    ce_u32 keep_alive_interval;
    bool enable_nagle;
    bool enable_time_stamp;
    bool enable_window_scaling;
    bool enable_selective_ack;
    bool enable_path_mtu_discovery;
} efi_tcp6_option;

typedef struct
{
    ce_u8 traffic_class;
    ce_u8 hop_limit;
    efi_tcp6_access_point access_point;
    efi_tcp6_option *control_option;
} efi_tcp6_config_data;

typedef enum
{
    EFI_TCP6_STATE_CLOSED = 0,
    EFI_TCP6_STATE_LISTEN = 1,
    EFI_TCP6_STATE_SYN_SENT = 2,
    EFI_TCP6_STATE_SYN_RECEIVED = 3,
    EFI_TCP6_STATE_ESTABLISHED = 4,
    EFI_TCP6_STATE_FIN_WAIT1 = 5,
    EFI_TCP6_STATE_FIN_WAIT2 = 6,
    EFI_TCP6_STATE_CLOSING = 7,
    EFI_TCP6_STATE_TIME_WAIT = 8,
    EFI_TCP6_STATE_CLOSE_WAIT = 9,
    EFI_TCP6_STATE_LAST_ACK = 10
} efi_tcp6_connection_state;

typedef struct
{
    efi_event event;
    efi_status status;
} efi_tcp6_completion_token;

typedef struct
{
    efi_tcp6_completion_token completion_token;
} efi_tcp6_connection_token;

typedef struct
{
    efi_tcp6_completion_token completion_token;
    efi_handle new_child_handle;
} efi_tcp6_listen_token;

typedef struct
{
    ce_u32 fragment_length;
    void *fragment_buffer;
} efi_tcp6_fragment_data;

typedef struct
{
    bool urgent_flag;
    ce_u32 data_length;
    ce_u32 fragment_count;
    efi_tcp6_fragment_data fragment_table[1];
} efi_tcp6_receive_data;

typedef struct
{
    bool push;
    bool urgent;
    ce_u32 data_length;
    ce_u32 fragment_count;
    efi_tcp6_fragment_data fragment_table[1];
} efi_tcp6_transmit_data;

typedef struct
{
    efi_tcp6_completion_token completion_token;
    union
    {
        efi_tcp6_receive_data *rx_data;
        efi_tcp6_transmit_data *tx_data;
    };
} efi_tcp6_io_token;

typedef struct
{
    efi_tcp6_completion_token completion_token;
    bool abort_on_close;
} efi_tcp6_close_token;

typedef struct efi_tcp6_protocol
{
    efi_api efi_status (*get_mode_data)(struct efi_tcp6_protocol *self, efi_tcp6_connection_state *tcp6_state, efi_tcp6_config_data *tcp6_config_data, efi_ip6_mode_data *ip6_mode_data, efi_managed_network_config_data *mnp_config_data, efi_simple_network_mode *snp_mode_data);
    efi_api efi_status (*configure)(struct efi_tcp6_protocol *self, efi_tcp6_config_data *tcp6_config_data);
    efi_api efi_status (*connect)(struct efi_tcp6_protocol *self, efi_tcp6_connection_token *connection_token);
    efi_api efi_status (*accept)(struct efi_tcp6_protocol *self, efi_tcp6_listen_token *listen_token);
    efi_api efi_status (*transmit)(struct efi_tcp6_protocol *self, efi_tcp6_io_token *token);
    efi_api efi_status (*receive)(struct efi_tcp6_protocol *self, efi_tcp6_io_token *token);
    efi_api efi_status (*close)(struct efi_tcp6_protocol *self, efi_tcp6_close_token *close_token);
    efi_api efi_status (*cancel)(struct efi_tcp6_protocol *self, efi_tcp6_completion_token *token);
    efi_api efi_status (*poll)(struct efi_tcp6_protocol *self);
} efi_tcp6_protocol;
