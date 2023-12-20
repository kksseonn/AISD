#include <iostream>
#include <vector>
#include <stdexcept>
#include <stack>
#include <ctime>
#include <cstdlib> 

#define SIZE 1000

struct stats {
    size_t comparison_count = 0;
    size_t copy_count = 0;
};

stats insertion_sort(std::vector<int>& arr) {
    stats result;
    int size = arr.size();
    if (size < 2)
        return result;
    for (int i = 1; i < size; ++i) {
        for (int j = i; j > 0; --j) {
            ++result.comparison_count;
            if (arr[j] < arr[j - 1]) {
                std::swap(arr[j], arr[j - 1]);
                ++result.copy_count;
            }
            else {
                break;
            }
        }
    }
    return result;
}

size_t partition(std::vector<int>& arr, size_t low, size_t high, stats& s) {
    int pivot = arr[high];
    size_t i = low;

    for (size_t j = low; j < high; ++j) {
        ++s.comparison_count;
        if (arr[j] <= pivot) {
            std::swap(arr[i], arr[j]);
            ++s.copy_count;
            ++i;
        }
    }

    std::swap(arr[i], arr[high]);
    ++s.copy_count;

    return i;
}

void quicksort(std::vector<int>& arr, size_t low, size_t high, stats& s) {
    std::stack<std::pair<size_t, size_t>> stack;
    stack.push(std::make_pair(low, high));

    while (!stack.empty()) {
        auto top = stack.top();
        stack.pop();

        size_t l = top.first;
        size_t h = top.second;

        if (l < h) {
            size_t pivotIndex = partition(arr, l, h, s);

            if (pivotIndex > 0) {
                stack.push(std::make_pair(l, pivotIndex - 1));
            }
            stack.push(std::make_pair(pivotIndex + 1, h));
        }
    }
}

stats quick_sort(std::vector<int>& arr) {
    stats s;
    quicksort(arr, 0, arr.size() - 1, s);
    return s;
}

stats comb_sort(std::vector<int>& arr) {
    stats result;
    size_t size = arr.size();
    if (size < 2)
        return result;

    double shrink_factor = 1.3; // Шаг уменьшения
    size_t step = size;
    bool swapped = true;

    while (step > 1 || swapped) {
        step = std::max<size_t>(1, static_cast<size_t>(step / shrink_factor));
        swapped = false;
        for (size_t i = 0; i + step < size; ++i) {
            ++result.comparison_count;
            if (arr[i] > arr[i + step]) {
                std::swap(arr[i], arr[i + step]);
                ++result.copy_count;
                swapped = true;
            }
        }
    }

    return result;
}

std::vector<int> generate_random_array(size_t n) {
    std::vector<int> result;
    for (size_t i = 0; i < n; ++i) {
        result.push_back(rand() % 100);
    }
    return result;
}

std::vector<int> generate_sorted_array(size_t n) {
    std::vector<int> result;
    for (size_t i = 0; i < n; ++i) {
        result.push_back(i);
    }
    return result;
}

std::vector<int> generate_inverted_array(size_t n) {
    std::vector<int> result;
    for (int i = n - 1; i >= 0; --i) {
        result.push_back(i);
    }
    return result;
}

int main() {
    
    // Insertion sort for 100 random arrays, 1 sorted, and 1 inverted
    size_t sum_comparison = 0, sum_copy = 0;

    for (int i = 0; i < 100; ++i) {
        std::vector<int> arr = generate_random_array(SIZE);
        stats tmp = insertion_sort(arr);
        sum_comparison += tmp.comparison_count;
        sum_copy += tmp.copy_count;
    }
    std::vector<int> sorted = generate_sorted_array(SIZE);
    stats sorted_stats = insertion_sort(sorted);
    std::vector<int> inverted = generate_inverted_array(SIZE);
    stats inverted_stats = insertion_sort(inverted);

    std::cout << "Insertion sort: Array Size: " << SIZE << "\n\n";
    std::cout << "Average Statistics for Random Arrays: " << " Comparisons: " << sum_comparison / 100 << ", Copies: " << sum_copy / 100 << "\n\n";
    std::cout << "Average Statistics for Sorted Arrays:" << " Comparisons: " << sorted_stats.comparison_count << ", Copies: " << sorted_stats.copy_count << "\n\n";
    std::cout << "Average Statistics for Reverse Arrays:" << " Comparisons: " << inverted_stats.comparison_count << ", Copies: " << inverted_stats.copy_count << "\n\n";
        
    std::cout << "--------------------------------------\n";

    // Quick sort for 100 random arrays, 1 sorted, and 1 inverted
    {
        size_t sum_comparison = 0, sum_copy = 0;

        for (int i = 0; i < 100; ++i) {
            std::vector<int> arr = generate_random_array(SIZE);
            stats tmp = quick_sort(arr);
            sum_comparison += tmp.comparison_count;
            sum_copy += tmp.copy_count;
        }
        std::vector<int> sorted = generate_sorted_array(SIZE);
        stats sorted_stats = quick_sort(sorted);
        std::vector<int> inverted = generate_inverted_array(SIZE);
        stats inverted_stats = quick_sort(inverted);

        std::cout << "Quick sort: Array Size: " << SIZE << "\n\n";
        std::cout << "Average Statistics for Random Arrays: " << "Comparisons: " << sum_comparison / 100 << ", Copies: " << sum_copy / 100 << "\n\n";
        std::cout << "Average Statistics for Sorted Arrays:" << " Comparisons: " << sorted_stats.comparison_count << ", Copies: " << sorted_stats.copy_count << "\n\n";
        std::cout << "Average Statistics for Reverse Arrays:" << " Comparisons: " << inverted_stats.comparison_count << ", Copies: " << inverted_stats.copy_count << "\n\n";

        std::cout << "--------------------------------------\n";
    }
    // Comb sort for 100 random arrays, 1 sorted, and 1 inverted
    {
        size_t sum_comparison = 0, sum_copy = 0;

        for (int i = 0; i < 100; ++i) {
            std::vector<int> arr = generate_random_array(SIZE);
            stats tmp = comb_sort(arr);
            sum_comparison += tmp.comparison_count;
            sum_copy += tmp.copy_count;
        }
        std::vector<int> sorted = generate_sorted_array(SIZE);
        stats sorted_stats = comb_sort(sorted);
        std::vector<int> inverted = generate_inverted_array(SIZE);
        stats inverted_stats = comb_sort(inverted);

        std::cout << "Comb sort: Array Size: " << SIZE << "\n\n";
        std::cout << "Average Statistics for Random Arrays: " << "Comparisons: " << sum_comparison / 100 << ", Copies: " << sum_copy / 100 << "\n\n";
        std::cout << "Average Statistics for Sorted Arrays:" << " Comparisons: " << sorted_stats.comparison_count << ", Copies: " << sorted_stats.copy_count << "\n\n";
        std::cout << "Average Statistics for Reverse Arrays:" << " Comparisons: " << inverted_stats.comparison_count << ", Copies: " << inverted_stats.copy_count << "\n\n";

        std::cout << "--------------------------------------\n";
    }

    return 0;
}