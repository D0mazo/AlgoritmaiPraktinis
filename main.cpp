#include <iostream>
#include <string>

// Vienkrypčio sąrašo mazgo struktūra
struct Node {
    char data;
    Node* next;
    Node(char val) : data(val), next(nullptr) {}
};

// Dvikrypčio sąrašo mazgo struktūra
struct DoubleNode {
    char data;
    DoubleNode* prev;
    DoubleNode* next;
    DoubleNode(char val) : data(val), prev(nullptr), next(nullptr) {}
};

// Dvejetainio medžio mazgo struktūra
struct TreeNode {
    char data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(char val) : data(val), left(nullptr), right(nullptr) {}
};

// Funkcija vienkrypčio sąrašo kūrimui iš įvestos eilutės
Node* createListFromInput(const std::string& input) {
    Node* head = nullptr;
    Node* tail = nullptr;

    for (char c : input) {
        Node* newNode = new Node(c);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    return head;
}

// 1. Simbolių sąrašo apdorojimo funkcija
Node* createNewList(Node* head, int n) {
    Node* current = head;
    int m = 0;

    // Randame tarpo poziciją
    while (current != nullptr && current->data != ' ') {
        current = current->next;
        m++;
    }

    if (current == nullptr) return nullptr; // Tarpas nerastas

    // Sukuriame naują sąrašą
    Node* newHead = nullptr;
    Node* newTail = nullptr;

    // Pirmiausia pridedame simbolius nuo m+1 iki n
    current = head;
    for (int i = 0; i < m + 1 && current != nullptr; i++) {
        current = current->next;
    }

    while (current != nullptr) {
        Node* newNode = new Node(current->data);
        if (newHead == nullptr) {
            newHead = newTail = newNode;
        } else {
            newTail->next = newNode;
            newTail = newNode;
        }
        current = current->next;
    }

    // Tada pridedame simbolius nuo tarpo iki pradžios
    current = head;
    for (int i = 0; i <= m && current != nullptr; i++) {
        Node* newNode = new Node(current->data);
        if (newHead == nullptr) {
            newHead = newTail = newNode;
        } else {
            newTail->next = newNode;
            newTail = newNode;
        }
        current = current->next;
    }

    return newHead;
}

// Dvejetainio medžio funkcijos
TreeNode* insertTree(TreeNode* root, char val) {
    if (root == nullptr) {
        return new TreeNode(val);
    }

    if (val < root->data) {
        root->left = insertTree(root->left, val);
    } else {
        root->right = insertTree(root->right, val);
    }

    return root;
}

TreeNode* findMin(TreeNode* root) {
    while (root && root->left) {
        root = root->left;
    }
    return root;
}

TreeNode* deleteTree(TreeNode* root, char val) {
    if (root == nullptr) return nullptr;

    if (val < root->data) {
        root->left = deleteTree(root->left, val);
    } else if (val > root->data) {
        root->right = deleteTree(root->right, val);
    } else {
        if (root->left == nullptr) {
            TreeNode* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            TreeNode* temp = root->left;
            delete root;
            return temp;
        }

        TreeNode* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteTree(root->right, temp->data);
    }
    return root;
}

TreeNode* searchTree(TreeNode* root, char val) {
    if (root == nullptr || root->data == val) {
        return root;
    }

    if (val < root->data) {
        return searchTree(root->left, val);
    }
    return searchTree(root->right, val);
}

void printTree(TreeNode* root) {
    if (root == nullptr) return;
    printTree(root->left);
    std::cout << root->data << " ";
    printTree(root->right);
}

// Medžio elementų perkėlimas į vienkryptį sąrašą
void treeToList(TreeNode* root, Node*& head) {
    if (root == nullptr) return;

    treeToList(root->left, head);

    Node* newNode = new Node(root->data);
    if (head == nullptr) {
        head = newNode;
    } else {
        Node* current = head;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
    }

    treeToList(root->right, head);
}

// Dvikrypčio sąrašo funkcijos
DoubleNode* createDoubleList(const std::string& text) {
    DoubleNode* head = nullptr;
    DoubleNode* tail = nullptr;

    for (char c : text) {
        DoubleNode* newNode = new DoubleNode(c);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    return head;
}

DoubleNode* removeWordsStartingWithA(DoubleNode* head) {
    DoubleNode* current = head;
    bool isWordStart = true;

    while (current != nullptr) {
        if (isWordStart && (current->data == 'A' || current->data == 'a')) {
            // Randame žodžio pabaigą
            DoubleNode* wordStart = current;
            while (current != nullptr && current->data != ' ' && current->data != ',' && current->data != '.') {
                current = current->next;
            }

            // Šaliname žodį
            DoubleNode* wordEnd = current;
            if (wordStart->prev == nullptr) {
                head = wordEnd;
                if (wordEnd) wordEnd->prev = nullptr;
            } else {
                wordStart->prev->next = wordEnd;
                if (wordEnd) wordEnd->prev = wordStart->prev;
            }

            // Išvalome pašalintus mazgus
            while (wordStart != wordEnd) {
                DoubleNode* temp = wordStart;
                wordStart = wordStart->next;
                delete temp;
            }
        } else {
            isWordStart = (current->data == ' ' || current->data == ',' || current->data == '.');
            current = current->next;
        }
    }

    return head;
}

void printDoubleList(DoubleNode* head) {
    DoubleNode* current = head;
    while (current != nullptr) {
        std::cout << current->data;
        current = current->next;
    }
    std::cout << std::endl;
}

void printList(Node* head) {
    Node* current = head;
    while (current != nullptr) {
        std::cout << current->data;
        current = current->next;
    }
    std::cout << std::endl;
}

int main() {
    // 1. Simbolių sąrašo įvestis
    std::string input;
    std::cout << "Iveskite simboliu seka su tarpu (pvz., Hel Wo): ";
    std::getline(std::cin, input);

    Node* head = createListFromInput(input);
    std::cout << "Originalus sarasas: ";
    printList(head);

    Node* newList = createNewList(head, input.length());
    std::cout << "Naujas sarasas: ";
    printList(newList);

    // 2. Dvejetainio medžio įvestis
    TreeNode* root = nullptr;
    std::string treeInput;
    std::cout << "Iveskite simbolius medzio mazgams (pvz., HELWO, arba tuscia iseiti): ";
    std::getline(std::cin, treeInput);

    for (char c : treeInput) {
        if (c != ' ') {
            root = insertTree(root, c);
        }
    }

    std::cout << "Medzio elementai: ";
    printTree(root);
    std::cout << std::endl;

    // Perkeliame į vienkryptį sąrašą
    Node* singleList = nullptr;
    treeToList(root, singleList);
    std::cout << "Vienkryptis sarasas is medzio: ";
    printList(singleList);

    // 3. Dvikrypčio sąrašo įvestis
    std::string text;
    std::cout << "Iveskite teksta dvikrypciam sarasui (pvz., Apple and Banana): ";
    std::getline(std::cin, text);

    DoubleNode* doubleList = createDoubleList(text);
    std::cout << "Pradinis dvikryptis sarasas: ";
    printDoubleList(doubleList);

    doubleList = removeWordsStartingWithA(doubleList);
    std::cout << "Dvikryptis sarasas be zodziu su A: ";
    printDoubleList(doubleList);

    return 0;
}