#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <cassert>

#include "sorted_set.hpp"
#include "sorted_map.hpp"

void compare_with_std_set();
void compare_with_std_map();

int main()
{
    compare_with_std_set();
    compare_with_std_map();
}

template<class T>
void assert_set_equal(const std::set<T>& std_set, const sel::sorted_set<T>& sorted_set)
{
    assert(std::vector<T>(std_set.cbegin(), std_set.cend()) == std::vector<T>(sorted_set.cbegin(), sorted_set.cend()));
}

template<class K, class T>
void assert_map_equal(const std::map<K,T>& std_map, const sel::sorted_map<K,T>& sorted_map)
{
    auto left = std::vector<std::pair<K,T>>(std_map.cbegin(), std_map.cend());
    auto right = std::vector<std::pair<K,T>>(sorted_map.cbegin(), sorted_map.cend());

    assert(left == right);
}

void compare_set_constructor()
{
    std::cout << "compare_set_constructor";

    auto list = std::vector<std::string>({"zero", "one", "two", "three"});
    auto std_set = std::set<std::string>(list.begin(), list.end());

    {
        auto sorted_set = sel::sorted_set<std::string>(list.begin(), list.end());
        assert_set_equal(std_set, sorted_set);
    }

    {
        auto sorted_set = sel::sorted_set<std::string>({"zero", "one", "two", "three"});
        assert_set_equal(std_set, sorted_set);
    }

    std::cout << " OK\n";
}

void compare_map_constructor()
{
    std::cout << "compare_map_constructor";

    auto list = std::vector<std::pair<const std::string,int>>({{"zero", 0}, {"one", 1}, {"two", 2}, {"three", 3}});
    auto std_map = std::map<std::string,int>(list.begin(), list.end());

    {
        auto sorted_map = sel::sorted_map<std::string, int>(list.begin(), list.end());
        assert_map_equal(std_map, sorted_map);
    }

    {
        auto sorted_map = sel::sorted_map<std::string, int>({{"zero", 0}, {"one", 1}, {"two", 2}, {"three", 3}});
        assert_map_equal(std_map, sorted_map);
    }

    std::cout << " OK\n";
}

void compare_set_assigns()
{
    std::cout << "compare_set_assigns";

    auto list = std::vector<std::string>({"zero", "one", "two", "three"});
    auto std_set = std::set<std::string>(list.begin(), list.end());

    {
        auto sorted_org_set = sel::sorted_set<std::string>({"zero", "one", "two", "three"});
        auto sorted_set = sorted_org_set;
        assert_set_equal(std_set, sorted_set);
    }

    std::cout << " OK\n";
}

void compare_map_assigns()
{
    std::cout << "compare_map_assigns";

    auto list = std::vector<std::pair<const std::string,int>>({{"zero", 0}, {"one", 1}, {"two", 2}, {"three", 3}});
    auto std_map = std::map<std::string,int>(list.begin(), list.end());

    {
        auto sorted_org_map = sel::sorted_map<std::string, int>({{"zero", 0}, {"one", 1}, {"two", 2}, {"three", 3}});
        auto sorted_map = sorted_org_map;
        assert_map_equal(std_map, sorted_map);
    }

    std::cout << " OK\n";
}

