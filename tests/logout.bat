@echo off
echo "starting tests"
pause

set /a failures=0

for /r %%F in (.\input\logout\*) do (
    echo %%~nF >> report.txt
    type %%F | ..\Vapour.exe > temp.txt
    fc temp.txt output/logout/%%~nF.txt >> report.txt
    if errorlevel 1 (
        echo ==== %%~nF ==== failed >> report.txt
        echo ==== %%~nF ==== failed >> failureReport.txt
	    fc temp.txt output/logout/%%~nF.txt >> failureReport.txt
        set /a failures+=1
    )
)
echo Failures in logout: %failures% >> failureReport.txt
echo Failures in logout: %failures% >> summary.txt
goto main