#!/bin/sh
make -C ./Libs/libft
make -C ./nm/
make -C ./otool/
mkdir -p bin
cp ./nm/ft_nm ./bin/
cp ./otool/ft_otool ./bin/
