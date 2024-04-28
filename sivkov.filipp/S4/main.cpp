struct Node
{
  int key;
  Node* left;
  Node* right;
  int height;
};

struct Tree
{
  Node* root;
  Tree():
   root(nullptr)
  {}
  Node* newNode(int key)
  {
    Node* node = new Node();
    node->key = key;
    node->left = nullptr;
    node->right = nullptr;
    node->height = 1;
    return node;
  }

  int height(Node* node)
  {
    if (node == nullptr)
    {
      return 0;
    }
    return node->height;
  }

    int getBalance(Node* node)
    {
      if (node == nullptr)
      {
            return 0;
      }
        return height(node->left) - height(node->right);
    }

    Node* rightRotate(Node* y)
    {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = std::max(height(y->left), height(y->right)) + 1;
        x->height = std::max(height(x->left), height(x->right)) + 1;

        return x;
    }

    Node* leftRotate(Node* x)
    {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = std::max(height(x->left), height(x->right)) + 1;
        y->height = std::max(height(y->left), height(y->right)) + 1;

        return y;
    }

    Node* insert(Node* node, int key) {
        if (node == nullptr)
            return newNode(key);

        if (key < node->key)
        {
            node->left = insert(node->left, key);
        }
        else if (key > node->key)
        {
            node->right = insert(node->right, key);
        }
        else
        {
            return node;
        }
        node->height = 1 + std::max(height(node->left), height(node->right));

        int balance = getBalance(node);

        if (balance > 1 && key < node->left->key)
        {
            return rightRotate(node);
        }
        // RR
        if (balance < -1 && key > node->right->key)
        {
            return leftRotate(node);
        }
        // LR
        if (balance > 1 && key > node->left->key)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // RL
        if (balance < -1 && key < node->right->key)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    void insert(int key)
    {
        root = insert(root, key);
    }

    void preOrder(Node* root)
    {
        if (root != nullptr)
        {
            std::cout << root->key << " ";
            preOrder(root->left);
            preOrder(root->right);
        }
    }

    void preOrder()
    {
        preOrder(root);
    }
};

int main()
{}
