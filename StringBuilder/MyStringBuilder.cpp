/*
 * StringBuilder Project
 *
 *
 * MyStringBuilder.cpp
 *
 * Date:        14/04/2023
 *
 * Author:      Mahmoud Yaman Seraj Alddin
 *
 * Purpose:     Implementation of the MyStringBuilder class,
 *              described in MyStringBuilder.h
 *
 * List of public Functions:
 *      MyStringBuilder(std::string)
 *          Parameterized constructor of the MyStringBuilder class.
 *
 *      MyStringBuilder& insert(int, const MyStringBuilder&)
 *          Inserts a copy of the given MyStringBuilder into the given position.
 *
 *      MyStringBuilder& append(const MyStringBuilder&)
 *          Inserts a copy of the given MyStringBuilder instance
 *          into the end of `this` MyStringBuilder.
 *
 *      MyStringBuilder& append(int)
 *          Inserts a copy of the given int into the end
 *          of `this` MyStringBuilder.
 *
 *      MyStringBuilder& replace(int begin, int end, const MyStringBuilder&)
 *          Replaces the substring from begin (inclusive) to
 *          end (exclusive) by a copy of the given MyStringBuilder instance.
 *
 *      MyStringBuilder& toUpperCase()
 *          Changes all the characters in the MyStringBuilder instance to
 *          upper case.
 *
 *      int length() const
 *          Returns the number of characters in the MyStringBuilder instance.
 *
 *      char charAt(int) const
 *          Returns the character at the given index in MyStringBuilder instance.
 *
 *      MyStringBuilder substring(int begin, int end)
 *          Returns a new MyStringBuilder instance from the characters between
 *          begin (inclusive) & end (exclusive).
 *
 *      MyStringBuilder substring(int begin)
 *          Returns a new MyStringBuilder instance from the characters starting
 *          from begin (inclusive) to the end of the MyStringBuilder.
 *
 *      std::string toString() const
 *          Returns a string of the characters stored in the MyStringBuilder
 *          instance.
 *
 *      void clear()
 *          Makes the MyStringBuilder empty.
 *
 * List of private Functions:
 *      MyStringBuilder(NodePtr, int)
 *          Parameterized constructor of the MyStringBuilder class.
 *          Takes a Node pointer & a size parameter.
 *
 *      NodePtr* copyChain(int start = 0, int end = 0) const
 *          Returns a Node double pointer to the beginning of a Node chain
 *          that has the copies of characters of `this` MyStringBuilder instance
 *          from the given start (inclusive) to the given end (exclusive).
 *
 *     void checkIndex(int) const
 *          Checks if the given index is valid (between 0 and size inclusive).
 *          If invalid, an invalid_argument exception is raised.
 *
 * List of global Functions:
 *      std::ostream& operator<<(std::ostream&, const MyStringBuilder&)
 *          Displays the string representation of the given MyStringBuilder
 *          instance in the given ostream.
 *
 *      void throwIndexException(int index, int end, int begin = 0)
 *          Throws an invalid_argument exception.
 *          The message is formatted based on the given parameters.
 */

#include "MyStringBuilder.h"

using namespace std;

/*
 * Pre-Conditions:
 *      The given index is not within the range [begin, end].
 *
 * Post-Conditions:
 *      invalid_argument exception is thrown.
 *
 * Throws an invalid_argument exception.
 * The message is formatted based on the given parameters.
 */
void throwIndexException(int index, int end, int begin = 0) {
    /* Equivalent to "Invalid index %d. Must be between %d & %d.\n" */
    throw invalid_argument(
            "Invalid index " + to_string(index)
            + ". Must be between " + to_string(begin)
            + " & " + to_string(end) + ".\n"
    );
}

/*
 * Pre-Conditions:
 *      A string whose characters are copied is given.
 *
 * Post-Conditions:
 *      A MyStringBuilder instance is created.
 *      first is initialized a Node* or remains a nullptr.
 *      size is equal to the size of the string.
 *
 * Marked explicit to prevent implicit conversions from char* to string.
 * Parameterized constructor of the MyStringBuilder class.
 */
