use std::collections::HashMap;

fn main() {
    let mut calculations:HashMap<String, f32> = HashMap::new();
    let mut nums = vec![45, 67, 23, 11, 23, 53, 78, 99, 600, 345];
    nums.sort();

    calculate_mean(&nums, &mut calculations);
    calculate_median(&mut nums, &mut calculations);
    calculate_mode(&mut nums, &mut calculations);
    println!("{:?}", calculations);
}

fn calculate_mean(nums:&[usize], calculations:&mut HashMap<String,f32>) {
    let mut total:usize = 0;
    for num in nums {
        total += num;
    }
    calculations.insert(String::from("mean"), (total / nums.len()) as f32);
}

fn calculate_median(nums:&[usize], calculations:&mut HashMap<String, f32>) {
    let middle = nums.len() / 2;
    let median = nums[middle];
    calculations.insert(String::from("median"), median as f32);
}

fn calculate_mode(nums:&[usize], calculations:&mut HashMap<String, f32>) {
    let mut mode_val:i32 = 0;
    let mut mode:i32 = 0;
    let mut nums_amount: HashMap<i32, i32> = HashMap::new();
    for num in nums {
        if nums_amount.contains_key(&(*num as i32)) {
            let count:&i32 = match nums_amount.get(&(*num as i32)) {
                Some(c) => c,
                None => &0,
            };
            let new_count = *count + 1;
            nums_amount.insert(*num as i32, new_count);
        } else {
            nums_amount.insert(*num as i32, 1);
        }
    }
    for (k, v) in &nums_amount {
        if v >= &mode_val {
            mode_val = *v;
            mode = *k;
        }
    }
    calculations.insert(String::from("mode"), mode as f32);
}
