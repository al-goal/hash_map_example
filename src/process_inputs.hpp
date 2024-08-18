#ifndef HASH_MAP_EXAMPLE_PROCESS_INPUTS_HPP
#define HASH_MAP_EXAMPLE_PROCESS_INPUTS_HPP

#include "hash_map.hpp"

namespace hash_map_example
{

HashMap<std::string, int> process_url(std::string url);
HashMap<std::string, int> process_stream(std::istream& is);

} // namespace hash_map_example

#endif // HASH_MAP_EXAMPLE_PROCESS_INPUTS_HPP