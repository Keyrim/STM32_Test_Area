
call "setup_msvc.bat"

cd .

chcp 1252

if "%1"=="" (nmake  -f pendulum_simulink_open_loop.mk all) else (nmake  -f pendulum_simulink_open_loop.mk %1)
@if errorlevel 1 goto error_exit

exit 0

:error_exit
echo The make command returned an error of %errorlevel%
exit 1