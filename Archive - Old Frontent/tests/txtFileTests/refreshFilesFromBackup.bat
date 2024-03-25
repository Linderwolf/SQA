rem   This file will copy the .txt log files from ../logFileBackup, 
rem   in order to return to a standard set of data for future tests
rem   	(Test suite may otherwise fail due to deleting users, for example)

rem  Refresh those in the root folder
rem copy "..\logFileBackUp\AvailableGamesBackup.txt" "..\AvailableGames.txt"
rem copy "..\logFileBackUp\CurrentUserAccountsBackup.txt" "..\CurrentUserAccounts.txt"
rem copy "..\logFileBackUp\DailyTransactionsBackup.txt" "..\DailyTransactions.txt"
rem copy "..\logFileBackUp\GameCollectionBackup.txt" "..\GameCollection.txt"

rem  Refresh from the current folder
copy "..\logFileBackUp\AvailableGamesBackup.txt" "AvailableGames.txt"
copy "..\logFileBackUp\CurrentUserAccountsBackup.txt" "CurrentUserAccounts.txt"
copy "..\logFileBackUp\DailyTransactionsBackup.txt" "DailyTransactions.txt"
copy "..\logFileBackUp\GameCollectionBackup.txt" "GameCollection.txt"