#pragma once

#include <cstddef>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

namespace cpptools::core::traits {

    // =====================================================
    // 1. 默认定义（唯一真源）
    // =====================================================
    template <typename T>
    struct container_category_defaults {
        // ---- 基本属性 ----
        static constexpr bool is_container = false;

        // ---- 关联式 ----
        static constexpr bool is_map = false;
        static constexpr bool is_set = false;

        // ---- map 细分 ----
        static constexpr bool is_singlemap = false;
        static constexpr bool is_multimap = false;

        // ---- unordered ----
        static constexpr bool is_unordered = false;
    };


    // =====================================================
    // 2. 主 traits（继承默认）
    // =====================================================
    template <typename T>
    struct container_category
        : container_category_defaults<T> {};


    // =====================================================
    // 3. std::map
    // =====================================================
    template <typename K, typename V, typename C, typename A>
    struct container_category<std::map<K, V, C, A>>
        : container_category_defaults<std::map<K, V, C, A>> {

        static constexpr bool is_container = true;
        static constexpr bool is_map = true;
        static constexpr bool is_singlemap = true;
    };


    // =====================================================
    // 4. std::multimap
    // =====================================================
    template <typename K, typename V, typename C, typename A>
    struct container_category<std::multimap<K, V, C, A>>
        : container_category_defaults<std::multimap<K, V, C, A>> {

        static constexpr bool is_container = true;
        static constexpr bool is_map = true;
        static constexpr bool is_multimap = true;
    };


    // =====================================================
    // 5. std::set
    // =====================================================
    template <typename K, typename C, typename A>
    struct container_category<std::set<K, C, A>>
        : container_category_defaults<std::set<K, C, A>> {

        static constexpr bool is_container = true;
        static constexpr bool is_set = true;
        static constexpr bool is_singlemap = true;
    };


    // =====================================================
    // 6. std::multiset
    // =====================================================
    template <typename K, typename C, typename A>
    struct container_category<std::multiset<K, C, A>>
        : container_category_defaults<std::multiset<K, C, A>> {

        static constexpr bool is_container = true;
        static constexpr bool is_set = true;
        static constexpr bool is_multimap = true;
    };


    // =====================================================
    // 7. unordered_map
    // =====================================================
    template <typename K, typename V, typename H, typename E, typename A>
    struct container_category<std::unordered_map<K, V, H, E, A>>
        : container_category_defaults<std::unordered_map<K, V, H, E, A>> {

        static constexpr bool is_container = true;
        static constexpr bool is_map = true;
        static constexpr bool is_singlemap = true;
        static constexpr bool is_unordered = true;
    };


    // =====================================================
    // 8. unordered_multimap
    // =====================================================
    template <typename K, typename V, typename H, typename E, typename A>
    struct container_category<std::unordered_multimap<K, V, H, E, A>>
        : container_category_defaults<std::unordered_multimap<K, V, H, E, A>> {

        static constexpr bool is_container = true;
        static constexpr bool is_map = true;
        static constexpr bool is_multimap = true;
        static constexpr bool is_unordered = true;
    };

} // namespace cpptools::core::traits

