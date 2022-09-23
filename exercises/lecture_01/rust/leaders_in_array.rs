use std::env;

fn main() {
    let args: Vec<String> = env::args().collect();

    if args.len() < 2 {
        println!("Usage: ./leaders_in_array elements");
        return;
    }

    let mut elems: Vec<i32> = Vec::new();

    for i in 1..args.len() {
        elems.push(args[i].parse().unwrap());
    }

    let leaders : Vec<i32> = leaders_in_array(elems);
    for leader in leaders.iter().rev() {
        println!("{}", leader);
    }
}

fn leaders_in_array(elems: Vec<i32>) -> Vec<i32> {
    let mut max = -1;
    let mut leaders: Vec<i32> = Vec::new();

    // Each element is marked as leader if it is greater than or
    // equal to every element on its right.
    for i in (0..elems.len()).rev() {
        if elems[i] > max {
            max = elems[i];
            leaders.push(elems[i]);
        }
    }

    return leaders
}
