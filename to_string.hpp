/*! \file to_string.hpp
    \brief Zawiera funkcje przeksztalacajaca dowolny typ danych na string
*/
#ifndef TO_STRING_HPP_INCLUDED
#define TO_STRING_HPP_INCLUDED
#include <sstream>
//! Funkcja przeksztalcajaca typ danych podany w parametrze na string
    /*!
        \param obj zmienna do przeksztalcenia na string
        \return zmienna typu string
    */
template<typename T>
std::string to_string(const T& obj)
{
    std::stringstream ss;
    ss << obj;
    return ss.str();
}

#endif // TO_STRING_HPP_INCLUDED
