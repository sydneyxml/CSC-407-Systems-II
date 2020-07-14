/*-------------------------------------------------------------------------*
 *---									---*
 *---		separator.c						---*
 *---									---*
 *---	    This file defines a C program that separates a comma-	---*
 *---	separated string into its component substrings, puts them into	---*
 *---	a linked list, prints the list, and frees the list.		---*
 *---									---*
 *---	----	----	----	----	----	----	----	----	---*
 *---									---*
 *---	Version 1.0					Joseph Phillips	---*
 *---									---*
 *-------------------------------------------------------------------------*/



#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>

#define		LINE_LEN	256

struct		Word
{
  char*		textPtr_;
  struct Word*	nextPtr_;
};


struct Word*	obtainCommaSeparatedList
				(const char*	string
				)
{
  if  (string == NULL)
  {
    fprintf(stderr,"NULL ptr to obtainCommaSeparatedList()\n");
    exit(EXIT_FAILURE);
  }

  struct Word*	toReturn	= (struct Word*)malloc(sizeof(struct Word));

  if  (*string == '\0')
  {
    toReturn->textPtr_	= (char*)malloc(1);
    *toReturn->textPtr_	= '\0';
    toReturn->nextPtr_	= NULL;
    return(toReturn);
  }

  size_t	diff;

  const char*	charRun;

  for ( charRun = string;
	(*charRun != '\0') && (*charRun != ',');
	charRun++
      );

  diff				= charRun - string;
  toReturn->textPtr_		= (char*)malloc(diff + 1);
  strncpy(toReturn->textPtr_,string,diff);
  toReturn->textPtr_[diff]	= '\0';

  toReturn->nextPtr_	= (*charRun == ',')
			  ? obtainCommaSeparatedList(charRun+1)
			  : NULL;

  return(toReturn);
}


void		printCommaSeparatedList
				(const struct Word*	list
				)
{
  for  ( ; list != NULL;  list = list->nextPtr_)
    printf("\t\"%s\"\n",list->textPtr_);
}


void		freeCommaSeparatedList
				(struct Word*	list
				)
{
  if  (list == NULL)
    return;

  free(list->textPtr_);
  freeCommaSeparatedList(list->nextPtr_);
  free(list);
}


int		main		()
{
  char		line[LINE_LEN];
  struct Word*	listPtr	= NULL;
  struct Word*	run;

  printf("Please enter a line of text: ");
  fgets(line,LINE_LEN,stdin);

  char*		cPtr	= strchr(line,'\n');

  if  (cPtr != NULL)
    *cPtr = '\0';

  listPtr	= obtainCommaSeparatedList(line);
  printCommaSeparatedList(listPtr);
  freeCommaSeparatedList (listPtr);
  return(EXIT_SUCCESS);
}
