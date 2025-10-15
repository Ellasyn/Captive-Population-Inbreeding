#include "pch.h"
#include "OptionsWindow.h"
#include "Coordinator.h"
#include "MathsUtils.h"

void OptionsWindow::clearOutputResult() {
	outputResult->Clear();
}

void OptionsWindow::addOutputResultLine(string textLine) {

	outputResult->AppendText(gcnew System::String(textLine.c_str()));
	outputResult->AppendText("\r\n");
}

void OptionsWindow::addOutputResult(vector<string> textLines) {

	if (!textLines.empty()) {
		for (string line : textLines) {
			addOutputResultLine(line);
		}
	}	
}

System::Void OptionsWindow::initialiseButtonClick(System::Object^ sender, System::EventArgs^ e) {
	int startYear = 2000;
	int numZoos = 10;
	int zooCapcity = 20;
	int numLoci = 100;

	bool selectiveMovement = movementsSelectiveRadio->Checked;
	bool alphaMaleMating = matingPatternAlphaRadio->Checked;
	
	coordinator->initialisePopulation(startYear, numZoos, zooCapcity, numLoci, selectiveMovement, alphaMaleMating);
}

System::Void OptionsWindow::cycleYearButton_Click(System::Object^ sender, System::EventArgs^ e) {
	coordinator->cycleYear(1);
}

System::Void OptionsWindow::CycleCenturyButton_Click(System::Object^ sender, System::EventArgs^ e) {
	coordinator->cycleYear(100);
}

System::Void OptionsWindow::outputButton_Click(System::Object^ sender, System::EventArgs^ e) {
	// Todo add text file outputs
}