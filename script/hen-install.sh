#!/usr/bin/env bash

ARCH=$(uname -m)
HEN_DIR="/opt/howell/iap/current/hen"
PROJ_DIR="/home/jiang/repo/hik/hen"
LS="ls --color -lhrt"

cd $PROJ_DIR/cmake-build-release || exit
ninja
sudo ninja install

src="lib/libhen_ce.so"
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

