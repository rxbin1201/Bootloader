/*

    gop.h - 01.01.23

*/

#ifndef __GOP_H
#define __GOP_H

// Import libraries
#include <efi.h>
#include <efilib.h>

EFI_GRAPHICS_OUTPUT_PROTOCOL *GetGop();
EFI_STATUS InitGraphicsOutputProtocol();

#endif // End of file