void compare_map_element_access()
{
    std::cout << "compare_map_element_access";

    {
        auto std_map = std::map<std::string,int>({{"zero", 0}, {"one", 1}, {"two", 2}, {"three", 3}});
        auto sorted_map = sel::sorted_map<std::string,int>({{"zero", 0}, {"one", 1}, {"two", 2}, {"three", 3}});

        auto a = std_map.at("one");
        auto b = sorted_map.at("one");

        assert(a == b);

        const auto c = std_map.at("one");
        const auto d = std_map.at("one");

        assert(c == d);
    }

    {
        auto std_map = std::map<std::string,int>({{"zero", 0}, {"one", 1}, {"two", 2}, {"three", 3}});
        auto sorted_map = sel::sorted_map<std::string,int>({{"zero", 0}, {"one", 1}, {"two", 2}, {"three", 3}});
        const auto four = std::string("four");
        const auto three = std::string("three");

        auto a = std_map[four];
        auto b = sorted_map[four];

        assert(a == b);

        std_map[four] = 4;
        sorted_map[four] = 4;

        a = std_map[four];
        b = sorted_map[four];

        assert(a == b);

        a = std_map[three];
        b = sorted_map[three];

        assert(a == b);
    }

    {
        auto std_map = std::map<std::string,int>({{"zero", 0}, {"one", 1}, {"two", 2}, {"three", 3}});
        auto sorted_map = sel::sorted_map<std::string,int>({{"zero", 0}, {"one", 1}, {"two", 2}, {"three", 3}});

        auto a = std_map["four"];
        auto b = sorted_map["four"];

        assert(a == b);

        std_map["four"] = 4;
        sorted_map["four"] = 4;

        a = std_map["four"];
        b = sorted_map["four"];

        assert(a == b);

        a = std_map["three"];
        b = sorted_map["three"];

        assert(a == b);
    }

    std::cout << " OK\n";
}

void compare_set_insert()
{
    std::cout << "compare_set_insert";

    {
        auto std_set = std::set<int>();
        auto sorted_set = sel::sorted_set<int>();
        int v = 1;

        auto std_set_result = std_set.insert(v);
        auto sorted_result = sorted_set.insert(v);

        assert(std_set_result.second == sorted_result.second);

        std_set_result = std_set.insert(v);
        sorted_result = sorted_set.insert(v);

        assert(std_set_result.second == sorted_result.second);
    }

    {
        auto std_set = std::set<int>();
        auto sorted_set = sel::sorted_set<int>();

        auto std_set_result = std_set.insert(1);
        auto sorted_result = sorted_set.insert(1);

        assert(std_set_result.second == sorted_result.second);

        std_set_result = std_set.insert(1);
        sorted_result = sorted_set.insert(1);

        assert(std_set_result.second == sorted_result.second);
    }

    {
        auto std_set = std::set<int>({1, 2, 3, 5, 6});
        auto sorted_set = sel::sorted_set<int>({1, 2, 3, 5, 6});
        int v = 4;

        std_set.insert(std_set.find(5), v);
        sorted_set.insert(sorted_set.find(5), v);

        assert_set_equal(std_set, sorted_set);
    }

    {
        auto std_set = std::set<int>({1, 2, 3, 5, 6});
        auto sorted_set = sel::sorted_set<int>({1, 2, 3, 5, 6});

        std_set.insert(std_set.find(5), 4);
        sorted_set.insert(sorted_set.find(5), 4);

        assert_set_equal(std_set, sorted_set);
    }

    {
        auto list = std::vector<int>({5, 3, 5, 3, 2, 4});
        auto std_set = std::set<int>();
        auto sorted_set = sel::sorted_set<int>();

        std_set.insert(list.begin(), list.end());
        sorted_set.insert(list.begin(), list.end());

        assert_set_equal(std_set, sorted_set);
    }

    {
        auto std_set = std::set<int>();
        auto sorted_set = sel::sorted_set<int>();

        std_set.insert({5, 3, 5, 3, 2, 4});
        sorted_set.insert({5, 3, 5, 3, 2, 4});

        assert_set_equal(std_set, sorted_set);
    }

    std::cout << " OK\n";
}

