/*
 * StringBuilder Project
 *
 *
 * main.cpp
 *
 * Date:        15/04/2023
 *
 * Author:      Mahmoud Yaman Seraj Alddin
 *
 * Purpose:     File containing the main function & other utility
 *              functions used to take input & display output.
 *
 * List of Functions:
 *      void displaySeparator(ostream& out = cout)
 *          Displays a separator of width 70.
 *
 *      void displayMenu(ostream& out = cout)
 *          Displays the options menu.
 *
 *      void displayCurrentIdentifier(const string& current, ostream& out = cout)
 *          Displays the current selected StringBuilder identifier.
 *
 *     void displayInvalidMessage(const string& msg, ostream& out = cout)
 *          Displays an error message.
 *
 *     void displayDataMessage(const string& msg, ostream& out = cout)
 *          Displays an information message.
 *
 *     map<int, string> displayBuilders(const StringBuilders&, ostream& out = cout)
 *          Displays a menu of the StringBuilders, returns a map that has the
 *          number of the identifier as key & string identifier as value.
 *
 *     string get(const string&, ostream& out = cout, istream& in = cin)
 *          Displays the given prompt, takes string input from the user.
 *
 *     int getInt(const string&, ostream& out = cout, istream& in = cin,
 *                  int lower = 0, int upper = 0, int defaultValue = -1)
 *          Displays the given prompt, keeps on trying to take int
 *          input from the user until a given value is given.
 *
 *     int getUserChoice(const string&, ostream& out = cout, istream& in = cin)
 *          Displays options menu, takes an option from the user.
 *
 *     void createStringBuilder(StringBuilders&, ostream& out = cout,
 *                              istream& in = cin)
 *          Performs all necessary input & output to create a new
 *          empty StringBuilder instance with an identifier.
 *
 *     string getStringBuilderIdentifier(StringBuilders&, ostream& out = cout,
 *                                       istream& in = cin)
 *          Displays the available StringBuilders, takes input from the user
 *          to determine which StringBuilder to use.
 *
 *     void switchCurrentBuilder(string&, StringBuilders&, MyStringBuilder*&,
 *                               ostream& out = cout, istream& in = cin)
 *          Performs all necessary input & output to change the current
 *          StringBuilder.
 *
 *     void insertString(StringBuilders&,
 *                       MyStringBuilders&,
 *                       ostream& out = cout,
 *                       istream& in = cin)
 *          Performs all necessary input & output to insert a
 *          string to the current StringBuilder.
 *
 *     void appendString(StringBuilders&,
 *                       MyStringBuilder&,
 *                       ostream& out = cout,
 *                       istream& in = cin)
 *          Performs all necessary input & output to append a
 *          string to the current StringBuilder.
 *
 *    void appendInteger(MyStringBuilder&,
 *                       ostream& out = cout,
 *                       istream& in = cin)
 *          Performs all necessary input & output to append an
 *          int to the current StringBuilder.
 *
 *    void displayBuilderSize(MyStringBuilder&, ostream& out = cout)
 *          Displays the length of the current StringBuilder.
 *
 *    void displayBuilderChar(MyStringBuilder& current,
 *                            ostream& out = cout, istream& in = cin)
 *          Performs all necessary input & output to display a char
 *          at a certain position in the current selected MyStringBuilder.
 *
 *    void toUpperCase(MyStringBuilder&)
 *          Changes the current StringBuilder to upper case.
 *
 *    void createSubstring(const string&,
 *                         StringBuilders&,
 *                         MyStringBuilder&,
 *                         ostream& out = cout, istream& in = cin)
 *          Performs all necessary input & output to create a new substring.
 *
 *    void replaceBuilder(StringBuilders&,
 *                         MyStringBuilder&,
 *                         ostream& out = cout, istream& in = cin)
 *          Performs all the necessary input & output to replace a substring
 *          in the current selected StringBuilder.
 *
 *    void displayStringBuilder(const MyStringBuilder&, ostream& out = cout)
 *          Displays the current StringBuilder.
 */

#include <iostream>
#include <map>
#include <string>

#include "MyStringBuilder.h"


using namespace std;

/* Type alias, shortens typing */
typedef map<string, MyStringBuilder> StringBuilders;

/*
 * Pre-Conditions:
 *      ostream reference (optional), default is cout.
 *
 * Post-Conditions:
 *      Displays a separator of width 70 to the given ostream.
 *
 * Displays a separator of width 70.
 */
