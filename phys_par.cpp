#include <cmath>
#include <iostream.h>
#include <valarray>		//����� ������ ��� ����� � NN != 1;

const double Pi = 3.141592653589793;

extern const int NN = 3;
extern const double gamma = 3.2;/////////!!!!
extern const double rb0 = 10.0;
extern const double r0 = 21.0;
double rho(double r){return 1;};
double kappa(double r){return 1;};
double sigma(double r){return 0;};
double q(double r){return 0;};
//double p1(double r){return 1;};
/************************************************************/
/*	  "����������" �������, ����������� �����, �� r = r0	*/

double net_rho(double r){return (r<=r0)?rho(r):1;};
double net_kappa(double r){return (r<=r0)?kappa(r):1;};
double net_sigma(double r){return (r<=r0)?sigma(r):0;};
double net_q(double r){return (r<=r0)?q(r):0;};


/********************************************************************/
/*	������������ ����. ��������� ����� ����� ��������� �������:		*/
/*	(a*du/dt + b*du/dr + c*u)|_(r = rb0 || r0) = ... + f_(rb0 || r0)*/
/*	� ����� �������������� � ��������� �������� � � ����� ����.		*/
/*	���������  -- ��. � ����� �����									*/


														
/********************************************************************/

/********************************************************************************/
/*							������ ��� ������									*/
/*			              ���� 1: ������� �����									*/

int m = 2;
double omega = Pi * m /(r0 - rb0);
char* ff;
double& use_omega()								
{													//������-�� ������ use_omega ��������
//	cout <<"omega in use_omega = "<<omega<<'\n';	//omega = 0, ������� ����� ������������ ������
	static double om = Pi * m /(r0 - rb0);			// <-- ����� ���������. ������������� �����
//	cout <<"om in use_omega = "<<om<<'\n';			//����������: �� ��������� � use_omega, �� 
//	cin >> ff;										//�������� ���������� ����� omega, ����� �����	
	return om;										//� Net_par.cpp � ��� ���������� �������� �����
};													//���� ������ � ������������ ���������
													//Pi * m /(r0 - rb0); ��������� �� � u_static
													//����� ����� � main.cpp, � ���� ��������� ����-
													//������ � ���� omega.
const double oo = use_omega();
//double h_t = 1.0; double h_x = 2.0;			//�� ������ �������� �������� K �/��� fc � Net_par.cpp
double h_t = 0.6; double h_x = 2.0;
/*	�������������� �����:
	omega_tild ��������� � �������  MATHEMATICA  ConsTest.nb  �� ���������
 
	tg(omega_tild * h_t / 2) = (h_t/h_x)*sin(omega * h_x/2)

	��� m = 1, r0 = 20, rb0 = 10, h_x = 2 (�. �. K = 5), h_t = 1 (�. �. fc = 0.5)
			omega_tild = 0.306592585897309;
	��� m = 1, r0 = 20, rb0 = 10, h_x = 2 (�. �. K = 5), h_t = 0.6 (�. �. fc = 0.3)
			omega_tild = 0.3081362764762855
	��� m = 2, r0 = 20, rb0 = 10, h_x = 2 (�. �. K = 5), h_t = 0.6 (�. �. fc = 0.3)
			omega_tild = 0.5818042033204008
*/
//double omega_tild = 0.306592585897309;
//double omega_tild = 0.3081362764762855;
//double omega_tild = 0.5818042033204008;

/*	����� "�����":
	omega_tild ��������� � �������  MATHEMATICA  CrosTest.nb  �� ���������
 
	sin(omega_tild * h_t / 2) = (h_t/h_x)*sin(omega * h_x/2)

	��� m = 1, r0 = 20, rb0 = 10, h_x = 2 (�. �. K = 5), h_t = 1 (�. �. fc = 0.5)
			omega_tild = ;
	��� m = 1, r0 = 20, rb0 = 10, h_x = 2 (�. �. K = 5), h_t = 0.6 (�. �. fc = 0.3)
			omega_tild = ;
	��� m = 2, r0 = 20, rb0 = 10, h_x = 2 (�. �. K = 5), h_t = 0.6 (�. �. fc = 0.3)
			omega_tild = 0.590874802986392
*/




