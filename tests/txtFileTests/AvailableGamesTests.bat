@echo off
echo Starting AvailableGames.txt Tests
pause

call refreshFilesFromBackup.bat

set /a availableGamesWriteFailures=0		&:: The number of test failures found when writing to AvailableGames.txt
set /a dailyTransactionsWriteFailures=0		&:: rem The number of test failures found when writing to DailyTransactions.txt

rem for every file::
rem send the file name to report.txt
rem pipe the contents to the exe, write output to testing.txt
rem compare the testing file to the corresponding input file
for /r %%F in (./txtFileInput/txtAvailableGames/*) do (
    type %%F | ..\..\Vapour.exe
    echo %%~nF >> /report/report.txt

    fc AvailableGames.txt txtFileOutput/txtAvailableGames/%%~nF.out >> /reports/report.txt
    
        if errorlevel 1 (
                echo Test Failure: %%~nF >> /reports/report.txt
                echo txtFileOutput/txtAvailableGames/&&~nF.out >> /reports/report.txt
                echo ____________________________________
                set /a availableGamesWriteFailures+=1
        )
)

echo Write to AvailableGames.txt failures: %availableGamesWriteFailures% >> ./reports/failureReport.txt
rem echo Write to AvailableGames.txt failures: %dailyTransactionsWriteFailures% >> failureReport.txt