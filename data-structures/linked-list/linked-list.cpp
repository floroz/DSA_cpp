#include <iostream>

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

class LinkedList
{
public:
    LinkedListNode *head{nullptr};
    LinkedListNode *tail{nullptr};
    uint32_t size{0};

public:
    LinkedList() {}

    // void insert(int index, int value) {}

    // LinkedListNode remove(int value) {}

    // LinkedListNode search(int value) {}

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
    // LinkedListNode at(int index) {}

    // LinkedListNode shift() {}

    LinkedListNode pop()
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
        return *current;
    }

    // void prepend(int value) {}
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

    // Test delete last
    {
        LinkedList linked_list;
        linked_list.append(1);
        linked_list.append(2);
        linked_list.append(3);
        LinkedListNode popped_node = linked_list.pop();
        if (popped_node.value != 3 || linked_list.head->next->next != nullptr || linked_list.tail->value != 2 || linked_list.size != 2)
        {
            std::cout << "Test delete last failed\n";
        }
        else
        {
            std::cout << "Test delete last passed\n";
        }
    }

    // Test delete first
    // {
    //     LinkedList linked_list;
    //     linked_list.append(1);
    //     linked_list.append(2);
    //     linked_list.append(3);
    //     LinkedListNode removed_node = linked_list.shift();
    //     if (removed_node.value != 1 || linked_list.head->value != 2 || linked_list.head->next->value != 3 || linked_list.tail->value != 3 || linked_list.size != 2)
    //     {
    //         std::cout << "Test delete first failed\n";
    //     }
    // }

    // Test access at index
    // {
    //     LinkedList linked_list;
    //     linked_list.append(1);
    //     linked_list.append(2);
    //     linked_list.append(3);
    //     if (linked_list.at(0).value != 1 || linked_list.at(1).value != 2 || linked_list.at(2).value != 3 || linked_list.at(3) != nullptr || linked_list.size != 3)
    //     {
    //         std::cout << "Test access at index failed\n";
    //     }
    // }

    // Test insert at index
    // {
    //     LinkedList linked_list;
    //     linked_list.append(1);
    //     linked_list.append(2);
    //     linked_list.append(3);
    //     linked_list.insert(1, 4);
    //     if (linked_list.head->value != 1 || linked_list.head->next->value != 4 || linked_list.head->next->next->value != 3 ||
    //         linked_list.at(0).value != 1 || linked_list.at(1).value != 4 || linked_list.at(2).value != 3 || linked_list.at(3) != nullptr || linked_list.size != 4)
    //     {
    //         std::cout << "Test insert at index failed\n";
    //     }
    // }

    return 0;
}