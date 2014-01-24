#!/bin/bash -f

PU=$1        #NoPileUp, 40PileUp, 140PileUp
sample=$2    #tt-4p-0-1000_100TEV/

echo "PU" ${PU}
echo "sample" ${sample}

xrd red-gridftp11.unl.edu dirlist /mnt/hadoop/user/Snowmass/HTBinned/Delphes-3.0.9.2/${PU}/${sample}/ | grep root | awk '{print $5}' > fileLists/${sample}_${PU}.txt

