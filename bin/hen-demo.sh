#!/usr/bin/env bash

src_url="hikn://admin:howell1409@192.168.21.202:8000/record/201?start_time=2024-07-12T15:55:00&end_time=2024-07-12T16:05:00";
dst_file=~/1/a.raw

arch=$(uname -m)

exe=/opt/howell/iap/current/hen/bin/"$arch"/hen-download

echo $exe $src_url $dst_file

$exe $src_url $dst_file
