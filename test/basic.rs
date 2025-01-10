fn factorial(n: i32) -> i32 {
    return calc(n);             // using function thats defined later
    fn calc(n: i32) -> i32 {
        if n <= 1 {  
            1
        } else {
            n * factorial(n - 1) 
        }
    }
}

fn count_even(n: i32) {
    let mut i = 0;  
    while i < n { 
        if i % 2 == 0 {      // print in loop
            println!("{i}");   
        };
        i = i + 1;
    };
}

fn main() {
    let x = 5;
    let mut y = 10;
    let sum = x + y;
    println!("{sum}");  // math operator 
    
    let fact5 = factorial(5);
    println!("{fact5}");    // recursive function
    
    if fact5 > 100 {  // conditional
        println!("1");
    } else {
        println!("0");
    };
    
    count_even(10);
    
    let block_result = {    // block assignment with implicit return
        let a = 5;
        let b = 10;
        a + b  
    };
    println!("{block_result}");
}
