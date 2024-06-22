#include <iostream>
#include "WindowsMemoryManipulator.h"


int main()
{
    WindowsMemoryManipulator* manipulator = new WindowsMemoryManipulator("chrome.exe");

    std::vector<ConsecutivePages> pages;
    manipulator->getAllPages(pages);
    std::cout << pages.size() << std::endl;

    delete manipulator;

    return 0;
}
