#ifndef ITER_UNIQUE_EVERSEEN_HPP_
#define ITER_UNIQUE_EVERSEEN_HPP_

#include "internal/iterbase.hpp"
#include "filter.hpp"

#include <type_traits>
#include <functional>
#include <utility>
#include <unordered_set>
#include <iterator>

namespace iter {
  // the container type must be usable in an unordered_map to achieve constant
  // performance checking if it has ever been seen
  template <typename Container>
  auto unique_everseen(Container&& container)
      -> impl::Filtered<std::function<bool(impl::iterator_deref<Container>)>,
          Container> {
    using elem_t = impl::iterator_deref<Container>;
    std::unordered_set<typename std::decay<elem_t>::type> elem_seen;

    std::function<bool(elem_t)> func =
        // has to be captured by value because it goes out of scope when the
        // function returns
        [elem_seen](elem_t e) mutable {
          if (elem_seen.find(e) == std::end(elem_seen)) {
            elem_seen.insert(e);
            return true;
          }
          return false;
        };
    return filter(func, std::forward<Container>(container));
  }

  template <typename T>
  auto unique_everseen(std::initializer_list<T> il)
      -> impl::Filtered<std::function<bool(T)>, std::initializer_list<T>> {
    std::unordered_set<T> elem_seen;
    std::function<bool(T)> func = [elem_seen](const T& e) mutable {
      if (elem_seen.find(e) == std::end(elem_seen)) {
        elem_seen.insert(e);
        return true;
      }
      return false;
    };
    return filter(func, il);
  }
}

#endif
