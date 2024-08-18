
#include <functional>
#include <string>
#include <iostream>

namespace hash_map_example
{

using WordExtractorCallback = std::function<void(std::string)>;

class WordExtractor
{
    public:

    WordExtractor(WordExtractorCallback& callback);

    void parse_char(char c);

    private:

    std::string word;
    WordExtractorCallback& callback;
};


WordExtractorCallback CallbackStreamWrapper(std::ostream& os);

}