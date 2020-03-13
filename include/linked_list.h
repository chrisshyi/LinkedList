#include "fmt/core.h"
#include <string>
#include <cstdlib>
template <typename T>
class LinkedList {
    private: 
        struct Node {
            T data;
            Node* next = nullptr;

            Node(T elem) : data{elem} {};
        };
        Node* head = nullptr;

        void swap(Node* x, Node* y) {
            T temp = x->data;
            x->data = y->data;
            y->data = temp;
        }

        friend LinkedList<int> sum(const LinkedList<int>&, const LinkedList<int>&); 
        friend LinkedList<int> sum_forward(const LinkedList<int>&, const LinkedList<int>&);

    public:
        LinkedList() = default;
        LinkedList(Node* head_node) : head{head_node} {};
        ~LinkedList() {
            Node* trav_ptr = head;
            while (trav_ptr != nullptr) {
                Node* next = trav_ptr->next;
                delete trav_ptr;
                trav_ptr = next;
            }
        }

        int get_length() const {
            Node* trav_ptr = head;
            int len = 0;
            while (trav_ptr != nullptr) {
                len++;
                trav_ptr = trav_ptr->next;
            }
            return len;
        }
        
        void insert_front(T elem) {
            Node* new_node = new Node(elem);
            new_node->next = head;
            head = new_node;
        }

        void insert_back(T elem) {
            if (head == nullptr) {
                insert_front(elem);
                return;
            } else {
                Node* trav_ptr = head;
                while (trav_ptr->next != nullptr) {
                    trav_ptr = trav_ptr->next;
                }
                Node* new_node = new Node(elem);
                trav_ptr->next = new_node;
            }
        }

        bool is_palindrome() {
            
            auto get_n_away = [] (const Node& node, int pos) {
                const Node* trav = &node;
                while (pos > 0) {
                    trav = trav->next;
                    pos -= 1;
                }
                return trav;
            };
            auto len = get_length();
            if (len < 2) {
                return true;
            }
            auto trav_ptr = head;
            for (int i = len - 1; i > 0; i -= 2) {
                if (trav_ptr->data != get_n_away(*trav_ptr, i)->data) {
                    return false;
                }
                trav_ptr = trav_ptr->next;
            }
            return true;
        }

        LinkedList reverse() {
            if (head == nullptr) {
                return LinkedList();
            }
            Node* trav_ptr = head->next;
            Node* head_of_reverse = new Node(head->data);
            while (trav_ptr != nullptr) {
                Node* new_node = new Node(trav_ptr->data);
                new_node->next = head_of_reverse;
                head_of_reverse = new_node;
                trav_ptr = trav_ptr->next;
            }
            return LinkedList{head_of_reverse};
        }

        void partition(T x) {
            if (head == nullptr || head->next == nullptr) {
                return;
            }
            Node* small_start = head;
            while ((small_start->data >= x) && (small_start->next != nullptr)) {
                small_start = small_start->next;
            }
            if (small_start->next == nullptr) {
                return;
            }

            if (small_start != head) {
                swap(small_start, head);
            }

            Node* trav_ptr = head->next;
            while ((trav_ptr->data < x) && (trav_ptr->next != nullptr)) {
                trav_ptr = trav_ptr->next;
            }

            Node* big_start = trav_ptr;
            if (big_start->next == nullptr) {
                return;
            }

            trav_ptr = big_start->next;
            while (trav_ptr != nullptr) {
                if (trav_ptr->data < x) {
                    swap(big_start, trav_ptr);
                    big_start = big_start->next;
                }
                trav_ptr = trav_ptr->next;
            }
        }

        std::string to_string() {
            // fmt::print("fmt test: {}\n", head->data);
            std::string output;

            Node* trav_ptr = head;

            if (head == nullptr) {
                return "Empty Linked List";
            }

            while (trav_ptr != nullptr) {
                output += std::to_string(trav_ptr->data) + "->";
                trav_ptr = trav_ptr->next;
            }
            return output;
        }
};

LinkedList<int> sum(const LinkedList<int>& list_1, const LinkedList<int>& list_2) {
    int carry = 0, sum = 0;
    using LLNode = LinkedList<int>::Node;
    LLNode* trav_1 = list_1.head;
    LLNode* trav_2 = list_2.head;

    LLNode* new_tail = nullptr;
    LLNode* new_head = nullptr;

    while ((trav_1 != nullptr) || (trav_2 != nullptr)) {
        if (trav_1 == nullptr) {
            sum = trav_2->data;
        } else if (trav_2 == nullptr) {
            sum = trav_1->data;
        } else {
            sum = trav_1->data + trav_2->data;
        }

        sum += carry;
        carry = sum / 10;
        sum = sum % 10;

        LLNode* new_node = new LLNode(sum);
        if (new_head != nullptr) {
            new_tail->next = new_node;
            new_tail = new_tail->next;
        } else {
            new_tail = new_node;
            new_head = new_node;
        }

        if (trav_1 != nullptr) {
            trav_1 = trav_1->next;
        }

        if (trav_2 != nullptr) {
            trav_2 = trav_2->next;
        }
    }
    if (carry != 0) {
        LLNode* new_node = new LLNode(carry);
        new_tail->next = new_node;
    }
    return LinkedList<int>(new_head);
}



LinkedList<int> sum_forward(const LinkedList<int>& ll1, const LinkedList<int>& ll2) {
    int carry = 0, sum = 0;
    int ll1_len = ll1.get_length();
    int ll2_len = ll2.get_length();

    if (ll1_len == 0) {
        return LinkedList<int>(ll2.head);
    } else if (ll2_len == 0) {
        return LinkedList<int>(ll1.head);
    }

    using LLNode = LinkedList<int>::Node;
    LLNode* longer_trav, *shorter_trav;
    if (ll1_len >= ll2_len) {
        longer_trav = ll1.head;
        shorter_trav = ll2.head;
    } else {
        longer_trav = ll2.head;
        shorter_trav = ll1.head;
    }
    auto len_diff = abs(ll1_len - ll2_len);
    LLNode* new_tail = nullptr, *new_head = nullptr;
    while (len_diff > 0) {
        if (new_tail == nullptr) {
            new_tail = new LLNode(longer_trav->data);
            new_head = new_tail;
        } else {
            new_tail->next = new LLNode(longer_trav->data);
            new_tail = new_tail->next;
        }
        len_diff--;
        longer_trav = longer_trav->next;
    }

    while (longer_trav != nullptr) {
        sum = longer_trav->data + shorter_trav->data;
        carry = sum / 10;
        sum = sum % 10;

        if (carry > 0) {
            if (new_tail == nullptr) {
                new_tail = new LLNode(carry);
                new_head = new_tail;
            } else {
                new_tail->data += 1;
            }
        }

        if (new_tail == nullptr) {
            new_tail = new LLNode(sum);
            new_head = new_tail;
        } else {
            new_tail->next = new LLNode(sum);
            new_tail = new_tail->next;
        }
        longer_trav = longer_trav->next;
        shorter_trav = shorter_trav->next;
    }
    return LinkedList<int>(new_head);
}