double omega_tild =  0.676914121276099;


//		������ �������:															
extern double u_static1(double r, double t){return sin(omega_tild * t) * sin(omega *(r - rb0));};
extern double u_static2(double r, double t){return cos(omega_tild * t) * sin(omega *(r - rb0));};
extern double u_static3(double r, double t){return sin(omega_tild * t) * cos(omega *(r - rb0));};
extern double u_travelling(double r, double t){return
										 sin( omega_tild * t - omega * (r-rb0) );};

/********************************************************************************/
/*						��������� ������� ���  u_static1						*/
//				�� ������:	a_rb0= 0; b_rb0 = 0; c_rb0 = 1;
//							a_r0 = 0; b_r0 = 0; c_r0 = 1; 
/*
extern double u_0_init(double r){return 0;};
extern double u_1_init(double r)
	{return sin(omega_tild* h_t/2)/(h_t/2) *sin(omega*(r-rb0));};
*/
/********************************************************************************/
/*						��������� ������� ���  u_static2						*/
//				�� ������:	a_rb0= 0; b_rb0 = 0; c_rb0 = 1;
//							a_r0 = 0; b_r0 = 0; c_r0 = 1; 
/*
/*
extern double u_0_init(double r)
	{return cos(omega_tild* h_t/2) *sin(omega*(r-rb0));};
extern double u_1_init(double r){return 0;};
*/
/********************************************************************************/
/********************************************************************************/
/*						��������� ������� ���  u_static3						*/
//				�� ������:	a_rb0= 0; b_rb0 = 1; c_rb0 = 0;
//							a_r0 = 0; b_r0 = 1; c_r0 = 0; 

extern double u_0_init(double r){return 0;};
extern double u_1_init(double r)
	{ 
	double ff;
	if((fabs(r - rb0) 
		> 0.25*h_t)&
		(fabs(r0 - r) > 
		0.25*h_t))
			ff = sin(omega_tild* h_t/2.0)/(h_t/2.0) *cos(omega*(r-rb0));
	else
			ff = sin(omega_tild* h_t/2.0)/(h_t/2.0) *cos(omega*(r-rb0))*cos(omega*h_x/2)
	;
		return ff;
	};

/********************************************************************************/
/*			              ���� 2: ������� �����									*/

//	������ �������: u(r, t) = sin( omega_tild * t - omega * (r-rb0) ) 
//	��������� �������:
/*
extern double u_0_init(double r){return (0.0 - cos(omega_tild*h_t/2)*sin(omega*(r-rb0)));};
extern double u_1_init(double r)
	{ 
	double ff;
	if((fabs(r - rb0) 
		> 0.25*h_t)&
		(fabs(r0 - r) > 
		0.25*h_t))
			ff = sin(omega_tild* h_t/2.0)/(h_t/2.0) *cos(omega*(r-rb0));
	else
			ff = sin(omega_tild* h_t/2.0)/(h_t/2.0) *cos(omega*(r-rb0))*cos(omega*h_x/2)
	;
		return ff;
	};
*/
//��������� �������:
//������� 1: a_r0 = b_r0 = a_rb0 = b_rb0 = 0; c_r0 = c_rb0 = 1;
/*
extern double f_rb0(double t)
{
	return 0.25*( 
		sin( omega_tild*(t + h_t/2) - omega * ( - h_x/2) ) +
		sin( omega_tild*(t + h_t/2) - omega * (   h_x/2) ) +
		sin( omega_tild*(t - h_t/2) - omega * ( - h_x/2) ) +
		sin( omega_tild*(t - h_t/2) - omega * (   h_x/2) )
		);
};
extern double f_r0(double t)
{
	return 0.25*(
		sin( omega_tild*(t + h_t/2) - omega * ( r0 - rb0 - h_x/2) ) +
		sin( omega_tild*(t + h_t/2) - omega * ( r0 - rb0 + h_x/2) ) +
		sin( omega_tild*(t - h_t/2) - omega * ( r0 - rb0 - h_x/2) ) +
		sin( omega_tild*(t - h_t/2) - omega * ( r0 - rb0 + h_x/2) )
		);
};
*/

