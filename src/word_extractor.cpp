#include "word_extractor.hpp" 

namespace hash_map_example
{
WordExtractor::WordExtractor(WordExtractorCallback& callback)
:   callback(callback)
{
}

void WordExtractor::parse_char(char c)
{
    if (std::isalpha(c) && c != '\n' && c != '\r' && c != '\t' && c != ' ')
    {
        word += c;
    }
    else
    {
        if (!word.empty())
        {
            std::transform(word.begin(), word.end(), word.begin(), ::tolower);
            callback(word);
            word.clear();
        }
    }
}

WordExtractorCallback CallbackStreamWrapper(std::ostream& os)
{
    return [&] (std::string word) { os << word << std::endl; };
    // return std::bind(&std::ostream::operator<<, std::ref(os), std::placeholders::_1);
}



}

