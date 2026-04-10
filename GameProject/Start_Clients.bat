@echo off
title Client Spawner

:: Prompt the user for input
set /p CLIENT_COUNT="Enter the number of clients to invoke: "

echo Spawning %CLIENT_COUNT% clients...

:: Loop from 1 up to the user's input number
for /L %%i in (1, 1, %CLIENT_COUNT%) do (
    echo Launching Client %%i...
    
    :: Run the executable from the Build\bin directory
    start "" "Build\bin\GameProject-Debug-x64.exe" --client
)

echo All %CLIENT_COUNT% clients invoked!
pause