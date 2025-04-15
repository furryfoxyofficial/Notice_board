@echo off
setlocal

REM Get the file address from the command line argument
set "fileAddress=%~1"

REM Check if PowerPoint is running
tasklist /FI "IMAGENAME eq POWERPNT.EXE" 2>NUL | find /I /N "POWERPNT.EXE">NUL
if "%ERRORLEVEL%"=="0" (
    echo PowerPoint is running. Closing it...
    taskkill /f /im POWERPNT.EXE
) else (
    echo PowerPoint is not running. Starting it...
    start "" "POWERPNT.EXE /s " "%fileAddress%"
)

endlocal