void displaySeparator(ostream& out = cout) {
    out << endl << string(70, '-') << endl;
}

/*
 * Pre-Conditions:
 *      ostream reference (optional), default is cout.
 *
 * Post-Conditions:
 *      Displays the options menu.
 *      Returns the number of options.
 *
 * Displays the options menu.
 */
int displayMenu(ostream& out = cout) {
    static const int kNumberOfOptions = 12;

    displaySeparator(out);

    string options[] = {
            "Create a new StringBuilder",
            "Switch selected StringBuilder",
            "Insert a string in the StringBuilder",
            "Append a string to the StringBuilder",
            "Append an integer to the StringBuilder",
            "Get the length of the StringBuilder",
            "Get a character in the StringBuilder",
            "Get a substring from the StringBuilder",
            "Replace a section from the StringBuilder",
            "Set the StringBuilder to upper case",
            "Display current StringBuilder",
            "Exit",
    };

    /* Iterate over options, display its int key & options */
    for (int i = 0; i < kNumberOfOptions; i++) {
        out << i + 1 << "-\t\t" << options[i] << endl;
    }

    displaySeparator(out);

    return kNumberOfOptions;
}

/*
 * Pre-Conditions:
 *      const reference to the identifier of the current StringBuilder
 *      ostream reference (optional), default is cout.
 *
 * Post-Conditions:
 *      Displays the current StringBuilder Identifier
 *
 * Displays the current selected StringBuilder identifier.
 */
void displayCurrentIdentifier(const string& current,
                              ostream& out = cout) {
    out << endl
        << "Current StringBuilder: "
        << "\033[32;1;1m"   /* Text color becomes green, bold */
        << current
        << "\033[0m"        /* Text color becomes normal */
        << endl;
}

/*
 * Pre-Conditions:
 *      const reference to a message to be displayed.
 *      ostream reference (optional), default is cout.
 *
 * Post-Conditions:
 *      Displays an error message.
 *
 * Displays an error message.
 */
void displayInvalidMessage(const string& msg, ostream& out = cout) {
    out << endl
    << "\033[31;1;1m"   /* Text color becomes red, underlined, bold */
    << msg
    << "\033[0m"        /* Text color becomes normal */
    << endl;
}

/*
 * Pre-Conditions:
 *      const reference to a message to be displayed.
 *      ostream reference (optional), default is cout.
 *
 * Post-Conditions:
 *      Displays an information message.
 *
 * Displays an information message.
 */
void displayDataMessage(const string& msg, ostream& out = cout) {
    out << endl
    << "\033[33;1;1m"   /* Text becomes yellow, bold */
    << msg
    << "\033[0m"        /* Text becomes normal */
    << endl;
}

/*
 * Pre-Conditions:
 *      const reference to StringBuilders.
 *      ostream reference (optional), default is cout.
 *
 * Post-Conditions:
 *      Displays StringBuilder identifiers with their int keys.
 *      Returns a map of ints & strings.
 *
 * Displays a menu of the StringBuilders, returns a map that has the
 * number of the identifier as key & string identifier as value.
 */
map<int, string> displayBuilders(const StringBuilders& values,
                                 ostream& out = cout) {
    cout << endl << "0-\t\tCancel" << endl;
    map<int, string> optionNames;

    int i = 1;

    /*
     * Display int keys with their respective identifiers,
     * inserts them to optionNames.
     */
    for (const auto& pair: values) {
        cout << i << "-\t\t"
             << "\033[32;1;1m"
             << pair.first
             << "\033[0m"
             << endl;

        optionNames[i++] = pair.first;
    }

    cout << endl;
    return optionNames;
}

/*
 * Pre-Conditions:
 *      const string reference to the prompt.
 *      ostream reference (optional), default is cout.
 *      istream reference (optional), default is cin.
 *
 * Post-Conditions:
 *      Returns user string input.
 *
 * Displays the given prompt, takes string input from the user.
 */
string get(const string& prompt, ostream& out = cout, istream& in = cin) {
    string result;

    out << prompt << ": ";
    getline(in, result);

    return result;
}

/*
 * Pre-Conditions:
 *      const string reference to the prompt.
 *      ostream reference (optional), default is cout.
 *      istream reference (optional), default is cin.
 *      int minimum input value. Default disables bound.
 *      int maximum input value. Default disables bound.
 *      int default input value. Default disables default.
 *
 * Post-Conditions:
 *      Returns user int input.
 *
 * Displays the given prompt, keeps on trying to take int
 * input from the user until a given value is given.
 */
