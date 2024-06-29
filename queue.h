#ifndef QUEUE_H
#define QUEUE_H

#include "book.h"

#include <queue>
#include <string>

class Queue {
public:
    void enqueue(const std::string &transaction);
    void dequeue();
    std::string front() const;
    bool isEmpty() const;
    void logTransaction(const std::string &transaction) const;
    void loadTransactionsFromFile(const std::string &filename);
    void saveTransactionsToFile(const std::string &filename) const;
    void displayTransactions() const;

private:
    std::queue<std::string> transactions;
};

#endif // QUEUE_H
