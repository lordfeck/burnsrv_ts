#!/bin/bash
# Approximem FFMPEG convenience script
# Writing this because we might want to mass convert to another format.
# MJB 20/01/2020

banner='MakeMPEG. Usage:\n./makempeg.sh <inputfile>'
infile=""

function runff
{
    local outfile=${infile%'.mp4'}q${quant}r${res}_${fps}fps.mp4
    echo "Launching FFMPEG to convert $infile to $outfile"
    ffmpeg $infile $quant $res $fps $outfile 
}

if [ -n "$0" ]; then
    echo -e "$banner"
    exit 1
else
    infile="$0"
fi

echo "MakeMPEG. Will produce X total files."

echo "Step 1/X"
