#include <assert.h>
#include "BSTree.h"
#include <stdio.h>


/* Menu that can be used to test individual functions */

void menuTree(BSTree tree);


int main(void)
{
    BSTree tree = emptyTree();
    
    menuTree(tree);
    
    return 0;
}




void menuTree(BSTree tree)
{
    int choice, data;
    char c;
    
    do
    {
        printf("\n\n--------------MENU--------------\n"
               "1 - Add to tree\n"
               "2 - Remove from tree\n"
               "3 - Print in preorder\n"
               "4 - Print in inorder\n"
               "5 - Print in postorder\n"
               "6 - Number of nodes in tree\n"
               "7 - Depth of tree (actual and theoretical)\n"
               "8 - Is the tree empty?\n"
               "9 - Balance tree\n"
               "10 - Search in tree\n"
               "11 - Free tree\n"
               "12 - End program\n"
               "-----------------------------------\n"
               "Choice: ");
        
        scanf("%d", &choice);
        while((c = getchar()) != '\n' && c != EOF); //clears the input buffert
        
        switch(choice)
        {
            case 1: printf("Data to add: ");
                scanf("%d", &data);
                insertSorted(&tree, data);
                printf("Tree: ");
                printPreorder(tree, stdout);
                break;
            case 2: printf("Data to remove: ");
                scanf("%d", &data);
                removeElement(&tree, data);
                printf("Tree: ");
                printPreorder(tree, stdout);
                break;
            case 3: printf("Tree in preorder: ");
                printPreorder(tree, stdout);
                break;
            case 4: printf("Tree in inorder: ");
                printInorder(tree, stdout);
                break;
            case 5: printf("Tree in postorder: ");
                printPostorder(tree, stdout);
                break;
            case 6: printf("Number of nodes in tree: %d", numberOfNodes(tree));
                break;
            case 7: printf("Actual depth of tree: %d\n", depth(tree));
                printf("Theoretical minimum depth of tree: %d\n", minDepth(tree));
                break;
            case 8: if (isEmpty(tree) == 1)
                printf("The tree is empty!\n");
            else
                printf("The tree is not empty!\n");
                
                break;
            case 9: balanceTree(&tree);
                break;
            case 10: printf("Data to search for: ");
                scanf("%d", &data);
                if (find(tree, data) == 1)
                    printf("%d was found in the tree", data);
                else
                    printf("%d was not found in the tree", data);
                
                break;
            case 11: freeTree(&tree);
                break;
            case 12: printf("Ending tree menu\n"); break;
            default: printf("Wrong input\n");
        }
        
    }while(choice != 12);
    
    freeTree(&tree);
    
}




