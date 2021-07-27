# Trie or String Map Data Structure Library in C++

Using trie is beneficial when have a lot of very long strings having the common prefix 
(e.g. urls, file paths) and you want to use them as keys for set or map. 
Trie will provide you with performance, close to the one of hash table 
(still worse on average, however), but with some benefits, like partial search 
(currently by prefix substring)


Member functions:
- constructor | *Construct Trie*
- constructor with copy | *Construct Trie with copy*
- destructor | *Trie Destructor*
- operator= | *Assign content*

Capacity:
- size | *Return size*
- empty | *Test whether Trie is empty*

Element access:
- at | *Access element*

Modifiers:
- insert | *Insert elements*
- erase | *Erase elements*

Operations:
- Count | *Count elements with a specific key*



