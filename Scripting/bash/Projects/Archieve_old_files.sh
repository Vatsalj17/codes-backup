#!/bin/bash

path="/home/Vatsal/Scripting/Projects/Useless"
limit=50M
depth=1
switch=true

if [[ ! -d $path ]]; then
	echo "Directory is no longer present: $path"
	exit 1
fi

if [[ ! -d $path/Archieve ]]; then
	echo "Creating the Archive Folder..."
	mkdir $path/Archieve
fi

for i in $(find $path -maxdepth $depth -size +$limit -type f); do
	if [[ $switch == true ]]; then
		gzip $i || exit 1
		mv $i.gz $path/Archieve || exit 1
	fi
done
