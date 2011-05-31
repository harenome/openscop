
    /*+-----------------------------------------------------------------**
     **                       OpenScop Library                          **
     **-----------------------------------------------------------------**
     **                      extensions/arrays.c                        **
     **-----------------------------------------------------------------**
     **                   First version: 07/12/2010                     **
     **-----------------------------------------------------------------**

 
 *****************************************************************************
 * OpenScop: Structures and formats for polyhedral tools to talk together    *
 *****************************************************************************
 *    ,___,,_,__,,__,,__,,__,,_,__,,_,__,,__,,___,_,__,,_,__,                *
 *    /   / /  //  //  //  // /   / /  //  //   / /  // /  /|,_,             *
 *   /   / /  //  //  //  // /   / /  //  //   / /  // /  / / /\             *
 *  |~~~|~|~~~|~~~|~~~|~~~|~|~~~|~|~~~|~~~|~~~|~|~~~|~|~~~|/_/  \            *
 *  | G |C| P | = | L | P |=| = |C| = | = | = |=| = |=| C |\  \ /\           *
 *  | R |l| o | = | e | l |=| = |a| = | = | = |=| = |=| L | \# \ /\          *
 *  | A |a| l | = | t | u |=| = |n| = | = | = |=| = |=| o | |\# \  \         *
 *  | P |n| l | = | s | t |=| = |d| = | = | = | |   |=| o | | \# \  \        *
 *  | H | | y |   | e | o | | = |l|   |   | = | |   | | G | |  \  \  \       *
 *  | I | |   |   | e |   | |   | |   |   |   | |   | |   | |   \  \  \      *
 *  | T | |   |   |   |   | |   | |   |   |   | |   | |   | |    \  \  \     *
 *  | E | |   |   |   |   | |   | |   |   |   | |   | |   | |     \  \  \    *
 *  | * |*| * | * | * | * |*| * |*| * | * | * |*| * |*| * | /      \* \  \   *
 *  | O |p| e | n | S | c |o| p |-| L | i | b |r| a |r| y |/        \  \ /   *
 *  '---'-'---'---'---'---'-'---'-'---'---'---'-'---'-'---'          '--'    *
 *                                                                           *
 * Copyright (C) 2008 University Paris-Sud 11 and INRIA                      *
 *                                                                           *
 * (3-clause BSD license)                                                    *
 * Redistribution and use in source  and binary forms, with or without       *
 * modification, are permitted provided that the following conditions        *
 * are met:                                                                  *
 *                                                                           *
 * 1. Redistributions of source code must retain the above copyright notice, *
 *    this list of conditions and the following disclaimer.                  *
 * 2. Redistributions in binary form must reproduce the above copyright      *
 *    notice, this list of conditions and the following disclaimer in the    *
 *    documentation and/or other materials provided with the distribution.   *
 * 3. The name of the author may not be used to endorse or promote products  *
 *    derived from this software without specific prior written permission.  *
 *                                                                           *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR      *
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES *
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.   *
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,          *
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT  *
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, *
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY     *
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT       *
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF  *
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.         *
 *                                                                           *
 * OpenScop Library, a library to manipulate OpenScop formats and data       *
 * structures. Written by:                                                   *
 * Cedric Bastoul     <Cedric.Bastoul@u-psud.fr> and                         *
 * Louis-Noel Pouchet <Louis-Noel.pouchet@inria.fr>                          *
 *                                                                           *
 *****************************************************************************/

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <ctype.h>
# include <openscop/extension.h>


/*+***************************************************************************
 *                          Structure display function                       *
 *****************************************************************************/


/**
 * openscop_arrays_print_structure function:
 * this function displays a openscop_arrays_t structure (*arrays) into a file
 * (file, possibly stdout) in a way that trends to be understandable. It
 * includes an indentation level (level) in order to work with others
 * print_structure functions.
 * \param file   The file where the information has to be printed.
 * \param arrays The arrays structure whose information has to be printed.
 * \param level  Number of spaces before printing, for each line.
 */
