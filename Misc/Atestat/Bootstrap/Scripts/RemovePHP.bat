if exist d:\ (
    set DriveLetter=D
) else (
    set DriveLetter=C
)

RMDIR /S/Q %DriveLetter%:\AppServ\www\Hexxy