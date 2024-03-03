@echo off
echo "starting tests"
pause

set /a failures=0

for /r %%F in (.\input\refund\*) do (
    echo %%~nF >> report.txt
    type %%F | ..\Vapour.exe > temp.txt
    fc temp.txt output/refund/%%~nF.out >> report.txt
    if errorlevel 1 (
        echo ==== %%~nF ==== failed >> report.txt
        echo ==== %%~nF ==== failed >> failureReport.txt
	    fc temp.txt output/refund/%%~nF.out >> failureReport.txt
        set /a failures+=1
    )
)
echo Failures in refund: %failures% >> failureReport.txt
echo Failures in refund: %failures% >> summary.txt
goto main