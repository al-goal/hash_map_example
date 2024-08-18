#include <string>
#include <iostream>
#include <fstream>
#include <limits>
#include <cctype>
#include <algorithm>
#include "word_extractor.hpp"
#include "process_inputs.hpp"

int main(int argc, char** argv)
{
    std::string url = "https://www.gutenberg.org/files/98/98-0.txt";

    // std::string path = "/home/aln/hash_map_example/98-0_short.txt";
    std::string path = "/home/aln/hash_map_example/98-0.txt";

    hash_map_example::WordExtractorCallback callback = hash_map_example::CallbackStreamWrapper(std::cout);
    hash_map_example::WordExtractor extractor(callback); 

    {
        // std::ifstream ifs(path.c_str());
        // auto map = hash_map_example::process_stream(ifs);
        auto map = hash_map_example::process_url(url);

        for (auto& pair : map)
        {
            std::cout << pair.first << " " << pair.second << std::endl;
        }
    }
    // {
    //     std::ifstream ifs(path.c_str());
    //     auto map_histogram = hash_map_example::word_size_histogram(ifs);
    //     for (auto& pair : map_histogram)
    //     {
    //         std::cout << "Word length: " << pair.first << " count: " << pair.second << std::endl;
    //     }
    // }
    


    // while (ifs)
    // {
    //     char c;
    //     ifs.get(c);
    //     extractor.parse_char(c);
    // }


    // std::ifstream ifs(path.c_str());
    // ifs.ignore( std::numeric_limits<std::streamsize>::max() );
    // std::streamsize length = ifs.gcount();
    // ifs.clear();   //  Since ignore will have set eof.
    // ifs.seekg( 0, std::ios_base::beg );

    // std::string buffer;
    // for (int i = 0; i < length; i++)
    // {
    //     char c;
    //     ifs.get(c);
    //     if (std::isalpha(c) && c != '\n' && c != '\r' && c != '\t' && c != ' ')
    //     {
    //         buffer += c;
    //     }
    //     else
    //     {
    //         if (buffer.size() > 0)
    //         {
    //             std::transform(buffer.begin(), buffer.end(), buffer.begin(), ::tolower);
    //             std::cout << buffer << std::endl;
    //             buffer.clear();
    //         }
    //     }
    // }
    return 0;
}