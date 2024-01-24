#pragma once

#include "base.h"

#define EFI_DEVICE_PATH_PROTOCOL_GUID                                                  \
    {                                                                                  \
        0x09576e91, 0x6d3f, 0x11d2, { 0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b } \
    }

typedef struct
{
    ce_u8 type;
    ce_u8 sub_type;
    ce_u8 length[2];
} efi_device_path_protocol;

#define DEVICE_PATH_HARDWARE       0x01
#define DEVICE_PATH_ACPI           0x02
#define DEVICE_PATH_MESSAGING      0x03
#define DEVICE_PATH_MEDIA          0x04
#define DEVICE_PATH_BIOS_BOOT_SPEC 0x05
#define DEVICE_PATH_END            0x7f

#define DEVICE_PATH_INSTANCE_END 0x01
#define DEVICE_PATH_ENTIRE_END   0xff

#define DEVICE_PATH_HW_PCI        0x01
#define DEVICE_PATH_HW_PCCARD     0x02
#define DEVICE_PATH_HW_MEMMAP     0x03
#define DEVICE_PATH_HW_VENDOR     0x04
#define DEVICE_PATH_HW_CONTROLLER 0x05
#define DEVICE_PATH_HW_BMC        0x06

#define DEVICE_PATH_MESSAGING_ATAPI            0x01
#define DEVICE_PATH_MESSAGING_SCSI             0x02
#define DEVICE_PATH_MESSAGING_FIBRE_CHANNEL    0x03
#define DEVICE_PATH_MESSAGING_1394             0x04
#define DEVICE_PATH_MESSAGING_USB              0x05
#define DEVICE_PATH_MESSAGING_I2O              0x06
#define DEVICE_PATH_MESSAGING_INFINIBAND       0x09
#define DEVICE_PATH_MESSAGING_VENDOR           0x0a
#define DEVICE_PATH_MESSAGING_MAC              0x0b
#define DEVICE_PATH_MESSAGING_IPV4             0x0c
#define DEVICE_PATH_MESSAGING_IPV6             0x0d
#define DEVICE_PATH_MESSAGING_UART             0x0e
#define DEVICE_PATH_MESSAGING_USB_CLASS        0x0f
#define DEVICE_PATH_MESSAGING_USB_WWID         0x10
#define DEVICE_PATH_MESSAGING_USB_LUN          0x11
#define DEVICE_PATH_MESSAGING_SATA             0x12
#define DEVICE_PATH_MESSAGING_VLAN             0x14
#define DEVICE_PATH_MESSAGING_FIBRE_CHANNEL_EX 0x15

typedef struct
{
    efi_device_path_protocol header;
    efi_memory_type memory_type;
    efi_physical_addr start_address;
    efi_physical_addr end_address;
} efi_device_path_hw_memmap;
