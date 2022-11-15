#!/bin/bash
cd  `dirname $0`
ls
export DOTNET_GCName=
export COMPlus_GCName=
./run.sh collect --clrevents gc --clreventlevel verbose $@ 
