#pragma once
#include <math.h>
#include <vector>
#include <functional>

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
		ai = 1/(1 / h * 1 / k((ksi + a) / 2) * (ksi - a) + 1 / h * 1 / k((a + ksi) / 2) * (b - ksi));
		return;
	}

	double mid = (a + b) / 2;
	if (ksi >= b) {
		ai = k(a);
		return;
	}

	if (ksi <= a) {
		ai = k(a);
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
		if (gn > b_edge) {
			gn = b_edge;
		}
		grid_values[i] = gn;
		gn += h;
	}
	out_grid = grid_values;
	// ============== grid half ====================
	gn = a_edge + h/2;
	for (int i = 0; i < n; i++) {
		if (gn > b_edge) {
			gn = b_edge;
		}
		grid_half_values[i] = gn;
		gn += h;
	}


	// ============== grid2 half h ====================
	gn = a_edge;
	for (int i = 0; i < 2*n+1; i++) {
		if (gn > b_edge) {
			gn = b_edge;
		}
		grid2_values[i] = gn;
		gn += h / 2;
	}
	out_grid2 = grid2_values;



	// ============== grid2 half ====================
	gn = a_edge + h / 4;
	for (int i = 0; i < 2*n; i++) {
		if (gn > b_edge) {
			gn = b_edge;
		}
		grid2_half_values[i] = gn;
		gn += h / 2;
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
	c[n] = 0;
	for (int i = n - 1; i >= 0; i--) {
		c[i] = alpha[i] * c[i+1] + betta[i];
	}

	// ========== узлы ==========
	vi = c;




	// ======================== v2i ======================
	c.clear();
	c.resize(2*n+1);
	c[0] = mu1; // c0
	c[n] = mu2; // cn

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
	c[n] = 0;
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

		// Настройка Таблицы 2+3 (Значения и производные)
		dataGridView2->Columns->Clear();
		dataGridView2->Columns->Add("j", L"j");
		dataGridView2->Columns->Add("xj", L"x_j");
		dataGridView2->Columns->Add("F", L"F(x)");
		dataGridView2->Columns->Add("S", L"S(x)");
		dataGridView2->Columns->Add("F_S", L"|F - S|");
		dataGridView2->Columns->Add("dF", L"F'(x)");
		dataGridView2->Columns->Add("dS", L"S'(x)");
		dataGridView2->Columns->Add("dF_dS", L"|F' - S'|");
		dataGridView2->Columns->Add("ddF", L"F''(x)");
		dataGridView2->Columns->Add("ddS", L"S''(x)");
		dataGridView2->Columns->Add("ddF_ddS", L"|F'' - S''|");
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





































	private: System::Windows::Forms::DataGridView^ dataGridView2;






















	private: System::Windows::Forms::Label^ labelTestInfo;











	private: System::Windows::Forms::TextBox^ textBox15;



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




	private: System::Windows::Forms::Label^ label20;
	private: System::Windows::Forms::Label^ label21;
	private: System::Windows::Forms::Label^ label22;

	private: System::Windows::Forms::Label^ label24;
	private: System::Windows::Forms::Label^ label23;







	private: System::Windows::Forms::Label^ label32;
	private: System::Windows::Forms::Label^ label33;
































	private: ZedGraph::ZedGraphControl^ zedGraphControl3;
	private: ZedGraph::ZedGraphControl^ zedGraphControl2;
	private: System::Windows::Forms::Label^ label36;
	private: System::Windows::Forms::Label^ label3;
private: System::Windows::Forms::RadioButton^ radioButton1;
private: System::Windows::Forms::RadioButton^ radioButton2;
private: System::Windows::Forms::RadioButton^ radioButton3;
private: System::Windows::Forms::Label^ label4;
private: System::Windows::Forms::Label^ label7;
private: System::Windows::Forms::Label^ label5;
private: System::Windows::Forms::Label^ label6;
private: System::Windows::Forms::Label^ label8;
private: System::Windows::Forms::Label^ label9;
private: System::Windows::Forms::Label^ label10;
private: System::Windows::Forms::Label^ label11;
private: System::Windows::Forms::Label^ label12;












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
			this->labelTestInfo = (gcnew System::Windows::Forms::Label());
			this->textBox15 = (gcnew System::Windows::Forms::TextBox());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->label22 = (gcnew System::Windows::Forms::Label());
			this->label23 = (gcnew System::Windows::Forms::Label());
			this->label24 = (gcnew System::Windows::Forms::Label());
			this->label32 = (gcnew System::Windows::Forms::Label());
			this->label33 = (gcnew System::Windows::Forms::Label());
			this->zedGraphControl3 = (gcnew ZedGraph::ZedGraphControl());
			this->zedGraphControl2 = (gcnew ZedGraph::ZedGraphControl());
			this->label36 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton3 = (gcnew System::Windows::Forms::RadioButton());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView2))->BeginInit();
			this->SuspendLayout();
			// 
			// zedGraphControl1
			// 
			this->zedGraphControl1->Location = System::Drawing::Point(1673, 45);
			this->zedGraphControl1->Margin = System::Windows::Forms::Padding(6, 7, 6, 7);
			this->zedGraphControl1->Name = L"zedGraphControl1";
			this->zedGraphControl1->ScrollGrace = 0;
			this->zedGraphControl1->ScrollMaxX = 0;
			this->zedGraphControl1->ScrollMaxY = 0;
			this->zedGraphControl1->ScrollMaxY2 = 0;
			this->zedGraphControl1->ScrollMinX = 0;
			this->zedGraphControl1->ScrollMinY = 0;
			this->zedGraphControl1->ScrollMinY2 = 0;
			this->zedGraphControl1->Size = System::Drawing::Size(876, 456);
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
			this->dataGridView1->Size = System::Drawing::Size(995, 320);
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
			this->ZoomButton->Location = System::Drawing::Point(1376, 267);
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
			// dataGridView2
			// 
			this->dataGridView2->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView2->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(10) {
				this->dataGridViewTextBoxColumn1,
					this->dataGridViewTextBoxColumn2, this->dataGridViewTextBoxColumn3, this->dataGridViewTextBoxColumn4, this->dataGridViewTextBoxColumn5,
					this->dataGridViewTextBoxColumn6, this->dataGridViewTextBoxColumn7, this->dataGridViewTextBoxColumn8, this->dataGridViewTextBoxColumn9,
					this->dataGridViewTextBoxColumn12
			});
			this->dataGridView2->Location = System::Drawing::Point(19, 933);
			this->dataGridView2->Margin = System::Windows::Forms::Padding(5, 6, 5, 6);
			this->dataGridView2->Name = L"dataGridView2";
			this->dataGridView2->RowHeadersVisible = false;
			this->dataGridView2->RowHeadersWidth = 51;
			this->dataGridView2->Size = System::Drawing::Size(1581, 362);
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
			// label21
			// 
			this->label21->AccessibleName = L"";
			this->label21->AutoSize = true;
			this->label21->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label21->Location = System::Drawing::Point(46, 28);
			this->label21->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(203, 25);
			this->label21->TabIndex = 58;
			this->label21->Text = L"Тестовая функция";
			// 
			// label22
			// 
			this->label22->AccessibleName = L"";
			this->label22->AutoSize = true;
			this->label22->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label22->Location = System::Drawing::Point(147, 87);
			this->label22->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label22->Name = L"label22";
			this->label22->Size = System::Drawing::Size(149, 20);
			this->label22->TabIndex = 59;
			this->label22->Text = L"x³+3x², x ∈ [-1,0]";
			this->label22->Click += gcnew System::EventHandler(this, &MyForm::label22_Click);
			// 
			// label23
			// 
			this->label23->AccessibleName = L"";
			this->label23->AutoSize = true;
			this->label23->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label23->Location = System::Drawing::Point(147, 130);
			this->label23->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label23->Name = L"label23";
			this->label23->Size = System::Drawing::Size(160, 20);
			this->label23->TabIndex = 60;
			this->label23->Text = L"-x³+3x², , x ∈ [0,1]";
			this->label23->Click += gcnew System::EventHandler(this, &MyForm::label23_Click);
			// 
			// label24
			// 
			this->label24->AccessibleName = L"";
			this->label24->BackColor = System::Drawing::Color::Transparent;
			this->label24->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 48, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label24->Location = System::Drawing::Point(78, 60);
			this->label24->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label24->Name = L"label24";
			this->label24->Size = System::Drawing::Size(61, 131);
			this->label24->TabIndex = 61;
			this->label24->Text = L"{";
			this->label24->Click += gcnew System::EventHandler(this, &MyForm::label24_Click);
			// 
			// label32
			// 
			this->label32->AccessibleName = L"";
			this->label32->AutoSize = true;
			this->label32->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label32->Location = System::Drawing::Point(14, 113);
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
			this->label33->Size = System::Drawing::Size(107, 25);
			this->label33->TabIndex = 70;
			this->label33->Text = L"Таблицы ";
			this->label33->Click += gcnew System::EventHandler(this, &MyForm::label33_Click);
			// 
			// zedGraphControl3
			// 
			this->zedGraphControl3->Location = System::Drawing::Point(1673, 943);
			this->zedGraphControl3->Margin = System::Windows::Forms::Padding(6, 7, 6, 7);
			this->zedGraphControl3->Name = L"zedGraphControl3";
			this->zedGraphControl3->ScrollGrace = 0;
			this->zedGraphControl3->ScrollMaxX = 0;
			this->zedGraphControl3->ScrollMaxY = 0;
			this->zedGraphControl3->ScrollMaxY2 = 0;
			this->zedGraphControl3->ScrollMinX = 0;
			this->zedGraphControl3->ScrollMinY = 0;
			this->zedGraphControl3->ScrollMinY2 = 0;
			this->zedGraphControl3->Size = System::Drawing::Size(876, 456);
			this->zedGraphControl3->TabIndex = 33;
			// 
			// zedGraphControl2
			// 
			this->zedGraphControl2->Location = System::Drawing::Point(1673, 493);
			this->zedGraphControl2->Margin = System::Windows::Forms::Padding(6, 7, 6, 7);
			this->zedGraphControl2->Name = L"zedGraphControl2";
			this->zedGraphControl2->ScrollGrace = 0;
			this->zedGraphControl2->ScrollMaxX = 0;
			this->zedGraphControl2->ScrollMaxY = 0;
			this->zedGraphControl2->ScrollMaxY2 = 0;
			this->zedGraphControl2->ScrollMinX = 0;
			this->zedGraphControl2->ScrollMinY = 0;
			this->zedGraphControl2->ScrollMinY2 = 0;
			this->zedGraphControl2->Size = System::Drawing::Size(876, 456);
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
			// radioButton1
			// 
			this->radioButton1->AutoSize = true;
			this->radioButton1->Checked = true;
			this->radioButton1->Location = System::Drawing::Point(371, 97);
			this->radioButton1->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(110, 26);
			this->radioButton1->TabIndex = 75;
			this->radioButton1->TabStop = true;
			this->radioButton1->Text = L"Тестовая";
			this->radioButton1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->radioButton1->UseVisualStyleBackColor = true;
			// 
			// radioButton2
			// 
			this->radioButton2->AutoSize = true;
			this->radioButton2->Location = System::Drawing::Point(371, 293);
			this->radioButton2->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->radioButton2->Name = L"radioButton2";
			this->radioButton2->Size = System::Drawing::Size(114, 26);
			this->radioButton2->TabIndex = 76;
			this->radioButton2->Text = L"Основная";
			this->radioButton2->UseVisualStyleBackColor = true;
			// 
			// radioButton3
			// 
			this->radioButton3->AutoSize = true;
			this->radioButton3->Location = System::Drawing::Point(371, 441);
			this->radioButton3->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->radioButton3->Name = L"radioButton3";
			this->radioButton3->Size = System::Drawing::Size(172, 26);
			this->radioButton3->TabIndex = 77;
			this->radioButton3->Text = L"Осциллирующая";
			this->radioButton3->UseVisualStyleBackColor = true;
			// 
			// label4
			// 
			this->label4->AccessibleName = L"";
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label4->Location = System::Drawing::Point(6, 292);
			this->label4->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(69, 29);
			this->label4->TabIndex = 81;
			this->label4->Text = L"F(x)=";
			// 
			// label7
			// 
			this->label7->AccessibleName = L"";
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label7->Location = System::Drawing::Point(100, 261);
			this->label7->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(96, 60);
			this->label7->TabIndex = 78;
			this->label7->Text = L"√(x² - 1)\r\n —————————\r\n      x\r\n";
			// 
			// label5
			// 
			this->label5->AccessibleName = L"";
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label5->Location = System::Drawing::Point(228, 292);
			this->label5->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(84, 20);
			this->label5->TabIndex = 82;
			this->label5->Text = L" x ∈ [2,4]";
			// 
			// label6
			// 
			this->label6->AccessibleName = L"";
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label6->Location = System::Drawing::Point(91, 216);
			this->label6->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(115, 25);
			this->label6->TabIndex = 83;
			this->label6->Text = L"Основная ";
			// 
			// label8
			// 
			this->label8->AccessibleName = L"";
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label8->Location = System::Drawing::Point(45, 358);
			this->label8->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(181, 25);
			this->label8->TabIndex = 87;
			this->label8->Text = L"Осциллирующая";
			// 
			// label9
			// 
			this->label9->AccessibleName = L"";
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label9->Location = System::Drawing::Point(214, 481);
			this->label9->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(84, 20);
			this->label9->TabIndex = 86;
			this->label9->Text = L" x ∈ [2,4]";
			// 
			// label10
			// 
			this->label10->AccessibleName = L"";
			this->label10->AutoSize = true;
			this->label10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label10->Location = System::Drawing::Point(-1, 429);
			this->label10->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(69, 29);
			this->label10->TabIndex = 85;
			this->label10->Text = L"F(x)=";
			// 
			// label11
			// 
			this->label11->AccessibleName = L"";
			this->label11->AutoSize = true;
			this->label11->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label11->Location = System::Drawing::Point(92, 399);
			this->label11->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(96, 60);
			this->label11->TabIndex = 84;
			this->label11->Text = L"√(x² - 1)\r\n —————————\r\n      x\r\n";
			// 
			// label12
			// 
			this->label12->AccessibleName = L"";
			this->label12->AutoSize = true;
			this->label12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label12->Location = System::Drawing::Point(220, 429);
			this->label12->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(79, 20);
			this->label12->TabIndex = 88;
			this->label12->Text = L"+cos10x";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(10, 22);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(2564, 1415);
			this->Controls->Add(this->label12);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->label9);
			this->Controls->Add(this->label10);
			this->Controls->Add(this->label11);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->radioButton3);
			this->Controls->Add(this->radioButton2);
			this->Controls->Add(this->radioButton1);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label36);
			this->Controls->Add(this->label33);
			this->Controls->Add(this->label32);
			this->Controls->Add(this->label23);
			this->Controls->Add(this->label24);
			this->Controls->Add(this->label22);
			this->Controls->Add(this->label21);
			this->Controls->Add(this->label20);
			this->Controls->Add(this->label18);
			this->Controls->Add(this->textBox15);
			this->Controls->Add(this->labelTestInfo);
			this->Controls->Add(this->dataGridView2);
			this->Controls->Add(this->zedGraphControl3);
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
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView2))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: void DrawTask() {
		// 1. Подготовка панели графика (используем только zedGraphControl1)
		GraphPane^ pane1 = zedGraphControl1->GraphPane;
		pane1->CurveList->Clear();

		pane1->Title->Text = L"Решение краевой задачи";
		pane1->XAxis->Title->Text = L"x";
		pane1->YAxis->Title->Text = L"v(x)";

		// Очищаем остальные графики, чтобы они не мешали
		zedGraphControl2->GraphPane->CurveList->Clear();
		zedGraphControl2->AxisChange(); zedGraphControl2->Invalidate();
		zedGraphControl3->GraphPane->CurveList->Clear();
		zedGraphControl3->AxisChange(); zedGraphControl3->Invalidate();

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

		// 5. Отрисовка на одном графике (zedGraphControl1)
		float curveWidth = 2.0f;
		float nodeSize = 5.0f;

		LineItem^ curve_v = pane1->AddCurve(L"v(x) (шаг h)", v_list, Color::Blue, SymbolType::Circle);
		curve_v->Line->Width = curveWidth;
		curve_v->Symbol->Size = nodeSize;
		curve_v->Symbol->Fill->Type = FillType::Solid;

		LineItem^ curve_v2 = pane1->AddCurve(L"v2(x) (шаг h/2)", v2_list, Color::Red, SymbolType::None);
		curve_v2->Line->Width = curveWidth;
		curve_v2->Line->Style = System::Drawing::Drawing2D::DashStyle::Dash;

		LineItem^ curve_diff = pane1->AddCurve(L"Разность v(x) - v2(x)", diff_list, Color::Green, SymbolType::Square);
		curve_diff->Line->Width = curveWidth;
		curve_diff->Symbol->Size = nodeSize;
		curve_diff->Symbol->Fill->Type = FillType::Solid;

		zedGraphControl1->AxisChange();
		zedGraphControl1->Invalidate();

		// 6. === ЗАПОЛНЕНИЕ ТАБЛИЦЫ ===
		// Пересоздаем нужные столбцы
		dataGridView1->Columns->Clear();
		dataGridView1->Columns->Add("NodeIndex", L"№ узла");
		dataGridView1->Columns->Add("Xi", L"x_i");
		dataGridView1->Columns->Add("Vi", L"v(x_i)");
		dataGridView1->Columns->Add("V2i", L"v2(x_2i)");
		dataGridView1->Columns->Add("Diff", L"v(x_i) - v2(x_2i)");

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
				Math::Round(out_grid[i], 5),
				Math::Round(vi[i], 5),
				Math::Round(v2i[2 * i], 5),
				diff.ToString("E5") // Экспоненциальный формат лучше подходит для малых разностей
			);
		}

		// Очищаем вторую таблицу, так как для этой задачи она не нужна
		dataGridView2->Rows->Clear();

		// 7. Обновление текстовой информации
		String^ infoText = L"Решение краевой задачи\r\n";
		infoText += L"Число сегментов (целый шаг): n = " + n + L"\r\n\r\n";
		infoText += L"Максимальная разность |v(x) - v2(x)| = " + max_diff.ToString("E5") + L"\r\n";
		infoText += L"Достигается в узле x = " + Math::Round(x_max_diff, 5);

		labelTestInfo->Text = infoText;
	}

		   // Событие OnClick для кнопки Draw
private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	try {
		// Вызываем новую функцию отрисовки без старых параметров
		DrawTask();
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
		double xmin = Convert::ToDouble(textBox1->Text);
		double xmax = Convert::ToDouble(textBox2->Text);

		array<ZedGraph::ZedGraphControl^>^ controls = { zedGraphControl1, zedGraphControl2, zedGraphControl3 };

		for (int i = 0; i < controls->Length; i++) {
			GraphPane^ pane = controls[i]->GraphPane;

			// Настройка множителей (Mag), чтобы не было проблем с порядками величин
			pane->XAxis->Scale->MagAuto = true;
			pane->YAxis->Scale->MagAuto = true;

			if (0) {
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