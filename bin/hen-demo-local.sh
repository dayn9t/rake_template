#!/usr/bin/env bash

src_url="hikn://admin:howell1409@10.1.0.21:8000/record/101?start_time=2024-07-15T10:00:00&end_time=2024-07-15T10:10:00";
dst_file=a.raw

arch=$(uname -m)

#exe=/opt/howell/iap/current/hen/bin/"$arch"/hen-download
exe=/home/jiang/repo/hik/hen/build/bin/hen-download
ls -la $exe

echo $exe $src_url $dst_file

$exe $src_url $dst_file
