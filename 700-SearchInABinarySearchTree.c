/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

/* C solution
struct TreeNode* searchBST(struct TreeNode* root, int val) {
    if (!root || root->val == val) return root;
    return (val < root->val ? searchBST(root->left, val) : searchBST(root->right, val));
} */

// at&t x86_64 solution using recursion
__attribute__((naked))
struct TreeNode* searchBST(struct TreeNode* root, int val) {
    __asm__(
        "test %rdi, %rdi;" // checking if root is null
        "jne after1;"
        "movq $0, %rax;" // returning null if so
        "ret;"

        "after1:"
        "cmpl (%rdi), %esi;" // checking if val is equal to root val
        "jne after2;"
        "movq %rdi, %rax;" // returning root if so
        "ret;"
        
        "after2:"
        "movq $1, %r8;" // r8 always 1 for indexing purposes
        "movq $2, %r9;" // r9 always 2 for indexing purposes
        "movq (%rdi, %r8, 8), %r10;" // store left node in r10
        "movq (%rdi, %r9, 8), %r11;" // store right node in r11

        "cmpl (%rdi), %eax;" // check if val is less than root val
        "jge right;"
        "movq %r10, %rdi;" // move left node to root for func call
        "jmp end;"

        "right:;"
        "movq %r11, %rdi;" // move right node to root for func call

        "end:;"
        "call searchBST;" // call self
        "ret;"
    );
} 