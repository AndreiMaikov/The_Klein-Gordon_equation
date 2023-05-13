#include <iostream.h>
#include <valarray>
#include "Net_Gen.h"
#include "Net_oper.h"
#include "IterSt_P.h"
#include "Net_Par.h"
#include "phys_par.h"

#include <cmath>


using std::valarray;

extern void print_valarray_length(const valarray<double>&,int = 10);

extern double weight_matrix[4][3];

char character_for_pause;

valarray<double>LambdaX(const valarray<double> U,
						const valarray<double> L0,
						const valarray<double> Lpls,
						const valarray<double> Lmns
						)
	{
		return L0*(U) +
			   Lpls*(U.shift(1)) +
			   Lmns*(U.shift(-1));
	};


void main()
{
	cout<<"\t*** begin main ***"<<'\n';
//	cout << "f_alpha(1) = " << f_alpha(1) <<'\n';
//	cout << "f_beta(1) = " << f_beta(1) <<'\n';
//	cout << "\nBeta: "<<"\n";
//	print_valarray_length(Beta,10);
//	cout << "\nTab_r_int: "<<"\n";
//	cout << "Tab_r_int: "; print_valarray_length(Tab_r_int, 10);


/*
	const NetOperators NetOp;

	const valarray<double>* P_Epsilon = &(NetOp.Epsilon);

	const valarray<double>* P_LF00 = &(NetOp.LF00);
	.....................................................
//	так делать в принципе можно, но тогда не удастся уничтожить
//	объект NetOperators NetOp, а он использует довольно много памяти.
*/
/*
	const NetOperators NetOp;

	const valarray<double> P_Epsilon = (NetOp.Epsilon);
	......................................................
//	можно было бы уничтожать NetOperators NetOp, но для этого просто
//	надо использовать стандартный синтаксис new -- delete (т. е. ини-
//	циировать не сам объект NetOperators NetOp, а указатель на него
//	(см. ниже)
*/

	NetOperators* P_NetOp = new NetOperators;

	const valarray<double> Epsilon = (P_NetOp->Epsilon);

	const valarray<double> LF00 = (P_NetOp->LF00);
	const valarray<double> LF10 = (P_NetOp->LF10);
	const valarray<double> LF20 = (P_NetOp->LF20);

	const valarray<double> LF0pls = (P_NetOp->LF0pls);
	const valarray<double> LF1pls = (P_NetOp->LF1pls);
	const valarray<double> LF2pls = (P_NetOp->LF2pls);

	const valarray<double> LF0mns = (P_NetOp->LF0mns);
	const valarray<double> LF1mns = (P_NetOp->LF1mns);
	const valarray<double> LF2mns = (P_NetOp->LF2mns);
/********************************************************/
/*					Только для теста					*/
	const valarray<double> L0 = (P_NetOp->TestL0);
	const valarray<double> Lpls = (P_NetOp->TestLpls);
	const valarray<double> Lmns = (P_NetOp->TestLmns);
	      valarray<double> Control(0.0, K+2);
	

/*														*/
/********************************************************/

	delete P_NetOp;

//	cout << "LF00: "; print_valarray_length(LF00, 10);

	cout << "CRight1 = " << CRight1 << '\n';
	cout << "CLeft0 = " << CLeft0 << '\n';
	cout << "f_rb0(1) = " << f_rb0(1) << '\n';
	cout << "in main h_x = " << h_x << '\n';
	cout << "in main h_t = " << h_t << '\n';


	cout << "  LF00:";
	print_valarray_length(LF00);
	cout << "  LF10:";
	print_valarray_length(LF10);
	cout << "  LF20:";
	print_valarray_length(LF20);
/*	cout << "  LF0pls:";
	print_valarray_length(LF0pls);
	cout << "  LF1pls:";
	print_valarray_length(LF1pls);
	cout << "  LF2pls:";
	print_valarray_length(LF2pls);
	cout << "  LF0mns:";
	print_valarray_length(LF0mns);
	cout << "  LF1mns:";
	print_valarray_length(LF1mns);
	cout << "  LF2mns:";
	print_valarray_length(LF2mns);
*/

/********************************************************************************/
/*	Инициализация начальных условиий U2init и U1init			*/   
/*	U0, U0New, U0Prev, U1 = U1init, U2 = U2init				*/
/*				)						*/

/*	valarray<double>U2init(0.0, K + 2);
	valarray<double>U1init(0.0, K + 2);
	NetData* P_NetDat = new NetData;
	U1init = P_NetDat->U1init;
	U2init = P_NetDat->U2init;
	delete P_NetDat;
	cout << "U1init: " << '\n';
	print_valarray_length(U1init,10);
	cin >> character_for_pause;
*/
	valarray<double>U2init(0.0, K + 2);
	valarray<double>U1init(0.0, K + 2);
	NetData* P_NetDat = new NetData;
//	U1init = P_NetDat->U1init;
//	U2init = P_NetDat->U2init;
	delete P_NetDat;
/********************************************************************************/
/*							Только для теста с NN != 1							*/

//						Для NN = 2;	gammma =0; K = 5; fc = 2;
//	{0.2367407537764706,-0.2367407537764706,-0.5496392412230395,
//	-0.6257641411610598,-0.4715947967519451,-0.1669374353539749,0.1669374353539749};
//					      omega_tild_Vec =  0.3043594240208501
	const double Vec[] = {0.6464850627430188,0.6464850627430188,0.5370050592066881,0.3519290866767011,
  0.1342298627898095,-0.07144432577829789,-0.2271204346311821,-0.\
3084200194700978,-0.3084200194700978};
double omega_tild_Vec =  0.3200243368887432;
	std::valarray<double>ValVec(Vec, K+2);
//						Точное решение -- sin(omega_tild*t)*ValVec				
	
/*																				*/
/********************************************************************************/

	double SIN = cos(-omega_tild_Vec*h_t/2);
	U2init =   SIN*ValVec;
	U1init =   SIN*(ValVec);
	double SIN_nn;
/*																				*/
/********************************************************************************/
	cout << "U2init: ";
	cout << "omega_tild_Vec = "<< omega_tild_Vec <<'\n';
	cin>>character_for_pause;
	print_valarray_length(U2init,10);
	cout << "U1init: ";
	print_valarray_length(U1init,10);
	cin >> character_for_pause;

//	valarray<double>U2 = U2init;
//	valarray<double>U1 = U1init;
	valarray<double>U0Prev(0.0, K + 2);
	valarray<double>U0New(0.0, K + 2);
//	valarray<double>&U0 = U0Prev;
//	print_valarray_length(U0,3);
	valarray<double>VF_internal(0.0, K+2);

	valarray<double>U12F(0.0, K + 2);
	double UIFRight;
	double UIFLeft;

	valarray<double>* P_U2 = &U2init;
	valarray<double>* P_U1 = &U1init;
	valarray<double>* P_U0Prev = &U0Prev;
	valarray<double>* P_U0New = &U0New;
	valarray<double>* temp_adress = P_U0Prev;

//	cout << temp_adress <<'\t'<<P_U0New<<'\t'<<P_U0Prev<<'\t'<<P_U1<<'\t'<<P_U2<<"\n\n";
/********************************************************************************/
/*	Точное решение:															*/
//	#define f_u_prec u_static1;
/*																				*/
/********************************************************************************/
/********************************************************************************/
/*							Начало цикла по  n									*/
	for (int nn = nn_0; nn <= nn_max ; nn++)
	{
		cout<< "nn = " << nn <<'\n';
		
		for (int k = 1; k<=K; k++)
		{
			VF_internal[k] = f_internal(Tab_r_int[k], (nn-1.5)*h_t);
		};
		U12F = LF10 * (*P_U1) + LF1pls * (P_U1->shift(1)) + LF1mns * (P_U1->shift(-1))+
			   LF20 * (*P_U2) + LF2pls * (P_U2->shift(1)) + LF2mns * (P_U2->shift(-1))+	
			   Epsilon * VF_internal;
		UIFRight = CRight2 * (*P_U1)[K+1] + CRight3 *(*P_U1)[K] + 
			CRight0 * (
			/* слагаемые из условий излучения (см. с. -07_6- ) + */ 
			f_r0( (nn - 1)*h_t )
			);
		UIFLeft = CLeft2 * (*P_U1)[0] + CLeft3 * (*P_U1)[1] + 
			CLeft0 * (
			/* слагаемые из условий излучения (см. с. -07_6- ) + */ 
			f_rb0( (nn - 1)*h_t )
			);

		F_IterStep_Pointer(P_U1, P_U0New, 
						   U12F, UIFRight, UIFLeft,
					       LF00, LF0pls, LF0mns,
					       CRight1, CLeft1
					  );
//		cout << "WM : " << !weight_matrix[0][0] << '\n';
/*		cout << "! Crit = " << 
			(((!weight_matrix[0][0]) || (!weight_matrix[0][2])) &
			( !IterCrit(*P_U1, *P_U0New, iteration_precision) ))
			<< '\n';

		bool crit = bool(
			((weight_matrix[0][0] != 0) || (weight_matrix[0][2] != 0 ))
			&
			( !IterCrit(*P_U1, *P_U0New, iteration_precision))
			);
		cout <<   "          crit = " << crit <<'\n';
*/
		cout << "!IterCrit(*P_U0Prev, *P_U0New, iteration_precision) =" <<
       		   ( !IterCrit(*P_U0Prev, *P_U0New, iteration_precision) ) << '\n';
/****************************************************************************************/
/*								Итерационный цикл										*/
		if ( ((weight_matrix[0][0] != 0) || (weight_matrix[0][2] != 0 ))
			 &
			 ( !IterCrit(*P_U1, *P_U0New, iteration_precision))
		   )
		{
			int jj = 0;
//			cout << "!IterCrit(*P_U0Prev, *P_U0New, iteration_precision) =" <<
//				( !IterCrit(*P_U0Prev, *P_U0New, iteration_precision) ) << '\n';
			do 
			{
				temp_adress = P_U0New;
				P_U0New = P_U0Prev;
				P_U0Prev = temp_adress;

				F_IterStep_Pointer(P_U0Prev, P_U0New, 
								   U12F, UIFRight, UIFLeft,
								   LF00, LF0pls, LF0mns,
								   CRight1, CLeft1
								   );
				jj++;
//				cout << "jj = " << jj << '\n';
/*				Control = ((*P_U0New )+ (*P_U2) - 2.0 * (*P_U1))/h_t/h_t - 
//					LambdaX(U1, L0, Lpls, Lmns);
					(
					((*P_U0Prev).shift(-1) + (*P_U0Prev).shift(1) - 2.0 * (*P_U0Prev))/h_x/h_x/4.0 +
					((*P_U1).shift(-1) + (*P_U1).shift(1) - 2.0 * (*P_U1))/h_x/h_x/2.0 +
					((*P_U2).shift(-1) + (*P_U2).shift(1) - 2.0 * (*P_U2))/h_x/h_x/4.0
					); 
				cout << "     Control for iterations";
				print_valarray_length(Control,10);
				cin >> character_for_pause;
*/
			}
			while( !IterCrit(*P_U0Prev, *P_U0New, iteration_precision) );
		};

/*							Окончание итерационного цикла								*/
/****************************************************************************************/

		cout << "U0 :";
		print_valarray_length(*P_U0New);
		/* 
		//Для консервативной схемы:
		Control = ((*P_U0New )+ (*P_U2) - 2.0 * (*P_U1))/h_t/h_t - 
//			LambdaX(U1, L0, Lpls, Lmns);
			(
			((*P_U0New).shift(-1) + (*P_U0New).shift(1) - 2.0 * (*P_U0New))/h_x/h_x/4.0 +
			((*P_U1).shift(-1) + (*P_U1).shift(1) - 2.0 * (*P_U1))/h_x/h_x/2.0 +
			((*P_U2).shift(-1) + (*P_U2).shift(1) - 2.0 * (*P_U2))/h_x/h_x/4.0
			);
		*/
		//Для схемы "крест":
		Control = ((*P_U0New )+ (*P_U2) - 2.0 * (*P_U1))/h_t/h_t - 
//			LambdaX(U1, L0, Lpls, Lmns);
			(
//			((*P_U0New).shift(-1) + (*P_U0New).shift(1) - 2.0 * (*P_U0New))/h_x/h_x/4.0 +
			((*P_U1).shift(-1) + (*P_U1).shift(1) - 2.0 * (*P_U1))/h_x/h_x 
//			+((*P_U2).shift(-1) + (*P_U2).shift(1) - 2.0 * (*P_U2))/h_x/h_x/4.0
			);
		cout << "Control_0";
		print_valarray_length(Control,10);
		Control = ((*P_U0New )+ (*P_U2) - 2.0 * (*P_U1))/h_t/h_t - 
			LambdaX((*P_U0New)/4.0 + (*P_U1)/2.0 + (*P_U2)/4.0, L0, Lpls, Lmns);
		cout << "Control_Lambda";
		print_valarray_length(Control,10);
//			((*P_U1).shift(-1) + (*P_U1).shift(1) - 2.0 * (*P_U1))/h_x/h_x; 
		valarray<double> u_prec0(0.0, K+2);
		for (k = 0; 
					k<=K+1; 
					k++){
			u_prec0[k] = u_static3(Tab_r_int[k],(nn-1.0/2.0)*h_t);
		};
		SIN_nn = cos(omega_tild_Vec*(nn - 0.5)*h_t);
		u_prec0 = SIN_nn*ValVec;
		valarray<double> u_prec1(0.0, K+2);
		for (k = 0; 
					k<=K+1; 
					k++){
			u_prec1[k] = u_static3(Tab_r_int[k],(nn-3.0/2.0)*h_t);
		};
		SIN_nn = cos(omega_tild_Vec*(nn - 1.5)*h_t);
		u_prec1 = SIN_nn*ValVec;
		valarray<double> u_prec2(0.0, K+2);
		for (k = 0; 
					k<=K+1; 
					k++){
			u_prec2[k] = u_static3(Tab_r_int[k],(nn-5.0/2.0)*h_t);
		};
		SIN_nn = cos(omega_tild_Vec*(nn - 2.5)*h_t);
		u_prec2 = SIN_nn*ValVec;
		Control = ((u_prec0 )+ (u_prec2) - 2.0 * (u_prec1))/h_t/h_t - 
			LambdaX((u_prec0)/4.0 + (u_prec1)/2.0 + (u_prec2)/4.0, L0, Lpls, Lmns);
		cout << "    Control for u_prec ";
		print_valarray_length(Control,10);
//		double omega;
		omega = use_omega();
		cout << "    du/dt + cos(omega*h_x/2)*du/dx|_(r=rb0):"<<'\n';
		cout << (u_prec0[1]+u_prec0[0]-u_prec1[1]-u_prec1[0])/2/h_t +
			cos(omega*h_x/2)*
			(u_prec0[1]-u_prec0[0]+u_prec1[1]-u_prec1[0])/2/h_x
			<< '\n';
		cout << "    du/dt + cos(omega*h_x/2)*du/dx|_(r=r0):"<<'\n';
		cout << (u_prec0[K+1]+u_prec0[K]-u_prec1[K+1]-u_prec1[K])/2/h_t +
			cos(omega*h_x/2)*
			(u_prec0[K+1]-u_prec0[K]+u_prec1[K+1]-u_prec1[K])/2/h_x
			<< '\n';
		cout << "    d(U0New)/dt + cos(omega*h_x/2)*d(U0New)/dx|_(r=r0):"<<'\n';
		cout << ((*P_U0New)[K+1]+(*P_U0New)[K]-(*P_U1)[K+1]-(*P_U1)[K])/2/h_t +
			cos(omega*h_x/2)*
			((*P_U0New)[K+1]-(*P_U0New)[K]+(*P_U1)[K+1]-(*P_U1)[K])/2/h_x
			<< '\n';
		cin >> character_for_pause;
//		cout << "U12F :";
//		print_valarray_length(U12F);
//		print_valarray_length(u_prec0);
		cout << "coeff" ;
		print_valarray_length((*P_U0New)/u_prec0);
		print_valarray_length((*P_U1)/u_prec1);
		print_valarray_length((*P_U2)/u_prec2);
//		print_valarray_length(U0New/u_prec0);
		cout << "    U0New : ";
		print_valarray_length(U0New);
		cin >> character_for_pause;
		temp_adress = P_U2;
		P_U2 = P_U1;
		P_U1 = P_U0New;
		P_U0New = temp_adress;
//		cout << temp_address <<'\t'<<P_U0New<<'\t'<<P_U0Prev<<'\t'<<P_U1<<'\t'<<P_U2<<'\n';
	};
	

	cout<<"\t*** end main ***"<<'\n';
}	