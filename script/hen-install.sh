#!/usr/bin/env bash

arch=$(uname -m)
cd ../cmake-build-release || exit
#cmake build
src=bin/hen-download
dst=/opt/howell/iap/current/hen/bin/"$arch"

sudo rsync -av $src "$dst"

echo -e "\n\033[32m更新到: $dst \033[0m\n"

ls -lh "$dst"

echo -e "\n  cd $dst && rput.sh ifly && cd -\n"

