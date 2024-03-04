@echo off
echo "starting tests"
pause

set /a failures=0 	& :: The number of failures found in the delete tests

rem loop recursively through the input folder
for /r %%F in (.\input\buy\*) do (			& :: for each buy file
    echo %%~nF >> report.txt
    type %%F | ..\Vapour.exe > testing.txt
    fc testing.txt output/buy/%%~nF.out >> report.txt
    if errorlevel 1 (
        echo ==== %%~nF ==== failed >> report.txt
        echo ==== %%~nF ==== failed >> failureReport.txt
	    fc testing.txt output/buy/%%~nF.out >> failureReport.txt
        set /a failures+=1
    )
)
echo Failures in buy: %failures% >> failureReport.txt
echo Failures in buy: %failures% >> summary.txt
goto main