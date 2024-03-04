@echo off
rem Login
echo testing login.bat
login.bat
pause

rem	Logout 
echo testing logout.bat
logout.bat
pause

rem	Create
call refreshFilesFromBackup.bat
echo Resetting Files for next tests
echo testing create.bat
create.bat
pause

rem	Delete
call refreshFilesFromBackup.bat
echo Resetting Files for next tests
echo testing delete.bat
delete.bat
pause

rem	AddCredit
call refreshFilesFromBackup.bat
echo Resetting Files for next tests
echo testing addCredit.bat
addCredit.bat
pause

rem	Refund
call refreshFilesFromBackup.bat
echo Resetting Files for next tests
echo testing refund.bat
refund.bat
pause

rem	Buy
echo testing buy.bat
buy.bat
call refreshFilesFromBackup.bat
echo Resetting Files for next tests
pause

rem	Sell
echo testing sell.bat
sell.bat
call refreshFilesFromBackup.bat
echo Resetting Files for next tests
pause

rem	List
echo testing list.bat
list.bat
call refreshFilesFromBackup.bat
echo Resetting Files for next tests
pause

rem	ListUsers
echo testing listusers.bat
listusers.bat
call refreshFilesFromBackup.bat
echo Resetting Files for next tests
pause