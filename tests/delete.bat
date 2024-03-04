@echo off
echo "starting tests"
pause

set /a failures=0 	& :: The number of failures found in the delete tests

rem loop recursively through the input folder
for /r %%F in (.\input\delete\*) do (			            & :: for each delete file
    echo %%~nF >> report.txt				                & :: send the file name to report.txt
    type %%F | ..\Vapour.exe > testing.txt		            & :: pipe the contents to the exe, write output to testing.txt
    fc testing.txt output/delete/%%~nF.out >> report.txt	& :: compare the testing file to the corresponding input file
							                                & :: record comparison in report.txt
rem Format the report					
    if errorlevel 1 (
	& :: Record the tests that failed.
        echo ==== %%~nF ==== failed >> report.txt
        echo ==== %%~nF ==== failed >> failureReport.txt
	    fc testing.txt output/delete/%%~nF.out >> failureReport.txt
        set /a failures+=1
    )
)
rem  Send number of failures to the report files.
echo Failures in delete: %failures% >> failureReport.txt
echo Failures in delete: %failures% >> summary.txt
goto main