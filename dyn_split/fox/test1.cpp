
#include <fx.h>

class DynResize : public FXMainWindow {
  FXDECLARE(DynResize)
public:
  DynResize(FXApp *app);
  virtual ~DynResize();

  enum {
    ID_DO_SPLIT = FXMainWindow::ID_LAST
  };

  void create();

  long OnCommandDoSplit(FXObject *, FXSelector, void *);
private:
  DynResize() = default;

  FXText *text;
  FXText *text2;

  FXSplitter *splitter;
};

FXDEFMAP(DynResize) drFuncMap[] = {
  FXMAPFUNC(SEL_COMMAND, DynResize::ID_DO_SPLIT, DynResize::OnCommandDoSplit)
};

FXIMPLEMENT(DynResize, FXMainWindow, drFuncMap, ARRAYNUMBER(drFuncMap))

DynResize::DynResize(FXApp *app) :
  FXMainWindow(app, "Testing", nullptr, nullptr, DECOR_ALL, 0, 0, 800, 600), text2{nullptr}
{
  // Create a frame to host things
  FXVerticalFrame *contentFrame = new FXVerticalFrame(this,FRAME_SUNKEN|LAYOUT_FILL_X|LAYOUT_FILL_Y|LAYOUT_TOP|LAYOUT_LEFT,0,0,0,0,10,10,10,10);

  new FXButton(contentFrame, "Do Split", nullptr, this, ID_DO_SPLIT, FRAME_THICK|FRAME_RAISED|LAYOUT_FILL_X|LAYOUT_TOP|LAYOUT_LEFT,0,0,0,0,10,10,5,5);

  FXVerticalFrame *resizeFrame = new FXVerticalFrame(contentFrame,FRAME_SUNKEN|LAYOUT_FILL_X|LAYOUT_FILL_Y|LAYOUT_TOP|LAYOUT_LEFT,0,0,0,0,10,10,10,10);

  splitter = new FXSplitter(resizeFrame, SPLITTER_VERTICAL | LAYOUT_FILL_X | LAYOUT_FILL_Y);
  FXVerticalFrame *queryTextFrame = new FXVerticalFrame(splitter, FRAME_SUNKEN | FRAME_THICK |
      LAYOUT_FILL_X | LAYOUT_FILL_Y, 0,0, 0, 0, 0,0,0,0);
  text = new FXText(queryTextFrame, nullptr, 0, LAYOUT_FILL_X | LAYOUT_FILL_Y);
}

DynResize::~DynResize()
{
}

void DynResize::create()
{
  FXMainWindow::create();

  show(PLACEMENT_SCREEN);
}

long DynResize::OnCommandDoSplit(FXObject*, FXSelector, void *)
{
  printf("You pressed 'Do Split'\n");

  if (text2 == nullptr) {
    printf("Building text2\n");
    text2 = new FXText(splitter, nullptr, 0, LAYOUT_FILL_X | LAYOUT_FILL_Y);

    text2->create();
    text2->show();

    splitter->layout();
    splitter->recalc();
    splitter->update();
  }
  return 1;
}

int main(int argc, char *argv[])
{
  FXApp app("dyn_resize", "dyn_resize");
  app.init(argc, argv);

  new DynResize(&app);

  app.create();
  app.run();

  return 0;
}
