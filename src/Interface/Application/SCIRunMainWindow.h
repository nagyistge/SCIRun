/*
   For more information, please see: http://software.sci.utah.edu

   The MIT License

   Copyright (c) 2012 Scientific Computing and Imaging Institute,
   University of Utah.

   License for the specific language governing rights and limitations under
   Permission is hereby granted, free of charge, to any person obtaining a
   copy of this software and associated documentation files (the "Software"),
   to deal in the Software without restriction, including without limitation
   the rights to use, copy, modify, merge, publish, distribute, sublicense,
   and/or sell copies of the Software, and to permit persons to whom the
   Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included
   in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
   THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
   FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
   DEALINGS IN THE SOFTWARE.
*/

#ifndef INTERFACE_APPLICATION_SCIRUN_MAIN_WINDOW_H
#define INTERFACE_APPLICATION_SCIRUN_MAIN_WINDOW_H

#include <QDialog>
#include <QDir>
#include <boost/shared_ptr.hpp>
#include "ui_SCIRunMainWindow.h"

namespace SCIRun {
  namespace Dataflow {
    namespace Engine {
      class NetworkEditorController;
    }}}

namespace SCIRun {
namespace Gui {

class NetworkEditor;
class HistoryWindow;

class SCIRunMainWindow : public QMainWindow, public Ui::SCIRunMainWindow
{
	Q_OBJECT
public:
	static SCIRunMainWindow* Instance();
  void setController(boost::shared_ptr<SCIRun::Dataflow::Engine::NetworkEditorController> controller);
  void initialize();
protected:
  virtual void closeEvent(QCloseEvent* event);
private:
  static SCIRunMainWindow* instance_;
  SCIRunMainWindow();
  NetworkEditor* networkEditor_;
  HistoryWindow* historyWindow_;
  QActionGroup* filterActionGroup_;
  QAction* actionEnterWhatsThisMode_;
  
private:
  bool okToContinue();
  void saveNetworkFile(const QString& fileName);
  void loadNetworkFile(const QString& filename);
  void setCurrentFile(const QString& fileName);
  void updateRecentFileActions();
  QString strippedName(const QString& fillFileName);
  void setActionIcons();
  void makeFilterButtonMenu();
  void writeSettings();
  void readSettings();
  void setupHistoryWindow();
  enum { MaxRecentFiles = 5 }; //TODO: could be a user setting
  std::vector<QAction*> recentFileActions_;
  QStringList recentFiles_;
  QString currentFile_;
  QDir latestNetworkDirectory_;
  boost::shared_ptr<class NetworkExecutionProgressBar> networkProgressBar_;
  boost::shared_ptr<class GuiActionCommandHistoryConverter> commandConverter_;
  //boost::shared_ptr<SCIRun::Dataflow::Engine::NetworkEditorController> controller_;
  bool regressionMode_;
  QString regressionTestDataDir_;
private Q_SLOTS:
  void saveNetworkAs();
  void saveNetwork();
  void loadNetwork();
  void loadRecentNetwork();
  bool clearNetwork();
  void networkModified();
  void filterModuleNamesInTreeView(const QString& start);
  void makePipesEuclidean();
  void makePipesCubicBezier();
  void makePipesManhattan();
  void disableInputWidgets(); 
  void enableInputWidgets();
  void setRegressionTestDataDir();
  void updateRegressionTestDataDir();
  void chooseBackgroundColor();
  void resetBackgroundColor();
  void exitApplication(int code);
};

}
}
#endif
