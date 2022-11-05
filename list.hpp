/**
 * Generic Connected List.
 *
 * @file list.hpp
 *
 * @brief Implementation of a generic connected list.
 *
 * @author Liav Barsheshet
 * Contact: liavbarsheshet@gmail.com
 *
 * This implementation is free: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This implementation is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

#ifndef _LIST_HPP
#define _LIST_HPP


#include <stdlib.h>
#include <iostream>

namespace CList {

    enum POSITION {
        START, END
    };

    class empty_list : public std::exception {
    };

    template<typename Value>
    class Node;

    template<typename Value>
    class List;
}

template<typename Value>
class CList::Node {
public:
    Node *next;
    Node *previous;
    Value value;

    Node() :
            next(NULL),
            previous(NULL) {}
};


/**
 * Class: Implementation of Linked-List.
 * @tparam Value - The value/data of each node.
 */
template<typename Value>
class CList::List {

    CList::Node<Value> *first;
    CList::Node<Value> *last;

public:

    class Iterator {
        CList::Node<Value> *first;
        CList::Node<Value> *previous_data;
        CList::Node<Value> *data;

        void Increment() {
            if (this->data == NULL) {
                if (!this->previous_data || !(this->previous_data->next)) {
                    throw std::out_of_range("Iterator is out of range.");
                } else {
                    this->data = this->previous_data;
                    this->previous_data = this->previous_data->next;
                }
            } else {
                this->previous_data = this->data;
                this->data = this->data->next;
            }
        }

        void Decrement() {
            if (this->data == NULL) {
                if (!this->previous_data || !(this->previous_data->previous)) {
                    throw std::out_of_range("Iterator is out of range.");
                } else {
                    this->data = this->previous_data;
                    this->previous_data = this->previous_data->previous;
                }
            } else {
                this->previous_data = this->data;
                this->data = this->data->previous;
            }
        }

    public:
        Iterator() :
                first(NULL),
                previous_data(NULL),
                data(NULL) {}

        Iterator(CList::Node<Value> *cur) :
                first(cur),
                previous_data(cur),
                data(cur) {}

        /**
         * Resets the iterator to its first value.
         * @note Worst-Time Complexity: O(1).
         */
        void Reset() {
            this->previous_data = this->first;
            this->data = this->first;
        }

        /**
         * Iterator Pointer Increment.
         * @note Worst-Time Complexity: O(1).
         * @return {Iterator&} Reference to the updated iterator.
         */
        Iterator &operator++() {
            this->Increment();
            return (*this);
        }

        /**
         * Iterator Pointer Increment.
         * @note Worst-Time Complexity: O(1).
         * @return {Iterator} Copy of the old iterator.
         */
        Iterator operator++(int) {
            Iterator tmp = *this;
            this->Increment();
            return (tmp);
        }

        /**
         * Iterator Pointer Decrement.
         * @note Worst-Time Complexity: O(1).
         * @return {Iterator&} Reference to the updated iterator.
         */
        Iterator &operator--() {
            this->Decrement();
            return (*this);
        }

        /**
         * Iterator Pointer Decrement.
         * @note Worst-Time Complexity: O(1).
         * @return {Iterator} Copy of the old iterator.
         */
        Iterator operator--(int) {
            Iterator tmp = *this;
            this->Decrement();
            return (tmp);
        }

        /**
         * Gets the value of the iterator.
         * @note Worst-Time Complexity: O(1).
         * @return {Value} Copy of iterator value.
         */
        Value operator*() {
            if (!this->data) throw std::invalid_argument("Iterators value is null.");
            return (data->value);
        }

        /**
         * Increase iterator by given number.
         * @param i - Number.
         * @note Worst-Time Complexity: O(1).
         * @return {Iterator&} Reference to the updated iterator.
         */
        Iterator& operator+(unsigned long long int i) {
            Iterator& tmp = *this;
            while (i > 0) {
                tmp.Increment();
                --i;
            }
            return (tmp);
        }

        /**
         * Decrease iterator by given number.
         * @param i - Number.
         * @note Worst-Time Complexity: O(1).
         * @return {Iterator&} Reference to the updated iterator.
         */
        Iterator& operator-(unsigned long long int i) {
            Iterator& tmp = *this;
            while (i > 0) {
                tmp.Decrement();
                --i;
            }
            return (tmp);
        }

        /**
         * Modify the current value of the iterator.
         * @note Worst-Time Complexity: O(1).
         */
        void operator*=(Value value) {
            if (!this->data) throw std::invalid_argument("Iterators value is null.");
            this->data->value = value;
        }

        /**
         * Compare values of two pointers.
         * @note Worst-Time Complexity: O(1).
         * @return {bool} True if equal o.w false.
         */
        bool operator==(const CList::List<Value>::Iterator &ref) {
            return this->data == ref.data;
        }

