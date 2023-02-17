fn partition<T: Ord>(arr: &mut [T], low_idx: usize, high_idx: usize) -> usize {
    let pivot = high_idx;
    let mut idx_for_swapping = low_idx as i32 - 1;
    for idx in low_idx..high_idx {
        if arr[idx] <= arr[pivot] {
            idx_for_swapping += 1;
            arr.swap(idx, idx_for_swapping as usize);
        }
    }
    let new_pivot_idx = idx_for_swapping as usize + 1;
    arr.swap(pivot, new_pivot_idx);
    new_pivot_idx
}
fn quick_sort_impl<T: Ord>(arr: &mut [T], low_idx: usize, high_idx: usize) {
    if low_idx < high_idx {
        let new_pivot_idx = partition(arr, low_idx, high_idx);
        quick_sort_impl(arr, low_idx, new_pivot_idx - 1);
        quick_sort_impl(arr, new_pivot_idx + 1, high_idx);
    }
}

fn quick_sort<T: Ord>(arr: &mut [T]) {
    if arr.len() > 1 {
        quick_sort_impl(arr, 0, arr.len() - 1)
    }
}

#[test]
fn test() {
    let size = 10000;
    use rand::{distributions::Uniform, Rng};
    let range = Uniform::from(0..20);
    let mut values: Vec<i32> = rand::thread_rng().sample_iter(&range).take(size).collect();
    let mut to_be_sorted = values.clone();
    quick_sort(&mut to_be_sorted);
    values.sort();
    assert_eq!(values, to_be_sorted);
}
