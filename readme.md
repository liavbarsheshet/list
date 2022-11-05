# C++ Generic Linked List

Implementation of Generic Linked List.

---

## Declaration

Supports >= c++11:

```c++
#include "list.hpp"

auto hash_table = CList::List<typename Value>();
```

## Template

```c++
/**
 * Class: Implementation of Linked-List.
 * @tparam Value - The value/data of each node.
 */
template<typename Value>
class CList::List {...}
```

## Enums

```c++
// Represents side Position of list.
typedef enum {
    START, END
} POSITION;
```

## List Node

```c++
/**
 * Class: Implementation of Node.
 * @tparam Value - The value/data of each node.
 */
template<typename Value>
class CList::Node {...}
```

## Methods

Methods of Linked-List.

```cpp
/**
 * Constructor: Creates an empty list.
 * @note Worst-Time Complexity: O(1).
 * @note Worst-Space Complexity: O(1).
 */
List();

/**
 * Copy Constructor: Creates a list from another.
 * @note Worst-Time Complexity: O(n).
 * @note Worst-Space Complexity: O(n).
 */
List(const List<Value> &list);

/**
 * Destructor: Deallocates the entire list.
 * @note Without responsibility of deallocating (values).
 * @note Worst-Time Complexity: O(n).
 */
~List();

/**
 * Insert new element to the list from a given position.
 * @note Worst-Time Complexity: O(1).
 * @param value - New value to be inserted.
 * @param position - Pops from start or from the end of the list. (default: END)
 */
void Insert(Value value, POSITION pos = END);

/**
 * Appends new element to the end of the list.
 * @note Worst-Time Complexity: O(1).
 * @param value - New value to be inserted.
 */
void Append(Value value);

/**
 * Appends new element to the start of the list.
 * @note Worst-Time Complexity: O(1).
 * @param value - New value to be inserted.
 */
void Prepend(Value value);

/**
 * Pop's an element from the list.
 * @note If stack is empty an error will occur.
 * @note Worst-Time Complexity: O(1).
 * @param position - Pops from start or from the end of the list. (default: END)
 * @return {Value} The popped value.
 */
Value Pop(POSITION pos = END);

/**
 * Returns the specific value without popping from given position.
 * @note Worst-Time Complexity: O(1).
 * @param position - Pops from start or from the end of the list. (default: END)
 * @return {Value} The top of the stack value.
 */
Value Peek(POSITION pos = END) const ;

/**
 * Calculates the length of the list.
 * @tparam Number - The primitive/custom type of number.
 * @note Worst-Time Complexity: O(n).
 * @return {Number} The length of the list.
 */
template<typename Number>
Number Length() const;

/**
 * Creates an iterator that pointing to a given position.
 * @note Worst-Time Complexity: O(1).
 * @param position - Pops from start or from the end of the list. (default: START)
 * @return {Iterator} - Iterator that pointing to a given position
 */
Iterator Begin(POSITION pos = START) const ;


/**
 * Creates an iterator that pointing to an END.
 * @note Worst-Time Complexity: O(1).
 * @return {Iterator} - Iterator that pointing to a given position
 */
Iterator End() const ;
```

## Author

[Liav Barsheshet, LBDevelopments](https://github.com/liavbarsheshet)

## License

[MIT](LICENSE)
