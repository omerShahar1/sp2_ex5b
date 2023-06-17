#include <vector>
#include <cstddef>

#pragma once
using namespace std;
namespace ariel 
{

    class MagicalContainer 
    {
    private:
        vector<int> list_objects;
        vector<int *> prime_point;

    public:
       
        MagicalContainer() = default;
        ~MagicalContainer() ;
        MagicalContainer(const MagicalContainer &) = default;
        MagicalContainer(MagicalContainer &&) = default;
        MagicalContainer &operator=(MagicalContainer &&) = default;
        MagicalContainer &operator=(const MagicalContainer &) = default;
        void addElement(int);
        void removeElement(int);
        bool is_Prime(int);
        size_t size() const;
        bool pointers_sorting(int *, int *);
        vector<int*>::iterator find_point(vector<int *> &, int *);
        bool check_exist(int);
        bool operator==(const MagicalContainer &) const;
        bool operator!=(const MagicalContainer &) const;
        const vector<int *> &get_prime_point() const;

//Iterators Classes
        //AscendingIterator
      
        class AscendingIterator 
        {
            MagicalContainer &list;
            vector<int>::iterator iterat;
            size_t cont_size;

        public:
            explicit AscendingIterator(MagicalContainer &);
            AscendingIterator(const AscendingIterator &);
            AscendingIterator(AscendingIterator &&) = default;
            AscendingIterator &operator=(const AscendingIterator &);
            ~AscendingIterator() = default;
            bool operator==(const AscendingIterator &) const;
            bool operator!=(const AscendingIterator &) const;
            bool operator>(const AscendingIterator &) const;
            bool operator<(const AscendingIterator &) const;
            AscendingIterator &operator++();
            int operator*();
            AscendingIterator begin();
            AscendingIterator end();
            AscendingIterator &operator=(AscendingIterator &&) noexcept;
        };

        // SideCrossIterator
        class SideCrossIterator 
        {
            MagicalContainer &list;
            vector<int>::iterator first_e;
            vector<int>::iterator last_e;
            bool flag; //true=front, false=end
            size_t cont_size;


        public:
            explicit SideCrossIterator(MagicalContainer &);
            SideCrossIterator(const SideCrossIterator &);
            SideCrossIterator(SideCrossIterator &&) = default;
            SideCrossIterator &operator=(const SideCrossIterator &);
            ~SideCrossIterator() = default;
            bool operator==(const SideCrossIterator &) const;
            bool operator!=(const SideCrossIterator &) const;
            bool operator>(const SideCrossIterator &) const;
            bool operator<(const SideCrossIterator &) const;
            SideCrossIterator &operator++();
            int operator*();
            SideCrossIterator begin();
            SideCrossIterator end();
            SideCrossIterator &operator=(SideCrossIterator &&) noexcept;
        };

        //PrimeIterator
        class PrimeIterator 
        {
            MagicalContainer &list;
            vector<int *>::iterator iterat;
            size_t cont_size;
        public:
            explicit PrimeIterator(MagicalContainer &);
            PrimeIterator(const PrimeIterator &);
            PrimeIterator(PrimeIterator &&) = default;
            PrimeIterator &operator=(const PrimeIterator &);
            ~PrimeIterator() = default;
            bool operator==(const PrimeIterator &) const;
            bool operator!=(const PrimeIterator &) const;
            bool operator>(const PrimeIterator &) const;
            bool operator<(const PrimeIterator &) const;
            PrimeIterator &operator++();
            int operator*();
            PrimeIterator begin();
            PrimeIterator end();
            PrimeIterator &operator=(PrimeIterator &&) noexcept;
        };


    };
}