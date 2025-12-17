#!/bash/bin

arr=( 1 20 19.9 Hello "Nvim is best" )

echo "arr[0] = ${arr[0]}"
echo "arr[1] = ${arr[1]}"
echo "arr[2] = ${arr[2]}"
echo "arr[3] = ${arr[3]}"
echo "arr[4] = ${arr[4]}"

# Printing all the values at once
echo 
echo "All the values in array are ${arr[*]}"

# Get the length of array
echo 
echo "No. of elements in the array are ${#arr[*]}"

# Printing range of values of array
echo 
echo "Values from index 2 to index 4 are ${arr[*]:2:3}" # Syntax :- ${arr[*]:index of first element:No. of elements to print}

# Updating an array
arr+=( add "new values" 3 )
echo 
echo "Printing complete array with the added values ${arr[*]}"

# Key-value array
declare -A map
map=( [name]=Vatsal [Editor]=neovim [num]=34 )
echo "the name is ${map[name]}"
