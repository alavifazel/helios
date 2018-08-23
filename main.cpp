#include <iostream>
#include "httpdownloader.h"
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <string>
#include <gumbo.h>

using namespace std;

void search_for_links(GumboNode *node) {
  if (node->type != GUMBO_NODE_ELEMENT){
    return;
  }
  GumboAttribute *href;
  if (node->v.element.tag == GUMBO_TAG_A &&
      (href = gumbo_get_attribute(&node->v.element.attributes, "href"))) {
    std::cout << href->value << std::endl;
  }
  GumboVector *children = &node->v.element.children;
  for (unsigned int i = 0; i < children->length; ++i) {
    search_for_links(static_cast<GumboNode*>(children->data[i]));
  }
}

int main(int argc, char** argv) {
    if(argc != 2) {
        cerr << "Usage: helios <url>\n";
        exit(EXIT_FAILURE);
    }
    string url = argv[1];
    HTTPDownloader h;
    try {
        string contents = h.download(url);
        GumboOutput* output = gumbo_parse(contents.c_str());
        search_for_links(output->root);
        gumbo_destroy_output(&kGumboDefaultOptions, output);
    } catch (const exception &e) {
        cerr << e.what() << ".\n";
    }

}
