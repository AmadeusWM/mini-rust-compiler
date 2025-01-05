fn a() {
    let x = 2;
    let y = 5;
    let b = 3;
    let c = 4;
    // return ((x*y)+b)*c-52 - 10;
    return;
}

fn main() {
    let mut x = 0;
    let y = a();
    println!("{y}");
    loop { 
        if x >= 10 {
            break
        }
        println!("{x}");
        x += 1;
    }
}
