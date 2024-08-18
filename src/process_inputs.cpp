#include "process_inputs.hpp"
#include "word_extractor.hpp"
#include <curl/curl.h>

namespace hash_map_example
{

static size_t write_function_direct(void *ptr, size_t size, size_t nmemb, void* data) {
    WordExtractor *extractor = (WordExtractor*) data;

    for (int i = 0; i < size * nmemb; i++)
    {
        extractor->parse_char(((char*) ptr)[i]);
    }

    return size * nmemb;
}

HashMap<std::string, int> process_url(std::string url)
{
    HashMap<std::string, int> hash_map;
    auto curl = curl_easy_init();
    if (curl)
    {

        // The following function takes a word as an argument,
        // loads the word count for it from the hash map,
        // and increments the count by 1.
        WordExtractorCallback callback = [&] (std::string word) { hash_map.insert(word, hash_map.get(word, 0) + 1); };
        WordExtractor extractor(callback);

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_function_direct);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &extractor);

        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        curl = NULL;
    }

    return hash_map;
}

HashMap<std::string, int> process_stream(std::istream& is)
{
    HashMap<std::string, int> map;

    // The following function takes a word as an argument,
    // loads the word count for it from the hash map,
    // and increments the count by 1.
    std::function<void(std::string)> callback = [&] (std::string word) { map.insert(word, map.get(word, 0) + 1); };

    WordExtractor extractor(callback);
    while (is)
    {
        char c;
        is.get(c);
        extractor.parse_char(c);
    }

    return map;
}

HashMap<int, int> word_size_histogram(std::istream& is)
{
    HashMap<int, int> map;
    std::function<void(std::string)> callback = [&] (std::string word) { map.insert(word.size(), map.get(word.size(), 0) + 1); };
    WordExtractor extractor(callback);
    while (is)
    {
        char c;
        is.get(c);
        extractor.parse_char(c);
    }

    return map;
}

} // namespace hash_map_example