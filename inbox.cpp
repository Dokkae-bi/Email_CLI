#include "inbox.h"
#include <iostream>

using namespace std;

Inbox::Inbox() {}

bool Inbox::push(const Email& e) {
    if (static_cast<int>(emails.size()) >= CAPACITY) {
        cout << "[Inbox] push failed: inbox is full.\n";
        return false;
    }
    emails.push_back(e);
    return true;
}

bool Inbox::pop() {
    if (emails.empty()) {
        cout << "[Inbox] pop failed: inbox is empty.\n";
        return false;
    }
    emails.pop_back();
    return true;
}

bool Inbox::remove(int index) {
    if (!validIndex(index)) {
        cout << "[Inbox] remove failed: index " << index << " is out of range.\n";
        return false;
    }
    
    // Remove logic to be implemented
    auto it = getEmailIterator(index);
    emails.erase(it);
    return true;
}

int Inbox::num_emails() const {
    return emails.size();
}

const Email& Inbox::getEmail(int index) const {
    static Email empty("", "", "", "", false);
    if (!validIndex(index)) return empty;
    return *getEmailIterator(index);
}

void Inbox::markRead(int index) {
    if (validIndex(index))
        getEmailIterator(index)->markRead();
}

bool Inbox::validIndex(int index) const {
    return index >= 0 && index < emails.size();
}

void Inbox::sortByDate() {
   for (int i = 0; i < emails.size() - 1; i++) {
        int maxIdx = i;
        for (int j = i + 1; j < emails.size(); j++) {
            if (getEmailIterator(j)->getDate().toInt() > getEmailIterator(maxIdx)->getDate().toInt()) {
                maxIdx = j;
            }
        }
        if (maxIdx != i) {
            Email temp = *getEmailIterator(i);
            *getEmailIterator(i) = *getEmailIterator(maxIdx);
            *getEmailIterator(maxIdx) = temp;
        }
   }
}

void Inbox::sortByReadStatus() {
    int unreadIdx = 0;
    for (int i = 0; i < emails.size(); i++) {
        Email temp = *getEmailIterator(i);
        for (int j = i; j > unreadIdx && temp.isRead(); j--) {
            *getEmailIterator(j) = *getEmailIterator(j - 1);
        }
        *getEmailIterator(unreadIdx) = temp;
        unreadIdx++;
    }
}