void compare_map_insert()
{
    std::cout << "compare_map_insert";

    {
        auto std_map = std::map<int,int>();
        auto sorted_map = sel::sorted_map<int,int>();
        auto pair = std::make_pair(1, 101);

        auto std_map_result = std_map.insert(pair);
        auto sorted_map_result = sorted_map.insert(pair);

        assert(std_map_result.second == sorted_map_result.second);

        std_map_result = std_map.insert(pair);
        sorted_map_result = sorted_map.insert(pair);

        assert(std_map_result.second == sorted_map_result.second);
    }

    {
        auto std_map = std::map<int,int>();
        auto sorted_map = sel::sorted_map<int,int>();

        auto std_map_result = std_map.insert(std::make_pair(1, 101));
        auto sorted_map_result = sorted_map.insert(std::make_pair(1, 101));

        assert(std_map_result.second == sorted_map_result.second);

        std_map_result = std_map.insert(std::make_pair(1, 101));
        sorted_map_result = sorted_map.insert(std::make_pair(1, 101));

        assert(std_map_result.second == sorted_map_result.second);
    }

    {
        auto std_map = std::map<int,int>({{1, 101},{2, 202},{3, 303},{5, 505},{6, 606}});
        auto sorted_map = sel::sorted_map<int,int>({{1, 101},{2, 202},{3, 303},{5, 505},{6, 606}});
        auto v = std::make_pair(4, 404);

        std_map.insert(std_map.find(5), v);
        sorted_map.insert(sorted_map.find(5), v);

        assert_map_equal(std_map, sorted_map);
    }

    {
        auto std_map = std::map<int,int>({{1, 101},{2, 202},{3, 303},{5, 505},{6, 606}});
        auto sorted_map = sel::sorted_map<int,int>({{1, 101},{2, 202},{3, 303},{5, 505},{6, 606}});

        std_map.insert(std_map.find(5), std::make_pair(4, 404));
        sorted_map.insert(sorted_map.find(5), std::make_pair(4, 404));

        assert_map_equal(std_map, sorted_map);
    }

    {
        auto list = std::vector<std::pair<int,int>>({{5, 505}, {3, 303}, {5, 505}, {2, 202}, {4, 404}});
        auto std_map = std::map<int,int>();
        auto sorted_map = sel::sorted_map<int,int>();
        
        std_map.insert(list.begin(), list.end());
        sorted_map.insert(list.begin(), list.end());

        assert_map_equal(std_map, sorted_map);
    }

    {
        auto std_map = std::map<int,int>();
        auto sorted_map = sel::sorted_map<int,int>();

        std_map.insert({{5, 505}, {3, 303}, {5, 505}, {2, 202}, {4, 404}});
        sorted_map.insert({{5, 505}, {3, 303}, {5, 505}, {2, 202}, {4, 404}});
    }

    std::cout << " OK\n";
}

void compare_set_emplace()
{
    std::cout << "compare_set_emplace";

    {
        auto std_set = std::set<int>({1, 6, 7});
        auto sorted_set = sel::sorted_set<int>({1, 6, 7});

        auto res_a = std_set.emplace(5);
        auto res_b = sorted_set.emplace(5);

        assert(res_a.second == res_b.second);

        assert_set_equal(std_set, sorted_set);

        res_a = std_set.emplace(5);
        res_b = sorted_set.emplace(5);

        assert(res_a.second == res_b.second);
    }

    {
        auto std_set = std::set<int>({1, 2, 3, 5, 6});
        auto sorted_set = sel::sorted_set<int>({1, 2, 3, 5, 6});

        std_set.emplace_hint(std_set.find(5), 4);
        sorted_set.emplace_hint(sorted_set.find(5), 4);

        assert_set_equal(std_set, sorted_set);
    }

    std::cout << " OK\n";
}

void compare_map_emplace()
{
    std::cout << "compare_map_emplace";

    {
        auto std_map = std::map<int,int>({{1, 101}, {6, 606}, {7, 707}});
        auto sorted_map = sel::sorted_map<int,int>({{1, 101}, {6, 606}, {7, 707}});

        std_map.emplace(5, 505);
        sorted_map.emplace(5, 505);

        assert_map_equal(std_map, sorted_map);
    }

    {
        auto std_map = std::map<int,int>({{1, 101},{2, 202},{3, 303},{5, 505},{6, 606}});
        auto sorted_map = sel::sorted_map<int,int>({{1, 101},{2, 202},{3, 303},{5, 505},{6, 606}});

        std_map.emplace_hint(std_map.find(5), 4, 404);
        sorted_map.emplace_hint(sorted_map.find(5), 4, 404);

        assert_map_equal(std_map, sorted_map);
    }

    std::cout << " OK\n";
}
    
