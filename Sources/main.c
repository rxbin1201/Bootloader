/*

    main.c - 30.12.22

*/

// Import libraries
#include <efi.h>
#include <efilib.h>
#include <Protocols/gop.h>
#include <File/volume.h>
#include <File/file.h>
#include <Images/png.h>
#include <Images/tga.h>
#include <config.h>


EFI_STATUS
EFIAPI
efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {

    // Initialize the UEFI
    InitializeLib(ImageHandle, SystemTable);

    // Declare variables
    EFI_STATUS Status;
    UINT8 *ImageTgaBuffer;
    UINTN ImageTgaBufferSize;

    Status = InitGraphicsOutputProtocol();
    if(EFI_ERROR(Status)) {
        Print(L"Failed to init graphics out protocol! Reason: %r\n", Status);
    }

    Status = InitBootConfig(ImageHandle);
    if(!EFI_ERROR(Status)) {
        Print(L"Config init!\n");
        //Print(L"Kernel path : %.*a\n", GetConfigValue("KERNEL_PATH="))
    } else {
        Print(L"Error init boot.cfg! Reason: %r\n", Status);
    }

    Print(L"Check tga header...\n");

    ImageTgaBuffer = LoadTgaImage(ImageHandle, L"image.tga");
    if(ImageTgaBuffer != NULL) {
        Print(L"Tga image header loaded successfully!\n");

        ImageTgaBufferSize = sizeof(ImageTgaBuffer);

        DrawTgaImage(ImageTgaBuffer, ImageTgaBufferSize);
    }


    /*Status = DrawPNGImage(ImageHandle, L"image.png");
    if(EFI_ERROR(Status)) {
        Print(L"Error png! Reason: %r\n", Status);
    }*/

    //Print(L"TEST!");

    while(1){};

    return EFI_SUCCESS;
}