void
openscop_arrays_print_structure(FILE * file, openscop_arrays_p arrays,
                                int level)
{
  int i, j;

  // Go to the right level.
  for (j = 0; j < level; j++)
    fprintf(file, "|\t");

  if (arrays != NULL)
    fprintf(file, "+-- openscop_arrays_t\n");
  else
    fprintf(file, "+-- NULL arrays\n");

  if (arrays != NULL)
  {
    // Go to the right level.
    for(j = 0; j <= level; j++)
      fprintf(file, "|\t");
  
    // Display the number of names.
    fprintf(file, "nb_names: %d\n", arrays->nb_names);

    // Display the id/name.
    for(i = 0; i < arrays->nb_names; i++)
    {
      // Go to the right level.
      for(j = 0; j <= level; j++)
        fprintf(file, "|\t");
      
      fprintf(file, "id: %2d, name: %s\n", arrays->id[i], arrays->names[i]);
    }
  }

  // The last line.
  for (j = 0; j <= level; j++)
    fprintf(file, "|\t");
  fprintf(file, "\n");
}


/**
 * openscop_arrays_print function:
 * this function prints the content of an openscop_arrays_t structure
 * (*arrays) into a file (file, possibly stdout).
 * \param file   The file where the information has to be printed.
 * \param arrays The arrays structure whose information has to be printed.
 */
void
openscop_arrays_print(FILE * file, openscop_arrays_p arrays)
{
  openscop_arrays_print_structure(file, arrays, 0);
}


/**
 * openscop_arrays_print_openscop function:
 * this function prints the content of an openscop_arrays_t structure
 * (*arrays) into a string (returned) in the OpenScop textual format.
 * \param  arrays The arrays structure whose information has to be printed.
 * \return A string containing the OpenScop dump of the arrays structure.
 */
char *
openscop_arrays_print_openscop(openscop_arrays_p arrays)
{
  int i;
  int high_water_mark = OPENSCOP_MAX_STRING;
  char * string = NULL;
  char * buffer;

  if (arrays != NULL)
  {
    string = (char *)malloc(high_water_mark * sizeof(char));
    buffer = (char *)malloc(OPENSCOP_MAX_STRING * sizeof(char));
    if ((string == NULL) || (buffer == NULL))
    {
      fprintf(stderr, "[OpenScop] Error: memory overflow.\n");
      exit(1);
    }
    string[0] = '\0';

    sprintf(buffer, OPENSCOP_TAG_ARRAY_START);
    openscop_util_safe_strcat(&string, buffer, &high_water_mark);

    sprintf(buffer, "\n%d\n", arrays->nb_names);
    openscop_util_safe_strcat(&string, buffer, &high_water_mark);

    for (i = 0; i < arrays->nb_names; i++)
    {
      sprintf(buffer, "%d %s\n", arrays->id[i], arrays->names[i]);
      openscop_util_safe_strcat(&string, buffer, &high_water_mark);
    }
    sprintf(buffer, OPENSCOP_TAG_ARRAY_STOP"\n");
    openscop_util_safe_strcat(&string, buffer, &high_water_mark);

    string = (char *)realloc(string, (strlen(string) + 1) * sizeof(char));
    free(buffer);
  }

  return string;
}


/*****************************************************************************
 *                               Reading function                            *
 *****************************************************************************/


/**
 * openscop_arrays_read function:
 * this function reads an arrays structure from a string complying to the
 * OpenScop textual format and returns a pointer to this arrays structure.
 * The string should contain only one textual format of an arrays structure.
 * \param  extensions The input string where to find an arrays structure.
 * \return A pointer to the arrays structure that has been read.
 */
