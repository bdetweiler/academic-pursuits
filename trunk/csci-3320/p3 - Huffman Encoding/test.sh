#!/bin/sh
# this is a simple shell script to test the program
# in addition to the filename you may pass the "-v" or "-vv" flags
# $# are the arguments
if [ $# -lt 1 ]; then
        echo 1>&2 Usage: $0 input_file
        exit 127
fi
./huffman -i $1 -o output.huff $2
# exit if return ($?) is not equal to 0
if [ $? -ne 0 ]; then
        echo 1>&2 encoding failed
        exit 127
fi
# display unsorted (f), but enable long listing (l)
ls -fl $1 output.huff 
# conditional execution
# if the huffman command is ok, run the ls and cmp commands
if ./huffman -i output.huff -o result.huff -d $2; then
        ls -fl $1 result.huff output.huff
        #cmp -b $1 result.huff
        diff --brief $1 result.huff
fi
#
# alias vimxxd='vim -R +"%!xxd" +"set ft=xxd" +"set nomod"'
# this will start vim in xxd mode with the file converted
# the file is readonly and it will not prompt for a save
