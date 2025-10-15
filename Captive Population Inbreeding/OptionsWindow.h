	#pragma once	
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	class Coordinator;
	#include <vector>
	#include <string>

	using std::vector;
	using std::string;

	public ref class OptionsWindow : public System::Windows::Forms::Form {

	private:

		Coordinator* coordinator;

	public:

		OptionsWindow(Coordinator* assignedCoordinator)
		{
			coordinator = assignedCoordinator;

			InitializeComponent();
		}

		void clearOutputResult();
		void addOutputResult(vector<string> textLines);
		void addOutputResultLine(string textLine);

	protected:

		~OptionsWindow()
		{
			if (components)
			{
				delete components;
			}
		}

	private: 
		System::Windows::Forms::Button^ initialiseButton;
		System::Windows::Forms::Button^ cycleYearButton;
		System::Windows::Forms::RadioButton^ matingPatternRandomRadio;
		System::Windows::Forms::RadioButton^ matingPatternAlphaRadio;
		System::Windows::Forms::TextBox^ outputResult;
		System::Windows::Forms::RadioButton^ movementsRandomRadio;
		System::Windows::Forms::RadioButton^ movementsSelectiveRadio;
		System::Windows::Forms::GroupBox^ matingPatternRadioGroup;
		System::Windows::Forms::GroupBox^ movementsRadioGroup;
		System::Windows::Forms::Button^ outputButton;
		System::Windows::Forms::Button^ CycleCenturyButton;

	private:

		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code

		void InitializeComponent(void)
		{
			this->initialiseButton = (gcnew System::Windows::Forms::Button());
			this->cycleYearButton = (gcnew System::Windows::Forms::Button());
			this->matingPatternRandomRadio = (gcnew System::Windows::Forms::RadioButton());
			this->matingPatternAlphaRadio = (gcnew System::Windows::Forms::RadioButton());
			this->outputResult = (gcnew System::Windows::Forms::TextBox());
			this->movementsRandomRadio = (gcnew System::Windows::Forms::RadioButton());
			this->movementsSelectiveRadio = (gcnew System::Windows::Forms::RadioButton());
			this->matingPatternRadioGroup = (gcnew System::Windows::Forms::GroupBox());
			this->movementsRadioGroup = (gcnew System::Windows::Forms::GroupBox());
			this->outputButton = (gcnew System::Windows::Forms::Button());
			this->CycleCenturyButton = (gcnew System::Windows::Forms::Button());
			this->matingPatternRadioGroup->SuspendLayout();
			this->movementsRadioGroup->SuspendLayout();
			this->SuspendLayout();
			// 
			// initialiseButton
			// 
			this->initialiseButton->Location = System::Drawing::Point(1034, 37);
			this->initialiseButton->Name = L"initialiseButton";
			this->initialiseButton->Size = System::Drawing::Size(192, 53);
			this->initialiseButton->TabIndex = 0;
			this->initialiseButton->Text = L"Initialise";
			this->initialiseButton->UseVisualStyleBackColor = true;
			this->initialiseButton->Click += gcnew System::EventHandler(this, &OptionsWindow::initialiseButtonClick);
			// 
			// cycleYearButton
			// 
			this->cycleYearButton->Location = System::Drawing::Point(1034, 106);
			this->cycleYearButton->Name = L"cycleYearButton";
			this->cycleYearButton->Size = System::Drawing::Size(192, 53);
			this->cycleYearButton->TabIndex = 1;
			this->cycleYearButton->Text = L"Cycle Year";
			this->cycleYearButton->UseVisualStyleBackColor = true;
			this->cycleYearButton->Click += gcnew System::EventHandler(this, &OptionsWindow::cycleYearButton_Click);
			// 
			// matingPatternRandomRadio
			// 
			this->matingPatternRandomRadio->AutoSize = true;
			this->matingPatternRandomRadio->Checked = true;
			this->matingPatternRandomRadio->Location = System::Drawing::Point(16, 25);
			this->matingPatternRandomRadio->Name = L"matingPatternRandomRadio";
			this->matingPatternRandomRadio->Size = System::Drawing::Size(95, 24);
			this->matingPatternRandomRadio->TabIndex = 2;
			this->matingPatternRandomRadio->TabStop = true;
			this->matingPatternRandomRadio->Text = L"Random";
			this->matingPatternRandomRadio->UseVisualStyleBackColor = true;
			// 
			// matingPatternAlphaRadio
			// 
			this->matingPatternAlphaRadio->AutoSize = true;
			this->matingPatternAlphaRadio->Location = System::Drawing::Point(16, 55);
			this->matingPatternAlphaRadio->Name = L"matingPatternAlphaRadio";
			this->matingPatternAlphaRadio->Size = System::Drawing::Size(113, 24);
			this->matingPatternAlphaRadio->TabIndex = 3;
			this->matingPatternAlphaRadio->Text = L"Alpha Male";
			this->matingPatternAlphaRadio->UseVisualStyleBackColor = true;
			// 
			// outputResult
			// 
			this->outputResult->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left));
			this->outputResult->BackColor = System::Drawing::SystemColors::Window;
			this->outputResult->Location = System::Drawing::Point(30, 35);
			this->outputResult->Multiline = true;
			this->outputResult->Name = L"outputResult";
			this->outputResult->ReadOnly = true;
			this->outputResult->Size = System::Drawing::Size(981, 997);
			this->outputResult->TabIndex = 4;
			// 
			// movementsRandomRadio
			// 
			this->movementsRandomRadio->AutoSize = true;
			this->movementsRandomRadio->Checked = true;
			this->movementsRandomRadio->Location = System::Drawing::Point(16, 25);
			this->movementsRandomRadio->Name = L"movementsRandomRadio";
			this->movementsRandomRadio->Size = System::Drawing::Size(95, 24);
			this->movementsRandomRadio->TabIndex = 5;
			this->movementsRandomRadio->TabStop = true;
			this->movementsRandomRadio->Text = L"Random";
			this->movementsRandomRadio->UseVisualStyleBackColor = true;
			// 
			// movementsSelectiveRadio
			// 
			this->movementsSelectiveRadio->AutoSize = true;
			this->movementsSelectiveRadio->Location = System::Drawing::Point(16, 55);
			this->movementsSelectiveRadio->Name = L"movementsSelectiveRadio";
			this->movementsSelectiveRadio->Size = System::Drawing::Size(98, 24);
			this->movementsSelectiveRadio->TabIndex = 6;
			this->movementsSelectiveRadio->Text = L"Selective";
			this->movementsSelectiveRadio->UseVisualStyleBackColor = true;
			// 
			// matingPatternRadioGroup
			// 
			this->matingPatternRadioGroup->Controls->Add(this->matingPatternRandomRadio);
			this->matingPatternRadioGroup->Controls->Add(this->matingPatternAlphaRadio);
			this->matingPatternRadioGroup->Location = System::Drawing::Point(1034, 819);
			this->matingPatternRadioGroup->Name = L"matingPatternRadioGroup";
			this->matingPatternRadioGroup->Size = System::Drawing::Size(192, 94);
			this->matingPatternRadioGroup->TabIndex = 7;
			this->matingPatternRadioGroup->TabStop = false;
			this->matingPatternRadioGroup->Text = L"Mating Pattern";
			// 
			// movementsRadioGroup
			// 
			this->movementsRadioGroup->Controls->Add(this->movementsRandomRadio);
			this->movementsRadioGroup->Controls->Add(this->movementsSelectiveRadio);
			this->movementsRadioGroup->Location = System::Drawing::Point(1034, 938);
			this->movementsRadioGroup->Name = L"movementsRadioGroup";
			this->movementsRadioGroup->Size = System::Drawing::Size(192, 94);
			this->movementsRadioGroup->TabIndex = 8;
			this->movementsRadioGroup->TabStop = false;
			this->movementsRadioGroup->Text = L"Movements";
			// 
			// outputButton
			// 
			this->outputButton->Location = System::Drawing::Point(1034, 177);
			this->outputButton->Name = L"outputButton";
			this->outputButton->Size = System::Drawing::Size(192, 53);
			this->outputButton->TabIndex = 9;
			this->outputButton->Text = L"Output";
			this->outputButton->UseVisualStyleBackColor = true;
			this->outputButton->Click += gcnew System::EventHandler(this, &OptionsWindow::outputButton_Click);
			// 
			// CycleCenturyButton
			// 
			this->CycleCenturyButton->Location = System::Drawing::Point(1034, 251);
			this->CycleCenturyButton->Name = L"CycleCenturyButton";
			this->CycleCenturyButton->Size = System::Drawing::Size(192, 53);
			this->CycleCenturyButton->TabIndex = 10;
			this->CycleCenturyButton->Text = L"Cycle Century";
			this->CycleCenturyButton->UseVisualStyleBackColor = true;
			this->CycleCenturyButton->Click += gcnew System::EventHandler(this, &OptionsWindow::CycleCenturyButton_Click);
			// 
			// OptionsWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1249, 1068);
			this->Controls->Add(this->CycleCenturyButton);
			this->Controls->Add(this->outputButton);
			this->Controls->Add(this->movementsRadioGroup);
			this->Controls->Add(this->matingPatternRadioGroup);
			this->Controls->Add(this->outputResult);
			this->Controls->Add(this->cycleYearButton);
			this->Controls->Add(this->initialiseButton);
			this->Name = L"OptionsWindow";
			this->Text = L"Captive Population Inbreeding";
			this->matingPatternRadioGroup->ResumeLayout(false);
			this->matingPatternRadioGroup->PerformLayout();
			this->movementsRadioGroup->ResumeLayout(false);
			this->movementsRadioGroup->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: 
		System::Void initialiseButtonClick(System::Object^ sender, System::EventArgs^ e);
		System::Void cycleYearButton_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void CycleCenturyButton_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void outputButton_Click(System::Object^ sender, System::EventArgs^ e);
};