openscop_arrays_p
openscop_arrays_read(char * extensions)
{
  int i, k, array_id;
  int  nb_names;
  int  *  id;
  char ** names;
  char * content, * content_backup;
  char buff[OPENSCOP_MAX_STRING];
  openscop_arrays_p arrays;

  content = openscop_util_tag_content(extensions, OPENSCOP_TAG_ARRAY_START,
                                                  OPENSCOP_TAG_ARRAY_STOP);

  if (content == NULL)
  {
    fprintf(stderr, "[OpenScop] Info: no array optional tag.\n");
    return NULL;
  }
  content_backup = content;

  // Find the number of names provided.
  nb_names = openscop_util_read_int(NULL, &content);

  // Allocate the array of id and names.
  id = (int *)malloc(nb_names * sizeof(int));
  names = (char **)malloc(nb_names * sizeof(char *));
  for (i = 0; i < nb_names; i++)
    names[i] = NULL;

  // Get each array name.
  for (k = 0; k < nb_names; k++)
  { 
    // Skip blank or commented lines.
    while (*content == '#' || *content == '\n')
    {
      for (; *content != '\n'; ++content)
        continue;
      ++content;
    }

    // Get the array name id.
    for (i = 0; *content && ! isspace(*content); ++i, ++content)
      buff[i] = *content;
    buff[i] = '\0';
    sscanf(buff, "%d", &array_id);
    if (array_id <= 0)
    {
      fprintf(stderr, "[OpenScop] Error: array id must be > 0.\n");
      exit(1);
    }
    id[k] = array_id;

    // Get the array name string.
    while (*content && isspace(*content))
      ++content;
    for (i = 0; *content && ! isspace(*content); ++i, ++content)
      buff[i] = *content;
    buff[i] = '\0';
    names[k] = strdup(buff);

    // Go to the end of line.
    while (*content && *content != '\n')
      ++content;
  }
  free(content_backup);

  arrays = openscop_arrays_malloc();
  arrays->nb_names = nb_names;
  arrays->id       = id;
  arrays->names    = names;

  return arrays;
}


/*+***************************************************************************
 *                    Memory allocation/deallocation function                *
 *****************************************************************************/


/**
 * openscop_arrays_malloc function:
 * This function allocates the memory space for an openscop_arrays_t
 * structure and sets its fields with default values. Then it returns a
 * pointer to the allocated space.
 * \return A pointer to an empty arrays structure with fields set to
 *         default values.
 */
openscop_arrays_p
openscop_arrays_malloc()
{
  openscop_arrays_p arrays;

  arrays = (openscop_arrays_p)malloc(sizeof(openscop_arrays_t));
  if (arrays == NULL)
  {
    fprintf(stderr, "[OpenScop] Error: memory overflow.\n");
    exit(1);
  }
  
  arrays->nb_names = 0;
  arrays->id       = NULL;
  arrays->names    = NULL;

  return arrays;
}


/**
 * openscop_arrays_free function:
 * This function frees the allocated memory for an arrays structure.
 * \param arrays The pointer to the arrays structure we want to free.
 */
void
openscop_arrays_free(openscop_arrays_p arrays)
{
  int i;

  if (arrays != NULL)
  {
    if (arrays->names != NULL)
    {
      free(arrays->id);
      for (i = 0; i < arrays->nb_names; i++)
        free(arrays->names[i]);
      free(arrays->names);
    }

    free(arrays);
  }
}


/*+***************************************************************************
 *                            Processing functions                           *
 *****************************************************************************/


/**
 * openscop_arrays_copy function:
 * This function builds and returns a "hard copy" (not a pointer copy) of an
 * openscop_arrays_t data structure.
 * \param arrays The pointer to the arrays structure we want to copy.
 * \return A pointer to the copy of the arrays structure.
 */
