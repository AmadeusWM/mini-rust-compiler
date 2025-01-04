fn rec(y: i32) -> i32 {
    if y <= 1 {
        y
    } else {
        rec(y - 1)
    }
}

fn main() {
    let x = rec(5);
}
