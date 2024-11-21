fn a() {
    main::something(5);
}

fn main() {
    something(5);
    fn something(a: i32) -> i32 {
        let x = 3;
        a + x
    }
    let x: i32 = 1;
}
