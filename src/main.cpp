#include <fstream>
#include "process_inputs.hpp"

int main(int argc, char** argv)
{
    bool calculate_histogram = false;
    if (argc > 1)
    {
        std::string arg = argv[1];
        if (arg == "--histogram")
        {
            calculate_histogram = true;
        }
    }

    try
    {
        if (calculate_histogram)
        {
            std::string path = "/home/aln/hash_map_example/98-0.txt";
            std::ifstream ifs(path.c_str());
            auto map_histogram = hash_map_example::word_size_histogram(ifs);
            double count = 0;
            for (auto& pair : map_histogram)
            {
                count += pair.second;
            }
            for (auto& pair : map_histogram)
            {
                std::cout << pair.first << " " << pair.second << " (" << 100*pair.second/count << " %)" << std::endl;
            }
        }
        else
        {
            std::string url = "https://www.gutenberg.org/files/98/98-0.txt";
            auto map = hash_map_example::process_url(url);
            for (auto& pair : map)
            {
                std::cout << pair.first << " " << pair.second << std::endl;
            }
        }
        return 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
}