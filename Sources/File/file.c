/*

    file.c - 31.12.22

*/

// Import libraries
#include <File/file.h>

UINT64 FileSize(EFI_FILE_HANDLE FileHandle) {
    
    // Declare variables
    UINT64 ReturnValue;
    EFI_FILE_INFO *FileInfo;

    // Get the file size
    FileInfo = LibFileInfo(FileHandle);
    ReturnValue = FileInfo->FileSize;

    FreePool(FileInfo);

    return ReturnValue;
}

UINT8 *ReadFile(EFI_FILE_HANDLE Volume, CHAR16 *FileName) {

    // Declare variables
    EFI_STATUS Status;
    EFI_FILE_HANDLE FileHandle;
    UINT64 ReadSize;
    UINT8 *Buffer;

    // Open the file
    Status = uefi_call_wrapper(
        Volume->Open,
        5,
        Volume,
        &FileHandle,
        FileName,
        EFI_FILE_MODE_READ,
        EFI_FILE_READ_ONLY | EFI_FILE_HIDDEN | EFI_FILE_SYSTEM
    );
    if(EFI_ERROR(Status)) {
        Print(L"Could not open file! Reason: %r\n", Status);
    }

    // Read the contents of the file
    ReadSize = FileSize(FileHandle);
    Buffer = AllocatePool(ReadSize);

    Status = uefi_call_wrapper(
        FileHandle->Read,
        3,
        FileHandle,
        &ReadSize,
        Buffer
    );
    if(EFI_ERROR(Status)) {
        Print(L"Could not read file! Reason: %r\n", Status);
    }

    // Close the file
    Status = uefi_call_wrapper(
        FileHandle->Close,
        1,
        FileHandle
    );
    if(EFI_ERROR(Status)) {
        Print(L"Could not close file! Reason: %r\n", Status);
    }

    Print(L"Test:\n %a\n", Buffer);

    return Buffer;
} // End of file