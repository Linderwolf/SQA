@echo off
echo "Starting AddCredit Tests"
pause

set /a failures=0	&:: The number of failures found in the addCredit tests

rem loop recursively through the input folder - for each 'delete' file:
rem send the file name to report.txt, pipe the contents to the exe, write output to testing.txt
rem compare the testing file to the corresponding input file, record comparison in report.txt

for /r %%F in (.\input\addCredit\*) do (		    &:: for each addCredit file
    echo %%~nF >> report.txt				    &:: send the file name to report.txt
    type %%F | ..\Vapour.exe > testing.txt		    &:: pipe the contents to the exe, write output to testing.txt
    fc testing.txt output/addCredit/%%~nF.out >> report.txt &:: compare the testing file to the corresponding input file

rem Format the report   
    if errorlevel 1 (
        echo ==== %%~nF ==== failed >> report.txt
        echo ==== %%~nF ==== failed >> failureReport.txt
	    fc testing.txt output/addCredit/%%~nF.out >> failureReport.txt
        set /a failures+=1
    )
)
rem Send the number of failures to the report file.
echo Failures in addCredit: %failures% >> failureReport.txt
echo Failures in addCredit: %failures% >> summary.txt
goto main