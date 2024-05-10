pushd %~dp0
rem call run.cmd collect --clrevents gc --clreventlevel verbose %* 
call run.cmd collect --profile gc-collect %* 
pause