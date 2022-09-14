#!/bin/bash

echo > out
for file in `ls BWCHP/*.bwp`; do
echo "Processing $file"
./BlocksworldAstar $file >> out
egrep -c "Fail" out
done
