rem /************************************************************/
rem 	Configuration Items
rem		2. QT_PATH is the path of the bin folder of Qt installation with msvc2015_64 kit
rem	/************************************************************/

rem	/********************************************************/
rem Check system paths

if "%ComputerName%" == "HIPWN201" (
	call :Set_Paths_HIPWN201
) else if "%ComputerName%" == "HIPWN210" (
	call :Set_Paths_HIPWN210
) else if "%ComputerName%" == "MyPcName" (
	call :Set_Paths_MyPcName
) else (
	call :Set_Paths_Default
)
goto :Set_Paths_End

:Set_Paths_Default
	echo Error: Need to define Paths for "%ComputerName%"
	echo Msg: copy Set_Paths_MyPcName flow and set your paths in ./config.bat
	goto eof

:Set_Paths_HIPWN201
	echo Using Path setting from "%ComputerName%"
	set QT_PATH=D:\QT\Qt5.9.0\5.9\msvc2015_64
	set VC_PATH=C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC
	goto :eof

:Set_Paths_HIPWN210
	echo Using Path setting from "%ComputerName%"
	set QT_PATH=C:\Qt\Qt5.9.0\5.9\msvc2015_64
	set VC_PATH=C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC
	goto :eof
	
:Set_Paths_MyPcName
	echo Using Path setting from "%ComputerName%"
	set QT_PATH=MyPcNameQtPath
	set VC_PATH=MyPcNameVcPath
	goto :eof

:Set_Paths_End

rem	/********************************************************/
rem Check configuration
if "%QT_PATH%" == "" (
	echo Error: QT_PATH is not defined!
	goto FAIL
) 

echo QT_PATH="%QT_PATH%"

if "%VC_PATH%" == "" (
	echo Error: VC_PATH is not defined!
	goto FAIL
) 

echo VC_PATH="%VC_PATH%"


rem	/********************************************************/
rem Set Environment Variable


set PATH=%VC_PATH%;%QT_PATH%;%PATH%

call %QT_PATH%\bin\qtenv2.bat

call "%VC_PATH%\vcvarsall.bat" amd64

rem pause
rem Format makefile include path
rem pushd "%QNX_TARGET%/usr/include"
rem set MAKEFLAGS=-I%CD:\=/%
rem popd

rem Format makefile build chain path
rem pushd %BUILD_CHAIN_ROOT%
rem set BUILD_CHAIN_ROOT=%CD:\=/%
rem popd

exit /b 0

rem	/********************************************************/

:FAIL
echo Please check config.bat and retry.
exit /b 1
