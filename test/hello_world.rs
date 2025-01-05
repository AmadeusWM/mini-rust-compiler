fn main() {
    A::B::hello();
}

fn hello4() {
    println!("Hello world 4");
}

mod A {
    mod B {
        fn hello() {
            hello2(2);
            println!("Hello, world!");
            fn hello2(two: i32) {
                println!("Hello world 2?");
                println!("{two}");
            }
            hello2(2);
            super::C::hello5();
        }
    }
    mod C {
        fn hello5() {
            println!("Hello world 5");
            super::B::hello::hello2(3);
        }
    }
}
