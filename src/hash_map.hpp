#include <functional>
#include <list>

namespace hash_map_example
{

template <typename T_Key, typename T_Value> class HashMap
{
public:

    using KeyValuePair = std::pair<T_Key, T_Value>;
    using HashFunction = std::function<int(T_Key)>;
    using Bucket = std::list<KeyValuePair>;

    HashMap();
    ~HashMap();

    void insert(const T_Key& key, const T_Value& value)
    {
        auto bucket = get_bucket(key);
        for (auto& pair : bucket)
        {
            if (pair.first == key)
            {
                pair.second = value;
                return;
            }
        }
        bucket.push_back(KeyValuePair(key, value));
    }

    T_Value get(const T_Key& key) const
    {
        auto& bucket = get_bucket(key); 
        for (auto& pair : bucket)
        {
            if (pair.first == key)
            {
                return pair.second;
            }
        }

        throw std::out_of_range("Key not found");
    }

    void remove(int key);

private:

    Bucket& get_bucket(const T_Key& key)
    {
        size_t index = (hash_function(key) % num_buckets + num_buckets) % num_buckets;
        return buckets[index];
    }

    const Bucket& get_bucket(const T_Key& key) const
    {
        size_t index = (hash_function(key) % num_buckets + num_buckets) % num_buckets;
        return buckets[index];
    }

    HashFunction hash_function;
    const size_t num_buckets;
    std::vector<Bucket> buckets;

};

}