int getInt(const string& prompt, ostream& out = cout, istream& in = cin,
           int lower = -1, int upper = -1, int default_val = -1) {
    string response;

    /* Take input until user gives a default value */
    while (true) {
        try {
            if (default_val == -1) {
                response = get(prompt, out, in);
            } else {
                response = get(prompt
                               + " (Default is " + to_string(default_val) + ")",
                        out, in);
            }

            /* No input */
            if (not response.length()) {
                return default_val;
            }

            /* Convert string response to int */
            const int result = stoi(response);

            if (lower != -1 and result < lower) {
                /* Lower than minimum */
                displayInvalidMessage(
                        "Invalid integer must be >= "
                        + to_string(lower)
                );
                continue;
            } else if (upper != -1 and upper < result) {
                /* Higher than maximum */
                displayInvalidMessage(
                        "Invalid integer must be between "
                        + to_string(lower) + " & " + to_string(upper)
                );
                continue;
            }

            return result;
        } catch (invalid_argument& ignored) {
            displayInvalidMessage("Invalid integer input!", out);
        }
    }
}

/*
 * Pre-Conditions:
 *      const string reference to the current selected identifier.
 *      ostream reference (optional), default is cout.
 *      istream reference (optional), default is cin.
 *
 * Post-Conditions:
 *      Returns user int input.
 *
 * Displays options menu, takes an option from the user.
 */
int getUserChoice(const string& current_key,
                  ostream& out = cout, istream& in = cin) {
    int numberOfOptions = displayMenu(out);

    displayCurrentIdentifier(current_key, out);

    int choice = getInt("Choose an option from the menu", out, in);

    return choice;
}

/*
 * Pre-Conditions:
 *      const reference to StringBuilders.
 *      ostream reference (optional), default is cout.
 *      istream reference (optional), default is cin.
 *
 * Post-Conditions:
 *      Inserts the identifier into StringBuilders, with an
 *      empty StringBuilder.
 *      Informs user with success.
 *
 * Performs all necessary input & output to create a new
 * empty StringBuilder instance with an identifier.
 */
void createStringBuilder(StringBuilders& values,
                         ostream& out = cout, istream& in = cin) {
    string name = get("Enter an identifier name", out, in);
    MyStringBuilder temp = MyStringBuilder("");
    values.insert_or_assign(name, temp);

    displayDataMessage("Builder created successfully.", out);
}

/*
 * Pre-Conditions:
 *      const reference to StringBuilders.
 *      ostream reference (optional), default is cout.
 *      istream reference (optional), default is cin.
 *
 * Post-Conditions:
 *      Returns the chosen StringBuilder if the choice is valid.
 *      Throws exception if user cancels.
 *
 * Displays the available StringBuilders, takes input from the user
 * to determine which StringBuilder to use.
 */
string getStringBuilderIdentifier(StringBuilders& values,
                                  ostream& out = cout,
                                  istream& in = cin) {
    auto optionNames = displayBuilders(values, out);

    int choice = getInt("Choose a StringBuilder from the menu",
                        out, in, 0, (int) optionNames.size(),
                        1);

    /* Cancel selection */
    if (not choice) {
        throw exception();
    }

    return optionNames[choice];
}

/*
 * Pre-Conditions:
 *      String reference to the current StringBuilder identifier.
 *      const reference to StringBuilders.
 *      Reference to MyStringBuilder pointer of the current StringBuilder.
 *      ostream reference (optional), default is cout.
 *      istream reference (optional), default is cin.
 *
 * Post-Conditions:
 *      Changes the current selected identifier.
 *      Changes the current selected StringBuilder.
 *
 * Performs all necessary input & output to change the current
 * StringBuilder.
 */
void switchCurrentBuilder(string& current_key,
                          StringBuilders& values,
                          MyStringBuilder*& current,
                          ostream& out = cout, istream& in = cin) {
    string chosen;

    try {
        chosen = getStringBuilderIdentifier(values, out, in);
    } catch (...) {
        /* Canceled */
        return;
    }

    if (chosen == current_key) {
        displayDataMessage("Already using this Builder.", out);
        return;
    }

    current_key = chosen;
    current = &values.at(chosen);
}

