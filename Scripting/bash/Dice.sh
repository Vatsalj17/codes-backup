#!/bin/bash

echo "Generating a number between 1 to 6 ...."
echo "$(( $RANDOM % 6 + 1 ))"
