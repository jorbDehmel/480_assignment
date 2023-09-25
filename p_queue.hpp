#pragma once

#include <functional>
#include <utility>
#include <vector>
#include <memory>
#include <stdexcept>

template <typename T, typename C = std::less<T>>
class PriorityQueue {
  public:
    PriorityQueue() {}
    PriorityQueue(C compare) : compare(compare) {}

    bool empty() const {
      return lst.empty();
    }

    void insert(const T& value) {
      lst.push_back(value);
    }

    void insert(T&& value) {
      lst.push_back(std::move(value));
    }

    T deleteMax() {
      if (lst.empty()) {
        throw std::runtime_error("Empty priority queue");
      }

      T* max = lst.data();
      auto lst_iter = lst.begin();
      ++lst_iter;
      for (;lst_iter != lst.end(); ++lst_iter) {
        T& item = *lst_iter;
        if (!max || compare(*max, item)) {
          max = std::addressof(item);
        }
      }

      T ret = std::move(*max);
      *max = std::move(lst.back());
      lst.pop_back();
      return ret;
    }
  private:
    C compare;
    std::vector<T> lst;
};
