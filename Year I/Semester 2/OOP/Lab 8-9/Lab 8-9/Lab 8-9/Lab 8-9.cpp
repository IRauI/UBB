// lab6-7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "ActivityRepo.h"
#include "Validator.h"
#include "ActivityStore.h"
#include "UI.h"
#include <stdlib.h>
#include <crtdbg.h>

int main()
{
    testeRepo();
    testValidator();
    testCtr();
    run();

    _CrtDumpMemoryLeaks();
}

