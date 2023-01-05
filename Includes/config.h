/*

    config.h - 01.01.23

*/

#ifndef __CONFIG_H
#define __CONFIG_H

// Import libraries
#include <efi.h>
#include <efilib.h>
#include <File/volume.h>
#include <File/file.h>

EFI_STATUS InitBootConfig(EFI_HANDLE ImageHandle);

#endif // End of file