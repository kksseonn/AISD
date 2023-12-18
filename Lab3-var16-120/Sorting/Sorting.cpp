#include <iostream>
#include <vector>
#include <stdexcept>
#include <stack>
#include <ctime>

struct stats {
    size_t comparison_count = 0;
    size_t copy_count = 0;
};

template <typename Iterator>
stats insertion_sort(Iterator begin, Iterator end) {
    stats result;
    size_t n = std::distance(begin, end);

    for (Iterator i = std::next(begin); i != end; ++i) {
        auto key = *i;
        Iterator j = i;

        while (j != begin && *(std::prev(j)) > key) {
            ++result.comparison_count;
            *j = *(std::prev(j));
            ++result.copy_count;
            --j;
        }

        *j = key;
        ++result.copy_count;
    }

    return result;
}

template <typename Iterator>
stats comb_sort(Iterator begin, Iterator end) {
    stats result;
    size_t n = std::distance(begin, end);
    bool swapped = true;
    size_t gap = n;

    while (gap > 1 || swapped) {
        gap = (gap * 10) / 13;
        if (gap < 1) {
            gap = 1;
        }

        swapped = false;

        for (Iterator i = begin; std::distance(i, end) > gap; ++i) {
            Iterator j = std::next(i, gap);
            ++result.comparison_count;

            if (*i > *j) {
                std::swap(*i, *j);
                swapped = true;
                ++result.copy_count;
            }
        }
    }

    return result;
}

template <typename Iterator>
Iterator partition(Iterator begin, Iterator end, stats& s) {
    Iterator pivot = std::prev(end);
    Iterator i = begin;

    for (Iterator j = begin; j != std::prev(end); ++j) {
        ++s.comparison_count;
        if (*j <= *pivot) {
            std::swap(*i, *j);
            ++s.copy_count;
            ++i;
        }
    }

    std::swap(*i, *pivot);
    ++s.copy_count;

    return i;
}

template <typename Iterator>
void quicksort(Iterator begin, Iterator end, stats& s) {
    std::stack<std::pair<Iterator, Iterator>> stack;
    stack.push(std::make_pair(begin, end));

    while (!stack.empty()) {
        auto top = stack.top();
        stack.pop();

        Iterator l = top.first;
        Iterator h = top.second;

        if (l != h) {
            Iterator pivotIndex = partition(l, h, s);

            if (pivotIndex != begin) {
                stack.push(std::make_pair(l, pivotIndex));
            }
            stack.push(std::make_pair(std::next(pivotIndex), h));
        }
    }
}

