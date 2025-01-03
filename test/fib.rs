fn fib(n: i32) -> i32 {
    if n <= 1 {
        n
    } else {
        fib(n - 1) + fib(n - 2)
    }
}

fn main() {
    let mut x = 0;
    while x <= 25 {
        let result = fib(x);
        println!("{result}");
        x += 1;
    }
}
