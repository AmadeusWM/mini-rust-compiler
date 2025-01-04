
fn main() {
    A::B::hello();
}

mod A {
    mod B {
        fn hello() {
            println!("Hello, world!");
            hello2(2);
            fn hello2(two: i32) {
                println!("Hello world 2?");
                println!("{two}");
            }
            hello3();
        }
    }
    fn hello3() {
        println!("Hello world 3");
    }
}
