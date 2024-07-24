#include "PmergeMe.hpp"

void printInitialState(int argc, char** argv, size_t limit) {
    size_t count = 0;
    for (int i = 1; i < argc && count < limit; ++i, ++count) {
        if (count > 0) std::cout << " ";
        std::cout << argv[i];
    }
    if (static_cast<size_t>(argc) > limit)
        std::cout << " [...] \n"<< std::endl;
    else
        std::cout << std::endl << std::endl;
}

template <typename Container>
void printArray(const Container& arr, size_t limit) {
    size_t count = 0;
    for (typename Container::const_iterator it = arr.begin(); it != arr.end() && count < limit; ++it, ++count) {
        if (count > 0) std::cout << " ";
        std::cout << *it;
    }
    if (arr.size() > limit)
        std::cout << " [...] \n"<< std::endl;
    else
        std::cout << std::endl << std::endl;
}

template <typename PairContainer>
void sort_each_pair(PairContainer& split_array) {
    for (size_t i = 0; i < split_array.size(); ++i) {
        if (split_array[i].first > split_array[i].second)
            std::swap(split_array[i].first, split_array[i].second);
    }
}

/**
 * Sorts a deque of integer pairs in ascending order based on their second elements using binary insertion sort.
 * This method iterates over each pair, performing a binary search to find the correct insertion point for the current pair,
 * then shifts the subsequent elements to make room for inserting the pair at its sorted position.
 *
 * @param pairs A reference to a deque of integer pairs to be sorted.
 */
void binary_insertion_sort_pairs(std::deque<std::pair<int, int> >& pairs) {
    for (size_t currentPosition = 1; currentPosition < pairs.size(); ++currentPosition) {
        std::pair<int, int> currentPair = pairs[currentPosition];
        int startPosition = 0;
        int endPosition = currentPosition - 1;
        while (startPosition <= endPosition) {
            int middlePosition = startPosition + (endPosition - startPosition) / 2;
            if (pairs[middlePosition].second > currentPair.second)
                endPosition = middlePosition - 1;
            else
                startPosition = middlePosition + 1;
        }
        for (int shiftPosition = currentPosition - 1; shiftPosition >= startPosition; --shiftPosition)
            pairs[shiftPosition + 1] = pairs[shiftPosition];
        pairs[startPosition] = currentPair;
    }
}


/**
 * Merges and sorts integers from pairs in a deque.
 * This function first sorts the elements within each pair in the deque and then applies a binary insertion sort on the deque based on the second element of the pairs.
 * It then merges the sorted pairs into a single deque of integers, maintaining sorted order, and inserts the second element of each pair at its appropriate position.
 *
 * @param pairs A reference to a deque of integer pairs to be merged and sorted.
 * @param hasStraggler A boolean indicating whether there is an additional 'straggler' integer to insert.
 * @param straggler The 'straggler' integer to be inserted if hasStraggler is true.
 * @return A deque of integers, sorted in ascending order, that merges all integers from the pairs and the optional straggler.
 */
std::deque<int> merge_pairs(std::deque<std::pair<int, int> >& pairs, bool hasStraggler, int straggler) {
    sort_each_pair(pairs);
    binary_insertion_sort_pairs(pairs);

    std::deque<int> sorted;
    for (size_t i = 0; i < pairs.size(); ++i)
        sorted.push_back(pairs[i].second);
    for (size_t i = 0; i < pairs.size(); ++i) {
        std::deque<int>::iterator insertPos = std::lower_bound(sorted.begin(), sorted.end(), pairs[i].first);
        sorted.insert(insertPos, pairs[i].first);
    }
    if (hasStraggler) {
        std::deque<int>::iterator insertPos = std::lower_bound(sorted.begin(), sorted.end(), straggler);
        sorted.insert(insertPos, straggler);
    }
    return (sorted);
}

void binary_insertion_sort_pairs(std::vector<std::pair<int, int> >& pairs) {
    for (size_t currentPosition = 1; currentPosition < pairs.size(); ++currentPosition) {
        std::pair<int, int> currentPair = pairs[currentPosition];
        int startPosition = 0;
        int endPosition = currentPosition - 1;
        while (startPosition <= endPosition) {
            int middlePosition = startPosition + (endPosition - startPosition) / 2;
            if (pairs[middlePosition].second > currentPair.second)
                endPosition = middlePosition - 1;
            else
                startPosition = middlePosition + 1;
        }
        for (int shiftPosition = currentPosition - 1; shiftPosition >= startPosition; --shiftPosition)
            pairs[shiftPosition + 1] = pairs[shiftPosition];
        pairs[startPosition] = currentPair;
    }
}

