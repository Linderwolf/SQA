@echo off
echo "Starting AvailableGames.txt tests"
pause

set /a availableGamesWriteFailures=0
set /a dailyTransactionsWriteFailures=0

for /r %%F in (.\txtFileInput\txtAvailableGames\*) do (
    echo %%~nF >> report.txt
    type %%F | ..\..\Vapour.exe
    fc ../AvailableGames.txt ./txtFileOutput/txtAvailableGames/%%~nF.out >> report.txt
    if errorlevel 1 (
        echo Test Failure: %%~nF >> report.txt
        echo Test Output: >> report.txt 
rem	echo ../AvailableGames.txt >> report.txt
	echo ____________________________________
	echo Expected Output: >> report.txt
	echo ./txtFileOutput/txtAvailableGames/&&~nF.out >> report.txt
        set /a availableGamesWriteFailures+=1
    )

    fc ../DailyTransactions.txt ./txtFileOutput\txtDailyTransactions\AvailableGamesTransactions/%%~nF.out >> report.txt
    if errorlevel 1{
	echo Test Failure: txtDailyTransactions\AvailableGamesTransactions/%%~nF.out >> report.txt
	echo Test Output: >> report.txt
rem	echo ../DailyTransactions.txt >> report.txt
	echo ____________________________________
	echo Expected Output: >> ./report.txt
	echo ./txtFileOutput/txtAvailableGames/&&~nF.out >> report.txt
	set /a dailyTransactionsWriteFailures+=1
    )
)
echo Write to AvailableGames.txt failures: %availableGamesWriteFailures% >> failureReport.txt
echo Write to AvailableGames.txt failures: %dailyTransactionsWriteFailures% >> failureReport.txt
goto main