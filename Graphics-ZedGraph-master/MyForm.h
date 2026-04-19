#pragma once
#include <math.h>
#include <vector>
#include <functional>












// ============ ТЕСТОВАЯ ЗАДАЧА ============
		// точное решение тестовой задачи






static std::function<double(double)> createSplineFunction(
	const std::vector<double>& grid_x,      // узлы
	const std::vector<double>& a,      // коэффициенты ai
	const std::vector<double>& b,      // коэффициенты bi
	const std::vector<double>& c,      // коэффициенты ci
	const std::vector<double>& d       // коэффициенты di
) {
	// Захватываем все векторы по значению
	return [grid_x, a, b, c, d](double x) -> double {

		//System::Diagnostics::Debug::WriteLine(grid_x.front() + " | " + x + " | " + grid_x.back());
		if (x < grid_x.front() || grid_x.back() < x) {
			if (x > grid_x.back() + 0.01) {
				throw "x is out of bounds [a,b]";
			}
			x = grid_x.back();
		}


		//  x_i-1 <= x <= x_i
		int i = 1;
		while (!(grid_x[i - 1] <= x && x <= grid_x[i]) && i < grid_x.size()) {
			i++;
		}



		double dx = x - grid_x[i];  // (x - xi)

		// S(x) = ai + bi*dx + (ci/2)*dx^2 + (di/6)*dx^3
		return a[i - 1] + b[i - 1] * dx + c[i] / 2.0 * dx * dx + d[i - 1] / 6.0 * dx * dx * dx;
		};
}

// сетка постоянная == есть формула адаптированная под кубич сплайн с пост шагом
// для решения трехдиаг системы - нужно использовать метод прогонки
// можно юзать адаптированные формулы которые показвыал С.А.
// есть 3 задачи
// 1 - тестовая функция
// надо найти сплайн который интерполирует функцию F(x)
// 1) F(x) = фи(x)
// Мы находим всегда сплайн с естественными граничными усл
// ( фи(х) в первой задаче - сплайн с естетвенными граничными усл
// причем сплайн на опред сетке с опред граничн усл - существует и единственен
// сама функция - сплайн - поэтому надо построить сплайн (определить все коэфф)
// и проверить (раскрыть скобки и сравнить с тем,что получаем)
// n = 2 - число участков разбиения [a,b] , кол-во узлов n+1
// 
// 2) F(x) = f(x)
// у нас первый вариант - смотрим f(x) под номером №1 в конце файла
// 
// 3) к функции нашего варианта добавляем +cos(10x) и строим сплайн 
// на равномерной сетке с пост шагом с естеств граничн усл
// 
// 
// 
// 
//

	// для этой тестовой функции в отчете 
	// нужно написать коэффициенты ai,bi,ci,di
	// раскрыть скобки
	// получить ту же самую функцию
	// (должно совпасть при n = 2)

static double fi(double x) {
	double a = -1;
	double b = 1;
	if (x < a || x > b) {
		throw "Function is not defined out of [a,b]";
	}

	if (-1 <= x && x <= 0) {
		return x * x * x + 3 * x * x;
	}

	if (0 <= x && x <= 1) {
		return -x * x * x + 3 * x * x;
	}

	return -9999999999;
}


static double fi_d1(double x) { // Первая производная
	if (x < -1 || x > 1) throw "Out of bounds";
	if (x <= 0) return 3 * x * x + 6 * x;
	return -3 * x * x + 6 * x;
}

static double fi_d2(double x) { // Вторая производная
	if (x < -1 || x > 1) throw "Out of bounds";
	if (x <= 0) return 6 * x + 6;
	return -6 * x + 6;
}



