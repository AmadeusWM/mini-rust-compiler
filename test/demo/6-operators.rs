
fn main() {
    // expressions and grouped expressions
    let a: i32 = (5 + 3)*5;
    println!("{a}");
    // modulo
    let b = a % 3;
    println!("{b}");
    // combination of operators, 
    let c = (5*3) + {
        let x = 5;
        5*8
    } + 7 * 3;
    println!("{c}");
    let mut x = 5;
    // assignment with +, -, /, *, % etc. 
    x += 3;
    // unary operators
    x = -x;
    println!("{x}");

    // modulo with floats
    let y: f32 = 5.0;
    let z: f32 = 3.0;
    let q = y % z;
    println!("{q}");
}
