#pragma once

#include "base.h"

#define EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL_GUID                                           \
    {                                                                                  \
        0x387477c2, 0x69c7, 0x11d2, { 0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b } \
    }

typedef struct
{
    ce_i32 max_mode;
    ce_i32 mode;
    ce_i32 attribute;
    ce_i32 cursor_column;
    ce_i32 cursor_row;
    bool cursor_visible;
} efi_simple_text_output_mode;

//*******************************************************
// UNICODE DRAWING CHARACTERS
//*******************************************************
#define EFI_BOXDRAW_HORIZONTAL                 0x2500
#define EFI_BOXDRAW_VERTICAL                   0x2502
#define EFI_BOXDRAW_DOWN_RIGHT                 0x250c
#define EFI_BOXDRAW_DOWN_LEFT                  0x2510
#define EFI_BOXDRAW_UP_RIGHT                   0x2514
#define EFI_BOXDRAW_UP_LEFT                    0x2518
#define EFI_BOXDRAW_VERTICAL_RIGHT             0x251c
#define EFI_BOXDRAW_VERTICAL_LEFT              0x2524
#define EFI_BOXDRAW_DOWN_HORIZONTAL            0x252c
#define EFI_BOXDRAW_UP_HORIZONTAL              0x2534
#define EFI_BOXDRAW_VERTICAL_HORIZONTAL        0x253c
#define EFI_BOXDRAW_DOUBLE_HORIZONTAL          0x2550
#define EFI_BOXDRAW_DOUBLE_VERTICAL            0x2551
#define EFI_BOXDRAW_DOWN_RIGHT_DOUBLE          0x2552
#define EFI_BOXDRAW_DOWN_DOUBLE_RIGHT          0x2553
#define EFI_BOXDRAW_DOUBLE_DOWN_RIGHT          0x2554
#define EFI_BOXDRAW_DOWN_LEFT_DOUBLE           0x2555
#define EFI_BOXDRAW_DOWN_DOUBLE_LEFT           0x2556
#define EFI_BOXDRAW_DOUBLE_DOWN_LEFT           0x2557
#define EFI_BOXDRAW_UP_RIGHT_DOUBLE            0x2558
#define EFI_BOXDRAW_UP_DOUBLE_RIGHT            0x2559
#define EFI_BOXDRAW_DOUBLE_UP_RIGHT            0x255a
#define EFI_BOXDRAW_UP_LEFT_DOUBLE             0x255b
#define EFI_BOXDRAW_UP_DOUBLE_LEFT             0x255c
#define EFI_BOXDRAW_DOUBLE_UP_LEFT             0x255d
#define EFI_BOXDRAW_VERTICAL_RIGHT_DOUBLE      0x255e
#define EFI_BOXDRAW_VERTICAL_DOUBLE_RIGHT      0x255f
#define EFI_BOXDRAW_DOUBLE_VERTICAL_RIGHT      0x2560
#define EFI_BOXDRAW_VERTICAL_LEFT_DOUBLE       0x2561
#define EFI_BOXDRAW_VERTICAL_DOUBLE_LEFT       0x2562
#define EFI_BOXDRAW_DOUBLE_VERTICAL_LEFT       0x2563
#define EFI_BOXDRAW_DOWN_HORIZONTAL_DOUBLE     0x2564
#define EFI_BOXDRAW_DOWN_DOUBLE_HORIZONTAL     0x2565
#define EFI_BOXDRAW_DOUBLE_DOWN_HORIZONTAL     0x2566
#define EFI_BOXDRAW_UP_HORIZONTAL_DOUBLE       0x2567
#define EFI_BOXDRAW_UP_DOUBLE_HORIZONTAL       0x2568
#define EFI_BOXDRAW_DOUBLE_UP_HORIZONTAL       0x2569
#define EFI_BOXDRAW_VERTICAL_HORIZONTAL_DOUBLE 0x256a
#define EFI_BOXDRAW_VERTICAL_DOUBLE_HORIZONTAL 0x256b
#define EFI_BOXDRAW_DOUBLE_VERTICAL_HORIZONTAL 0x256c

//*******************************************************
// EFI Required Block Elements Code Chart
//*******************************************************
#define EFI_BLOCKELEMENT_FULL_BLOCK  0x2588
#define EFI_BLOCKELEMENT_LIGHT_SHADE 0x2591

//*******************************************************
// EFI Required Geometric Shapes Code Chart
//*******************************************************
#define EFI_GEOMETRICSHAPE_UP_TRIANGLE    0x25b2
#define EFI_GEOMETRICSHAPE_RIGHT_TRIANGLE 0x25ba
#define EFI_GEOMETRICSHAPE_DOWN_TRIANGLE  0x25bc
#define EFI_GEOMETRICSHAPE_LEFT_TRIANGLE  0x25c4

//*******************************************************
// EFI Required Arrow shapes
//*******************************************************
#define EFI_ARROW_UP   0x2191
#define EFI_ARROW_DOWN 0x2193

//*******************************************************
// Attributes
//*******************************************************
#define EFI_BLACK                0x00
#define EFI_BLUE                 0x01
#define EFI_GREEN                0x02
#define EFI_CYAN                 0x03
#define EFI_RED                  0x04
#define EFI_ZIRCON               0x05
#define EFI_BROWN                0x06
#define EFI_LIGHTGRAY            0x07
#define EFI_BRIGHT               0x08
#define EFI_DARKGRAY             0x08
#define EFI_LIGHTBLUE            0x09
#define EFI_LIGHTGREEN           0x0A
#define EFI_LIGHTCYAN            0x0B
#define EFI_LIGHTRED             0x0C
#define EFI_LIGHTZIRCON          0x0D
#define EFI_YELLOW               0x0E
#define EFI_WHITE                0x0F
#define EFI_BACKGROUND_BLACK     0x00
#define EFI_BACKGROUND_BLUE      0x10
#define EFI_BACKGROUND_GREEN     0x20
#define EFI_BACKGROUND_CYAN      0x30
#define EFI_BACKGROUND_RED       0x40
#define EFI_BACKGROUND_ZIRCON    0x50
#define EFI_BACKGROUND_BROWN     0x60
#define EFI_BACKGROUND_LIGHTGRAY 0x70

typedef struct efi_simple_text_output_protocol
{
    efi_api efi_status (*reset)(struct efi_simple_text_output_protocol *self, bool extended_verification);
    efi_api efi_status (*output_string)(struct efi_simple_text_output_protocol *self, ce_u16 *string);
    efi_api efi_status (*test_string)(struct efi_simple_text_output_protocol *self, ce_u16 *string);
    efi_api efi_status (*query_mode)(struct efi_simple_text_output_protocol *self, ce_usize mode_num, ce_usize *cols, ce_usize *rows);
    efi_api efi_status (*set_mode)(struct efi_simple_text_output_protocol *self, ce_usize mode_num);
    efi_api efi_status (*set_attribute)(struct efi_simple_text_output_protocol *self, ce_usize attribute);
    efi_api efi_status (*clear_screen)(struct efi_simple_text_output_protocol *self);
    efi_api efi_status (*set_cursor_position)(struct efi_simple_text_output_protocol *self, ce_usize col, ce_usize row);
    efi_api efi_status (*enable_cursor)(struct efi_simple_text_output_protocol *self, bool visible);
    efi_simple_text_output_mode *mode;
} efi_simple_text_output_protocol;
