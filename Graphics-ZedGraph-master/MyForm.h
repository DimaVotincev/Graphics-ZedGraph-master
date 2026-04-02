#pragma once
#include <math.h>
#include <vector>
namespace Graph {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace ZedGraph;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: ZedGraph::ZedGraphControl^ zedGraphControl1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::DataGridView^ dataGridView1;



	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::TextBox^ textBox2;

	private: System::Windows::Forms::TextBox^ textBox3;





	private: System::Windows::Forms::TextBox^ textBox6;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Button^ ZoomButton;






	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::TextBox^ textBox7;
	private: System::Windows::Forms::TextBox^ textBox8;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::TextBox^ textBox9;
	private: System::Windows::Forms::Label^ label9;

	private: System::Windows::Forms::Label^ label10;
	private: System::Windows::Forms::ToolTip^ toolTip1;


	private: System::Windows::Forms::CheckBox^ checkBox1;































	private: ZedGraph::ZedGraphControl^ zedGraphControl2;
	private: ZedGraph::ZedGraphControl^ zedGraphControl3;
	private: ZedGraph::ZedGraphControl^ zedGraphControl4;
	private: System::Windows::Forms::DataGridView^ dataGridView2;












	private: System::Windows::Forms::TextBox^ textBox10;
	private: System::Windows::Forms::Label^ label11;
	private: System::Windows::Forms::TextBox^ textBox11;
	private: System::Windows::Forms::Label^ label12;
	private: System::Windows::Forms::TextBox^ textBox12;
	private: System::Windows::Forms::Label^ label13;
	private: System::Windows::Forms::TextBox^ textBox13;
	private: System::Windows::Forms::Label^ label14;
	private: System::Windows::Forms::TextBox^ textBox14;
	private: System::Windows::Forms::Label^ label15;
	private: System::Windows::Forms::Label^ labelTestInfo;
	private: System::Windows::Forms::Label^ labelMainInfo;










	private: System::Windows::Forms::TextBox^ textBox15;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label16;
	private: System::Windows::Forms::Label^ label17;
	private: System::Windows::Forms::Label^ label18;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ X;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ F_2;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column2;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column3;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column4;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column5;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column6;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column7;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ F_1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column8;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column9;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ dataGridViewTextBoxColumn1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ dataGridViewTextBoxColumn2;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ dataGridViewTextBoxColumn3;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ dataGridViewTextBoxColumn4;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ dataGridViewTextBoxColumn5;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ dataGridViewTextBoxColumn6;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ dataGridViewTextBoxColumn7;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ dataGridViewTextBoxColumn8;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ dataGridViewTextBoxColumn9;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ dataGridViewTextBoxColumn12;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label19;

	private: System::Windows::Forms::Label^ label20;
	private: System::Windows::Forms::Label^ label21;
	private: System::Windows::Forms::Label^ label22;

	private: System::Windows::Forms::Label^ label24;
	private: System::Windows::Forms::Label^ label23;
	private: System::Windows::Forms::Label^ label25;
	private: System::Windows::Forms::Label^ label26;
	private: System::Windows::Forms::Label^ label27;
	private: System::Windows::Forms::Label^ label28;
	private: System::Windows::Forms::Label^ label29;
	private: System::Windows::Forms::Label^ label30;
	private: System::Windows::Forms::Label^ label31;
	private: System::Windows::Forms::Label^ label32;
	private: System::Windows::Forms::Label^ label33;
	private: System::Windows::Forms::Label^ label34;
	private: System::Windows::Forms::Label^ label35;