MyStringBuilder::MyStringBuilder(string s): first{nullptr} {
    size = (int) s.size();

    /* s is empty */
    if (not size) {
        return;
    }

    first = new Node{s[0]};
    NodePtr current = first;

    /*
     * Iterate over the characters of s from the second to the last,
     * adding them to Nodes chain.
     */
    for (int i = 1; i < size; i++) {
        /* Node pointer */
        auto newNext = new Node{s[i]};

        current->chain(newNext);
        current = current->getNext();
    }
}

/*
 * Pre-Conditions:
 *      NodePtr to a char Node.
 *      int of the number of Nodes.
 *
 * Post-Conditions:
 *      A MyStringBuilder instance is created.
 *      first is initialized to the given NodePtr.
 *      size is initialized to the given size.
 *
 * Marked explicit to prevent implicit conversions from void* to Node*.
 * Parameterized constructor of the MyStringBuilder class.
 * Takes a Node pointer & a size parameter.
 */
MyStringBuilder::MyStringBuilder(NodePtr ptr,
                                 int length): first{ptr}, size{length} {}

/*
 * Pre-Conditions:
 *      MyStringBuilder instance is initialized.
 *      Given start & end are valid indices.
 *      end is greater than or equal to start.
 *
 * Post-Conditions:
 *      A Node double pointer, pointing to the start
 *      of a memory chunk containing 2 Node pointers.
 *      The first of which is the start of the chain,
 *      while the second is the end.
 *      No changes to `this`.
 *
 * If `this` MyStringBuilder is empty, nullptr is returned.
 * Returns a Node double pointer to the beginning of a Node chain
 * that has the copies of characters of `this` MyStringBuilder instance
 * from the given start (inclusive) to the given end (exclusive).
 */
MyStringBuilder::NodePtr* MyStringBuilder::copyChain(int start,
                                                     int end) const {
    if (not first) {
        /* Empty StringBuilder */
        return nullptr;
    }

    /* Initialize end to its default */
    if (end <= 0) {
        end = length();
    }

    checkIndex(start);
    checkIndex(end);

    if (end < start) {
        throwIndexException(end, length(), start);
    }

    /* Create beginning of a new Node chain */
    auto begin = new Node{first->skip(start)->getData()};
    NodePtr current = begin;
    NodePtr pivot = first->skip(start)->getNext();

    const int chainSize = end - start;

    /* Iterate over all the characters from index begin + 1 to end */
    for (int i = 1; i < chainSize; i++) {
        current->chain(new Node{pivot->getData()});

        current = current->getNext();
        pivot = pivot->getNext();
    }

    /* Pointer to NodePtr array of size 2 */
    return new NodePtr[2]{begin, current};
}

/*
 * Pre-Conditions:
 *      MyStringBuilder instance is initialized.
 *      int position of the insertion, must be valid.
 *      const reference to a MyStringBuilder instance to insert.
 *
 * Post-Conditions:
 *      The characters of the given
 *      MyStringBuilder are inserted at the given position.
 *      A reference to `this` is returned.
 *
 * Inserts a copy of the given MyStringBuilder into the given position.
 */
MyStringBuilder& MyStringBuilder::insert(int offset,
                                         const MyStringBuilder& s) {
    checkIndex(offset);

    /* Pointer to NodePtr array of size 2 */
    const auto temp = s.copyChain();

    /* s is Empty */
    if (not temp) {
        return *this;
    }

    NodePtr chain_start = temp[0], chain_end = temp[1];
    NodePtr current = first->skip(offset - 1);

    if (not offset) {
        /* Handle changing first NodePtr */
        chain_end->chain(first);
        first = chain_start;
    } else {
        /* Connect the copy chain to the main chain */
        chain_end->chain(current->getNext());
        current->chain(chain_start);
    }

    size += s.length();
    return *this;
}

/*
 * Pre-Conditions:
 *      MyStringBuilder instance is initialized.
 *      const reference to a MyStringBuilder instance to insert
 *      at the end of `this` MyStringBuilder instance.
 *
 * Post-Conditions:
 *      The characters of the given MyStringBuilder instance
 *      are inserted at the end of `this`.
 *      A reference to `this` is returned.
 *
 * Equivalent to insert(length(), s).
 * Inserts a copy of the given MyStringBuilder instance
 * into the end of `this` MyStringBuilder.
 */
