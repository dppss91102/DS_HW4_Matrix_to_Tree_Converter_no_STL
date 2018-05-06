#include <iostream>
using namespace std;

#define MAX_SIZE 10000
template<class T>
class queue{
private:
    T *a;
    int first, last, count;
public:
    queue(){
        a = new T[MAX_SIZE];
        first = last = count = 0;
    }
    ~queue(){
        delete[] a;
    }
    bool empty(){
        return count == 0;
    }
    void push(T item){
        if (last != first || count == 0) {
            a[last] = item;
            count++;
        }
        if (last == MAX_SIZE - 1)
            last = 0;
        else
            last++;
    }
    void pop(){
        if (!empty()) {
            a[first].~T();
            count--;
            if (first == MAX_SIZE - 1)
                first = 0;
            else
                first++;
        }
    }
    T front(){
        return a[first];
    }
};

class Node {
public:
    Node(int value = 0){
        data = value;
        left = nullptr;
        down = nullptr;
        right = nullptr;
        up = nullptr;
    }
    int data;
    Node *left, *down, *right, *up;
};
class Tree {
private:
    queue<int> result;
    void _delete(Node *current){
        if (current != nullptr){
            Node *l = current->left;
            Node *d = current->down;
            Node *r = current->right;
            Node *u = current->up;
            delete current;
            current = nullptr;
            _delete(l);
            _delete(d);
            _delete(r);
            _delete(u);
        }
    }
public:
    Tree(){
        root = nullptr;
    }
    ~Tree(){
        _delete(root);
    }
    Node *root;
    void visit(Node *current){
        result.push(current->data);
    }
    void print(){
        while (true) {
            cout << result.front();
            result.pop();
            if (!result.empty())
                cout << " ";
            else
                break;
        }
        cout << endl;
    }
    void preOrder(Node *current){
        if (current != nullptr){
            visit(current);
            preOrder(current->left);
            preOrder(current->down);
            preOrder(current->right);
            preOrder(current->up);
        }
    }
    void postOrder(Node *current){
        if (current != nullptr){
            postOrder(current->left);
            postOrder(current->down);
            postOrder(current->right);
            postOrder(current->up);
            visit(current);
        }
    }
    void levelOrder(){
        queue<Node*> q;
        Node *current = root;
        while (current){
            visit(current);
            if (current->left != nullptr) q.push(current->left);
            if (current->down != nullptr) q.push(current->down);
            if (current->right != nullptr) q.push(current->right);
            if (current->up != nullptr) q.push(current->up);
            if (q.empty()) return;
            current = q.front();
            q.pop();
        }
    }
};

Node* makeTree(int** matrix, Node *current, int x, int y, int dir);
int** makeMatrix(int w, int h);
int width, height;

int main() {
    int n, start_x, start_y;
    string command;

    cin >> n;

    while (n-- > 0){
        Tree tree;
        int** matrix;
        cin >> width;
        cin >> height;
        cin >> start_x;
        cin >> start_y;

        matrix = makeMatrix(width, height);
        cin >> command;

        if (matrix[start_y][start_x] != 0) {
            tree.root = makeTree(matrix, tree.root, start_x, start_y, 0);

            if (command == "Pre-order-traversal") {
                tree.preOrder(tree.root);
                tree.print();
            } else if (command == "Post-order-traversal") {
                tree.postOrder(tree.root);
                tree.print();
            } else if (command == "Level-order-traversal") {
                tree.levelOrder();
                tree.print();
            }
        }
    }

    return 0;
}

Node* makeTree(int** matrix, Node* current, int x, int y, int dir){
    if (matrix[y][x] != 0)
        current = new Node(matrix[y][x]);

    if (x-1 >= 0 && dir != 3 && matrix[y][x-1] != 0)
        current->left = makeTree(matrix, current->left,  x - 1, y, 1);
    if (y+1 < height && dir != 4 && matrix[y+1][x] != 0)
        current->down = makeTree(matrix, current->down,  x, y + 1, 2);
    if (x+1 < width && dir != 1 && matrix[y][x+1] != 0)
        current->right = makeTree(matrix, current->right, x + 1, y, 3);
    if (y-1 >= 0 && dir != 2 && matrix[y-1][x] != 0)
        current->up = makeTree(matrix, current->up,    x, y - 1, 4);

    return current;
}
int** makeMatrix(int w, int h){
    auto temp = (int**)malloc(sizeof(int*) * h);
    for (int i = 0; i < h; i++){
        temp[i] = (int *) malloc(sizeof(int) * w);
        for (int j = 0; j < w; j++){
            cin >> temp[i][j];
        }
    }

    return temp;
}