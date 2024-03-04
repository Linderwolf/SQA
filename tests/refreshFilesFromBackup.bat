rem   This file will copy the .txt log files from ../logFileBackup, 
rem   in order to return to a standard set of data for future tests
rem   	(Test suite may otherwise fail due to deleting users, for example)

copy "..\logFileBackUp\AvailableGames.txt" "..\AvailableGames.txt"

copy "..\logFileBackUp\CurrentUserAccounts.txt" "..\CurrentUserAccounts.txt"

copy "..\logFileBackUp\DailyTransactions.txt" "..\DailyTransactions.txt"

copy "..\logFileBackUp\GameCollection.txt" "..\GameCollection.txt"