openscop_arrays_p
openscop_arrays_copy(openscop_arrays_p arrays)
{
  openscop_arrays_p copy;
  int i;

  if (arrays == NULL)
    return NULL;

  copy = openscop_arrays_malloc();
  if (copy != NULL)
  {
    copy->nb_names = arrays->nb_names;
    copy->id = (int *)malloc(arrays->nb_names * sizeof(int));
    copy->names = (char **)malloc(arrays->nb_names * sizeof(char*));
    if ((copy->id == NULL) || (copy->names == NULL))
    {
      fprintf(stderr, "[OpenScop] Error: memory overflow.\n");
      exit(1);
    }
    for (i = 0; i < arrays->nb_names; i++)
    {
      copy->id[i] = arrays->id[i];
      copy->names[i] = strdup(arrays->names[i]);
      if ((copy->names[i] == NULL) && (arrays->names[i] != NULL))
      {
        fprintf(stderr, "[OpenScop] Error: memory overflow.\n");
        exit(1);
      }
    }
  }

  return copy;
}


/**
 * openscop_arrays_equal function:
 * this function returns true if the two arrays structures are the same
 * (content-wise), false otherwise. This functions considers two arrays
 * structures as equal if the order of the array names differ, however the
 * identifiers and names must be the same.
 * \param a1  The first arrays structure.
 * \param a2  The second arrays structure.
 * \return 1 if a1 and a2 are the same (content-wise), 0 otherwise.
 */
int
openscop_arrays_equal(openscop_arrays_p a1, openscop_arrays_p a2)
{
  int i, j, found;

  if ((a1 == NULL) && (a2 == NULL))
    return 1;

  if (((a1 == NULL) && (a2 != NULL)) || ((a1 != NULL) && (a2 == NULL)))
    return 0;

  // Check whether the number of names is the same.
  if (a1->nb_names != a2->nb_names)
    return 0;

  // We accept a different order of the names, as long as the identifiers
  // are the same.
  for (i = 0; i < a1->nb_names; i++)
  {
    found = 0;
    for (j = 0; j < a2->nb_names; j++)
    {
      if ((a1->id[i] == a2->id[j]) && (!strcmp(a1->names[i], a2->names[j])))
      {
        found = 1;
        break;
      }
    }
    if (found != 1)
      return 0;
  }

  return 1;
}


/**
 * openscop_arrays_generate_names function:
 * This function generates an array of strings corresponding to array names.
 * The ith string will correspond to the array name with identifier i in the
 * arrays structure. If some identifiers are missing, the corresponding names
 * will be generated. The size of the array of strings corresponds to the
 * maximum identifier, it is returned using the parameter nb_names.
 * \param arrays   The source of some array names.
 * \param nb_names Pointer to the location to store the number of names.
 * \return An array of strings corresponding to the array names.
 */
char **
openscop_arrays_generate_names(openscop_arrays_p arrays, int * nb_names)
{
  char ** names = NULL;
  char ** tmpnames;
  int i;

  *nb_names = 0;

  if (arrays != NULL)
  {
    // Get the maximum id (it will be nb_names).
    for (i = 0; i < arrays->nb_names; i++)
      if (arrays->id[i] > *nb_names)
	*nb_names = arrays->id[i];
  
    // Allocate the array of names and store the existing names.
    names = (char **)malloc(*nb_names * sizeof(char *));
    if (names == NULL)
    {
      fprintf(stderr, "[OpenScop] Error: memory overflow.\n");
      exit(1);
    }
    for (i = 0; i < arrays->nb_names; i++)
    {
      names[arrays->id[i] - 1] = strdup(arrays->names[i]);
      if (names[arrays->id[i] - 1] == NULL)
      {
	fprintf(stderr, "[OpenScop] Error: memory overflow.\n");
	exit(1);
      }
    }

    // Fill the missing names.
    tmpnames = openscop_util_strings_generate("A_", *nb_names);
    for (i = 0; i < *nb_names; i++)
    {
      if (names[i] == NULL || names[i][0] == '\0')
	names[i] = tmpnames[i]; // Use a generated name.
      else
	free(tmpnames[i]);      // Use a read name.
    }
    free(tmpnames);
  }

  return names;
}

