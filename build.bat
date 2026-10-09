@echo off
setlocal
cd /d "%~dp0"

if not exist build mkdir build

echo [1/4] Compiling int_vector.c...
gcc -std=c11 -Wall -Wextra -Wpedantic -g -Iinclude -c src\int_vector.c -o build\int_vector.o
if errorlevel 1 exit /b 1

echo [2/4] Creating static library...
ar rcs build\libcstl.a build\int_vector.o
if errorlevel 1 exit /b 1

echo [3/4] Compiling tests and example...
gcc -std=c11 -Wall -Wextra -Wpedantic -g -Iinclude tests\test_int_vector.c build\libcstl.a -o build\test_int_vector.exe
if errorlevel 1 exit /b 1
gcc -std=c11 -Wall -Wextra -Wpedantic -g -Iinclude examples\vector_example.c build\libcstl.a -o build\vector_example.exe
if errorlevel 1 exit /b 1

echo [4/4] Running tests...
build\test_int_vector.exe
if errorlevel 1 exit /b 1

echo Build and tests completed successfully.
exit /b 0
