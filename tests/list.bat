@echo off
echo "Starting List Tests"
pause

set /a failures=0 	&:: The number of failures found in the List tests

rem loop recursively through the input folder
for /r %%F in (.\input\list\*) do (			&:: for each List file
    echo %%~nF >> report.txt				&:: send the file name to report.txt
    type %%F | ..\Vapour.exe > testing.txt		&:: pipe the contents to the exe, write output to testing.txt
    fc testing.txt output/list/%%~nF.out >> report.txt	&:: compare the testing file to the corresponding input file
							&:: record comparison in report.txt    
rem Format the report   
    if errorlevel 1 (
        echo ==== %%~nF ==== failed >> report.txt
        echo ==== %%~nF ==== failed >> failureReport.txt
	    fc testing.txt output/list/%%~nF.out >> failureReport.txt
        set /a failures+=1
    )
)
rem Send the number of failures to the report file.
echo Failures in List: %failures% >> failureReport.txt
echo Failures in List: %failures% >> summary.txt
goto main