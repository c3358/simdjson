#pragma once

#ifdef SIMDJSON_IMPLEMENTATION
#if SIMDJSON_EXCEPTIONS

#include "largerandom.h"

namespace largerandom {

using namespace simdjson;
using namespace SIMDJSON_IMPLEMENTATION;
using namespace SIMDJSON_IMPLEMENTATION::stage2;

class OnDemand {
public:
  simdjson_really_inline bool Run(const padded_string &json);
  simdjson_really_inline bool SetUp() { return true; }
  simdjson_really_inline bool TearDown() { return true; }
  simdjson_really_inline const std::vector<my_point> &Records() { return container; }

private:
  ondemand::parser parser;
  std::vector<my_point> container;
};

simdjson_really_inline bool OnDemand::Run(const padded_string &json) {
  container.clear();

  auto doc = parser.iterate(json);
  for (ondemand::object point_object : doc) {
    auto point = point_object.begin();
    container.emplace_back(my_point{(*point).value(), (*++point).value(), (*++point).value()});
  }

  return true;
}

BENCHMARK_TEMPLATE(LargeRandom, OnDemand);

} // namespace largerandom

#endif // SIMDJSON_EXCEPTIONS
#endif // SIMDJSON_IMPLEMENTATION
