#pragma once
#include "my_lib_export.h"

namespace src
{
    LIBRARY_API int add(int a, int b);
    LIBRARY_API int subtract(int a, int b);
    LIBRARY_API int multiply(int a, int b);
    LIBRARY_API int divide(int a, int b);
}