#pragma once
#include <math.h>
#include <vector>
#include <functional>
#include <omp.h>
#include <limits.h>
#include <fstream>
#include <string>

# define M_PI 3.14159265358979323846


static double mu1_func(double y, double a, double b) {
	double arg = sin(M_PI * a * y);
	return exp(arg*arg);

}


static double mu2_func(double y, double a, double b) {
	double arg = sin(M_PI * b * y);
	return exp(arg * arg);

}

static double mu3_func(double x, double c, double d) {
	double arg = sin(M_PI * c * x);
	return exp(arg * arg);
}

static double mu4_func(double x, double c, double d) {
	double arg = sin(M_PI * d * x);
	return exp(arg * arg);

}


static double u_star_func(double x, double y) {
	double arg = sin(M_PI * x * y);
	return exp(arg * arg);

}

static double f_xy_func(double x, double y) {
	double arg = sin(M_PI * x * y);
	
	return -(x * x + y * y) *
		M_PI * M_PI *
		exp(arg * arg) *
		(sin(2 * M_PI * x * y) * sin(2 * M_PI * x * y)
			+
			2 * cos(2 * M_PI * x * y));

}


static void MBP(
	double w,
	double h, double k,
	int n, int m,
	std::vector<double>& x,
	std::vector<double>& y,
	std::vector<std::vector<double>>& V) {
	double hh = h * h;
	double kk = k * k;
	double A = -2 * (1 / hh + 1 / kk);

	for (int i = 1; i < n; ++i) {
		for (int j = 1; j < m; ++j) {
			double arg = f_xy_func(x[i], y[j])
				+ 1 / hh * V[i - 1][j]
				+ 1 / hh * V[i + 1][j]
				+ 1 / kk * V[i][j - 1]
				+ 1 / kk * V[i][j + 1];
			V[i][j] = -1 / A * ((1-w)*(-A)*V[i][j] + w * arg);
		}
	}

}



// ++ ещё на контрольной сетке сделать
// (для оценки погрешности решения СЛАУ)
// основная сетка (n,m)
// дополнительная (2n,2m)
// хотя для тестовой вроде не надо?


// eps = 0.5 * 10^-6 - задается с Box (UI)
// погрешнось eps1 = max |u*(xi,yj)-v(xi,yj)|
// макс отклонение в x_max, y_max
// n = ... m = ... (задает пользователь)
// w = .. (мне не надо у меня Зейдель, хотя Зейдель это w=1)
// eps_метода = (задает пользователь)    N_max = (задает пользоваль)
// N = ... (кол-во итераций, возвращается функцией)
// точность eps_N = ||x_S - x_S-1||
// невязка ||R_N|| = ||A*V_N - F|| 
// использована норма max|R_N(i)|
// погрешность решения СЛАУ ||Z_N||inf <= ||Z_N||2  <=.. (нужно оценить норму погрешности по невязке)
// погрешность схемы оценивается как ||z||inf <= ... ( оценить норму по Т о сх-ти схемы)
// использована норма ||z||inf = ...
// общая погрешность решения тестовой задачи ||z_общ||inf <= ... (оценить через нормы её компонент, вычислит погршен не учитывать)
// использована норма ||z_общ||inf = ... 
// + выписать определения для всех норм

// таблицы 3 штуки: (u*, V_N, u*(x,y) - V_N(x,y))
// u* , V, difference - все возвращает функция.

// графики: u*, V_N, разность
// возвращаются узлы - поэтому всё можно

// Справка для тестовой задачи:
// n,m, w = 1, eps_метода, N_max - задает пользователь (кроме w)
// затрачено итераций N = ... (считает функция), eps_N = ||x_S - x_S-1|| (по сути тоже считает функция)
// невязка || R_N || = || A * V_N - F ||
// использована норма max|R_N(i)|
// Тестовая задача дб решена с eps=0.5*10^-6, решена с eps1 = max |u*(xi,yj)-v(xi,yj)| (может возвращать функция)
// макс отклонение от точного и числ решения в x_max, y_max (можно их тоже возвращать функцией)
// начальное приближение: линейная интерполяция по x (это нужно сделать в функции, это не возвращается, просто что дб в функции)