/*
 * Pre-Conditions:
 *      Reference to StringBuilders.
 *      Reference to the current StringBuilder.
 *      ostream reference (optional), default is cout.
 *      istream reference (optional), default is cin.
 *
 * Post-Conditions:
 *      Inserts the given string to the current StringBuilder at the
 *      specified position.
 *
 * Performs all necessary input & output to insert a
 * string to the current StringBuilder.
 */
void insertString(StringBuilders& values,
                  MyStringBuilder& current,
                  ostream& out = cout,
                  istream& in = cin) {
    int mode = getInt("0 to insert string, 1 to insert existing StringBuilder",
                      out, in, 0, 1, 0);

    MyStringBuilder *to_be_inserted;

    if (mode) {
        /* Take string */

        try {
            string chosen = getStringBuilderIdentifier(values, out, in);
            to_be_inserted = &values.at(chosen);
        } catch (...) {
            return insertString(values, current, out, in);
        }
    } else {
        /* Take a string builder identifier */
        to_be_inserted = new MyStringBuilder(get("Enter a string",
                                                 out, in));
    }

    int position = getInt("Enter insertion position", out, in,
                          0, current.length());

    current.insert(position, *to_be_inserted);
}

/*
 * Pre-Conditions:
 *      Reference to StringBuilders.
 *      String reference to the current StringBuilder.
 *      ostream reference (optional), default is cout.
 *      istream reference (optional), default is cin.
 *
 * Post-Conditions:
 *      Inserts the given string to the current StringBuilder at the
 *      end.
 *
 * Performs all necessary input & output to append a
 * string to the current StringBuilder.
 */
void appendString(StringBuilders& values,
                  MyStringBuilder& current,
                  ostream& out = cout,
                  istream& in = cin) {
    int mode = getInt("0 to append string, 1 to append existing StringBuilder",
                      out, in, 0, 1, 0);

    MyStringBuilder *to_be_inserted;

    if (mode) {
        /* Take string */
        try {
            string chosen = getStringBuilderIdentifier(values,
                                                       out, in);
            to_be_inserted = &values.at(chosen);
        } catch (...) {
            return appendString(values, current, out, in);
        }
    } else {
        /* Get identifier */
        to_be_inserted = new MyStringBuilder(get("Enter a string",
                                                 out, in));
    }

    current.append(*to_be_inserted);
}

/*
 * Pre-Conditions:
 *      Reference to the current StringBuilder.
 *      ostream reference (optional), default is cout.
 *      istream reference (optional), default is cin.
 *
 * Post-Conditions:
 *      Inserts the given int to the current StringBuilder at the end.
 *
 * Performs all necessary input & output to append an
 * int to the current StringBuilder.
 */
void appendInteger(MyStringBuilder& current,
                   ostream& out = cout,
                   istream& in = cin) {
    int to_be_inserted = getInt("Enter an integer", out, in);
    current.append(to_be_inserted);
}

/*
 * Pre-Conditions:
 *      Reference to the current StringBuilder.
 *      ostream reference (optional), default is cout.
 *
 * Post-Conditions:
 *      Displays the length of the current StringBuilder.
 *
 * Displays the length of the current StringBuilder.
 */
void displayBuilderSize(MyStringBuilder& current, ostream& out = cout) {
    displayDataMessage(
            "Current StringBuilder size is " + to_string(current.length()),
            out
    );
}

/*
 * Pre-Conditions:
 *      Reference to the current StringBuilder.
 *      ostream reference (optional), default is cout.
 *      istream reference (optional), default is cin.
 *
 * Post-Conditions:
 *      Displays the character at the given position.
 *
 * Performs all necessary input & output to display a char
 * at a certain position in the current selected MyStringBuilder.
 */
void displayBuilderChar(MyStringBuilder& current,
                        ostream& out = cout, istream& in = cin) {
    if (not current.length()) {
        displayInvalidMessage("Empty StringBuilder!");
        return;
    }

    int position = getInt("Enter a position", out, in,
                          0, current.length());

    displayDataMessage(
            "'" + string{current.charAt(position)}
            + "' at position "
            + to_string(position)
    );
}

/*
 * Pre-Conditions:
 *      Reference to the current StringBuilder.
 *
 * Post-Conditions:
 *      Changes the Current StringBuilder to upper case.
 *
 * Changes the current StringBuilder to upper case.
 */
void toUpperCase(MyStringBuilder& current) {
    current.toUpperCase();
}