/*������� 2: 

�������������� �����:
 
a_rb0 = 1;
b_rb0 = cos(use_omega()*h_x/2);
c_rb0 = 0;

a_r0 = 1;
b_r0 = cos(use_omega()*h_x/2);
c_r0 = 0;

����� �����:

a_rb0 = 1;
b_rb0 = cos(use_omega()*h_x/2)/cos(omega_tild*h_t/2);
c_rb0 = 0;

a_r0 = 1;
b_r0 = cos(use_omega()*h_x/2)/cos(omega_tild*h_t/2);
c_r0 = 0;
*/

/*						��������� ������ ��� ������								*/
/********************************************************************************/
extern double f_internal(double r, double t){return 0;};
double f_rb0(double t)
{
	return 0;
};
double f_r0(double t)
{
	return 0;
};
/********************************************************************************/
/*
struct phys_par
{
	double A_rb0;
	double B_rb0;
	double C_rb0, A_r0, B_r0, C_r0 ;
	phys_par();
	~phys_par();
};

phys_par::phys_par()
{
	cout << "      constructor for phys_par"<<'\n';
	A_rb0 = 1; 
	B_rb0 = b_rb0; 
	C_rb0 = c_rb0;
	A_r0 = a_r0; B_r0 = b_r0; C_r0 = c_r0;
	cout << A_rb0 <<'\t'<< B_rb0<<'\t'<< C_rb0<<'\t'<< A_r0 <<'\t'<< B_r0<<'\t'<< C_r0<<'\n' ;
	char* ch = "ch";
	cin>>ch;
};
phys_par::~phys_par(){cout << "destructor for phys_par"<<'\n';};
*/
/*
struct phys_par
{
	static double A_rb0;
	static double B_rb0;
	static double C_rb0, A_r0, B_r0, C_r0 ;
	phys_par();
	~phys_par();
};

phys_par::phys_par()
{
	cout << "      constructor for phys_par"<<'\n';
	cout << A_rb0 <<'\t'<< B_rb0<<'\t'<< C_rb0<<'\t'<< A_r0 <<'\t'<< B_r0<<'\t'<< C_r0<<'\n' ;
//	char* ch = "ch";
//	cin>>ch;
};

phys_par::~phys_par(){cout << "destructor for phys_par"<<'\n';};
double phys_par::A_rb0 = 1.0;
double phys_par::B_rb0 = cos(use_omega()*h_x/2);
double phys_par::C_rb0 = 0.0;
double phys_par::A_r0 = 1.0;
double phys_par::B_r0 = cos(use_omega()*h_x/2);
double phys_par::C_r0 = 0.0;

/*extern const*///phys_par ph_p0 = phys_par();
/*
extern phys_par& use_ph_p()
{	
	static phys_par jj = phys_par();
	return jj;
};
phys_par ph_p0 = use_ph_p();
*/
extern double& use_a_rb0()
{	
	static double jj = 0.0;
	return jj;
};
extern double& use_b_rb0()
{	
//	static double jj = cos(use_omega()*h_x/2);	//��� �������������� �����
//	static double jj = cos(use_omega()*h_x/2)/cos(omega_tild*h_t/2);	//��� ����� "�����"
	static double jj = -1.0;
	return jj;
};
extern double& use_c_rb0()
{	
	static double jj = 0.0;
	return jj;
};
extern double& use_a_r0()
{	
	static double jj = 0.0;
	return jj;
};
//char* fff;
extern double& use_b_r0()
{
//	cout << ::omega <<'\n';
//	cout << b_r0<<'\n';
//	static double jj = cos(use_omega()*h_x/2);	//��� �������������� �����
//	static double jj = cos(use_omega()*h_x/2)/cos(omega_tild*h_t/2);	//��� ����� "�����"
	static double jj = 1.0;
//	cout << "jj in use_b_r0 ="<<jj<<'\n';
//	cin>>fff;
	return jj;
};
extern double& use_c_r0()
{	
	static double jj = 0.0;
	return jj;
};

/********************************************************************************/