static void solveDirichleForPuasson(
	double a, double b,
	double c, double d,
	int n,
	int m,
	double eps_met, double Nmax,
	double omega,
	std::vector<std::vector<double>>& u_star,
	std::vector<std::vector<double>>& V,
	std::vector<std::vector<double>>& difference,
	int& iter_count,      // N
	double& eps_N,        // Достигнута точность метода ||v^s - v^s-1||
	double& eps_1,        // Погрешность задачи max|u* - v|
	double& x_max_err,    // x, где max погрешность
	double& y_max_err,    // y, где max погрешность
	double& R_norm        // Норма невязки ||R||
)
{

	// шаги
	double h = (b - a) / n;
	double k = (d - c) / m;


	// узлы сетки
	std::vector<double> x(n + 1);
	std::vector<double> y(m + 1);
	for (int i = 0; i < n+1; i++) {
		x[i] = a + i * h;
	}
	for (int j = 0; j < m+1; j++) {
		y[j] = c + j * k;
	}

	
	// u_star
	for (int i = 0; i < n+1; ++i) {
		for (int j = 0; j < m+1; ++j) {
			u_star[i][j] = u_star_func(x[i],y[j]);
		}
	}



	// решение
	// std::vector<std::vector<double>> V((n + 1), std::vector<double>(m+1,1.0));

	// ========== граничные условия (начало) 
	// !!!!! вообще должна быть линейная интерполяция граничных условий
	// а это разве не линейная интерполяция?
	for (int j = 1; j <= m - 1; j++) {
		double yj = c + j * k;
		V[0][j] = mu1_func(yj,a,b);
		V[n][j] = mu2_func(yj,a,b);
	}

	for (int i = 1; i <= n - 1; i++) {
		double xi = a+ i * h;
		V[i][0] = mu3_func(xi,c,d);
		V[i][m] = mu4_func(xi,c,d);
	}
	// ========== граничные условия (конец)

	
	bool flag = true;
	int count = 0;
	double max_diff_;
	std::vector<std::vector<double>> V_prev;
	while (flag) {
		eps_N = -1;
		V_prev = V;
		MBP(omega,h,k,n,m,x,y,V);
		count++;


		// выход по числу итераций
		if (count >= Nmax) {
			iter_count = count;
			flag = false;
		}

		// поиск точности eps_S
		for (int i = 0; i < n+1; ++i) {
			for (int j = 0; j < m + 1; ++j) {
				eps_N = std::max(eps_N, abs(V[i][j]-V_prev[i][j]));
			}
		}

		// выход по точности
		if (eps_N < eps_met) {
			iter_count = count;
			flag = false;
		}

	}

	double max_err = -1;
	for (int i = 0; i < n + 1; ++i) {
		for (int j = 0; j < m + 1; ++j) {
			difference[i][j] = u_star[i][j] - V[i][j];
			if (max_err < difference[i][j]) {
				max_err = difference[i][j];
				x_max_err = x[i];
				y_max_err = y[j];
			}
		}
	}
	eps_1 = max_err;


	
	double hh = h * h;
	double kk = k * k;
	R_norm = -1;
	for (int i = 1; i < n-1; ++i) {
		for (int j = 1; j < m - 1; ++j) {
			double R = (V[i + 1][j] - 2 * V[i][j] + V[i - 1][j]) / hh + (V[i][j + 1] - 2 * V[i][j] + V[i][j - 1]) / kk + f_xy_func(x[i],y[j]);
			R_norm = std::max(R_norm,R);
		}
	}

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

	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::DataGridView^ dataGridView1;




	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::TextBox^ textBox2;
























	private: System::Windows::Forms::ToolTip^ toolTip1;




























































	private: System::Windows::Forms::Label^ labelTestInfo;
private: System::Windows::Forms::TextBox^ textBoxN;















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
private: System::Windows::Forms::TextBox^ textBoxM;
private: System::Windows::Forms::Label^ label1;
private: System::Windows::Forms::TextBox^ textBoxEps;
private: System::Windows::Forms::Label^ label4;
private: System::Windows::Forms::TextBox^ textBoxNmax;
private: System::Windows::Forms::TextBox^ textBoxOmega;
private: System::Windows::Forms::Label^ label5;
private: System::Windows::Forms::Label^ label6;
private: System::Windows::Forms::Label^ label7;
private: System::Windows::Forms::Label^ label8;
private: System::Windows::Forms::TextBox^ textBox3;
private: System::Windows::Forms::Label^ label9;
private: System::Windows::Forms::TextBox^ textBox4;
















































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
			this->toolTip1 = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->labelTestInfo = (gcnew System::Windows::Forms::Label());
			this->textBoxN = (gcnew System::Windows::Forms::TextBox());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->label32 = (gcnew System::Windows::Forms::Label());
			this->label33 = (gcnew System::Windows::Forms::Label());
			this->label36 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->textBoxM = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBoxEps = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->textBoxNmax = (gcnew System::Windows::Forms::TextBox());
			this->textBoxOmega = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(167, 823);
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
			this->dataGridView1->Location = System::Drawing::Point(1074, 64);
			this->dataGridView1->Margin = System::Windows::Forms::Padding(5, 6, 5, 6);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->RowHeadersVisible = false;
			this->dataGridView1->RowHeadersWidth = 51;
			this->dataGridView1->Size = System::Drawing::Size(1455, 1247);
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
			this->textBox1->Location = System::Drawing::Point(337, 723);
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
			this->label2->Location = System::Drawing::Point(421, 721);
			this->label2->Margin = System::Windows::Forms::Padding(5, 0, 5, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(27, 29);
			this->label2->TabIndex = 5;
			this->label2->Text = L"b";
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(458, 723);
			this->textBox2->Margin = System::Windows::Forms::Padding(5, 6, 5, 6);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(79, 28);
			this->textBox2->TabIndex = 6;
			this->textBox2->Text = L"1";
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
			this->labelTestInfo->Location = System::Drawing::Point(98, 978);
			this->labelTestInfo->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelTestInfo->Name = L"labelTestInfo";
			this->labelTestInfo->Size = System::Drawing::Size(208, 25);
			this->labelTestInfo->TabIndex = 46;
			this->labelTestInfo->Text = L"Справка по задаче:";
			this->labelTestInfo->Click += gcnew System::EventHandler(this, &MyForm::labelTestInfo_Click);
			// 
			// textBoxN
			// 
			this->textBoxN->Location = System::Drawing::Point(339, 465);
			this->textBoxN->Margin = System::Windows::Forms::Padding(5, 6, 5, 6);
			this->textBoxN->Name = L"textBoxN";
			this->textBoxN->Size = System::Drawing::Size(99, 28);
			this->textBoxN->TabIndex = 49;
			this->textBoxN->Text = L"100";
			// 
			// label18
			// 
			this->label18->AccessibleName = L"";
			this->label18->AutoSize = true;
			this->label18->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label18->Location = System::Drawing::Point(69, 723);
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
			this->label20->Location = System::Drawing::Point(107, 912);
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
			this->label33->Location = System::Drawing::Point(1910, 33);
			this->label33->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label33->Name = L"label33";
			this->label33->Size = System::Drawing::Size(103, 25);
			this->label33->TabIndex = 70;
			this->label33->Text = L"Таблица ";
			this->label33->Click += gcnew System::EventHandler(this, &MyForm::label33_Click);
			// 
			// label36
			// 
			this->label36->AccessibleName = L"";
			this->label36->AutoSize = true;
			this->label36->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label36->Location = System::Drawing::Point(71, 474);
			this->label36->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label36->Name = L"label36";
			this->label36->Size = System::Drawing::Size(217, 22);
			this->label36->TabIndex = 73;
			this->label36->Text = L"Число разбиений по X";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label3->Location = System::Drawing::Point(309, 721);
			this->label3->Margin = System::Windows::Forms::Padding(5, 0, 5, 0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(26, 29);
			this->label3->TabIndex = 74;
			this->label3->Text = L"a";
			// 
			// textBoxM
			// 
			this->textBoxM->Location = System::Drawing::Point(339, 524);
			this->textBoxM->Margin = System::Windows::Forms::Padding(5, 6, 5, 6);
			this->textBoxM->Name = L"textBoxM";
			this->textBoxM->Size = System::Drawing::Size(99, 28);
			this->textBoxM->TabIndex = 75;
			this->textBoxM->Text = L"100";
			// 
			// label1
			// 
			this->label1->AccessibleName = L"";
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(71, 530);
			this->label1->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(217, 22);
			this->label1->TabIndex = 76;
			this->label1->Text = L"Число разбиений по Y";
			// 
			// textBoxEps
			// 
			this->textBoxEps->Location = System::Drawing::Point(339, 567);
			this->textBoxEps->Margin = System::Windows::Forms::Padding(5, 6, 5, 6);
			this->textBoxEps->Name = L"textBoxEps";
			this->textBoxEps->Size = System::Drawing::Size(99, 28);
			this->textBoxEps->TabIndex = 77;
			this->textBoxEps->Text = L"0,00000001";
			// 
			// label4
			// 
			this->label4->AccessibleName = L"";
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label4->Location = System::Drawing::Point(71, 573);
			this->label4->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(170, 22);
			this->label4->TabIndex = 78;
			this->label4->Text = L"Точность метода";
			// 
			// textBoxNmax
			// 
			this->textBoxNmax->Location = System::Drawing::Point(339, 634);
			this->textBoxNmax->Margin = System::Windows::Forms::Padding(5, 6, 5, 6);
			this->textBoxNmax->Name = L"textBoxNmax";
			this->textBoxNmax->Size = System::Drawing::Size(99, 28);
			this->textBoxNmax->TabIndex = 79;
			this->textBoxNmax->Text = L"500";
			// 
			// textBoxOmega
			// 
			this->textBoxOmega->Location = System::Drawing::Point(339, 674);
			this->textBoxOmega->Margin = System::Windows::Forms::Padding(5, 6, 5, 6);
			this->textBoxOmega->Name = L"textBoxOmega";
			this->textBoxOmega->Size = System::Drawing::Size(99, 28);
			this->textBoxOmega->TabIndex = 80;
			this->textBoxOmega->Text = L"1";
			// 
			// label5
			// 
			this->label5->AccessibleName = L"";
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label5->Location = System::Drawing::Point(17, 640);
			this->label5->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(299, 22);
			this->label5->TabIndex = 81;
			this->label5->Text = L"Максимальное число итераций";
			// 
			// label6
			// 
			this->label6->AccessibleName = L"";
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label6->Location = System::Drawing::Point(94, 680);
			this->label6->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(167, 22);
			this->label6->TabIndex = 82;
			this->label6->Text = L"Параметр omega";
			// 
			// label7
			// 
			this->label7->AccessibleName = L"";
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label7->Location = System::Drawing::Point(69, 771);
			this->label7->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(215, 22);
			this->label7->TabIndex = 83;
			this->label7->Text = L"Границы отрезка [c,d]";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label8->Location = System::Drawing::Point(309, 771);
			this->label8->Margin = System::Windows::Forms::Padding(5, 0, 5, 0);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(25, 29);
			this->label8->TabIndex = 87;
			this->label8->Text = L"c";
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(337, 773);
			this->textBox3->Margin = System::Windows::Forms::Padding(5, 6, 5, 6);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(79, 28);
			this->textBox3->TabIndex = 86;
			this->textBox3->Text = L"0";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label9->Location = System::Drawing::Point(421, 771);
			this->label9->Margin = System::Windows::Forms::Padding(5, 0, 5, 0);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(27, 29);
			this->label9->TabIndex = 85;
			this->label9->Text = L"d";
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(458, 772);
			this->textBox4->Margin = System::Windows::Forms::Padding(5, 6, 5, 6);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(78, 28);
			this->textBox4->TabIndex = 84;
			this->textBox4->Text = L"1";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(10, 22);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(2564, 1415);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->label9);
			this->Controls->Add(this->textBox4);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->textBoxOmega);
			this->Controls->Add(this->textBoxNmax);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->textBoxEps);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBoxM);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label36);
			this->Controls->Add(this->label33);
			this->Controls->Add(this->label32);
			this->Controls->Add(this->label20);
			this->Controls->Add(this->label18);
			this->Controls->Add(this->textBoxN);
			this->Controls->Add(this->labelTestInfo);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->dataGridView1);
			this->Controls->Add(this->button1);
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
			if (this->label32 == nullptr) return;

			int anchorX = this->label32->Location.X;
			int anchorY = this->label32->Location.Y;

			// Еще более крупные шрифты для лучшей читаемости
			System::Drawing::Font^ titleFont = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold);
			System::Drawing::Font^ mainFont = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Regular);

			if (this->labelMainTaskTitle != nullptr) this->Controls->Remove(this->labelMainTaskTitle);

			this->labelMainTaskTitle = (gcnew System::Windows::Forms::Label());
			this->labelMainTaskTitle->Text = L"ТЕСТОВАЯ ЗАДАЧА (Вариант 1)";
			this->labelMainTaskTitle->Font = titleFont;
			this->labelMainTaskTitle->Location = System::Drawing::Point(anchorX, anchorY);
			this->labelMainTaskTitle->AutoSize = true;

			// Секция уравнения и условий с разделением по строкам
			this->labelEquation = (gcnew System::Windows::Forms::Label());
			this->labelEquation->Text =
				L"Δu(x,y) = -f*(x,y), x ∈ [a,b], y ∈ [c,d]\r\n\r\n" +
				L"u(a,y) = μ1*(y),  u(b,y) = μ2*(y) при y ∈ [c,d]\r\n" +
				L"u(x,c) = μ3*(x),  u(x,d) = μ4*(x) при x ∈ [a,b]\r\n\r\n" +
				L"μ1*(y) = exp(sin²(πay))\r\n" +
				L"μ2*(y) = exp(sin²(πby))\r\n" +
				L"μ3*(x) = exp(sin²(πcx))\r\n" +
				L"μ4*(x) = exp(sin²(πdx))\n\n";

			this->labelEquation->Font = mainFont;
			// Сдвигаем вниз от заголовка
			this->labelEquation->Location = System::Drawing::Point(anchorX, anchorY + 50);
			this->labelEquation->AutoSize = true;

			// Секция точного решения и f*
			this->labelQfunc = (gcnew System::Windows::Forms::Label());
			this->labelQfunc->Text =
				L"u*(x,y) = exp(sin²(πxy))\r\n\r\n" +
				L"f*(x,y) = -(x²+y²)π² exp(sin²(πxy)) [sin²(2πxy) + 2cos(2πxy)]";

			this->labelQfunc->Font = mainFont;
			// Сдвигаем еще ниже, чтобы не было наложения (на 300 пикселей от начала)
			this->labelQfunc->Location = System::Drawing::Point(anchorX, anchorY + 300);
			this->labelQfunc->AutoSize = true;

			this->Controls->Add(this->labelMainTaskTitle);
			this->Controls->Add(this->labelEquation);
			this->Controls->Add(this->labelQfunc);

			this->label32->Visible = false;
		}
	private: void DrawTask() {
		try {
			// 1. Считывание параметров
			double a = Convert::ToDouble(textBox1->Text);
			double b = Convert::ToDouble(textBox2->Text);
			double c = Convert::ToDouble(textBox3->Text);
			double d = Convert::ToDouble(textBox4->Text);

			int n = Convert::ToInt32(textBoxN->Text);
			int m = Convert::ToInt32(textBoxM->Text);
			double eps_met = Convert::ToDouble(textBoxEps->Text);
			int n_max = Convert::ToInt32(textBoxNmax->Text);
			double omega = Convert::ToDouble(textBoxOmega->Text);

			// 2. Расчет
			std::vector<std::vector<double>> u_star(n + 1, std::vector<double>(m + 1));
			std::vector<std::vector<double>> V(n + 1, std::vector<double>(m + 1, 0.0));
			std::vector<std::vector<double>> diff(n + 1, std::vector<double>(m + 1));
			int N = 0; double eps_N = 0, eps_1 = 0, x_err = 0, y_err = 0, R_norm = 0;

			solveDirichleForPuasson(a, b, c, d, n, m, eps_met, n_max, omega,
				u_star, V, diff, N, eps_N, eps_1, x_err, y_err, R_norm);

			// 3. ЗАПОЛНЕНИЕ ТАБЛИЦЫ (обязательно создание колонок!)
			dataGridView1->Columns->Clear();
			dataGridView1->Rows->Clear();
			dataGridView1->Columns->Add("j_col", "j \\ i");
			for (int i = 0; i <= n; i++) {
				dataGridView1->Columns->Add("i" + i, i.ToString());
				dataGridView1->Columns[i + 1]->Width = 70;
			}

			for (int j = 0; j <= m; j++) {
				array<String^>^ row = gcnew array<String^>(n + 2);
				row[0] = j.ToString();
				for (int i = 0; i <= n; i++) {
					row[i + 1] = diff[i][j].ToString("E2"); // Вывод погрешности |u*-v|
				}
				dataGridView1->Rows->Add(row);
			}

			// 4. ФОРМИРОВАНИЕ СПРАВКИ (по образцу бланка отчета)
			System::Text::StringBuilder^ sb = gcnew System::Text::StringBuilder();
			sb->AppendLine("СПРАВКА (Тестовая задача)");
			sb->AppendLine("------------------------------------------------------------------");
			sb->AppendFormat("Сетка: n={0}, m={1}\r\n", n, m);
			sb->AppendFormat("Шаги: hx={0:F4}, hy={1:F4}\r\n", (b - a) / n, (d - c) / m);
			sb->AppendFormat("Параметры МВР: омега={0}, эпсилон_мет={1:E1}, N_max={2}\r\n", omega, eps_met, n_max);
			sb->AppendLine("------------------------------------------------------------------");
			sb->AppendFormat("Затрачено итераций N: \t{0}\r\n", N);
			sb->AppendFormat("Достигнутая точность ε(N): \t{0:E4}\r\n", eps_N);
			sb->AppendFormat("Погрешность эпсилон1 (max|u*-v|): \t{0:E4}\r\n", eps_1);
			sb->AppendFormat("  в узле: \t\t(x={0:F3}, y={1:F3})\r\n", x_err, y_err);
			sb->AppendFormat("Норма невязки ||R||: \t{0:E4}\r\n", R_norm);

			labelTestInfo->Text = sb->ToString();

			// 5. Вызов Python
			System::Diagnostics::ProcessStartInfo^ startInfo = gcnew System::Diagnostics::ProcessStartInfo();
			startInfo->FileName = "dist/plot_3d.exe"; // Убедитесь, что python в PATH или укажите полный путь
			startInfo->CreateNoWindow = true;
			startInfo->UseShellExecute = false;
			System::Diagnostics::Process::Start(startInfo);
		}
		catch (Exception^ ex) {
			MessageBox::Show("Ошибка данных: " + ex->Message);
		}
	}



		   // Событие OnClick для кнопки Draw
private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	try {
		DrawTask();
		// Если используете button2_Click для автомасштабирования, 
		// убедитесь, что логика Zoom адаптирована или отключена, 
		// так как ZedGraphControl1->AxisChange() уже выравнивает оси.
		// this->button2_Click(this->ZoomButton, e); 
	}
	catch (const char* msg) {
		MessageBox::Show(gcnew String(msg), L"Ошибка области определения");
	}
	catch (Exception^ ex) {
		MessageBox::Show(ex->Message, L"Ошибка ввода или вычисления");
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