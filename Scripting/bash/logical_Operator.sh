#!/bin/bash

read -p "Enter you age: " age
[[ $age -ge 18 ]] && echo "Adult" || echo "Minor"
