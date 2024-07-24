#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <sstream>
#include <utility>
#include <algorithm>
#include <string>
#include <ctime>
#include <utility>

#define GREEN "\033[32m"
#define RESET "\033[0m"

class PmergeMe
{
    public:
        PmergeMe ();
        PmergeMe (const PmergeMe &a);
        ~PmergeMe ();
        PmergeMe & operator = (const PmergeMe &a);
};

#endif
