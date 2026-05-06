#pragma once
#include <math.h>
#include <vector>
#include <functional>
#include <omp.h>

# define M_PI 3.14159265358979323846



static double k_func(double x) {
	double a = 0;
	double b = 1;
	double ksi = M_PI / 4.0;

	if (x < a || x > b) {
		throw "k(x) not defined out of [0,1]";
	}

	if (x <= ksi) {
		return sqrt(2) * sin(x) + 0.1;
	}

	if (x > ksi) {
		return cos(x) * cos(x) + 0.1;
	}
	
}


static double q_func(double x) {
	double a = 0;
	double b = 1;
	double ksi = M_PI / 4.0;

	if (x < a || x > b) {
		throw "q(x) not defined out of [0,1]";
	}

	if (x <= ksi) {
		return 1;
	}

	if (x > ksi) {
		return x*x;
	}

}


static double f_func(double x) {
	double a = 0;
	double b = 1;
	double ksi = M_PI / 4.0;

	if (x < a || x > b) {
		throw "f(x) not defined out of [0,1]";
	}

	if (x <= ksi) {
		return sin(2*x);
	}

	if (x > ksi) {
		return cos(x);
	}

}








void Calc_fi(double& fi, std::function<double(double)> f, double a, double ksi, double b, double h) {
	
	if (a < ksi && ksi < b) {
		fi = 1 / h * f((ksi + a) / 2) * (ksi - a) + 1 / h * f((b + ksi) / 2) * (b - ksi);
		return;
	}

	double mid = (a + b) / 2;
	if (ksi >= b) {
		fi = f(mid);
		return;
	}

	if (ksi <= a) {
		fi = f(mid);
		return;
	}
	throw "Something went wrong?";
}



void Calc_di(double& di, std::function<double(double)> q, double a, double ksi, double b, double h) {

	if (a < ksi && ksi < b) {
		di = 1 / h * q((ksi+a)/2)*(ksi-a) + 1/h * q((b+ksi)/2)*(b-ksi);
		return;
	}

	double mid = (a + b) / 2;
	if (ksi >= b) {
		di = q(mid);
		return;
	}

	if (ksi <= a) {
		di = q(mid);
		return;
	}

	throw "Something went wrong?";
}


void Calc_ai(double& ai, std::function<double(double)> k, double a, double ksi, double b, double h) {
	if (a < ksi && ksi < b) {
		ai = 1/(1 / h * 1 / k((ksi + a) / 2) * (ksi - a) + 1 / h * 1 / k((b + ksi) / 2) * (b - ksi));
		return;
	}

	double mid = (a + b) / 2;
	

	if (ksi >= b) {
		ai = k(mid);
		return;
	}

	if (ksi <= a) {
		ai = k(mid);
		return;
	}

	throw "Something went wrong?";
}




