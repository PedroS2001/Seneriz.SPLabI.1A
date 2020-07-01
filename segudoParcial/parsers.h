#ifndef PARSERS_H_INCLUDED
#define PARSERS_H_INCLUDED



#endif // PARSERS_H_INCLUDED

int controller_loadFromText(char* path, LinkedList* pArray);
int parser_paisFromText(FILE* pFile, LinkedList* pArray);
int controller_ListPaises(LinkedList* pArray);
int controller_saveAsText(char* path, LinkedList* pArray);
