use std::env;

pub fn next_greater_elements(nums: Vec<i32>) -> Vec<i32> {
    let mut nums_extended :Vec<i32> = nums.clone();
    let n = nums.len();
    let mut res : Vec<i32> = vec![-1; n];
    let mut stack : Vec<i32> = Vec::with_capacity(n);

    // Extend the array in order to account for circularity
    for i in 0..n-1 {
        nums_extended.push(nums[i]);
    }

    for i in (0..nums_extended.len()).rev() {
        let el = nums_extended[i];
        while let Some(&top) = stack.last() {
            // Pop any element we don't need anymore
            if top <= el {
                stack.pop();
            } else {
                // This check is needed because we are iterating over
                // the extended version of nums
                if i < n {
                    // If the stack is not empty, its top is the solution
                    res[i] = top;
                }
                break;
            }
        }
        
        stack.push(el);
    }

    res
}

fn main() {
    let args: Vec<String> = env::args().collect();

    if args.len() < 2 {
        println!("Usage: ./next_greater_element nums");
        return;
    }

    let mut elements: Vec<i32> = Vec::new();

    for i in 1..args.len() {
        elements.push(args[i].parse().unwrap());
    }

    let res: Vec<i32> = next_greater_elements(elements);

    println!("{:?}", res);
}