static void solveBoundaryValueProblem(
	std::function<double(double)> k,
	std::function<double(double)> q,
	std::function<double(double)> f,
	double a_edge, double b_edge, double n, double mu1, double mu2,
	double ksi,
	std::vector<double>& vi, std::vector<double>& v2i,
	std::vector<double>& out_grid, std::vector<double>& out_grid2) {


	double h = (b_edge - a_edge) / n; // постоянный шаг
	
	std::vector<double> grid_values(n + 1);
	std::vector<double> grid_half_values(n);

	std::vector<double> grid2_values(2*n + 1);
	std::vector<double> grid2_half_values(2 * n);
	

	// ============== grid main ====================
	// gn - greed node (узел сетки)
	double gn = a_edge;

	for (int i = 0; i < n + 1; i++) {
		gn = a_edge + i * h;

		if (gn > b_edge) {
			gn = b_edge;
		}
		grid_values[i] = gn;
		
	}
	out_grid = grid_values;
	// ============== grid half ====================
	gn = a_edge + h/2;

	for (int i = 0; i < n; i++) {
		gn = a_edge + h / 2 + i * h;
		if (gn > b_edge) {
			gn = b_edge;
		}
		grid_half_values[i] = gn;
		
	}


	// ============== grid2 half h ====================
	gn = a_edge;

	for (int i = 0; i < 2*n+1; i++) {
		gn = a_edge + i * h / 2;
		if (gn > b_edge) {
			gn = b_edge;
		}
		grid2_values[i] = gn;
		
	}
	out_grid2 = grid2_values;



	// ============== grid2 half ====================
	gn = a_edge + h / 4;

	for (int i = 0; i < 2*n; i++) {
		gn = a_edge + h / 4 + i * h / 2;
		if (gn > b_edge) {
			gn = b_edge;
		}
		grid2_half_values[i] = gn;
		
	}


	// сводим интерполяцию к методу прогонки
	std::vector<double> c(n + 1);
	c[0] = mu1; // c0
	c[n] = mu2; // cn

	double kappa1 = 0;
	std::vector<double> alpha(n);
	std::vector<double> betta(n);
	alpha[0] = kappa1; // alpha1
	betta[0] = mu1; // betta1


	double Ai;
	double Bi;
	double Ci;
	// double fi_i; // будет дальше
	double znamen;


	// ======================== vi ======================
	double a_i, a_iplus1, d_i, fi_i;

	double hh = h * h;


	for (int i = 0; i <= n - 2; i++) {

		Calc_ai(a_i,k, grid_values[i],ksi,grid_values[i+1], h);
		Calc_ai(a_iplus1, k, grid_values[i+1],ksi, grid_values[i + 2], h);
		Calc_di(d_i, q, grid_half_values[i],ksi, grid_half_values[i + 1], h);
		Calc_fi(fi_i,f, grid_half_values[i],ksi, grid_half_values[i+1],h);

		
		Ai = a_i / hh;
		Ci = (a_i + a_iplus1) / hh + d_i;
		Bi = a_iplus1 / hh;

		znamen = Ci - Ai * alpha[i];

		alpha[i + 1] = Bi / znamen;
		betta[i + 1] = (fi_i + Ai * betta[i]) / (znamen);
	}

	// =========== прогонка ==========
	c[n] = mu2;
	for (int i = n - 1; i >= 0; i--) {
		c[i] = alpha[i] * c[i+1] + betta[i];
	}

	// ========== узлы ==========
	vi = c;




	// ======================== v2i ======================
	c.clear();
	c.resize(2*n+1);
	c[0] = mu1; // c0
	c[2*n] = mu2; // cn

	alpha.clear();
	alpha.resize(2*n);
	
	betta.clear();
	betta.resize(2 * n);

	alpha[0] = kappa1; // alpha1
	betta[0] = mu1; // betta1


	h = h / 2;

	hh = h * h;

	for (int i = 0; i <= 2*n - 2; i++) {


		Calc_ai(a_i, k, grid2_values[i], ksi, grid2_values[i + 1], h);
		Calc_ai(a_iplus1, k, grid2_values[i + 1], ksi, grid2_values[i + 2], h);
		Calc_di(d_i, q, grid2_half_values[i], ksi, grid2_half_values[i + 1], h);
		Calc_fi(fi_i, f, grid2_half_values[i], ksi, grid2_half_values[i + 1], h);


		Ai = a_i / hh;
		Ci = (a_i + a_iplus1) / hh + d_i;
		Bi = a_iplus1 / hh;

		znamen = Ci - Ai * alpha[i];

		alpha[i + 1] = Bi / znamen;
		betta[i + 1] = (fi_i + Ai * betta[i]) / (znamen);
	}

	// =========== прогонка ==========
	c[2*n] = mu2;
	for (int i = 2*n - 1; i >= 0; i--) {
		c[i] = alpha[i] * c[i + 1] + betta[i];
	}

	// ========== узлы ==========
	v2i = c;

	return;
}


















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
			SetupTables();
			InitializeTaskInfoLabels();
		}

	private: void SetupTables() {
		// Настройка Таблицы 1 (Коэффициенты сплайна)
		dataGridView1->Columns->Clear();
		dataGridView1->Columns->Add("i", L"i");
		dataGridView1->Columns->Add("xi_1", L"x_{i-1}");
		dataGridView1->Columns->Add("xi", L"x_i");
		dataGridView1->Columns->Add("ai", L"a_i");
		dataGridView1->Columns->Add("bi", L"b_i");
		dataGridView1->Columns->Add("ci", L"c_i");
		dataGridView1->Columns->Add("di", L"d_i");


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




	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::TextBox^ textBox2;









	private: System::Windows::Forms::Button^ ZoomButton;














	private: System::Windows::Forms::ToolTip^ toolTip1;




























































	private: System::Windows::Forms::Label^ labelTestInfo;











	private: System::Windows::Forms::TextBox^ textBox15;



	private: System::Windows::Forms::Label^ label18;


























	private: System::Windows::Forms::Label^ label20;












	private: System::Windows::Forms::Label^ label32;
	private: System::Windows::Forms::Label^ label33;





	private: System::Windows::Forms::Label^ labelMainTaskTitle;
	private: System::Windows::Forms::Label^ labelEquation;
	private: System::Windows::Forms::Label^ labelKfunc;
	private: System::Windows::Forms::Label^ labelQfunc;
	private: System::Windows::Forms::Label^ labelFfunc;
	private: System::Windows::Forms::Label^ labelBoundaryCond;



























	private: ZedGraph::ZedGraphControl^ zedGraphControl2;
	private: System::Windows::Forms::Label^ label36;
	private: System::Windows::Forms::Label^ label3;
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
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->ZoomButton = (gcnew System::Windows::Forms::Button());
			this->toolTip1 = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->labelTestInfo = (gcnew System::Windows::Forms::Label());
			this->textBox15 = (gcnew System::Windows::Forms::TextBox());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->label32 = (gcnew System::Windows::Forms::Label());
			this->label33 = (gcnew System::Windows::Forms::Label());
			this->zedGraphControl2 = (gcnew ZedGraph::ZedGraphControl());
			this->label36 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			this->SuspendLayout();
			// 
			// zedGraphControl1
			// 
			this->zedGraphControl1->Location = System::Drawing::Point(1573, 85);
			this->zedGraphControl1->Margin = System::Windows::Forms::Padding(6, 7, 6, 7);
			this->zedGraphControl1->Name = L"zedGraphControl1";
			this->zedGraphControl1->ScrollGrace = 0;
			this->zedGraphControl1->ScrollMaxX = 0;
			this->zedGraphControl1->ScrollMaxY = 0;
			this->zedGraphControl1->ScrollMaxY2 = 0;
			this->zedGraphControl1->ScrollMinX = 0;
			this->zedGraphControl1->ScrollMinY = 0;
			this->zedGraphControl1->ScrollMinY2 = 0;
			this->zedGraphControl1->Size = System::Drawing::Size(976, 580);
			this->zedGraphControl1->TabIndex = 0;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(737, 224);
			this->button1->Margin = System::Windows::Forms::Padding(5, 6, 5, 6);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(236, 50);
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
			this->dataGridView1->Location = System::Drawing::Point(14, 601);
			this->dataGridView1->Margin = System::Windows::Forms::Padding(5, 6, 5, 6);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->RowHeadersVisible = false;
			this->dataGridView1->RowHeadersWidth = 51;
			this->dataGridView1->Size = System::Drawing::Size(995, 726);
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
			this->X->Width = 125;
			// 
			// F_2
			// 
			this->F_2->HeaderText = L"V_i";
			this->F_2->MinimumWidth = 6;
			this->F_2->Name = L"F_2";
			this->F_2->ReadOnly = true;
			this->F_2->Width = 200;
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
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(895, 332);
			this->textBox1->Margin = System::Windows::Forms::Padding(5, 6, 5, 6);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(78, 28);
			this->textBox1->TabIndex = 4;
			this->textBox1->Text = L"0";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->Location = System::Drawing::Point(979, 330);
			this->label2->Margin = System::Windows::Forms::Padding(5, 0, 5, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(27, 29);
			this->label2->TabIndex = 5;
			this->label2->Text = L"b";
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(1016, 332);
			this->textBox2->Margin = System::Windows::Forms::Padding(5, 6, 5, 6);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(79, 28);
			this->textBox2->TabIndex = 6;
			this->textBox2->Text = L"1";
			// 
			// ZoomButton
			// 
			this->ZoomButton->Location = System::Drawing::Point(1305, 254);
			this->ZoomButton->Margin = System::Windows::Forms::Padding(5, 6, 5, 6);
			this->ZoomButton->Name = L"ZoomButton";
			this->ZoomButton->Size = System::Drawing::Size(236, 50);
			this->ZoomButton->TabIndex = 9;
			this->ZoomButton->Text = L"Zoom";
			this->ZoomButton->UseVisualStyleBackColor = true;
			this->ZoomButton->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// toolTip1
			// 
			this->toolTip1->ShowAlways = true;
			this->toolTip1->ToolTipIcon = System::Windows::Forms::ToolTipIcon::Info;
			// 
			// labelTestInfo
			// 
			this->labelTestInfo->AutoSize = true;
			this->labelTestInfo->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->labelTestInfo->Location = System::Drawing::Point(1047, 583);
			this->labelTestInfo->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelTestInfo->Name = L"labelTestInfo";
			this->labelTestInfo->Size = System::Drawing::Size(208, 25);
			this->labelTestInfo->TabIndex = 46;
			this->labelTestInfo->Text = L"Справка по задаче:";
			this->labelTestInfo->Click += gcnew System::EventHandler(this, &MyForm::labelTestInfo_Click);
			// 
			// textBox15
			// 
			this->textBox15->Location = System::Drawing::Point(895, 286);
			this->textBox15->Margin = System::Windows::Forms::Padding(5, 6, 5, 6);
			this->textBox15->Name = L"textBox15";
			this->textBox15->Size = System::Drawing::Size(99, 28);
			this->textBox15->TabIndex = 49;
			this->textBox15->Text = L"10";
			// 
			// label18
			// 
			this->label18->AccessibleName = L"";
			this->label18->AutoSize = true;
			this->label18->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label18->Location = System::Drawing::Point(627, 332);
			this->label18->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(216, 22);
			this->label18->TabIndex = 52;
			this->label18->Text = L"Границы отрезка [a,b]";
			// 
			// label20
			// 
			this->label20->AccessibleName = L"";
			this->label20->AutoSize = true;
			this->label20->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->label20->Location = System::Drawing::Point(1056, 517);
			this->label20->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(209, 38);
			this->label20->TabIndex = 57;
			this->label20->Text = L"Результаты";
			this->label20->Click += gcnew System::EventHandler(this, &MyForm::label20_Click);
			// 
			// label32
			// 
			this->label32->AccessibleName = L"";
			this->label32->AutoSize = true;
			this->label32->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label32->Location = System::Drawing::Point(14, 45);
			this->label32->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label32->Name = L"label32";
			this->label32->Size = System::Drawing::Size(69, 29);
			this->label32->TabIndex = 69;
			this->label32->Text = L"F(x)=";
			// 
			// label33
			// 
			this->label33->AccessibleName = L"";
			this->label33->AutoSize = true;
			this->label33->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label33->Location = System::Drawing::Point(450, 538);
			this->label33->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label33->Name = L"label33";
			this->label33->Size = System::Drawing::Size(103, 25);
			this->label33->TabIndex = 70;
			this->label33->Text = L"Таблица ";
			this->label33->Click += gcnew System::EventHandler(this, &MyForm::label33_Click);
			// 
			// zedGraphControl2
			// 
			this->zedGraphControl2->Location = System::Drawing::Point(1573, 714);
			this->zedGraphControl2->Margin = System::Windows::Forms::Padding(6, 7, 6, 7);
			this->zedGraphControl2->Name = L"zedGraphControl2";
			this->zedGraphControl2->ScrollGrace = 0;
			this->zedGraphControl2->ScrollMaxX = 0;
			this->zedGraphControl2->ScrollMaxY = 0;
			this->zedGraphControl2->ScrollMaxY2 = 0;
			this->zedGraphControl2->ScrollMinX = 0;
			this->zedGraphControl2->ScrollMinY = 0;
			this->zedGraphControl2->ScrollMinY2 = 0;
			this->zedGraphControl2->Size = System::Drawing::Size(976, 580);
			this->zedGraphControl2->TabIndex = 32;
			// 
			// label36
			// 
			this->label36->AccessibleName = L"";
			this->label36->AutoSize = true;
			this->label36->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label36->Location = System::Drawing::Point(627, 295);
			this->label36->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label36->Name = L"label36";
			this->label36->Size = System::Drawing::Size(199, 22);
			this->label36->TabIndex = 73;
			this->label36->Text = L"Число сегментов (n)";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label3->Location = System::Drawing::Point(867, 330);
			this->label3->Margin = System::Windows::Forms::Padding(5, 0, 5, 0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(26, 29);
			this->label3->TabIndex = 74;
			this->label3->Text = L"a";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(10, 22);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(2564, 1415);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label36);
			this->Controls->Add(this->label33);
			this->Controls->Add(this->label32);
			this->Controls->Add(this->label20);
			this->Controls->Add(this->label18);
			this->Controls->Add(this->textBox15);
			this->Controls->Add(this->labelTestInfo);
			this->Controls->Add(this->zedGraphControl2);
			this->Controls->Add(this->ZoomButton);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->dataGridView1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->zedGraphControl1);
			this->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Margin = System::Windows::Forms::Padding(5, 6, 5, 6);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		private: void InitializeTaskInfoLabels() {
			// Проверка на существование label32, чтобы избежать ошибок
			if (this->label32 == nullptr) return;

			// Определяем базовую точку (якорь)
			int anchorX = this->label32->Location.X;
			int anchorY = this->label32->Location.Y;

			// Определяем шрифты
			System::Drawing::Font^ titleFont = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16, System::Drawing::FontStyle::Bold);
			System::Drawing::Font^ mainFont = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular);
			System::Drawing::Font^ italicFont = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Italic);

			// 1. Заголовок
			this->labelMainTaskTitle = (gcnew System::Windows::Forms::Label());
			this->labelMainTaskTitle->Text = L"Основная задача (Вариант 5):";
			this->labelMainTaskTitle->Font = titleFont;
			this->labelMainTaskTitle->Location = System::Drawing::Point(anchorX, anchorY); // Точно в позиции label32
			this->labelMainTaskTitle->AutoSize = true;

			// 2. Уравнение
			this->labelEquation = (gcnew System::Windows::Forms::Label());
			this->labelEquation->Text = L"Уравнение: (k(x)u')' - q(x)u = -f(x), x ∈ [0,1]";
			this->labelEquation->Font = mainFont;
			this->labelEquation->Location = System::Drawing::Point(anchorX, anchorY + 40); // Смещение вниз на 40 пикселей
			this->labelEquation->AutoSize = true;

			// 3. Коэффициент k(x)
			this->labelKfunc = (gcnew System::Windows::Forms::Label());
			this->labelKfunc->Text = L"k(x) = { √2*sin(x)+0.1, x ≤ π/4\n         { cos²(x)+0.1, x > π/4";
			this->labelKfunc->Font = mainFont;
			this->labelKfunc->Location = System::Drawing::Point(anchorX, anchorY + 100);
			this->labelKfunc->AutoSize = true;

			// 4. Коэффициент q(x)
			this->labelQfunc = (gcnew System::Windows::Forms::Label());
			this->labelQfunc->Text = L"q(x) = { 1, x ≤ π/4\n         { x², x > π/4";
			this->labelQfunc->Font = mainFont;
			this->labelQfunc->Location = System::Drawing::Point(anchorX, anchorY + 190);
			this->labelQfunc->AutoSize = true;

			// 5. Правая часть f(x)
			this->labelFfunc = (gcnew System::Windows::Forms::Label());
			this->labelFfunc->Text = L"f(x) = { sin(2x), x ≤ π/4\n         { cos(x), x > π/4";
			this->labelFfunc->Font = mainFont;
			this->labelFfunc->Location = System::Drawing::Point(anchorX, anchorY + 280);
			this->labelFfunc->AutoSize = true;

			// 6. Граничные условия
			this->labelBoundaryCond = (gcnew System::Windows::Forms::Label());
			this->labelBoundaryCond->Text = L"Условия: u(0) = 1, u(1) = 0\nРазрыв ξ = π/4 ≈ 0.785";
			this->labelBoundaryCond->Font = italicFont;
			this->labelBoundaryCond->Location = System::Drawing::Point(anchorX, anchorY + 400);
			this->labelBoundaryCond->AutoSize = true;

			// Добавление новых элементов на форму
			this->Controls->Add(this->labelMainTaskTitle);
			this->Controls->Add(this->labelEquation);
			this->Controls->Add(this->labelKfunc);
			this->Controls->Add(this->labelQfunc);
			this->Controls->Add(this->labelFfunc);
			this->Controls->Add(this->labelBoundaryCond);

			// Скрываем сам якорь, если он не нужен для отображения
			this->label32->Visible = false;
		}
	private: void DrawTask() {
		// 1. Подготовка панели графика (используем только zedGraphControl1)
		GraphPane^ pane1 = zedGraphControl1->GraphPane;
		GraphPane^ pane2 = zedGraphControl2->GraphPane;
		pane1->CurveList->Clear();

		pane1->Title->Text = L"Решение краевой задачи";
		pane1->XAxis->Title->Text = L"x";
		pane1->YAxis->Title->Text = L"v(x)";

		pane2->Title->Text = L"Разность численных решений в общих узлах";
		pane2->XAxis->Title->Text = L"x";
		pane2->YAxis->Title->Text = L"v(x_i) - v2(x_2i)";

		// Очищаем остальные графики, чтобы они не мешали
		zedGraphControl2->GraphPane->CurveList->Clear();
		zedGraphControl2->AxisChange(); zedGraphControl2->Invalidate();

		// 2. Считывание параметров
		double a = Convert::ToDouble(textBox1->Text);
		double b = Convert::ToDouble(textBox2->Text);
		int n = Convert::ToInt32(textBox15->Text);

		// Параметры для задачи (граничные условия и точка разрыва)
		double mu1 = 1;
		double mu2 = 0.0;
		double ksi = M_PI / 4.0;

		// 3. Получение численного решения
		std::vector<double> vi, v2i, out_grid, out_grid2;
		solveBoundaryValueProblem(k_func, q_func, f_func, a, b, (double)n, mu1, mu2, ksi, vi, v2i, out_grid, out_grid2);

		// 4. Подготовка списков точек
		PointPairList^ v_list = gcnew PointPairList();
		PointPairList^ v2_list = gcnew PointPairList();
		PointPairList^ diff_list = gcnew PointPairList();

		// Данные для целого шага и разности
		for (int i = 0; i <= n; i++) {
			v_list->Add(out_grid[i], vi[i]);

			// Разность считаем только в общих узлах: x_i для целого шага совпадает с x_{2i} для половинного
			double diff = vi[i] - v2i[2 * i];
			diff_list->Add(out_grid[i], diff);
		}

		// Данные для половинного шага
		for (int i = 0; i <= 2 * n; i++) {
			v2_list->Add(out_grid2[i], v2i[i]);
		}

		// 5. Отрисовка на двух графиках (zedGraphControl1,2)
		float curveWidth = 1.5f;
		float nodeSize = 2.0f;

		LineItem^ curve_v = pane1->AddCurve(L"v(x) (шаг h)", v_list, Color::Blue, SymbolType::Circle);
		curve_v->Line->Width = curveWidth;
		curve_v->Symbol->Size = nodeSize;
		curve_v->Symbol->Fill->Type = FillType::Solid;

		LineItem^ curve_v2 = pane1->AddCurve(L"v2(x) (шаг h/2)", v2_list, Color::Red, SymbolType::None);
		curve_v2->Line->Width = curveWidth;
		curve_v2->Line->Style = System::Drawing::Drawing2D::DashStyle::Dash;

		float curveDiffWidth = 1.0f;
		float nodeDiffSize = 1.0f;
		LineItem^ curve_diff = pane2->AddCurve(L"Разность v(x) - v2(x)", diff_list, Color::Green, SymbolType::Square);
		curve_diff->Line->Width = curveDiffWidth;
		curve_diff->Symbol->Size = nodeDiffSize;
		curve_diff->Symbol->Fill->Type = FillType::Solid;

		zedGraphControl1->AxisChange();
		zedGraphControl1->Invalidate();

		// 6. === ЗАПОЛНЕНИЕ ТАБЛИЦЫ ===
		dataGridView1->Columns->Clear();
		dataGridView1->Columns->Add("NodeIndex", L"№ узла");
		dataGridView1->Columns["NodeIndex"]->Width = 60; // Установка ширины

		dataGridView1->Columns->Add("Xi", L"x_i");
		dataGridView1->Columns["Xi"]->Width = 180;

		dataGridView1->Columns->Add("Vi", L"v(x_i)");
		dataGridView1->Columns["Vi"]->Width = 180;

		dataGridView1->Columns->Add("V2i", L"v2(x_2i)");
		dataGridView1->Columns["V2i"]->Width = 180;

		dataGridView1->Columns->Add("Diff", L"v(x_i) - v2(x_2i)");
		dataGridView1->Columns["Diff"]->Width = 260;

		dataGridView1->Rows->Clear();

		double max_diff = -1.0;
		double x_max_diff = a;

		for (int i = 0; i <= n; i++) {
			double diff = vi[i] - v2i[2 * i];

			// Поиск максимальной разности для вывода в label
			if (Math::Abs(diff) > max_diff) {
				max_diff = Math::Abs(diff);
				x_max_diff = out_grid[i];
			}

			dataGridView1->Rows->Add(
				i,
				Math::Round(out_grid[i], 15),
				Math::Round(vi[i], 15),
				Math::Round(v2i[2 * i],15),
				diff.ToString("E15") // Экспоненциальный формат лучше подходит для малых разностей
			);
		}


		// 7. Обновление текстовой информации
		String^ infoText;
		infoText += L"Число разбиений n:\n n = " + n + L"\r\n\r\n";
		infoText += L"Шаг h (постоянный):\n h = " + (b-a)/n + L"\r\n\r\n";
		infoText += L"Решена с точностью:\n |v(x) - v2(x)| = " + max_diff.ToString("E15") + L"\r\n";
		infoText += L"Должна быть решена с точностью: " + (0.5/1000000).ToString("E5") + L"\r\n\r\n";
		infoText += L"Достигается в узле:\n x = " + Math::Round(x_max_diff, 15);

		labelTestInfo->Text = infoText;
	}

		   // Событие OnClick для кнопки Draw
