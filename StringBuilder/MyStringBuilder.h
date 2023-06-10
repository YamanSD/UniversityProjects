/*
 * StringBuilder Project
 *
 *
 * MyStringBuilder.h
 *
 * Date:        14/04/2023
 *
 * Author:      Mahmoud Yaman Seraj Alddin
 *
 * Purpose:     Header file for the MyStringBuilder class,
 *              based on the Java StringBuilder class.
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
 *      void clear(int begin, int end)
 *          Makes the range in the MyStringBuilder empty.
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
 */

#ifndef MYSTRINGBUILDER_MYSTRINGBUILDER_H
#define MYSTRINGBUILDER_MYSTRINGBUILDER_H

#include <exception>
#include <iostream>
#include <string>

#include "Node.h"

/*
 * MyStringBuilder class mimics Java's StringBuilder class.
 */
class MyStringBuilder {
public:
    /*
     * Type alias for Node*.
     * Can be accessed outside the class using MyStringBuilder::NodePtr.
     */
    typedef Node* NodePtr;

    /*
     * Pre-Conditions:
     *      A string whose characters are copied is given.
     *
     * Post-Conditions:
     *      A MyStringBuilder instance is created.
     *      first is a Node* or nullptr.
     *      size is equal to the size of the string.
     *
     * Parameterized constructor of the MyStringBuilder class.
     */
    explicit MyStringBuilder(std::string);

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
    MyStringBuilder& insert(int, const MyStringBuilder&);

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
     * Inserts a copy of the given MyStringBuilder instance
     * into the end of `this` MyStringBuilder.
     */
    MyStringBuilder& append(const MyStringBuilder&);

    /*
     * Pre-Conditions:
     *      MyStringBuilder instance is initialized.
     *      int to append to the MyStringBuilder
     *
     * Post-Conditions:
     *      The given int is inserted at the end of `this`.
     *      A reference to `this` is returned.
     *
     * Inserts a copy of the given int into the end
     * of `this` MyStringBuilder.
     */
    MyStringBuilder& append(int);

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
    MyStringBuilder& replace(int /* begin */, int /* end */,
                             const MyStringBuilder&);

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
    MyStringBuilder& toUpperCase();

    /*
     * Pre-Conditions:
     *      MyStringBuilder instance is initialized.
     *
     * Post-Conditions:
     *      Number of characters in the builder is returned.
     *      No changes to `this`.
     *
     * Returns the number of characters in the MyStringBuilder instance.
     */
    [[nodiscard]] int length() const;

    /*
     * Pre-Conditions:
     *      MyStringBuilder instance is initialized.
     *      Given int position is valid.
     *
     * Post-Conditions:
     *      Characters in the builder at the given position is returned.
     *      No changes to `this`.
     *
     * Returns the character at the given index in MyStringBuilder instance.
     */
    [[nodiscard]] char charAt(int) const;

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
     * Returns a new MyStringBuilder instance from the characters between
     * begin (inclusive) & end (exclusive)
     */
    [[nodiscard]] MyStringBuilder substring(int /* begin */,
                                            int /* end */) const;

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
     * Returns a new MyStringBuilder instance from the characters starting
     * from begin (inclusive) to the end of the MyStringBuilder.
     */
    [[nodiscard]] MyStringBuilder substring(int /* begin */) const;

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
    [[nodiscard]] std::string toString() const;

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
    void clear(int /* begin */, int /* end */);

private:
    /*
     * Pre-Conditions:
     *      NodePtr to a char Node.
     *      int of the number of Nodes.
     *
     * Post-Conditions:
     *      A MyStringBuilder instance is created.
     *      first is the given NodePtr.
     *      size is the given size.
     *
     * Parameterized constructor of the MyStringBuilder class.
     * Takes a Node pointer & a size parameter.
     */
    explicit MyStringBuilder(NodePtr, int);

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
     * Returns a Node double pointer to the beginning of a Node chain
     * that has the copies of characters of `this` MyStringBuilder instance
     * from the given start (inclusive) to the given end (exclusive).
     */
    [[nodiscard]] NodePtr* copyChain(int start = 0, int end = 0) const;

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
    void checkIndex(int) const;

    /* Node pointer to the first Node in MyStringBuilder */
    NodePtr first;

    /* Number of Nodes in the string builder */
    int size;
};

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
std::ostream& operator<<(std::ostream&, const MyStringBuilder&);

#endif /* MYSTRINGBUILDER_MYSTRINGBUILDER_H */
