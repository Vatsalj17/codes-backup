use std::io;

fn main() {
    let tupple = (112, 5.6, "this is tupple");
    let (x, y, z) = tupple;
    println!("{}, {}, {}", x, y, z);
    let ttup = ((1, 4.5), ("2", 'z', 9.3), (3.4, '&', 55, false));
    let fnum = ttup.0.1;
    println!("{}", fnum);
    
    let arr = [1, 2, 3, 4, 5, 6];
    let months = ["January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"];
    let _first_month = months[0];
    println!("Enter an index of an array: ");
    let mut index = String::new();
    io::stdin().read_line(&mut index).expect("Failed to read line");
    let index: usize = index.trim().parse().expect("Index was not a number");
    let element = arr[index];
    println!("The value of element at the {index} in the arr is {element}");

    let _a:[i32; 5] = [10, 11, 12, 13, 14]; // Fixed length array
    let _a2 = [7; 5]; // [7, 7, 7, 7, 7]
}
