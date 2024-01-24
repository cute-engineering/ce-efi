#pragma once

#include "base.h"

#define EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID                                              \
    {                                                                                  \
        0x9042a9de, 0x23dc, 0x4a38, { 0x96, 0xfb, 0x7a, 0xde, 0xd0, 0x80, 0x51, 0x6a } \
    }

typedef struct
{
    ce_u32 red_mask;
    ce_u32 green_mask;
    ce_u32 blue_mask;
    ce_u32 reserved_mask;
} efi_pixel_bitmask;

typedef enum
{
    EFI_PIXEL_RGBX8888,
    EFI_PIXEL_BGRX8888,
    EFI_PIXEL_BIT_MASK,
    EFI_PIXEL_BLT_ONLY,

    EFI_PIXEL_FORMAT_MAX
} efi_graphics_pixel_format;

typedef struct
{
    ce_u32 version;
    ce_u32 horizontal_resolution;
    ce_u32 vertical_resolution;
    efi_graphics_pixel_format pixel_format;
    efi_pixel_bitmask pixel_information;
    ce_u32 pixels_per_scan_line;
} efi_graphics_output_mode_information;

typedef struct
{
    ce_u32 max_mode;
    ce_u32 mode;
    efi_graphics_output_mode_information *info;
    ce_usize size_of_info;
    efi_physical_addr frame_buffer_base;
    ce_usize frame_buffer_size;
} efi_graphics_output_mode;

typedef struct
{
    ce_u8 blue;
    ce_u8 green;
    ce_u8 red;
    ce_u8 reserved;
} efi_graphics_output_blt_pixel;

typedef enum
{
    EFI_BLT_VIDEO_FILL,
    EFI_BLT_VIDEO_TO_BLT_BUFFER,
    EFI_BLT_BUFFER_TO_VIDEO,
    EFI_BLT_VIDEO_TO_VIDEO,
    EFI_GRAPHICS_OUTPUT_BLT_OPERATION_MAX
} efi_graphics_output_blt_operation;

typedef struct efi_graphics_output_protocol
{
    efi_api efi_status (*query_mode)(struct efi_graphics_output_protocol *self, ce_u32 mode_num, ce_usize *info_len, efi_graphics_output_mode_information **info);
    efi_api efi_status (*set_mode)(struct efi_graphics_output_protocol *self, ce_u32 mode_num);
    efi_api efi_status (*blt)(struct efi_graphics_output_protocol *self, efi_graphics_output_blt_pixel *blt_buf, efi_graphics_output_blt_operation blt_operation, ce_usize src_x, ce_usize src_y, ce_usize dest_x, ce_usize dest_y, ce_usize width, ce_usize height, ce_usize delta);
    efi_graphics_output_mode *mode;
} efi_graphics_output_protocol;
