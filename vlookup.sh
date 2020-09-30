#!/bin/bash

if [ $# -eq 0 ]; then
	echo "No input file."
	exit 1
fi

cat $1 | grep "user read" | sed 's/[,:]//g' | awk '{print $10}' > userio_lba
cat $1 | grep "GC read" | sed 's/[,:]//g' | awk '{print $10}' > gcio_lba
cat $1 | grep "user read" | sed 's/[,:]//g' | awk '{out=" "$4" "$10; print out}' | awk '{print $2 " " $1}' > userio_lba_ts.csv
cat $1 | grep "GC read" | sed 's/[,:]//g' | awk '{out=" "$4" "$10; print out}' | awk '{print $2 " " $1}' > gcio_lba_ts.csv

comm -12 <(sort userio_lba) <(sort gcio_lba) > comm_lba

for i in $(cat comm_lba);
do
	grep -wE "^${i}" userio_lba_ts.csv >> red_user_ts.csv
done

for i in $(cat comm_lba);
do
	grep -wE "^${i}" gcio_lba_ts.csv >> red_gc_ts.csv
done

user_lba_count=`cat userio_lba | wc -l`
gc_lba_count=`cat gcio_lba | wc -l`
red=`cat comm_lba | wc -l`
echo "userio_count: ${user_lba_count}" > lba_report
echo "gcio_count: ${gc_lba_count}" >> lba_report
echo "redundant_lba_count: ${red}" >> lba_report


