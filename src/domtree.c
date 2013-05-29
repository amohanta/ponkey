/*
 *
 * AUTHOR: Pankaj Tanwar <pankaj.tux@gmail.com>
 *
 * This program is free software subject to the terms of the GNU General Public
 * License.  You can use, copy, redistribute and/or modify the program under
 * the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 3 of the License, or (at your option)
 * any later version. You should have received a copy of the GNU General Public
 * License along with this program.  If not, please see
 * http://www.gnu.org/licenses/ for a copy of the GNU General Public License.
 *
 * The program is subject to a disclaimer of warranty and a limitation of
 * liability, as disclosed below.
 *
 * Disclaimer of Warranty.
 *
 * THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY
 * APPLICABLE LAW.  EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT
 * HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM "AS IS" WITHOUT WARRANTY
 * OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE.  THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM
 * IS WITH YOU.  SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF
 * ALL NECESSARY SERVICING, REPAIR, CORRECTION OR RECOVERY FROM DATA LOSS OR
 * DATA ERRORS.
 *
 * Limitation of Liability.
 *
 * IN NO EVENT UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING
 * WILL ANY COPYRIGHT HOLDER, OR ANY OTHER PARTY WHO MODIFIES AND/OR CONVEYS
 * THE PROGRAM AS PERMITTED ABOVE, BE LIABLE TO YOU FOR DAMAGES, INCLUDING ANY
 * GENERAL, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES ARISING OUT OF THE
 * USE OR INABILITY TO USE THE PROGRAM (INCLUDING BUT NOT LIMITED TO LOSS OF
 * DATA OR DATA BEING RENDERED INACCURATE OR LOSSES SUSTAINED BY YOU OR THIRD
 * PARTIES OR A FAILURE OF THE PROGRAM TO OPERATE WITH ANY OTHER PROGRAMS),
 * EVEN IF SUCH HOLDER OR OTHER PARTY HAS BEEN ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGES.
 *
 */

/* TODO
 * 1. error handling 
 * 2. child additions next sibling - DONE
 * 3. linear search working fine
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum association { PARENT, SIBLING };

#define MAXID 20

typedef struct dom_node {
	char id[MAXID];
	struct dom_node *parent;
	struct dom_node *child;
	struct dom_node *nextsibling;
	struct dom_node *prevsibling;
	//add attributes
} dom_node;

static dom_node *root = NULL;

typedef struct globallist {
	dom_node *entry;
	struct globallist *next;
} globallist;

/* Global list for keeping pointers to every element */
static globallist *list=NULL;


/* Initialize DOM tree root element */
static int initDOMRoot(const char *id)
{
	root = (dom_node*) malloc(sizeof(dom_node));

	strcpy(root->id, id);
	root->parent = root->child = NULL;
	root->nextsibling = root->prevsibling = NULL;

	list = (globallist*) malloc(sizeof(globallist));
	list->entry = root;
	list->next = NULL;
printf("root id added %s\n", list->entry->id);
}

/* Add new entry to global list */
static int addtogloballist(dom_node *n)
{
	globallist *itr;
	globallist *newnode;

	if(list == NULL) {
		initDOMRoot("html");
	}

	itr = list;
	while(itr->next != NULL) {
		itr = itr->next;
	}

	newnode = (globallist*)malloc(sizeof(globallist));
	newnode->entry = n;
	newnode->next = NULL;
	itr->next = newnode;
}

/* Performing Cleanup 
 * Caution: all global list entries and element nodes deleted
 */
static int delgloballist(globallist *list)
{
	globallist *itr, *tmp;
	int count = 0;

	if(list == NULL)
		return count;

	itr = list;
	while(itr->next != NULL) {
		globallist *tmp = itr;
printf("list node %p deleted\n", itr->entry);
		free(itr->entry);
		free(itr);
		count++;
		itr=tmp->next;
	}
printf("list node %p deleted\n", itr->entry);
	free(itr->entry);
	free(itr);
printf("%d nodes deleted\n", count +1);
	return count+1;

}

/* Add a new node to the DOM tree */
static dom_node* addDOMNode(dom_node *conn, int asstion, const char *id)
{
	if (root == NULL) {
		initDOMRoot(id);
		return root;
	}

	dom_node *newnode = (dom_node*)malloc(sizeof(dom_node));
	strcpy(newnode->id, id);
	newnode->child = NULL;
	newnode->nextsibling = NULL;
	
	if(asstion==PARENT) {
		newnode->parent=conn;
		if(conn != NULL)
			conn->child = newnode;
	} else {
		newnode->prevsibling=conn;
		conn->nextsibling=newnode;
	}

	addtogloballist(newnode);

	return newnode;
}

/* Search for id in the list */
static dom_node* searchlist(const char *id)
{
	globallist *itr;

	if(list == NULL)
		return NULL;

/* Search whole list */
	itr = list;
	while(itr->next != NULL) {
		if( (strcmp(itr->entry->id, id)) == 0 ) 
			return itr->entry;

			printf("me = %p\tid = %s \t parent = %p \t Child = %p\t"
				"Presibling = %p \t Nextsibling = %p\n",
				itr->entry, itr->entry->id, itr->entry->parent, itr->entry->child,
				itr->entry->prevsibling, itr->entry->nextsibling);

		
		itr = itr->next;
	}

	printf("me = %p\tid = %s \t parent = %p \t Child = %p\t"
		"Presibling = %p \t Nextsibling = %p last one\n",
		itr->entry, itr->entry->id, itr->entry->parent, itr->entry->child,
		itr->entry->prevsibling, itr->entry->nextsibling);

/* Search last node */
	if( (strcmp(itr->entry->id, id)) == 0 ) {
		return itr->entry;
	}
/* Not Found */
	return NULL;
}

/* Testing correctness of tree 
 * Result : SUCCESSFUL SO FAR
 */
int main()
{
	addDOMNode(NULL, PARENT, "html");
	dom_node *n = addDOMNode(root, PARENT, "body");
	dom_node *k = addDOMNode(n, PARENT, "head");
	addDOMNode(n, SIBLING, "noooo");
	searchlist("test");
	printf("%p has %s\n",searchlist("head"), searchlist("head")->id );
	delgloballist(list);
}

