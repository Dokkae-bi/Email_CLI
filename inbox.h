#pragma once
#include <string>
#include "email_server.h"

class Inbox {
public:
    static const int CAPACITY = 50;

    Inbox();

    bool push(const Email& e);  // append to end; returns false if full
    bool pop();                 // remove last; returns false if empty
    bool remove(int index);     // remove at 0-based index, shifts left

    int              num_emails() const;
    const Email&     getEmail(int index) const;
    void             markRead(int index);

    void sortByDate();   // sorts emails by date (newest first)
    void sortByReadStatus(); // sorts emails by read status (Unread first)

private:
    Email inbox[CAPACITY];
    int   count;

    bool validIndex(int index) const;
};