void compare_set_erase()
{
    std::cout << "compare_set_erase";

    {
        auto std_set = std::set<int>({1, 6, 7});
        auto sorted_set = sel::sorted_set<int>({1, 6, 7});

        auto pos_std_set = std_set.find(6);
        auto pos_sorted_set_a = sorted_set.find(6);

        std_set.erase(pos_std_set);
        sorted_set.erase(pos_sorted_set_a);

        assert_set_equal(std_set, sorted_set);
    }

    {
        auto std_set = std::set<int>({5, 2, 4, 1, 8, 3});
        auto sorted_set = sel::sorted_set<int>({5, 2, 4, 1, 8, 3});

        std_set.erase(std_set.find(2), std_set.find(4));
        sorted_set.erase(sorted_set.find(2), sorted_set.find(4));

        assert_set_equal(std_set, sorted_set);
    }

    {
        auto std_set = std::set<int>({5, 2, 4, 1, 8, 3});
        auto sorted_set = sel::sorted_set<int>({5, 2, 4, 1, 8, 3});

        std_set.erase(2);
        sorted_set.erase(2);

        std_set.erase(10);
        sorted_set.erase(10);

        assert_set_equal(std_set, sorted_set);
    }

    std::cout << " OK\n";
}

void compare_map_erase()
{
    std::cout << "compare_map_erase";

    {
        auto std_map = std::map<int,int>({{1, 101}, {6, 606}, {7, 707}});
        auto sorted_map = sel::sorted_map<int,int>({{1, 101}, {6, 606}, {7, 707}});

        auto pos_std_map = std_map.find(6);
        auto pos_sorted_map = sorted_map.find(6);
        
        std_map.erase(pos_std_map);
        sorted_map.erase(pos_sorted_map);

        assert_map_equal(std_map, sorted_map);
    }

    {
        auto std_map = std::map<int,int>({{5., 505}, {2, 202}, {4, 404}, {1, 101}, {8, 808}, {3, 303}});
        auto sorted_map = sel::sorted_map<int,int>({{5, 505}, {2, 202}, {4, 404}, {1, 101}, {8, 808}, {3, 303}});

        std_map.erase(2);
        sorted_map.erase(2);

        std_map.erase(10);
        sorted_map.erase(10);

        assert_map_equal(std_map, sorted_map);
    }

    std::cout << " OK\n";
}

void compare_set_equal_range()
{
    std::cout << "compare_set_equal_range";

    auto std_set = std::set<int>({5, 2, 4, 1, 8, 3});
    auto sorted_set = sel::sorted_set<int>({5, 2, 4, 1, 8, 3});

    auto std_set_range = std_set.equal_range(5);
    auto sorted_set_range = sorted_set.equal_range(5);

    assert(*(std_set_range.first) == 5);
    assert(*(sorted_set_range.first) == 5);

    assert(*(std_set_range.second) == 8);
    assert(*(sorted_set_range.second) == 8);

    std::cout << " OK\n";
}

void  compare_map_equal_range()
{
    std::cout << "compare_map_equal";

    auto std_map = std::map<int,int>({{5., 505}, {2, 202}, {4, 404}, {1, 101}, {8, 808}, {3, 303}});
    auto sorted_map = sel::sorted_map<int,int>({{5, 505}, {2, 202}, {4, 404}, {1, 101}, {8, 808}, {3, 303}});

    auto std_map_range = std_map.equal_range(5);
    auto sorted_map_range = sorted_map.equal_range(5);


    assert(std_map_range.first->first == 5);
    assert(sorted_map_range.first->first == 5);

    assert(std_map_range.second->first == 8);
    assert(sorted_map_range.second->first == 8);

    std::cout << " OK\n";
}

