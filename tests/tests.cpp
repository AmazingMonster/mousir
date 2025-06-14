// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0


#include "conceptrodon/functivore/analyzer.hpp"
Conceptrodon::Functivore::Analyzer<void()> x;
#include "mousir/activator.hpp"
#include "mousir/practicer.hpp"
#include "mousir/releasor.hpp"
#include "mousir/correspondence.hpp"
#include <iostream>

int main()
{
    using namespace Mousir;

    int a {0};

    auto activate
    {
        [&a](int x)
        {
            a += x;
            return true;
        }
    };

    auto practice
    {
        [&a](int x, int y)
        {
            a += (x + y);
            return true;
        }
    };

    
    auto release
    {
        [&a](int x, int y, int z)
        {
            a += (x + y + z);
            return true;
        }
    };

    
    auto reset
    {
        [&a]()
        {
            a = 0;
            return true;
        }
    };

    Correspondence<>::Mold<> correspondence {};
    Activator<>::Mold<int>::Mold<int>::Mold<Correspondence<>::Mold<>> act {correspondence};
    act.insert(correspondence.get(), 0, activate);
    Practicer<>::Mold<int>::Mold<int, int>::Mold<Correspondence<>::Mold<>> pra {correspondence};
    pra.insert(0, practice);
    Releasor<>::Mold<int>::Mold<int, int, int>::Mold<Correspondence<>::Mold<>> rel {correspondence};
    rel.insert(correspondence.get(), 1, release);
    Releasor<>::Mold<int>::Mold<>::Mold<Correspondence<>::Mold<>> res {correspondence};
    res.insert(correspondence.get(), 0, reset);

    int key {0};
    int x {0};
    int y {0};
    int z {0};
    while (true) {
        std::cout << "a = " << a << '\n';
        std::cout << "Activate:" << '\n';
        std::cin >> key >> x;
        act.execute(key, x);
        std::cout << "a = " << a << '\n';
        std::cout << "Practice:" << '\n';
        std::cin >> key >> x >> y;
        pra.execute(key, x, y);
        std::cout << "a = " << a << '\n';
        std::cout << "Release:" << '\n';
        std::cin >> key >> x >> y >> z;
        rel.execute(key, x, y, z);
        std::cout << "a = " << a << '\n';
    }
 
    return 0; 
}