private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	try {
		// Вызываем новую функцию отрисовки без старых параметров
		DrawTask();
		this->button2_Click(this->ZoomButton, e);
	}
	catch (const char* msg) {
		MessageBox::Show(gcnew String(msg), L"Ошибка области определения");
	}
	catch (Exception^ ex) {
		MessageBox::Show(ex->Message, L"Ошибка ввода или вычисления");
	}
}




		   // событие OnClick для кнопки Zoom
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		// Получаем границы отрезка из полей ввода
		double xmin = Convert::ToDouble(textBox1->Text);
		double xmax = Convert::ToDouble(textBox2->Text);

		// Рассчитываем длину интервала и величину отступа (5%)
		double delta = xmax - xmin;
		double margin = delta * 0.05;

		array<ZedGraph::ZedGraphControl^>^ controls = { zedGraphControl1, zedGraphControl2 };

		for (int i = 0; i < controls->Length; i++) {
			GraphPane^ pane = controls[i]->GraphPane;

			// Включаем автоматическое определение порядков величин (10^N)
			pane->XAxis->Scale->MagAuto = true;
			pane->YAxis->Scale->MagAuto = true;

			// Устанавливаем границы по X с небольшим отходом
			pane->XAxis->Scale->Min = xmin - margin;
			pane->XAxis->Scale->Max = xmax + margin;

			// Выключаем автоподбор для X, так как задали их вручную
			pane->XAxis->Scale->MinAuto = false;
			pane->XAxis->Scale->MaxAuto = false;

			// Для оси Y оставляем автомат, чтобы график всегда вписывался по высоте[cite: 7, 8]
			pane->YAxis->Scale->MinAuto = true;
			pane->YAxis->Scale->MaxAuto = true;

			// Применяем изменения и перерисовываем[cite: 7, 8]
			controls[i]->AxisChange();
			controls[i]->Invalidate();
		}
	}

	private: System::Void label22_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label23_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label24_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void labelTestInfo_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label20_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label33_Click(System::Object^ sender, System::EventArgs^ e) {
	}
}; // MyForm

} // namespace Graph