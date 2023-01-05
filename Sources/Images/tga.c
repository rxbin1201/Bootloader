/*

    tga.c - 02.01.23

*/

// Import libraries
#include <Images/tga.h>

// TgaParse funciton from https://wiki.osdev.org/Loading_Icons
UINT32 *TgaParse(unsigned char *ptr, int size) {

    unsigned int *data;
    int i, j, k, x, y, w = (ptr[13] << 8) + ptr[12], h = (ptr[15] << 8) + ptr[14], o = (ptr[11] << 8) + ptr[10];
    int m = ((ptr[1]? (ptr[7]>>3)*ptr[5] : 0) + 18);
 
    if(w<1 || h<1) return NULL;

    Print(L"Tga1\n");
 
    data = (unsigned int*)malloc((w*h+2)*sizeof(unsigned int));
    if(!data) {
        Print(L"Error: Unable to allocate memory with malloc\n");
        return NULL;
    }
 
    Print(L"Tga2\n");

    switch(ptr[2]) {
        case 1:
            if(ptr[6]!=0 || ptr[4]!=0 || ptr[3]!=0 || (ptr[7]!=24 && ptr[7]!=32)) { free(data); return NULL; }
            for(y=i=0; y<h; y++) {
                k = ((!o?h-y-1:y)*w);
                for(x=0; x<w; x++) {
                    j = ptr[m + k++]*(ptr[7]>>3) + 18;
                    data[2 + i++] = ((ptr[7]==32?ptr[j+3]:0xFF) << 24) | (ptr[j+2] << 16) | (ptr[j+1] << 8) | ptr[j];
                }
            }
            break;
        case 2:
            if(ptr[5]!=0 || ptr[6]!=0 || ptr[1]!=0 || (ptr[16]!=24 && ptr[16]!=32)) { free(data); return NULL; }
            for(y=i=0; y<h; y++) {
                j = ((!o?h-y-1:y)*w*(ptr[16]>>3));
                for(x=0; x<w; x++) {
                    data[2 + i++] = ((ptr[16]==32?ptr[j+3]:0xFF) << 24) | (ptr[j+2] << 16) | (ptr[j+1] << 8) | ptr[j];
                    j += ptr[16]>>3;
                }
            }
            break;
        case 9:
            if(ptr[6]!=0 || ptr[4]!=0 || ptr[3]!=0 || (ptr[7]!=24 && ptr[7]!=32)) { free(data); return NULL; }
            y = i = 0;
            for(x=0; x<w*h && m<size;) {
                k = ptr[m++];
                if(k > 127) {
                    k -= 127; x += k;
                    j = ptr[m++]*(ptr[7]>>3) + 18;
                    while(k--) {
                        if(!(i%w)) { i=((!o?h-y-1:y)*w); y++; }
                        data[2 + i++] = ((ptr[7]==32?ptr[j+3]:0xFF) << 24) | (ptr[j+2] << 16) | (ptr[j+1] << 8) | ptr[j];
                    }
                } else {
                    k++; x += k;
                    while(k--) {
                        j = ptr[m++]*(ptr[7]>>3) + 18;
                        if(!(i%w)) { i=((!o?h-y-1:y)*w); y++; }
                        data[2 + i++] = ((ptr[7]==32?ptr[j+3]:0xFF) << 24) | (ptr[j+2] << 16) | (ptr[j+1] << 8) | ptr[j];
                    }
                }
            }
            break;
        case 10:
            if(ptr[5]!=0 || ptr[6]!=0 || ptr[1]!=0 || (ptr[16]!=24 && ptr[16]!=32)) { free(data); return NULL; }
            y = i = 0;
            for(x=0; x<w*h && m<size;) {
                k = ptr[m++];
                if(k > 127) {
                    k -= 127; x += k;
                    while(k--) {
                        if(!(i%w)) { i=((!o?h-y-1:y)*w); y++; }
                        data[2 + i++] = ((ptr[16]==32?ptr[m+3]:0xFF) << 24) | (ptr[m+2] << 16) | (ptr[m+1] << 8) | ptr[m];
                    }
                    m += ptr[16]>>3;
                } else {
                    k++; x += k;
                    while(k--) {
                        if(!(i%w)) { i=((!o?h-y-1:y)*w); y++; }
                        data[2 + i++] = ((ptr[16]==32?ptr[m+3]:0xFF) << 24) | (ptr[m+2] << 16) | (ptr[m+1] << 8) | ptr[m];
                        m += ptr[16]>>3;
                    }
                }
            }
            break;
        default:
            free(data); return NULL;
    }

    Print(L"Tga3\n");

    data[0] = w;
    data[1] = h;
    return data;
}

