#!/usr/bin/env bash

start=2024-07-15T16:33:00
end=2024-07-15T16:43:00

#start=2024-07-15T14:00:00
#end=2024-07-15T14:10:00

host=192.168.21.202

src_url="hikn://admin:howell1409@$host:8000/record/201?start_time=$start&end_time=$end";
dst_file=07-15.pcm

arch=$(uname -m)

exe=/opt/howell/iap/current/hen/bin/x86_64/hen-download
#exe=/opt/howell/iap/current/hen/bin/"$arch"/hen-download

echo $exe $src_url $dst_file

$exe $src_url $dst_file

echo "ffmpeg -f s16le -acodec pcm_alaw -ar 8000 -ac 1 -i $dst_file -ar 16000 a.mp3"
