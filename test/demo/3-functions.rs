fn parameters(a: i32, x: i32) -> i32 {
    a * x + 3
}

fn no_type() {
    println!("this function has no parameters or return type");
}

fn main() {
    let x = parameters(3, 2);
    println!("{x}");
    let x = no_type();
    println!("{x}");
}
