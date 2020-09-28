# cpp-containers
Several implementations are involved in this project:

1)  a class template called sv_set is developed that represents an ordered set of unique elements. This
template has two parameters:
    (a) Key. The type of each of the elements in the set (i.e., the key type).
    (b) Compare. The type of the callable entity (e.g., function or functor) used to test if one key is less
        than another. Since the elements of the container are ordered, a comparison predicate must be provided
        by the container user to define the sorting criterion to be employed by the container. A callable entity f
        of type Compare has he function-call operator applied with exactly two function arguments x and y of type
        Key and yields a return type of bool. The value returned by f(x,y) is true if x is less than y and false
        otherwise (i.e., f is a less-than predicate). Only a less-than predicate is provided for the user of sv_set,
        since all other relational operators (e.g., equal, not-equal, greater-than, greater-than-or-equal, and
        less-than-or-equal) can be synthesized from this single predicate. (For the sake of simplicity, the interface
        for sv_set assumes that Compare is a default-constructible type. This assumption eliminates the need to provide
        a comparison object to the sv_set constructor).
The sv_set class template is somewhat similar to std::set, except that the underlying data structure used to store
container elements differs. In the case of std::set, container elements are stored in a balanced (nodebased) tree. In
contrast, sv_set uses a dynamically-resizable array as the underlying data structure for storing the elements of the set.
In order to facilitate efficient searching for elements, the elements of the array are stored in sorted order, namely,
ascending order by key.

2)  A class template called list is developed that represents an intrusive doubly-linked list with a sentinel node. The
list class template relies on a (nontemplate) helper class called list_hook, which stores per-node list management
information. The list_hook class (which is a non-template class) is used to store per-node information needed for list
management (i.e., pointers to the successor and predecessor nodes). For a type T to be compatible with list, T must include
a data member of type list_hook.
