// - Only functions within the same scope casn be called
//   or from a parent scope

fn main() {
    println!("main");
    a();
    b();
    fn a(){
        println!("A");
    }
    // c(); // this function cannot be called, not reachable
}

fn b() {
    println!("B");
    c();
    fn c() {
        println!("C");
        fn x() {
            println!("X");
        }
    }
}