        /**
         * Compare values of two pointers.
         * @note Worst-Time Complexity: O(1).
         * @return {bool} True if not equal o.w false.
         */
        bool operator!=(const CList::List<Value>::Iterator &ref) {
            return this->data != ref.data;
        }
    };

    /**
     * Constructor: Creates an empty list.
     * @note Worst-Time Complexity: O(1).
     * @note Worst-Space Complexity: O(1).
     */
    List() :
            first(NULL),
            last(NULL) {}

    /**
     * Copy Constructor: Creates a list from another.
     * @note Worst-Time Complexity: O(n).
     * @note Worst-Space Complexity: O(n).
     */
    List(const List<Value> &list) :
            first(NULL),
            last(NULL) {
        CList::Node<Value> *head = list.first;
        while (head) {
            this->Append(head->value);
            head = head->next;
        }

    }

    /**
     * Destructor: Deallocates the entire list.
     * @note Without responsibility of deallocating (values).
     * @note Worst-Time Complexity: O(n).
     */
    ~List() {
        if (!first) return;
        CList::Node<Value> *tmp;
        while (first) {
            tmp = first;
            first = first->next;
            delete tmp;
        }
    }

    /**
     * Insert new element to the list from a given position.
     * @note Worst-Time Complexity: O(1).
     * @param value - New value to be inserted.
     * @param position - Pops from start or from the end of the list. (default: END)
     */
    void Insert(Value value, POSITION pos = END) {
        CList::Node<Value> *new_elem = new CList::Node<Value>();
        new_elem->value = value;
        if (!this->first) {
            this->first = new_elem;
            this->last = new_elem;
            return;
        }
        if (pos == START) {
            new_elem->next = this->first;
            this->first->previous = new_elem;
            this->first = new_elem;
            return;
        }
        new_elem->previous = this->last;
        this->last->next = new_elem;
        this->last = new_elem;
    }

    /**
     * Appends new element to the end of the list.
     * @note Worst-Time Complexity: O(1).
     * @param value - New value to be inserted.
     */
    void Append(Value value) {
        this->Insert(value);
    }

    /**
     * Appends new element to the start of the list.
     * @note Worst-Time Complexity: O(1).
     * @param value - New value to be inserted.
     */
    void Prepend(Value value) {
        this->Insert(value, START);
    }


    /**
     * Pop's an element from the list.
     * @note If stack is empty an error will occur.
     * @note Worst-Time Complexity: O(1).
     * @param position - Pops from start or from the end of the list. (default: END)
     * @return {Value} The popped value.
     */
    Value Pop(POSITION pos = END) {
        if (!this->first) throw CList::empty_list();
        CList::Node<Value> *popped_elem;
        if (pos == START) {
            popped_elem = this->first;
            Value value = popped_elem->value;
            this->first = this->first->next;
            if (!this->first) {
                this->last = NULL;
            } else {
                this->first->previous = NULL;
            }
            delete popped_elem;
            return value;
        }
        popped_elem = this->last;
        Value value = popped_elem->value;
        this->last = this->last->previous;
        if (!this->last) {
            this->first = NULL;
        } else {
            this->last->next = NULL;
        }
        delete popped_elem;
        return value;
    }

    /**
     * Returns the specific value without popping from given position.
     * @note Worst-Time Complexity: O(1).
     * @param position - Pops from start or from the end of the list. (default: END)
     * @return {Value} The top of the stack value.
     */
    Value Peek(POSITION pos = END) const {
        if (!this->first) throw CList::empty_list();
        Value value = (pos == START ? this->first->value : this->last->value);
        return value;
    }

    /**
     * Calculates the length of the list.
     * @tparam Number - The primitive/custom type of number.
     * @note Worst-Time Complexity: O(n).
     * @return {Number} The length of the list.
     */
    template<typename Number>
    Number Length() const {
        Number count = Number();
        CList::Node<Value> *head = this->first;
        while (head) {
            ++count;
            head = head->next;
        }
        return count;
    }

    /**
     * Creates an iterator that pointing to a given position.
     * @note Worst-Time Complexity: O(1).
     * @param position - Pops from start or from the end of the list. (default: START)
     * @return {Iterator} - Iterator that pointing to a given position
     */
    Iterator Begin(POSITION pos = START) const {
        return Iterator((pos == START ? this->first : this->last));
    }

    /**
     * Creates an iterator that pointing to an END.
     * @note Worst-Time Complexity: O(1).
     * @return {Iterator} - Iterator that pointing to a given position
     */
    Iterator End() const {
        return Iterator(NULL);
    }

};


#endif
