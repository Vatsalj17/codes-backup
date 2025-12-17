function hello () {
    console.log(arguments);
}

function sum() {
    let total = 0;
    arg = arguments;
    for (let i = 0; i < arg.length; i++) total += arg[i];
    return total;
}

hello (1, 2, 3, 4, 5);
console.log(sum(1, 2, 3, 4, 5));