/*
 * Pre-Conditions:
 *      const string reference to the current identifier.
 *      Reference to StringBuilders.
 *      Reference to the current StringBuilder.
 *      ostream reference (optional), default is cout.
 *      istream reference (optional), default is cin.
 *
 * Post-Conditions:
 *      Creates a new StringBuilder with name current identifier(being->end).
 *      Displays the substring.
 *
 * Performs all necessary input & output to create a new substring.
 */
void createSubstring(const string& current_key,
                     StringBuilders& values,
                     MyStringBuilder& current,
                     ostream& out = cout, istream& in = cin) {
    int begin = getInt("Enter the begin index", out, in, 0, current.length() - 1, 0);
    int end = getInt("Enter the end index", out, in, begin + 1, current.length(), current.length());

    /* identifier(being->end) */
    const string identifier = current_key +
            "(" + to_string(begin) + "->" + to_string(end) + ")";

    values.insert_or_assign(identifier, current.substring(begin, end));
    displayDataMessage("Created new StringBuilder " + identifier);
    displayDataMessage("Result: " + values.at(identifier).toString());
}

/*
 * Pre-Conditions:
 *      Reference to StringBuilders.
 *      Reference to the current StringBuilder.
 *      ostream reference (optional), default is cout.
 *      istream reference (optional), default is cin.
 *
 * Post-Conditions:
 *      Replaces the substring of the current StringBuilder
 *      with the current builder.
 *
 * Performs all the necessary input & output to replace a substring
 * in the current selected StringBuilder.
 */
void replaceBuilder(StringBuilders& values,
                    MyStringBuilder& current,
                    ostream& out = cout, istream& in = cin) {
    if (not current.length()) {
        displayInvalidMessage("Empty StringBuilder. Cannot replace!");
        return;
    }

    int mode = getInt("0 to replace with string, 1 to replace with existing StringBuilder",
                      out, in, 0, 1, 0);

    MyStringBuilder *to_replace;

    if (mode) {
        /* Get string */
        try {
            string chosen = getStringBuilderIdentifier(values, out, in);
            to_replace = &values.at(chosen);
        } catch (...) {
            return replaceBuilder(values, current, out, in);
        }
    } else {
        /* Use existing */
        to_replace = new MyStringBuilder(get("Enter a string", out, in));
    }

    int begin = getInt("Enter the begin index", out, in,
                        0, current.length() - 1, 0
    );

    int end = getInt("Enter the end index", out, in,
                     begin, current.length(), current.length()
    );

    current.replace(begin, end, *to_replace);
}

/*
 * Pre-Conditions:
 *      const reference to the current StringBuilder.
 *      ostream reference (optional), default is cout.
 *
 * Post-Conditions:
 *      Displays the StringBuilder.
 *
 * Displays the current StringBuilder.
 */
void displayStringBuilder(const MyStringBuilder& current,
                          ostream& out = cout) {
    displayDataMessage(current.toString(), out);
}

/*
 * Pre-Conditions:
 *      No preconditions.
 *
 * Post-Conditions:
 *      Program startup.
 */
int main() {
    string current_key = "default";
    MyStringBuilder default_builder = MyStringBuilder("");
    StringBuilders string_builders{
        {current_key, default_builder},
    };

    MyStringBuilder *currentBuilder = &string_builders.at(current_key);
    int userChoice;

    /* Process user input */
    do {
        userChoice = getUserChoice(current_key);

        switch (userChoice) {
            case 1:
                createStringBuilder(string_builders);
                break;
            case 2:
                switchCurrentBuilder(current_key, string_builders, currentBuilder);
                break;
            case 3:
                insertString(string_builders, *currentBuilder);
                break;
            case 4:
                appendString(string_builders, *currentBuilder);
                break;
            case 5:
                appendInteger(*currentBuilder);
                break;
            case 6:
                displayBuilderSize(*currentBuilder);
                break;
            case 7:
                displayBuilderChar(*currentBuilder);
                break;
            case 8:
                createSubstring(current_key, string_builders, *currentBuilder);
                break;
            case 9:
                replaceBuilder(string_builders, *currentBuilder);
                break;
            case 10:
                toUpperCase(*currentBuilder);
                break;
            case 11:
                displayStringBuilder(*currentBuilder);
                break;
            case 12:
                break;
            default:
                displayInvalidMessage("Invalid Option!");
                break;
        }
    } while (userChoice != 12);

    displaySeparator();
    return 0;
}
