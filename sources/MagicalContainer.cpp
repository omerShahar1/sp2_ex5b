#include <cstddef>
#include <algorithm>
#include <stdexcept>
#include <valarray>
#include <iostream>
#include "MagicalContainer.hpp"

using namespace ariel;
using namespace std;



const vector<int*> &MagicalContainer::get_prime_point() const 
{
    return prime_point;
}

bool MagicalContainer::is_Prime(int num) 
{
    if (num <= 1) 
    {
        return false;
    }
    if (num == 2) 
    {
        return true;
    }
    if (num % 2 == 0) 
    {
        return false;
    }
    for (int i = 3; i <= sqrt(num); i += 2) 
    {
        if (num % i == 0) 
        {
            return false;
        }
    }
    return true;
}

bool MagicalContainer::check_exist(int num) 
{
    if (find(list_objects.begin(), list_objects.end(), num) != list_objects.end())
    {
        return true;
    }
    return false;
}

MagicalContainer::~MagicalContainer() 
{
    for (size_t j = 0; j < prime_point.size(); ++j) 
    {
        delete prime_point.at(j);
    }

}


void MagicalContainer::addElement(int temp) 
{
    if (!check_exist(temp)) 
    {
        auto iterator = lower_bound(this->list_objects.begin(), this->list_objects.end(), temp);
        this->list_objects.insert(iterator, temp);
        if (is_Prime(temp)) 
        {
            int *number = new int(temp);
            auto it_prime = find_point(this->prime_point, number);
            this->prime_point.insert(it_prime, number);
        }
    }
}

vector<int*>::iterator MagicalContainer::find_point(vector<int*> &vect, int *temp) 
{
    for (auto i = vect.begin(); i != vect.end(); ++i) 
    {
        if (pointers_sorting(temp, *i)) 
        {
            return i;
        }
    }
    return vect.end();
}

void MagicalContainer::removeElement(int temp) 
{
    {
        auto i = find(list_objects.begin(), list_objects.end(), temp);

        if (i != list_objects.end()) 
        {
            list_objects.erase(i);
        } 
        else 
        {
            throw runtime_error("element not found");
        }
    }
}

size_t MagicalContainer::size() const 
{
    return list_objects.size();
}

bool MagicalContainer::pointers_sorting(int *temp1, int *temp2) 
{
    return (*temp1 < *temp2);
}

bool MagicalContainer::operator==(const MagicalContainer &temp) const 
{
    return ((list_objects == temp.list_objects) && (prime_point == temp.prime_point));
}

bool MagicalContainer::operator!=(const MagicalContainer &temp) const 
{
    return !(temp == *this);
}


//AscendingIterator
MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer &temp) : list(temp), iterat(list.list_objects.begin()), cont_size(1) 
{
}


MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator &temp) : list(temp.list), iterat(temp.iterat), cont_size(1) 
{
}

MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator=(const AscendingIterator &temp) 
{
    if (this != &temp) 
    {
        if (list != temp.list)
        {
            throw runtime_error("diffrent list");
        }
        iterat = temp.iterat;
        cont_size = temp.cont_size;
        return *this;
    }
    return *this;
}


bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator &temp) const 
{
    if (list.list_objects != temp.list.list_objects)
    {
        throw runtime_error("diffrent list");
    }
    return ((list == temp.list) && (cont_size == temp.cont_size));
}

bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator &temp) const 
{
    return (!(cont_size == temp.cont_size));
}

bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator &temp) const 
{
    if (list.list_objects != temp.list.list_objects)
    {
        throw runtime_error("diffrent list");
    }
    return (cont_size > temp.cont_size);
}

bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator &temp) const 
{
    if (list.list_objects != temp.list.list_objects)
    {
        throw runtime_error("diffrent list");
    }
    return (cont_size < temp.cont_size);
}

MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++() 
{
    if (iterat == list.list_objects.end()) 
    {
        throw runtime_error("error ++ ");
    }
    iterat++;
    cont_size++;
    return *this;
}

