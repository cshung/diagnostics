#!/bin/bash
cd  `dirname $0`
ls
./run.sh collect --clrevents gc --clreventlevel verbose $@ 
