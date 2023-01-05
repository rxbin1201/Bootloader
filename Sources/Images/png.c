/*

    png.c - 05.01.23

*/

// Import libraries
#include <Images/png.h>

EFI_STATUS DrawPNGImage(EFI_HANDLE ImageHandle, CHAR16 *PngFileName) {

    // Declare variables
    EFI_STATUS Status;
    EFI_GRAPHICS_OUTPUT_PROTOCOL *GraphicsOutput = GetGop();
    EFI_FILE_HANDLE Volume;
    UINT8 *PngBuffer;
    UINT64 PngBufferSize;
    UINT32 *Data;
    INT32 w, h, l;
    stbi__context s;
    stbi__result_info ri;

    Volume = GetVolume(ImageHandle);
    PngBuffer = ReadFile(Volume, PngFileName);
    PngBufferSize = sizeof(PngBuffer);

    ri.bits_per_channel = 8;
    s.read_from_callbacks = 0;
    s.img_buffer = s.img_buffer_original = PngBuffer;
    s.img_buffer = s.img_buffer_original_end = PngBuffer + PngBufferSize;
    Data = (UINT32*)stbi__png_load(&s, &w, &h, &l, 4, &ri);
    if(!Data) {
        Print(L"Unable to decode png: %s\n", stbi__g_failure_reason);
        return EFI_LOAD_ERROR;
    }

    // PNG is RGBA but UEFI needs BGRA
    if(GraphicsOutput->Mode->Info->PixelFormat == PixelBlueGreenRedReserved8BitPerColor || (GraphicsOutput->Mode->Info->PixelFormat == PixelBitMask && GraphicsOutput->Mode->Info->PixelInformation.BlueMask != 0xFF0000)) {
        for(l = 0; l < w * h; l++) {
            Data[l] = ((Data[l] & 0xFF) << 16) | (Data[l] & 0xFF00) | ((Data[l] >> 16) & 0xFF);
        }
    } 

    // Draw image
    Status = uefi_call_wrapper(
        GraphicsOutput->Blt,
        10,
        GraphicsOutput,
        Data,
        EfiBltBufferToVideo,
        0, 0,
        (GraphicsOutput->Mode->Info->HorizontalResolution - w) / 2,
        (GraphicsOutput->Mode->Info->VerticalResolution - h) / 2,
        w, h,
        0
    );
    if(EFI_ERROR(Status)) {
        Print(L"Unable to draw image! Reason: %r\n", Status);
        return Status;
    }

    // Free data and buffer
    FreePool(Data);
    FreePool(PngBuffer);

    return EFI_SUCCESS;
} // End of file