int MagicalContainer::AscendingIterator::operator*() 
{
    if (iterat == list.list_objects.end()) 
    {
        throw runtime_error("error");
    }
    return *iterat;
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin() 
{
    return AscendingIterator(this->list);
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end() 
{
    AscendingIterator temp(this->list);
    temp.iterat = this->list.list_objects.end();
    temp.cont_size = this->list.list_objects.size() + 1;
    return temp;
}

MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator=(MagicalContainer::AscendingIterator &&temp) noexcept 
{
    if (this != &temp) 
    {
        list = temp.list;
        iterat = move(temp.iterat);
        cont_size = temp.cont_size;
    }
    return *this;
}



// SideCrossIterator
MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer &temp) : list(temp), first_e(temp.list_objects.begin()),last_e(--temp.list_objects.end()),flag(true), cont_size(1)
{
}

MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator &temp) : list(temp.list), first_e(temp.list.list_objects.begin()),last_e(--temp.list.list_objects.end()),flag(true), cont_size(1) 
{
}


MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator &temp) 
{
    if (this != &temp) 
    {
        if (list != temp.list)
        {
            throw runtime_error("error = ");
        }
        first_e = temp.first_e;
        last_e = temp.last_e;
        return *this;
    }
    return *this;
}


bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator &temp) const 
{
    if (list.list_objects != temp.list.list_objects)
    {
        throw runtime_error("error == ");
    }
    return (cont_size == temp.cont_size);
}

bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator &temp) const 
{
    return (!(cont_size == temp.cont_size));
}

bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator &temp) const 
{
    if (list.list_objects != temp.list.list_objects)
    {
        throw runtime_error("error > ");
    }
    return (cont_size > temp.cont_size);
}

bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator &temp) const 
{
    if (list.list_objects != temp.list.list_objects)
    {
        throw runtime_error("error < ");
    }
    return (cont_size < temp.cont_size);
}

MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++() 
{
    if (cont_size >= list.size() + 1) 
    {
        throw runtime_error("error ++ ");
    }
    flag ? ++first_e : --last_e;
    flag = !flag;
    ++cont_size;
    return *this;
}

int MagicalContainer::SideCrossIterator::operator*() 
{
    if (cont_size > this->list.size()) 
    {
        throw runtime_error("error * ");
    }
    return flag ? *first_e : *last_e;
}


MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin() 
{
    return SideCrossIterator(list);
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end() 
{
    SideCrossIterator temp(list);
    temp.first_e = list.list_objects.end();
    temp.last_e = list.list_objects.end();
    temp.cont_size = list.size() + 1;
    return temp;
}

MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator=(MagicalContainer::SideCrossIterator &&temp) noexcept 
{
    if (this != &temp) 
    {
        list = temp.list;
        first_e = move(temp.first_e);
        last_e = move(temp.last_e);
        cont_size = temp.cont_size;
    }
    return *this;
}

//PrimeIterator
MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer &temp) : list(temp),iterat(list.prime_point.begin()),cont_size(1) 
{
}

MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator &temp) : list(temp.list), iterat(temp.iterat), cont_size(1) 
{
}

MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator=(const PrimeIterator &temp) 
{
    if (this != &temp) 
    {
        if (list.prime_point != temp.list.prime_point)
        {
            throw runtime_error("error = ");
        }
        this->iterat = temp.iterat;
        return *this;
    }
    return *this;
}

bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator &temp) const 
{
    if (this->list.prime_point != temp.list.prime_point)
    {
        throw runtime_error("erro ==");
    }
    return list == temp.list && this->cont_size == temp.cont_size;
}

bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator &temp) const 
{
    return (!(cont_size == temp.cont_size));
}

bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator &temp) const 
{
    if (this->list.prime_point != temp.list.prime_point)
    {
        throw runtime_error("error > ");
    }
    return this->cont_size > temp.cont_size;
}

bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator &temp) const 
{
    if (this->list.prime_point != temp.list.prime_point)
    {
        throw runtime_error("error < ");
    }
    return this->cont_size < temp.cont_size;
}

MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++() 
{
    if (iterat == list.prime_point.end()) 
    {
        throw runtime_error("error ++");
    }
    iterat++;
    cont_size++;
    return *this;
}

int MagicalContainer::PrimeIterator::operator*() 
{
    if (iterat == list.prime_point.end()) 
    {
        throw runtime_error("error * ");
    }
    return **iterat;
}


MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() 
{
    return PrimeIterator(list);
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() 
{
    PrimeIterator EndPrimeIt(*this);
    EndPrimeIt.iterat = list.prime_point.end();
    EndPrimeIt.cont_size = list.prime_point.size() + 1;
    return EndPrimeIt;
}

MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator=(MagicalContainer::PrimeIterator &&temp) noexcept 
{
    if (this != &temp) 
    {
        list = temp.list;
        iterat = move(temp.iterat);
        cont_size = temp.cont_size;
    }
    return *this;
}
