#pragma once
#include <memory>
#include <optional>
#include <vector>

/**
* P is a shorthand for std::unique_ptr
*/
template <typename T> using P = std::unique_ptr<T>;

template <typename T> using Opt = std::optional<T>;

template <typename T> using Vec = std::vector<T>;

/**
 * overloaded operator() for std::visit
 * ```
 * std::visit(overloaded{
 *    [](int i) { std::cout << i << std::endl; }, // only called for int
 *   [](auto _other) { std::cout << _other << std::endl; }, // can be used to handle all other types
 * });
 * ```
 */
template<class... Ts>
struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;
