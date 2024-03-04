@echo off
:: 	Login
echo testing login.bat
login.bat
pause

::	Logout 
echo testing logout.bat
logout.bat
pause

::	Create
call refreshFilesFromBackup.bat
echo Resetting Files for next tests
echo testing create.bat
create.bat
pause

::	Delete
call refreshFilesFromBackup.bat
echo Resetting Files for next tests
echo testing delete.bat
delete.bat
pause

::	AddCredit
call refreshFilesFromBackup.bat
echo Resetting Files for next tests
echo testing addCredit.bat
addCredit.bat
pause

::	Refund
call refreshFilesFromBackup.bat
echo Resetting Files for next tests
echo testing refund.bat
refund.bat
pause

::	Buy
echo testing buy.bat
buy.bat
call refreshFilesFromBackup.bat
echo Resetting Files for next tests
pause

::	Sell
echo testing sell.bat
sell.bat
call refreshFilesFromBackup.bat
echo Resetting Files for next tests
pause

::	List
echo testing list.bat
list.bat
call refreshFilesFromBackup.bat
echo Resetting Files for next tests
pause

::	ListUsers
echo testing listusers.bat
listusers.bat
call refreshFilesFromBackup.bat
echo Resetting Files for next tests
pause