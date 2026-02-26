#include "inbox.h"
#include <iostream>

using namespace std;

Inbox::Inbox() : count(0) {}

bool Inbox::push(const Email& e) {
    if (count >= CAPACITY) {
        cout << "[Inbox] push failed: inbox is full.\n";
        return false;
    }
    inbox[count] = e;
    count++;
    return true;
}

bool Inbox::pop() {
    if (count == 0) {
        cout << "[Inbox] pop failed: inbox is empty.\n";
        return false;
    }
    count--;
    return true;
}

bool Inbox::remove(int index) {
    if (!validIndex(index)) {
        cout << "[Inbox] remove failed: index " << index << " is out of range.\n";
        return false;
    }
    
    // Remove logic to be implemented

    return true;
}

int Inbox::num_emails() const {
    return count;
}

const Email& Inbox::getEmail(int index) const {
    static Email empty("", "", "", "", false);
    if (!validIndex(index)) return empty;
    return inbox[index];
}

void Inbox::markRead(int index) {
    if (validIndex(index))
        inbox[index].markRead();
}

bool Inbox::validIndex(int index) const {
    return index >= 0 && index < count;
}

void Inbox::sortByDate() {
   for (int i = 0; i < count - 1; i++) {
        int maxIdx = i;
        for (int j = i + 1; j < count; j++) {
            if (inbox[j].getDate().toInt() > inbox[maxIdx].getDate().toInt()) {
                maxIdx = j;
            }
        }
        if (maxIdx != i) {
            Email temp = inbox[i];
            inbox[i] = inbox[maxIdx];
            inbox[maxIdx] = temp;
        }
   }
}

void Inbox::sortByReadStatus() {
    int unreadIdx = 0;
    for (int i = 0; i < count; i++) {
        Email temp = inbox[i];
        for (int j = i; j > unreadIdx && temp.isRead(); j--) {
            inbox[j] = inbox[j - 1];
        }
        inbox[unreadIdx] = temp;
        unreadIdx++;
    }
}