use parameterized::parameterized;
use std::collections::BTreeMap;

//impl Solution {
pub fn two_sum(nums: Vec<i32>, target: i32) -> Vec<i32> {
    // Recall solution:
    // Create binary tree map to index each item
    // If we see required number ever then fabulous we done
    let mut nums_found: BTreeMap<i32, i32> = BTreeMap::new();

    for (i, x) in nums.iter().enumerate() {
        // Identify required "partner"
        let num_req = target - x;
        match nums_found.get(&num_req) {
            Some(num_found) => return vec![*num_found, i.try_into().expect("usize to i32 conversion failed")],
            None => (),
        }

        // Else just add this value to tree 
        // Actually doesn't matter if keys are duplicated - only time we need to 
        // care about duplicate values is if they're correct, which is already
        // handled by above code
        nums_found.insert(*x, i.try_into().expect("usize to i32 conversion failed"));
    }

    Vec::new()
}
//}

#[cfg(test)]
mod tests {
    use super::*;

    fn vec_cmp_sym(vec1: Vec<i32>, vec2: Vec<i32>) -> bool {
        (vec1[0] == vec2[0] && vec1[1] == vec2[1]) || (vec1[1] == vec2[0] && vec1[0] == vec2[1])
    }

    #[parameterized(nums = {
        vec![2,7,11,15], vec![3,2,4], vec![3, 3]
    }, target = {
        9, 6, 6,
    }, result = {
        vec![0,1], vec![1, 2], vec![0, 1],
    })]
    fn basic(nums: Vec<i32>, target: i32, result: Vec<i32>) {
        let test_result = two_sum(nums, target);
        assert_eq!(test_result.len(), 2);
        assert!(vec_cmp_sym(test_result, result));
    }
}


fn main() {
    println!("No actual code here!");
}
