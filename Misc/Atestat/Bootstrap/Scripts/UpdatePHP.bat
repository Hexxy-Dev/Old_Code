if exist d:\ (
    set DriveLetter=D
) else (
    set DriveLetter=C
)

xcopy /s/e/i/y ..\PHP\Hexxy %DriveLetter%:\AppServ\www\Hexxy