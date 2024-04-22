#include <iostream>
#include <stdexcept>

class LinkedList
{
private:
    class LinkedListNode
    {
    public:
        LinkedListNode *next{nullptr};
        int value;

    public:
        LinkedListNode(int value)
        {
            this->value = value;
        };
    };

public:
    LinkedListNode *head{nullptr};
    LinkedListNode *tail{nullptr};
    uint32_t size{0};

    LinkedList() = default;
    ~LinkedList()
    {
        while (this->head != nullptr)
        {
            LinkedListNode *next = this->head->next;
            delete this->head;
            this->head = next;
        }
    }

    LinkedList(const LinkedList &other) = delete;            // disallow copying
    LinkedList &operator=(const LinkedList &other) = delete; // disallow assignment

    void insert(int index, int value)
    {
        if (index < 0 || index > this->size)
        {
            throw std::out_of_range("Index out of range");
        }
        // O(1)
        else if (index == 0)
        {
            this->prepend(value);
            return;
        }
        // O(1)
        else if (index == this->size)
        {
            this->append(value);
            return;
        }

        LinkedListNode *new_node = new LinkedListNode(value);

        LinkedListNode *prev{nullptr};
        LinkedListNode *current = this->head;
        int i{0};

        while (i < index)
        {
            prev = current;
            current = current->next;
            i++;
        }

        prev->next = new_node;
        new_node->next = current;
        this->size++;
    }

    void remove(int value)
    {
        LinkedListNode *prev{nullptr};
        LinkedListNode *curr{this->head};

        while (curr->next != nullptr)
        {
            if (curr->value == value)
            {
                prev->next = curr->next;
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
        LinkedListNode *new_node = new LinkedListNode(value);
        if (this->head == nullptr)
        {
            this->head = new_node;
            this->tail = this->head;
            this->size++;
            return;
        }

        this->tail->next = new_node;
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
        LinkedListNode *current = this->head;

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

        LinkedListNode *deleted = this->head;

        int value = this->head->value;
        this->head = this->head->next;
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

        LinkedListNode *prev{nullptr};
        LinkedListNode *current = this->head;

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
        LinkedListNode *new_node = new LinkedListNode(value);
        new_node->next = this->head;
        this->head = new_node;
        this->size++;
    }
};

int main()
{
    // Test create linked list
    {
        LinkedList linked_list;
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
        LinkedList linked_list;
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
        LinkedList linked_list;
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

    // Test preprend
    {
        LinkedList linked_list;
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
        LinkedList linked_list;
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
        LinkedList linked_list;
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
        LinkedList linked_list;
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
        LinkedList linked_list;
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
        LinkedList linked_list;
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