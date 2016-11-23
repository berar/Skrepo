#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include "urihandler.h"
#include "stringutil.h"

#define RES_TAG "resource"
#define URI_TAG "uri"
#define ELEM_TAG "element"
#define TAG_TAG "tag"
#define ATTRIB_TAG "attrib"

#define URIS_FILE_NAME "resources.xml"

static char* uris[111];
static int uriCnt = 0, initialized = 0;

static void parseElem(xmlNode* node, resource* res) {
    char* nodeName = node->name;
    if (strcmp(nodeName, RES_TAG) == 0) {
        resource r;
        res[uriCnt++] = r;
    } else if (strcmp(nodeName, URI_TAG) == 0) {
        res[uriCnt - 1].uri = xmlNodeGetContent(node);
    } else if (strcmp(nodeName, ELEM_TAG) == 0) {
        element e;
        res[uriCnt - 1].elem = e;
    } else if (strcmp(nodeName, TAG_TAG) == 0) {
        res[uriCnt - 1].elem.tag = xmlNodeGetContent(node);
    } else if (strcmp(nodeName, ATTRIB_TAG) == 0) {
        attrib a;
        a.value = xmlNodeGetContent(node);
        xmlAttr* attribute = node->properties;
        xmlChar* name = xmlNodeListGetString(node->doc, attribute->children, 1);
        a.name = name;
        res[uriCnt - 1].elem.attr = a;
    }
}

static void parseNode(xmlNode* a_node, resource* res) {
    xmlNode *cur_node = NULL;
    for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
        if (cur_node->type == XML_ELEMENT_NODE) {
            parseElem(cur_node, res);
        }
        parseNode(cur_node->children, res);
    }
}

static void initURIs(resource* res) {
    xmlDoc *doc = NULL;
    xmlNode *root_element = NULL;

    doc = xmlReadFile(URIS_FILE_NAME, NULL, 0);
    if (doc == NULL) {
        printf("Could not parse file %s\n", URIS_FILE_NAME);
        exit(1);
    }

    root_element = xmlDocGetRootElement(doc);
    parseNode(root_element, res);

    xmlFreeDoc(doc);
    xmlCleanupParser();
}

void try2InitURIs(resource* res) {
    if (initialized == 1)
        return;

    initURIs(res);
    initialized = 1;
}

char** getURIs() {
    return uris;
}

int getURICnt() {
    return uriCnt;
}
