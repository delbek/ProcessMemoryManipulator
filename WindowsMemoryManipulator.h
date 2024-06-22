//
// Created by delbek on 6/22/2024.
//

#ifndef PROCESSMEMORYMANIPULATOR_WINDOWSMEMORYMANIPULATOR_H
#define PROCESSMEMORYMANIPULATOR_WINDOWSMEMORYMANIPULATOR_H

#include "MemoryManipulator.h"
#include "Windows.h"


class WindowsMemoryManipulator: public MemoryManipulator
{
public:
    WindowsMemoryManipulator(std::string processName);
    virtual ~WindowsMemoryManipulator();

    virtual void getAllPages(std::vector<ConsecutivePages>& pages) final;

    virtual ULL readProcessMemory(void* address) final;

    virtual void writeProcessMemory(void* address, const ULL& value) final;

private:
    HANDLE m_Handle;
};


#endif //PROCESSMEMORYMANIPULATOR_WINDOWSMEMORYMANIPULATOR_H
