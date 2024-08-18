# Hash table example

This application was created to fetch a text file from a given URL, break it down into individual words, and store the word count in a dedicated data structure

# How to build and run

From the project root folder, run:

```console
foo@bar:~$ cmake -S . -B build
foo@bar:~$ cmake --build build
foo@bar:~$ ./build/src/hash_map_example [--histogram]
foo@bar:~$ ./build/test/test_hash_map
```

# Rationale

The requirements can be broken down in the following independent functionalities:

- Fetching a text file from a given URL
- Parsing the text file, removing whitespace, punctuation, etc. and identifying words
- Counting how many times a word is present in the original text, using a dedicated data structure

## Fetching a text file

For fetching the text file, libcurl is used, with default settings. A write function is called while the text is being downloaded, parsing the downloaded data buffer byte by byte. This functionality is implemented primarily inside the ``process_url()`` function.

## Parsing the text

A dedicated class (``WordExtractor``) was implemented, with a single method (``parse_char()``). Given a new character from the text stream, it evaluates whether it is an alphabetic character or not, and, if it deems that a new word has been completed, calls a customizable _callback_ function to process it further (e.g. to count the number of appearances). To avoid misleading results, all words are converted to lower case.

## Obtaining the word count

The hash table was implemented in the templated ``HashMap`` class. The templated types represent both the key and value types. It also allows customizing its size (i.e. number of 'buckets') and hash function (uses ``std::hash()`` by default).

Internally, this class contains 'buckets', the number of which is fixed at construction. Upon inserting, removing or accessing a given key, the key's value is hashed, leading to the index of the bucket corresponding to it. Inside the bucket, there is a linked list corresponding to all key-value pairs for which the keys have the same hash value.

As requested, it implements the following methods with O(1) complexity:

- ``insert(key, value)``
- ``remove(key)``
- ``get(key)``
- ``get_last()``
- ``get_first()``

The class also implements a custom read-only ``Iterator`` class, with corresponding ``begin()`` and ``end()`` methods. This allows for accessing the key-value pairs by iterating over them.

As it turns out, the popular word 'the' features 8242 times in the original text. 

## Other ideas

The same infrastructure can be used to count the word size frequency, i.e the percentage of words with a given size in the original text. This is possible because the HashMap class is templated. In this case, the key is word size (an integer), while the value is the corresponding word count. This can be checked by using the optional ``--histogram`` command line option.

The largest word in the text contains 17 letters; about 24% of the individual words (including repetitions) are three-letter words.

# Known limitations

The ``get_first()`` and ``get_last()`` methods may return a non-existing key if ``remove()`` has been called after the latest insertion/modification. The alternative would be to create a data structure containing the entire insertion history of the object.

The implementation uses, for the sake of simplicity, ``std::string`` as a class to model words and text. More efficient alternatives are discussed in the book 'Efficient C++: Performance Programming Techniques'.

The implementation assumes an ASCII text that can be parsed byte by byte. Alternatives should consider other encodings (e.g. UTF-8).

# Dependencies

CMake, libcurl, googletest

# Requirements

Create a data-set of words from the book (https://www.gutenberg.org/files/98/98-0.txt). Implement a fixed sized hash table by using linear probing to resolve collisions. Assume that the keys are the words from the given data-set and the hash table’s values are integers. You need to implement the following functions with O(1)-complexity:

- insert(key, value): inserts a new key-value pair or replaces a key’s existing value,
- remove(key): removes the corresponding key-value pair,
- get(key): returns the value of the corresponding key,
- get_last(): returns the most recently inserted or changed key-value pair,
- get_first(): returns the least recently inserted or changed key-value pair