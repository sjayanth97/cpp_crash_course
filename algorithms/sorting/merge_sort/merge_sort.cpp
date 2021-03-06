// This program shows a simple way to implement merge sort in C++
// By: Nick from CoffeeBeforeArch

#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

// Combine two sorted subvectors
void merge(std::vector<int> &v, unsigned left, unsigned right) {
  // Start of the left sub-vector
  auto l_begin = begin(v) + left;
  // End of the left sub-vector
  auto l_end = begin(v) + (left + right) / 2 + 1;
  // Start of the right sub_vector
  auto r_begin = l_end;
  // End of the right sub_vector
  auto r_end = begin(v) + right + 1;
  
  // Copy the two sub_vectors to simplify the remainder of the code
  std::vector<int> l(l_begin, l_end);
  std::vector<int> r(r_begin, r_end);
  
  // Simplifying temporary variables
  auto l_index = 0u;
  auto r_index = 0u;
  int v_index = left;
  
  // Dump elements into the original vector one at a time
  while(l_index < l.size() && r_index < r.size()) {
    // Take from either the left or right vector and increment the index
    if(l[l_index] <= r[r_index]) {
      v[v_index] = l[l_index++];
    }else {
      v[v_index] = r[r_index++];
    }

    // Move the primary vector index over
    v_index++;
  }

  // Dump the remaining elements
  while(l_index != l.size()) v[v_index++] = l[l_index++];
  while(r_index != r.size()) v[v_index++] = r[r_index++];
}

// Split the vector in half until we have a single element
void merge_sort(std::vector<int> &v, unsigned left, unsigned right) {
  if(left != right){
    // Sort both sides
    merge_sort(v, left, (left + right) / 2);
    merge_sort(v, (left + right) / 2 + 1, right);

    // Combine the results
    merge(v, left, right);
  }
}

int main() {
  // Number of elements to sort
  const unsigned N = 20;

  // Our vector to sort
  std::vector<int> v(N);

  // Set up our random number generator
  std::mt19937 rng;
  rng.seed(std::random_device()());
  std::uniform_int_distribution<int> dist(0, 255);

  // Generate our random inputs
  std::generate(begin(v), end(v), [&]() { return dist(rng); });

  // Dump the potentially unsorted contents
  std::cout << "Before: ";
  for (auto i : v) {
    std::cout << i << " ";
  }
  std::cout << '\n';

  // Sort the vector
  merge_sort(v, 0, N - 1);

  // Dump the sorted contents
  std::cout << "After: ";
  for (auto i : v) {
    std::cout << i << " ";
  }
  std::cout << '\n';

  return 0;
}
