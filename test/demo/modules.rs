mod B {
    fn b() {
        println!("We are inside B::b");
        c();
        fn c() {
            println!("We are inside B::b::c");
            a();
        }
        fn a() {
            println!("We are inside B::b::a");
            xyz();
        }
        super::A::a();
        super::B::xyz();
        super::A::a();
    }

    fn xyz(){
        println!("We are inside xyz");
    }
}

fn main() {
    A::a();
    B::b();
    let mut x;
    x = hard_math(3, 7.0);
    println!("{x}");
    let x = {
        let h;
    };
    println!("{x}");
}

fn hard_math(x: i32, y: f64) -> i32 {
    let q = (y + 5.0) * 3.0 * 10.0;
    let b = (x + 5) * 3 * 10;
    return b;
}

mod A {
    fn a() {
        println!("We are inside A::a");
    }
}
