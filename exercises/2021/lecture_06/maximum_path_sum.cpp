#include <iostream>

using namespace std;

struct Node
{
    int value;
    struct Node *left;
    struct Node *right;

    Node(int x)
    {
        value = x;
        left = right = NULL;
    }
};

int main()
{
    int n = -1;

    while (n < 0)
    {
        cout << "Please input the number of elements in the tree."
                "The value must be greater than 0."
             << endl;

        cin >> n;
    }
    int input[n];

    Node *root = buildTree(input, n, root, 0);
}

//Recursively build a binary tree from an array
Node *buildTree(int input[], int n, Node *root, int i)
{
    if (i < n)
    {
        Node node(input[i]);
        *root = node;

        root->left = buildTree(input, n, root->left, 2 * i);
        root->right = buildTree(input, n, root->right, 2 * i + 1);
    }

    return root;
}

//Return the longest root-to-leaf path for the tree and save the maximum
// leaf-to-leaf path in maxPath
int treeTraversal(Node *root, int &maxPath)
{
    //The node is a leaf, so we return its value
    if (root->left == NULL && root->right == NULL)
        return root->value;

    int leftSum = 0, rightSum = 0;

    //Get the longest root-to-leaf path for the left subtree
    if (root->left != NULL)
        leftSum = treeTraversal(root->left, maxPath);

    //Get the longest root-to-leaf path for the right subtree
    if (root->right != NULL)
        rightSum = treeTraversal(root->right, maxPath);

    //Compute the maximum leaf-to-leaf path for this subtree

    //If the node has two children, compute the maximum leaf-to-leaf path and compare it to the maximum
    if (root->left != NULL && root->right != NULL)
    {
        int pathValue = leftSum + rightSum + root->value;
        if (pathValue > maxPath)
            maxPath = pathValue;
    }

    return max(leftSum, rightSum) + root->value;
}

//Return the maximum of two integers
int max(int a, int b)
{
    return a >= b ? a : b;
}