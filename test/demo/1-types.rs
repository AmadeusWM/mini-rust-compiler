// - Type inference
// - Types 
// - Literals of every type
// - Shadowing

/* line comments */
fn main() {
    let x = 1;
    let y = 2;
    let z: i64 = x + y; // infer x, and y to i64
    let q: i32 = x; // ERROR: i32 not inferrable to i64
    println!("{z}");
    // other integer types
    let i: i8 = 1;
    let i: i16 = 2;

    // floats, shadowing
    let x: f32 = 5.0;
    let y: f32 = 7.0;
    let z = x + y;
    // also f64 floats
    let q: f64 = 15.0;
    println!("{z}");

    let s: &str = "Hello world!";
    println!("{s}");

    let unit = ();
    println!("{unit}");

    // booleans
    let t: bool = true;
    let f = !t;
    println!("{t}");
    println!("{f}");
}
