#pragma once

#include <functional>
#include <utility>
#include <vector>
#include <memory>
#include <stdexcept>
#include "sort_requirements.hpp"

template <typename T, typename C = std::less<T>>
class PriorityQueue
{
public:
  PriorityQueue(int cap) : PriorityQueue(C(), cap) {}
  PriorityQueue(C compare, int cap) : compare(compare) {
    lst.resize(cap);
    data.name = "Priority Queue";
    data.total_bytes_used = data.max_concurrent_bytes_used = sizeof(*this) + sizeof(T) * cap;
    data.is_stable = false;
    data.is_in_place = false;
    data.input_size = cap;
  }
  bool empty() const
  {
    return size == 0;
  }

  void insert(const T &value)
  {
    if (size == lst.size())
    {
      throw std::runtime_error("Priority queue overflow");
    }
    lst[size] = value;
    size++;
  }

  T deleteMax()
  {
    if (empty())
    {
      throw std::runtime_error("Empty priority queue");
    }

    T *max = &lst[0];
    for (int i = 1; i < size; i++)
    {
      T &item = lst[i];
      data.comparisons++;
      if (compare(*max, item))
      {
        max = &item;
      }
    }

    T ret = std::move(*max);
    *max = lst[size - 1];
    data.swaps++;
    size--;
    return ret;
  }

  sort_data get_data() const {
    sort_data ret = data;
    auto end = std::chrono::high_resolution_clock::now();
    ret.execution_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
    return ret;
  }

private:
  int size = 0;
  C compare;
  std::vector<T> lst;
  sort_data data;
  std::chrono::high_resolution_clock::time_point begin = std::chrono::high_resolution_clock::now();
};
