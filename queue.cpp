#include "queue.h"

#include <fstream>
#include <iostream>

void Queue::enqueue(const std::string &transaction) {
    transactions.push(transaction);
    logTransaction(transaction);
}

void Queue::dequeue() {
    if (!transactions.empty()) {
        transactions.pop();
    }
}

std::string Queue::front() const {
    return transactions.empty() ? "" : transactions.front();
}

bool Queue::isEmpty() const {
    return transactions.empty();
}

void Queue::logTransaction(const std::string &transaction) const {
    std::ofstream file("database/transactions.txt", std::ios::app);
    if (file.is_open()) {
        file << transaction << "\n";
        file.close();
    } else {
        std::cerr << "Failed to open transaction log file.\n";
    }
}

void Queue::loadTransactionsFromFile(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for reading: " << filename << std::endl;
        return;
    }

    std::string transaction;
    while (std::getline(file, transaction)) {
        transactions.push(transaction);
    }
    file.close();
}

void Queue::saveTransactionsToFile(const std::string &filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for writing: " << filename << std::endl;
        return;
    }

    std::queue<std::string> tempQueue = transactions;
    while (!tempQueue.empty()) {
        file << tempQueue.front() << "\n";
        tempQueue.pop();
    }
    file.close();
}

void Queue::displayTransactions() const {
    std::queue<std::string> tempQueue = transactions;
    while (!tempQueue.empty()) {
        std::cout << tempQueue.front() << "\n";
        tempQueue.pop();
    }
}
