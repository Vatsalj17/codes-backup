#!/bin/bash

echo "Hello World!"

# This is a single line comment

: <<'ha' # The word with which the comment has started
kdjf
dkfjdk
kdjfkd
ha
# It should end with the same word

: <<'comment'
This
is
a
multi
line
comment

echo "Hello Comment"
