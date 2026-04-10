@echo off
title Engine Server
echo Booting Game Engine as Server...

:: Run the executable from the Build\bin directory
start "" "Build\bin\GameProject-Debug-x64.exe" --server

echo Server started!