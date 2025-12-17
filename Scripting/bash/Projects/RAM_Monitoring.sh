#!/bin/bash

FREE_RAM=$( free -mt | grep Total | awk '{print $4}' ) 
LIMIT=500

if [[ $FREE_RAM -lt $LIMIT ]] 
then 
    echo "WARNING! RAM is running low"
else
    echo "RAM space is sufficient"
fi
