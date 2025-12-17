#!/bin/bash

set -x # It enables debuggin in the script (Executes the script step by step)

set -e # It exits the script if any command fails

pwd
echo "hello"
ping -c 1 google.com
sudo apt update
