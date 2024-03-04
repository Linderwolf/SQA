@echo off
echo "starting tests"
pause

set /a failures=0 	& :: The number of failures found in the delete tests

<<<<<<< HEAD
rem loop recursively through the input folder
for /r %%F in (.\input\create\*) do (			& :: for each create file
    echo %%~nF >> report.txt				& :: send the file name to report.txt
    type %%F | ..\Vapour.exe > temp.txt			& :: pipe the contents to the exe, write output to temp.txt
    fc temp.txt output/create/%%~nF.out >> report.txt	& :: compare the temp file to the corresponding input file
							& :: record comparison in report.txt
rem Format the report   
 if errorlevel 1 (
	& :: Record the tests that failed.
=======
for /r %%F in (.\input\create\*) do (
    echo %%~nF >> report.txt
    type %%F | ..\Vapour.exe > testing.txt
    fc testing.txt output/create/%%~nF.out >> report.txt
    if errorlevel 1 (
>>>>>>> 3295b81a3db74eada736df6107337244cb33fc2c
        echo ==== %%~nF ==== failed >> report.txt
        echo ==== %%~nF ==== failed >> failureReport.txt
	    fc testing.txt output/create/%%~nF.out >> failureReport.txt
        set /a failures+=1
    )
)
rem Send the number of failures to the report file.
echo Failures in create: %failures% >> failureReport.txt
echo Failures in create: %failures% >> summary.txt
goto main