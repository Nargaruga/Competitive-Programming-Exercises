use std::env;
use std::cmp;

fn main() {
    let args: Vec<String> = env::args().collect();

    if args.len() < 2 {
        println!("Usage: ./trapping_rainwater heights");
        return;
    }

    let mut heights: Vec<i32> = Vec::new();

    for i in 1..args.len() {
        heights.push(args[i].parse().unwrap());
    }

    println!("{}", trapping_rainwater(heights));
}

// Returns the maximum amount of water that can be contained
// in the provided heightmap.
fn trapping_rainwater(heights: Vec<i32>) -> i32 {
    let mut water = 0;
    let mut left_max: Vec<i32> = vec![0; heights.len()];
    let mut right_max: Vec<i32> = vec![0; heights.len()];
    let mut max = -1;
    
    // Build the prefix-max array
    for (i, &wall) in heights.iter().enumerate() {
        if wall > max {
            max = wall;
        }
        
        left_max[i] = max;
    }
    
    max = -1;
    
    // Build the suffix-max array
    for (i, &wall) in heights.iter().enumerate().rev() {
        if wall > max {
            max = wall;
        }
        
        right_max[i] = max;
    }
    
    // A cell contains an amount of water equal to the height
    // of lowest one among the two walls delimiting the pool minus
    // the height of the wall in the cell itself.
    for (i, &wall) in heights.iter().enumerate() {
        if left_max[i] > wall && right_max[i] > wall {
            water += cmp::min(left_max[i], right_max[i]) - wall;
        }
    }
    
    return water;
}