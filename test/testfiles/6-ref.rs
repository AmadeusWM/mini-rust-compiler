fn main() {
  let mut x = 5;
  x = x+2;
  let u = &mut x;
  // let v = &x; // niet OK, er is al een mutable borrow
  changer(u);
  println!("{x}");
}

fn changer(z: &mut i32) {
  *z = *z+2;
}