void compare_set_operators()
{
    std::cout << "compare_set_operators";

    auto std_set_left = std::set<int>({5, 2, 4, 1, 8, 3});
    auto std_set_right = std::set<int>({6, 2, 4, 1, 8, 3});

    auto sorted_set_left = sel::sorted_set<int>({5, 2, 4, 1, 8, 3});
    auto sorted_set_right = sel::sorted_set<int>({6, 2, 4, 1, 8, 3});

    bool std_set_eq = std_set_left == std_set_right;
    bool sorted_set_eq = sorted_set_left == sorted_set_right;

    bool std_set_neq = std_set_left != std_set_right;
    bool sorted_set_neq = sorted_set_left != sorted_set_right;

    bool std_set_le = std_set_left < std_set_right;
    bool sorted_set_le = sorted_set_left < sorted_set_right;

    bool std_set_le_eq = std_set_left <= std_set_right;
    bool sorted_set_le_eq = sorted_set_left <= sorted_set_right;

    bool std_set_gr = std_set_left > std_set_right;
    bool sorted_set_gr = sorted_set_left > sorted_set_right;

    bool std_set_gr_eq = std_set_left >= std_set_right;
    bool sorted_set_gr_eq = sorted_set_left >= sorted_set_right;

    assert(std_set_eq == sorted_set_eq);
    assert(std_set_neq == sorted_set_neq);
    assert(std_set_le == sorted_set_le);
    assert(std_set_le_eq == sorted_set_le_eq);
    assert(std_set_gr == sorted_set_gr);
    assert(std_set_gr_eq == sorted_set_eq);

    std::cout << " OK\n";
}

void compare_map_operators()
{
    std::cout << "compare_map_operator";

    auto std_map_left = std::map<int,int>({{5, 505}, {2, 202}, {4, 404}, {1, 101}, {8, 808}, {3, 303}});
    auto std_map_right = std::map<int,int>({{6, 606}, {2, 202}, {4, 404}, {1, 101}, {8, 808}, {3, 303}});

    auto sorted_map_left = sel::sorted_map<int,int>({{5, 505}, {2, 202}, {4, 404}, {1, 101}, {8, 808}, {3, 303}});
    auto sorted_map_right = sel::sorted_map<int,int>({{6, 606}, {2, 202}, {4, 404}, {1, 101}, {8, 808}, {3, 303}});

    bool std_map_eq = std_map_left == std_map_right;
    bool sorted_map_eq = sorted_map_left == sorted_map_right;

    bool std_map_neq = std_map_left != std_map_right;
    bool sorted_map_neq = sorted_map_left != sorted_map_right;

    bool std_map_le = std_map_left < std_map_right;
    bool sorted_map_le = sorted_map_left < sorted_map_right;

    bool std_map_le_eq = std_map_left <= std_map_right;
    bool sorted_map_le_eq = sorted_map_left <= sorted_map_right;

    bool std_map_gr = std_map_left > std_map_right;
    bool sorted_map_gr = sorted_map_left > sorted_map_right;

    bool std_map_gr_eq = std_map_left >= std_map_right;
    bool sorted_map_gr_eq = sorted_map_left >= sorted_map_right;

    assert(std_map_eq == sorted_map_eq);
    assert(std_map_neq == sorted_map_neq);
    assert(std_map_le == sorted_map_le);
    assert(std_map_le_eq == sorted_map_le_eq);
    assert(std_map_gr == sorted_map_gr);
    assert(std_map_gr_eq == sorted_map_eq);

    std::cout << " OK\n";
}

void compare_with_std_set()
{
    compare_set_constructor();
    compare_set_assigns();
    compare_set_insert();
    compare_set_emplace();
    compare_set_erase();
    compare_set_equal_range();
    compare_set_operators();
}

void compare_with_std_map()
{
    compare_map_constructor();
    compare_map_assigns();
    compare_map_element_access();
    compare_map_insert();
    compare_map_emplace();
    compare_map_erase();
    compare_map_equal_range();
    compare_map_operators();
}