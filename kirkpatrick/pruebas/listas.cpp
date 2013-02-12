/*
 * =====================================================================================
 *
 *       Filename:  listas.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/11/2013 09:41:48 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <list>
#include <iostream>

int main() {
    std::list<int> lista;
    lista.push_back(1);
    lista.push_back(2);
    lista.push_back(3);
    std::list<int>::iterator it = lista.begin();
    std::advance(it, 1);
    int i = *(it);
    std::cout<<i;
    return 0;

}
