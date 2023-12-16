#pragma once
#include <iostream>
#include <vector>
#include <stdexcept>
#include <stack>

struct stats {
    size_t comparison_count = 0;
    size_t copy_count = 0;
};

stats insertion_sort(std::vector<int>& arr) {
    stats result;
    size_t n = arr.size();

    for (size_t i = 1; i < n; ++i) {
        int key = arr[i];
        size_t j = i;

        while (j > 0 && arr[j - 1] > key) {
            ++result.comparison_count;
            arr[j] = arr[j - 1];
            ++result.copy_count;
            --j;
        }

        arr[j] = key;
        ++result.copy_count;
    }

    return result;
}

stats comb_sort(std::vector<int>& arr) {
    stats result;
    size_t n = arr.size();
    bool swapped = true;
    size_t gap = n;

    while (gap > 1 || swapped) {
        gap = (gap * 10) / 13;
        if (gap < 1) {
            gap = 1;
        }

        swapped = false;

        for (size_t i = 0; i < n - gap; ++i) {
            size_t j = i + gap;
            ++result.comparison_count;

            if (arr[i] > arr[j]) {
                std::swap(arr[i], arr[j]);
                swapped = true;
                ++result.copy_count;
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

std::ostream& operator<<(std::ostream& os, const std::vector<int>& arr) {
    os << "[";
    for (size_t i = 0; i < arr.size(); ++i) {
        os << arr[i];
        if (i < arr.size() - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

std::vector<int> generate_random_array(size_t size) {
    std::vector<int> arr;
    for (size_t i = 0; i < size; ++i) {
        arr.push_back(rand());
    }
    return arr;
}

std::vector<int> generate_sorted_array(size_t size) {
    std::vector<int> arr;
    for (size_t i = 0; i < size; ++i) {
        arr.push_back(i);
    }
    return arr;
}

std::vector<int> generate_reverse_sorted_array(size_t size) {
    std::vector<int> arr;
    for (size_t i = size; i > 0; --i) {
        arr.push_back(i);
    }
    return arr;
}

stats run_experiment(std::vector<int>& arr, stats(*sort_function)(std::vector<int>&)) {
    std::vector<int> copy = arr; // Create a copy to preserve the original array
    return sort_function(copy);
}

stats run_average_experiment(size_t size, stats(*sort_function)(std::vector<int>&), size_t num_experiments) {
    stats total_stats;
    srand(static_cast<unsigned int>(time(0))); // Seed for random number generation

    for (size_t i = 0; i < num_experiments; ++i) {
        std::vector<int> arr = generate_random_array(size);
        total_stats.comparison_count += run_experiment(arr, sort_function).comparison_count;
        total_stats.copy_count += run_experiment(arr, sort_function).copy_count;
    }

    // Calculate averages
    total_stats.comparison_count /= num_experiments;
    total_stats.copy_count /= num_experiments;

    return total_stats;
}

int main() {
    try {
        std::vector<int> arr = { 5, 2, 9, 1, 5, 6 };
        std::cout << "Original array: " << arr << "\n\n";

        stats result_insertion = insertion_sort(arr);
        std::cout << "Insertion Sort: ";
        std::cout << arr << "\n";
        std::cout << "Comparison count: " << result_insertion.comparison_count << "\n";
        std::cout << "Copy count: " << result_insertion.copy_count << "\n\n";

        std::vector<int> arr2 = { 5, 2, 9, 1, 5, 6 };
       
        stats result_comb = comb_sort(arr2);
        std::cout << "Comb Sort: ";
        std::cout << arr2 << "\n";
        std::cout << "Comparison count: " << result_comb.comparison_count << "\n";
        std::cout << "Copy count: " << result_comb.copy_count << "\n\n";

        std::vector<int> arr3 = { 5, 2, 9, 1, 5, 6 };

        stats result_quick = quick_sort(arr3);
        std::cout << "Quick Sort: ";
        std::cout << arr3 << "\n";
        std::cout << "Comparison count: " << result_quick.comparison_count << "\n";
        std::cout << "Copy count: " << result_quick.copy_count << "\n\n";

        const size_t array_size = 5000;
        const size_t num_experiments = 100;

        // Random array experiment
        stats avg_random_insertion = run_average_experiment(array_size, insertion_sort, num_experiments);
        stats avg_random_comb = run_average_experiment(array_size, comb_sort, num_experiments);
        stats avg_random_quick = run_average_experiment(array_size, quick_sort, num_experiments);

        // Sorted array experiment
        stats avg_sorted_insertion = run_average_experiment(array_size, insertion_sort, num_experiments);
        stats avg_sorted_comb = run_average_experiment(array_size, comb_sort, num_experiments);
        stats avg_sorted_quick = run_average_experiment(array_size, quick_sort, num_experiments);

        // Reverse sorted array experiment
        stats avg_reverse_sorted_insertion = run_average_experiment(array_size, insertion_sort, num_experiments);
        stats avg_reverse_sorted_comb = run_average_experiment(array_size, comb_sort, num_experiments);
        stats avg_reverse_sorted_quick = run_average_experiment(array_size, quick_sort, num_experiments);

        std::cout << "Average Statistics for Random Arrays:\n";
        std::cout << "Insertion Sort - Comparisons: " << avg_random_insertion.comparison_count << ", Copies: " << avg_random_insertion.copy_count << "\n";
        std::cout << "Comb Sort - Comparisons: " << avg_random_comb.comparison_count << ", Copies: " << avg_random_comb.copy_count << "\n";
        std::cout << "Quick Sort - Comparisons: " << avg_random_quick.comparison_count << ", Copies: " << avg_random_quick.copy_count << "\n\n";

        std::cout << "Average Statistics for Sorted Arrays:\n";
        std::cout << "Insertion Sort - Comparisons: " << avg_sorted_insertion.comparison_count << ", Copies: " << avg_sorted_insertion.copy_count << "\n";
        std::cout << "Comb Sort - Comparisons: " << avg_sorted_comb.comparison_count << ", Copies: " << avg_sorted_comb.copy_count << "\n";
        std::cout << "Quick Sort - Comparisons: " << avg_sorted_quick.comparison_count << ", Copies: " << avg_sorted_quick.copy_count << "\n\n";

        std::cout << "Average Statistics for Reverse Sorted Arrays:\n";
        std::cout << "Insertion Sort - Comparisons: " << avg_reverse_sorted_insertion.comparison_count << ", Copies: " << avg_reverse_sorted_insertion.copy_count << "\n";
        std::cout << "Comb Sort - Comparisons: " << avg_reverse_sorted_comb.comparison_count << ", Copies: " << avg_reverse_sorted_comb.copy_count << "\n";
        std::cout << "Quick Sort - Comparisons: " << avg_reverse_sorted_quick.comparison_count << ", Copies: " << avg_reverse_sorted_quick.copy_count << "\n";
    }
    catch (const std::out_of_range& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
    catch (...) {
        std::cerr << "An unexpected error occurred.\n";
    }

    return 0;
}