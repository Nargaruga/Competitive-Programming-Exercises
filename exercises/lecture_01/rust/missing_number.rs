use std::env;

fn main() {
    let args: Vec<String> = env::args().collect();

    if args.len() < 2 {
        println!("Usage: ./missing_number elements");
        return;
    }

    let mut elems: Vec<i32> = Vec::new();

    for i in 1..args.len() {
        elems.push(args[i].parse().unwrap());
    }

    println!("{}", missing_number(elems));
}

// Returns the missing element in the vector.
// This assumes that the vector is in the form
// [0..n] with exactly one missing element. 
fn missing_number(nums: Vec<i32>) -> i32 {
    let mut sum = 0;
    let n = nums.len() as i32;
    let target_sum = n * (n+1) / 2;
    
    for v in nums {           
        sum += v;
    }
    
    return target_sum - sum;        
}