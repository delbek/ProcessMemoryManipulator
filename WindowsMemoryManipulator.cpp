//
// Created by delbek on 6/22/2024.
//

#include "WindowsMemoryManipulator.h"
#include "Windows.h"
#include <tchar.h>
#include <psapi.h>
#include <stdexcept>
#include <iostream>


WindowsMemoryManipulator::WindowsMemoryManipulator(std::string processName)
:   MemoryManipulator(processName)
{

    UL activeProcesses[1024];
    UL sizeRead;
    EnumProcesses(activeProcesses, sizeof(activeProcesses), &sizeRead);

    UL numberOfProcesses = sizeRead / sizeof(UL);

    TCHAR currentProcessName[MAX_PATH] = TEXT("<unknown>");
    for (int i = 0; i < numberOfProcesses; ++i)
    {
        m_Handle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION,
                                       FALSE,
                                       activeProcesses[i]);

        if (m_Handle != NULL)
        {
            HMODULE module;
            if (EnumProcessModules(m_Handle, &module, sizeof(module), &sizeRead))
            {
                GetModuleBaseName(m_Handle, module, currentProcessName, sizeof(currentProcessName)/sizeof(TCHAR));
            }
        }

        if (currentProcessName == processName)
        {
            std::cout << "PROCESS: " << currentProcessName << " FOUND!" << std::endl;
            break;
        }

        CloseHandle(m_Handle);
    }
}

WindowsMemoryManipulator::~WindowsMemoryManipulator()
{
    CloseHandle(m_Handle);
}

void WindowsMemoryManipulator::getAllPages(std::vector<ConsecutivePages>& pages)
{
    MEMORY_BASIC_INFORMATION memoryInformation;

    char* address = 0x0;
    for (;;)
    {
        int flags = PAGE_FLAGS::NONE;
        bool ret = VirtualQueryEx(m_Handle, (void*) address, &memoryInformation, sizeof(MEMORY_BASIC_INFORMATION));

        if (!ret)
        {
            throw std::runtime_error("Error occured while reading virtual pages");
        }

        address = (char*) memoryInformation.BaseAddress + memoryInformation.RegionSize;

        if (memoryInformation.State == MEM_COMMIT)
        {
            if (memoryInformation.Protect & PAGE_READONLY)
            {
                flags |= PAGE_FLAGS::READ;
            }

            if (memoryInformation.Protect & PAGE_READWRITE)
            {
                flags |= (PAGE_FLAGS::READ | PAGE_FLAGS::WRITE);
            }

            if (memoryInformation.Protect & PAGE_EXECUTE)
            {
                flags |= PAGE_FLAGS::EXECUTE;
            }

            if (memoryInformation.Protect & PAGE_EXECUTE_READ)
            {
                flags |= (PAGE_FLAGS::EXECUTE | PAGE_FLAGS::READ);
            }

            if (memoryInformation.Protect & PAGE_EXECUTE_READWRITE)
            {
                flags |= (PAGE_FLAGS::EXECUTE | PAGE_FLAGS::READ | PAGE_FLAGS::WRITE);
            }

            if (memoryInformation.Protect & PAGE_EXECUTE_WRITECOPY)
            {
                flags |= (PAGE_FLAGS::EXECUTE | PAGE_FLAGS::READ);
            }

            if (memoryInformation.Protect & PAGE_WRITECOPY)
            {
                flags |= PAGE_FLAGS::READ;
            }

            ConsecutivePages consecutivePages;
            consecutivePages.flags = flags;
            consecutivePages.pageAddress = (char*) memoryInformation.BaseAddress;
            consecutivePages.size = memoryInformation.RegionSize;
            pages.emplace_back(consecutivePages);
        }
        else
        {
            break;
        }
    }
}

MemoryManipulator::ULL WindowsMemoryManipulator::readProcessMemory(void *address)
{

}

void WindowsMemoryManipulator::writeProcessMemory(void *address, const MemoryManipulator::ULL &value)
{

}
