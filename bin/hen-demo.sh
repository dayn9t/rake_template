#!/usr/bin/env bash

start=2024-07-15T16:33:00
end=2024-07-15T16:43:00

#start=2024-07-15T14:00:00
#end=2024-07-15T14:10:00

host=192.168.21.202

src_url="hikn://admin:howell1409@$host:8000/record/200?start_time=$start&end_time=$end";
dst_file=a.raw

arch=$(uname -m)

exe=/home/jiang/repo/hik/hen/build/bin/hen-download
#exe=/opt/howell/iap/current/hen/bin/"$arch"/hen-download

echo $exe $src_url $dst_file

$exe $src_url $dst_file
