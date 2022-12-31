/*

    main.c - 30.12.22

*/

// Import libraries
#include <efi.h>
#include <efilib.h>
#include <File/volume.h>
#include <File/file.h>
//#include <string.h>


EFI_STATUS
EFIAPI
efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {

    // Initialize the UEFI
    InitializeLib(ImageHandle, SystemTable);

    // Declare variables
    EFI_STATUS Status;
    EFI_FILE_HANDLE Volume = GetVolume(ImageHandle);
    CHAR16 *FileName = L"boot.cfg";

    UINT8 *Buffer = ReadFile(Volume, FileName);

    Print(L"File content:\n%a\n", Buffer);

    // Print file content
    //Print(L"File:\n%a\n\n", Buffer); 

    // Print config values
    /*UINT8 *Line = Buffer;
    UINTN LineSize = 0;

    UINT8 *KernelPathValue = NULL;
    UINT8 *TimeOutValue = NULL;
    UINT8 *ThemeValue = NULL;

    // Read the config line by line
    while(Line < Buffer + ReadSize) {

        // Find the end of the line
        while(Line[LineSize] != '\n' && Line + LineSize < Buffer + ReadSize) {
            LineSize++;
        }

        // Check if the line starts with a #
        if(Line[0] != '#') {

            // Declare variables
            UINTN KernelPathSize = strlen("KERNEL_PATH=");
            UINTN TimeOutSize = strlen("TIMEOUT=");
            UINTN ThemeSize = strlen("THEME=");
            UINTN i;

            // Check for KERNEL_PATH
            for(i = 0; i < KernelPathSize; i++) {
                if(Line[i] != "KERNEL_PATH="[i]) {
                    break;
                }
            }

            if(i == KernelPathSize) {
                // Store the KERNEL_PATH value in the variable
                KernelPathValue = AllocatePool(LineSize - KernelPathSize + 1);

                if(KernelPathValue == NULL) {
                    // Error allocating memory
                    Print(L"Error allocating memory for KERNEL_PATH value!\n");
                }

                CopyMem(KernelPathValue, Line + KernelPathSize, LineSize - KernelPathSize);
                KernelPathValue[LineSize - KernelPathSize] = '\0';

                //Print(L"%.*a\n", LineSize - KernelPathSize, Line + KernelPathSize);
                //Print(L"%.*a\n", LineSize, Line);
            }
            
            
            // Check for TIMEOUT
            for(i = 0; i < TimeOutSize; i++) {
                if(Line[i] != "TIMEOUT="[i]) {
                    break;
                }
            }

            if(i == TimeOutSize) {
                // Store the TIMEOUT value in the variable
                TimeOutValue = AllocatePool(LineSize - TimeOutSize + 1);

                if(TimeOutValue == NULL) {
                    // Error allocating memory
                    Print(L"Error allocating memory for TIMEOUT value!\n");
                }

                CopyMem(TimeOutValue, Line + TimeOutSize, LineSize - TimeOutSize);
                TimeOutValue[LineSize - TimeOutSize] = '\0';
                //Print(L"%.*a\n", LineSize, Line);
            }

            // Check for THEME
            for(i = 0; i < ThemeSize; i++) {
                if(Line[i] != "THEME="[i]) {
                    break;
                }
            }

            if(i == ThemeSize) {
                // Store the THEME value in the variable
                ThemeValue = AllocatePool(LineSize - ThemeSize + 1);

                if(TimeOutValue == NULL) {
                    // Error allocating memory
                    Print(L"Error allocating memory for THEME value!\n");
                }

                CopyMem(ThemeValue, Line + ThemeSize, LineSize - ThemeSize);
                ThemeValue[LineSize - ThemeSize] = '\0';
                //Print(L"%.*a\n", LineSize, Line);
            }

            //Print the line if it does not start with a #
            //Print(L"%.*a\n", LineSize, Line);
        }



        // Move to the next line
        Line += LineSize + 1;
        LineSize = 0;
    }*/

    /*if(KernelPathValue != NULL) {
        Print(L"KERNEL_PATH value: %a\n", KernelPathValue);
    } else {
        Print(L"KERNEL_PATH value not found!\n");
    }

    if(KernelPathValue != NULL) {
        FreePool(KernelPathValue);
    }

    if(TimeOutValue != NULL) {
        Print(L"TIMEOUT value: %a\n", TimeOutValue);
    } else {
        Print(L"TIMEOUT value not found!\n");
    }

    if(TimeOutValue != NULL) {
        FreePool(TimeOutValue);
    }

    if(ThemeValue != NULL) {
        Print(L"THEME value: %a\n", ThemeValue);
    } else {
        Print(L"THEME value not found!\n");
    }

    if(ThemeValue != NULL) {
        FreePool(ThemeValue);
    }*/

    // Print Hello, World!
    Print(L"Hello, World!\n");

    while(1){};

    return EFI_SUCCESS;
}