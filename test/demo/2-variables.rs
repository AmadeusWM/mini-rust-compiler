fn main() {
    // mutable variables can be changed
    let mut a: i32 = 0;
    a = 5;
    // implicit return with blocks
    let b: i32 = {
        let x = 5;
        if true {
            x
        } else {
            6
        }
    };
    println!("{b}");
}
