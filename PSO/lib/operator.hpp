#include <vector>
#include <iostream>
#include <cassert>

//================== Operator Vector ============================
// operator +
template<class T>
std::vector<T> operator+(const std::vector<T>& lhs,const std::vector<T>& rhs){
    assert(lhs.size() == rhs.size());
    std::vector<T> add(lhs.size());
    for (int i = 0; i < lhs.size(); i++)
        add.at(i) = lhs.at(i) + rhs.at(i);
    return add;
    
}
// operator -
template<class T>
std::vector<T> operator-(const std::vector<T>& lhs,const std::vector<T>& rhs){
    assert(lhs.size() == rhs.size());
    std::vector<T> add(lhs.size());
    for (int i = 0; i < lhs.size(); i++)
        add.at(i) = lhs.at(i) - rhs.at(i);
    return add;
    
}


// operator *
template<class T,class U>
std::vector<T> operator*(const std::vector<T> &lhs,const U& rhs){
    std::vector<T> mul(lhs.size());
    for (int i = 0; i < lhs.size(); i++)
        mul.at(i) = lhs.at(i)*rhs;
    return mul;
}
//=======================================================================

template<class T,class U>
std::vector<T> operator*(const U& lhs,const std::vector<T>& rhs){
    std::vector<T> mul(rhs.size());
    for (int i = 0; i < rhs.size(); i++)
        mul.at(i) = rhs.at(i)*lhs;
    return mul;
}


// operator << 
template <class T>
std::ostream& operator << (std::ostream& os, const std::vector<T>& v) 
{
    os << "[";
    for (typename std::vector<T>::const_iterator it = v.begin(); it != v.end(); ++it)
    {
        if (it != v.begin()) os << " " << (*it);
        else os << (*it);
    }
    os << "]";
    return os;
}
