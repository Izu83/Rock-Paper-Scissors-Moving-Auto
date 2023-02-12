@echo off

if "%1" == "compile" (
    g++ -IC:\\SFML-2.5.1\\include -c main.cpp -o main.o
) else if "%1" == "link" (
    g++ -I"C:\\SFML-2.5.1\\include" -L"C:\\SFML-2.5.1\\lib" main.o -o app.exe -lmingw32 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-main
) else if "%1" == "run" (
    start app.exe
) else if "%1" == "s" (
    g++ -IC:\\SFML-2.5.1\\include -c main.cpp -o main.o
    g++ -I"C:\\SFML-2.5.1\\include" -L"C:\\SFML-2.5.1\\lib" main.o -o app.exe -lmingw32 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-main   
    start app.exe
) else (
    echo Invalid command. Available commands: compile, link, run, s for doing all commands
)