MyStringBuilder& MyStringBuilder::append(const MyStringBuilder& s) {
    return insert(length(), s);
}

/*
 * Pre-Conditions:
 *      MyStringBuilder instance is initialized.
 *      int to append to the MyStringBuilder
 *
 * Post-Conditions:
 *      The given int is inserted at the end of `this`.
 *      A reference to `this` is returned.
 *
 * Equivalent to append(to_string(i))
 * Inserts a copy of the given int into the end
 * of `this` MyStringBuilder.
 */
MyStringBuilder& MyStringBuilder::append(int i) {
    return append(MyStringBuilder(to_string(i)));
}

/*
 * Pre-Conditions:
 *      MyStringBuilder instance is initialized.
 *
 * Post-Conditions:
 *      Number of characters in the builder is returned.
 *      No changes to `this`.
 *
 * Marked [[nodiscard]] to allow the compiler to issue warnings in case of
 * wasteful calls. For example `builder.length();`.
 * Returns the number of characters in the MyStringBuilder instance.
 */
int MyStringBuilder::length() const {
    return size;
}

/*
 * Pre-Conditions:
 *      MyStringBuilder instance is initialized.
 *      Given int position is valid.
 *
 * Post-Conditions:
 *      Characters in the builder at the given position is returned.
 *      No changes to `this`.
 *
 * Marked [[nodiscard]] to allow the compiler to issue warnings in case of
 * wasteful calls. For example `builder.charAt(0);`.
 * Returns the character at the given index in MyStringBuilder instance.
 */
char MyStringBuilder::charAt(int position) const {
    checkIndex(position);

    return first->skip(position)->getData();
}

/*
 * Pre-Conditions:
 *      MyStringBuilder instance is initialized.
 *      Given begin & end are valid indices.
 *      end is greater than or equal to begin.
 *
 * Post-Conditions:
 *      A MyStringBuilder instance is returned,
 *      having the characters between begin (inclusive)
 *      & end (exclusive) of `this`.
 *      No changes to `this`.
 *
 * Marked [[nodiscard]] to allow the compiler to issue warnings in case of
 * wasteful calls. For example `builder.substring(0, length());`.
 * Returns a new MyStringBuilder instance from the characters between
 * begin (inclusive) & end (exclusive)
 */
MyStringBuilder MyStringBuilder::substring(int begin, int end) const {
    checkIndex(begin);
    checkIndex(end);

    if (end < begin) {
        throwIndexException(end, length(), begin);
    } else if (end == begin) {
        /* Range is empty */
        return MyStringBuilder("");
    }

    /* Pointer to NodePtr array of size 2 */
    const auto temp = copyChain(begin, end);

    /* `this` is empty */
    if (not temp) {
        return MyStringBuilder("");
    }

    /* Return a new MyStringBuilder with begin */
    return MyStringBuilder(temp[0], end - begin);
}

/*
 * Pre-Conditions:
 *      MyStringBuilder instance is initialized.
 *      Given begin is a valid index.
 *
 * Post-Conditions:
 *      A MyStringBuilder instance is returned,
 *      having the characters after begin (inclusive) of `this`.
 *      No changes to `this`.
 *
 * Equivalent to substring(begin, length()).
 * Marked [[nodiscard]] to allow the compiler to issue warnings in case of
 * wasteful calls. For example `builder.substring(0);`.
 * Returns a new MyStringBuilder instance from the characters starting
 * from begin (inclusive) to the end of the MyStringBuilder.
 */
MyStringBuilder MyStringBuilder::substring(int begin) const {
    return substring(begin, length());
}

/*
 * Pre-Conditions:
 *      begin & end valid indices range to clear.
 *      MyStringBuilder instance is initialized.
 *
 * Post-Conditions:
 *      The MyStringBuilder is empty from begin to end.
 *      first is nullptr.
 *      size is 0.
 *
 * Makes the range in the MyStringBuilder empty.
 */