template <typename Iterator>
stats quick_sort(Iterator begin, Iterator end) {
    stats s;
    quicksort(begin, end, s);
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

template <typename Iterator>
Iterator generate_random_array(Iterator begin, Iterator end) {
    for (auto it = begin; it != end; ++it) {
        *it = rand();
    }
    return begin;
}

template <typename Iterator>
Iterator generate_sorted_array(Iterator begin, Iterator end) {
    int value = 0;
    for (auto it = begin; it != end; ++it) {
        *it = value++;
    }
    return begin;
}

template <typename Iterator>
Iterator generate_reverse_sorted_array(Iterator begin, Iterator end) {
    int value = static_cast<int>(std::distance(begin, end));
    for (auto it = begin; it != end; ++it) {
        *it = value--;
    }
    return begin;
}

template <typename Iterator>
stats run_experiment(Iterator begin, Iterator end, stats(*sort_function)(Iterator, Iterator)) {
    std::vector<int> copy(begin, end);
    return sort_function(copy.begin(), copy.end());
}

template <typename Iterator>
stats run_average_experiment(Iterator begin, Iterator end, stats(*sort_function)(Iterator, Iterator), size_t num_experiments) {
    stats total_stats;
    srand(static_cast<unsigned int>(time(0)));

    for (size_t i = 0; i < num_experiments; ++i) {
        generate_random_array(begin, end);
        total_stats.comparison_count += run_experiment(begin, end, sort_function).comparison_count;
        total_stats.copy_count += run_experiment(begin, end, sort_function).copy_count;
    }

    // Calculate averages
    total_stats.comparison_count /= num_experiments;
    total_stats.copy_count /= num_experiments;

    return total_stats;
}

int main() {
    try {
        std::vector<int> arr1 = { 5, 2, 9, 1, 5, 6 };
        std::cout << "Original array: ";
        for (const auto& elem : arr1) {
            std::cout << elem << " ";
        }
        std::cout << "\n\n";

        // Insertion sort
        auto insertion_begin = arr1.begin();
        auto insertion_end = arr1.end();
        stats result_insertion = insertion_sort(insertion_begin, insertion_end);
        std::cout << "Insertion Sort: ";
        for (const auto& elem : arr1) {
            std::cout << elem << " ";
        }
        std::cout << "\n";
        std::cout << "Comparison count: " << result_insertion.comparison_count << "\n";
        std::cout << "Copy count: " << result_insertion.copy_count << "\n\n";

        // Comb sort
        std::vector<int> arr2 = { 5, 2, 9, 1, 5, 6 };
        auto comb_begin = arr2.begin();
        auto comb_end = arr2.end();
        stats result_comb = comb_sort(comb_begin, comb_end);
        std::cout << "Comb Sort: ";
        for (const auto& elem : arr2) {
            std::cout << elem << " ";
        }
        std::cout << "\n";
        std::cout << "Comparison count: " << result_comb.comparison_count << "\n";
        std::cout << "Copy count: " << result_comb.copy_count << "\n\n";

        // Quick sort
        std::vector<int> arr3 = { 5, 2, 9, 1, 5, 6 };
        auto quick_begin = arr3.begin();
        auto quick_end = arr3.end();
        stats result_quick = quick_sort(quick_begin, quick_end);
        std::cout << "Quick Sort: ";
        for (const auto& elem : arr3) {
            std::cout << elem << " ";
        }
        std::cout << "\n";
        std::cout << "Comparison count: " << result_quick.comparison_count << "\n";
        std::cout << "Copy count: " << result_quick.copy_count << "\n\n";

        const size_t array_sizes[] = { 1000, 2000, 3000, 10000, 25000, 50000, 100000 };
        const size_t num_experiments = 2;

        for (size_t size : array_sizes) {
            std::vector<int> arr_random(size);
            std::vector<int> arr_sorted(size);
            std::vector<int> arr_reverse_sorted(size);

            // Random array experiment
            stats avg_random_insertion = run_average_experiment(arr_random.begin(), arr_random.end(), insertion_sort, num_experiments);
            stats avg_random_comb = run_average_experiment(arr_random.begin(), arr_random.end(), comb_sort, num_experiments);
            stats avg_random_quick = run_average_experiment(arr_random.begin(), arr_random.end(), quick_sort, num_experiments);

            // Sorted array experiment
            generate_sorted_array(arr_sorted.begin(), arr_sorted.end());
            stats avg_sorted_insertion = run_average_experiment(arr_sorted.begin(), arr_sorted.end(), insertion_sort, num_experiments);
            stats avg_sorted_comb = run_average_experiment(arr_sorted.begin(), arr_sorted.end(), comb_sort, num_experiments);
            stats avg_sorted_quick = run_average_experiment(arr_sorted.begin(), arr_sorted.end(), quick_sort, num_experiments);

            // Reverse sorted array experiment
            generate_reverse_sorted_array(arr_reverse_sorted.begin(), arr_reverse_sorted.end());
            stats avg_reverse_sorted_insertion = run_average_experiment(arr_reverse_sorted.begin(), arr_reverse_sorted.end(), insertion_sort, num_experiments);
            stats avg_reverse_sorted_comb = run_average_experiment(arr_reverse_sorted.begin(), arr_reverse_sorted.end(), comb_sort, num_experiments);
            stats avg_reverse_sorted_quick = run_average_experiment(arr_reverse_sorted.begin(), arr_reverse_sorted.end(), quick_sort, num_experiments);

            // Output results for each array type and size
            std::cout << "Array Size: " << size << "\n";
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

            std::cout << "--------------------------------------\n";
        }
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