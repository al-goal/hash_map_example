#include <functional>
#include <optional>
#include <list>

#include <iostream>

namespace hash_map_example
{

template <typename T_Key, typename T_Value> class HashMap
{
public:

    using KeyValuePair = std::pair<T_Key, T_Value>;
    using HashFunction = std::function<int(T_Key)>;
    using Bucket = std::list<KeyValuePair>;

    struct Iterator
    {
        Iterator(const HashMap& map, size_t bucket_index, typename Bucket::const_iterator bucket_iterator)
        :   map(map),
            bucket_index(bucket_index),
            bucket_iterator(bucket_iterator)
        {
        }

        Iterator& operator++()
        {
            ++bucket_iterator;
            // std::cout << "Bucket iterator: " << bucket_index << " " << std::endl;  
            if (bucket_iterator == map.buckets[bucket_index].end())
            {
                ++bucket_index;
                while (bucket_index < map.num_buckets && map.buckets[bucket_index].empty())
                {
                    ++bucket_index;
                }
                if (bucket_index < map.num_buckets)
                {
                    bucket_iterator = map.buckets[bucket_index].begin();
                }
            }
            return *this;
        }

        bool operator!=(const Iterator& other) const
        {
            if (bucket_index == map.num_buckets && other.bucket_index == map.num_buckets)
            {
                // Special case for end()
                return false;
            }
            return bucket_index != other.bucket_index || bucket_iterator != other.bucket_iterator;
        }

        const KeyValuePair& operator*() const
        {
            std::cout << "Bucket iterator: " << bucket_index << " " << std::endl;  
            return *bucket_iterator;
        }

        const HashMap& map;
        size_t bucket_index;
        typename Bucket::const_iterator bucket_iterator;
    };

    Iterator begin() const
    {
        size_t index = 0;
        while (index < num_buckets && buckets[index].empty())
        {
            ++index;
        }
        if (index < num_buckets)
        {
            return Iterator(*this, index, buckets[index].begin());
        }
        return end();
    }

    Iterator end() const
    {
        return Iterator(*this, num_buckets, Bucket().end());
    }

    HashMap(int num_buckets = 1024, HashFunction hash_function = std::hash<T_Key>())
    :   hash_function(hash_function),
        num_buckets(num_buckets),
        buckets(num_buckets)
    {
        if (num_buckets < 1)
        {
            throw std::invalid_argument("HashMap must have at least one bucket");
        }
    }
    ~HashMap()
    {
        std::cout << "Destructor called" << std::endl;
    }

    void insert(const T_Key& key, const T_Value& value)
    {
        auto& bucket = get_bucket(key);
        for (auto& pair : bucket)
        {
            if (pair.first == key)
            {
                pair.second = value;
                last_key = key;
                return;
            }
        }
        bucket.push_back(KeyValuePair(key, value));
        if (!first_key)
        {
            first_key = key;
            std::cout << "First key: " << *first_key << std::endl;
            std::cout << "Insert, has first" << first_key.has_value() << std::endl;
        }
        last_key = key;

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

    T_Value get(const T_Key& key, const T_Value& default_value) const
    {
        auto& bucket = get_bucket(key);
        for (auto& pair : bucket)
        {
            if (pair.first == key)
            {
                return pair.second;
            }
        }

        return default_value;
    }

    void remove(const T_Key& key)
    {
        auto& bucket = get_bucket(key);
        for (auto it = bucket.begin(); it != bucket.end(); ++it)
        {
            if (it->first == key)
            {
                bucket.erase(it);
                return;
            }
        }
    }

    KeyValuePair get_first() const
    {
        if (!first_key)
        {
            throw std::out_of_range("No elements inserted or modified");
        }
        return KeyValuePair(*first_key, get(*first_key));
    }

    KeyValuePair get_last() const
    {
        if (!last_key)
        {
            throw std::out_of_range("No elements inserted or modified");
        }
        return KeyValuePair(*last_key, get(*last_key));
    }


private:

    Bucket& get_bucket(const T_Key& key)
    {
        size_t index = (hash_function(key) % num_buckets + num_buckets) % num_buckets;
        std::cout << "Non-const get_bucket " << index << " " << num_buckets << std::endl;
        return buckets[index];
    }

    const Bucket& get_bucket(const T_Key& key) const
    {
        size_t index = (hash_function(key) % num_buckets + num_buckets) % num_buckets;
        std::cout << "Const get_bucket " << index << " " << num_buckets << std::endl;
        return buckets[index];
    }

    HashFunction hash_function;
    const size_t num_buckets;
    std::vector<Bucket> buckets;

    std::optional<T_Key> first_key = std::nullopt;
    std::optional<T_Key> last_key = std::nullopt;

};

}