// while
fn while_test() {
    let mut i = 10;
    while i > 0 {
        println!("{i}");
        i -= 1;
        if i < 5 {
            break;
        };
    };
}

// loops and breaks
fn loop_test() {
    let mut i = 10;
    loop {
        if (i < 0) {
            break; // breaks
        };
        println!("{i}");
        i -= 1;
    }
}

fn return_test() -> i32 {
    return 5 + 3;
}

fn main() {
    while_test();
    loop_test();
    let x = return_test();
    println!("{x}");
}
