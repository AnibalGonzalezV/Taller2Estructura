#pragma once
#include <iostream>
#include <stdexcept>
using namespace std;

template<typename K, typename V>
class HashNode {
public:
    K key;
    V value;
    HashNode* next;
    HashNode(K k, V v) : key(k), value(v), next(nullptr) {}
};

template<typename K, typename V>
class HashMap {
private:
    HashNode<K, V>** table;
    int capacity;
    int size;
    int hashFunction(K key);

public:
    HashMap(int cap = 100);
    ~HashMap();

    void insert(K key, V value);
    V get(K key);
    bool remove(K key);
    int getSize() const;
    bool isEmpty() const;
    int getCapacity() const { return capacity; }
    HashNode<K, V>** getTable() const { return table; }
};

// Implementación de los métodos de HashMap...

template<typename K, typename V>
HashMap<K, V>::HashMap(int cap) : capacity(cap), size(0) {
    table = new HashNode<K, V>*[capacity];
    for (int i = 0; i < capacity; ++i)
        table[i] = nullptr;
}

template<typename K, typename V>
HashMap<K, V>::~HashMap() {
    for (int i = 0; i < capacity; ++i) {
        HashNode<K, V>* current = table[i];
        while (current != nullptr) {
            HashNode<K, V>* prev = current;
            current = current->next;
            delete prev;
        }
    }
    delete[] table;
}

template<typename K, typename V>
void HashMap<K, V>::insert(K key, V value) {
    int index = hashFunction(key) % capacity;
    HashNode<K, V>* newNode = new HashNode<K, V>(key, value);
    if (table[index] == nullptr) {
        table[index] = newNode;
    } else {
        newNode->next = table[index];
        table[index] = newNode;
    }
    size++;
}

template<typename K, typename V>
V HashMap<K, V>::get(K key) {
    int index = hashFunction(key) % capacity;
    HashNode<K, V>* current = table[index];
    while (current != nullptr) {
        if (current->key == key)
            return current->value;
        current = current->next;
    }
    cout << "[!] Clave no existe." << endl;
}

template<typename K, typename V>
bool HashMap<K, V>::remove(K key) {
    int index = hashFunction(key) % capacity;
    HashNode<K, V>* current = table[index];
    HashNode<K, V>* prev = nullptr;
    while (current != nullptr) {
        if (current->key == key) {
            if (prev == nullptr) {
                table[index] = current->next;
            } else {
                prev->next = current->next;
            }
            delete current;
            size--;
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false;
}

template<typename K, typename V>
int HashMap<K, V>::getSize() const {
    return size;
}

template<typename K, typename V>
bool HashMap<K, V>::isEmpty() const {
    return size == 0;
}

template<typename K, typename V>
int HashMap<K, V>::hashFunction(K key) {
    return std::hash<K>{}(key);
}