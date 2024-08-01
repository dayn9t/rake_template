#!/usr/bin/env bash

HEN_DIR=/home/jiang/repo/hik/hen

host=10.1.0.21
today=$(date +%Y-%m-%d)
start="$today"T10:00:00
end="$today"T10:10:00
src_url="hikn://admin:howell1409@$host:8000/record/101?start_time=$start&end_time=$end";
dst_file=$HEN_DIR/$today.pcm

cd $HEN_DIR/cmake-build-release || exit
ninja

exe=$HEN_DIR/cmake-build-release/bin/hen-download2
ls -la $exe

echo $exe "$src_url" "$dst_file"

$exe "$src_url" "$dst_file"

echo "ffmpeg -f s16le -acodec pcm_alaw -ar 8000 -ac 1 -i $dst_file -ar 16000 $today.mp3"