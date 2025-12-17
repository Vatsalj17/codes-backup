fn main() {
    println!("Hello, world!");
    const A: i32 = 4 + 4;
    println!("{A}");
    let a = 10;
    println!("{}", a);

    let tup = (122, 5.6, "hello");
    let ad = ('t', 9.6);
    let _char = ad.0;
    let _flt = ad.1;
    let (x, y, z) = tup;
    println!("{}, {}, {}", x, y, z);
    let ttup = ((1, 4.5), ("2", 'z', 9.3), (3.4, '&', 55, false));
    let fnum = ttup.0.1;
    println!("{}", fnum);

    let num: u8 = 255;
    println!("{num}");
    // let num:u8 = (num + 1).wrapping_add(57);
    // println!("{num}");
}
