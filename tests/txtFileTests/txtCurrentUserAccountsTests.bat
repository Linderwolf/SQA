@echo off
echo Starting CurrentUserAccount.txt Tests
pause

rem copy fresh versions of the .txt files
call refreshFilesFromBackup.bat

set /a currentUserAccountsWriteFailures=0		&:: The number of test failures found when writing to AvailableGames.txt
set /a dailyTransactionsWriteFailures=0		&:: rem The number of test failures found when writing to DailyTransactions.txt

rem for every file::
rem send the file name to report.txt
rem pipe the contents to the exe, write output to testing.txt
rem compare the testing file to the corresponding input file
for /r %%F in (./txtFileInput/txtCurrentUserAccounts/*) do (
    type %%F | ..\..\Vapour.exe
    echo %%~nF >> /report/report.txt

    fc AvailableGames.txt txtFileOutput/txtCurrentUserAccounts/%%~nF.out >> /reports/report.txt
    
        if errorlevel 1 (
                echo Test Failure: %%~nF >> /reports/report.txt
                echo txtFileOutput/txtCurrentUserAccounts/&&~nF.out >> /reports/report.txt
                echo ____________________________________
                set /a availableGamesWriteFailures+=1
        )
)

echo Write to AvailableGames.txt failures: %availableGamesWriteFailures% >> ./reports/failureReport.txt
rem echo Write to AvailableGames.txt failures: %dailyTransactionsWriteFailures% >> failureReport.txt