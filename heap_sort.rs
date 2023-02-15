struct Heap<T> {
    heap: Vec<T>,
    length: usize,
}
impl<T: Ord> Heap<T> {
    fn from_vec(mut arr: Vec<T>) -> Self {
        let length = arr.len();
        Self::heapify(&mut arr);
        Self { heap: arr, length }
    }

    fn new() -> Self {
        Self {
            heap: Vec::new(),
            length: 0,
        }
    }

    fn len(&self) -> usize {
        self.length
    }

    fn is_empty(&self) -> bool {
        self.length == 0
    }

    fn elder_child_index(heap: &[T], parent_index: usize, length: usize) -> usize {
        if !(length > 2 * parent_index + 2)
            || heap[2 * parent_index + 1] > heap[2 * parent_index + 2]
        {
            2 * parent_index + 1
        } else {
            2 * parent_index + 2
        }
    }

    fn heapify(heap: &mut [T]) {
        let mut current_level = (heap.len() as f64).log2() as usize;
        while current_level > 0 {
            for index in 2usize.pow(current_level as u32) - 1
                ..heap.len().min(2usize.pow((current_level + 1) as u32) - 1)
            {
                if heap[index] > heap[(index - 1) / 2] {
                    heap.swap(index, (index - 1) / 2);
                    let mut current_node_index = index;
                    while 2 * current_node_index + 1 < heap.len() {
                        //while not leaf: while has left child
                        let elder_child_index =
                            Self::elder_child_index(heap, current_node_index, heap.len());
                        if heap[elder_child_index] > heap[current_node_index] {
                            heap.swap(current_node_index, elder_child_index);
                            current_node_index = elder_child_index;
                        } else {
                            break;
                        }
                    }
                }
            }
            current_level = current_level - 1;
        }
    }

    fn insert(&mut self, el: T) {
        // the following three lines insert the new element in the end of the actual heap
        self.heap.insert(self.length, el);
        self.length += 1;

        // shift up
        if self.length > 1 {
            let mut el_index = self.length - 1;
            //while not root
            while el_index > 0 && self.heap[el_index] > self.heap[(el_index - 1) / 2] {
                self.heap.swap(el_index, (el_index - 1) / 2);
                el_index = (el_index - 1) / 2;
            }
        }
    }

    // u cant shift the vacancy because this may cause incomplete tree
    fn pop(&mut self) -> T
    where
        T: Clone,
    {
        assert!(!self.is_empty());
        let root = self.heap[0].clone();
        self.remove_front();
        root
    }

    fn remove_front(&mut self) {
        assert!(!self.is_empty());
        // the following three lines swaps the root with the last element of the actual heap
        self.heap.swap(0, self.length - 1);
        self.length = self.length - 1;
        let mut current_node_index = 0usize;

        // shift down
        while 2 * current_node_index + 1 < self.length {
            //while not leaf: while has left child
            let elder_child_index =
                Self::elder_child_index(&self.heap[..self.length], current_node_index, self.length);
            if self.heap[elder_child_index] > self.heap[current_node_index] {
                self.heap.swap(current_node_index, elder_child_index);
                current_node_index = elder_child_index;
            } else {
                break;
            }
        }
    }
}

fn heap_sort<T: Ord>(arr: Vec<T>) -> Vec<T> {
    let mut heap = Heap::from_vec(arr);
    while heap.len() > 0 {
        heap.remove_front();
    }
    heap.heap
}

#[test]
fn test_heap() {
    let pq_size = 1000;
    use rand::{distributions::Uniform, Rng};
    let range = Uniform::from(0..20);
    let values: Vec<i32> = rand::thread_rng()
        .sample_iter(&range)
        .take(pq_size)
        .collect();
    let mut b_h = std::collections::BinaryHeap::<i32>::new();
    let mut my_b_h = Heap::from_vec(values.clone());
    for val in &values {
        b_h.push(*val);
    }

    for _ in 0..values.len() / 2 {
        assert_eq!(b_h.pop().unwrap(), my_b_h.pop())
    }

    for val in &values {
        b_h.push(*val);
        my_b_h.insert(*val);
    }

    for _ in 0..b_h.len() {
        assert_eq!(b_h.pop().unwrap(), my_b_h.pop())
    }
}

#[test]
fn test_sort() {
    let pq_size = 1000;
    use rand::{distributions::Uniform, Rng};
    let range = Uniform::from(0..20);
    let mut values: Vec<i32> = rand::thread_rng()
        .sample_iter(&range)
        .take(pq_size)
        .collect();
    let sorted_by_heap_sort = heap_sort(values.clone());
    values.sort();
    assert_eq!(values, sorted_by_heap_sort)
}
