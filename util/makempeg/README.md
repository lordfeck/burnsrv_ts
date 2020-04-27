# About MakeMPEG

Convenient scripts to produce MPEG videos in desired formats.

We wish to vary parameters and use only a short sample video. These scrips will pass the requisite parameters to FFmpeg for conversion.

## Script overview.

Loads in the same parameters used by `testrunner.sh`. Takes an input file and converts it to video files formatted according to each parameter. The video filename conventions follow those expected by `testrunner.sh` exactly.

## Requirements.

The script feeds every parameter to FFmpeg, so naturally you should have it installed.

It also expects `../testcfg/stream.config` to exist and to be correctly configured.

## Usage.

`./makempeg.sh <inputfile.mp4>` Will begin conversion of input file into files of each parameter.

`./makempeg.sh -h` Reminder text is displayed.
