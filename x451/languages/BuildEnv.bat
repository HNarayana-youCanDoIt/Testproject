@echo off

set CURRENT_PATH=%CD%

call config.bat
if NOT "%errorlevel%" == "0" goto FAIL

rem start "QNX Environment" /D%CD% cmd.exe
start /D%CURRENT_PATH% cmd.exe
goto END

:FAIL
@echo on
@pause

:END
