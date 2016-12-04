#ifndef DIALOG_H
#define DIALOG_H

#include "xmlparser.h"
#include <allegro.h>
extern "C" {
    #include "agup.h"
}
#include <string>
#include <vector>
#include <allegro.h>

class Dialog {
public:
    // Type of allegro's gui functions.
    typedef int (*d_func_proc)(int, DIALOG*, int);
    typedef std::map<std::string, d_func_proc> ProcTable;
    
    // Parameters from script to callbacks.
    typedef std::vector<std::string> Parameters;
    
    struct CallbackData {
        std::string proc;
        const Dialog *dialog;
        const XmlNode *xmlNode;
        const Parameters &parameters;
        
        CallbackData(const std::string &proc, const Dialog *dialog = 0,
                     const XmlNode *xmlNode = 0,
                     const Parameters &parameters = Parameters())
                     : proc(proc), dialog(dialog), xmlNode(xmlNode),
                       parameters(parameters)
        {}
    };
    
    // Callbacks should return D_O_K by default.
    // 
    // 'dialog' is the dialog that caused this callback.
    // 'xmlNode' is the one that caused this callback to be called.
    // It may be null, so check for that.
    typedef int (*callback_t)(CallbackData);
    typedef std::map<std::string, callback_t> DefCallbacks;
    
    static ProcTable procTable;
    static DefCallbacks defCallbacks;
    
    Dialog();
    Dialog(const XmlNodes&);
    Dialog(std::istream &inStream);
    Dialog(const std::string &filename);
    ~Dialog();
    
    // Loads the xmlCache from various sources.  The source will contain
    // the XML required to display and run this dialog.
    void load(const XmlNodes&);
    void load(std::istream &inStream);
    void load(const std::string &filename);
    
    // Sets the given callback to 'callback'.
    // If 'callback' is 0 than the callback is removed.
    //
    // A script can call this callback by setting the appropriate field to
    // whatever 'name' is (typically dp).
    void setCallback(const std::string &name, callback_t callback = 0);
    
    // Returns the active dialog pointer or 0 if none are active.
    static Dialog *getActiveDialog();
    
    // Returns the XmlNode that closed the dialog.  Pointer valid
    // until load or dtor called.
    //
    // Will not work if you've called initDialog but failed to call
    // shutdownDialog
    XmlNode *doDialog();
    
    // Uses this to start non-blocking usage.  Safety checks are performed.
    void initDialog();
    
    // Do this to update and draw the dialog.  If false returned you must
    // call shutdownDialog, this dialog has been ended.
    // Safety checks are performed.
    bool updateDialog();
    
    // Returns a reference to the string for the given registry value.
    // The reference can become invalid, so don't rely on it permanently.
    static std::string &registry(int index);
    
    // Use this to end non-blocking usage.  Safety checks are performed.
    XmlNode *shutdownDialog();
    
    // unloads and then loads again this dialog's agup theme.
    void reloadTheme();
    
    // For internal use
    class Dirt {
    public:
        void *ptr;
        int type;
        static const int T_BITMAP = 1;
        static const int T_CSTR = 2;
        
        Dirt(void *ptr, int type) : ptr(ptr), type(type) {}
    };
    
    // For internal use only.  Handles proc magic.  Returns what the proc
    // should be for 'd'.  Returns 0 if not found.
    d_func_proc lookupProc(DIALOG *d);
    
    // private:
    
    // Cleans up all the dirt, dialog, menus etc.
    void cleanup();
    
    // Adds DIALOG 'd' to this internal dialog list.  Performs magic with proc
    // help the capturing of active_dialog_item.
    //
    // Warning the proc parameter will change!  This due to proc magic.
    void addToDialog(DIALOG &d);
    
    // Finds XmlNode in xmlCache by index.  0 if not found.
    XmlNode *findByIndex(int index);
    XmlNode *findByMenuIndex(int index);
    
    // Returns -1 if invalid index.
    int findIndex(DIALOG *d);
    int findMenuIndex(MENU *m);
    
    // Shorthand for using findIndex and findByIndex.
    // May return NULL.
    XmlNode *findXmlNode(DIALOG *d);
    XmlNode *findXmlNode(MENU *m);
    
    // Looks up and performs a callback with name 'callback'.  xmlNode is
    // passed to the callback.  Return value should be passed all the way back
    // to the allegro gui.
    int performCallback(const std::string &callback, XmlNode *xmlNode);
    
    // Call this when a DIALOG callback is executed.
    int dialogCallback(DIALOG *dialog);
    
    // Call this when a MENU callback is executed.
    int menuCallback(MENU *dialog);
    
    // Returns a MENU* you can use with d_menu_proc.
    // Calling this invalidates previous calls.
    //
    // firstCall should be false (unless loadMenu calls itself).
    MENU *loadMenu(XmlNodes &menuNodes, bool firstCall = true);
    
    // For internal use by loadMenu.
    //
    // This does post-processing on 'menus' to make child pointers line up.
    // xmlNodes must have indexes set properly (no invalids allowed).
    void loadMenuChildPointers(const XmlNodes &xmlNodes);
    
    XmlNodes xmlCache;
    
    // Menus is a particularly weird array.  Root level elements are from the
    // begining until the MENU whose text field is NULL.  After that follow all
    // child menus, grandchild menus etc in the order they are discovered.
    // This is so we can lookup a MENU again yet stay comatible with allegro.
    typedef std::vector<MENU> Menus;
    Menus menus;
    
    typedef std::vector<DIALOG> dialog_t;
    typedef std::vector<d_func_proc> Procs;
    dialog_t dialog;
    Procs procs;
    
    int defaultFocus;
    DIALOG_PLAYER *player;
    
    typedef std::vector<Dirt> Dirts;
    Dirts dirts;
    
    typedef std::map<std::string, callback_t> Callbacks;
    Callbacks callbacks;
    
    // Set to true to reload on the next loop.
    bool reload;
    
    AGUP_THEME const *theme;
    
    XmlNode::Attr prefs;
    
    FONT *oldFont;
};

#endif
