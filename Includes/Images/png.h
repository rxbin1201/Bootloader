/*

    png.h - 05.01.23

*/

#ifndef __PNG_H
#define __PNG_H

// Import libraries
#include <efi.h>
#include <efilib.h>
#include <string.h>
#include <stdlib.h>
#include <File/file.h>
#include <File/volume.h>
#include <Protocols/gop.h>

EFI_STATUS DrawPNGImage(EFI_HANDLE ImageHandle, CHAR16 *FileName);

#endif // End of file