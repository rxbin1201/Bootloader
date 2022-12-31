/*

    volume.c - 31.12.22

*/

// Import libraries
#include <File/volume.h>

EFI_FILE_HANDLE GetVolume(EFI_HANDLE ImageHandle) {

    // Declare variables
    EFI_STATUS Status;
    EFI_LOADED_IMAGE *LoadedImage = NULL;
    EFI_GUID LoadedImageProtocol = EFI_LOADED_IMAGE_PROTOCOL_GUID;
    EFI_FILE_IO_INTERFACE *FileIOInterface;
    EFI_GUID SimpelFileSystemProtocol = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;
    EFI_FILE_HANDLE Volume;

    // Get the loaded image protocol
    Status = uefi_call_wrapper(
        BS->HandleProtocol,
        3,
        ImageHandle,
        &LoadedImageProtocol,
        (VOID **)&LoadedImage
    );
    if(EFI_ERROR(Status)) {
        Print(L"Could not get the loaded image protocol(LIP)! Reason: %r\n", Status);
    }

    // Get the volume handle
    Status = uefi_call_wrapper(
        BS->HandleProtocol,
        3,
        LoadedImage->DeviceHandle,
        &SimpelFileSystemProtocol,
        (VOID *)&FileIOInterface
    );
    if(EFI_ERROR(Status)) {
        Print(L"Could not get the volume handle! Reason: %r\n", Status);
    }

    Status = uefi_call_wrapper(
        FileIOInterface->OpenVolume,
        2,
        FileIOInterface,
        &Volume
    );
    if(EFI_ERROR(Status)) {
        Print(L"Could not open the volume! Reason: %r\n", Status);
    }

    return Volume;

} // End of file