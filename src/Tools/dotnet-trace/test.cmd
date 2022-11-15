pushd %~dp0
set DOTNET_GCName=
set COMPlus_GCName=
call run.cmd collect --clrevents gc --clreventlevel verbose %* 