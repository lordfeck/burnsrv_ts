#!/bin/bash
# Approximem FFMPEG convenience script
# Writing this because we might want to mass convert to another format.
# MJB 20/01/2020, updated 16/04/2020

banner='MakeMPEG. Usage:\n./makempeg.sh <inputfile.mp4>\nRelies upon stream.config to get conversion formats.'
streamcfg="../testcfg/stream.config"
# Set start time and max length for imput video (optional)
timearg='-ss 00:02:35 -t 00:05:00'

if [ ! -s "$streamcfg" ]; then
    echo "Critical failure: stream.config file doesn't exist or is empty. Exiting."
    exit 1
fi

. "$streamcfg"

function checkError {
    if [ "$?" -ne "0" ]; then
        echo "CRITICAL: Failure when $1. Exiting."
        exit 1
    fi
}

# this function takes its args from the loops below
function runff
{
    local outfile="${basename}-${quant}-${res}.mp4"
    echo "Launching FFMPEG to convert $infile to $outfile"
    local ffargs="-y -i $infile $timearg -acodec copy -c:v libx264 -preset slow -crf $quant -s $res $outfile"
    echo FFARGS: $ffargs
    ffmpeg $ffargs
    # we may want this on or we may not
    checkError "encoding $basename $quant $res."
}

# if we get incorrect args then show the banner
if [ ! -n "$1" ] || [ "$1" = "-h" ]; then
    echo -e "$banner"
    exit 1
else
    infile="$1"
fi

# chop infile name of its extension for renaming
basename="${infile%'.mp4'}"

# quick calculation to verify we've read the config file correctly
resc=${#resolutions[@]}
quantc=${#quants[@]}
total="$((resc*quantc))"

echo "MakeMPEG. Will produce $total total files."
echo "Resolutions: ${resolutions[@]}. CRF aka Quantisations: ${quants[@]}."
echo "Beginning in 2..."
sleep 2

# Main double loop to do conversions and call runff

for res in "${resolutions[@]}"; do
    for quant in "${quants[@]}"; do
        runff
    done
done
