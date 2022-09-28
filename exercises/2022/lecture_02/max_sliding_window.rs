use std::env;
use std::collections::VecDeque;

fn main() {
    let args: Vec<String> = env::args().collect();

    if args.len() < 3 {
        println!("Usage: ./max_sliding_window window_width elements");
        return;
    }

    let window_width = args[1].parse().unwrap();
    let mut elements: Vec<i32> = Vec::new();

    for i in 2..args.len() {
        elements.push(args[i].parse().unwrap());
    }

    let max_vals: Vec<i32> = max_sliding_window(elements, window_width);

    println!("{:?}", max_vals);
}

fn max_sliding_window(nums: Vec<i32>, k: i32) -> Vec<i32> {
    let k = k as usize;
    let mut max_vals: Vec<i32> = Vec::new();
    let mut candidate_queue : VecDeque<i32> = VecDeque::new();
    
    for (i, num) in nums.iter().enumerate() {
        if i >= k && nums[i-k] == *candidate_queue.front().unwrap() {
            candidate_queue.pop_front();
        }
        
        insert_candidate(&mut candidate_queue, num);

        if i >= k - 1 {
            max_vals.push(*candidate_queue.front().unwrap());
        }

    }
    
    return max_vals;
}

fn insert_candidate(queue: &mut VecDeque<i32>, val: &i32) {
    while !queue.is_empty() && queue.back().unwrap() < val {
        queue.pop_back();
    }
        
    queue.push_back(*val);
}