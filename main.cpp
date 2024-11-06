#include <iostream>
#include <list>
#include <unordered_map>

#include "cache.hpp"

int main() {
  auto SlowGetPage = [](const int &key) -> int { return key; };

  std::cout << "# Enter data in following format:\n"
            << "  n queries, ... (quries)\n\n";

  int n_queries;
  std::cin >> n_queries;
  std::vector<int> queries;
  std::queue<int> queries_queue;

  unsigned curr;
  for (int i = 0; i < n_queries; i++) {
    std::cin >> curr;
    queries.push_back(curr);
    queries_queue.push(curr);
  }
 
  caches::LFU_cache<int, int> cache {3};
  for (int i = 0; i < queries.size(); i++) {
    cache.get<SlowGetPage>(queries[i]);
  }

  std::cout << "LFU hits = " << cache.hits() << '\n';

  caches::Belady_cache<int, int> beladka {3, queries_queue};
  std::cout << "IDEAL hits = " << beladka.hits() << '\n';

  return 0;
}
