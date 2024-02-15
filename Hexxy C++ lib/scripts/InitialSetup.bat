@echo off
pushd %~dp0\..\
call scripts\RunPremake.bat
popd
PAUSE