#pragma once

#define RTL_CONSTANT_STRING(s) { sizeof(s) - sizeof((s)[0]), sizeof(s), (PWSTR)s }

#define EFI_VARIABLE_NON_VOLATILE                          0x00000001
#define EFI_VARIABLE_BOOTSERVICE_ACCESS                    0x00000002
#define EFI_VARIABLE_RUNTIME_ACCESS                        0x00000004
#define EFI_VARIABLE_HARDWARE_ERROR_RECORD                 0x00000008
#define EFI_VARIABLE_AUTHENTICATED_WRITE_ACCESS            0x00000010
#define EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS 0x00000020
#define EFI_VARIABLE_APPEND_WRITE                          0x00000040
#define ATTRIBUTES (EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS)

namespace ntdll
{
	extern "C"
	{
		NTSYSAPI
		NTSTATUS
		NTAPI
		RtlAdjustPrivilege(
			_In_ ULONG Privilege,
			_In_ BOOLEAN Enable,
			_In_ BOOLEAN Client,
			_Out_ PBOOLEAN WasEnabled
		);

		NTSYSCALLAPI
		NTSTATUS
		NTAPI
		NtSetSystemEnvironmentValueEx(
			_In_ PUNICODE_STRING VariableName,
			_In_ LPGUID VendorGuid,
			_In_reads_bytes_opt_(ValueLength) PVOID Value,
			_In_ ULONG ValueLength,
			_In_ ULONG Attributes
		);
	}
}