#pragma once
#include "GameState.h"
#include "Ship.h"
#include "goods.h"

class State_ShipStatus : public GameState
  // Displays ship stuff.
  {
  public:
    State_ShipStatus(Ship& ship);
    ~State_ShipStatus();
    virtual void Update();
    virtual void Render(TCODConsole *root);
    virtual void End();
    virtual bool Init();
    //virtual void RecoverFromPush() {if (!nextState) delete nextState; pushSomething = false;}
    //
    virtual void RecoverFromPush();
		virtual void Resize(int new_w,int new_h);
    virtual void WindowActive();
    virtual void WindowInactive();
    virtual void KeyUp(const int &key,const int &unicode);
		virtual void KeyDown(const int &key,const int &unicode);
		virtual void MouseMoved(const int &iButton,const int &iX,const int &iY,const int &iRelX,const int &iRelY);
		virtual void MouseButtonUp(const int &iButton,const int &iX,const int &iY,const int &iRelX,const int &iRelY);
		virtual void MouseButtonDown(const int &iButton,const int &iX,const int &iY,const int &iRelX,const int &iRelY);

    TCODConsole* console;

  private:
    int selector;
    bool redraw;
    void redrawList();
    void invertLine(const int& line);
    void printStats(TCODConsole* con, int& line);
    void swapLineColors(TCODConsole* con, const int& line);

    Ship& refToShip;
    std::string newname;
    std::string header();
    std::string assembleOutput(const LedgerItemTuple& tuple);
  };