#pragma once

#include "base.h"

#define EFI_USB_IO_PROTOCOL_GUID                                                       \
    {                                                                                  \
        0x2b2f68d6, 0x0cd2, 0x44cf, { 0x8e, 0x8b, 0xbb, 0xa2, 0x0b, 0x1b, 0x5b, 0x75 } \
    }

typedef enum
{
    EFI_USB_DATA_IN,
    EFI_USB_DATA_OUT,
    EFI_USB_NO_DATA
} efi_usb_data_direction;

#define EFI_USB_NOERROR        0x0000
#define EFI_USB_ERR_NOTEXECUTE 0x0001
#define EFI_USB_ERR_STALL      0x0002
#define EFI_USB_ERR_BUFFER     0x0004
#define EFI_USB_ERR_BABBLE     0x0008
#define EFI_USB_ERR_NAK        0x0010
#define EFI_USB_ERR_CRC        0x0020
#define EFI_USB_ERR_TIMEOUT    0x0040
#define EFI_USB_ERR_BITSTUFF   0x0080
#define EFI_USB_ERR_SYSTEM     0x0100

typedef struct
{
    ce_u8 request_type;
    ce_u8 request;
    ce_u16 value;
    ce_u16 index;
    ce_u16 length;
} efi_usb_device_request;

typedef efi_api efi_status (*efi_async_usb_transfer_callback)(void *Data, ce_usize DataLength, void *Context, ce_u32 Status);

typedef struct
{
    ce_u8 length;
    ce_u8 descriptor_type;
    ce_u16 bcd_usb;
    ce_u8 device_class;
    ce_u8 device_sub_class;
    ce_u8 device_protocol;
    ce_u8 max_packet_size0;
    ce_u16 id_vendor;
    ce_u16 id_product;
    ce_u16 bcd_device;
    ce_u8 str_manufacturer;
    ce_u8 str_product;
    ce_u8 str_serial_number;
    ce_u8 num_configurations;
} efi_usb_device_descriptor;

typedef struct
{
    ce_u8 length;
    ce_u8 descriptor_type;
    ce_u16 total_length;
    ce_u8 num_interfaces;
    ce_u8 configuration_value;
    ce_u8 configuration;
    ce_u8 attributes;
    ce_u8 max_power;
} efi_usb_config_descriptor;

typedef struct
{
    ce_u8 length;
    ce_u8 descriptor_type;
    ce_u8 interface_number;
    ce_u8 alternate_setting;
    ce_u8 num_endpoints;
    ce_u8 interface_class;
    ce_u8 interface_sub_class;
    ce_u8 interface_protocol;
    ce_u8 interface;
} efi_usb_interface_descriptor;

typedef struct
{
    ce_u8 length;
    ce_u8 descriptor_type;
    ce_u8 endpoint_address;
    ce_u8 attributes;
    ce_u16 max_packet_size;
    ce_u8 interval;
} efi_usb_endpoint_descriptor;

typedef struct efi_usb_io_protocol
{
    efi_api efi_status (*usb_control_transfer)(struct efi_usb_io_protocol *self, efi_usb_device_request *request, efi_usb_data_direction direction, ce_u32 timeout, void *data, ce_usize data_len, ce_u32 *status);

    efi_api efi_status (*usb_bulk_transfer)(struct efi_usb_io_protocol *self, ce_u8 endpoint, void *data, ce_usize data_len, ce_usize timeout, ce_u32 *status);

    efi_api efi_status (*usb_async_interrupt_transfer)(struct efi_usb_io_protocol *self, ce_u8 endpoint, bool is_new_transfer, ce_usize polling_interval, ce_usize data_len, efi_async_usb_transfer_callback interrupt_cb, void *context);

    efi_api efi_status (*usb_sync_interrupt_transfer)(struct efi_usb_io_protocol *self, ce_u8 endpoint, void *data, ce_usize *data_len, ce_usize timeout, ce_u32 *status);

    efi_api efi_status (*usb_isochronous_transfer)(struct efi_usb_io_protocol *self, ce_u8 endpoint, void *data, ce_usize data_len, ce_u32 *status);

    efi_api efi_status (*usb_async_isochronous_transfer)(struct efi_usb_io_protocol *self, ce_u8 endpoint, void *data, ce_usize data_len, efi_async_usb_transfer_callback isoc_cb, void *context);

    efi_api efi_status (*usb_get_device_descriptor)(struct efi_usb_io_protocol *self, efi_usb_device_descriptor *descriptor);

    efi_api efi_status (*usb_get_config_descriptor)(struct efi_usb_io_protocol *self, efi_usb_config_descriptor *descriptor);

    efi_api efi_status (*usb_get_interface_descriptor)(struct efi_usb_io_protocol *self, efi_usb_interface_descriptor *descriptor);

    efi_api efi_status (*usb_get_endpoint_descriptor)(struct efi_usb_io_protocol *self, ce_u8 endpt_index, efi_usb_endpoint_descriptor *descriptor);

    efi_api efi_status (*usb_get_string_descriptor)(struct efi_usb_io_protocol *self, ce_u16 langid, ce_u8 stringid, ce_u16 **str);

    efi_api efi_status (*usb_get_supported_languages)(struct efi_usb_io_protocol *self, ce_u16 **langid_table, ce_u16 *table_size);

    efi_api efi_status (*usb_port_reset)(struct efi_usb_io_protocol *self);
} efi_usb_io_protocol;
