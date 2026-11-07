#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
    // 1. Распределение виртуальной памяти процессу
    int* a;   
    const int size_a = 1000;  
    
    a = (int*)VirtualAlloc(
        NULL,
        size_a * sizeof(int),
        MEM_COMMIT,
        PAGE_READWRITE);
    if (!a)
    {
        cout << "Virtual allocation failed." << endl;
        return GetLastError();
    }
    cout << "Virtual memory address: " << a << endl;

    if (!VirtualFree(a, 0, MEM_RELEASE))
    {
        cout << "Memory release failed." << endl;
        return GetLastError();
    }


    // 2. Распределение виртуальной памяти по конкретному адресу
    LPVOID lp;
    const int size_lp = 1000;

    lp = VirtualAlloc(
        (LPVOID)0x00890002,
        size_lp,
        MEM_RESERVE | MEM_COMMIT,
        PAGE_READWRITE);
    if (!lp)
    {
        cout << "Virtual allocation failed." << endl;
        return GetLastError();
    }
    cout << "Virtual memory address: " << lp << endl;

    if (!VirtualFree(lp, 0, MEM_RELEASE))
    {
        cout << "Memory release failed." << endl;
        return GetLastError();
    }


    // 3. Резервирование и распределение виртуальной памяти
    LPVOID lpr, lpc;
    const int Kb = 1024;
    const int size_reserv = 100;

    lpr = VirtualAlloc(
        (LPVOID)0x00880000,
        size_reserv * Kb,
        MEM_RESERVE,
        PAGE_READWRITE);
    if (!lpr)
    {
        cout << "Virtual memory reservation failed." << endl;
        return GetLastError();
    }
    cout << "Virtual memory address: " << lpr << endl;

    lpc = VirtualAlloc(
        (LPVOID)0x00888000,
        Kb,
        MEM_COMMIT,
        PAGE_READWRITE);
    if (!lpc)
    {
        cout << "Virtual memory allocation failed." << endl;
        return GetLastError();
    }
    cout << "Virtual memory address: " << lpc << endl;

    if (!VirtualFree(lpc, Kb, MEM_DECOMMIT))
    {
        cout << "Memory decommit failed." << endl;
        return GetLastError();
    }

    if (!VirtualFree(lpr, 0, MEM_RELEASE))
    {
        cout << "Memory release failed." << endl;
        return GetLastError();
    }


    // 4. Блокирование и разблокирование виртуальных страниц
    LPVOID vm; 
    SIZE_T size_block = 4096; 

    vm = VirtualAlloc(
        NULL,
        size_block,
        MEM_COMMIT,
        PAGE_READWRITE);
    if (!vm)
    {
        cout << "Virtual allocation failed." << endl;
        return GetLastError();
    }

    if (!VirtualLock(vm, size_block))
    {
        cout << "Virtual lock failed." << endl;
        return GetLastError();
    }

    if (!VirtualUnlock(vm, size_block))
    {
        cout << "Virtual unlock failed." << endl;
        return GetLastError();
    }

    if (!VirtualFree(vm, 0, MEM_RELEASE))
    {
        cout << "Memory release failed." << endl;
        return GetLastError();
    }

    return 0;
}
