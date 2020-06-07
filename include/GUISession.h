#ifndef _GUI_SESSION_H_
#define _GUI_SESSION_H_

class GUISession {
public:
  GUISession() { glfwInit(); }

  ~GUISession() { glfwTerminate(); }
};

#endif /* _GUI_SESSION_H_ */