static std::function<double(double)> makeSpline(std::function<double(double)> F,
	double a_edge, double b_edge, double n, double mu1, double mu2,
	std::vector<double>& out_a, std::vector<double>& out_b,
	std::vector<double>& out_c, std::vector<double>& out_d, std::vector<double>& out_grid) {

	// F(x) - сама функция которую интерполируем
	// double a,b - левая и правая границы
	// n - кол-во интервалов разбиения отрезка [a,b] (узлов сетки n+1)
	// mu1, mu2 - граничные условия (у нас: mu1=mu2=0)

	double h = (b_edge - a_edge) / n; // постоянный шаг

	std::vector<double> F_values(n + 1);
	std::vector<double> grid_values(n + 1);

	// gn - greed node (узел сетки)
	double gn = a_edge;
	for (int i = 0; i < n + 1; i++) {

		if (gn > b_edge) {
			throw "This leads to fall in case: fi,[-1,1] , gn over 1";
		}

		F_values[i] = F(gn);
		grid_values[i] = gn;



		gn += h;
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


	for (int i = 0; i <= n - 2; i++) {
		double fxxi = (F_values[i + 1 + 1] - 2 * F_values[i + 1] + F_values[i - 1 + 1]) / (h * h);

		alpha[i + 1] = -1 / (4 + alpha[i]);
		betta[i + 1] = (6 * fxxi - betta[i]) / (4 + alpha[i]);
	}

	// double kappa2 = 0; не нужен (у нас c[n] = 0)

	for (int i = n - 1; i >= 1; i--) {
		// c_n-1 =    alph_n      *    c_n      +   betta_n   ???
		// c[n-2] = alpha[n-1]    *   c[n-1]    +  betta[n-1] ???
		c[i] = alpha[i] * c[i] + betta[i];
	}

	std::vector<double> a(n);
	std::vector<double> d(n);
	std::vector<double> b(n);

	for (int i = 0; i < n; i++) {
		a[i] = F_values[i + 1];
		d[i] = (c[i + 1] - c[i]) / h;
		b[i] = (F_values[i + 1] - F_values[i]) / h + c[i + 1] * h / 3.0 + c[i] * h / 6.0;
	}

	// now all coeffs ai,bi,ci,di - found
	// now cubic Spline is
	//         {  Si(x) = ai + bi*(x-xi)+ci/2 * (x-xi)^2 + di/6 * (x-xi)^3
	// S(x) =  {
	//         {  xi from [x_i-1, x_i]

	// now need to create labda which will represent cubic Spline logic

	out_a = a; out_b = b; out_c = c; out_d = d; out_grid = grid_values;
	return createSplineFunction(grid_values, a, b, c, d);
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



	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::TextBox^ textBox2;









	private: System::Windows::Forms::Button^ ZoomButton;














	private: System::Windows::Forms::ToolTip^ toolTip1;





































	private: System::Windows::Forms::DataGridView^ dataGridView2;






















	private: System::Windows::Forms::Label^ labelTestInfo;
	private: System::Windows::Forms::Label^ labelMainInfo;










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































	private: ZedGraph::ZedGraphControl^ zedGraphControl4;
	private: ZedGraph::ZedGraphControl^ zedGraphControl3;
	private: ZedGraph::ZedGraphControl^ zedGraphControl2;
	private: System::Windows::Forms::Label^ label36;
	private: System::Windows::Forms::Label^ label3;












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
			this->label1 = (gcnew System::Windows::Forms::Label());
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
			this->labelMainInfo = (gcnew System::Windows::Forms::Label());
			this->textBox15 = (gcnew System::Windows::Forms::TextBox());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->label22 = (gcnew System::Windows::Forms::Label());
			this->label23 = (gcnew System::Windows::Forms::Label());
			this->label24 = (gcnew System::Windows::Forms::Label());
			this->label32 = (gcnew System::Windows::Forms::Label());
			this->label33 = (gcnew System::Windows::Forms::Label());
			this->zedGraphControl4 = (gcnew ZedGraph::ZedGraphControl());
			this->zedGraphControl3 = (gcnew ZedGraph::ZedGraphControl());
			this->zedGraphControl2 = (gcnew ZedGraph::ZedGraphControl());
			this->label36 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView2))->BeginInit();
			this->SuspendLayout();
			// 
			// zedGraphControl1
			// 
			this->zedGraphControl1->Location = System::Drawing::Point(35, 318);
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
			this->button1->Location = System::Drawing::Point(792, 82);
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
			this->dataGridView1->Location = System::Drawing::Point(32, 776);
			this->dataGridView1->Margin = System::Windows::Forms::Padding(4);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->RowHeadersVisible = false;
			this->dataGridView1->RowHeadersWidth = 51;
			this->dataGridView1->Size = System::Drawing::Size(681, 233);
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
			this->label1->Location = System::Drawing::Point(189, 222);
			this->label1->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(15, 16);
			this->label1->TabIndex = 3;
			this->label1->Text = L"a";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(227, 222);
			this->textBox1->Margin = System::Windows::Forms::Padding(4);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(63, 22);
			this->textBox1->TabIndex = 4;
			this->textBox1->Text = L"0";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(298, 225);
			this->label2->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(15, 16);
			this->label2->TabIndex = 5;
			this->label2->Text = L"b";
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(312, 222);
			this->textBox2->Margin = System::Windows::Forms::Padding(4);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(64, 22);
			this->textBox2->TabIndex = 6;
			this->textBox2->Text = L"1";
			// 
			// ZoomButton
			// 
			this->ZoomButton->Location = System::Drawing::Point(792, 173);
			this->ZoomButton->Margin = System::Windows::Forms::Padding(4);
			this->ZoomButton->Name = L"ZoomButton";
			this->ZoomButton->Size = System::Drawing::Size(189, 36);
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
			this->dataGridView2->Location = System::Drawing::Point(32, 1033);
			this->dataGridView2->Margin = System::Windows::Forms::Padding(4);
			this->dataGridView2->Name = L"dataGridView2";
			this->dataGridView2->RowHeadersVisible = false;
			this->dataGridView2->RowHeadersWidth = 51;
			this->dataGridView2->Size = System::Drawing::Size(682, 263);
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
			this->labelTestInfo->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->labelTestInfo->Location = System::Drawing::Point(1151, 973);
			this->labelTestInfo->Name = L"labelTestInfo";
			this->labelTestInfo->Size = System::Drawing::Size(227, 16);
			this->labelTestInfo->TabIndex = 46;
			this->labelTestInfo->Text = L"Справка по тестовой задаче:";
			this->labelTestInfo->Click += gcnew System::EventHandler(this, &MyForm::labelTestInfo_Click);
			// 
			// labelMainInfo
			// 
			this->labelMainInfo->AutoSize = true;
			this->labelMainInfo->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->labelMainInfo->Location = System::Drawing::Point(1432, 973);
			this->labelMainInfo->Name = L"labelMainInfo";
			this->labelMainInfo->Size = System::Drawing::Size(229, 16);
			this->labelMainInfo->TabIndex = 47;
			this->labelMainInfo->Text = L"Справка по основной задаче:";
			// 
			// textBox15
			// 
			this->textBox15->Location = System::Drawing::Point(230, 193);
			this->textBox15->Margin = System::Windows::Forms::Padding(4);
			this->textBox15->Name = L"textBox15";
			this->textBox15->Size = System::Drawing::Size(80, 22);
			this->textBox15->TabIndex = 49;
			this->textBox15->Text = L"10";
			// 
			// label18
			// 
			this->label18->AccessibleName = L"";
			this->label18->AutoSize = true;
			this->label18->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label18->Location = System::Drawing::Point(32, 222);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(171, 16);
			this->label18->TabIndex = 52;
			this->label18->Text = L"Границы отрезка [a,b]";
			// 
			// label20
			// 
			this->label20->AccessibleName = L"";
			this->label20->AutoSize = true;
			this->label20->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->label20->Location = System::Drawing::Point(1212, 924);
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
			this->label21->Location = System::Drawing::Point(93, 20);
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
			this->label22->Location = System::Drawing::Point(170, 79);
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
			this->label23->Location = System::Drawing::Point(170, 110);
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
			this->label24->Location = System::Drawing::Point(126, 54);
			this->label24->Name = L"label24";
			this->label24->Size = System::Drawing::Size(49, 95);
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
			this->label32->Location = System::Drawing::Point(75, 92);
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
			this->label33->Location = System::Drawing::Point(209, 747);
			this->label33->Name = L"label33";
			this->label33->Size = System::Drawing::Size(280, 25);
			this->label33->TabIndex = 70;
			this->label33->Text = L"Таблицы тестовой задачи";
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
			// label36
			// 
			this->label36->AccessibleName = L"";
			this->label36->AutoSize = true;
			this->label36->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label36->Location = System::Drawing::Point(67, 193);
			this->label36->Name = L"label36";
			this->label36->Size = System::Drawing::Size(156, 16);
			this->label36->TabIndex = 73;
			this->label36->Text = L"Число сегментов (n)";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(208, 225);
			this->label3->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(15, 16);
			this->label3->TabIndex = 74;
			this->label3->Text = L"a";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(2499, 1380);
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
			this->Controls->Add(this->labelMainInfo);
			this->Controls->Add(this->labelTestInfo);
			this->Controls->Add(this->dataGridView2);
			this->Controls->Add(this->zedGraphControl4);
			this->Controls->Add(this->zedGraphControl3);
			this->Controls->Add(this->zedGraphControl2);
			this->Controls->Add(this->ZoomButton);
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
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView2))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private:
		




		// событие OnClick для кнопки Draw
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		// 1. Очистка графика
		GraphPane^ panel = zedGraphControl1->GraphPane;
		panel->CurveList->Clear();
		panel->Title->Text = L"Интерполяция кубическим сплайном";
		panel->XAxis->Title->Text = L"x";
		panel->YAxis->Title->Text = L"f(x) / S(x)";

		// 2. Считывание параметров
		double a = Convert::ToDouble(textBox1->Text);
		double b = Convert::ToDouble(textBox2->Text);
		int n = Convert::ToInt32(textBox15->Text); // Число разбиений

		// жесткие значения (для теста)
		/*double a = -1, b = 1;
		int n = 2;*/


		// 3. Построение сплайна
		// Вызываем вашу функцию makeSpline. 
		// Вместо лямбда-выражения передаем указатель на вашу функцию fi
		// Если makeSpline принимает std::function, это сработает.
		std::vector<double> a_v, b_v, c_v, d_v, grid_v;
		// Вызываем makeSpline с новыми параметрами-ссылками
		auto spline_func = makeSpline(fi, a, b, n, 0.0, 0.0, a_v, b_v, c_v, d_v, grid_v);

		// 4. Подготовка данных для отрисовки
		PointPairList^ exact_list = gcnew PointPairList();
		PointPairList^ spline_list = gcnew PointPairList();
		PointPairList^ nodes_list = gcnew PointPairList(); // Узлы интерполяции

		int points_count = 500; // Плотность отрисовки линий
		double step = (b - a) / points_count;

		for (int i = 0; i <= points_count; i++) {
			double x = a + i * step;

			// Считаем точную функцию
			exact_list->Add(x, fi(x));


			// Считаем сплайн
			spline_list->Add(x, spline_func(x));
		}

		// Отдельно добавим точки узлов сетки
		double h_nodes = (b - a) / n;
		for (int i = 0; i <= n; i++) {
			double x_node = a + i * h_nodes;
			nodes_list->Add(x_node, fi(x_node));
		}

		// 5. Отрисовка 
		// Рисуем точную функцию синей линией
		panel->AddCurve(L"Точная функция", exact_list, Color::Blue, SymbolType::None);

		// Рисуем сплайн красной линией
		LineItem^ s_curve = panel->AddCurve(L"Сплайн", spline_list, Color::Red, SymbolType::None);

		// ИСПРАВЛЕНИЕ ДЛЯ ZedGraph: стиль пунктирной линии задается через свойство Style
		s_curve->Line->Style = System::Drawing::Drawing2D::DashStyle::Dash;

		// Рисуем узлы в виде черных кружочков
		LineItem^ nodes_curve = panel->AddCurve(L"Узлы", nodes_list, Color::Black, SymbolType::Circle);
		nodes_curve->Line->IsVisible = false; // Отключаем соединительную линию для узлов
		nodes_curve->Symbol->Fill->Type = FillType::Solid; // Заливка кружков

		// Автомасштабирование и обновление
		zedGraphControl1->AxisChange();
		zedGraphControl1->Invalidate();


		// === ЗАПОЛНЕНИЕ ТАБЛИЦ ===
		dataGridView1->Rows->Clear();
		dataGridView2->Rows->Clear();


		// ЗАПОЛНЕНИЕ ТАБЛИЦЫ 1 (Коэффициенты)
		// n - это количество интервалов. Индексы в ваших векторах от 0 до n-1
		for (int i = 0; i < n; i++) {
			dataGridView1->Rows->Add(
				i + 1, // Номер интервала (от 1 до n)
				grid_v[i], // x_{i-1}
				grid_v[i + 1], // x_i
				Math::Round(a_v[i], 5),
				Math::Round(b_v[i], 5),
				Math::Round(c_v[i + 1], 5), // Ваша формула использует c[i] (сдвинутый)
				Math::Round(d_v[i], 5)
			);
		}

		// ЗАПОЛНЕНИЕ ТАБЛИЦЫ 2+3 (Значения в узлах и серединах)
		// Переменные для поиска максимальных погрешностей
		double max_err_f = -1.0, x_max_f = a;
		double max_err_d1 = -1.0, x_max_d1 = a;
		double max_err_d2 = -1.0, x_max_d2 = a;

		int N_points = 2 * n; // Точек в два раза больше (узлы + полуцелые точки)
		double step_table = (b - a) / N_points;

		for (int j = 0; j <= N_points; j++) {
			double x = a + j * step_table;

			// Точные значения
			double f_val = fi(x);
			double f_d1 = fi_d1(x);
			double f_d2 = fi_d2(x);

			// Значения сплайна
			double s_val = spline_func(x);

			// Вычисление производных сплайна вручную
			double s_d1 = 0, s_d2 = 0;
			// Ищем нужный интервал, как в лямбде
			int idx = 1;
			while (!(grid_v[idx - 1] <= x && x <= grid_v[idx]) && idx < grid_v.size() - 1) idx++;

			double dx = x - grid_v[idx]; // Смещение от ПРАВОЙ границы (по вашей логике)

			// S'(x) = b + c*dx + (d/2)*dx^2
			s_d1 = b_v[idx - 1] + c_v[idx] * dx + (d_v[idx - 1] / 2.0) * dx * dx;
			// S''(x) = c + d*dx
			s_d2 = c_v[idx] + d_v[idx - 1] * dx;

			// Добавляем строку
			dataGridView2->Rows->Add(
				j,
				Math::Round(x, 4),
				Math::Round(f_val, 5),
				Math::Round(s_val, 5),
				Math::Round(Math::Abs(f_val - s_val), 7), // |F - S|
				Math::Round(f_d1, 5),
				Math::Round(s_d1, 5),
				Math::Round(Math::Abs(f_d1 - s_d1), 7), // |F' - S'|
				Math::Round(f_d2, 5),
				Math::Round(s_d2, 5),
				Math::Round(Math::Abs(f_d2 - s_d2), 7)  // |F'' - S''|
			);

			// Вычисление текущих погрешностей
			double err_f = Math::Abs(f_val - s_val);
			double err_d1 = Math::Abs(f_d1 - s_d1);
			double err_d2 = Math::Abs(f_d2 - s_d2);

			// Поиск максимумов и точек, где они достигаются
			if (err_f > max_err_f) { max_err_f = err_f; x_max_f = x; }
			if (err_d1 > max_err_d1) { max_err_d1 = err_d1; x_max_d1 = x; }
			if (err_d2 > max_err_d2) { max_err_d2 = err_d2; x_max_d2 = x; }
		}

		// === ЗАПОЛНЕНИЕ labelTestInfo ===
		// Используем юникодные штрихи: ′ (U+2032) и ″ (U+2033)
		String^ infoText = "";
		infoText += L"Справка по тестовой задаче:\r\n";
		infoText += L"Сетка сплайна: n = " + n + L"\r\n";
		infoText += L"Контрольная сетка: N = " + N_points + L"\r\n\r\n";

		infoText += L"Погрешность сплайна на контрольной сетке\r\n";
		infoText += L"max |F(xⱼ) − S(xⱼ)| = " + max_err_f.ToString("G5") + L" при x = " + Math::Round(x_max_f, 4) + L"\r\n\r\n";

		infoText += L"Погрешность производной на контрольной сетке\r\n";
		infoText += L"max |F′(xⱼ) − S′(xⱼ)| = " + max_err_d1.ToString("G5") + L" при x = " + Math::Round(x_max_d1, 4) + L"\r\n\r\n";

		infoText += L"Погрешность второй производной на контрольной сетке (опция)\r\n";
		infoText += L"max |F″(xⱼ) − S″(xⱼ)| = " + max_err_d2.ToString("G5") + L" при x = " + Math::Round(x_max_d2, 4);

		// Присваиваем сформированный текст вашему элементу управления
		labelTestInfo->Text = infoText;
	}






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
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void labelTestInfo_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label20_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	}; // MyForm

} // namespace Graph