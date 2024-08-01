#!/usr/bin/env bash

echo -e "\n\033[32m卸载库: hen...\033[0m\n"

sudo rm -rf /usr/local/bin/hen-*
sudo rm -rf /usr/local/include/hen/
sudo rm -rf /usr/local/lib/libhen*

HEN_DIR="/opt/howell/iap/current/hen"
LS="ls --color -lhrt"

rm -rf $HEN_DIR/bin/hen-*
$LS $HEN_DIR/bin

rm -rf $HEN_DIR/lib/libhen_*
$LS $HEN_DIR/lib

