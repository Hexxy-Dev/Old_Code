@echo off

::<----- USAGE ----->


::FOR THE PROGRAM TO RUN AT SHUTDOWN REPLACE THE SHUTDOWN SCRIPT IN WINDOWS POLICIES

::FOR THE PROGRAM TO WORK YOU NEED THE WINRAR FOLDER TO BE SET AS A ENVIRONMENT VARIABLES

::THIS PROGRAM ALSO DEPENDS ON IT'S STARTUP COUNTERPART IN ORDER TO WORK PROPERLY


::<----- END OF USAGE ----->




::<----- GET ENCRYPT VARIABLES ----->

set temp_data_path="C:\myTemp"

if NOT exist %temp_data_path% (
    echo no temp data was found
    PAUSE
)

set /p pass=< %temp_data_path%\pass.txt
set /p archive_path=< %temp_data_path%\archive_path.txt
set /p file_path=< %temp_data_path%\file_path.txt

rmdir %temp_data_path%\ /s /q

::<----- END OF GET ENCRYPT VARIABLES ----->


::<----- CLOSING SEQUENCE ----->

rar a -r -df -hp%pass% %archive_path% %file_path%

::<----- END OF CLOSING SEQUENCE ----->

shutdown /s