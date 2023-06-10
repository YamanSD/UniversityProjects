/*
 * StringBuilder Project
 *
 *
 * Node.cpp
 *
 * Date:        13/04/2023
 *
 * Author:      Mahmoud Yaman Seraj Alddin
 *
 * Purpose:     Implementation of the Node class, described in Node.h
 *
 * List of public Functions:
 *      Node()
 *          No-arg constructor of the Node class.
 *
 *      Node(const DataType&)
 *          Parameterized constructor of the Node class.
 *
 *      Node& operator=(const Node&)
 *          Assignment operator for the Node class.
 *
 *      ~Node()
 *          Destructor for the Node class.
 *
 *      Node* getNext() const
 *          Returns the pointer to the next Node instance.
 *
 *      DataType getData() const
 *          Returns the data stored in the Node instance.
 *
 *      void chain(Node*)
 *          Assigns the next Node instance.
 *
 *      void setData(const DataType&)
 *          Assigns the data field in the Node instance.
 *
 *      Node* unchain(int)
 *          Deletes a given number of Node instances following a Node instance.
 *          Returns a pointer to the new next Node instance.
 *
 *      Node* skip(int)
 *          Returns a pointer to a Node,
 *          after performing a given number of hops.
 */

#include "Node.h"


/*
 * Pre-Conditions:
 *      No preconditions.
 *
 * Post-Conditions:
 *      A default Node instance is created.
 *      next is initialized to nullptr.
 *      data is initialized to default value of the type.
 *
 * No-arg constructor of the Node class.
 */
Node::Node(): data{}, next{nullptr} {}

/*
 * Pre-Conditions:
 *      A const Reference to a variable of type `DataType` is given.
 *
 * Post-Conditions:
 *      A Node instance with the given data is created.
 *      next is initialized to nullptr.
 *      data is initialized to the given value.
 *
 * Marked explicit to prevent implicit conversions from char* to string.
 * Parameterized constructor of the Node class,
 * that takes the data to be stored.
 */
Node::Node(const DataType& data): data{data}, next{nullptr} {}

/*
 * Pre-Conditions:
 *      `this` Node instance & the given Node instance are initialized.
 *      A const Reference to a Node instance is given from which to copy.
 *
 * Post-Conditions:
 *      data is a copy of the given Node's data.
 *      next is a copy of the given Node's next.
 *      Returns a reference to this.
 *
 * Assignment operator for the Node class that copies the data fields of
 * the given Node to this.
 * data & next data fields are copied using their assignment operators.
 * If the pointer to other is the same as this, no copying is performed,
 * prevents self assignment & needles copying.
 */
Node& Node::operator=(const Node& other) {
    /* Self-assignment test */
    if (this == &other) {
        return *this;
    }

    data = other.data;
    next = other.next;

    return *this;
}

/*
 * Pre-Conditions:
 *      `this` Node instance is not destroyed.
 *
 * Post-Conditions:
 *      `this` Node instance is destroyed.
 *      next is nullptr
 *
 * Destructor for the Node class.
 * Deletes all the following Node instances, till it reaches a nullptr.
 */
Node::~Node() {
    /* Deleting nullptr has no effect */
    delete next;

    /* Provides protection against illegal access */
    next = nullptr;
}

/*
 * Pre-Conditions:
 *      `this` Node instance is initialized.
 *
 * Post-Conditions:
 *      A Node pointer to the next Node or nullptr is returned.
 *      No changes to this.
 *
 * Marked [[nodiscard]] to allow the compiler to issue warnings in case of
 * wasteful calls. For example `node.getNext();`.
 * Returns a copy of the pointer to the next Node instance.
 */
Node* Node::getNext() const {
    return next;
}

/*
 * Pre-Conditions:
 *      `this` Node instance is initialized.
 *
 * Post-Conditions:
 *      Data of type `DataType` is returned.
 *      No changes to this.
 *
 * Marked [[nodiscard]] to allow the compiler to issue warnings in case of
 * wasteful calls. For example `node.getData();`.
 * Returns a copy of the data stored in the Node instance.
 */
Node::DataType Node::getData() const {
    return data;
}

/*
 * Pre-Conditions:
 *      `this` Node instance is initialized.
 *      An int is given that represents the number of hops.
 *
 * Post-Conditions:
 *      A pointer to a Node instance (or nullptr) is returned,
 *      points to the instance n-Nodes away.
 *
 * Marked [[nodiscard]] to allow the compiler to issue warnings in case of
 * wasteful calls. For example `node.skip(5);`.
 * If the number of hops exceeds the number of Nodes nullptr is returned.
 * If the number of hops is 0 or less, `this` is returned.
 * Returns a pointer to a Node,
 * after performing the given number of hops.
 */
Node* Node::skip(int n) {
    Node *result = this;

    /* Perform n-hops */
    while (result and 0 < n--) {
        result = result->getNext();
    }

    return result;
}

/*
 * Pre-Conditions:
 *      `this` Node instance is initialized.
 *      An int is given that represents the number of Nodes to delete,
 *      after this.
 *
 * Post-Conditions:
 *      All n-Nodes following `this` are deleted.
 *      next points to the node after the last deleted node.
 *
 * If the count is 0 or less, no changes occur, next is returned.
 * Deletes a given number of Node instances following a Node instance.
 * Returns a pointer to the new next Node instance.
 */
Node* Node::unchain(int count) {
    if (count <= 0) {
        return getNext();
    }

    /* Last node in the chain to be deleted */
    Node *chain_end = skip(count);

    /* First node in the chain to be deleted */
    Node *chain_start = getNext();

    chain(chain_end->getNext());

    /* Prevents the deletion of Nodes after the last Node */
    chain_end->chain(nullptr);
    delete chain_start;

    return getNext();
}

/*
 * Pre-Conditions:
 *      `this` Node instance is initialized.
 *      A pointer to a Node is given.
 *
 * Post-Conditions:
 *      next points to the Node represented by the given pointer.
 *
 * Assigns the given pointer to next.
 */
void Node::chain(Node *newNext) {
    next = newNext;
}

/*
 * Pre-Conditions:
 *      `this` Node instance is initialized.
 *      A const reference to a variable of type `DataType` is given.
 *
 * Post-Conditions:
 *      data in the Node instance is a copy of the given data.
 *
 * Uses the DataType assignment operator.
 * Assigns the data field in the Node instance.
 */
void Node::setData(const DataType& newData) {
    data = newData;
}
