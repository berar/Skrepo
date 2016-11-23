#ifndef URIHANDLER_H_INCLUDED
#define URIHANDLER_H_INCLUDED

typedef struct attrib {
    char* name;
    char* value;
} attrib;

typedef struct element {
    char* tag;
    attrib attr;
} element;

typedef struct resource {
    char* uri;
    element elem;
} resource;

/**
 * Returns pointer to URIs.
 */
char** getURIs();

/**
 * Returns size of URIs.
 */
int getURICnt();

/**
 * Terminates program on error. Will initialize only once.
 */
void try2InitURIs(resource* res);

#endif // URIHANDLER_H_INCLUDED
