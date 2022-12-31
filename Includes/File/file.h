/*

    file.h - 31.12.22

*/

#ifndef __FILE_H
#define __FILE_H

// Import libraries
#include <efi.h>
#include <efilib.h>

// Declare function
UINT64 FileSize(EFI_FILE_HANDLE FileHandle);
UINT8 *ReadFile(EFI_FILE_HANDLE Volume, CHAR16 *FileName);

#endif // End of file