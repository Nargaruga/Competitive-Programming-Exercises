use std::env;

fn main() {
    let args: Vec<String> = env::args().collect();

    if args.len() < 2 {
        println!("Usage: ./maximum_subarray elements");
        return;
    }

    let mut elems: Vec<i32> = Vec::new();

    for i in 1..args.len() {
        elems.push(args[i].parse().unwrap());
    }
    
    println!("{}", maximum_subarray(elems));
}

fn maximum_subarray(elems: Vec<i32>) -> i32 {
    let mut current_sum = elems[0];
    let mut max_sum = current_sum;

    for el in elems {
        if current_sum > max_sum {
            max_sum = current_sum;
        }

        // The maximum subarray can't have a negative-value prefix
        if current_sum < 0 {
            current_sum = 0;
        }

        if el + current_sum < 0 {
            current_sum = el;
        } else {
            current_sum += el;
        }
    }

    return max_sum;
}