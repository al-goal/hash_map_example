#include "process_inputs.hpp"
#include "word_extractor.hpp"
#include <curl/curl.h>

namespace hash_map_example
{

HashMap<std::string, int> process_url(std::string url)
{
    HashMap<std::string, int> hash_map;
    // auto curl = curl_easy_init();
    // if (curl)
    // {
    //     StreamEventHandler event_handler(os);
    //     MiniJsonParser parser(event_handler);
    //     std::string response_string;
    //     curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    //     curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);

    //     if (use_buffer)
    //     {
    //         curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_function_buffered);
    //         curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
    //     }
    //     else
    //     {
    //         curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_function_direct);
    //         curl_easy_setopt(curl, CURLOPT_WRITEDATA, &parser);

    //     }
    //     curl_easy_perform(curl);

    //     if (use_buffer)
    //     {
    //         long response_code;
    //         curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
    //         if (response_code != 200)
    //         {
    //             os << "Error: " << response_code << std::endl;
    //             return;
    //         }
    //         std::istringstream is(response_string);
    //         process_stream(is, os);
    //     }

    //     curl_easy_cleanup(curl);
    //     curl = NULL;
    // }

    return hash_map;
}

HashMap<std::string, int> process_stream(std::istream& is)
{
    HashMap<std::string, int> map;
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

} // namespace hash_map_example