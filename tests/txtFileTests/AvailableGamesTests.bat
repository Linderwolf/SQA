@echo off
echo Starting AvailableGames.txt Tests
pause

call refreshFilesFromBackup.bat

set /a availableGamesWriteFailures=0		&:: The number of test failures found when writing to AvailableGames.txt
set /a dailyTransactionsWriteFailures=0		&:: rem The number of test failures found when writing to DailyTransactions.txt

rem for every file::
for /r %%F in (.\txtFileInput\txtAvailableGames\*) do (
    echo %%~nF >> report.txt							  &:: send the file name to report.txt
    type %%F | ..\..\Vapour.exe >> reports/testing.txt				  &:: pipe the contents to the exe, write output to testing.txt
    fc AvailableGames.txt txtFileOutput/txtAvailableGames/%%~nF.out >> report.txt &:: compare the testing file to the corresponding input file
    
if errorlevel 1 (
        echo Test Failure: %%~nF >> report.txt
	echo txtFileOutput/txtAvailableGames/&&~nF.out >> report.txt
	echo ____________________________________
        set /a availableGamesWriteFailures+=1
)
)
rem    fc DailyTransactions.txt ./txtFileOutput\txtDailyTransactions\AvailableGamesTransactions/%%~nF.out >> report.txt
rem    if errorlevel 1{
rem	echo Test Failure: txtDailyTransactions\AvailableGamesTransactions/%%~nF.out >> report.txt
rem	echo Test Output: >> report.txt
rem	echo ../DailyTransactions.txt >> report.txt
rem	echo ____________________________________
rem	echo Expected Output: >> ./report.txt
rem	echo ./txtFileOutput/txtAvailableGames/&&~nF.out >> report.txt
rem	set /a dailyTransactionsWriteFailures+=1
rem    )

echo Write to AvailableGames.txt failures: %availableGamesWriteFailures% >> failureReport.txt
rem echo Write to AvailableGames.txt failures: %dailyTransactionsWriteFailures% >> failureReport.txt
goto main