	protected:
	private: System::ComponentModel::IContainer^ components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->zedGraphControl1 = (gcnew ZedGraph::ZedGraphControl());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->Column1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->X = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->F_2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column3 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column4 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column5 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column6 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column7 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->F_1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column8 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column9 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->ZoomButton = (gcnew System::Windows::Forms::Button());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->textBox7 = (gcnew System::Windows::Forms::TextBox());
			this->textBox8 = (gcnew System::Windows::Forms::TextBox());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->textBox9 = (gcnew System::Windows::Forms::TextBox());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->toolTip1 = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->zedGraphControl2 = (gcnew ZedGraph::ZedGraphControl());
			this->zedGraphControl3 = (gcnew ZedGraph::ZedGraphControl());
			this->zedGraphControl4 = (gcnew ZedGraph::ZedGraphControl());
			this->dataGridView2 = (gcnew System::Windows::Forms::DataGridView());
			this->dataGridViewTextBoxColumn1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn3 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn4 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn5 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn6 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn7 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn8 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn9 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn12 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->textBox10 = (gcnew System::Windows::Forms::TextBox());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->textBox11 = (gcnew System::Windows::Forms::TextBox());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->textBox12 = (gcnew System::Windows::Forms::TextBox());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->textBox13 = (gcnew System::Windows::Forms::TextBox());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->textBox14 = (gcnew System::Windows::Forms::TextBox());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->labelTestInfo = (gcnew System::Windows::Forms::Label());
			this->labelMainInfo = (gcnew System::Windows::Forms::Label());
			this->textBox15 = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->label22 = (gcnew System::Windows::Forms::Label());
			this->label23 = (gcnew System::Windows::Forms::Label());
			this->label24 = (gcnew System::Windows::Forms::Label());
			this->label25 = (gcnew System::Windows::Forms::Label());
			this->label26 = (gcnew System::Windows::Forms::Label());
			this->label27 = (gcnew System::Windows::Forms::Label());
			this->label28 = (gcnew System::Windows::Forms::Label());
			this->label29 = (gcnew System::Windows::Forms::Label());
			this->label30 = (gcnew System::Windows::Forms::Label());
			this->label31 = (gcnew System::Windows::Forms::Label());
			this->label32 = (gcnew System::Windows::Forms::Label());
			this->label33 = (gcnew System::Windows::Forms::Label());
			this->label34 = (gcnew System::Windows::Forms::Label());
			this->label35 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView2))->BeginInit();
			this->SuspendLayout();
			// 
			// zedGraphControl1
			// 
			this->zedGraphControl1->Location = System::Drawing::Point(1120, 456);
			this->zedGraphControl1->Margin = System::Windows::Forms::Padding(5);
			this->zedGraphControl1->Name = L"zedGraphControl1";
			this->zedGraphControl1->ScrollGrace = 0;
			this->zedGraphControl1->ScrollMaxX = 0;
			this->zedGraphControl1->ScrollMaxY = 0;
			this->zedGraphControl1->ScrollMaxY2 = 0;
			this->zedGraphControl1->ScrollMinX = 0;
			this->zedGraphControl1->ScrollMinY = 0;
			this->zedGraphControl1->ScrollMinY2 = 0;
			this->zedGraphControl1->Size = System::Drawing::Size(668, 402);
			this->zedGraphControl1->TabIndex = 0;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(843, 405);
			this->button1->Margin = System::Windows::Forms::Padding(4);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(189, 36);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Draw";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// dataGridView1
			// 
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(12) {
				this->Column1,
					this->X, this->F_2, this->Column2, this->Column3, this->Column4, this->Column5, this->Column6, this->Column7, this->F_1, this->Column8,
					this->Column9
			});
			this->dataGridView1->Location = System::Drawing::Point(13, 888);
			this->dataGridView1->Margin = System::Windows::Forms::Padding(4);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->RowHeadersVisible = false;
			this->dataGridView1->RowHeadersWidth = 51;
			this->dataGridView1->Size = System::Drawing::Size(997, 427);
			this->dataGridView1->TabIndex = 2;
			// 
			// Column1
			// 
			this->Column1->HeaderText = L"i";
			this->Column1->MinimumWidth = 6;
			this->Column1->Name = L"Column1";
			this->Column1->Width = 60;
			// 
			// X
			// 
			this->X->HeaderText = L"x_i";
			this->X->MinimumWidth = 6;
			this->X->Name = L"X";
			this->X->ReadOnly = true;
			this->X->Width = 50;
			// 
			// F_2
			// 
			this->F_2->HeaderText = L"V_i";
			this->F_2->MinimumWidth = 6;
			this->F_2->Name = L"F_2";
			this->F_2->ReadOnly = true;
			this->F_2->Width = 125;
			// 
			// Column2
			// 
			this->Column2->HeaderText = L"V_2i";
			this->Column2->MinimumWidth = 6;
			this->Column2->Name = L"Column2";
			this->Column2->Width = 125;
			// 
			// Column3
			// 
			this->Column3->HeaderText = L"v_i-v_2i";
			this->Column3->MinimumWidth = 6;
			this->Column3->Name = L"Column3";
			this->Column3->Width = 125;
			// 
			// Column4
			// 
			this->Column4->HeaderText = L"ОЛП";
			this->Column4->MinimumWidth = 6;
			this->Column4->Name = L"Column4";
			this->Column4->Width = 125;
			// 
			// Column5
			// 
			this->Column5->HeaderText = L"h_i";
			this->Column5->MinimumWidth = 6;
			this->Column5->Name = L"Column5";
			this->Column5->Width = 125;
			// 
			// Column6
			// 
			this->Column6->HeaderText = L"C1";
			this->Column6->MinimumWidth = 6;
			this->Column6->Name = L"Column6";
			this->Column6->Width = 125;
			// 
			// Column7
			// 
			this->Column7->HeaderText = L"C2";
			this->Column7->MinimumWidth = 6;
			this->Column7->Name = L"Column7";
			this->Column7->Width = 125;
			// 
			// F_1
			// 
			this->F_1->HeaderText = L"u_i";
			this->F_1->MinimumWidth = 6;
			this->F_1->Name = L"F_1";
			this->F_1->ReadOnly = true;
			this->F_1->Width = 125;
			// 
			// Column8
			// 
			this->Column8->HeaderText = L"|u_i - v_i |";
			this->Column8->MinimumWidth = 6;
			this->Column8->Name = L"Column8";
			this->Column8->Width = 125;
			// 
			// Column9
			// 
			this->Column9->HeaderText = L"--";
			this->Column9->MinimumWidth = 6;
			this->Column9->Name = L"Column9";
			this->Column9->Width = 125;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(840, 457);
			this->label1->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(15, 16);
			this->label1->TabIndex = 3;
			this->label1->Text = L"a";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(854, 457);
			this->textBox1->Margin = System::Windows::Forms::Padding(4);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(63, 22);
			this->textBox1->TabIndex = 4;
			this->textBox1->Text = L"0";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(949, 460);
			this->label2->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(15, 16);
			this->label2->TabIndex = 5;
			this->label2->Text = L"b";
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(963, 457);
			this->textBox2->Margin = System::Windows::Forms::Padding(4);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(64, 22);
			this->textBox2->TabIndex = 6;
			this->textBox2->Text = L"1";
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(910, 685);
			this->textBox3->Margin = System::Windows::Forms::Padding(4);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(100, 22);
			this->textBox3->TabIndex = 8;
			this->textBox3->Text = L"0,0001";
			// 
			// textBox6
			// 
			this->textBox6->Location = System::Drawing::Point(66, 600);
			this->textBox6->Margin = System::Windows::Forms::Padding(4);
			this->textBox6->Name = L"textBox6";
			this->textBox6->Size = System::Drawing::Size(80, 22);
			this->textBox6->TabIndex = 15;
			this->textBox6->Text = L"1";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label6->Location = System::Drawing::Point(22, 593);
			this->label6->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(36, 29);
			this->label6->TabIndex = 14;
			this->label6->Text = L"u₀";
			// 
			// ZoomButton
			// 
			this->ZoomButton->Location = System::Drawing::Point(843, 496);
			this->ZoomButton->Margin = System::Windows::Forms::Padding(4);
			this->ZoomButton->Name = L"ZoomButton";
			this->ZoomButton->Size = System::Drawing::Size(189, 36);
			this->ZoomButton->TabIndex = 9;
			this->ZoomButton->Text = L"Zoom";
			this->ZoomButton->UseVisualStyleBackColor = true;
			this->ZoomButton->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// label7
			// 
			this->label7->AccessibleName = L"";
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label7->Location = System::Drawing::Point(619, 601);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(285, 16);
			this->label7->TabIndex = 16;
			this->label7->Text = L"Параметр выхода за правую границу";
			// 
			// textBox7
			// 
			this->textBox7->Location = System::Drawing::Point(910, 601);
			this->textBox7->Name = L"textBox7";
			this->textBox7->Size = System::Drawing::Size(100, 22);
			this->textBox7->TabIndex = 17;
			this->textBox7->Text = L"0,0001";
			// 
			// textBox8
			// 
			this->textBox8->Location = System::Drawing::Point(910, 628);
			this->textBox8->Name = L"textBox8";
			this->textBox8->Size = System::Drawing::Size(100, 22);
			this->textBox8->TabIndex = 19;
			this->textBox8->Text = L"1000";
			// 
			// label8
			// 
			this->label8->AccessibleName = L"";
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label8->Location = System::Drawing::Point(691, 628);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(212, 16);
			this->label8->TabIndex = 18;
			this->label8->Text = L"Максимальное число шагов";
			// 
			// textBox9
			// 
			this->textBox9->Location = System::Drawing::Point(910, 656);
			this->textBox9->Name = L"textBox9";
			this->textBox9->Size = System::Drawing::Size(100, 22);
			this->textBox9->TabIndex = 21;
			this->textBox9->Text = L"0,0001";
			// 
			// label9
			// 
			this->label9->AccessibleName = L"";
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label9->Location = System::Drawing::Point(566, 656);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(337, 16);
			this->label9->TabIndex = 20;
			this->label9->Text = L"Параметр контроля локальной погрешности";
			// 
			// label10
			// 
			this->label10->AccessibleName = L"";
			this->label10->AutoSize = true;
			this->label10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label10->Location = System::Drawing::Point(747, 685);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(146, 16);
			this->label10->TabIndex = 22;
			this->label10->Text = L"Начальный шаг (x₀)";
			// 
			// toolTip1
			// 
			this->toolTip1->ShowAlways = true;
			this->toolTip1->ToolTipIcon = System::Windows::Forms::ToolTipIcon::Info;
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Location = System::Drawing::Point(1017, 660);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(100, 20);
			this->checkBox1->TabIndex = 23;
			this->checkBox1->Text = L"Учитывать";
			this->checkBox1->UseVisualStyleBackColor = true;
			// 
			// zedGraphControl2
			// 
			this->zedGraphControl2->Location = System::Drawing::Point(1120, 30);
			this->zedGraphControl2->Margin = System::Windows::Forms::Padding(5);
			this->zedGraphControl2->Name = L"zedGraphControl2";
			this->zedGraphControl2->ScrollGrace = 0;
			this->zedGraphControl2->ScrollMaxX = 0;
			this->zedGraphControl2->ScrollMaxY = 0;
			this->zedGraphControl2->ScrollMaxY2 = 0;
			this->zedGraphControl2->ScrollMinX = 0;
			this->zedGraphControl2->ScrollMinY = 0;
			this->zedGraphControl2->ScrollMinY2 = 0;
			this->zedGraphControl2->Size = System::Drawing::Size(668, 402);
			this->zedGraphControl2->TabIndex = 32;
			// 
			// zedGraphControl3
			// 
			this->zedGraphControl3->Location = System::Drawing::Point(1817, 30);
			this->zedGraphControl3->Margin = System::Windows::Forms::Padding(5);
			this->zedGraphControl3->Name = L"zedGraphControl3";
			this->zedGraphControl3->ScrollGrace = 0;
			this->zedGraphControl3->ScrollMaxX = 0;
			this->zedGraphControl3->ScrollMaxY = 0;
			this->zedGraphControl3->ScrollMaxY2 = 0;
			this->zedGraphControl3->ScrollMinX = 0;
			this->zedGraphControl3->ScrollMinY = 0;
			this->zedGraphControl3->ScrollMinY2 = 0;
			this->zedGraphControl3->Size = System::Drawing::Size(668, 402);
			this->zedGraphControl3->TabIndex = 33;
			// 
			// zedGraphControl4
			// 
			this->zedGraphControl4->Location = System::Drawing::Point(1817, 442);
			this->zedGraphControl4->Margin = System::Windows::Forms::Padding(5);
			this->zedGraphControl4->Name = L"zedGraphControl4";
			this->zedGraphControl4->ScrollGrace = 0;
			this->zedGraphControl4->ScrollMaxX = 0;
			this->zedGraphControl4->ScrollMaxY = 0;
			this->zedGraphControl4->ScrollMaxY2 = 0;
			this->zedGraphControl4->ScrollMinX = 0;
			this->zedGraphControl4->ScrollMinY = 0;
			this->zedGraphControl4->ScrollMinY2 = 0;
			this->zedGraphControl4->Size = System::Drawing::Size(668, 402);
			this->zedGraphControl4->TabIndex = 34;
			// 
			// dataGridView2
			// 
			this->dataGridView2->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView2->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(10) {
				this->dataGridViewTextBoxColumn1,
					this->dataGridViewTextBoxColumn2, this->dataGridViewTextBoxColumn3, this->dataGridViewTextBoxColumn4, this->dataGridViewTextBoxColumn5,
					this->dataGridViewTextBoxColumn6, this->dataGridViewTextBoxColumn7, this->dataGridViewTextBoxColumn8, this->dataGridViewTextBoxColumn9,
					this->dataGridViewTextBoxColumn12
			});
			this->dataGridView2->Location = System::Drawing::Point(1489, 888);
			this->dataGridView2->Margin = System::Windows::Forms::Padding(4);
			this->dataGridView2->Name = L"dataGridView2";
			this->dataGridView2->RowHeadersVisible = false;
			this->dataGridView2->RowHeadersWidth = 51;
			this->dataGridView2->Size = System::Drawing::Size(996, 427);
			this->dataGridView2->TabIndex = 35;
			// 
			// dataGridViewTextBoxColumn1
			// 
			this->dataGridViewTextBoxColumn1->HeaderText = L"i";
			this->dataGridViewTextBoxColumn1->MinimumWidth = 6;
			this->dataGridViewTextBoxColumn1->Name = L"dataGridViewTextBoxColumn1";
			this->dataGridViewTextBoxColumn1->Width = 60;
			// 
			// dataGridViewTextBoxColumn2
			// 
			this->dataGridViewTextBoxColumn2->HeaderText = L"x_i";
			this->dataGridViewTextBoxColumn2->MinimumWidth = 6;
			this->dataGridViewTextBoxColumn2->Name = L"dataGridViewTextBoxColumn2";
			this->dataGridViewTextBoxColumn2->ReadOnly = true;
			this->dataGridViewTextBoxColumn2->Width = 50;
			// 
			// dataGridViewTextBoxColumn3
			// 
			this->dataGridViewTextBoxColumn3->HeaderText = L"V_i";
			this->dataGridViewTextBoxColumn3->MinimumWidth = 6;
			this->dataGridViewTextBoxColumn3->Name = L"dataGridViewTextBoxColumn3";
			this->dataGridViewTextBoxColumn3->ReadOnly = true;
			this->dataGridViewTextBoxColumn3->Width = 125;
			// 
			// dataGridViewTextBoxColumn4
			// 
			this->dataGridViewTextBoxColumn4->HeaderText = L"V_2i";
			this->dataGridViewTextBoxColumn4->MinimumWidth = 6;
			this->dataGridViewTextBoxColumn4->Name = L"dataGridViewTextBoxColumn4";
			this->dataGridViewTextBoxColumn4->Width = 125;
			// 
			// dataGridViewTextBoxColumn5
			// 
			this->dataGridViewTextBoxColumn5->HeaderText = L"v_i-v_2i";
			this->dataGridViewTextBoxColumn5->MinimumWidth = 6;
			this->dataGridViewTextBoxColumn5->Name = L"dataGridViewTextBoxColumn5";
			this->dataGridViewTextBoxColumn5->Width = 125;
			// 
			// dataGridViewTextBoxColumn6
			// 
			this->dataGridViewTextBoxColumn6->HeaderText = L"ОЛП";
			this->dataGridViewTextBoxColumn6->MinimumWidth = 6;
			this->dataGridViewTextBoxColumn6->Name = L"dataGridViewTextBoxColumn6";
			this->dataGridViewTextBoxColumn6->Width = 125;
			// 
			// dataGridViewTextBoxColumn7
			// 
			this->dataGridViewTextBoxColumn7->HeaderText = L"h_i";
			this->dataGridViewTextBoxColumn7->MinimumWidth = 6;
			this->dataGridViewTextBoxColumn7->Name = L"dataGridViewTextBoxColumn7";
			this->dataGridViewTextBoxColumn7->Width = 125;
			// 
			// dataGridViewTextBoxColumn8
			// 
			this->dataGridViewTextBoxColumn8->HeaderText = L"C1";
			this->dataGridViewTextBoxColumn8->MinimumWidth = 6;
			this->dataGridViewTextBoxColumn8->Name = L"dataGridViewTextBoxColumn8";
			this->dataGridViewTextBoxColumn8->Width = 125;
			// 
			// dataGridViewTextBoxColumn9
			// 
			this->dataGridViewTextBoxColumn9->HeaderText = L"C2";
			this->dataGridViewTextBoxColumn9->MinimumWidth = 6;
			this->dataGridViewTextBoxColumn9->Name = L"dataGridViewTextBoxColumn9";
			this->dataGridViewTextBoxColumn9->Width = 125;
			// 
			// dataGridViewTextBoxColumn12
			// 
			this->dataGridViewTextBoxColumn12->HeaderText = L"--";
			this->dataGridViewTextBoxColumn12->MinimumWidth = 6;
			this->dataGridViewTextBoxColumn12->Name = L"dataGridViewTextBoxColumn12";
			this->dataGridViewTextBoxColumn12->Width = 125;
			// 
			// textBox10
			// 
			this->textBox10->Location = System::Drawing::Point(445, 591);
			this->textBox10->Name = L"textBox10";
			this->textBox10->Size = System::Drawing::Size(100, 22);
			this->textBox10->TabIndex = 37;
			this->textBox10->Text = L"1";
			// 
			// label11
			// 
			this->label11->AccessibleName = L"";
			this->label11->AutoSize = true;
			this->label11->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label11->Location = System::Drawing::Point(410, 591);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(19, 16);
			this->label11->TabIndex = 36;
			this->label11->Text = L"m";
			// 
			// textBox11
			// 
			this->textBox11->Location = System::Drawing::Point(445, 618);
			this->textBox11->Name = L"textBox11";
			this->textBox11->Size = System::Drawing::Size(100, 22);
			this->textBox11->TabIndex = 39;
			this->textBox11->Text = L"0,15";
			// 
			// label12
			// 
			this->label12->AccessibleName = L"";
			this->label12->AutoSize = true;
			this->label12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label12->Location = System::Drawing::Point(410, 618);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(15, 16);
			this->label12->TabIndex = 38;
			this->label12->Text = L"c";
			// 
			// textBox12
			// 
			this->textBox12->Location = System::Drawing::Point(445, 646);
			this->textBox12->Name = L"textBox12";
			this->textBox12->Size = System::Drawing::Size(100, 22);
			this->textBox12->TabIndex = 41;
			this->textBox12->Text = L"2";
			// 
			// label13
			// 
			this->label13->AccessibleName = L"";
			this->label13->AutoSize = true;
			this->label13->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label13->Location = System::Drawing::Point(410, 646);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(15, 16);
			this->label13->TabIndex = 40;
			this->label13->Text = L"k";
			// 
			// textBox13
			// 
			this->textBox13->Location = System::Drawing::Point(445, 676);
			this->textBox13->Name = L"textBox13";
			this->textBox13->Size = System::Drawing::Size(100, 22);
			this->textBox13->TabIndex = 43;
			this->textBox13->Text = L"2";
			// 
			// label14
			// 
			this->label14->AccessibleName = L"";
			this->label14->AutoSize = true;
			this->label14->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label14->Location = System::Drawing::Point(410, 676);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(21, 16);
			this->label14->TabIndex = 42;
			this->label14->Text = L"k*";
			// 
			// textBox14
			// 
			this->textBox14->Location = System::Drawing::Point(305, 643);
			this->textBox14->Margin = System::Windows::Forms::Padding(4);
			this->textBox14->Name = L"textBox14";
			this->textBox14->Size = System::Drawing::Size(80, 22);
			this->textBox14->TabIndex = 45;
			this->textBox14->Text = L"0";
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label15->Location = System::Drawing::Point(261, 639);
			this->label15->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(41, 29);
			this->label15->TabIndex = 44;
			this->label15->Text = L"u₀\'";
			// 
			// labelTestInfo
			// 
			this->labelTestInfo->AutoSize = true;
			this->labelTestInfo->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->labelTestInfo->Location = System::Drawing::Point(1017, 924);
			this->labelTestInfo->Name = L"labelTestInfo";
			this->labelTestInfo->Size = System::Drawing::Size(227, 16);
			this->labelTestInfo->TabIndex = 46;
			this->labelTestInfo->Text = L"Справка по тестовой задаче:";
			// 
			// labelMainInfo
			// 
			this->labelMainInfo->AutoSize = true;
			this->labelMainInfo->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->labelMainInfo->Location = System::Drawing::Point(1250, 924);
			this->labelMainInfo->Name = L"labelMainInfo";
			this->labelMainInfo->Size = System::Drawing::Size(229, 16);
			this->labelMainInfo->TabIndex = 47;
			this->labelMainInfo->Text = L"Справка по основной задаче:";
			// 
			// textBox15
			// 
			this->textBox15->Location = System::Drawing::Point(305, 612);
			this->textBox15->Margin = System::Windows::Forms::Padding(4);
			this->textBox15->Name = L"textBox15";
			this->textBox15->Size = System::Drawing::Size(80, 22);
			this->textBox15->TabIndex = 49;
			this->textBox15->Text = L"10";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label3->Location = System::Drawing::Point(261, 611);
			this->label3->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(32, 25);
			this->label3->TabIndex = 48;
			this->label3->Text = L"u₀";
			// 
			// label16
			// 
			this->label16->AccessibleName = L"";
			this->label16->AutoSize = true;
			this->label16->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label16->Location = System::Drawing::Point(293, 559);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(224, 16);
			this->label16->TabIndex = 50;
			this->label16->Text = L"Параметры основной задачи";
			// 
			// label17
			// 
			this->label17->AccessibleName = L"";
			this->label17->AutoSize = true;
			this->label17->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label17->Location = System::Drawing::Point(10, 559);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(222, 16);
			this->label17->TabIndex = 51;
			this->label17->Text = L"Параметры тестовой задачи";
			// 
			// label18
			// 
			this->label18->AccessibleName = L"";
			this->label18->AutoSize = true;
			this->label18->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label18->Location = System::Drawing::Point(683, 457);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(171, 16);
			this->label18->TabIndex = 52;
			this->label18->Text = L"Границы отрезка [a,b]";
			// 
			// label4
			// 
			this->label4->AccessibleName = L"";
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label4->Location = System::Drawing::Point(61, 1338);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(694, 18);
			this->label4->TabIndex = 53;
			this->label4->Text = L"!! Если ОЛП == 0, значит разница v_i - v_2i  слишком маленькая для точности doubl"
				L"e !!";
			// 
			// label5
			// 
			this->label5->AccessibleName = L"";
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label5->Location = System::Drawing::Point(1556, 1338);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(929, 18);
			this->label5->TabIndex = 54;
			this->label5->Text = L"!! Если ОЛП > Параметр_контроля_лок_погршности , то это ограничение типа double ("
				L"неустранимая погрешность) !!";
			// 
			// label19
			// 
			this->label19->AccessibleName = L"";
			this->label19->AutoSize = true;
			this->label19->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label19->Location = System::Drawing::Point(871, 1338);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(581, 18);
			this->label19->TabIndex = 55;
			this->label19->Text = L"!! Если max|u-v| достигается при x == b, то не хватило точности double !!";
			// 
			// label20
			// 
			this->label20->AccessibleName = L"";
			this->label20->AutoSize = true;
			this->label20->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->label20->Location = System::Drawing::Point(1123, 865);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(209, 38);
			this->label20->TabIndex = 57;
			this->label20->Text = L"Результаты";
			// 
			// label21
			// 
			this->label21->AccessibleName = L"";
			this->label21->AutoSize = true;
			this->label21->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label21->Location = System::Drawing::Point(9, 340);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(183, 25);
			this->label21->TabIndex = 58;
			this->label21->Text = L"Тестовая задача";
			// 
			// label22
			// 
			this->label22->AccessibleName = L"";
			this->label22->AutoSize = true;
			this->label22->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label22->Location = System::Drawing::Point(57, 408);
			this->label22->Name = L"label22";
			this->label22->Size = System::Drawing::Size(57, 20);
			this->label22->TabIndex = 59;
			this->label22->Text = L"u\' = u";
			this->label22->Click += gcnew System::EventHandler(this, &MyForm::label22_Click);
			// 
			// label23
			// 
			this->label23->AccessibleName = L"";
			this->label23->AutoSize = true;
			this->label23->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label23->Location = System::Drawing::Point(57, 439);
			this->label23->Name = L"label23";
			this->label23->Size = System::Drawing::Size(89, 20);
			this->label23->TabIndex = 60;
			this->label23->Text = L"u(x₀) = u₀";
			this->label23->Click += gcnew System::EventHandler(this, &MyForm::label23_Click);
			// 
			// label24
			// 
			this->label24->AccessibleName = L"";
			this->label24->BackColor = System::Drawing::Color::Transparent;
			this->label24->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 48, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label24->Location = System::Drawing::Point(10, 381);
			this->label24->Name = L"label24";
			this->label24->Size = System::Drawing::Size(49, 95);
			this->label24->TabIndex = 61;
			this->label24->Text = L"{";
			this->label24->Click += gcnew System::EventHandler(this, &MyForm::label24_Click);
			// 
			// label25
			// 
			this->label25->AccessibleName = L"";
			this->label25->AutoSize = true;
			this->label25->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label25->Location = System::Drawing::Point(323, 381);
			this->label25->Name = L"label25";
			this->label25->Size = System::Drawing::Size(89, 20);
			this->label25->TabIndex = 64;
			this->label25->Text = L"u(x₀) = u₀";
			// 
			// label26
			// 
			this->label26->AccessibleName = L"";
			this->label26->BackColor = System::Drawing::Color::Transparent;
			this->label26->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 48, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label26->Location = System::Drawing::Point(277, 338);
			this->label26->Name = L"label26";
			this->label26->Size = System::Drawing::Size(49, 95);
			this->label26->TabIndex = 65;
			this->label26->Text = L"{";
			// 
			// label27
			// 
			this->label27->AccessibleName = L"";
			this->label27->AutoSize = true;
			this->label27->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label27->Location = System::Drawing::Point(323, 361);
			this->label27->Name = L"label27";
			this->label27->Size = System::Drawing::Size(207, 20);
			this->label27->TabIndex = 63;
			this->label27->Text = L"m·u\'\'+c·u\'+k·u+k*·u³ = 0";
			// 
			// label28
			// 
			this->label28->AccessibleName = L"";
			this->label28->AutoSize = true;
			this->label28->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label28->Location = System::Drawing::Point(360, 9);
			this->label28->Name = L"label28";
			this->label28->Size = System::Drawing::Size(185, 25);
			this->label28->TabIndex = 62;
			this->label28->Text = L"Основная задача";
			// 
			// label29
			// 
			this->label29->AccessibleName = L"";
			this->label29->AutoSize = true;
			this->label29->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label29->Location = System::Drawing::Point(323, 404);
			this->label29->Name = L"label29";
			this->label29->Size = System::Drawing::Size(99, 20);
			this->label29->TabIndex = 66;
			this->label29->Text = L"u\'(x₀) = u₀\'";
			// 
			// label30
			// 
			this->label30->AccessibleName = L"";
			this->label30->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label30->Location = System::Drawing::Point(211, 33);
			this->label30->Name = L"label30";
			this->label30->Size = System::Drawing::Size(471, 306);
			this->label30->TabIndex = 67;
			this->label30->Text = resources->GetString(L"label30.Text");
			// 
			// label31
			// 
			this->label31->AccessibleName = L"";
			this->label31->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label31->Location = System::Drawing::Point(239, 442);
			this->label31->Name = L"label31";
			this->label31->Size = System::Drawing::Size(371, 79);
			this->label31->TabIndex = 68;
			this->label31->Text = L"где u(x) – смещение груза вдоль оси абсцисс относительно положения равновесия, x "
				L"– время, u₀ – начальное отклонение груза от равновесия и u\'₀ – его начальная ско"
				L"рость.";
			// 
			// label32
			// 
			this->label32->AccessibleName = L"";
			this->label32->AutoSize = true;
			this->label32->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label32->Location = System::Drawing::Point(27, 492);
			this->label32->Name = L"label32";
			this->label32->Size = System::Drawing::Size(119, 29);
			this->label32->TabIndex = 69;
			this->label32->Text = L"u = u₀eˣ⁻ˣ⁰";
			// 
			// label33
			// 
			this->label33->AccessibleName = L"";
			this->label33->AutoSize = true;
			this->label33->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label33->Location = System::Drawing::Point(300, 859);
			this->label33->Name = L"label33";
			this->label33->Size = System::Drawing::Size(276, 25);
			this->label33->TabIndex = 70;
			this->label33->Text = L"Таблица тестовой задачи";
			// 
			// label34
			// 
			this->label34->AccessibleName = L"";
			this->label34->AutoSize = true;
			this->label34->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label34->Location = System::Drawing::Point(1852, 859);
			this->label34->Name = L"label34";
			this->label34->Size = System::Drawing::Size(274, 25);
			this->label34->TabIndex = 71;
			this->label34->Text = L"Таблица основной задачи";
			// 
			// label35
			// 
			this->label35->AccessibleName = L"";
			this->label35->AutoSize = true;
			this->label35->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label35->Location = System::Drawing::Point(27, 643);
			this->label35->Name = L"label35";
			this->label35->Size = System::Drawing::Size(68, 25);
			this->label35->TabIndex = 72;
			this->label35->Text = L"x₀ = a";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(2499, 1380);
			this->Controls->Add(this->label35);
			this->Controls->Add(this->label34);
			this->Controls->Add(this->label33);
			this->Controls->Add(this->label32);
			this->Controls->Add(this->label31);
			this->Controls->Add(this->label30);
			this->Controls->Add(this->label29);
			this->Controls->Add(this->label25);
			this->Controls->Add(this->label26);
			this->Controls->Add(this->label27);
			this->Controls->Add(this->label28);
			this->Controls->Add(this->label23);
			this->Controls->Add(this->label24);
			this->Controls->Add(this->label22);
			this->Controls->Add(this->label21);
			this->Controls->Add(this->label20);
			this->Controls->Add(this->label19);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label18);
			this->Controls->Add(this->label17);
			this->Controls->Add(this->label16);
			this->Controls->Add(this->textBox15);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->labelMainInfo);
			this->Controls->Add(this->labelTestInfo);
			this->Controls->Add(this->textBox14);
			this->Controls->Add(this->label15);
			this->Controls->Add(this->textBox13);
			this->Controls->Add(this->label14);
			this->Controls->Add(this->textBox12);
			this->Controls->Add(this->label13);
			this->Controls->Add(this->textBox11);
			this->Controls->Add(this->label12);
			this->Controls->Add(this->textBox10);
			this->Controls->Add(this->label11);
			this->Controls->Add(this->dataGridView2);
			this->Controls->Add(this->zedGraphControl4);
			this->Controls->Add(this->zedGraphControl3);
			this->Controls->Add(this->zedGraphControl2);
			this->Controls->Add(this->checkBox1);
			this->Controls->Add(this->label10);
			this->Controls->Add(this->textBox9);
			this->Controls->Add(this->label9);
			this->Controls->Add(this->textBox8);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->textBox7);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->textBox6);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->ZoomButton);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->dataGridView1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->zedGraphControl1);
			this->Margin = System::Windows::Forms::Padding(4);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView2))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private:
		// ============ ТЕСТОВАЯ ЗАДАЧА ============
		// точное решение тестовой задачи
		double f1(double x, double x0, double u0) {
			return u0 * Math::Exp(x - x0);
		}

		// численное решение тестовой задачи
		double f2(double x, double u) {
			double variant = 2;
			if ((int)variant % 2) {
				return (-1.0 * variant / 2.0 * u);
			}
			else {
				return (1.0 * variant / 2.0 * u);
			}
		}

		// RK4 для ОДУ
		double RK4_Step(double x, double v, double h) {
			double k1 = f2(x, v);
			double k2 = f2(x + h / 2.0, v + h / 2.0 * k1);
			double k3 = f2(x + h / 2.0, v + h / 2.0 * k2);
			double k4 = f2(x + h, v + h * k3);
			return v + (h / 6.0) * (k1 + 2.0 * k2 + 2.0 * k3 + k4);
		}



		// ============ ОСНОВНАЯ ЗАДАЧА ============
		// параметры системы (пользователь может переписать, изначальные значения - записаны в textbox)
		double m_val, c_val, k_val, ks_val;

		// система ОДУ основной задачи
		void f_system(double x, double u1, double u2, double& du1, double& du2) {
			du1 = u2; // f1(x,u1,u2)
			// u2' = -1/m * (c*u2 + k*u1 + k_star * u1^3)
			du2 = (-1.0 / m_val) * (c_val * u2 + k_val * u1 + ks_val * Math::Pow(u1, 3.0)); // f2(x,u1,u2)
		}

		// RK4 для системы 2-го порядка ОДУ
		void RK4_Step_System(double x, double u1, double u2, double h, double& u1_next, double& u2_next) {
			double k1_1, k1_2, k2_1, k2_2, k3_1, k3_2, k4_1, k4_2;

			// k1_1   k1_2
			f_system(x, u1, u2, k1_1, k1_2);

			// k2_1   k2_2
			f_system(x + h / 2.0, u1 + h / 2.0 * k1_1, u2 + h / 2.0 * k1_2, k2_1, k2_2);

			// k3_1   k3_2
			f_system(x + h / 2.0, u1 + h / 2.0 * k2_1, u2 + h / 2.0 * k2_2, k3_1, k3_2);

			// k4_1   k4_2
			f_system(x + h, u1 + h * k3_1, u2 + h * k3_2, k4_1, k4_2);

			// теперь знаю все k, считаю каждую компоненту - она передается по ссылке, изменения сохраняются
			u1_next = u1 + (h / 6.0) * (k1_1 + 2.0 * k2_1 + 2.0 * k3_1 + k4_1);
			u2_next = u2 + (h / 6.0) * (k1_2 + 2.0 * k2_2 + 2.0 * k3_2 + k4_2);
		}



		// событие OnClick для кнопки Draw
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		GraphPane^ panel = zedGraphControl1->GraphPane;
		panel->CurveList->Clear();
		PointPairList^ f1_list = gcnew ZedGraph::PointPairList();
		PointPairList^ f2_list = gcnew ZedGraph::PointPairList();
		PointPairList^ f3_list = gcnew ZedGraph::PointPairList();




		// настройка заголовков для Тестовой задачи
		zedGraphControl1->GraphPane->Title->Text = L"Тестовая задача";
		zedGraphControl1->GraphPane->XAxis->Title->Text = L"x";
		zedGraphControl1->GraphPane->YAxis->Title->Text = L"U / V";

		// интервал [a,b] (вводит пользователь)
		double xmin = Convert::ToDouble(textBox1->Text);
		double xmax = Convert::ToDouble(textBox2->Text);

		dataGridView1->Rows->Clear();


		// параметр выхода за правую границу
		double Eps_edge = Convert::ToDouble(textBox7->Text); // [b_n - Eps_edge,b_n)   --( x_n принадлежит [b_n - Eps_edge,b_n) , x_n < b_n !! )--

		// максимальное кол-во итераций (чтобы не упереться в асимптоту и бесконечный счет)
		int N_max = Convert::ToDouble(textBox8->Text);

		// начальный шаг
		double h0 = Convert::ToDouble(textBox3->Text);

		// Задача Коши Тестовой задачи
		double U0 = Convert::ToDouble(textBox6->Text);
		std::vector<double> V(1);
		V[0] = U0;
		std::vector<double> X(1);
		X[0] = xmin;

		// Контроль локальной погрешности
		double eps_lp = Convert::ToDouble(textBox9->Text);
		// если пользователь вводит число меньше MIN_DOUBLE - ставлю 1e-15
		if (eps_lp < 1e-15) {
			eps_lp = 1e-15;
			textBox9->Text = "1e-15";
		}

		// информация о каждой итерации (для таблицы)
		std::vector<double> X_arr;      // xi
		std::vector<double> V_arr;      // vi (численное решение)
		std::vector<double> V2_arr;     // v2i (расчет с половинным шагом)
		std::vector<double> OLP_arr;    // |vi - v2i| / 15
		std::vector<double> H_arr;      // hi (шаг, с которым был принят результат)
		std::vector<int> C1_arr;        // Счетчики деления
		std::vector<int> C2_arr;        // Счетчики умножения
		std::vector<double> Err_arr;    // |ui - vi| (разность с точным решением)


		// Переменные для итоговой справки
		int total_c1 = 0;            // Общее число делений
		int total_c2 = 0;            // Общее число удвоений
		double max_olp_val = 0;      // максимальная ОЛП
		double max_h_val = 0;        // максимальный шаг
		double x_at_max_h = xmin;    // значение x при максимальном шаге
		double min_h_val = 1e30;     // минимальный шаг (изначально беру равным большому числу чтобы точно уменьшился)
		double x_at_min_h = xmin;    // значение x при минимальном шаге
		double max_err_val = 0;      // максимальная глобальная погрешность
		double x_at_max_err = xmin;  // значение x при котором достигается макс глобальная погрешность



		// 0-я итерация
		double x0_const = xmin;
		double u0_const = U0;
		int i = 0;
		double x_curr = x0_const;
		double v_curr = U0;
		double h = h0;


		// --- Добавление начальной точки (i=0) в таблицу ---
		dataGridView1->Rows->Add();
		dataGridView1->Rows[i]->Cells[0]->Value = i;         // i = 0
		dataGridView1->Rows[i]->Cells[1]->Value = x_curr;    // x0
		dataGridView1->Rows[i]->Cells[2]->Value = v_curr;    // v0
		dataGridView1->Rows[i]->Cells[3]->Value = v_curr;    // v2i (для x0 совпадает)
		dataGridView1->Rows[i]->Cells[4]->Value = 0;         // v_i - v_2i
		dataGridView1->Rows[i]->Cells[5]->Value = 0;         // ОЛП
		dataGridView1->Rows[i]->Cells[6]->Value = h;         // Начальный шаг
		dataGridView1->Rows[i]->Cells[7]->Value = 0;         // C1
		dataGridView1->Rows[i]->Cells[8]->Value = 0;         // C2

		double u0 = f1(x_curr, x0_const, u0_const);
		dataGridView1->Rows[i]->Cells[9]->Value = u0;        // u0
		dataGridView1->Rows[i]->Cells[10]->Value = Math::Abs(u0 - v_curr); // Ошибка в 0

		// Добавляем начальную точку на графики
		f1_list->Add(x_curr, u0);
		f2_list->Add(x_curr, v_curr);


		// точка x0 поставлена - увеличиваем счетчик итераций
		i++;


		// флаг для выхода на последней итерации (попали на [b-Eps_edge, b)  -- значит нужно заканчивать)
		bool is_last_step = false;


		// основной цикл (тестовая задача)
		while (x_curr < xmax && i < N_max && !is_last_step)
		{
			// счетчики деления (C1) умножения (C2) шага на текущей итерации
			int c1 = 0;
			int c2 = 0;


			// если начинаем выходить за правую границу, то подбираю шаг, чтобы не выйти 
			if (x_curr + h > xmax - Eps_edge) {
				is_last_step = true;

				if (x_curr + h > xmax) {
					// 1. Пытаемся прыгнуть в середину интервала Eps_edge
					double h_to_edge = (xmax - Eps_edge / 2.0) - x_curr;

					// если точности double хватило - значит делаем шаг, чтобы попасть в середину отрезка  [b_n - Eps_edge,b_n)
					if (h_to_edge > 0) {
						h = h_to_edge;

					}
					// если точности double не хватило - значит считаем, что уже достаточно близко подошли к правой границе
					else {
						break;
					}
				}

			} // if (...) подбор шага чтобы не выйти за правую границу



			double v_h;      // численное решение на текущей итерации с шагом h
			double v_half_2; // численное решение с помощью 2х шагов по h/2
			double S;        // параметр для контроля локальной погрешности (для адаптивного шага)



			// адаптивный шаг
			while (1) {




				// нахожу текущее численное решение с шагом h
				v_h = RK4_Step(x_curr, v_curr, h); // (x_n, V_n) -> (x_n+1, V_n+1)

				// нахожу численное решение с шагом h/2
				double v_half_1 = RK4_Step(x_curr, v_curr, h / 2.0); // (x_n,V_n) -> (x_n+0.5 , V_n+0.5)
				v_half_2 = RK4_Step(x_curr + h / 2.0, v_half_1, h / 2.0); // (x_n+0.5 , V_n+0.5) -> (x_n+1, V_n+1) =  (x_n+1, V_n+1_с_крышкой)

				// параметр S = (V_n+1_с_крышкой - V_n+1) / (2^p -1)
				S = (v_half_2 - v_h) / 15.0; // 2^p - 1 = 15.0  (так как порядок RK4: p = 4 )



				// если не выбран адаптивный шаг или шаг последний - дальше шаг можно не подбирать
				if (!checkBox1->Checked || is_last_step) {
					break;
				}



				// ==== подбор шага ===
				// Eps_lp/2^p+1 <= |S| <= Eps_lp      (принимаем точку и не меняем шаг)	
				if (eps_lp / 32.0 <= Math::Abs(S) && Math::Abs(S) <= eps_lp) {
					break;
				}
				// |S| < Eps_lp/2^p+1   (принимаем точку и шаг*=2  так как посчитали точнее, чем нужно)	
				else if (Math::Abs(S) < eps_lp / 32.0) {
					h *= 2.0;
					c2++;
					break;
				}
				// |S| > Eps_lp         (точку не принимаем так как не посчитали достаточно точно; делим шаг на 2)
				else if (Math::Abs(S) > eps_lp) {
					h /= 2.0;
					c1++;


					// если шаг стал меньше, чем мантисса типа double - выходим, чтобы не зависнуть
					if (h < 1e-16) {
						break;
					}


					continue;

				} // if else else  подбор шага
			} // конец while(1) -  цикла подбора адаптивного шага


			// x_n+1 = x_n + h
			x_curr += h;


			// v_n+1 = v_n + h/6(k1+2*k2+2*k3+k4) |||  RK4_Step(x_curr, v_curr, h)
			v_curr = v_h;

			// P.S. v_h вычисляется в цикле адаптивного шага


			// на этом этапе все посчитали - осталось вывести информацию на график и в таблицу


			// добавление на график
			f1_list->Add(x_curr, f1(x_curr, x0_const, u0_const));
			f2_list->Add(x_curr, v_curr);
			// печать в таблицу
			dataGridView1->Rows->Add();
			dataGridView1->Rows[i]->Cells[0]->Value = i;                // i
			dataGridView1->Rows[i]->Cells[1]->Value = x_curr;           // x_i
			dataGridView1->Rows[i]->Cells[2]->Value = v_h;              // v_i
			dataGridView1->Rows[i]->Cells[3]->Value = v_half_2;         // v_2i
			dataGridView1->Rows[i]->Cells[4]->Value = v_h - v_half_2;   // v_i - v_2i
			dataGridView1->Rows[i]->Cells[5]->Value = Math::Abs(S) * 16.0; // ОЛП
			dataGridView1->Rows[i]->Cells[6]->Value = h;                // h_i
			dataGridView1->Rows[i]->Cells[7]->Value = c1;               // C1
			dataGridView1->Rows[i]->Cells[8]->Value = c2;               // C2
			// u_i
			double u_i = f1(x_curr, x0_const, u0_const); // точное решение
			dataGridView1->Rows[i]->Cells[9]->Value = u_i;
			// |u_i - v_i|
			double err = Math::Abs(u_i - v_h);
			dataGridView1->Rows[i]->Cells[10]->Value = err;
			// обновляем итоговую статистику: общее кол-во делений(C1) , умножений(C2)
			total_c1 += c1;
			total_c2 += c2;

			double current_olp = Math::Abs(S) * 16.0;
			// максимальная ОЛП
			if (current_olp > max_olp_val) {
				max_olp_val = current_olp;
			}
			// максимальный шаг
			if (h > max_h_val) {
				max_h_val = h;
				x_at_max_h = x_curr;
			}
			// минимальный шаг
			if (h < min_h_val) {
				min_h_val = h;
				x_at_min_h = x_curr;
			}
			// максимальная глобальная погрешность max|u - v|
			if (err > max_err_val) {
				max_err_val = err;
				x_at_max_err = x_curr;
			}
			// шаг итерации увеличивается на 1
			i++;

		} // конец цикла for (основной цикл решения тестовой задачи)


		LineItem Curve1 = panel->AddCurve("U(x)", f1_list, Color::Green, SymbolType::None);
		LineItem Curve2 = panel->AddCurve("V(x)", f2_list, Color::Red, SymbolType::None);


		// Вывод справочной информации (тестовая задача)
		labelTestInfo->Text = String::Format(
			"Справка по тестовой задаче:\n" +
			"n = {0}\n" +
			"b - xn = {1}\n" +
			"max|ОЛП| = {2:F16}\n" +
			"Делений шага: {3}\n" +
			"Удвоений шага: {4}\n\n" +
			"max h = {5:F16}\n" +
			"(при x={6:F16})\n\n" +
			"min h = {7:F16} \n" +
			"(при x={8:F16})\n\n"
			"max|u - v| = {9:F16} \n" +
			"(при x={10:F16})",
			i, (xmax - x_curr), max_olp_val, total_c1, total_c2,
			max_h_val, x_at_max_h, min_h_val, x_at_min_h, max_err_val, x_at_max_err
		);








		// ================ ОСНОВНАЯ ЗАДАЧА ===========

		// Списки точек траекторий
		PointPairList^ list_u1 = gcnew PointPairList();
		PointPairList^ list_u2 = gcnew PointPairList();
		PointPairList^ list_phase = gcnew PointPairList();


		// Настройка заголовков для Графика смещения
		zedGraphControl2->GraphPane->Title->Text = L"Основная задача: Зависимость u(x) (смещение)";
		zedGraphControl2->GraphPane->XAxis->Title->Text = L"x";
		zedGraphControl2->GraphPane->YAxis->Title->Text = L"u (смещение)";

		// Настройка заголовков для Графика скорости
		zedGraphControl3->GraphPane->Title->Text = L"Основная задача: Зависимость u'(x) (скорость)";
		zedGraphControl3->GraphPane->XAxis->Title->Text = L"x";
		zedGraphControl3->GraphPane->YAxis->Title->Text = L"u' (скорость)";


		// Настройка заголовков для Фазового портрета
		zedGraphControl4->GraphPane->Title->Text = L"Фазовый портрет";
		zedGraphControl4->GraphPane->XAxis->Title->Text = L"u (смещение)";
		zedGraphControl4->GraphPane->YAxis->Title->Text = L"u' (скорость)";

		// Очистка графиков
		zedGraphControl2->GraphPane->CurveList->Clear();
		zedGraphControl3->GraphPane->CurveList->Clear();
		zedGraphControl4->GraphPane->CurveList->Clear();

		// Очистка таблицы (основная задача)
		dataGridView2->Rows->Clear();


		// Инициализация статистики (как и в тестовой задаче)
		int total_c1_s = 0;
		int total_c2_s = 0;
		double max_olp_s = 0;
		double max_h_s = 0;
		double x_at_max_h_s = xmin;
		double min_h_s = 1e30;
		double x_at_min_h_s = xmin;

		// Чтение параметров системы
		m_val = Convert::ToDouble(textBox10->Text);  // m
		c_val = Convert::ToDouble(textBox11->Text);  // c
		k_val = Convert::ToDouble(textBox12->Text);  // k
		ks_val = Convert::ToDouble(textBox13->Text); // k*

		m_val *= 0.01; // чтобы смещение U(x) было в сантиметрах и все правильно считалось


		// 0-я итерация
		int i_s = 0;
		double x_s = xmin; // x0
		double u1_s = Convert::ToDouble(textBox15->Text); // u(0)
		double u2_s = Convert::ToDouble(textBox14->Text); // u'(0)
		double h_s = h0; // h0

		bool is_last_s = false;

		// --- Добавление начальной точки (i=0) в таблицу 2 ---
		int r0 = dataGridView2->Rows->Add();
		dataGridView2->Rows[r0]->Cells[0]->Value = i_s;      // i = 0
		dataGridView2->Rows[r0]->Cells[1]->Value = x_s;      // x0
		dataGridView2->Rows[r0]->Cells[2]->Value = u1_s;     // v1_0 (смещение)
		dataGridView2->Rows[r0]->Cells[3]->Value = u2_s;     // v2_0 (скорость)
		dataGridView2->Rows[r0]->Cells[4]->Value = 0;        // v - v2
		dataGridView2->Rows[r0]->Cells[5]->Value = 0;        // ОЛП
		dataGridView2->Rows[r0]->Cells[6]->Value = h_s;      // h0
		dataGridView2->Rows[r0]->Cells[7]->Value = 0;        // C1
		dataGridView2->Rows[r0]->Cells[8]->Value = 0;        // C2

		// Добавляем начальную точку на графики
		list_u1->Add(x_s, u1_s);
		list_u2->Add(x_s, u2_s);
		list_phase->Add(u1_s, u2_s);

		// добавили в таблицу x0 - значит надо счетчик итерации увеличить на 1
		i_s++;

		// основной цикл (основная задача)
		while (x_s < xmax && i_s < N_max && !is_last_s) {

			// локальные счетчики делений (C1) умножений (C2)
			int c1 = 0;
			int c2 = 0;

			// контроль правой границы (то же самое,что и в тестовой задаче)
			if (x_s + h_s > xmax - Eps_edge) {
				is_last_s = true;
				if (x_s + h_s > xmax) {
					double h_to_edge = (xmax - Eps_edge / 2.0) - x_s;
					if (h_to_edge > 0) h_s = h_to_edge; else break;
				}
			}

			double v1_h, v2_h, v1_half2, v2_half2, S_norm;

			while (1) {

				RK4_Step_System(x_s, u1_s, u2_s, h_s, v1_h, v2_h);

				// два шага по h/2
				double v1_temp;
				double v2_temp;
				RK4_Step_System(x_s, u1_s, u2_s, h_s / 2.0, v1_temp, v2_temp);
				RK4_Step_System(x_s + h_s / 2.0, v1_temp, v2_temp, h_s / 2.0, v1_half2, v2_half2);

				// оценка каждой компоненты
				double s1 = (v1_half2 - v1_h) / 15.0;
				double s2 = (v2_half2 - v2_h) / 15.0;

				// оценка ОЛП (норма по Чебышёву)
				S_norm = Math::Max(Math::Abs(s1), Math::Abs(s2));

				// если не выбран адаптивный шаг или шаг последний - дальше шаг можно не подбирать
				if (!checkBox1->Checked || is_last_s) {
					break;
				}


				// ==== подбор шага === (как в тестовой)
				// Eps_lp/2^p+1 <= |S| <= Eps_lp      (принимаем точку и не меняем шаг)	
				if (eps_lp / 32.0 <= S_norm && S_norm <= eps_lp) {
					break;
				}
				// |S| < Eps_lp/2^p+1   (принимаем точку и шаг*=2  так как посчитали точнее, чем нужно)	
				else if (S_norm < eps_lp / 32.0) {
					h_s *= 2.0;
					c2++;
					break;
				}
				// |S| > Eps_lp         (точку не принимаем так как не посчитали достаточно точно; делим шаг на 2)
				else if (S_norm > eps_lp) {
					h_s /= 2.0;
					c1++;
					// если шаг стал меньше, чем мантисса типа double - выходим, чтобы не зависнуть
					if (h_s < 1e-16) {
						break;
					}
					continue;

				} // if else else  подбор шага

			} // цикл for подбора адаптивного шага


			// делаем шаг
			x_s += h_s;
			u1_s = v1_h;
			u2_s = v2_h;


			// обновляем статистику: кол-во делений (C1) , кол-во умножений(C2), max|OLP|, 
			// max шаг (+значение x при нем), min шаг(+значение x при нем)
			total_c1_s += c1;
			total_c2_s += c2;
			double current_olp_s = S_norm * 16.0;
			if (current_olp_s > max_olp_s) max_olp_s = current_olp_s;
			if (h_s > max_h_s) { max_h_s = h_s; x_at_max_h_s = x_s; }
			if (h_s < min_h_s) { min_h_s = h_s; x_at_min_h_s = x_s; }


			// добавляю точку в список точек для отрисовки
			list_u1->Add(x_s, u1_s);     // смещение
			list_u2->Add(x_s, u2_s);     // скорость
			list_phase->Add(u1_s, u2_s); // фазовый портрет

			// заполнение таблицы
			int r = dataGridView2->Rows->Add();
			dataGridView2->Rows[r]->Cells[0]->Value = i_s;
			dataGridView2->Rows[r]->Cells[1]->Value = x_s;
			dataGridView2->Rows[r]->Cells[2]->Value = v1_h;
			dataGridView2->Rows[r]->Cells[3]->Value = v2_h;
			dataGridView2->Rows[r]->Cells[4]->Value = v1_h - v1_half2;
			dataGridView2->Rows[r]->Cells[5]->Value = current_olp_s;
			dataGridView2->Rows[r]->Cells[6]->Value = h_s;
			dataGridView2->Rows[r]->Cells[7]->Value = c1;
			dataGridView2->Rows[r]->Cells[8]->Value = c2;

			// увеличиваю счетчик итераций
			i_s++;

		} // цикл for (основной цикл решения основной задачи)

		// отрисовка графиков
		zedGraphControl2->GraphPane->AddCurve("u(x)", list_u1, Color::Blue, SymbolType::None);
		zedGraphControl2->AxisChange(); zedGraphControl2->Invalidate();

		zedGraphControl3->GraphPane->AddCurve("u'(x)", list_u2, Color::OrangeRed, SymbolType::None);
		zedGraphControl3->AxisChange(); zedGraphControl3->Invalidate();

		zedGraphControl4->GraphPane->AddCurve("Траектория", list_phase, Color::Purple, SymbolType::None);
		zedGraphControl4->AxisChange(); zedGraphControl4->Invalidate();

		// вывод справочной информации (основная задача)
		labelMainInfo->Text = String::Format(
			"Справка по основной задаче:\n" +
			"n = {0}\n" +
			"b - xn = {1:F16}\n" +
			"max|ОЛП| = {2:F16}\n" +
			"Делений шага: {3}\n" +
			"Удвоений шага: {4}\n\n" +
			"max h = {5:F16}\n" +
			"(при x={6:F16})\n\n" +
			"min h = {7:F16} \n" +
			"(при x={8:F16})",
			i_s, (xmax - x_s), max_olp_s, total_c1_s, total_c2_s,
			max_h_s, x_at_max_h_s, min_h_s, x_at_min_h_s
		);


		// на этом этапе решение закончено, можно сделать zoom на отрезок [a,b]

		// auto zoom:
		double xmin_limit = xmin - 0.1;
		double xmax_limit = xmax + 0.1;
		// Устанавливаем интересующий нас интервал по оси X
		panel->XAxis->Scale->Min = xmin_limit;
		panel->XAxis->Scale->Max = xmax_limit;
		/*
				// Устанавливаем интересующий нас интервал по оси Y
				panel->YAxis->Scale->Min = ymin_limit;
				panel->YAxis->Scale->Max = ymax_limit;
		*/
		// Вызываем метод AxisChange (), чтобы обновить данные об осях. 
		// В противном случае на рисунке будет показана только часть графика, 
		// которая умещается в интервалы по осям, установленные по умолчанию
		zedGraphControl1->AxisChange();
		// Обновляем график
		zedGraphControl1->Invalidate();

	} // OnClick для кнопки Draw



	// событие OnClick для кнопки Zoom
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		double xmin = Convert::ToDouble(textBox1->Text);
		double xmax = Convert::ToDouble(textBox2->Text);

		array<ZedGraph::ZedGraphControl^>^ controls = { zedGraphControl1, zedGraphControl2, zedGraphControl3, zedGraphControl4 };

		for (int i = 0; i < controls->Length; i++) {
			GraphPane^ pane = controls[i]->GraphPane;

			// Настройка множителей (Mag), чтобы не было проблем с порядками величин
			pane->XAxis->Scale->MagAuto = true;
			pane->YAxis->Scale->MagAuto = true;

			if (controls[i] != zedGraphControl4) {
				// Для обычных графиков (1, 2, 3) ставим границы по X (это x)
				pane->XAxis->Scale->Min = xmin;
				pane->XAxis->Scale->Max = xmax;
				pane->XAxis->Scale->MinAuto = false;
				pane->XAxis->Scale->MaxAuto = false;
				pane->YAxis->Scale->MinAuto = true; // Авто-высота
			}
			else {
				// ЛОГИКА ДЛЯ ФАЗОВОГО ПОРТРЕТА (zedGraphControl4)
				// Здесь оси — это u1 и u2. Ставим их в Auto, чтобы они подстроились 
				// под новые вычисленные значения функций.
				pane->XAxis->Scale->MinAuto = true;
				pane->XAxis->Scale->MaxAuto = true;
				pane->YAxis->Scale->MinAuto = true;
				pane->YAxis->Scale->MaxAuto = true;
			}

			controls[i]->AxisChange();
			controls[i]->Invalidate();
		}

	} // OnClick для кнопки Zoom

	private: System::Void label22_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label23_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label24_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	}; // MyForm

} // namespace Graph