std::vector<int> merge_pairs(std::vector<std::pair<int, int> >& pairs, bool hasStraggler, int straggler) {
    sort_each_pair(pairs);
    binary_insertion_sort_pairs(pairs);

    std::vector<int> sorted;
    for (size_t i = 0; i < pairs.size(); ++i)
        sorted.push_back(pairs[i].second);
    for (size_t i = 0; i < pairs.size(); ++i) {
        std::vector<int>::iterator insertPos = std::lower_bound(sorted.begin(), sorted.end(), pairs[i].first);
        sorted.insert(insertPos, pairs[i].first);
    }
    if (hasStraggler) {
        std::vector<int>::iterator insertPos = std::lower_bound(sorted.begin(), sorted.end(), straggler);
        sorted.insert(insertPos, straggler);
    }
    return (sorted);
}

/**
 * Parses command-line arguments into integer pairs and an optional single 'straggler' integer. Validates for duplicates and
 * ensures input integrity. If an odd number of valid integers is provided, the last one is treated as a 'straggler'.
 *
 * @param argc Number of command-line arguments.
 * @param argv Command-line arguments.
 * @param pairs Container for storing integer pairs.
 * @param hasStraggler Indicates the presence of a 'straggler' integer.
 * @param straggler The 'straggler' integer, if present.
 * @return True on successful parsing and validation, False on errors or duplicates.
 */
template <typename PairContainer>
bool processArguments(int argc, char* argv[], PairContainer& pairs, bool& hasStraggler, int& straggler) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <list of integers>\n";
        return false;
    }

    std::vector<int> seenIntegers;
    for (int i = 1; i < argc; i += 2) {
        int number;
        char check;
        std::istringstream iss(argv[i]);
        if (!(iss >> number) || iss.get(check)) {
            std::cerr << "Invalid input: " << argv[i] << std::endl;
            return false;
        }

        if (std::find(seenIntegers.begin(), seenIntegers.end(), number) != seenIntegers.end()) {
            std::cerr << "Duplicate input: " << number << std::endl;
            return false;
        }
        seenIntegers.push_back(number);

        if (i + 1 < argc) {
            std::istringstream iss2(argv[i + 1]);
            int second;
            if (!(iss2 >> second) || iss2.get(check)) {
                std::cerr << "Invalid input: " << argv[i + 1] << std::endl;
                return false;
            }
            if (std::find(seenIntegers.begin(), seenIntegers.end(), second) != seenIntegers.end()) {
                std::cerr << "Duplicate input: " << second << std::endl;
                return false;
            }
            seenIntegers.push_back(second);
            pairs.push_back(std::make_pair(number, second));
        } else {
            hasStraggler = true;
            straggler = number;
        }
    }
    return true;
}

template <typename Container>
bool isSorted(const Container& container) {
    typename Container::const_iterator it = container.begin();
    if (it == container.end()) return true;
    typename Container::value_type lastValue = *it;
    while (++it != container.end()) {
        if (lastValue > *it) return false;
        lastValue = *it;
    }
    return true;
}

int main(int argc, char* argv[]) {
    bool hasStraggler = false;
    int straggler = 0;
    std::vector<std::pair<int, int> > pairVec;
    std::deque<std::pair<int, int> > pairDeque;

    if (!processArguments(argc, argv, pairVec, hasStraggler, straggler))
        return (1);

    std::cout << "Before sorting :" << std::endl;
    printInitialState(argc, argv, 300);
    clock_t start = clock();
    std::vector<int> sortedVec = merge_pairs(pairVec, hasStraggler, straggler);
    clock_t end = clock();
    double timeVec = 1000000.0 * (end - start) / CLOCKS_PER_SEC;
    std::cout << "After sorting Vector:" << std::endl;
    printArray(sortedVec, 300);
    if (!isSorted(sortedVec)) {
        std::cout << "Vector is not sorted.\n";
        return (1);
    } else {
        std::cout << GREEN << "Sorted: OK" << RESET << "\n" << std::endl;
    }

    hasStraggler = false;
    straggler = 0;

    if (!processArguments(argc, argv, pairDeque, hasStraggler, straggler))
        return (1);

    start = clock();
    std::deque<int> sortedDeque = merge_pairs(pairDeque, hasStraggler, straggler);
    end = clock();
    double timeDeque = 1000000.0 * (end - start) / CLOCKS_PER_SEC;
    std::cout << "After sorting Deque:" << std::endl;
    printArray(sortedDeque, 300);
    if (!isSorted(sortedDeque)) {
        std::cout << "Deque is not sorted.\n";
        return (1);
    } else {
        std::cout << GREEN << "Sorted: OK" << RESET << "\n" << std::endl;
    }
    
    std::cout << "Vector Sort Time for " << argc - 1 << " elements " << timeVec << " μs" << std::endl;
    std::cout << "Deque Sort Time for " << argc - 1 << " elements " << timeDeque << " μs" << std::endl;
    
    return (0);
}