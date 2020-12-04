  #ifndef __BASE_H
  #define __BASE_H
    class SudokuSolver: public wxApp
    { 
    public:
      virtual bool OnInit();
    };
    
    class MainFrame: public wxFrame
    {
    public:
      MainFrame( const wxString &title, const wxPoint &pos, const wxSize &size );
      wxBoxSizer *sizer;
      wxGridSizer *gs;
      wxButton *ButtonSolve;
      wxButton *ButtonClear;
      void OnExit( wxCommandEvent& event );
      void Solve( wxCommandEvent& event );
      void Clear( wxCommandEvent& event );
  
      DECLARE_EVENT_TABLE()
    };
  
    enum
    {
      BUTTON_SOLVE = 1,
      BUTTON_CLEAR = 2
    };
 
  #endif