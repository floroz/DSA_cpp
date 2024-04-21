#include <iostream>

class DoublyLinkedListNode
{
public:
    DoublyLinkedListNode *prev{nullptr};
    DoublyLinkedListNode *next{nullptr};
    int value;

public:
    DoublyLinkedListNode(int value)
    {
        this->value = value;
    };
};

class DoublyLinkedList
{
public:
    DoublyLinkedListNode *head{nullptr};
    DoublyLinkedListNode *tail{nullptr};
    uint32_t size{0};

public:
    DoublyLinkedList() {}

    void insert(int index, int value)
    {
        if (index == 0)
        {
            this->prepend(value);
            return;
        }
        else if (index == this->size)
        {
            this->append(value);
            return;
        }

        DoublyLinkedListNode *new_node = new DoublyLinkedListNode(value);

        DoublyLinkedListNode *prev{nullptr};
        DoublyLinkedListNode *current = this->head;
        int i{0};

        while (i < index)
        {
            prev = current;
            current = current->next;
            i++;
        }

        prev->next = new_node;
        new_node->prev = prev;
        new_node->next = current;
        this->size++;
    }

    void remove(int value)
    {
        DoublyLinkedListNode *prev{nullptr};
        DoublyLinkedListNode *curr{this->head};

        while (curr->next != nullptr)
        {
            if (curr->value == value)
            {
                prev->next = curr->next;
                curr->next->prev = prev;
                this->size--;

                // cleanup node from memory
                delete curr;
                curr = nullptr;
                return;
            }

            prev = curr;
            curr = curr->next;
        }

        throw std::runtime_error("Value not found");
    }

    void append(int value)
    {
        DoublyLinkedListNode *new_node = new DoublyLinkedListNode(value);
        if (this->head == nullptr)
        {
            this->head = new_node;
            this->tail = this->head;
            this->size++;
            return;
        }

        this->tail->next = new_node;
        new_node->prev = this->tail;
        this->tail = new_node;
        this->size++;
    }
    int at(int index)
    {
        if (index == -1)
        {
            return this->tail->value;
        }
        if (index >= this->size)
        {
            throw std::runtime_error("Accessing out of bounds");
        }

        int i{0};
        DoublyLinkedListNode *current = this->head;

        while (i < index)
        {
            current = current->next;
            i++;
        }

        return current->value;
    }

    int shift()
    {
        if (this->head == nullptr)
        {
            throw std::runtime_error("Cannot shift from an empty list");
        }

        DoublyLinkedListNode *deleted = this->head;

        int value = this->head->value;
        this->head = this->head->next;
        this->head->prev = nullptr;
        this->size--;
        // cleanup memory
        delete deleted;
        deleted = nullptr;

        return value;
    }

    int pop()
    {
        if (this->tail == nullptr)
        {
            throw std::runtime_error("Cannot pop from an empty list");
        }

        DoublyLinkedListNode *prev{nullptr};
        DoublyLinkedListNode *current = this->head;

        while (current->next != nullptr)
        {
            prev = current;
            current = current->next;
        }

        prev->next = nullptr;
        this->tail = prev;
        this->size--;

        int deleted_value = current->value;

        // cleanup memory
        prev = nullptr;
        delete current;
        current = nullptr;

        return deleted_value;
    }

    void prepend(int value)
    {
        DoublyLinkedListNode *new_node = new DoublyLinkedListNode(value);
        new_node->next = this->head;
        this->head->prev = new_node;
        this->head = new_node;
        this->size++;
    }
};

