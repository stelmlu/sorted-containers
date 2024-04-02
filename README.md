Sorted set and map container
============================

These are single-header-file C++11 compatible library that using sorted std::vector to implement std::set and std::map to make it more cpu cache friendly.

Installation
------------

The easiest way to install the library to your C/C++ project is to copy 'n' paste the sorted_set.hpp or sorted.map.hpp to your C++ project and compile it.

```c++
#include "sorted_set.hpp"
#imclude "sorted-map.hpp"
```

Usage
-----

This map support the same functionalty as [std::set](https://en.cppreference.com/w/cpp/container/set) and [std::map](https://en.cppreference.com/w/cpp/container/map) but using the namespace sel instead of std i.e. sel.sorted_set and sel.sorted_map.

```c++
auto mymap = sel::sorted_map<int,int>({{1, 101}, {2, 202}});

mymap.emplace(3, 303);

for(auto pair : mymap) {
    std::cout << "("<< pair.first << ", " << pair.second << ") ";
}

// out: (1, 101) (2, 202) (2, 303)
```

Build
-----

If you want to compile the main.cpp tests.

```bash
git clone https://github.com/stelmlu/sorted_containers.git
cd sorted_containers
cmake -S . -B build
cmake --build build
./build/sorted_container
```

License
-------

Placed in the public domain and also MIT licensed. See end of the header files file for detailed license information.