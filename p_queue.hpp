#pragma once

#include <functional>
#include <utility>
#include <vector>
#include <memory>
#include <stdexcept>

template <typename T, typename C = std::less<T>>
class PriorityQueue
{
public:
  PriorityQueue() {}
  PriorityQueue(C compare) : compare(compare) {}

  bool empty() const
  {
    return size == 0;
  }

  void insert(const T &value)
  {
    if (size == CAP)
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

    T *max = lst[0];
    for (int i = 1; i < size; i++)
    {
      T &item = lst[i];
      if (!max || compare(*max, item))
      {
        max = std::addressof(item);
      }
    }

    T ret = std::move(*max);
    *max = lst[size - 1];
    size--;
    return ret;
  }

private:
  constexpr int CAP = 10000;
  int size = 0;
  C compare;
  T[CAP] lst;
};
