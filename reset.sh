#/bin/bash

FILE=ocssd.img
if [ -f "$FILE" ]; then
    rm ocssd.img
fi

if [ $? -eq 0 ]; then
	echo "remove ocssd.img"
fi

qemu-img create -f ocssd -o num_grp=2,num_pu=4,num_chk=64 $FILE

if [ $? -eq 0 ]; then
    echo "create new ocssd.img"
fi

if [ -f "$FILE" ]; then
	du -sh $FILE
fi

