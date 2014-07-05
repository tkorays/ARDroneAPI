#include "XWindow.h"
#include "XConfig.h"
#include <wx/xrc/xmlres.h>

XWindow::XWindow() {
	
	wxXmlResource::Get()->LoadFrame(this, NULL, wxT("esdc_mainwin"));
}
XWindow::~XWindow() {

}