#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

//#include "map"

#include "gui_sudoku.hpp"
#include "SudokuJoints.cpp"
//#include "sudoku_attr.cpp"
//#include "Utils.cpp"
//#include "PrintStuff.cpp"

IMPLEMENT_APP(SudokuSolver)

bool SudokuSolver::OnInit()
{
  MainFrame *MainWin = new MainFrame(_T("Sudoku Solver"), wxPoint(1, 1), wxSize(450, 600));
  MainWin->Show(TRUE);

  return TRUE;
}

BEGIN_EVENT_TABLE(MainFrame, wxFrame)
  EVT_BUTTON(BUTTON_SOLVE, MainFrame::Solve)
  EVT_BUTTON(BUTTON_CLEAR, MainFrame::Clear)
END_EVENT_TABLE()

MainFrame::MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size) : wxFrame((wxFrame *)NULL, -1, title, pos, size)
{
  sizer = new wxBoxSizer(wxVERTICAL);
  gs = new wxGridSizer(maxRows, maxColumns, 3, 3);

  for (int i = 0; i < maxRows; i++)
  {
    for (int z = 0; z < maxColumns; z++)
    {
      wxTextCtrl *cell = new wxTextCtrl(this, -1, wxT(""));
      cell->SetMaxLength(1);
      gs->Add(cell, 0, wxEXPAND);
    }
  }

  sizer->Add(gs, 1, wxEXPAND);

  ButtonSolve = new wxButton(this, BUTTON_SOLVE, _T("Solve it!"), wxDefaultPosition, wxDefaultSize, 0);
  ButtonClear = new wxButton(this, BUTTON_CLEAR, _T("Clear"), wxDefaultPosition, wxDefaultSize, 0);
  sizer->Add(ButtonSolve, 0, wxEXPAND);
  sizer->Add(ButtonClear, 0, wxEXPAND);
  SetSizer(sizer);
  SetMinSize(wxSize(270, 220));
  Centre();
}

void MainFrame::Solve(wxCommandEvent &event)
{
  int inserts = 0;
  while(inserts < gs->GetItemCount()){
    for (int row = 0; row < maxColumns; row++){
      for (int column = 0; column < maxColumns; column++){
        wxTextCtrl *control = (wxTextCtrl *)gs->GetItem(inserts)->GetWindow();
        cells[row][column] = wxAtoi(control->GetValue());
        inserts++;
      }
    }
  }

  SudokuJoints::solve();

  inserts = 0;

  while(inserts < gs->GetItemCount()){
    for (int row = 0; row < maxColumns; row++){
      for (int column = 0; column < maxColumns; column++){
        wxTextCtrl *control = (wxTextCtrl *)gs->GetItem(inserts)->GetWindow();
        wxString value = wxString::Format(wxT("%i"),cells[row][column]);
        control->ChangeValue(value);
        inserts++;
      }
    }
  }

}

void MainFrame::Clear(wxCommandEvent &event){
    for (int i = 0; i < gs->GetItemCount(); i++){
        wxTextCtrl *control = (wxTextCtrl *)gs->GetItem(i)->GetWindow();
        control->ChangeValue("");
    }
}

void MainFrame::OnExit(wxCommandEvent &event)
{
  Close(TRUE);
}