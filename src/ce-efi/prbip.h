#pragma once

#include "bs.h"

#define EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_GUID                                           \
    {                                                                                  \
        0x2f707ebb, 0x4a1a, 0x11D4, { 0x9a, 0x38, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d } \
    }

typedef enum
{
    EFI_PCI_WIDTH_UINT8,
    EFI_PCI_WIDTH_UINT16,
    EFI_PCI_WIDTH_UINT32,
    EFI_PCI_WIDTH_UINT64,
    EFI_PCI_WIDTH_FIFO_UINT8,
    EFI_PCI_WIDTH_FIFO_UINT16,
    EFI_PCI_WIDTH_FIFO_UINT32,
    EFI_PCI_WIDTH_FIFO_UINT64,
    EFI_PCI_WIDTH_FILL_UINT8,
    EFI_PCI_WIDTH_FILL_UINT16,
    EFI_PCI_WIDTH_FILL_UINT32,
    EFI_PCI_WIDTH_FILL_UINT64,
    EFI_PCI_WIDTH_MAXIMUM,
} efi_pci_root_bridge_io_width;

struct efi_pci_root_bridge_io_protocol;

typedef struct
{
    efi_api efi_status (*read)(struct efi_pci_root_bridge_io_protocol *self, efi_pci_root_bridge_io_width width, ce_u64 addr, ce_usize count, void *buffer);
    efi_api efi_status (*write)(struct efi_pci_root_bridge_io_protocol *self, efi_pci_root_bridge_io_width width, ce_u64 addr, ce_usize count, void *buffer);
} efi_pci_root_bridge_io_access;

#define EFI_PCI_ATTRIBUTE_ISA_MOTHERBOARD_IO   0x0001
#define EFI_PCI_ATTRIBUTE_ISA_IO               0x0002
#define EFI_PCI_ATTRIBUTE_VGA_PALETTE_IO       0x0004
#define EFI_PCI_ATTRIBUTE_VGA_MEMORY           0x0008
#define EFI_PCI_ATTRIBUTE_VGA_IO               0x0010
#define EFI_PCI_ATTRIBUTE_IDE_PRIMARY_IO       0x0020
#define EFI_PCI_ATTRIBUTE_IDE_SECONDARY_IO     0x0040
#define EFI_PCI_ATTRIBUTE_MEMORY_WRITE_COMBINE 0x0080
#define EFI_PCI_ATTRIBUTE_MEMORY_CACHED        0x0800
#define EFI_PCI_ATTRIBUTE_MEMORY_DISABLE       0x1000
#define EFI_PCI_ATTRIBUTE_DUAL_ADDRESS_CYCLE   0x8000
#define EFI_PCI_ATTRIBUTE_ISA_IO_16            0x10000
#define EFI_PCI_ATTRIBUTE_VGA_PALETTE_IO_16    0x20000
#define EFI_PCI_ATTRIBUTE_VGA_IO_16            0x40000

typedef enum
{
    EFI_PCI_OPERATION_BUS_MASTER_READ,
    EFI_PCI_OPERATION_BUS_MASTER_WRITE,
    EFI_PCI_OPERATION_BUS_MASTER_COMMON_BUFFER,
    EFI_PCI_OPERATION_BUS_MASTER_READ64,
    EFI_PCI_OPERATION_BUS_MASTER_WRITE64,
    EFI_PCI_OPERATION_BUS_MASTER_COMMON_BUFFER64,
    EFI_PCI_OPERATION_MAXIMUM,
} efi_pci_root_bridge_io_operation;

typedef struct efi_pci_root_bridge_io_protocol
{
    efi_handle parent_handle;

    efi_api efi_status (*poll_mem)(struct efi_pci_root_bridge_io_protocol *self, efi_pci_root_bridge_io_width width, ce_u64 addr, ce_u64 mask, ce_u64 value, ce_u64 delay, ce_u64 *result);
    efi_api efi_status (*poll_io)(struct efi_pci_root_bridge_io_protocol *self, efi_pci_root_bridge_io_width width, ce_u64 addr, ce_u64 mask, ce_u64 value, ce_u64 delay, ce_u64 *result);

    efi_pci_root_bridge_io_access mem;
    efi_pci_root_bridge_io_access io;
    efi_pci_root_bridge_io_access pci;

    efi_api efi_status (*copy_mem)(struct efi_pci_root_bridge_io_protocol *self, efi_pci_root_bridge_io_width width, ce_u64 dest_addr, ce_u64 src_addr, ce_usize count);
    efi_api efi_status (*map)(struct efi_pci_root_bridge_io_protocol *self, efi_pci_root_bridge_io_operation operation, void *host_addr, ce_usize *num_bytes, efi_physical_addr *device_addr, void **mapping);
    efi_api efi_status (*unmap)(struct efi_pci_root_bridge_io_protocol *self, void *mapping);
    efi_api efi_status (*allocate_buffer)(struct efi_pci_root_bridge_io_protocol *self, efi_allocate_type type, efi_memory_type memory_type, ce_usize pages, void **host_addr, ce_u64 attributes);
    efi_api efi_status (*free_buffer)(struct efi_pci_root_bridge_io_protocol *self, ce_usize pages, void *host_addr);
    efi_api efi_status (*flush)(struct efi_pci_root_bridge_io_protocol *self);
    efi_api efi_status (*get_attributes)(struct efi_pci_root_bridge_io_protocol *self, ce_u64 *supports, ce_u64 *attributes);
    efi_api efi_status (*set_attributes)(struct efi_pci_root_bridge_io_protocol *self, ce_u64 attributes, ce_u64 *resource_base, ce_u64 *resource_len);
    efi_api efi_status (*configuration)(struct efi_pci_root_bridge_io_protocol *self, void **resources);

    ce_u32 segment_number;
} efi_pci_root_bridge_io_protocol;
