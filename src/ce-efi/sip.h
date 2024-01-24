#pragma once

#include "base.h"

#define EFI_SERIAL_IO_PROTOCOL_GUID                                                    \
    {                                                                                  \
        0xBB25CF6F, 0xF1D4, 0x11D2, { 0x9a, 0x0c, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0xfd } \
    }

#define EFI_SERIAL_TERMINAL_DEVICE_TYPE_GUID                                           \
    {                                                                                  \
        0x6ad9a60f, 0x5815, 0x4c7c, { 0x8a, 0x10, 0x50, 0x53, 0xd2, 0xbf, 0x7a, 0x1b } \
    }

#define EFI_SERIAL_IO_PROTOCOL_REVISION    0x00010000
#define EFI_SERIAL_IO_PROTOCOL_REVISION1p1 0x00010001

//
// Control bits.
//
#define EFI_SERIAL_CLEAR_TO_SEND                0x0010
#define EFI_SERIAL_DATA_SET_READY               0x0020
#define EFI_SERIAL_RING_INDICATE                0x0040
#define EFI_SERIAL_CARRIER_DETECT               0x0080
#define EFI_SERIAL_REQUEST_TO_SEND              0x0002
#define EFI_SERIAL_DATA_TERMINAL_READY          0x0001
#define EFI_SERIAL_INPUT_BUFFER_EMPTY           0x0100
#define EFI_SERIAL_OUTPUT_BUFFER_EMPTY          0x0200
#define EFI_SERIAL_HARDWARE_LOOPBACK_ENABLE     0x1000
#define EFI_SERIAL_SOFTWARE_LOOPBACK_ENABLE     0x2000
#define EFI_SERIAL_HARDWARE_FLOW_CONTROL_ENABLE 0x4000

typedef enum
{
    EFI_PARITY_DEFAULT,
    EFI_PARITY_NO,
    EFI_PARITY_EVEN,
    EFI_PARITY_ODD,
    EFI_PARITY_MARK,
    EFI_PARITY_SPACE,
} efi_parity_type;

typedef enum
{
    EFI_STOP_BITS_DEFAULT,
    EFI_STOP_BITS_ON,
    EFI_STOP_BITS_ONE_FIVE,
    EFI_STOP_BITS_TWO
} efi_stop_bits_type;

typedef struct
{
    ce_u32 control_mask;
    ce_u32 timeout;
    ce_u64 baud_rate;
    ce_u32 receive_fifo_depth;
    ce_u32 data_bits;
    efi_parity_type parity;
    efi_stop_bits_type stop_bits;
} efi_serial_io_mode;

typedef struct efi_serial_io_protocol
{
    ce_u32 revision;

    efi_api efi_status (*reset)(struct efi_serial_io_protocol *self);
    efi_api efi_status (*set_attributes)(struct efi_serial_io_protocol *self, ce_u64 baud_rate, ce_u32 receive_fifo_depth, ce_u32 timeout, efi_parity_type parity, ce_u8 data_bits, efi_stop_bits_type stop_bits);
    efi_api efi_status (*set_control)(struct efi_serial_io_protocol *self, ce_u32 control);
    efi_api efi_status (*get_control)(struct efi_serial_io_protocol *self, ce_u32 *control);
    efi_api efi_status (*write)(struct efi_serial_io_protocol *self, ce_usize *buffer_size, void *buffer);
    efi_api efi_status (*read)(struct efi_serial_io_protocol *self, ce_usize *buffer_size, void *buffer);

    efi_serial_io_mode *mode;
    const struct elf_guid *device_type_guid; // revision 1.1
} efi_serial_io_protocol;
