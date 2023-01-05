/*

    gop.c - 01.01.23

*/

// Import libraries
#include <Protocols/gop.h>

EFI_GRAPHICS_OUTPUT_PROTOCOL *GetGop() {

    // Declare variables
    EFI_STATUS Status;
    EFI_GRAPHICS_OUTPUT_PROTOCOL *ReturnGop;

    // Locate the graphics output protocol(GOP)
    Status = uefi_call_wrapper(
        BS->LocateProtocol,
        3,
        &GraphicsOutputProtocol,
        NULL,
        (VOID **)&ReturnGop
    );
    if(EFI_ERROR(Status)) {
        Print(L"Error locating graphics output protocol! Reason: %r\n", Status);
    }

    return ReturnGop;
}

EFI_STATUS InitGraphicsOutputProtocol() {

    // Declare variables
    EFI_STATUS Status;
    EFI_GRAPHICS_OUTPUT_PROTOCOL *Gop;
    EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *Info;
    UINT32 ScreenWidth, ScreenHeight;
    UINTN GopMaxMode;
    UINTN MaxResolution;
    UINTN Resolution;
    UINTN GopSize;

    Gop = GetGop();

    // Get the screen width and screen height
    ScreenWidth = Gop->Mode->Info->HorizontalResolution;
    ScreenHeight = Gop->Mode->Info->VerticalResolution;

    Print(L"Width: %dpx\nHeight: %dpx\n", ScreenWidth, ScreenHeight);

    return EFI_SUCCESS;
} // End of file

