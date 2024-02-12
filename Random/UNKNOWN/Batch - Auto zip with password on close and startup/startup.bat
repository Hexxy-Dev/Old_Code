@echo off

::<----- USAGE ----->


::FOR THE PROGRAM TO RUN AT STARTUP PLACE IT IN THE FOLLOWING FOLDER:
::[D|C]:\Profiles\{User}\‌​AppData\Roaming\Micro‌​soft\Windows\Start Menu\Programs\Startu‌​p

::FOR THE PROGRAM TO WORK YOU NEED THE WINRAR FOLDER TO BE SET AS A ENVIRONMENT VARIABLES

::THIS PROGRAM ALSO DEPENDS ON IT'S SHUTDOWN COUNTERPART IN ORDER TO WORK PROPERLY


::<----- END OF USAGE ----->



::<----- SETTINGS ----->

set archive_path="D:\testArchive.rar"
set backup_path="C:\ProgramData\archiveBackup.rar"
set drive=D
set folder_name=FILME
set delete_old_archive=true
set create_backup=true

::<----- END OF SETTINGS ----->










::<----- INTERNAL VARIABLES DECLARATION ----->

set drive_path=%drive%:\
set file_path="%drive_path%%folder_name%\*.*"
set temp_data_path="C:\myTemp"

::<----- END OF INTERNAL VARIABLES DECLARATION ----->



::<----- STARTUP SEQUENCE ----->

:STARTUP_LABEL

::set /p pass="Password:"
set /P "=_" < NUL > "Enter password"
findstr /A:1E /V "^$" "Enter password" NUL > CON
del "Enter password"
set /P "pass="
cls
color 07

if exist %archive_path% (
    unrar x -y -hp%pass% %archive_path% %drive_path%
    
    :: retry if password is incorrect
    if errorlevel 1 GOTO :STARTUP_LABEL

    if %create_backup%==true (
        copy %archive_path% %backup_path%
    )

    if  %delete_old_archive%==true (
        del %archive_path%
    )
)

::write data to file before closing the program

if NOT exist %temp_data_path% mkdir %temp_data_path%

echo %pass% > %temp_data_path%\pass.txt
echo %archive_path% >> %temp_data_path%\archive_path.txt
echo %file_path% >> %temp_data_path%\file_path.txt

::<----- END OF STARTUP SEQUENCE ----->