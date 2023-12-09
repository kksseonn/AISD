#pragma once
#include <iostream>
#include <vector>
#include <stdexcept>

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

int main() {
    try {
        std::vector<int> arr = { 5, 2, 9, 1, 5, 6 };
        std::cout << "Original array: " << arr << "\n\n";

        stats result_insertion = insertion_sort(arr);
        std::cout << "Insertion Sort: ";
        std::cout << arr << "\n";
        std::cout << "Comparison count: " << result_insertion.comparison_count << "\n";
        std::cout << "Copy count: " << result_insertion.copy_count << "\n";
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