@echo off
REM Configure CMake for a test build using VS 2026 generator and Win32 platform.
call "C:\Program Files\Microsoft Visual Studio\18\Community\VC\Auxiliary\Build\vcvars64.bat" >nul
if errorlevel 1 (
    echo vcvars64 failed
    exit /b 1
)
"C:\Program Files\Microsoft Visual Studio\18\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" -S . -B build-test -G "Visual Studio 18 2026" -A Win32 -DSFML_DIR="C:/SFML/lib/cmake/SFML"