int main()
{
    // Test create linked list
    {
        DoublyLinkedList linked_list;
        if (linked_list.head != nullptr || linked_list.tail != nullptr || linked_list.size != 0)
        {
            std::cout << "Test create linked list failed\n";
            return EXIT_FAILURE;
        }
        else
        {
            std::cout << "Test create linked list passed\n";
        }
    }

    // Test add node
    {
        DoublyLinkedList linked_list;
        linked_list.append(1);
        if (linked_list.head->value != 1 || linked_list.tail->value != 1 || linked_list.size != 1)
        {
            std::cout << "Test add node failed\n";
            return EXIT_FAILURE;
        }
        else
        {
            std::cout << "Test add node passed\n";
        }
    }

    // Test next references
    {
        DoublyLinkedList linked_list;
        linked_list.append(1);
        linked_list.append(2);
        linked_list.append(3);
        if (linked_list.head->next->value != 2 || linked_list.head->next->next->value != 3 ||
            linked_list.head->next->next->next != nullptr || linked_list.tail->value != 3 || linked_list.size != 3)
        {
            std::cout << "Test next references failed\n";
        }
        else
        {
            std::cout << "Test next references passed\n";
        }
    }

    // Test prev references
    {
        DoublyLinkedList linked_list;
        linked_list.append(1);
        linked_list.append(2);
        linked_list.append(3);
        if (linked_list.tail->prev->value != 2 || linked_list.tail->prev->prev->value != 1 ||
            linked_list.tail->prev->prev->prev != nullptr || linked_list.head->value != 1 || linked_list.size != 3)
        {
            std::cout << "Test prev references failed\n";
        }
        else
        {
            std::cout << "Test prev references passed\n";
        }
    }

    // Test preprend
    {
        DoublyLinkedList linked_list;
        linked_list.append(1);
        linked_list.prepend(2);
        if (linked_list.head->value != 2 || linked_list.head->next->value != 1 || linked_list.tail->value != 1 || linked_list.size != 2)
        {
            std::cout << "Test preprend failed\n";
        }
        else
        {
            std::cout << "Test preprend passed\n";
        }
    }

    // Test delete last
    {
        DoublyLinkedList linked_list;
        linked_list.append(1);
        linked_list.append(2);
        linked_list.append(3);
        int value = linked_list.pop();
        if (value != 3 || linked_list.head->next->next != nullptr || linked_list.tail->value != 2 || linked_list.size != 2)
        {
            std::cout << "Test delete last failed\n";
        }
        else
        {
            std::cout << "Test delete last passed\n";
        }
    }

    // Test delete first
    {
        DoublyLinkedList linked_list;
        linked_list.append(1);
        linked_list.append(2);
        linked_list.append(3);
        int value = linked_list.shift();
        if (value != 1 || linked_list.head->value != 2 || linked_list.head->next->value != 3 || linked_list.tail->value != 3 || linked_list.size != 2)
        {
            std::cout << "Test delete first failed\n";
        }
        else
        {
            std::cout << "Test delete first passed\n";
        }
    }

    // Test access at index
    {
        DoublyLinkedList linked_list;
        linked_list.append(1);
        linked_list.append(2);
        linked_list.append(3);
        if (linked_list.at(0) != 1 || linked_list.at(1) != 2 || linked_list.at(2) != 3 || linked_list.size != 3 || linked_list.at(-1) != 3)
        {
            std::cout << "Test access at index failed\n";
        }
        else
        {
            std::cout << "Test access at index passed\n";
        }
    }

    // Test insert at index
    {
        DoublyLinkedList linked_list;
        linked_list.append(1);
        linked_list.append(2);
        linked_list.append(3);
        linked_list.insert(1, 4);
        if (linked_list.at(1) != 4 || linked_list.at(2) != 2 || linked_list.size != 4)
        {
            std::cout << "Test insert at index failed\n";
        }
        else
        {
            std::cout << "Test insert at index passed\n";
        }
    }

    // Test delete by value
    {
        DoublyLinkedList linked_list;
        linked_list.append(1);
        linked_list.append(2);
        linked_list.append(3);
        linked_list.remove(2);
        if (linked_list.at(1) != 3 || linked_list.size != 2)
        {
            std::cout << "Test delete by value failed\n";
        }
        else
        {
            std::cout << "Test delete by value passed\n";
        }
    }

    return 0;
}