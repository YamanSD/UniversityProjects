/*
 * StringBuilder Project
 *
 *
 * Node.h
 *
 * Date:        13/04/2023
 *
 * Author:      Mahmoud Yaman Seraj Alddin
 *
 * Purpose:     Header file for the Node class,
 *              used in the MyStringBuilder class.
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

#ifndef MYSTRINGBUILDER_NODE_H
#define MYSTRINGBUILDER_NODE_H

/*
 * Node class used in MyStringBuilder class to manage single characters.
 */
class Node {
public:
    /*
     * Type alias for the type of data stored in the Nodes class.
     * For the use case in MyStringBuilder, char is the type of the data.
     * Can be accessed outside the class using Node::DataType.
     */
    typedef char DataType;

    /*
     * Pre-Conditions:
     *      No preconditions.
     *
     * Post-Conditions:
     *      A default Node instance is created.
     *      next is nullptr.
     *      data is default value of the type.
     *
     * No-arg constructor of the Node class.
     */
    Node();

    /*
     * Pre-Conditions:
     *      A const Reference to a variable of type `DataType` is given.
     *
     * Post-Conditions:
     *      A Node instance with the given data is created.
     *      next is nullptr.
     *      data is a copy of the given value.
     *
     * Parameterized constructor of the Node class,
     * that takes the data to be stored.
     */
    explicit Node(const DataType&);

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
     */
    Node& operator=(const Node&);

    /*
     * Pre-Conditions:
     *      `this` Node instance is not destroyed.
     *
     * Post-Conditions:
     *      `this` Node instance is destroyed.
     *      next is nullptr.
     *
     * Destructor for the Node class.
     */
    ~Node();

    /*
     * Pre-Conditions:
     *      `this` Node instance is initialized.
     *
     * Post-Conditions:
     *      A Node pointer to the next Node or nullptr is returned.
     *      No changes to this.
     *
     * Returns a copy of the pointer to the next Node instance.
     */
    [[nodiscard]] Node* getNext() const;

    /*
     * Pre-Conditions:
     *      `this` Node instance is initialized.
     *
     * Post-Conditions:
     *      Data of type `DataType` is returned.
     *      No changes to this.
     *
     * Returns a copy of the data stored in the Node instance.
     */
    [[nodiscard]] DataType getData() const;

    /*
     * Pre-Conditions:
     *      `this` Node instance is initialized.
     *      An int is given that represents the number of hops.
     *
     * Post-Conditions:
     *      A pointer to a Node instance (or nullptr) is returned,
     *      points to the instance n-Nodes away.
     *
     * Returns a pointer to a Node,
     * after performing the given number of hops.
     */
    [[nodiscard]] Node* skip(int);

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
     * Deletes a given number of Node instances following a Node instance.
     * Returns a pointer to the new next Node instance.
     */
    Node* unchain(int);

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
    void chain(Node*);

    /*
     * Pre-Conditions:
     *      `this` Node instance is initialized.
     *      A const reference to a variable of type `DataType` is given.
     *
     * Post-Conditions:
     *      data in the Node instance is a copy of the given data.
     *
     * Assigns the data field in the Node instance.
     */
    void setData(const DataType&);

private:
    /*
     * Pointer to the next Node.
     * Initialized to nullptr by default.
     */
    Node *next;

    /*
     * Data stored in the Node instance.
     * Initialized to the default value of the type.
     */
    DataType data;
};

#endif /* MYSTRINGBUILDER_NODE_H */
