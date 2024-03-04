@echo off
echo "starting tests"
pause

set /a failures=0

for /r %%F in (.\input\delete\*) do (
    echo %%~nF >> report.txt
    type %%F | ..\Vapour.exe > testing.txt
    fc testing.txt output/delete/%%~nF.out >> report.txt
    if errorlevel 1 (
        echo ==== %%~nF ==== failed >> report.txt
        echo ==== %%~nF ==== failed >> failureReport.txt
	    fc testing.txt output/delete/%%~nF.out >> failureReport.txt
        set /a failures+=1
    )
)
echo Failures in delete: %failures% >> failureReport.txt
echo Failures in delete: %failures% >> summary.txt
goto main