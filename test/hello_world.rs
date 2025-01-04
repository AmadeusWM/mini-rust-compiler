fn rec(mut y: i32, z: i32) -> i32 {
    y = y + z;
    return y;
}

fn main() {
    let x = rec(5, 7);
    println!("{x}");
}