void MyStringBuilder::clear(int begin, int end) {
    checkIndex(begin);
    checkIndex(end);

    if (begin > end) {
        throwIndexException(end, length(), begin);
    } else if (begin == end) {
        return;
    }

    NodePtr begin_ptr = first->skip(begin - 1);
    NodePtr end_ptr = begin_ptr->unchain(end - begin - !begin);

    if (not begin) {
        /* Handle changing first NodePtr */
        first = end_ptr;
    } else {
        /* Connect the copy chain to the main chain */
        begin_ptr->chain(end_ptr);
    }

    size -= end - begin;
}

/*
 * Pre-Conditions:
 *      MyStringBuilder instance is initialized.
 *      begin & end are valid indices.
 *      end is greater than or equal to begin.
 *
 * Post-Conditions:
 *      The characters between begin (inclusive) & end (exclusive)
 *      are replaced with the given MyStringBuilder characters.
 *      A reference to `this` is returned.
 *
 * Replaces the substring from begin (inclusive) to
 * end (exclusive) by a copy of the given MyStringBuilder instance.
 */
MyStringBuilder& MyStringBuilder::replace(int begin, int end,
                                          const MyStringBuilder& s) {
    checkIndex(begin);
    checkIndex(end);

    if (end < begin) {
        throwIndexException(end, length(), begin);
    } else if (end == begin) {
        return *this;
    }

    /* Pointer to NodePtr array of size 2 */
    const auto temp = s.copyChain();

    /* s is Empty */
    if (not temp) {
        clear(begin, end);
        return *this;
    }

    NodePtr chain_start = temp[0], chain_end = temp[1];

    NodePtr begin_ptr = first->skip(begin - 1);
    NodePtr end_ptr = begin_ptr->unchain(end - begin - !begin);

    if (not begin) {
        /* Handle changing first NodePtr */
        first = chain_start;
    } else {
        /* Connect the copy chain to the main chain */
        begin_ptr->chain(chain_start);
    }

    chain_end->chain(end_ptr);
    size += s.length() - end + begin;

    return *this;
}

/*
 * Pre-Conditions:
 *      MyStringBuilder instance is initialized.
 *
 * Post-Conditions:
 *      The characters in `this` MyStringBuilder are all capitalized.
 *      A reference to `this` is returned.
 *
 * Changes all the characters in the MyStringBuilder instance to
 * upper case.
 */
MyStringBuilder& MyStringBuilder::toUpperCase() {
    NodePtr current = first;

    /* Iterate over all characters & change them to upper case */
    while (current) {
        current->setData((char) toupper(current->getData()));
        current = current->getNext();
    }

    return *this;
}


/*
 * Pre-Conditions:
 *      MyStringBuilder instance is initialized.
 *
 * Post-Conditions:
 *      A string of the characters in `this` MyStringBuilder is returned.
 *      No changes to `this`.
 *
 * Returns a string of the characters stored in the MyStringBuilder
 * instance.
 */
string MyStringBuilder::toString() const {
    string result{};

    NodePtr current = first;

    /* Iterate over all the character & add them to the string */
    while (current) {
        result.push_back(current->getData());
        current = current->getNext();
    }

    return result;
}

/*
 * Pre-Conditions:
 *      Reference to an output stream.
 *      const reference to a MyStringBuilder instance.
 *
 * Post-Conditions:
 *      String representation of MyStringBuilder is displayed.
 *      ostream& is returned.
 *
 * Displays the string representation of the given MyStringBuilder
 * instance in the given ostream.
 */
ostream& operator<<(ostream& out, const MyStringBuilder& str) {
    return out << str.toString();
}

/*
 * Pre-Conditions:
 *      MyStringBuilder instance is initialized.
 *      An int of the index to check.
 *
 * Post-Conditions:
 *      A invalid_argument exception is thrown if the
 *      index is invalid.
 *      No changes to `this`.
 *
 * Checks if the given index is valid (between 0 and size inclusive).
 * If invalid, an invalid_argument exception is raised.
 */
void MyStringBuilder::checkIndex(int index) const {
    if (index < 0 or length() < index) {
        throwIndexException(index, length());
    }
}
