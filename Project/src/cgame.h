// Utility class used to draw text on the screen using a 
// specific font.


// #include <stdio.h>
class CGameFont
{
public:
  // Default constructor
  CGameFont();
  // Default destructor
  ~CGameFont();

  // Create the font with a specific height and weight.
  void CreateFont(const std::string& strTypeface , 
          int iFontHeight, 
          int iFontWeight);
  // Draw text on the screen at the specified location with
  // the specified colour.
  void DrawText(const std::string& strText, int XPos, 
          int YPos, GLfloat fRed, GLfloat fGreen, 
          GLfloat fBlue);

  // Returns the size of the text. The top and right fields
  // of the returned rectangle are set to 0.
  TRectanglei GetTextSize(const std::string& strText);

  static void SetDeviceContext(HDC hDevContext)  
  { m_hDeviceContext = hDevContext; }

private:
  // The device context used to create the font.
  static HDC m_hDeviceContext;
  // The index of the base of the lists.
  GLuint m_uiListBase;
  // The win32 font
  HFONT m_hFont;
};

// Manages the different states of the game.
class CStateManager
{
public:
  // Default constructor
  CStateManager();
  // Default destructor
  ~CStateManager();

  // Switches to another active state.
  void ChangeState(CGameState* pNewState)
  {
    if (m_pActiveState)
      m_pActiveState->LeaveState();
    m_pActiveState = pNewState;
    m_pActiveState->EnterState();
  }

  // Returns the current active state.
  CGameState* GetActiveState()  { return m_pActiveState; }

  // 'Events' function, they are simply redirected to
  // the active state.
  void OnKeyDown(WPARAM wKey);
  void OnKeyUp(WPARAM wKey);
  void Update(DWORD dwCurrentTime);
  void Draw();

private:
  // Active State of the game (intro, play, ...)
  CGameState* m_pActiveState;   
};

void CGameFont::CreateFont(const std::string& strTypeface, 
               int iFontHeight,
               int iFontWeight)
{
  if (!m_hDeviceContext)
  {
    string strError = "Impossible to create the font: ";
    strError += strTypeface;
    throw CException(strError);
    return;
  }

  // Ask openGL to generate a contiguous set of 255 display lists.
  m_uiListBase = glGenLists(255);
  if (m_uiListBase == 0)
  {
    string strError = "Impossible to create the font: ";
    strError += strTypeface;
    throw CException(strError);
    return;
  }

  // Create the Windows font
  m_hFont = ::CreateFont(-iFontHeight,
                  0,
                  0,
                  0,
                  iFontWeight,
                  FALSE,
                  FALSE,
                  FALSE,
                  ANSI_CHARSET,
                  OUT_TT_PRECIS,
                  CLIP_DEFAULT_PRECIS,
                  ANTIALIASED_QUALITY,
                  FF_DONTCARE|DEFAULT_PITCH,
                  strTypeface.c_str());
  if (m_hFont == NULL)
  {
    m_uiListBase = 0;
    string strError = "Impossible to create the font: ";
    strError += strTypeface;
    throw CException(strError);
    return;
  }

  // Select the newly create font into the device context (and save the previous
  // one).
  HFONT hOldFont = (HFONT)SelectObject(m_hDeviceContext, m_hFont);
  // Generate the font display list (for the 255 characters) starting
  // at display list m_uiListBase.
  wglUseFontBitmaps(m_hDeviceContext, 0, 255, m_uiListBase);  
  // Set the original font back in the device context
  SelectObject(m_hDeviceContext, hOldFont); 
}


void CGameFont::DrawText(const std::string& strText, 
             int XPos, int YPos,
             GLfloat fRed, 
             GLfloat fGreen, 
             GLfloat fBlue)
{
  if (m_uiListBase == 0)
  {
    throw CException("Impossible to diplay the text.");
    return;
  }

  // Disable 2D texturing
  glDisable(GL_TEXTURE_2D);
  // Specify the current color
  glColor3f(fRed, fGreen, fBlue);
  // Specify the position of the text
  glRasterPos2i(XPos, YPos);

  // Push the list base value
  glPushAttrib (GL_LIST_BIT);
    // Set a new list base value. 
    glListBase(m_uiListBase);
    // Call the lists to draw the text.
    glCallLists((GLsizei)strText.size(), GL_UNSIGNED_BYTE, 
          (GLubyte *)strText.c_str());
  glPopAttrib ();

  // Reenable 2D texturing
  glEnable(GL_TEXTURE_2D);



CGameFont::~CGameFont()
{
  if (m_uiListBase)
    glDeleteLists(m_uiListBase,255);
  DeleteObject(m_hFont);
}