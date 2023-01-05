/*

    config.c - 01.01.23

*/

#define CONFIG_FILE L"boot.cfg"

// Import libraries
#include <config.h>

// Declare variables
UINT8 *CurrentConfigBuffer;

EFI_STATUS InitBootConfig(EFI_HANDLE ImageHandle) {
    
    // Declare variables
    EFI_FILE_HANDLE Volume;
    CHAR16 *ConfigFileName = CONFIG_FILE;

    // Get the volume
    Volume = GetVolume(ImageHandle);

    // Read config file into buffer
    CurrentConfigBuffer = ReadFile(Volume, ConfigFileName);
    if(CurrentConfigBuffer == NULL) {
        return EFI_NOT_FOUND;
    }

    Print(L"[TEST] Print out config file:\n%a\n", CurrentConfigBuffer);

    return EFI_SUCCESS;
} // End of file