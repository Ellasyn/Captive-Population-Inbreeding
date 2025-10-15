#include "pch.h"
#include "Coordinator.h"
#include "OptionsWindow.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
int main()
{	
	Coordinator* coordinator = new Coordinator();

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	OptionsWindow^ window = gcnew OptionsWindow(coordinator);
	coordinator->setOptionsWindow(window);

	Application::Run(window);  

	// During application exit:
	delete coordinator;

	return 0;
}