UINT8 *LoadTgaImage(EFI_HANDLE ImageHandle, CHAR16 *TgaFileName) {

    // Declare variables
    EFI_STATUS Status;
    UINT8 *TgaBuffer;
    TGA_HEADER *TgaHeader;
    EFI_FILE_HANDLE Volume;

    // Load file
    Volume = GetVolume(ImageHandle);

    TgaBuffer = ReadFile(Volume, TgaFileName);

    TgaHeader = (TGA_HEADER *)TgaBuffer;
    if(TgaHeader->ImageType != TGA_UNCOMPRESSED_RGB) {
        Print(L"The Tga image type is unsupported!\n");
        return NULL;
    }

    return TgaBuffer;   
}

VOID DrawTgaImage(UINT8 *FinalTgaBuffer, UINTN TgaImageSize) {

    // Declare variables
    EFI_STATUS Status;
    EFI_GRAPHICS_OUTPUT_PROTOCOL *GraphicsOutput = GetGop();
    UINT32 *TgaImageData;
    UINTN Width, Height;

    Print(L"Test4\n");

    // Parse the tga image
    TgaImageData = TgaParse(FinalTgaBuffer, TgaImageSize);
    if(TgaImageData == NULL) {
        Print(L"Failed to parse tga image!\n");
    }

    Print(L"Test5\n");

    Width = TgaImageData[0];
    Height = TgaImageData[1];

    Print(L"Test3\n");

    Status = DrawFinalImageToScreen(GraphicsOutput, TgaImageData + 2, Width, Height);
    if(EFI_ERROR(Status)) {
        Print(L"Failed to draw tga image! Reason: %r\n", Status);
    }

}

EFI_STATUS DrawFinalImageToScreen(EFI_GRAPHICS_OUTPUT_PROTOCOL *GraphicsOutput, UINT32 *ImageData, UINTN Width, UINTN Height) {

    // Declare variables
    EFI_STATUS Status;
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL *Blt;
    UINTN ImageSize;
    UINTN x, y;

    // Calculate the size of the image in pixels
    ImageSize = Width * Height;

    // Allocate a buffer for the image pixels
    Blt = AllocatePool(ImageSize * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));
    if(Blt == NULL) {
        return EFI_OUT_OF_RESOURCES;
    }

    Print(L"Test1\n");

    // Convert image data from 32-bit ARGB format to EFI_GRAPHICS_OUTPUT_BLT_PIXEL format
    for(y = 0; y < Height; y++) {
        for(x = 0; x < Width; x++) {
            Blt[y * Width + x].Blue = (ImageData[y * Width + x] & 0x000000FF) >> 0;
            Blt[y * Width + x].Green = (ImageData[y * Width + x] & 0x0000FF00) >> 8;
            Blt[y * Width + x].Red = (ImageData[y * Width + x] & 0x00FF0000) >> 16;
            Blt[y * Width + x].Reserved = (ImageData[y * Width + x] & 0xFF000000) >> 24;
        }
    }

    Print(L"Test2\n");

    // Draw the image to the screen
    Status = uefi_call_wrapper(
        GraphicsOutput->Blt,
        8,
        GraphicsOutput,
        Blt,
        EfiBltBufferToVideo,
        0, 0,
        0, 0,
        Width, Height,
        0
    );
    if(EFI_ERROR(Status)) {
        FreePool(Blt);
        return Status;
    }

    // Free the buffer
    FreePool(Blt);

    return EFI_SUCCESS;
} // End of file