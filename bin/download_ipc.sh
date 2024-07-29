#!/usr/bin/env bash

host=10.1.0.21
start=2024-07-28T11:00:00
end=2024-07-28T11:10:00
src_url="hikn://admin:howell1409@$host:8000/record/101?start_time=$start&end_time=$end";
dst_file=a.pcm

#arch=$(uname -m)

#exe=/opt/howell/iap/current/hen/bin/"$arch"/hen-download
exe=/home/jiang/repo/hik/hen/build/bin/hen-download
ls -la $exe

echo $exe "$src_url" $dst_file

$exe "$src_url" $dst_file
