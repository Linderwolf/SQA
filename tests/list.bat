@echo off
echo "starting tests"
pause

set /a failures=0

for /r %%F in (.\input\list\*) do (
    echo %%~nF >> report.txt
    type %%F | ..\Vapour.exe > testing.txt
    fc testing.txt output/list/%%~nF.out >> report.txt
    if errorlevel 1 (
        echo ==== %%~nF ==== failed >> report.txt
        echo ==== %%~nF ==== failed >> failureReport.txt
	    fc testing.txt output/list/%%~nF.out >> failureReport.txt
        set /a failures+=1
    )
)
echo Failures in list: %failures% >> failureReport.txt
echo Failures in list: %failures% >> summary.txt
goto main