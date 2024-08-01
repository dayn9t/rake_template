#!/usr/bin/env bash

ARCH=$(uname -m)
cd ../cmake-build-release || exit
ninja
sudo ninja install

HEN_DIR="/opt/howell/iap/current/hen"
LS="ls --color -lhrt"

src="lib/libhen_reader.so"
dst="$HEN_DIR/lib/$ARCH"
rsync -av $src "$dst"
echo -e "\n\033[32m更新到: $dst \033[0m\n"
$LS "$dst"

src="bin/hen-download2"
dst="$HEN_DIR/bin/$ARCH"
rsync -av $src "$dst"
echo -e "\n\033[32m更新到: $dst \033[0m\n"
$LS "$dst"

echo -e "\n  cd $dst && rput.sh ifly && cd -\n"

