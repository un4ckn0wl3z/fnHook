#include <Windows.h>
#include <stdio.h>
#include <Detours/detours.h>

decltype(::MessageBox)* OriginalMessageBox = ::MessageBox;

int WINAPI HookMessageBox(
	_In_opt_ HWND    hWnd,
	_In_opt_ LPCTSTR lpText,
	_In_opt_ LPCTSTR lpCaption,
	_In_     UINT    uType
)
{
	printf("=========== HookMessageBox ===========\n");
	printf("Title: %ws\n", lpText);
	printf("Message: %ws\n", lpCaption);
	printf("======================================\n");

	lpText = L"Hooked!";

	return OriginalMessageBox(hWnd, lpText, lpCaption, uType);
}

void InstallHooks()
{
	DetourTransactionBegin();
	DetourAttach((PVOID*)&OriginalMessageBox, HookMessageBox);
	DetourTransactionCommit();
}

int main()
{
	InstallHooks();
	::MessageBox(NULL, L"MessageBox", L"Hello!", MB_OK);
	return 0;
}