//
// Created by delbek on 6/22/2024.
//

#ifndef PROCESSMEMORYMANIPULATOR_MEMORYMANIPULATOR_H
#define PROCESSMEMORYMANIPULATOR_MEMORYMANIPULATOR_H

#include <string>
#include <vector>


struct ConsecutivePages
{
    char* pageAddress;
    unsigned long long size;
    int flags;
};

enum PAGE_FLAGS
{
    NONE = 0,
    READ		= 0b0001,
    WRITE		= 0b0010,
    EXECUTE 	= 0b0100,
    PAGE_FLAGS_END = 0
};


class MemoryManipulator
{
public:
    typedef unsigned long long ULL;
    typedef unsigned long UL;

    MemoryManipulator(std::string processName);
    virtual ~MemoryManipulator() = default;

    MemoryManipulator(const MemoryManipulator& other) = delete;
    MemoryManipulator(MemoryManipulator&& other) = delete;
    MemoryManipulator& operator=(const MemoryManipulator& other) = delete;
    MemoryManipulator& operator=(MemoryManipulator&& other) = delete;

    virtual void getAllPages(std::vector<ConsecutivePages>& pages) = 0;

    virtual ULL readProcessMemory(void* address) = 0;

    virtual void writeProcessMemory(void* address, const ULL& value) = 0;

private:
    std::string m_ProcessName;
};


#endif //PROCESSMEMORYMANIPULATOR_MEMORYMANIPULATOR_H
