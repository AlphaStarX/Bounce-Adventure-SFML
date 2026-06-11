
@echo off
call "C:\Program Files\Microsoft Visual Studio\18\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
"C:\Program Files\Microsoft Visual Studio\18\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" -S C:\Users\bhavi\Documents\Test -B C:\Users\bhavi\Documents\Test\build-msvc -A x64 -D SFML_DIR=C:\SFML\lib\cmake\SFML
if %errorlevel% neq 0 exit /b %errorlevel%
"C:\Program Files\Microsoft Visual Studio\18\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" --build C:\Users\bhavi\Documents\Test\build-msvc --config Debug

