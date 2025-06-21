#include <windows.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc > 1 && strcmp(argv[1], "child") == 0) {
        // Child process block
        printf("Child Process:\n");
        printf("Process ID: %lu\n", GetCurrentProcessId());
        printf("Note: Windows does not directly support getppid()\n");
    } else {
        // Parent process block
        STARTUPINFO si = { sizeof(si) };
        PROCESS_INFORMATION pi;

        // Create child process by running the same program with "child" argument
        if (!CreateProcess(NULL, "process.exe child", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
            printf("CreateProcess failed (%lu).\n", GetLastError());
            return 1;
        }

        printf("Parent Process:\n");
        printf("Process ID: %lu\n", GetCurrentProcessId());

        // Wait for the child process to finish
        WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }

    return 0;
}

