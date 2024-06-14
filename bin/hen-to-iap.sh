#!/usr/bin/env bash

arch=$(uname -m)
src=../cmake-build-release/bin/hen-download
dst=/opt/howell/iap/current/hen/bin/"$arch"

sudo rsync -av $src "$dst"

echo -e "\n\033[32m更新到: $dst \033[0m\n"

ls -lh "$dst"