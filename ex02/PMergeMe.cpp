#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &copy) { this->operator=(copy); }

PmergeMe::~PmergeMe() {}

PmergeMe & PmergeMe::operator= (const PmergeMe &copy)
{
        (void)copy;
        return(*this);
}