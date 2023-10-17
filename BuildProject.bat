@echo off
set arg_1 = %1
@REM echo -- Building library Zipper
@REM git clone --recursive https://github.com/sebastiandev/zipper.git
@REM cd src
@REM mkdir lib
@REM cd ..
@REM cd zipper
@REM mkdir build
@REM cmake  .
@REM cmake --build .
@REM rename "libstaticZipper.a" "libZipper.a"
@REM Xcopy *.a  ..\src\lib\  /Y
@REM cd ..
@REM rmdir .\zipper /s /q
@REM echo - Zipper successfully builded
@REM echo ==================================
echo -- Building project
if exist .\build\Windows (
    if ERRORLEVEL 0 (
        g++ -o .\build\Windows\Client.exe .\src\Client.cpp -lurlmon -I ..\..\include  -L ..\..\lib\ -I .\src\include -L .\src\lib -lws2_32 -static -static-libgcc -static-libstdc++  -lwinmm -std=c++20
        echo -- Build of project finished
    ) else (
        echo -- Error in project build.
    )
) else (
    mkdir build
    cd build
    mkdir Windows
    cd ..
    if ERRORLEVEL 0 (
        g++ -o .\build\Windows\Client.exe .\src\Client.cpp -lurlmon -I ..\..\include  -L ..\..\lib\ -I .\src\include -L .\src\lib -lws2_32 -static -static-libgcc -static-libstdc++  -lwinmm -std=c++20
        echo -- Build of project finished
    ) else (
        echo -- Error in project build.
    )
)

echo ==================================

if arg_1=="-autostart" or arg_1=="-AutoStart" or arg_1=="-Autostart" (
   echo -- Running ".\build\Windows\Client.exe"
   cd build
   cd Windows
   Client.exe
)