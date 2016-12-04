#ifndef EDITOR_H
#define EDITOR_H

#include "dialog.h"
#include <string>
#include <vector>

class Editor {
public:
    Editor();
    ~Editor();
    
    // Runs the editor
    void doEditor(const std::string &filename);
    
    // Below is private, don't touch
    
    std::string filename;
    
    void reload();
    void drawProject(int x = 0, int y = 15);
    
    void add(const std::string &tagName);
    void modify(int index);
    
    std::string generateScript();
    
    Dialog dialog;
    XmlNodes project;
    
    bool modified;
    bool redraw;
    
    void undoStep();
    void undo();
    void redo();
    
    typedef std::vector<XmlNodes> Queue;
    Queue undoQueue, redoQueue;
    
    int wRes;
    int hRes;
};

#endif
