fn a() -> i32 {
    let a = 3;
    {
        a + 5
    }
}

fn main() {
    let mut x: i32;
    x = 10;
    if (x ==5 || x == 10 && true) {
        println!("X is 10 or 5");
    }
}
